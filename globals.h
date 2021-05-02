#ifndef GLOBALS_H
#define GLOBALS_H
/*INCLUDES----------------------------- */
//#include "main.h"
#include "stm32f0xx.h"
#include "stm32f072xb.h"
#include "stm32f0xx_hal_uart.h"
#include "stm32f0xx_hal_rtc.h"
#include "stm32f0xx_hal_rcc.h"
#include "stm32f0xx_hal_rcc_ex.h"
#include "stm32f0xx_hal.h"
#include "stm32f0xx_hal_conf.h"
#include "stm32f0xx_hal_rtc_ex.h"
#include "stm32f0xx_hal_wwdg.h"
#include "stm32f0xx_hal_gpio_ex.h"
#include "stm32f0xx_hal_spi.h"
#include "stm32f0xx_hal_spi_ex.h"
#include <string.h>
#include <stdint.h>
#include <stdio.h>
/*-------------------------------------*/
/*Defines----------------------------- */
#define SET                                 1U
#define RESET                               0U

#define PIN_BUTTON      (GPIO_PIN_13)
#define BUTTON_PORT     (GPIOC)

#define SERIAL_PORT     GPIOA
#define GPIO_TX         GPIO_PIN_2
#define GPIO_RX         GPIO_PIN_3

#define GPIO_LED        GPIO_PIN_5
#define GPIO_LED_PORT   GPIOA

#define GPIO_LCD_PINS   (GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6)
#define GPIO_LCD_CS     (GPIO_PIN_4)
#define GPIO_LCD_RS     (GPIO_PIN_5)
#define GPIO_LCD_RST    (GPIO_PIN_6)
#define LCD_PORT        (GPIOB)

#define NVIC_PRIORITY_HIGHEST               0U
#define NVIC_PRIORITY_HIGH                  1U
#define NVIC_PRIORITY_LOW                   2U
#define NVIC_PRIORITY_LOWEST                3U

#define NVIC_SUBPRIORITY_HIGHEST            0U
#define NVIC_SUBPRIORITY_HIGH               1U
#define NVIC_SUBPRIORITY_LOW                2U
#define NVIC_SUBPRIORITY_LOWEST             3U

#define NONE                                0U
#define TIME                                1U 
#define DATE                                2U
#define ALARM                               3U

/**/
/*Variables--------------------------- */
/**/

/*Enums*/

/**/
/*Structures*/
typedef struct{
    uint8_t msg_Type;       /* Message Type     */
    uint8_t Hour_Day;       /* Hour or Day      */
    uint8_t Min_Month;      /* Minutes or Month */
    uint16_t Sec_Year;
}_msg_Serial;
/**/

extern _msg_Serial          InfoGeneral;
extern UART_HandleTypeDef 	UART_InitStructure;
extern RTC_HandleTypeDef    RTC_Handle;

extern uint32_t timetick ;
#endif

