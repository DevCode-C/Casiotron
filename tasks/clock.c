#include "clock.h"


RTC_HandleTypeDef   RTC_Handle;
RTC_TimeTypeDef 	RTC_TImeConfig;
RTC_DateTypeDef 	RTC_DateConfig;
RTC_AlarmTypeDef 	RTC_AlarmConfig;

static uint8_t Button = 0;
static uint8_t Alarm = 0;
static uint8_t StatesRTC;

void ClockInit(void){
	
    GPIO_InitTypeDef  	GPIO_InitStructC;
    __HAL_RCC_GPIOC_CLK_ENABLE();
	GPIO_InitStructC.Mode  = GPIO_MODE_IT_FALLING;
  	GPIO_InitStructC.Pull  = GPIO_PULLUP;
  	GPIO_InitStructC.Speed = GPIO_SPEED_FREQ_HIGH;
  	GPIO_InitStructC.Pin = GPIO_PIN_13;
	HAL_GPIO_Init(GPIOC,&GPIO_InitStructC);
	HAL_NVIC_EnableIRQ(EXTI4_15_IRQn);
	HAL_NVIC_SetPriority(EXTI4_15_IRQn,NVIC_PRIORITY_HIGH,NVIC_SUBPRIORITY_LOWEST);

	RTC_Handle.Instance             = RTC;
    RTC_Handle.Init.HourFormat      = RTC_HOURFORMAT_24;
    RTC_Handle.Init.AsynchPrediv    = RTC_ASYNCH_PREDIV;
    RTC_Handle.Init.SynchPrediv     = RTC_SYNCH_PREDIV;
    RTC_Handle.Init.OutPut          = RTC_OUTPUT_DISABLE;
    RTC_Handle.Init.OutPutPolarity  = RTC_OUTPUT_POLARITY_HIGH;
    RTC_Handle.Init.OutPutType      = RTC_OUTPUT_TYPE_OPENDRAIN;
    HAL_RTC_Init(&RTC_Handle);

    RTC_TImeConfig.Hours = 05;
    RTC_TImeConfig.Minutes = 15;
    RTC_TImeConfig.Seconds = 30;
    HAL_RTC_SetTime(&RTC_Handle,&RTC_TImeConfig,RTC_FORMAT_BIN);

    RTC_DateConfig.Date = 10;
    RTC_DateConfig.Month = RTC_MONTH_JANUARY;
    RTC_DateConfig.Year = 20;
    HAL_RTC_SetDate(&RTC_Handle,&RTC_DateConfig,RTC_FORMAT_BIN);

    RTC_AlarmConfig.Alarm = RTC_ALARM_A;
    RTC_AlarmConfig.AlarmDateWeekDay = 10;
    RTC_AlarmConfig.AlarmTime.TimeFormat = RTC_HOURFORMAT_24;

    StatesRTC = IDLE;
}

void ClockTask( void ){
    switch (StatesRTC)
    {
        case IDLE:
            if((HAL_GetTick()-timetick)>= 1000){
                timetick = HAL_GetTick();
                StatesRTC = Mostrar;
            }
            else if(Button == 1U){
                StatesRTC = MostrarAlarma;
            }
            else if(Alarm == 1U){
                StatesRTC = ActivarAlarma;
            }
            else if(InfoGeneral.msg_Type != NONE){
                StatesRTC = RTCConfig;
            }
            break;
        
        case Mostrar:
            HAL_RTC_GetTime(&RTC_Handle,&RTC_TImeConfig,RTC_FORMAT_BIN);
            HAL_RTC_GetDate(&RTC_Handle,&RTC_DateConfig,RTC_FORMAT_BIN);
            printf("Hora: %02d:%02d:%02d\n", RTC_TImeConfig.Hours, RTC_TImeConfig.Minutes, RTC_TImeConfig.Seconds);
            printf("Fecha: %02d/%02d/20 %02d\n", RTC_DateConfig.Date, RTC_DateConfig.Month, RTC_DateConfig.Year);
            StatesRTC = IDLE;
            break;

        case ActivarAlarma:

            break;

        case MostrarAlarma:
            HAL_RTC_GetAlarm(&RTC_Handle,&RTC_AlarmConfig,RTC_ALARM_A,RTC_FORMAT_BIN);
            printf("Hora de Alarma: %02d:%02d\n", RTC_AlarmConfig.AlarmTime.Hours, RTC_AlarmConfig.AlarmTime.Minutes);
            if(Button == 0U){
                StatesRTC = IDLE;
            }
            break;

        case RTCConfig:
            if (InfoGeneral.msg_Type == TIME){
                InfoGeneral.msg_Type = NONE;
                RTC_TImeConfig.Hours = InfoGeneral.Hour_Day;
                RTC_TImeConfig.Minutes = InfoGeneral.Min_Month;
                RTC_TImeConfig.Seconds = InfoGeneral.Sec_Year;
                HAL_RTC_SetTime(&RTC_Handle,&RTC_TImeConfig,RTC_FORMAT_BIN);
            }
            else if(InfoGeneral.msg_Type == DATE){
                InfoGeneral.msg_Type = NONE;
                RTC_DateConfig.Date = InfoGeneral.Hour_Day;
                RTC_DateConfig.Month = InfoGeneral.Min_Month;
                RTC_DateConfig.Year = InfoGeneral.Sec_Year;
                HAL_RTC_SetDate(&RTC_Handle,&RTC_DateConfig,RTC_FORMAT_BIN);
            }
            else if(InfoGeneral.msg_Type == ALARM){
                InfoGeneral.msg_Type = NONE;
                RTC_AlarmConfig.AlarmTime.Hours = InfoGeneral.Hour_Day;
                RTC_AlarmConfig.AlarmTime.Minutes = InfoGeneral.Min_Month;
                RTC_AlarmConfig.AlarmDateWeekDay = RTC_DateConfig.Date;
                HAL_RTC_SetAlarm(&RTC_Handle,&RTC_AlarmConfig,RTC_FORMAT_BIN);
            }
            else{
                StatesRTC = IDLE;
            }
            break;

        default:
            break;
    }
}
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
    Button = !Button;
}

void HAL_RTC_AlarmAEventCallback(RTC_HandleTypeDef *hrtc){
    Alarm = 1;
}