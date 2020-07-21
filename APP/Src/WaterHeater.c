/**
 * @file WaterHeater.c
 * @author Mark Attia (markjosephattia@gmail.com)
 * @brief This is the implementation for the Electric Water Heater Application
 * @version 0.1
 * @date 2020-07-05
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include "Std_Types.h"
#include "Gpio.h"
#include "Switch.h"
#include "Element.h"
#include "Led.h"
#include "SSeg.h"
#include "Adc.h"
#include "Eeprom.h"
#include "Sched.h"
#include "WaterHeater.h"
#include "WaterHeater_Cfg.h"

/* The Number Of Readings (Configurable) */
#define WATER_HEATER_NUMBER_OF_READINGS       10

/* The Address In The EEPROM (Configurable) */
#define WATER_HEATER_TEMP_DATA_ADDRESS        (Eeprom_Address_t)0x0000
/* The Initial Temprature */
#define WATER_HEATER_INITIAL_TEMP             60

/* The Water Heater Modes */
#define WATER_HEATER_OFF_MODE                   0
#define WATER_HEATER_TEMPRATURE_SETTING_MODE    1
#define WATER_HEATER_RUNNING_MODE               2

/* The Water Heater Temprature Settings */
#define WATER_HEATER_LOWER_LIMIT                35
#define WATER_HEATER_UPPER_LIMIT                75
#define WATER_HEATER_CHANGE_RATE                5

/* The Water Heater Running Elements States */
#define WATER_HEATER_HEATING_ELEMENT_RUNNING                0
#define WATER_HEATER_COOLING_ELEMENT_RUNNING                1
#define WATER_HEATER_NO_ELEMENT_RUNNING                     2

/* The Water Heater Masks */
#define WATER_HEATER_100_MS_MASK                            0x07
#define WATER_HEATER_100_MS_MASK_OK                         0

#define WATER_HEATER_HALF_SEC_MASK                          20
#define WATER_HEATER_5_SEC                                  10

#define WATER_HEATER_COUNTER_RESET_VALUE                    0
#define WATER_HEATER_INDEX_RESET_VALUE                      0
#define WATER_HEATER_TEMPRATURE_SENSOR_FACTOR               2

/* The Temprature Getting Macros */
#define WATER_HEATER_GET_ONES(data)                         (data%10)
#define WATER_HEATER_GET_TENS(data)                         ((data/10)%10)

/* Tasks Periodicity */
#define WATER_HEATER_INIT_TASK_PERIODICITY                  5
#define WATER_HEATER_MAIN_TASK_PERIODICITY                  25

/* Static Functions Declaration */
static void WaterHeater_Init(void);
static void WaterHeater_Runnable(void);
static Std_ReturnType WaterHeater_CheckSwitches(void);
static Std_ReturnType WaterHeater_UpdateCfgModeCounter(void);
static Std_ReturnType WaterHeater_AddReading(void);
static Std_ReturnType WaterHeater_TakeAction(void);
static Std_ReturnType WaterHeater_Blink(void);

/* Water Heater Defined Data Types */
typedef uint8_t temperature_t;
typedef uint8_t heaterMode_t;
typedef uint8_t runningElement_t;
typedef uint8_t secCounter_t;
typedef temperature_t tempratureReadings_t[WATER_HEATER_NUMBER_OF_READINGS];

/* Water Heater Data Elements */
static volatile temperature_t WaterHeater_temperature;
static volatile heaterMode_t WaterHeater_mode;
static volatile tempratureReadings_t WaterHeater_readings;
static volatile secCounter_t WaterHeater_settingModeCounter;
static volatile runningElement_t WaterHeater_runningElement;

/* The init task will run only one time then it will be suspended */
const task_t WaterHeater_InitTask = {WaterHeater_Init, WATER_HEATER_INIT_TASK_PERIODICITY};
/* The Least Period Task Is To Check For The Switches And This May Need 25 Milli Seconds */
const task_t WaterHeater_Task = {WaterHeater_Runnable, WATER_HEATER_MAIN_TASK_PERIODICITY};

/**
 * @brief The Initialization Runnable, Runs One Time And Then Suspends Itself
 * 
 */
