/**
 * @file  Switch_Cfg.c
 * @brief This file is to be used as an implementation of the configurations the user configured in the Switch_Cfg.h.
 *
 * @author Mark Attia
 * @date January 22, 2020
 *
 */
#include "Std_Types.h"
#include "Gpio.h"
#include "Switch.h"

const switch_t Switch_switches[SWITCH_NUMBER_OF_SWITCHES] = {
    {GPIO_PIN_5, GPIO_PORTB, GPIO_PIN_RESET},
    {GPIO_PIN_4, GPIO_PORTB, GPIO_PIN_RESET},
    {GPIO_PIN_3, GPIO_PORTB, GPIO_PIN_RESET}
};
