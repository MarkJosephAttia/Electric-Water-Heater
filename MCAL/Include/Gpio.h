/**
 * @file  Gpio.h 
 * @brief This file is to be used as an interface for the user of GPIO driver.
 *
 * @author Mark Attia
 * @date February 6, 2020
 *
 */

#ifndef GPIO_H
#define GPIO_H

typedef uint8_t Gpio_Pins_t;
typedef uint8_t Gpio_Mode_t;
typedef uint8_t Gpio_Port_t;
typedef uint8_t Gpio_PinStatus_t;
typedef uint8_t Gpio_PullupStatus_t;

typedef struct 
{
    Gpio_Pins_t pins;
    Gpio_Mode_t mode;
    Gpio_Port_t port;
} gpio_t;

/* GPIO Pins State */
#define GPIO_PIN_SET                    0
#define GPIO_PIN_RESET                  !GPIO_PIN_SET

/* GPIO Pins */
#define GPIO_PIN_0                      0x01
#define GPIO_PIN_1                      0x02
#define GPIO_PIN_2                      0x04
#define GPIO_PIN_3                      0x08
#define GPIO_PIN_4                      0x10
#define GPIO_PIN_5                      0x20
#define GPIO_PIN_6                      0x40
#define GPIO_PIN_7                      0x80
#define GPIO_PIN_ALL                    0xFF

/* GPIO Modes */
#define GPIO_MODE_OUTPUT_PP             0
#define GPIO_MODE_INPUT                 1

/* GPIO Ports */
#define GPIO_PORTA                      0x05
#define GPIO_PORTB                      0x06
#define GPIO_PORTC                      0x07
#define GPIO_PORTD                      0x08
#define GPIO_PORTE                      0x09

/* GPIO PortB Pullup Status */
#define GPIO_PORTB_PULLUP_EN            0x7F
#define GPIO_PORTB_PULLUP_DIS           0xFF

/**
 * Function:  Gpio_InitPins 
 * --------------------
 *  @brief Initializes pins mode and speed for a specific port
 *
 *  @param gpio: An object of type gpio_t to set pins for
 *  
 *  
 *  @returns: A status
 *                 E_OK : if the function is executed correctly
 *                 E_NOT_OK : if the function is not executed correctly
 */
extern Std_ReturnType Gpio_InitPins(gpio_t* gpio);

/**
 * Function:  Gpio_WritePin 
 * --------------------
 *  @brief Write a value to a pin(0/1)
 *
 *  @param port: The port you want to configure
 *                 @arg GPIO_PORTX : The pin number you want to configure  
 * 
 *  @param pin: The pin you want to configure
 *                 @arg GPIO_PIN_X : The pin number you want to configure
 *                 //You can OR more than one pin\\
 *
 *  @param pinStatus: The status of the pins (GPIO_PIN_SET/GPIO_PIN_RESET)
 *                 @arg GPIO_PIN_SET : Sets the pin value to 1
 *                 @arg GPIO_PIN_RESET : Resets the pin value to 0
 *  
 *  @returns: A status
 *                 E_OK : if the function is executed correctly
 *                 E_NOT_OK : if the function is not executed correctly
 */
extern Std_ReturnType Gpio_WritePin(Gpio_Port_t port, Gpio_Pins_t pin, Gpio_PinStatus_t pinStatus);

/**
 * Function:  Gpio_ReadPin 
 * --------------------
 *  @brief Reads a value to a pin(0/1)
 *
 *  @param port: The port you want to read from
 *                 @arg GPIO_PORTX : The pin number you want to read from  
 * 
 *  @param pin: The pin you want to read
 *                 @arg GPIO_PIN_X : The pin number you want to read
 *                 //You can OR more than one pin\\
 *
 *  @param state: To return a status in
 *                  @arg GPIO_PIN_SET : The pin is set to 1
 *                  @arg GPIO_PIN_RESET : The pin is set to 0
 *  @returns: A status
 *              E_OK : if the function is executed correctly
 *              E_NOT_OK : if the function is not executed correctly
 */
extern Std_ReturnType Gpio_ReadPin(Gpio_Port_t port, Gpio_Pins_t pin, Gpio_PinStatus_t* state);

/**
 * Function:  Gpio_SetPortBPullup 
 * --------------------
 *  @brief Sets Port B Pullup State
 *
 *  @param pullupState: The port you want to read from
 *                      @arg GPIO_PORTB_PULLUP_EN  
 *                      @arg GPIO_PORTB_PULLUP_DIS  
 * 
 *  @returns: A status
 *              E_OK : if the function is executed correctly
 *              E_NOT_OK : if the function is not executed correctly
 */
extern Std_ReturnType Gpio_SetPortBPullup(Gpio_PullupStatus_t pullupState);

#endif