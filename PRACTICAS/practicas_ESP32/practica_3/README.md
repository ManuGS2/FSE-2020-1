# Práctica 3 y Examen 1: Sensor de Temperatura con ADC y Puerto UART

## Integrantes

* Guzmán Sánchez José, Emmanuel
* Mejia Ortiz, Aarón Enrique
* Sáenz Barragán, Ricardo

## Objetivo
Construir implementación para toma de lecturas de un sensor de temperatura LM335 con el ADC del ESP32 y su envio
a la PC a través de una Raspberri PI con el uso del puerto UART y el protocolo RS232.

## Descripción
Esta práctica ejemplifica la conexión entre dispositivos por medio del módulo UART a través de una conexión serial 
usando el protocolo RS232. Se obtienen los datos de un sensor de temperatura LM335 y se envía a un ADC del ESP32.
El ESP32 lee los datos del ADC y los procesa para obtener los valores de temperatura en Celsius y Kelvin. Una vez obtenidos, se envían por medio del módulo UART 2 del ESP32 al módulo UART de la Raspberry, ésta última lee los datos enviados y los retransmite por UART a la PC para que ésta finalmente despliegue los datos sensados en pantalla.

## Video

https://drive.google.com/open?id=12c4odELBeDxysvXwJXvrqWZMYg1VjGpH