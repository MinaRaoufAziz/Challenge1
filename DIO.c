/*
 * DIO.c
 *
 * Created: 9/13/2019 10:49:12 AM
 *  Author: Peter
 */ 

#include "DIO.h"
#include "registers.h"
#include "stdtypes.h"
#include "DIO_cnfg.h"

Std_Func_t DIO_init (PINS_t input)
{
	Std_Func_t retval = OK;
	if (input <= MAX_NUM_OF_PINS)
	{
		DIO_cnfg_arr[input].IS_init_arr = INITIALIZED;
		switch(DIO_cnfg_arr[input].PORT)
		{
			case PORT_A:
					if(DIO_cnfg_arr[input].DIR == OUTPUT)
					{
						REG_DDRA |=(1u<<DIO_cnfg_arr[input].PIN);
						if (DIO_cnfg_arr[input].OUT == HIGH)
						{
							REG_PORTA |=(1u<<DIO_cnfg_arr[input].PIN);
						}
						else if (DIO_cnfg_arr[input].OUT == LOW)
						{
							REG_PORTA &=~(1u<<DIO_cnfg_arr[input].PIN);
						}
						else
						{
							DIO_cnfg_arr[input].IS_init_arr = NOT_INITIALIZED;
							retval = NOK;
						}
					}
					else if(DIO_cnfg_arr[input].DIR == INPUT)
					{
						REG_DDRA &=~(1u<<DIO_cnfg_arr[input].PIN);
						if (DIO_cnfg_arr[input].RES == PULLUP)
						{
							REG_PORTA |=(1u<<DIO_cnfg_arr[input].PIN);
						}
						else if (DIO_cnfg_arr[input].RES == EXTRES)
						{
							REG_PORTA &=~(1u<<DIO_cnfg_arr[input].PIN);
						}
						else
						{
							DIO_cnfg_arr[input].IS_init_arr = NOT_INITIALIZED;
							retval = NOK;
						}
					}
					else
					{
						DIO_cnfg_arr[input].IS_init_arr = NOT_INITIALIZED;
						retval = NOK;
					}
				break;
		case PORT_B:
			if(DIO_cnfg_arr[input].DIR == OUTPUT)
				{
				REG_DDRB |=(1u<<DIO_cnfg_arr[input].PIN);
					if (DIO_cnfg_arr[input].OUT == HIGH)
					{
						REG_PORTB |=(1u<<DIO_cnfg_arr[input].PIN);
					}
					else if (DIO_cnfg_arr[input].OUT == LOW)
					{
						REG_PORTB &=~(1u<<DIO_cnfg_arr[input].PIN);
					}
					else
					{
						DIO_cnfg_arr[input].IS_init_arr = NOT_INITIALIZED;
						retval = NOK;
					}
				}
			else if(DIO_cnfg_arr[input].DIR == INPUT)
				{
				REG_DDRB &=~(1u<<DIO_cnfg_arr[input].PIN);
					if (DIO_cnfg_arr[input].RES == PULLUP)
					{
						REG_PORTB |=(1u<<DIO_cnfg_arr[input].PIN);
					}
					else if (DIO_cnfg_arr[input].RES == EXTRES)
					{
						REG_PORTB &=~(1u<<DIO_cnfg_arr[input].PIN);
					}
					else
					{
						DIO_cnfg_arr[input].IS_init_arr = NOT_INITIALIZED;
						retval = NOK;
					}
				}
			else
				{
					DIO_cnfg_arr[input].IS_init_arr = NOT_INITIALIZED;
					retval = NOK;
				}
			break;
			case PORT_C:
				if(DIO_cnfg_arr[input].DIR == OUTPUT)
				{
					REG_DDRC |=(1u<<DIO_cnfg_arr[input].PIN);
					if (DIO_cnfg_arr[input].OUT == HIGH)
					{
						REG_PORTC |=(1u<<DIO_cnfg_arr[input].PIN);
					}
					else if (DIO_cnfg_arr[input].OUT == LOW)
					{
						REG_PORTC &=~(1u<<DIO_cnfg_arr[input].PIN);
					}
					else
					{
						DIO_cnfg_arr[input].IS_init_arr = NOT_INITIALIZED;
						retval = NOK;
					}
				}
				else if(DIO_cnfg_arr[input].DIR == INPUT)
				{
					REG_DDRC &=~(1u<<DIO_cnfg_arr[input].PIN);
					if (DIO_cnfg_arr[input].RES == PULLUP)
					{
						REG_PORTC |=(1u<<DIO_cnfg_arr[input].PIN);
					}
					else if (DIO_cnfg_arr[input].RES == EXTRES)
					{
						REG_PORTC &=~(1u<<DIO_cnfg_arr[input].PIN);
					}
					else
					{
						DIO_cnfg_arr[input].IS_init_arr = NOT_INITIALIZED;
						retval = NOK;
					}
				}
				else
				{
					DIO_cnfg_arr[input].IS_init_arr = NOT_INITIALIZED;
					retval = NOK;
				}
				break;
			case PORT_D:
				if(DIO_cnfg_arr[input].DIR == OUTPUT)
				{
					REG_DDRD |=(1u<<DIO_cnfg_arr[input].PIN);
					if (DIO_cnfg_arr[input].OUT == HIGH)
					{
						REG_PORTD |=(1u<<DIO_cnfg_arr[input].PIN);
					}
					else if (DIO_cnfg_arr[input].OUT == LOW)
					{
						REG_PORTD &=~(1u<<DIO_cnfg_arr[input].PIN);
					}
					else
					{
						DIO_cnfg_arr[input].IS_init_arr = NOT_INITIALIZED;
						retval = NOK;
					}
				}
				else if(DIO_cnfg_arr[input].DIR == INPUT)
				{
					REG_DDRD &=~(1u<<DIO_cnfg_arr[input].PIN);
					if (DIO_cnfg_arr[input].RES == PULLUP)
					{
						REG_PORTD |=(1u<<DIO_cnfg_arr[input].PIN);
					}
					else if (DIO_cnfg_arr[input].RES == EXTRES)
					{
						REG_PORTD &=~(1u<<DIO_cnfg_arr[input].PIN);
					}
					else
					{
						DIO_cnfg_arr[input].IS_init_arr = NOT_INITIALIZED;
						retval = NOK;
					}
				}
				else
				{
					DIO_cnfg_arr[input].IS_init_arr = NOT_INITIALIZED;
					retval = NOK;
				}
				break;
			default:
				DIO_cnfg_arr[input].IS_init_arr = NOT_INITIALIZED;
				retval = NOK;
			}	
	}
	else
	{
		DIO_cnfg_arr[input].IS_init_arr = NOT_INITIALIZED;
	}
		retval = NOK;
	return retval;
}

