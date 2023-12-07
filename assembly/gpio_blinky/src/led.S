# Direccion base del banco de IO
.equ IO_BANK_BASE, 0x40014000
# Offset para el registro de control de GPIO
.equ GPIO_25_CTRL_OFF, 0xcc
# Funcion de SIO para el GPIO
.equ SIO_FUNC, 0x5
# Direccion base para el SIO
.equ SIO_BASE, 0xd0000000
# Offset para el Output Enable Set
.equ GPIO_OE_SET_OFF, 0x24
# Offset para el Output XOR
.equ GPIO_OUT_XOR_OFF, 0x1c
# Direccion base para registro de reset
.equ RESET_BASE, 0x4000c000
# Offset para acceder al registro de clear
.equ ATOMIC_CLR_OFF, 0x3000
# Numero de bit del IO BANK en el registro de reset
.equ IO_BANK_RST_BIT, 5
# Offset para el registro de RESET_DONE
.equ RESET_DONE_OFF, 0x8
# Numeor de bit del GPIO del LED
.equ LED_GPIO_BIT, 25

# Definiciones de funciones globales
.global asm_led_init
.global asm_led_blink

asm_led_init:
    # Guardo el valor del RESET_BASE en r0
    ldr r0, =RESET_BASE
    # Guardo el offset para el registro de clear
    ldr r1, =ATOMIC_CLR_OFF
    # Escribo un 1 en r2
    mov r2, #1
    # Lo desplazo hasta el bit de IO_BANK
    lsl r2, #IO_BANK_RST_BIT
    # Guardo el valor de r2 en la direccion que suman r0 y r1 (RESET_CLR)
    str r2, [r0, r1]

rst_wait:
    # Guardo el offset en r1
    ldr r1, =RESET_DONE_OFF
    # Apunto al registro RESET_DONE sumando el offset
    add r0, r1
    # Comparo r0 con cero
    cmp r0, #0
    # Cuando termine el reset, va a dar 1
    beq rst_wait

    # Apunto al registro base del IO_BANK
    ldr r0, =IO_BANK_BASE
    # Guardo el offset al registro de control del GPIO25
    ldr r1, =GPIO_25_CTRL_OFF
    # Guardo el valor para que GPIO funcione como SIO
    mov r2, #SIO_FUNC
    # Guardo en el registro de control del GPIO25 el valor de r2
    str r2, [r0, r1]

    # Apunto al SIO_BASE
    ldr r0, =SIO_BASE
    # Cargo el offset del OE_SET
    ldr r1, =GPIO_OE_SET_OFF
    # Guardo un 1
    mov r2, #1
    # Lo muevo al bit que quiero usar
    lsl r2, #LED_GPIO_BIT
    # Activo la salida
    str r2, [r0, r1]

    # Cargo el offset a XOR
    ldr r1, =GPIO_OUT_XOR_OFF
    # Vuelvo a la funcion original
    bx lr

asm_led_blink:
    # Conmuto la salida
    str r2, [r0, r1]
    # Vuelvo al bucle
    bx lr