# Práctica 6: Raspberry Pi: Puertos USB, Real Time Clock y comunicación I2C

## Integrantes

* Guzmán Sánchez José, Emmanuel
* Mejia Ortiz, Aarón Enrique
* Sáenz Barragán, Ricardo

## Objetivo
El alumno conocerá la configuración, la programación y de la interfaz I2C para la comunicación de dispositivos.
El alumno conocerá como leer y escribir datos en un Reloj de tiempo real.

## Descripción

En la siguiente práctica se vera el uso de los puertos para la comunicación I2C implementando un Reloj de tiempo real, una vez asignado el tiempo actual en el reloj se leerá el tiempo guardado cada segundo y se escribirá un archivo en una memoria USB con los tiempos leidos.

El código en **actividad_1_set_clock.py** asigna el tiempo para el Reloj, mientras que el código **actividad_1.py** lee el valor actual del Reloj y lo escribe en un documento .txt en alguna memoria USB.

**Ejecución del código:**

``` 
$python actividad_1_set_clock.py
$python actividad_1.py

```

**Resultado:**

```
    cat /media/pi/USB/timer12C.txt

    Friday, 29 May 2015 05:50:06
    Friday, 29 May 2015 05:50:07
    Friday, 29 May 2015 05:50:08
    Friday, 29 May 2015 05:50:09
    .
    .
    .

```

## Referencias

https://pimylifeup.com/raspberry-pi-rtc/

https://cdn-learn.adafruit.com/downloads/pdf/adding-a-real-time-clock-to-raspberry-pi.pdf

El código para leer y escribir en el reloj esta basado en una implementación de un código de git:

https://gist.github.com/sorz/6049584


```
Copyright (C) 2013 @XiErCh

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