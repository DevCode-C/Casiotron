#include "stm32f0xx.h"
#include "stm32f0xx_hal_gpio.h"
#include "globals.h"

void USART2_IRQHandler(void);
void RTC_IRQHandler(void);
void EXTI4_15_IRQHandler(void);

void NMI_Handler(void){

}

void HardFault_Handler(void){
/* Go to infinite loop when Hard Fault exception occurs */
while (1){
}
}

void SVC_Handler(void){

}

void PendSV_Handler(void){

}

void SysTick_Handler(void){
HAL_IncTick();
}

void USART2_IRQHandler(void){
    HAL_UART_IRQHandler(&UART_InitStructure);
}

void RTC_IRQHandler(void){
    HAL_RTC_AlarmIRQHandler(&RTC_Handle);
}

void EXTI4_15_IRQHandler(void){
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_13);
}

