#ifndef SERIAL_H
#define SERIAL_H
/*Includes--------------------------------------------*/
#include "globals.h"
#include "stm32f0xx_hal_gpio.h"
#include "stm32f0xx_hal_uart.h"
#include "stm32f0xx_hal_uart_ex.h"
#include "stm32f0xx_hal_rcc.h"
#include "stm32f0xx_hal_cortex.h"
#include "stm32f072xb.h"
/*----------------------------------------------------*/
/*Defines --------------------------------------------*/
#define Serial_IDLE             0u
#define Serial_AT               1u
#define Serial_TIME             2u
#define Serial_DATE             3u
#define Serial_ALARM            4u    
#define Serial_ERROR            5u
#define Serial_OK               6u

#define SerialBuffer            30U
/*----------------------------------------------------*/
/*Private Functions-----------------------------------*/

/**---------------------------------------------------------------
Brief.- Init all the configurations about serial (UART and GPIO)
----------------------------------------------------------------*/
void SerialInit( void );

/**---------------------------------------------------------------
Brief.- Breve descripcion de la función
----------------------------------------------------------------*/
void SerialTask( void );

/**---------------------------------------------------------------
Brief.- Breve descripcion de la función
----------------------------------------------------------------*/
uint32_t strtoint(char * str);

/**---------------------------------------------------------------
Brief.- Breve descripcion de la función
Param.- <nombre> descripcion del parámetro. si existe
Param.- <nombre> descripcion del parámetro. si existe
Return.- descripcion del valor del parámetro. si existe
----------------------------------------------------------------*/
uint8_t TestOfDataTime(uint32_t hh, uint32_t mm, uint32_t ss);

/**---------------------------------------------------------------
Brief.- Breve descripcion de la función
Param.- <nombre> descripcion del parámetro. si existe
Param.- <nombre> descripcion del parámetro. si existe
Return.- descripcion del valor del parámetro. si existe
----------------------------------------------------------------*/
uint8_t TestOfDataDate(uint32_t hh, uint32_t mm, uint32_t yyyy);
/*--------------------------------------------------------------*/
#endif