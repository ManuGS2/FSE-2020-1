#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/adc.h"
#include "esp_adc_cal.h"
#include "driver/uart.h"
#include "esp_err.h"

// Vref and # of Samples
#define DEFAULT_VREF 3300
#define NO_OF_SAMPLES 64

// ADC constants
static esp_adc_cal_characteristics_t *adc_chars;
static const adc_channel_t channel = ADC_CHANNEL_0;
static const adc_atten_t atten = ADC_ATTEN_DB_11;
static const adc_unit_t unit = ADC_UNIT_1;


void initUART() {
  uart_config_t uart_config = {
    .baud_rate = 115200,
    .data_bits = UART_DATA_8_BITS,
    .parity    = UART_PARITY_DISABLE,
    .stop_bits = UART_STOP_BITS_1,
    .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
  };
  // Config UART_2
  uart_param_config(UART_NUM_2, &uart_config);
  uart_set_pin(UART_NUM_2, 17, 16, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
  uart_driver_install(UART_NUM_2, 1024, 0, 0, NULL, 0);
  
  printf("\nUART_2 ready...");
  return;
}

void initADC() {
  // Config ADC
  adc1_config_width(ADC_WIDTH_BIT_12);
  adc1_config_channel_atten(channel, atten);
  adc_chars = calloc(1, sizeof(esp_adc_cal_characteristics_t));
  esp_adc_cal_characterize(unit, atten, ADC_WIDTH_BIT_12, DEFAULT_VREF, adc_chars);
  
  printf("\nADC ready...");
  return;
}

void initPheripherials() {
  initUART();
  initADC();
}

void sendData(double voltage, double kelvin, double celcius) {
  char buf[36];
  // Stores vars and chars into buffer
  snprintf(buf, 36, "%f,%f,%f", voltage, kelvin, celcius);
  uart_write_bytes(UART_NUM_2, buf, 36);
  printf("\n%s", buf);
  return;
}

void app_main() {
  uint32_t adc_reading, voltage;
  double celcius = 0, kelvin = 0;
  int i;

	initPheripherials();
	
  while (1) {
    adc_reading = 0;

    // Multisampling
    for (i = 0; i < NO_OF_SAMPLES; i++) {
      adc_reading += adc1_get_raw((adc1_channel_t)channel);
    }
    // Average samples
    adc_reading /= NO_OF_SAMPLES;

    // Convert adc_reading to voltage in mV
    voltage = esp_adc_cal_raw_to_voltage(adc_reading, adc_chars);

    // Data conversion
    kelvin =  voltage/10;
    celcius = kelvin - 273.15f;

    // Output
    sendData(voltage, kelvin, celcius);

    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}