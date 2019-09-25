/*
 * timer.h
 *
 *  Created on: Sep 20, 2019
 *      Author: Mina Raouf
 */

#ifndef TIMER_H_
#define TIMER_H_

#include"DIO.h"
#include "registers.h"
#include "stdtypes.h"
#include "timerconfig.h"

#define F0C0 7
#define WGM00 6
#define COM01 5
#define COM00 4
#define WGM01 3
#define CS02 2
#define CS01 1
#define CS00 0
#define TOIE0 0
#define OCIE0 1
#define CRYSTAL_FREQ 8000

Std_Func_t Timer_Init (TIMERS_t);
Std_Func_t Generate_PWM (uint8);
Std_Func_t Timer_Wait(Std_Func_t, uint32);
Std_Func_t Timer_Deinit (TIMERS_t);





#endif /* TIMER_H_ */
