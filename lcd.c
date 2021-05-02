#include "lcd.h"

void MOD_LCD_Init( LCD_HandleTypeDef *hlcd ){
    MOD_LCD_MspInit(hlcd);

    HAL_GPIO_WritePin(LCD_PORT,GPIO_LCD_CS,SET);
    HAL_GPIO_WritePin(LCD_PORT,GPIO_LCD_RST,RESET);
    HAL_Delay(2);
    HAL_GPIO_WritePin(LCD_PORT,GPIO_LCD_RST,SET);
    HAL_Delay(20);
}

void MOD_LCD_Command( LCD_HandleTypeDef *hlcd, uint8_t cmd ){
    //HAL_SPI_Transmit_IT(hlcd,cmd,sizeof(cmd));
}