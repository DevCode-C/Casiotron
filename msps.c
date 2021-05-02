#include "globals.h"

void HAL_MspInit(void){
    RCC_OscInitTypeDef RCC_InitStructure = {0};
    RCC_ClkInitTypeDef RCC_ClkStructure = {0};

    RCC_InitStructure.OscillatorType = RCC_OSCILLATORTYPE_HSI48;
    RCC_InitStructure.HSI48State = RCC_HSI48_ON;
    RCC_InitStructure.PLL.PLLState = RCC_PLL_ON;
    RCC_InitStructure.PLL.PLLSource = RCC_PLLSOURCE_HSI48;
    RCC_InitStructure.PLL.PREDIV = RCC_PREDIV_DIV2;
    RCC_InitStructure.PLL.PLLMUL = RCC_PLL_MUL2;
    HAL_RCC_OscConfig(&RCC_InitStructure);
    
    RCC_ClkStructure.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1);
    RCC_ClkStructure.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkStructure.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkStructure.APB1CLKDivider = RCC_HCLK_DIV8;
    HAL_RCC_ClockConfig(&RCC_ClkStructure,FLASH_LATENCY_1);
}

void HAL_UART_MspInit(UART_HandleTypeDef *huart){
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_USART2_CLK_ENABLE();
    GPIO_InitTypeDef GPIOA_InitStruture;

    GPIOA_InitStruture.Pin = GPIO_TX | GPIO_RX;
    GPIOA_InitStruture.Mode = GPIO_MODE_AF_PP;
    GPIOA_InitStruture.Pull = GPIO_NOPULL;
    GPIOA_InitStruture.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIOA_InitStruture.Alternate = GPIO_AF1_USART2;   
    HAL_GPIO_Init(GPIOA,&GPIOA_InitStruture);
}

void HAL_RTC_MspInit(RTC_HandleTypeDef *hrtc){
    __HAL_RCC_PWR_CLK_ENABLE();
    HAL_PWR_EnableBkUpAccess();
    __HAL_RCC_LSE_CONFIG(RCC_LSE_ON);

    __HAL_RCC_RTC_CONFIG(RCC_RTCCLKSOURCE_LSE);
    __HAL_RCC_RTC_ENABLE();

    __HAL_RTC_ALARMA_ENABLE(hrtc);
    HAL_NVIC_EnableIRQ(RTC_IRQn);
    HAL_NVIC_SetPriority(RTC_IRQn,NVIC_PRIORITY_HIGH,1);
}

void HAL_WWDG_MspInit(WWDG_HandleTypeDef *hwwdg){
    __HAL_RCC_WWDG_CLK_ENABLE();
}

void HAL_SPI_MspInit(SPI_HandleTypeDef *hspi){
	GPIO_InitTypeDef GPIO_InitStructSPIA = {0};
    GPIO_InitTypeDef GPIO_InitStructSPIB = {0};
    GPIO_InitTypeDef GPIO_InitStructLCD  = {0};
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

	GPIO_InitStructSPIA.Pin = GPIO_PIN_6|GPIO_PIN_7;
    GPIO_InitStructSPIA.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStructSPIA.Pull = GPIO_NOPULL;
    GPIO_InitStructSPIA.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStructSPIA.Alternate = GPIO_AF0_SPI1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStructSPIA);

    GPIO_InitStructSPIB.Pin = GPIO_PIN_3;
    GPIO_InitStructSPIB.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStructSPIB.Pull = GPIO_NOPULL;
    GPIO_InitStructSPIB.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStructSPIB.Alternate = GPIO_AF0_SPI1;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStructSPIB);

    GPIO_InitStructLCD.Pin = GPIO_LCD_PINS;
    GPIO_InitStructLCD.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructLCD.Pull = GPIO_PULLDOWN;
    GPIO_InitStructLCD.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB,&GPIO_InitStructLCD);
}