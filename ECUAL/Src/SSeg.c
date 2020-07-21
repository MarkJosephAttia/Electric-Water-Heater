/**
 * @file SSeg.c
 * @author Mark Attia (markjosephattia@gmail.com)
 * @brief This is the implementation for the Seven Segment Display Driver
 * @version 0.1
 * @date 2020-07-05
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include "Std_Types.h"
#include "Gpio.h"
#include "SSeg.h"
#include "Sched.h"

/* The Numbers From 0 To 9 For The Anode */
const char numsA[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
/* The Numbers From 0 To 9 For The Cathode */
const char numsC[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};

extern const sseg_t SSeg_sseg;
static volatile uint8_t SSeg_data[SSEG_NUMBER_OF_SSEGS];

static volatile SSeg_display_t SSeg_display = SSEG_OFF;
static Std_ReturnType SSeg_SetOn(SSeg_name_t name);
static Std_ReturnType SSeg_SetOff(SSeg_name_t name);
/**
 * @brief The Seven Segment initialization
 * 
 * @return Std_ReturnType A Status
 *                  E_OK : if the function is executed correctly
 *                  E_NOT_OK : if the function is not executed correctly
 */
Std_ReturnType SSeg_Init(void)
{
    uint8_t i;
    gpio_t gpio;
    /* Initialize The GPIO Pins For The Seven Segments */
	gpio.mode = GPIO_MODE_OUTPUT_PP;
    for(i=0; i<SSEG_NUMBER_OF_PINS; i++)
    {
        gpio.pins = SSeg_sseg.dPin[i];
        gpio.port = SSeg_sseg.dPort[i];
        Gpio_InitPins(&gpio);
    }
    for(i=0; i<SSEG_NUMBER_OF_SSEGS; i++)
    {
        gpio.pins = SSeg_sseg.enPin[i];
        gpio.port = SSeg_sseg.enPort[i];
        Gpio_InitPins(&gpio);
        SSeg_SetOff(i);
    }
    return E_OK;
}
/**
 * @brief Sets The Seven Segments Display On And Off
 * 
 * @param display The Display State
 *              @arg SSEG_ON
 *              @arg SSEG_OFF
 * @return Std_ReturnType A Status
 *                  E_OK : if the function is executed correctly
 *                  E_NOT_OK : if the function is not executed correctly
 */
Std_ReturnType SSeg_SetDisplay(SSeg_display_t display)
{
    SSeg_display = display; 
    return E_OK;
}
/**
 * @brief Sets A Seven Segment Display On
 * 
 * @param name The Name Of The Seven Segment
 * @return Std_ReturnType A Status
 *                  E_OK : if the function is executed correctly
 *                  E_NOT_OK : if the function is not executed correctly
 */
static Std_ReturnType SSeg_SetOn(SSeg_name_t name)
{
    if(SSeg_sseg.common[name] == SSEG_COMMON_ANODE)
    {
        Gpio_WritePin(SSeg_sseg.enPort[name] , SSeg_sseg.enPin[name], GPIO_PIN_SET);
    }
    else if(SSeg_sseg.common[name] == SSEG_COMMON_CATHODE)
    {
        Gpio_WritePin(SSeg_sseg.enPort[name] , SSeg_sseg.enPin[name], GPIO_PIN_SET);
    }
    else
    {
        /* Empty Else To Satisfy The Misra Rules */
    }
    
    return E_OK;
}
/**
 * @brief Sets A Seven Segment Display Off
 * 
 * @param name The Name Of The Seven Segment
 * @return Std_ReturnType A Status
 *                  E_OK : if the function is executed correctly
 *                  E_NOT_OK : if the function is not executed correctly
 */
static Std_ReturnType SSeg_SetOff(SSeg_name_t name)
{
    if(SSeg_sseg.common[name] == SSEG_COMMON_ANODE)
    {
        Gpio_WritePin(SSeg_sseg.enPort[name] , SSeg_sseg.enPin[name], GPIO_PIN_RESET);
    }
    else if(SSeg_sseg.common[name] == SSEG_COMMON_CATHODE)
    {
        Gpio_WritePin(SSeg_sseg.enPort[name] , SSeg_sseg.enPin[name], GPIO_PIN_RESET);
    }
    else
    {
        /* Empty Else To Satisfy The Misra Rules */
    }
    
    return E_OK;
}
/**
 * @brief Sets A Digit For A Specific Seven Segment
 * 
 * @param name The Name Of The Seven Segment
 * @param digit The Digit To Set
 * @return Std_ReturnType A Status
 *                  E_OK : if the function is executed correctly
 *                  E_NOT_OK : if the function is not executed correctly
 */
Std_ReturnType SSeg_SetNum(SSeg_name_t name, uint8_t digit)
{
    SSeg_data[name] = digit;
    return E_OK;
}
/**
 * @brief The Seven Segment Runnable
 * 
 */
void SSeg_Runnable(void)
{
    static uint8_t sSegItr;
    uint8_t pinItr;
    /* Sets The Previous Display Off */
    if(sSegItr > 0)
    {
        SSeg_SetOff(sSegItr-1);
    }
    else
    {
        SSeg_SetOff(SSEG_NUMBER_OF_SSEGS-1);
    }
    /* Writes The Digit To The Pins */
    for(pinItr=0; pinItr<SSEG_NUMBER_OF_PINS; pinItr++)
    {
        if(SSeg_sseg.common[sSegItr] == SSEG_COMMON_ANODE)
        {
            Gpio_WritePin(SSeg_sseg.dPort[pinItr] , SSeg_sseg.dPin[pinItr], !((numsA[SSeg_data[sSegItr]]>>pinItr)&1));
        }
        else if(SSeg_sseg.common[sSegItr] == SSEG_COMMON_CATHODE)
        {
            Gpio_WritePin(SSeg_sseg.dPort[pinItr] , SSeg_sseg.dPin[pinItr], !((numsC[SSeg_data[sSegItr]]>>pinItr)&1)); 
        }
        else
        {
            /* Empty Else To Satisfy The Misra Rules */
        }
        
    }
    /* Sets The Display On And Jumps To The Next Seven Segment*/
    if(SSeg_display == SSEG_ON)
    {
        SSeg_SetOn(sSegItr++);
    }
    else
    {
        /* Empty Else To Satisfy The Misra Rules */
    }
    if(sSegItr == SSEG_NUMBER_OF_SSEGS)
    {
        sSegItr=0;
    }
    else
    {
        /* Empty Else To Satisfy The Misra Rules */
    }
}

const task_t SSeg_task = {SSeg_Runnable, 25};