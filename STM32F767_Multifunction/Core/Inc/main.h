/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "features.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */
#define ADC_BUFFER_SIZE 32
#define USART1_BUFFER_SIZE  64

#define USART2_BUFFER_SIZE 4  // sizeof(float)

#define SPI_CS_Pin        GPIO_PIN_10
#define SPI_CS_GPIO_Port  GPIOG


typedef struct{
	uint16_t rawValue;
	float voltage;
} ADC_Data;

typedef struct {
    uint8_t rxBuffer[USART1_BUFFER_SIZE];
    volatile uint16_t rxIndex;
    volatile bool dataReady;
    volatile bool errorFlag;
} USART1_Data;

typedef struct {
    uint16_t targetDuty;    // Requested duty (0-1024)
    uint16_t currentDuty;   // Active duty (for safety checks)
    bool pwmEnabled;        // Emergency disable flag
} PWM_Control;

typedef struct {
    volatile bool overflowActive;  // True when (ADC+USART) > 1024
    volatile uint32_t lastToggleTime;  // For debounce
} Overflow_Control;

typedef enum {
    PROTOCOL_I2C,
    PROTOCOL_SPI
} CommProtocol;

typedef struct {
    //volatile bool buttonPressed;     // True if button active (low)
	bool buttonPressed;
    CommProtocol currentProtocol;   // I2C or SPI
    uint16_t dataToSend;            // ADC + USART value
    bool transmissionDone;          // Flag for completion
} Transmission_Control;

typedef struct {
    uint8_t rxBuffer[USART2_BUFFER_SIZE];
    volatile bool dataReady;
    volatile bool watchdogTrigger;
    float receivedFloat;
} USART2_Control;

typedef struct {
    uint16_t rawValue;      // ADC value + offset
    float voltage;          // Calculated voltage
    bool overvoltageFault;  // AWD trigger flag
} DAC_Control;

extern ADC_Data adcData;
extern uint16_t adcBUFFER[ADC_BUFFER_SIZE];

extern USART1_Data usart1Data;

extern PWM_Control pwmControl;

extern Overflow_Control overflowCtrl;

extern Transmission_Control txCtrl;

extern USART2_Control usart2Ctrl;

extern DAC_Control dacCtrl;

extern DAC_HandleTypeDef hdac;

extern uint16_t adcBuffer[ADC_BUFFER_SIZE];
/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc);

void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart);

void Process_USART1_Data(void);

uint16_t Parse_USART1_Data(void);

void PWM_Init(void);

void PWM_UpdateDuty(uint16_t combinedValue);

void TIM3_Init(void);

void TIM4_Init(void);

void Comm_Init(void);

void Transmit_Data_Protocol(uint16_t data);

void USART2_Init(void);

void Process_USART2_Data(void);

void Update_Timer_Interval(float ms);

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);

void Send_ADC_Hex(uint16_t adcValue);

void DAC_Init(void);

void Update_DAC_Output(uint16_t adcValue);

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define USER_Btn_Pin GPIO_PIN_13
#define USER_Btn_GPIO_Port GPIOC
#define USER_Btn_EXTI_IRQn EXTI15_10_IRQn
#define MCO_Pin GPIO_PIN_0
#define MCO_GPIO_Port GPIOH
#define RMII_MDC_Pin GPIO_PIN_1
#define RMII_MDC_GPIO_Port GPIOC
#define RMII_REF_CLK_Pin GPIO_PIN_1
#define RMII_REF_CLK_GPIO_Port GPIOA
#define RMII_MDIO_Pin GPIO_PIN_2
#define RMII_MDIO_GPIO_Port GPIOA
#define RMII_CRS_DV_Pin GPIO_PIN_7
#define RMII_CRS_DV_GPIO_Port GPIOA
#define RMII_RXD0_Pin GPIO_PIN_4
#define RMII_RXD0_GPIO_Port GPIOC
#define RMII_RXD1_Pin GPIO_PIN_5
#define RMII_RXD1_GPIO_Port GPIOC
#define LD1_Pin GPIO_PIN_0
#define LD1_GPIO_Port GPIOB
#define RMII_TXD1_Pin GPIO_PIN_13
#define RMII_TXD1_GPIO_Port GPIOB
#define LD3_Pin GPIO_PIN_14
#define LD3_GPIO_Port GPIOB
#define STLK_RX_Pin GPIO_PIN_8
#define STLK_RX_GPIO_Port GPIOD
#define STLK_TX_Pin GPIO_PIN_9
#define STLK_TX_GPIO_Port GPIOD
#define USB_PowerSwitchOn_Pin GPIO_PIN_6
#define USB_PowerSwitchOn_GPIO_Port GPIOG
#define USB_OverCurrent_Pin GPIO_PIN_7
#define USB_OverCurrent_GPIO_Port GPIOG
#define USB_SOF_Pin GPIO_PIN_8
#define USB_SOF_GPIO_Port GPIOA
#define USB_VBUS_Pin GPIO_PIN_9
#define USB_VBUS_GPIO_Port GPIOA
#define USB_ID_Pin GPIO_PIN_10
#define USB_ID_GPIO_Port GPIOA
#define USB_DM_Pin GPIO_PIN_11
#define USB_DM_GPIO_Port GPIOA
#define USB_DP_Pin GPIO_PIN_12
#define USB_DP_GPIO_Port GPIOA
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define RMII_TX_EN_Pin GPIO_PIN_11
#define RMII_TX_EN_GPIO_Port GPIOG
#define RMII_TXD0_Pin GPIO_PIN_13
#define RMII_TXD0_GPIO_Port GPIOG
#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB
#define LD2_Pin GPIO_PIN_7
#define LD2_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
