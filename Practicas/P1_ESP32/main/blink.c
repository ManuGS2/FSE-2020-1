/* Blink Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"

/* Can run 'make menuconfig' to choose the GPIO to blink,
   or you can edit the following line and set a number here.
*/
#define INPUT 27
#define LED1 32
#define LED2 33
#define LED3 25
#define LED4 26

short contador[4], cont=0;

int not(int val){
    if (val == 0)
        return 1;
    else   
        return 0;
}

void suma(){

    cont += 1;
    if (cont > 10){
        cont = 0;
        contador[0] = 0;
        contador[1] = 0;
        contador[2] = 0;
        contador[3] = 0;
    }
    if (cont % 2 == 1)
        contador[0] = 1;
    else
        contador[0] = 0;
    
    if (cont==2||cont==3||cont==6||cont==7||cont==10)
        contador[1] = 1;
    else
        contador[1] = 0;
    
    if (cont >= 8)
        contador[3] = 1;
    else
        contador[3] = 0;

    if (cont > 3 && cont < 8)
        contador[2] = 1;
    else
        contador[2] = 0;
        
    /*
    if (contador[0])
        contador[0] = 0;
    else
        contador[0] = 1;

    if (not(contador[1])*contador[0]+not(contador[3])*contador[1]*not(contador[0]))
        contador[1] = 1;
    else
        contador[1] = 0;

    if (cont >= 8)
        contador[3] = 1;
    else
        contador[3] = 0;

    if (cont > 3 && cont < 8)
        contador[2] = 1;
    else
        contador[2] = 0;
    
    if 0*/
}

void blink_task(void *pvParameter)
{
    /* Configure the IOMUX register for pad INPUT (some pads are
       muxed to GPIO on reset already, but some default to other
       functions and need to be switched to GPIO. Consult the
       Technical Reference for a list of pads and their default
       functions.)
    */
    gpio_pad_select_gpio(INPUT);
    gpio_pad_select_gpio(LED1);
    gpio_pad_select_gpio(LED2);
    gpio_pad_select_gpio(LED3);
    gpio_pad_select_gpio(LED4);

    /* Set the GPIO as a push/pull output */
    gpio_set_direction(INPUT, GPIO_MODE_INPUT);
    gpio_set_direction(LED1, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED2, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED3, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED4, GPIO_MODE_OUTPUT);

    while(1) {
        /* Blink off (output low) */
        if (!gpio_get_level(INPUT)){
            suma();
        }
        gpio_set_level(LED1, contador[0]);
        gpio_set_level(LED2, contador[1]);
        gpio_set_level(LED3, contador[2]);
        gpio_set_level(LED4, contador[3]);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void app_main()
{
    xTaskCreate(&blink_task, "blink_task", configMINIMAL_STACK_SIZE, NULL, 5, NULL);
}
