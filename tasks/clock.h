#ifndef CLOCK_H
#define CLOCK_H
/*Includes--------------------------------------------*/
#include "globals.h"
#include "stm32f0xx_hal_gpio.h"
#include "stm32f072xb.h"
/*----------------------------------------------------*/
/*Privates Defines-------------------*/
#define RTC_ASYNCH_PREDIV  0x7F
#define RTC_SYNCH_PREDIV   0x00FF

//FSM of Clock
#define IDLE            0U
#define Mostrar         1U
#define ActivarAlarma   2U
#define MostrarAlarma   3U
#define RTCConfig       4U

/**/
/*Private functions--------------------------------------------*/
void ClockInit( void );
void ClockTask( void );
/*----------------------------------------------------*/
#endif