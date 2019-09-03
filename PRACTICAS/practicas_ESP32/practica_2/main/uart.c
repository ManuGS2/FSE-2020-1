
#include "string.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_log.h"
#include "driver/uart.h"
#include "soc/uart_struct.h"
#include "driver/gpio.h"

static const int RX_BUF_SIZE = 1024;

//#define TXD_PIN 1
//#define RXD_PIN 3
#define LED 2
#define BUTTON 27

void init() {
  // LED
  gpio_pad_select_gpio(LED);
  gpio_set_direction(LED, GPIO_MODE_OUTPUT);

  const uart_config_t uart_config = {
    .baud_rate = 115200,
    .data_bits = UART_DATA_8_BITS,
    .parity = UART_PARITY_DISABLE,
    .stop_bits = UART_STOP_BITS_1,
    .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
  };
  uart_param_config(UART_NUM_0, &uart_config);
  uart_driver_install(UART_NUM_0, RX_BUF_SIZE * 2, 0, 0, NULL, 0);
}

int sendData(const char *data) {
  const int len = strlen(data);
  const int txBytes = uart_write_bytes(UART_NUM_0, data, len);
  return txBytes;
}

static void tx_task() {
  static const char *TX_TASK_TAG = "TX_TASK";
  esp_log_level_set(TX_TASK_TAG, ESP_LOG_INFO);

  while (1) {
    if(gpio_get_level(BUTTON)){
        sendData("Me lastimas!!!!!\n");
    }
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

static void rx_task() {
  static const char *RX_TASK_TAG = "RX_TASK";
  esp_log_level_set(RX_TASK_TAG, ESP_LOG_INFO);

  uint8_t *data = (uint8_t *)malloc(RX_BUF_SIZE + 1);
  while (1) {
    const int rxBytes = uart_read_bytes(UART_NUM_0, data, RX_BUF_SIZE, 100 / portTICK_RATE_MS);
    if (rxBytes > 0) {
      ESP_LOG_BUFFER_HEXDUMP(RX_TASK_TAG, data, rxBytes, ESP_LOG_INFO);
      if(!strcmp((char*)data, "a")){
        gpio_set_level(LED, 1);
      }
      if(!strcmp((char*)data, "s")){
        gpio_set_level(LED, 0);
      }
      data[rxBytes] = 0;
    }
  }
  free(data);
}

void app_main() {
  init();
  xTaskCreate(rx_task, "uart_rx_task", 1024 * 2, NULL, configMAX_PRIORITIES, NULL);
  xTaskCreate(tx_task, "uart_tx_task", 1024 * 2, NULL, configMAX_PRIORITIES - 1, NULL);
}
