/**
 * @file  Element.c
 * @brief This file is to be used as an implementation for the Element Handler.
 *
 * @author Mark Attia
 * @date January 22, 2020
 *
 */
#include "Std_Types.h"
#include "Gpio.h"
#include "Element.h"

extern const element_t Element_elements[ELEMENT_NUMBER_OF_ELEMENTS];

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
Std_ReturnType Element_Init(void)
{
    uint8_t i;
    gpio_t gpio;
    /* Initialize GPIO Pins */
	gpio.mode = GPIO_MODE_OUTPUT_PP;
    for(i=0; i<ELEMENT_NUMBER_OF_ELEMENTS; i++)
    {
        gpio.pins = Element_elements[i].pin;
        gpio.port = Element_elements[i].port;
        Gpio_InitPins(&gpio);
    }
    return E_OK;
}

/**
 * Function:  Element_SetElementOn 
 * --------------------
 *  @brief Sets the Element on
 * 
 *  @param elementName: The name of the Element
 *  
 *  @returns: A status
 *                 E_OK : if the function is executed correctly
 *                 E_NOT_OK : if the function is not executed correctly
 */
extern Std_ReturnType Element_SetElementOn(Element_Name_t elementName)
{
    Gpio_WritePin(Element_elements[elementName].port, Element_elements[elementName].pin, Element_elements[elementName].activeState);
    return E_OK;
}

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
Std_ReturnType Element_SetElementOff(Element_Name_t elementName)
{
    Gpio_WritePin(Element_elements[elementName].port, Element_elements[elementName].pin, !Element_elements[elementName].activeState);
    return E_OK;
}

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
Std_ReturnType Element_SetElementStatus(Element_Name_t elementName, Element_State_t status)
{
    Gpio_WritePin(Element_elements[elementName].port, Element_elements[elementName].pin, status^Element_elements[elementName].activeState);
    return E_OK;
}