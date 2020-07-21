/**
 * @file  Element.h 
 * @brief This file is to be used as an interface for the user of the Element Handler.
 *
 * @author Mark Attia
 * @date January 22, 2020
 *
 */
#ifndef ELEMENT_H
#define ELEMENT_H
#include "Element_Cfg.h"


typedef struct
{
    Gpio_Pins_t pin;
    Gpio_Port_t port;
    Gpio_PinStatus_t activeState;
} element_t;

typedef uint8_t Element_Name_t;
typedef uint8_t Element_State_t;

/* Element States */
#define ELEMENT_ON              0
#define ELEMENT_OFF             1


/**
 * Function:  Element_Init 
 * --------------------
 *  @brief Initializes GPIOs for the ELEMENTs
 * 
 *  
 *  @returns: A status
 *                 E_OK : if the function is executed correctly
 *                 E_NOT_OK : if the function is not executed correctly
 */
extern Std_ReturnType Element_Init(void);

/**
 * Function:  Element_SetElementOn 
 * --------------------
 *  @brief Sets the Element on
 * 
 *  @param elementName: The name of the ELEMENT
 *  
 *  @returns: A status
 *                 E_OK : if the function is executed correctly
 *                 E_NOT_OK : if the function is not executed correctly
 */
extern Std_ReturnType Element_SetElementOn(Element_Name_t elementName);

/**
 * Function:  Element_SetElementOff 
 * --------------------
 *  @brief Sets the Element off
 * 
 *  @param elementName The name of the ELEMENT
 *  
 *  @returns: A status
 *                 E_OK : if the function is executed correctly
 *                 E_NOT_OK : if the function is not executed correctly
 */
extern Std_ReturnType Element_SetElementOff(Element_Name_t elementName);

/**
 * Function:  Element_SetElementStatus 
 * --------------------
 *  @brief Sets the Element off
 * 
 *  @param elementName: The name of the ELEMENT
 *                  
 *  @param pinStatus: The status of the pin (GPIO_PIN_SET/GPIO_PIN_RESET)
 *                 @arg ELEMENT_ON : Sets the pin value to 1
 *                 @arg ELEMENT_OFF : Resets the pin value to 0
 *  
 *  @returns: A status
 *                 E_OK : if the function is executed correctly
 *                 E_NOT_OK : if the function is not executed correctly
 */
extern Std_ReturnType Element_SetElementStatus(Element_Name_t elementName, Element_State_t status);


#endif