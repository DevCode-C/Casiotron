#ifndef LCD_H
#define LCD_H
/*Privates Includes---------------------------------------------*/
#include "globals.h"
/*--------------------------------------------------------------*/

/*Privates Defines----------------------------------------------*/
#define CLEAR_LCD   1U
/*--------------------------------------------------------------*/

/*Privates Typedefs---------------------------------------------*/
typedef struct{
    SPI_HandleTypeDef   *SPIHandlet;
    GPIO_TypeDef        *RstPort;
    uint32_t            RstPin;
    GPIO_TypeDef        *RsPort;
    uint32_t            RsPin;
    GPIO_TypeDef        *CsPort;
    uint32_t            CsPin;
}LCD_HandleTypeDef;
/*--------------------------------------------------------------*/

/*Private Functions---------------------------------------------*/

/**---------------------------------------------------------------
Brief.- Breve descripcion de la función
Param.- <nombre> descripcion del parámetro. si existe
Param.- <nombre> descripcion del parámetro. si existe
Return.- descripcion del valor del parámetro. si existe
----------------------------------------------------------------*/
void MOD_LCD_Init( LCD_HandleTypeDef *hlcd );

/**---------------------------------------------------------------
Brief.- Breve descripcion de la función
Param.- <nombre> descripcion del parámetro. si existe
Param.- <nombre> descripcion del parámetro. si existe
Return.- descripcion del valor del parámetro. si existe
----------------------------------------------------------------*/
__weak void MOD_LCD_MspInit( LCD_HandleTypeDef *hlcd );
	
/**---------------------------------------------------------------
Brief.- Breve descripcion de la función
Param.- <nombre> descripcion del parámetro. si existe
Param.- <nombre> descripcion del parámetro. si existe
Return.- descripcion del valor del parámetro. si existe
----------------------------------------------------------------*/
void MOD_LCD_Command( LCD_HandleTypeDef *hlcd, uint8_t cmd );

/**---------------------------------------------------------------
Brief.- Breve descripcion de la función
Param.- <nombre> descripcion del parámetro. si existe
Param.- <nombre> descripcion del parámetro. si existe
Return.- descripcion del valor del parámetro. si existe
----------------------------------------------------------------*/
void MOD_LCD_Data( LCD_HandleTypeDef *hlcd, uint8_t data );

/**---------------------------------------------------------------
Brief.- Breve descripcion de la función
Param.- <nombre> descripcion del parámetro. si existe
Param.- <nombre> descripcion del parámetro. si existe
Return.- descripcion del valor del parámetro. si existe
----------------------------------------------------------------*/
void MOD_LCD_String( LCD_HandleTypeDef *hlcd, char *str, uint8_t size );

/**---------------------------------------------------------------
Brief.- Breve descripcion de la función
Param.- <nombre> descripcion del parámetro. si existe
Param.- <nombre> descripcion del parámetro. si existe
Return.- descripcion del valor del parámetro. si existe
----------------------------------------------------------------*/
void MOD_LCD_SetCursor( LCD_HandleTypeDef *hlcd, uint8_t row, uint8_t col );

/*--------------------------------------------------------------*/

#endif