static void WaterHeater_Init(void)
{
    /* Hardware Initializations */
    Gpio_SetPortBPullup(GPIO_PORTB_PULLUP_EN);
    Led_Init();
    Led_SetLedOff(WATER_HEATER_HEATING_LED);
    Element_Init();
    Element_SetElementOff(WATER_HEATER_HEATING_ELEMENT);
    Element_SetElementOff(WATER_HEATER_COOLING_ELEMENT);
    Switch_Init();
    SSeg_Init();
    SSeg_SetDisplay(SSEG_OFF);
    Adc_Init();
    Adc_SelectChannel(ADC_CH_2);
    Eeprom_Init();
    /* Writing The Initial Temprature To The EEPROM */
    Eeprom_WriteByte(WATER_HEATER_TEMP_DATA_ADDRESS, WATER_HEATER_INITIAL_TEMP);
    /* Initializing The Data Elements */
    WaterHeater_runningElement = WATER_HEATER_NO_ELEMENT_RUNNING;
    WaterHeater_temperature = WATER_HEATER_INITIAL_TEMP;
    WaterHeater_mode = WATER_HEATER_OFF_MODE;
    /* Suspend The Init Task */
    Sched_SuspendTask();
}

/**
 * @brief The Main Runnable For The Water Heater Application
 * Application Is Designed In One Task For The Modularity Of The Application
 * So It Can Be Easily Integrated With Other Applications In A System
 * 
 */
static void WaterHeater_Runnable(void)
{
    /* The Counter To Toggle Between States (Small Tasks) */
    static uint16_t taskCounter;
    /* The Switches Checking */
    WaterHeater_CheckSwitches();
    /* 100 Milli Tasks */
    if((taskCounter & WATER_HEATER_100_MS_MASK) == WATER_HEATER_100_MS_MASK_OK)
    {
        /* Get Readings */
        WaterHeater_AddReading();
        /* Taking Action According To The Readings */
        WaterHeater_TakeAction();
    }
    else
    {
        /* Empty Else Statement To Satisfy The Misra Rules */
    }
    /* 500 Milly Tasks */
    if(taskCounter == WATER_HEATER_HALF_SEC_MASK)
    {
        /* Toggling Tasks Comes Every 500 Milli So That A Complete Blink Happens In A Second */
        WaterHeater_UpdateCfgModeCounter();
        WaterHeater_Blink();
        taskCounter = WATER_HEATER_COUNTER_RESET_VALUE;
    }
    else
    {
        /* Empty Else Statement To Satisfy The Misra Rules */
    }
    taskCounter++;
}


/**
 * @brief Checking The State Of The Switches
 * 
 *  @returns: A status
 *                 E_OK : if the function is executed correctly
 *                 E_NOT_OK : if the function is not executed correctly
 */
