#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>
#include <WebSocketsServer.h>
#include <arduinoFFT.h>
#include <driver/i2s.h>

const i2s_port_t I2S_PORT = I2S_NUM_0;
const int BLOCK_SIZE = 512;

const double signalFrequency = 1000;
const double samplingFrequency = 10000;
const uint8_t amplitude = 150;

double vReal[BLOCK_SIZE];
double vImag[BLOCK_SIZE];
int32_t samples[BLOCK_SIZE];

String labels[] = {"125", "250", "500", "1K", "2K", "4K", "8K", "16K"};

arduinoFFT FFT = arduinoFFT(); /* Create FFT object */

// Nombre y contraseña de AP
const char *ssid = "EmbebidosAP";
const char *password = "1234567890";

int bands[8] = {0, 0, 0, 0, 0, 0, 0, 0};

// Running a web server
WiFiServer server(80);

// Adding a websocket to the server
WebSocketsServer webSocket = WebSocketsServer(81);

// Serving a web page (from flash memory)
// formatted as a string literal!
char webpage[] PROGMEM = R"=====(
<html>
<head>
  <script src='https://cdnjs.cloudflare.com/ajax/libs/Chart.js/2.5.0/Chart.min.js'></script>
</head>
<body onload="javascript:init()">

<center>
<h1>Proyecto Final Fundamentos de Sistemas Embebidos 2019</h1>
<h2>Analizador de Espectro de Audio</h2>
<h2>Guzman Sanchez Jose, Emmanuel</h2>
<h2>Mejia Ortiz, Aaron Enrique</h2>
<h2>Saenz Barragan, Ricardo</h2>

<h3>Grupo: 02</h3>
<h3>Profesor: DR. ROBERTO GIOVANNI RAMIREZ CHAVARRIA</h3>
<div>
  <canvas id="chart" width="600" height="400"></canvas>
</div>

<button onclick="backColor()"> <- Anterior </button>
<button onclick="nextColor()"> Siguiente -> </button>

</center>

<!-- Adding a websocket to the client (webpage) -->
<script>
  var webSocket, dataPlot;
  var maxDataPoints = 20;
  var colorIndex = 0;
  const maxValue = 30000000;
  const maxLow = maxValue * 0.4;
  const maxMedium = maxValue * 0.3;
  const maxHigh = maxValue * 0.3;

  const colorBars = [
  ["#09FBD3", "#FE53BB", "#F5D300"],
  ["#f547c3", "#eb0450", "#7a0406"],
  ["#D6E9C6", "#FAEBCC", "#EBCCD1"]
  ];

  function nextColor(){

    if (colorIndex != 2) {
      document.body.style.backgroundColor = "black";
      document.body.style.color = "white";
      dataPlot.options.legend.display = false;
      dataPlot.options.scales.xAxes[0].gridLines.display = false;
      dataPlot.options.scales.yAxes[0].gridLines.display = false;
    }else{
      document.body.style.backgroundColor = "white";
      document.body.style.color = "black"; 
      dataPlot.options.legend.display = true;
      dataPlot.options.scales.xAxes[0].gridLines.display = true;
      dataPlot.options.scales.yAxes[0].gridLines.display = true;
    }
    
    dataPlot.data.datasets[0].backgroundColor = colorBars[colorIndex][0];
    dataPlot.data.datasets[1].backgroundColor = colorBars[colorIndex][1];
    dataPlot.data.datasets[2].backgroundColor = colorBars[colorIndex][2];

    colorIndex ++;
    if (colorIndex >= 3){
      colorIndex = 0;
    }
  }

  function backColor() {

    if (colorIndex != 2) {
      document.body.style.backgroundColor = "black";
      document.body.style.color = "white";
      dataPlot.options.legend.display = false;
      dataPlot.options.scales.xAxes[0].gridLines.display = false;
      dataPlot.options.scales.yAxes[0].gridLines.display = false;
    }else{
      document.body.style.backgroundColor = "white";
      document.body.style.color = "black"; 
      dataPlot.options.legend.display = true;
      dataPlot.options.scales.xAxes[0].gridLines.display = true;
      dataPlot.options.scales.yAxes[0].gridLines.display = true;
    }
    
    dataPlot.data.datasets[0].backgroundColor = colorBars[colorIndex][0];
    dataPlot.data.datasets[1].backgroundColor = colorBars[colorIndex][1];
    dataPlot.data.datasets[2].backgroundColor = colorBars[colorIndex][2];

    colorIndex --;
    if (colorIndex <= -1){
      colorIndex = 2;
    }
  }

  function init() {
    webSocket = new WebSocket('ws://' + window.location.hostname + ':81/');
    dataPlot = new Chart(document.getElementById("chart"), {
      type: 'bar',
      data: {
        labels: [],
        datasets: [{
          data: [],
          label: "Bajo",
          backgroundColor: "#D6E9C6"
        },
        {
          data: [],
          label: "Moderado",
          backgroundColor: "#FAEBCC"
        },
        {
          data: [],
          label: "Alto",
          backgroundColor: "#EBCCD1"
        },
        ]
      }, 
      options: {
          legend: {
            display: true
          },
          responsive: false,
          animation: false,
          scales: {
              xAxes: [{ 
                stacked: true,
                gridLines: {display:false}
              }],
              yAxes: [{
                  display: true,
                  stacked: true,
                  gridLines: {display:false},
                  ticks: {
                    beginAtZero: true,
                    steps: 1000,
                    stepValue: 500,
                    max: maxValue
                  }
              }]
           }
       }
    });
    webSocket.onmessage = function(event) {
      var data = JSON.parse(event.data);
      dataPlot.data.labels = [];
      dataPlot.data.datasets[0].data = [];
      dataPlot.data.datasets[1].data = [];
      dataPlot.data.datasets[2].data = [];
      
      data.forEach(function(element) {
        dataPlot.data.labels.push(element.bin);
        var lowValue = Math.min(maxLow, element.value);
        dataPlot.data.datasets[0].data.push(lowValue);
        
        var mediumValue = Math.min(Math.max(0, element.value - lowValue), maxMedium);
        dataPlot.data.datasets[1].data.push(mediumValue);
        
        var highValue = Math.max(0, element.value - lowValue - mediumValue);
        dataPlot.data.datasets[2].data.push(highValue);
      });
      dataPlot.update();
    }
  }
