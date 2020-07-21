/**
 * @file  Switch.h 
 * @brief This file is to be used as an interface for the user of the Switch Handler.
 *
 * @author Mark Attia
 * @date January 22, 2020
 *
 */
#ifndef SWITCH_H
#define SWITCH_H
#include "Switch_Cfg.h"

typedef struct
{
    Gpio_Pins_t pin;
    Gpio_Port_t port;
    Gpio_PinStatus_t activeState;
} switch_t;

typedef uint8_t Switch_Name_t;
typedef uint8_t Switch_State_t;

/* Switch States */
#define SWITCH_NOT_PRESSED              1
#define SWITCH_PRESSED                  0

/**
 * Function:  Switch_Init 
 * --------------------
 *  @brief Initializes GPIOs for the Switches
 * 
 *  @returns: A status
 *                 E_OK : if the function is executed correctly
 *                 E_NOT_OK : if the function is not executed correctly
 */
extern Std_ReturnType Switch_Init(void);

/**
 * Function:  Switch_GetSwitchStatus 
 * --------------------
 *  @brief Gets the status of the switch
 * 
 *  @param switchName: The name of the Switch
 *                   
 *  @param state: Save the status of the switch in
 *                 @arg SWITCH_PRESSED : if the switch is pressed
 *                 @arg SWITCH_NOT_PRESSED : if the switch is not pressed
 *  @returns: A status
 *                 E_OK : if the function is executed correctly
 *                 E_NOT_OK : if the function is not executed correctly
 */
extern Std_ReturnType Switch_GetSwitchStatus(Switch_Name_t switchName, Switch_State_t* state);

#endif