static Std_ReturnType WaterHeater_CheckSwitches(void)
{
    /* Switches States */
    static Switch_State_t onOffState = SWITCH_NOT_PRESSED, onOffPrevState, upState = SWITCH_NOT_PRESSED, upPrevState, downState = SWITCH_NOT_PRESSED, downPrevState;
    /* Save The Previous States */
    onOffPrevState = onOffState;
    upPrevState = upState;
    downPrevState = downState;
    /* Read The Current States */
    Switch_GetSwitchStatus(WATER_HEATER_ON_OFF_BUTTON, &onOffState);
    Switch_GetSwitchStatus(WATER_HEATER_UP_BUTTON, &upState);
    Switch_GetSwitchStatus(WATER_HEATER_DOWN_BUTTON, &downState);

    /* When Switch Is Released */
    /* ON/OFF State */
    if(onOffState == SWITCH_NOT_PRESSED && onOffPrevState == SWITCH_PRESSED)
    {
        /* If Current Mode Is Off */
        if(WaterHeater_mode == WATER_HEATER_OFF_MODE)
        {
            /* Change Mode To Running Mode */
            WaterHeater_mode = WATER_HEATER_RUNNING_MODE;
            /* Load The Last Saved Temprature */
            Eeprom_ReadByte(WATER_HEATER_TEMP_DATA_ADDRESS, &WaterHeater_temperature);
        }
        else
        {
            /* Turn The Water Heater Off */
            WaterHeater_mode = WATER_HEATER_OFF_MODE;
            Element_SetElementOff(WATER_HEATER_HEATING_ELEMENT);
            Element_SetElementOff(WATER_HEATER_COOLING_ELEMENT);
            Led_SetLedOff(WATER_HEATER_HEATING_LED);
            SSeg_SetDisplay(SSEG_OFF);
            /* Save The Last Set Temprature */
            Eeprom_WriteByte(WATER_HEATER_TEMP_DATA_ADDRESS, WaterHeater_temperature);
        }
    }
    /* When Switch Is Released */
    /* Up State */
    if(upState == SWITCH_NOT_PRESSED && upPrevState == SWITCH_PRESSED)
    {
        switch(WaterHeater_mode)
        {
            case WATER_HEATER_RUNNING_MODE:
                /* If The Mode Wase Running Just Change The Mode */
                WaterHeater_mode = WATER_HEATER_TEMPRATURE_SETTING_MODE;
                WaterHeater_settingModeCounter = WATER_HEATER_COUNTER_RESET_VALUE;
                break;
            case WATER_HEATER_TEMPRATURE_SETTING_MODE:
                /* If The Mode Was Temprature Setting Raise The Temprature By 5 Degrees*/
                WaterHeater_temperature += WATER_HEATER_CHANGE_RATE;
                if(WaterHeater_temperature > WATER_HEATER_UPPER_LIMIT)
                {
                    /* Check For The Limit Violation */
                    WaterHeater_temperature = WATER_HEATER_UPPER_LIMIT;
                }
                else
                {
                    /* Empty Else Statement To Satisfy The Misra Rules */
                }
                WaterHeater_settingModeCounter = WATER_HEATER_COUNTER_RESET_VALUE;
                break;
        }
        /* Display The Set Temprature */
        SSeg_SetNum(SSEG_ONES,WATER_HEATER_GET_ONES(WaterHeater_temperature));
        SSeg_SetNum(SSEG_TENS,WATER_HEATER_GET_TENS(WaterHeater_temperature));
    }
    /* When Switch Is Released */
    /* Down State */
    if(downState == SWITCH_NOT_PRESSED && downPrevState == SWITCH_PRESSED)
    {
        switch(WaterHeater_mode)
        {
            case WATER_HEATER_RUNNING_MODE:
                /* If The Mode Wase Running Just Change The Mode */
                WaterHeater_mode = WATER_HEATER_TEMPRATURE_SETTING_MODE;
                WaterHeater_settingModeCounter = WATER_HEATER_COUNTER_RESET_VALUE;
                break;
            case WATER_HEATER_TEMPRATURE_SETTING_MODE:
                /* If The Mode Was Temprature Setting Decrease The Temprature By 5 Degrees*/
                WaterHeater_temperature -= WATER_HEATER_CHANGE_RATE;
                if(WaterHeater_temperature < WATER_HEATER_LOWER_LIMIT)
                {
                    /* Check For The Limit Violation */
                    WaterHeater_temperature = WATER_HEATER_LOWER_LIMIT;
                }
                else
                {
                    /* Empty Else Statement To Satisfy The Misra Rules */
                }
                WaterHeater_settingModeCounter = WATER_HEATER_COUNTER_RESET_VALUE;
                break;
        }
        /* Display The Set Temprature */
        SSeg_SetNum(SSEG_ONES,WATER_HEATER_GET_ONES(WaterHeater_temperature));
        SSeg_SetNum(SSEG_TENS,WATER_HEATER_GET_TENS(WaterHeater_temperature));
    }
    return E_OK;
}
/**
 * @brief Updates The Counter And Changes Modes According To The Counter
 * 
 *  @returns: A status
 *                 E_OK : if the function is executed correctly
 *                 E_NOT_OK : if the function is not executed correctly
 */
static Std_ReturnType WaterHeater_UpdateCfgModeCounter(void)
{
    /* Check For The Current Mode */
    if(WaterHeater_mode == WATER_HEATER_TEMPRATURE_SETTING_MODE)
    {
        /* If The Setting Mode Exceeded 5 Seconds*/
        if(WaterHeater_settingModeCounter == WATER_HEATER_5_SEC)
        {
            /* Reset The Counter */
            WaterHeater_settingModeCounter = WATER_HEATER_COUNTER_RESET_VALUE;
            /* Go Back To The Running Mode */
            WaterHeater_mode = WATER_HEATER_RUNNING_MODE;
        }
        else
        {
            WaterHeater_settingModeCounter++;
        }
    }
    else
    {
        /* Empty Else Statement To Satisfy The Misra Rules */
    }
    return E_OK;
}
/**
 * @brief Gets A New Reading And Displays The Temperature
 * 
 *  @returns: A status
 *                 E_OK : if the function is executed correctly
 *                 E_NOT_OK : if the function is not executed correctly
 */
