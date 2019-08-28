        .text
        .global _start

_start:

        mov     r7,#4
        mov     r0,#1

        @ Registors a comparar 1 y 2
        mov     r1, #8 @ Primer registro
        mov     r2, #8 @ Segundo registro
        cmp     r1, r2 @ Comparacion
        beq     igual
        blt     menor
        bgt     mayor

igual:
        ldr     r1, =m_igual
        mov     r2,#40
        b       print

menor:
        ldr     r1, =m_menor
        mov     r2,#42
        b       print
mayor:
        ldr     r1, =m_mayor
        mov     r2, #42
print:
        svc     #0
        mov     r7,#1
        mov     r0,#0
        svc     #0

     .data

m_igual:
        .ascii "Los registros tienen el mismo valor.\n"
m_menor:
        .ascii "El registro R1 es menor al registro R2\n"
m_mayor:
        .ascii "El registro R1 es mayor al registro R2\n"
