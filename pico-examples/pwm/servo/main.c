#include "pico/stdlib.h"
#include <stdio.h>
#include "hardware/pwm.h"

/* Valor maximo para el contador */
const uint16_t tope = 20000;
/* Periodo del PWM en milisegundos */
const float t = 20;

/* Prototipo de funcion */
void pwm_set_duty_milis(uint8_t servo_gpio, float milis);

/**
 * @brief Programa principal
 */
int main(void) {
    /* Divisor de clock para el PWM */
    const float clockDiv = 125.0;
    /* GPIO para conectar el servo */
    const uint8_t servo_gpio = 28;
    /* Valores maximos y minimos de ciclo de actividad */
    const float min_duty_milis = 0.5, max_duty_milis = 2.5;
    /* Ciclo de actividad en milisegundos */
    float milis = min_duty_milis;

    /* Inicializo USB */
    stdio_init_all();
    /* Habilito salida de PWM */
    gpio_set_function(servo_gpio, GPIO_FUNC_PWM);
    /* Busco el slice que genera el PWM en este GPIO */
    uint8_t slice_num = pwm_gpio_to_slice_num(servo_gpio);
    /* Configuracion por defecto de PWM */
    pwm_config config = pwm_get_default_config();
    /* Asigno prescaler, clock final de 500Hz (Clock original de 125MHz) */
    pwm_config_set_clkdiv(&config, clockDiv);
    /* Con esta cantidad de pulsos, tengo frecuencia de 50Hz */
    pwm_config_set_wrap(&config, tope);
    /* Habilito PWM */
    pwm_init(slice_num, &config, true);

    while (true) {
        /* Voy subiendo el ciclo de actividad hasta un extremo del servo */
        while(milis < 0.0025) {
            /* Seteo ciclo de actividad */
            pwm_set_duty_milis(servo_gpio, milis);
            /* Incremento en 100 ms */
            milis += 0.1;
            /* Espero un tiempo */
            sleep_ms(50);
        }
        /* Voy bajando el ciclo de actividad hasta el otro extremo del servo */
        while(milis > 0.0005) {
            /* Seteo ciclo de actividad */
            pwm_set_duty_milis(servo_gpio, milis);
            /* Reduzco en 100 ms */
            milis -= 0.1;
            /* Espero un tiempo */
            sleep_ms(50);
        }
    }

    return 0;
}

/**
 * @brief Setea un ciclo de actividad en milisegundos en una
 * salida de PWM
 * 
 * @param servo_gpio GPIO que usa PWM
 * @param milis ciclo de actividad en milisegundos
 */
void pwm_set_duty_milis(uint8_t servo_gpio, float milis) {
    /* Regla de tres para calcular la cantidad de pulsos de clock */
    float ticks = milis * tope / t;
    /* Seteo el ciclo de actividad */
    pwm_set_gpio_level(servo_gpio, ticks);
}