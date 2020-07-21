/**
 * @file  Timer1.h 
 * @brief This file is to be used as an interface for the user of Timer 1 driver.
 *
 * @author Mark Attia
 * @date January 22, 2020
 *
 */
#include "Std_Types.h"
#include "Int.h"
#include "Timer1.h"
/* Timer 1 Registers */
#define TMR1                      *(uint16_t*)0x0E
#define CCPR1                     *(uint16_t*)0x15
#define TMR1_CON                  *(uint8_t*)0x10

#define INT_CON                   *(uint8_t*)0x0B
#define CCP1_CON                  *(uint8_t*)0x17
#define PIE                       *(uint8_t*)0x8C
#define PIF                       *(uint8_t*)0x0C
/* Timer 1 Masks */
#define CCP1_INT_EN                          0x04
#define CCP1_CON_CLR                         0xF0
#define CCP1_CON_SP                          0x0B
#define CCP1_INT_FLAG                        0x04
#define CCP1_INT_FLAG_CLR                    0xFB
#define CCP1_INT_DIS                         0xFB
#define INT_EN                               0xC0
#define TMR1_CLR                             0xCF
#define TMR1_EN                              0x01
#define TMR1_DIS                             0xFE
#define TMR1_CS_INTERNAL                     0xFD  
#define TMR1_PRESCALER_CLR		             0xF8

/**
 * Function:  Timer1_InterruptEnable 
 * --------------------
 *  @brief Enables the interrupt for the Timer1
 *
 *  
 *  @returns: A status
 *                 E_OK : if the function is executed correctly
 *                 E_NOT_OK : if the function is not executed correctly
 */
Std_ReturnType Timer1_InterruptEnable(void)
{
    /* Enable Global Interrupt */
    INT_CON |= INT_EN;
    /* Enable Timer 1 Interrupt */
    PIE |= CCP1_INT_EN;
    CCP1_CON |= CCP1_CON_CLR;
    CCP1_CON |= CCP1_CON_SP;
    return E_OK;
}

/**
 * Function:  Timer1_InterruptDisable 
 * --------------------
 *  @brief Disables the interrupt for the Timer1
 *
 *  
 *  @returns: A status
 *                 E_OK : if the function is executed correctly
 *                 E_NOT_OK : if the function is not executed correctly
 */
Std_ReturnType Timer1_InterruptDisable(void)
{
    /* Disable Timer 1 Interrupt */
    PIE &= CCP1_INT_DIS;
    return E_OK;
}

/**
 * Function:  Timer1_Start 
 * --------------------
 *  @brief Enables the Timer1 timer
 *  
 *  @param prescaler: the division value for system clock
 *					@arg TMR0_DIV_1
 *                  @arg TMR0_DIV_2
 *                  @arg TMR0_DIV_4
 *                  @arg TMR0_DIV_8
 *  @returns: A status
 *                 E_OK : if the function is executed correctly
 *                 E_NOT_OK : if the function is not executed correctly
 */
Std_ReturnType Timer1_Start(Timer1_Prescaler_t prescaler)
{
    /* Disable Timer 1 */
    TMR1_CON &= TMR1_DIS;
    /* Clears The Prescaler */
	TMR1_CON &= TMR1_PRESCALER_CLR & TMR1_CS_INTERNAL;
    /* Sets The Prescaler */
    TMR1_CON |= prescaler;
    /* Clears The Timer Value */
    TMR1 = 0;
    /* Enables The Timer */
    TMR1_CON |= TMR1_EN;
    return E_OK;
}

/**
 * Function:  Timer1_Stop 
 * --------------------
 *  @brief Disables the Timer1 timer
 *
 *  
 *  @returns: A status
 *                 E_OK : if the function is executed correctly
 *                 E_NOT_OK : if the function is not executed correctly
 */
Std_ReturnType Timer1_Stop(void)
{
    /* Stops The Timer */
    TMR1_CON &= TMR1_DIS;
    return E_OK;
}

/**
 * Function:  Timer1_GetValue 
 * --------------------
 *  @brief Reads the current value inside the Timer1 timer
 *
 *  @param val: a pointer to return data in
 *  
 *  @returns: A status
 *                 E_OK : if the function is executed correctly
 *                 E_NOT_OK : if the function is not executed correctly
 */
Std_ReturnType Timer1_GetValue(uint16_t* val)
{
    /* Saves The Timer Value */
    *val = TMR1;
    return E_OK;
}

/**
 * Function:  Timer1_SetCallBack 
 * --------------------
 *  @brief Sets the callback function for the Timer1
 *
 *  @param func: the callback function
 *  
 *  @returns: A status
 *                 E_OK : if the function is executed correctly
 *                 E_NOT_OK : if the function is not executed correctly
 */
Std_ReturnType Timer1_SetCallBack(interruptCb_t func)
{
    Timer1_func = func;
    return E_OK;
}

/**
 * Function:  Timer1_ClearValue 
 * --------------------
 *  @brief Clears the value of the counter
 *  
 *  @returns: A status
 *                 E_OK : if the function is executed correctly
 *                 E_NOT_OK : if the function is not executed correctly
 */
Std_ReturnType Timer1_ClearValue(void)
{
    TMR1 = 0;
    return E_OK;
}

/**
 * Function:  Timer1_SetTimeUS 
 * --------------------
 *  @brief Sets The reload time for timer 1
 *
 *  @param timerClock: The Timer clock frequency
 *  @param timeUS: The time in Micro seconds
 *  
 *  @returns: A status
 *                 E_OK : if the function is executed correctly
 *                 E_NOT_OK : if the function is not executed correctly
 */
Std_ReturnType Timer1_SetTimeUS(f64 timerClock, uint32_t timeUS)
{
    f64 val;
    /* Get The Value In Micro Seconds */
    val = (f64)timerClock*(f64)timeUS/1000000.0;
    /* Instert The Value Into The Register */
    CCPR1 = (uint16_t)val;
	return E_OK;
}
