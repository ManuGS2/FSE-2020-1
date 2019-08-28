# Práctica 2: Raspberry Pi: Lenguaje Ensamblador

## Integrantes

* Guzmán Sánchez José, Emmanuel
* Mejia Ortiz, Aarón Enrique
* Sáenz Barragán, Ricardo

## Objetivo
El alumno conocerá la programación en lenguaje ensamblador del procesador asociado a la tarjeta de desarrollo Raspberry Pi.

## Comentarios y Respuestas a las preguntas 

### 2. Lenguaje ensamblador

-	**SWI:**  Interrupción que se utiliza para acceder a rutinas de OS o modulos de terceros.
	Parametro que recive es la rutina o la instrucción. 

### 3. Manejando cadenas

**Código**

> _start:
>	mov	r7,#4 **@ Escribe llamada al sistema**
>	mov	r0,#1 **@ Especificamos salida estándar**
>	ldr	r1,=message **@ Apuntamos a la dirección donde se encuentra la cadena a imprimir**
>	mov 	r2,#21 **@ Damos la longitud de la cadena a imprimir**
>	svc	#0 **@ Abrimos salida estándar**
>	mov	r7,#1 **@ Salimos de la llamada al sistema**
>	mov	r0,#0 **@ Regresa 0**
>	svc	#0 **@ Cerramos salida estándar**

En el código se posicionan los registros con los valores que darán las instrucciones necesarias a la raspberry para abrir el canal de salida estándar (la consola), después recorrerá usando un apuntador una cadena de caracteres que serán mostrados en la pantalla y por ultimo cerrara el canal de comunicación de la salida estándar.

### 5. Conteste las siguientes preguntas

Respuestas breves y concisas. Ponga las respuestas en el archivo README usando un editor de texto.

1. Cuál es la diferencia entre las instrucciones swi 0x0, svc #0 y bx lr?
	- "swi 0x0" y "svc,#0" funcionan de la misma forma, para acceder a rutinas de OS o modulos de terceros. Parametro que recive es la rutina o la instrucción.
	- bx lr realiza un return, dependiendo del lsb toma la siguiente instrucción como arm o thumb.

2.  A que se refiere la instrucción .balign 4 en el lenguaje ensamblador para ARM?
	- syntaxis GNU de ".align n" alinea los limites de los registros a n.

3. Cuántas instrucciones en lenguaje ensamblador hay para la arquitectura ARM11 y cuantos modos de direccionamiento hay (nombrelos)?
	- 34 intrucciones y 3 modos de direccioamiento:
		- Indirecto de registro
		- Indirecto de registro con desplazamiento constante
		- Indirecto de registro con desplazamiento por registro