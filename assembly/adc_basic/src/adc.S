# Direccion base del ADC
.equ ADC_BASE, 0x4004c000
# Offset del registro de control y status
.equ CS_OFF, 0x00
# Offset del registro de resultado
.equ RESULT_OFF, 0x04
# Bit de enable
.equ EN_BIT, 0x00
# Bit para habilitar el sensor de temperatura
.equ TS_EN_BIT, 0x01
# Bit de inicio de conversion unica
.equ START_ONCE_BIT, 0x02
# Bit de conversion lista
.equ READY_BIT, 0x08
# Bit de seleccion de canal
.equ AINSEL_BIT, 0xc
# Direccion base para registro de reset
.equ RESET_BASE, 0x4000c000
# Offset para acceder al registro de clear
.equ ATOMIC_CLR_OFF, 0x3000
# Offset para el registro de RESET_DONE
.equ RESET_DONE_OFF, 0x8

# Definiciones de funciones globales
.global asm_adc_init
.global asm_adc_read

asm_adc_init:
    # Guardo el valor del RESET_BASE en r0
    ldr r0, =RESET_BASE
    # Guardo el offset para el registro de clear
    ldr r1, =ATOMIC_CLR_OFF
    # Escribo un 1 en r2 (bit ADC)
    mov r2, #1
    # Guardo el valor de r2 en la direccion que suman r0 y r1 (RESET_CLR)
    str r2, [r0, r1]

adc_rst_wait:
    # Guardo el offset en r1
    ldr r1, =RESET_DONE_OFF
    # Apunto al registro RESET_DONE sumando el offset
    add r0, r1
    # Comparo r0 con cero
    cmp r0, #0
    # Cuando termine el reset, va a dar 1
    beq adc_rst_wait
    # Apunto a la base del ADC (es el registro CS)
    ldr r0, =ADC_BASE
    # Pongo un 5 (entrada analogica) en el registro
    mov r1, #5
    # Lo muevo al bit de AINSEL
    lsl r1, #AINSEL_BIT
    # Agrego 0b11 para habilitar sensor de temperatura y ADC
    add r1, #3
    # Escribo el registro CS con los valores de r2
    str r1, [r0]
    # Vuelvo
    bx lr


asm_adc_read:
    # Apunto a la base del ADC (regitro CS)
    ldr r0, =ADC_BASE
    # Copio lo que apunta r0
    ldr r1, [r0]
    # Cargo el bit de START_ONCE
    mov r2, #4
    orr r1, r2
    # Inicio conversion
    str r1, [r0]
    # Cargo el registro con la mascara del bit ready
    mov r1, #1
    lsl r1, #READY_BIT

adc_wait:
    # Copio el valor de r0
    ldr r2, [r0]
    # Evaluo el bit de READY (bit 8)
    and r2, r1
    # Si es cero, espero
    beq adc_wait
    # Cargo el offset del RESULT register
    ldr r1, =RESULT_OFF
    # Guardo el resultado en r0
    ldr r0, [r0, r1]
    # Vuelvo
    bx lr