Std_Func_t DIO_read (uint8 port,uint8 pin,uint8 * Pval, PINS_t input)
{
	Std_Func_t retval = OK;
	if ((DIO_cnfg_arr[input].PORT == port)&&(DIO_cnfg_arr[input].PIN == pin))
	{
		if((DIO_cnfg_arr[input].IS_init_arr == INITIALIZED)&&(DIO_cnfg_arr[input].DIR == INPUT))
		{
			switch (port)
			{
				case PORT_A:
					*Pval = (1u&(REG_PINA>>pin));
					break;
				case PORT_B:
					*Pval = (1u&(REG_PINB>>pin));
					break;
				case PORT_C:
					*Pval = (1u&(REG_PINC>>pin));
					break;
				case PORT_D:
					*Pval = (1u&(REG_PIND>>pin));
					break;
			}
		}
		else
		{
			retval = NOK;
		}
	}
	else
	{
		retval = OK;
	}
	return retval;
}

Std_Func_t DIO_write (uint8 port,uint8 pin,uint8 val, PINS_t input)
{
	Std_Func_t retval = OK;
	if ((DIO_cnfg_arr[input].PORT == port)&&(DIO_cnfg_arr[input].PIN == pin))
	{
		if(((DIO_cnfg_arr[input].IS_init_arr == INITIALIZED))
			&&(DIO_cnfg_arr[input].DIR == OUTPUT)
			&&((val == HIGH)||(val == LOW)))
		{
			switch (port)
			{
				case PORT_A:
					if (val == HIGH)
					{
						REG_PORTA |=(1u<<pin);
					}
					else
					{
						REG_PORTA &=~(1u<<pin);
					}
					break;
				case PORT_B:
					if (val == HIGH)
					{
						REG_PORTB |=(1u<<pin);
					}
					else
					{
						REG_PORTB &=~(1u<<pin);
					}
					break;
				case PORT_C:
					if (val == HIGH)
					{
						REG_PORTC |=(1u<<pin);
					}
					else
					{
						REG_PORTC &=~(1u<<pin);
					}
					break;
				case PORT_D:
					if (val == HIGH)
					{
						REG_PORTD |=(1u<<pin);
					}
					else
					{
						REG_PORTD &=~(1u<<pin);
					}
					break;
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
	return retval;
}
