/*
 * timer.c
 *
 *  Created on: Sep 20, 2019
 *      Author: Mina Raouf
 */

#include "timer.h"

Std_Func_t Timer_Init (TIMERS_t TIMER)
{
	uint8 retval;
	if (TIMER < TOTAL_TIMERS)
	{
		TIMER_cnfg_arr[TIMER].IS_OK = INITIALIZED;
		switch (TIMER)
		{
		case TIMER0:
			if ((TIMER_cnfg_arr[TIMER0].clock) == EXTERNAl) // To check if the clock connected externally
			{
				if ((TIMER_cnfg_arr[TIMER0].EDGE) == FALLING_EDGE)
				{
					REG_TCCR0 = REG_TCCR0 | ((1u <<CS01) | (1u <<CS02));
					REG_TCCR0 &=~(1u<<CS00);
				}
				else if ((TIMER_cnfg_arr[TIMER0].EDGE) == RISING_EDGE)
				{
					REG_TCCR0 = REG_TCCR0 | ((1u <<CS00) | (1u <<CS01) | (1u <<CS02));
				}
				else
				{
					TIMER_cnfg_arr[TIMER0].EDGE = DEFAULT;
				}

			}
			else if ((TIMER_cnfg_arr[TIMER0].clock) == INTERNAL)
			{
				if((TIMER_cnfg_arr[TIMER0].freq) == CRYSTAL_FREQ)
				{
					if ((TIMER_cnfg_arr[TIMER0].PRESCALER) == NONE)
					{
						REG_TCCR0 &=~((1u<<CS01) | (1u<<CS02));
						REG_TCCR0 = REG_TCCR0 | (1u <<CS00);
					}
					else if ((TIMER_cnfg_arr[TIMER0].PRESCALER) == PRESCALE_8)
					{
						REG_TCCR0 &=~((1u<<CS00) | (1u<<CS02));
						REG_TCCR0 = REG_TCCR0 | (1u <<CS01);
					}
					else if ((TIMER_cnfg_arr[TIMER0].PRESCALER) == PRESCALE_64)
					{
						REG_TCCR0 = REG_TCCR0 | ((1u <<CS00) | (1u <<CS01));
						REG_TCCR0 &=~ (1u <<CS02);
					}
					else if ((TIMER_cnfg_arr[TIMER0].PRESCALER) == PRESCALE_256)
					{
						REG_TCCR0 = REG_TCCR0 | (1u <<CS01);
						REG_TCCR0 &=~ ((1u<<CS01) | (1u<<CS00));
					}
					else if ((TIMER_cnfg_arr[TIMER0].PRESCALER) == PRESCALE_1024)
					{
						REG_TCCR0 = REG_TCCR0 | ((1u <<CS00) | (1u <<CS02))
						REG_TCCR0 &=~ (1u<<CS01);
					}
					else
					{
						retval = NOK;
					}
				}
				else
				{
					retval = NOK;
				}

			}
			else
			{
				retval = NOK;
			}
			// To check on the TOMER0 operating mode
			if ((TIMER_cnfg_arr[TIMER0].MODE) == NORMAL)
			{
				// In normal mode. clear bit WGM00, bit WGM01, COM00, COM01
				REG_TCCR0 &=~ ((1u<<WGM00) | (1u<<WGM01));
				REG_TCCR0 &=~ ((1u<<COM00) | (1u<<COM01)); //default hardware values
				if((TIMER_cnfg_arr[TIMER0].COMPARE) == TOOGLE)
				{
					REG_TCCR0 |= (1u <<COM00);
					REG_TCCR0 &=~ (1u<<COM01);
				}
				else if((TIMER_cnfg_arr[TIMER0].COMPARE) == CLEAR)
				{
					REG_TCCR0 |= (1u <<COM01);
					REG_TCCR0 &=~ (1u<<COM00);
				}
				else if ((TIMER_cnfg_arr[TIMER0].COMPARE) == SET)
				{
					REG_TCCR0 |= ((1u<<COM00) | (1u<<COM01));
				}
				else
				{
					retval = NOK;
				}

			}
			else if ((TIMER_cnfg_arr[TIMER0].MODE) == PHASECORRECTPWM)
			{
				// In phase correct PWM mode.  Set bit WGM00
				REG_TCCR0 |= (1u <<WGM00);
				REG_TCCR0 &=~ (1u<<WGM01);
				if ((TIMER_cnfg_arr[TIMER0].COMPARE) == CLEAR)
				{
					REG_TCCR0 |= (1u <<COM01);
					REG_TCCR0 &=~ (1u<<COM00);
				}
				else if ((TIMER_cnfg_arr[TIMER0].COMPARE) == SET)
				{
					REG_TCCR0 |= ((1u<<COM00) | (1u<<COM01));
				}
				else
				{
					retval = NOK;
				}
			}
			else if ((TIMER_cnfg_arr[TIMER0].MODE) == CTC)
			{
				REG_TCCR0 |= (1u <<WGM01);
				REG_TCCR0 &=~ (1u<<WGM00);
				if((TIMER_cnfg_arr[TIMER0].COMPARE) == TOOGLE)
				{
					REG_TCCR0 |= (1u <<COM00);
					REG_TCCR0 &=~ (1u<<COM01);
				}
				else if((TIMER_cnfg_arr[TIMER0].COMPARE) == CLEAR)
				{
					REG_TCCR0 |= (1u <<COM01);
					REG_TCCR0 &=~ (1u<<COM00);
				}
				else if ((TIMER_cnfg_arr[TIMER0].COMPARE) == SET)
				{
					REG_TCCR0 |= ((1u<<COM00) | (1u<<COM01));
				}
				else
				{
					retval = NOK;
				}
			}
			else if ((TIMER_cnfg_arr[TIMER0].MODE) == FASTPWM)
			{
				REG_TCCR0 = REG_TCCR0 | ((1u <<WGM01) | (1u <<WGM00));
			}
			else
			{
				retval = NOK;
			}
			if ((TIMER_cnfg_arr[TIMER0].STATE) == POLLING)
			{
				REG_TCCR0 &=~ ((1u<<WGM00) | (1u<<WGM01));
			}
			else if ((TIMER_cnfg_arr[TIMER0].STATE) == INTERRUPT)
			{
				if ((TIMER_cnfg_arr[TIMER0].MODE) == CTC)
				{
					// in CTC mode, set the OCIE0 bit in
					REG_TIMSK |= (1u <<OCIE0);
				}
				else if((TIMER_cnfg_arr[TIMER0].MODE) == NORMAL)
				{
					REG_TIMSK |= (1u <<TOIE0);
				}
				else
				{
					retval = NOK;
				}
			}
			else
			{
				retval = NOK;
			}

		}
		return retval;
		case TIMER1:


	}
	else
	{
		retval = NOK;
		return retval;
	}

}