static Std_ReturnType WaterHeater_AddReading(void)
{
    static uint8_t readingIndex;
    Adc_Value_t reading; 
    /* Gets The Analog Value */
    Adc_GetValue(&reading);
    /* Calculate The Temperature */
    reading/=WATER_HEATER_TEMPRATURE_SENSOR_FACTOR;
    /* Adds The Reading */
    WaterHeater_readings[readingIndex++] = reading;
    if(readingIndex == WATER_HEATER_NUMBER_OF_READINGS)
    {
        readingIndex = WATER_HEATER_INDEX_RESET_VALUE;
    }
    else
    {
        /* Empty Else Statement To Satisfy The Misra Rules */
    }
    /* Display the current readig in the running mode */
    if(WaterHeater_mode == WATER_HEATER_RUNNING_MODE)
    {
        SSeg_SetNum(SSEG_ONES,WATER_HEATER_GET_ONES(reading));
        SSeg_SetNum(SSEG_TENS,WATER_HEATER_GET_TENS(reading));
        SSeg_SetDisplay(SSEG_ON);
    }
    else
    {
        /* Empty Else Statement To Satisfy The Misra Rules */
    }
    return E_OK;
}
/**
 * @brief Takes Action For The Elements And The Led
 * 
 *  @returns: A status
 *                 E_OK : if the function is executed correctly
 *                 E_NOT_OK : if the function is not executed correctly
 */
static Std_ReturnType WaterHeater_TakeAction(void)
{
    uint8_t readingIndex;
    uint16_t readingsTotal;
    float32_t readingsAvg;
    /* If The Water Heater Is On */
    if(WaterHeater_mode != WATER_HEATER_OFF_MODE)
    {
        /* Calculate the average */
        readingsTotal = 0;
        for(readingIndex=0; readingIndex<WATER_HEATER_NUMBER_OF_READINGS; readingIndex++)
        {
            readingsTotal += (uint16_t)WaterHeater_readings[readingIndex];
        }
        readingsAvg = (float32_t)readingsTotal/(float32_t)WATER_HEATER_NUMBER_OF_READINGS;
        /* Check For The Low Temperature Case */
        if(readingsAvg - (float32_t)WaterHeater_temperature > (float32_t)WATER_HEATER_CHANGE_RATE)
        {
            Element_SetElementOn(WATER_HEATER_COOLING_ELEMENT);
            Element_SetElementOff(WATER_HEATER_HEATING_ELEMENT);
            Led_SetLedOn(WATER_HEATER_HEATING_LED);
            WaterHeater_runningElement = WATER_HEATER_COOLING_ELEMENT_RUNNING;
        }
        /* Check For The High Temperature Case */
        else if((float32_t)WaterHeater_temperature - readingsAvg > (float32_t)WATER_HEATER_CHANGE_RATE)
        {
            Element_SetElementOn(WATER_HEATER_HEATING_ELEMENT);
            Element_SetElementOff(WATER_HEATER_COOLING_ELEMENT);
            WaterHeater_runningElement = WATER_HEATER_HEATING_ELEMENT_RUNNING;
        }
        /* Check For The Suitable Temperature Case */
        else
        {
            /* An Added Feature To Control The Water's Temprature By Turning Off The Heater And The Cooler When The
             * Temprature Difference Is Less Than 5 Degrees */
#ifdef ADD_WATER_TEMPRATURE_CONTROL_FEATURE
            Element_SetElementOff(WATER_HEATER_HEATING_ELEMENT);
            Element_SetElementOff(WATER_HEATER_COOLING_ELEMENT);
            Led_SetLedOff(WATER_HEATER_HEATING_LED);
            WaterHeater_runningElement = WATER_HEATER_NO_ELEMENT_RUNNING;
#endif
        }
    }
    else
    {
        /* Empty Else Statement To Satisfy The Misra Rules */
    }
    
    return E_OK;
}
/**
 * @brief Toggles The Led And The 7-Segment Display 
 * 
 *  @returns: A status
 *                 E_OK : if the function is executed correctly
 *                 E_NOT_OK : if the function is not executed correctly
 */
static Std_ReturnType WaterHeater_Blink(void)
{
    static Led_State_t heatingLedState = LED_OFF;
    static SSeg_display_t ssegDisp = SSEG_OFF;
    /* If The Led Should Be Toggled */
    if(WaterHeater_mode != WATER_HEATER_OFF_MODE && WaterHeater_runningElement == WATER_HEATER_HEATING_ELEMENT_RUNNING)
    {
        Led_SetLedStatus(WATER_HEATER_HEATING_LED, heatingLedState);
        heatingLedState = !heatingLedState;
    }
    else
    {
        /* Empty Else Statement To Satisfy The Misra Rules */
    }
    /* If The 7-Segment Should Be Toggled */
    if(WaterHeater_mode == WATER_HEATER_TEMPRATURE_SETTING_MODE)
    {
        SSeg_SetDisplay(ssegDisp);
        ssegDisp = !ssegDisp;
    }
    else
    {
        /* Empty Else Statement To Satisfy The Misra Rules */
    }
    return E_OK;
}