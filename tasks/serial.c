#include "serial.h"
/*Includes--------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
/*----------------------------------------------------*/
_msg_Serial InfoGeneral;
UART_HandleTypeDef UART_InitStructure;
/*Ptivates Variables----------------------------------*/
static uint8_t tx_flag;
static uint8_t rx_flag;
static uint8_t Rx_T_Buffer;
static char Rx_Buffer[SerialBuffer];
static char Info_Buffer[SerialBuffer];

const char AT_TIME[] = "AT+TIME";
const char AT_DATE[] = "AT+DATE";
const char AT_ALARM[] = "AT+ALARM";

const char AT_Error[ ] = "\r\nERROR\r\n";
const char AT_Ok[ ]    = "\r\nOK\r\n";

/*----------------------------------------------------*/

void SerialInit(void){
    
    UART_InitStructure.Instance = USART2;
    UART_InitStructure.Init.BaudRate = 9600;
    UART_InitStructure.Init.WordLength = UART_WORDLENGTH_8B;
    UART_InitStructure.Init.StopBits = UART_STOPBITS_1;
    UART_InitStructure.Init.Parity = UART_PARITY_NONE;
    UART_InitStructure.Init.Mode = UART_MODE_TX_RX;
    UART_InitStructure.Init.OverSampling = UART_OVERSAMPLING_16;
    UART_InitStructure.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    
    HAL_UART_Init(&UART_InitStructure);
    HAL_NVIC_EnableIRQ(USART2_IRQn);
    HAL_NVIC_SetPriority(USART2_IRQn,NVIC_PRIORITY_HIGHEST,0);

    HAL_UART_Receive_IT(&UART_InitStructure,&Rx_T_Buffer,1U);
    InfoGeneral.msg_Type = NONE;
    tx_flag = SET;
    
}

void SerialTask(void){
    uint32_t hh,mm,ss,dd;
    uint32_t yyyy;
    char *AT_comand, *params;
    static uint8_t state = Serial_IDLE;

    switch (state){
        case Serial_IDLE:
            if(rx_flag == SET){
                rx_flag = RESET;
                strcpy(Info_Buffer, Rx_Buffer);
                state = Serial_AT;
            }
        break;
        case Serial_AT:
            AT_comand = strtok(Info_Buffer, "=");
            if (strcmp(AT_comand, AT_TIME) == 0U){
                state = Serial_TIME;
            }
            else if(strcmp(AT_comand, (const char *)"AT+DATE") == 0U){
                state = Serial_DATE;
            }
            else if(strcmp(AT_comand, (const char *)"AT+ALARM") == 0U){
                state = Serial_ALARM;
            }
            else{
                state = Serial_ERROR;
            }
        break;
        case Serial_TIME:
            params = strtok(NULL,",");
            hh = strtoint(params);
            params = strtok(NULL, ",");
            mm = strtoint(params);
            params = strtok(NULL, ",");
            ss = strtoint(params);
            if (TestOfDataTime(hh,mm,ss)){
                InfoGeneral.msg_Type = TIME;
                InfoGeneral.Hour_Day = hh;
                InfoGeneral.Min_Month = mm;
                InfoGeneral.Sec_Year = ss;
                state = Serial_OK;
            }else{
                state = Serial_ERROR;
            }
            
        break;
        case Serial_DATE:
            params = strtok(NULL,",");
            dd = strtoint(params);
            params = strtok(NULL, ",");
            mm = strtoint(params);
            params = strtok(NULL, ",");
            yyyy = strtoint(params);
            if(TestOfDataDate(dd,mm,yyyy)){
                InfoGeneral.msg_Type = DATE;
                InfoGeneral.Hour_Day = dd;
                InfoGeneral.Min_Month = mm;
                InfoGeneral.Sec_Year = yyyy;
                state = Serial_OK;
            }else{
                state = Serial_ERROR;
            }
        break;
        case Serial_ALARM:
            params = strtok(NULL,",");
            hh = strtoint(params);
            params = strtok(NULL, ",");
            mm = strtoint(params);
            if (TestOfDataTime(hh,mm,0U)){
                InfoGeneral.msg_Type = TIME;
                InfoGeneral.Hour_Day = hh;
                InfoGeneral.Min_Month = mm;
                InfoGeneral.Sec_Year = 0U;
                state = Serial_OK;
            }else{
                state = Serial_ERROR;
            }
        break;
        case Serial_ERROR:
            if (tx_flag == SET){
                tx_flag = RESET;
                HAL_UART_Transmit_IT(&UART_InitStructure,(uint8_t *)AT_Error,sizeof(AT_Error)-1U);
                state = Serial_IDLE;
            }
        break;
        case Serial_OK:
            if (tx_flag == SET){
                tx_flag = RESET;
                HAL_UART_Transmit_IT(&UART_InitStructure,(uint8_t *)AT_Ok,sizeof(AT_Ok)-1U);
                state = Serial_IDLE;
            }
        break;
    }

}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
    static uint8_t i = 0U;

    if (i == SerialBuffer){
        Rx_T_Buffer = '\r';
    }
    if ((Rx_T_Buffer == '\r') && (i > 0U)){
        Rx_Buffer[i] = '\0';
        rx_flag = SET;
        i = 0U;
    }
    else if(isprint(Rx_T_Buffer)){
        Rx_Buffer[i] = (char)Rx_T_Buffer;
        i++;
    }
    HAL_UART_Receive_IT(huart,&Rx_T_Buffer,1U);
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart){
    tx_flag = SET;
}

uint32_t strtoint(char * str){
    uint32_t number = 6666U;
    uint32_t counter = 0;
    if (str != NULL){
        while ( isdigit( *str) ){
            counter++;
            str++;
        }
        if (counter == strlen(str)){
            number = atoi(str);
        }   
    }
    return number;
}

uint8_t TestOfDataTime(uint32_t hh, uint32_t mm, uint32_t ss){
    uint8_t Sample = 0U;
    if((hh < 24U) && (mm < 60U) && (ss < 60U)){
        Sample = 1U;
    }
    return Sample;
}

uint8_t TestOfDataDate(uint32_t dd, uint32_t mm, uint32_t yyyy){
    uint8_t Sample = 0U;
    if((dd < 30U) && (mm < 13U) && (yyyy < 9999U)){
        Sample = 1U;
    }
    return Sample;
}