# Práctica 5: Raspberry Pi: Raspberry Pi y Puertos USB

## Integrantes

* Guzmán Sánchez José, Emmanuel
* Mejia Ortiz, Aarón Enrique
* Sáenz Barragán, Ricardo

## Objetivo
El alumno conocerá la configuración, la programación y el uso de los módulos USB en la Raspberry Pi.
El alumno conocerá como leer y escribir datos a una memoría externa conectada por puerto USB.

## Descripción

En la siguiente práctica se vera el uso de los puertos USB's para la escritura y lectura de datos en la Raspberry pi.
Consiste en un programa que al recibir dos argumentos:
- Nombre del archivo a creara 
- Número de veces que se escribirá un dato en el archivo 

**Ejecución del código:**

``` 
$python actividad_1.py <Nombre del archivo> <Número entero> 

```

**Resultado:**

```
    cat /media/pi/USB/<Nombre del archivo>.csv

    0,HolaUSB,dato0
    1,HolaUSB,dato1
    .
    .
    .
    <Número entero - 1>,HolaUSB,dato<Número entero - 1>

```