</script>
</body>
</html>
)=====";


void setupMic() {
  Serial.println("Configuring I2S...");
  esp_err_t err;

  // The I2S config as per the example
  const i2s_config_t i2s_config = {
      .mode = i2s_mode_t(I2S_MODE_MASTER | I2S_MODE_RX), // Receive, not transfer
      .sample_rate = samplingFrequency,                        
      .bits_per_sample = I2S_BITS_PER_SAMPLE_32BIT, // could only get it to work with 32bits
      .channel_format = I2S_CHANNEL_FMT_ONLY_RIGHT, // although the SEL config should be left, it seems to transmit on right
      .communication_format = i2s_comm_format_t(I2S_COMM_FORMAT_I2S | I2S_COMM_FORMAT_I2S_MSB),
      .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,     // Interrupt level 1
      .dma_buf_count = 4,                           // number of buffers
      .dma_buf_len = BLOCK_SIZE                     // samples per buffer
  };

  // The pin config as per the setup
    i2s_pin_config_t pin_config = {
        .bck_io_num = 26,  // IIS_SCLK
        .ws_io_num = 32,   // IIS_LCLK
        .data_out_num = -1,// IIS_DSIN
        .data_in_num = 33  // IIS_DOUT
    };

  // Configuring the I2S driver and pins.
  // This function must be called before any I2S driver read/write operations.
  err = i2s_driver_install(I2S_PORT, &i2s_config, 0, NULL);
  if (err != ESP_OK) {
    Serial.printf("Failed installing driver: %d\n", err);
    while (true);
  }
  err = i2s_set_pin(I2S_PORT, &pin_config);
  if (err != ESP_OK) {
    Serial.printf("Failed setting pin: %d\n", err);
    while (true);
  }
  Serial.println("I2S driver installed.");
}



void setup() {
  Serial.begin(115200);
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  delay(1000);
  setupMic();

  delay(1000);
  server.begin();
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
}

void loop() {
  WiFiClient client = server.available(); 
  webSocket.loop();
  
  if (client) {                             // if you get a client,
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            client.println(webpage);
            // The HTTP response ends with another blank line:
            client.println();
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    client.stop();
  }

  // Read multiple samples at once and calculate the sound pressure
  int num_bytes_read = i2s_read_bytes(I2S_PORT, 
                                      (char *)samples, 
                                      BLOCK_SIZE,     // the doc says bytes, but its elements.
                                      portMAX_DELAY); // no timeout
                               

  for (uint16_t i = 0; i < BLOCK_SIZE; i++) {
    vReal[i] = samples[i] << 8;
    vImag[i] = 0.0; //Imaginary part must be zeroed in case of looping to avoid wrong calculations and overflows
  }

  FFT.Windowing(vReal, BLOCK_SIZE, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  FFT.Compute(vReal, vImag, BLOCK_SIZE, FFT_FORWARD);
  FFT.ComplexToMagnitude(vReal, vImag, BLOCK_SIZE);
  for (int i = 0; i < 8; i++) {
    bands[i] = 0;
  }
  
  for (int i = 2; i < (BLOCK_SIZE/2); i++){
    if (vReal[i] > 2000) { // Add a crude noise filter, 10 x amplitude or more
      if (i<=2 )             bands[0] = max(bands[0], (int)(vReal[i]/amplitude)); // 125Hz
      if (i >3   && i<=5 )   bands[1] = max(bands[1], (int)(vReal[i]/amplitude)); // 250Hz
      if (i >5   && i<=7 )   bands[2] = max(bands[2], (int)(vReal[i]/amplitude)); // 500Hz
      if (i >7   && i<=15 )  bands[3] = max(bands[3], (int)(vReal[i]/amplitude)); // 1000Hz
      if (i >15  && i<=30 )  bands[4] = max(bands[4], (int)(vReal[i]/amplitude)); // 2000Hz
      if (i >30  && i<=53 )  bands[5] = max(bands[5], (int)(vReal[i]/amplitude)); // 4000Hz
      if (i >53  && i<=200 ) bands[6] = max(bands[6], (int)(vReal[i]/amplitude)); // 8000Hz
      if (i >200           ) bands[7] = max(bands[7], (int)(vReal[i]/amplitude)); // 16000Hz
    }
  }
  getData();
}

void getData() {

  String json = "[";
  for (int i = 0; i < 8; i++) {
    if (i > 0) {
      json +=", ";
    }
    json += "{\"bin\":";
    json += "\"" + labels[i] + "\"";
    json += ", \"value\":";
    json += String(bands[i]);
    json += "}"; 
  }
  json += "]";
  webSocket.broadcastTXT(json.c_str(), json.length());
}

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length){
  if(type == WStype_TEXT){

  }
}
