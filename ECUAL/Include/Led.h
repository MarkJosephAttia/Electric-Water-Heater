/**
 * @file  Led.h 
 * @brief This file is to be used as an interface for the user of the Led Handler.
 *
 * @author Mark Attia
 * @date January 22, 2020
 *
 */
#ifndef LED_H
#define LED_H
#include "Led_Cfg.h"


typedef struct
{
    Gpio_Pins_t pin;
    Gpio_Port_t port;
    Gpio_PinStatus_t activeState;
} led_t;

typedef uint8_t Led_Name_t;
typedef uint8_t Led_State_t;

/* Led States */
#define LED_ON              0
#define LED_OFF             1


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
extern Std_ReturnType Led_Init(void);

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
extern Std_ReturnType Led_SetLedOn(Led_Name_t ledName);

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
extern Std_ReturnType Led_SetLedOff(Led_Name_t ledName);

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
extern Std_ReturnType Led_SetLedStatus(Led_Name_t ledName, Led_State_t status);


#endif