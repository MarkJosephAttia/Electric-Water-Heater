/**
 * @file Sched_Cfg.c
 * @author Mark Attia (markjosephattia@gmail.com)
 * @brief This file contains the configurations implementation for the Scheduler
 * @version 0.1
 * @date 2020-03-08
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "Std_Types.h"
#include "Sched_Cfg.h"
#include "Sched.h"

extern const task_t WaterHeater_InitTask;
extern const task_t WaterHeater_Task;
extern const task_t SSeg_task;
extern const task_t Switch_task;

const sysTaskInfo_t Sched_sysTaskInfo[SCHED_NUMBER_OF_TASKS] = 
{
    /* Task                        First Delay */
    {&WaterHeater_InitTask,              0      },
    {&Switch_task,                       1     },
    {&WaterHeater_Task,                  1     },
    {&SSeg_task,                         2     }
};
