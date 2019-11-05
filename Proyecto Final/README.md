# Proyecto Final: Analizador de Espectro de Audio

## Integrantes

* Guzmán Sánchez José, Emmanuel
* Mejia Ortiz, Aarón Enrique
* Sáenz Barragán, Ricardo

## Objetivo
El alumno conocerá pondrá en práctica los conocimientos adquiridos durante el curso de Sistemas Embebidos creando una aplicación compleja y aplicando lo visto en clase para su creación.

## Descripción

En el siguiente proyecto se mostrara el uso de la ESP32 como cliente, servidor y API de web, de igual manera se utilizara para la lectura de audio por medio de los pines de entrada. Utilizando la función rápida de fourier para el análisis de entradas de audio y crear la representación visual en tiempo real por medio de un access point que sera controlado por la ESP32.

**Ejecución del código:**

``` 
Compile en un GUI de arduino con las bibliotecas:

- ArduinoFFT
- webSockets by Markus Sattle

e instalando el compilador para la ESP32

```

## Referencias

https://docs.espressif.com/projects/esp-idf/en/latest/api-reference/peripherals/i2s.html

https://docs.espressif.com/projects/esp-idf/en/latest/api-reference/protocols/esp_websocket_client.html

https://lastminuteengineers.com/creating-esp32-web-server-arduino-ide/

https://www.youtube.com/watch?v=RnVeXkrrnPI&feature=youtu.be

https://github.com/G6EJD/ESP32-8266-Audio-Spectrum-Display


```
MIT License

Copyright (c) 2019 Daniel Eichhorn

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```