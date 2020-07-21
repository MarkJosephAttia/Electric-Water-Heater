/**
 * @file  Timer1.h 
 * @brief This file is to be used as an implementation for the user of Timer 1 driver.
 *
 * @author Mark Attia
 * @date January 22, 2020
 *
 */

#ifndef TIMER1_H
#define TIMER1_H
/* Timer 1 Prescalers */
#define TMR1_DIV_1				0x00
#define TMR1_DIV_2				0x10
#define TMR1_DIV_4				0x20
#define TMR1_DIV_8  			0x30

typedef uint8_t Timer1_Prescaler_t;
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
extern Std_ReturnType Timer1_InterruptEnable(void);

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
extern Std_ReturnType Timer1_InterruptDisable(void);

/**
 * Function:  Timer1_Start 
 * --------------------
 *  @brief Enables the Timer1 timer
 *  
 *  @param prescaler: the division value for system clock
 *					@arg TMR0_DIV_1
 *					@arg TMR0_DIV_8
 *     				@arg TMR0_DIV_64
 *     				@arg TMR0_DIV_256
 *					@arg TMR0_DIV_1024
 *  @returns: A status
 *                 E_OK : if the function is executed correctly
 *                 E_NOT_OK : if the function is not executed correctly
 */
extern Std_ReturnType Timer1_Start(Timer1_Prescaler_t prescaler);

/**
 * Function:  Timer1_SetTimeUS 
 * --------------------
 *  @brief Sets The reload time for timer 0
 *
 *  @param timerClock: The Timer clock frequency
 *  @param timeUS: The time in Micro seconds
 *  
 *  @returns: A status
 *                 E_OK : if the function is executed correctly
 *                 E_NOT_OK : if the function is not executed correctly
 */
extern Std_ReturnType Timer1_SetTimeUS(f64 timerClock, uint32_t timeUS);

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
extern Std_ReturnType Timer1_Stop(void);

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
extern Std_ReturnType Timer1_GetValue(uint16_t* val);

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
extern Std_ReturnType Timer1_SetCallBack(interruptCb_t func);

/**
 * Function:  Timer1_ClearValue 
 * --------------------
 *  @brief Clears the value of the counter
 *  
 *  @returns: A status
 *                 E_OK : if the function is executed correctly
 *                 E_NOT_OK : if the function is not executed correctly
 */
extern Std_ReturnType Timer1_ClearValue(void);


#endif