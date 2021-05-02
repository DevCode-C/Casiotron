/*Includes-----------------------------------------------*/
#include "serial.h"
#include "clock.h"
#include "globals.h"
/**/

/*Private typedef----------------------------------------*/
static WWDG_HandleTypeDef	WWDG_Handle;
/**/

/*Private Variables--------------------------------------*/
uint32_t SystemTick;
uint32_t timetick;

/**/

/*Private Functions prototypes---------------------------*/
extern void initialise_monitor_handles(void);
static void GPIO_Init(void);
static void HeartBeat(void);
static void WatchDogInit(void);
static void Peth_the_dog(void);
static void SPI_Init(void);
/*-------------------------------------------------------*/


int main(void){
	initialise_monitor_handles(); //
	

	HAL_Init(); // 
	if (__HAL_RCC_GET_FLAG(RCC_FLAG_WWDGRST) != RESET){
        /* WWDGRST flag set: Print Reset */
        printf("RESET\n");
    }

    /* Clear reset flags in any case */
    __HAL_RCC_CLEAR_RESET_FLAGS();
	SPI_Init();
	SerialInit();
	ClockInit();
	GPIO_Init(); 		//GPIOs Configuration 
	WatchDogInit(); 	//WWDG Configuration
	
	timetick = HAL_GetTick();
	while (1){
		SerialTask();
		ClockTask();
		HeartBeat();
		Peth_the_dog();
  	}
}



void GPIO_Init(void){
	__HAL_RCC_SYSCFG_CLK_ENABLE();

	GPIO_InitTypeDef  	GPIO_InitLED;
	__HAL_RCC_GPIOA_CLK_ENABLE();
	
 	GPIO_InitLED.Mode  = GPIO_MODE_OUTPUT_PP;
  	GPIO_InitLED.Pull  = GPIO_NOPULL;
  	GPIO_InitLED.Speed = GPIO_SPEED_FREQ_HIGH;
  	GPIO_InitLED.Pin = GPIO_LED;
  	HAL_GPIO_Init(GPIO_LED_PORT, &GPIO_InitLED);
	SystemTick 		= 	HAL_GetTick();
}

void HeartBeat(void){
	if ((HAL_GetTick()-SystemTick) >= 300){
			SystemTick = HAL_GetTick();
			HAL_GPIO_TogglePin(GPIO_LED_PORT,GPIO_LED);
		}
}

void WatchDogInit(void){

	WWDG_Handle.Instance = WWDG;
    WWDG_Handle.Init.Prescaler = WWDG_PRESCALER_4;
    WWDG_Handle.Init.Window    = 0x7F;
    WWDG_Handle.Init.Counter   = 0x7F;
    WWDG_Handle.Init.EWIMode   = WWDG_EWI_DISABLE;
	HAL_WWDG_Init(&WWDG_Handle);
	
}

void Peth_the_dog(void){
	// if((HAL_GetTick() - SystemTickWWDG) >= 40U){
		HAL_WWDG_Refresh(&WWDG_Handle);
		// SystemTickWWDG = HAL_GetTick();
	// }
}

void SPI_Init(void){
	SPI_HandleTypeDef SPI_InitStructure;
	__HAL_RCC_SPI1_CLK_ENABLE();
	SPI_InitStructure.Instance 					= SPI1;
	SPI_InitStructure.Init.Direction 			= SPI_DIRECTION_2LINES;
	SPI_InitStructure.Init.FirstBit 			= SPI_FIRSTBIT_MSB;
	SPI_InitStructure.Init.Mode 				= SPI_MODE_MASTER;
	SPI_InitStructure.Init.DataSize 			= SPI_DATASIZE_8BIT;
	SPI_InitStructure.Init.BaudRatePrescaler 	= SPI_BAUDRATEPRESCALER_64;
	SPI_InitStructure.Init.CLKPolarity			= SPI_POLARITY_LOW;
	SPI_InitStructure.Init.CLKPhase 			= SPI_PHASE_2EDGE;
	SPI_InitStructure.Init.CRCCalculation		= SPI_CRCCALCULATION_DISABLE;
	SPI_InitStructure.Init.TIMode				= SPI_TIMODE_DISABLE;
	SPI_InitStructure.Init.NSSPMode				= SPI_NSS_PULSE_DISABLE;
	SPI_InitStructure.Init.CRCPolynomial		= 7;

	HAL_SPI_Init(&SPI_InitStructure);
}
