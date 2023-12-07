# Valor para decrementar
.equ DELAY_500_MS, 16624999

# Definicion global de funcion
.global asm_delay

# A 133 MHz de clock necesito 66500000 ciclos de clock

asm_delay:
    # Cargo el valor para restar en el registro (2 ciclos)
    ldr r4, =DELAY_500_MS
loop:
    # Resto uno en el registro (1 ciclo)
    sub r4, #1
    # Comparo con cero (1 ciclo)
    cmp r4, #0
    # Si no es cero todavia, repito (2 ciclos si salta, 1 sino)
    bne loop
    # Vuelvo (2 ciclos)
    bx lr