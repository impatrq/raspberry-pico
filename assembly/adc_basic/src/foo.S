# Defino constante de ADC a T = 20
.equ ADC_TEMP_20, 891

# Funcion global
.global asm_temperature_compare

asm_temperature_compare:
    # El resultado del ADC quedo en r0

    # Cargo r1 con el valor de ADC de T = 20
    ldr r1, =ADC_TEMP_20
    # Comparo r0 con r1
    cmp r0, r1
    # Si r0 > r1 -> Temperatura menor a 20 (apago LED)
    bhi asm_led_off
    # Sino, prendo LED
    b asm_led_on
    # Vuelvo
    bx lr

