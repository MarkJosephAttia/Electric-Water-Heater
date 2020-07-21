/**
 * @file  Led.c
 * @brief This file is to be used as an implementation for the Led Handler.
 *
 * @author Mark Attia
 * @date January 22, 2020
 *
 */
#include "Std_Types.h"
#include "Gpio.h"
#include "Led.h"

extern const led_t Led_leds[LED_NUMBER_OF_LEDS];

/**
 * Function:  Led_Init 
 * --------------------
 *  @brief Initializes GPIOs for the LEDs
 * 
 *  
 *  @returns: A status
 *                 E_OK : if the function is executed correctly
 *                 E_NOT_OK : if the function is not executed correctly
 */
Std_ReturnType Led_Init(void)
{
    uint8_t i;
    gpio_t gpio;
    /* Initialize GPIO Pins */
	gpio.mode = GPIO_MODE_OUTPUT_PP;
    for(i=0; i<LED_NUMBER_OF_LEDS; i++)
    {
        gpio.pins = Led_leds[i].pin;
        gpio.port = Led_leds[i].port;
        Gpio_InitPins(&gpio);
    }
    return E_OK;
}

/**
 * Function:  Led_SetLedOn 
 * --------------------
 *  @brief Sets the Led on
 * 
 *  @param ledName: The name of the LED
 *  
 *  @returns: A status
 *                 E_OK : if the function is executed correctly
 *                 E_NOT_OK : if the function is not executed correctly
 */
extern Std_ReturnType Led_SetLedOn(Led_Name_t ledName)
{
    Gpio_WritePin(Led_leds[ledName].port, Led_leds[ledName].pin, Led_leds[ledName].activeState);
    return E_OK;
}

/**
 * Function:  Led_SetLedOff 
 * --------------------
 *  @brief Sets the Led off
 * 
 *  @param ledName The name of the LED
 *  
 *  @returns: A status
 *                 E_OK : if the function is executed correctly
 *                 E_NOT_OK : if the function is not executed correctly
 */
Std_ReturnType Led_SetLedOff(Led_Name_t ledName)
{
    Gpio_WritePin(Led_leds[ledName].port, Led_leds[ledName].pin, !Led_leds[ledName].activeState);
    return E_OK;
}

/**
 * Function:  Led_SetLedStatus 
 * --------------------
 *  @brief Sets the Led off
 * 
 *  @param ledName: The name of the LED
 *                  
 *  @param pinStatus: The status of the pin (GPIO_PIN_SET/GPIO_PIN_RESET)
 *                 @arg LED_ON : Sets the pin value to 1
 *                 @arg LED_OFF : Resets the pin value to 0
 *  
 *  @returns: A status
 *                 E_OK : if the function is executed correctly
 *                 E_NOT_OK : if the function is not executed correctly
 */
Std_ReturnType Led_SetLedStatus(Led_Name_t ledName, Led_State_t status)
{
    Gpio_WritePin(Led_leds[ledName].port, Led_leds[ledName].pin, status^Led_leds[ledName].activeState);
    return E_OK;
}