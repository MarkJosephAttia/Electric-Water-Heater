/**
 * @file  SSeg_Cfg.c
 * @author Mark Attia (markjosephattia@gmail.com)
 * @brief These are the configurations for the Seven Segment Display Driver
 * @version 0.1
 * @date 2020-07-05
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include "Std_Types.h"
#include "Gpio.h"
#include "SSeg_Cfg.h"
#include "SSeg.h"

const sseg_t SSeg_sseg = {
    .dPin = { GPIO_PIN_0, GPIO_PIN_1, GPIO_PIN_2, GPIO_PIN_3, GPIO_PIN_4, GPIO_PIN_5, GPIO_PIN_6},
    .dPort = { GPIO_PORTD, GPIO_PORTD, GPIO_PORTD, GPIO_PORTD, GPIO_PORTD, GPIO_PORTD, GPIO_PORTD},
    .enPin = { GPIO_PIN_4, GPIO_PIN_5},
    .enPort = { GPIO_PORTA, GPIO_PORTA},
    .common = {SSEG_COMMON_ANODE, SSEG_COMMON_ANODE}
};
