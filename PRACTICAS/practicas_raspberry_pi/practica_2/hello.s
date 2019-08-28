	.text
	.global _start

_start:
	mov	r7,#4 @ Escribe llamada al sistema
	mov	r0,#1 @ Especificamos salida estandar
	ldr	r1,=message @ Apuntamos a la dirección donde se encuentra la cadena a imprimir
	mov 	r2,#21 @ Damos la longitud de la cadena a imprimir
	svc	#0 @ Abrimos salida estandar
	mov	r7,#1 @ Salimos de la llamada al sistema
	mov	r0,#0 @ Regresa 0
	svc	#0 @ Cerramos salida estandar
       .data

message:
       .ascii "FSE2020-1 is cool\n" @ Cadena para mostrar en pantalla
