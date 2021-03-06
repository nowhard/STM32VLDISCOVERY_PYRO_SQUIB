/**
  ******************************************************************************
  * File Name          : main.h
  * Description        : This file contains the common defines of the application
  ******************************************************************************
  *
  * Copyright (c) 2017 STMicroelectronics International N.V. 
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H
  /* Includes ------------------------------------------------------------------*/

/* USER CODE BEGIN Includes */
#define SCL_SDA_AKT_GPIO_Port GPIOB
/* USER CODE END Includes */

/* Private define ------------------------------------------------------------*/

#define SCL_AKT_Pin GPIO_PIN_10
#define SCL_AKT_GPIO_Port GPIOB
#define SDA_AKT_Pin GPIO_PIN_11
#define SDA_AKT_GPIO_Port GPIOB
#define A0_AKT_Pin GPIO_PIN_12
#define A0_AKT_GPIO_Port GPIOB
#define A1_AKT_Pin GPIO_PIN_13
#define A1_AKT_GPIO_Port GPIOB
#define A2_AKT_Pin GPIO_PIN_14
#define A2_AKT_GPIO_Port GPIOB
#define INT_AKT_Pin GPIO_PIN_15
#define INT_AKT_GPIO_Port GPIOB
#define LED_1_Pin GPIO_PIN_6
#define LED_1_GPIO_Port GPIOC
#define LED_0_Pin GPIO_PIN_7
#define LED_0_GPIO_Port GPIOC
#define LD4_Pin GPIO_PIN_8
#define LD4_GPIO_Port GPIOC
#define LD3_Pin GPIO_PIN_9
#define LD3_GPIO_Port GPIOC
#define USART1_TX_AKTIV_Pin GPIO_PIN_9
#define USART1_TX_AKTIV_GPIO_Port GPIOA
#define USART1_RX_AKTIV_Pin GPIO_PIN_10
#define USART1_RX_AKTIV_GPIO_Port GPIOA
#define TMS_SWDIO_Pin GPIO_PIN_13
#define TMS_SWDIO_GPIO_Port GPIOA
#define TCK_SWCLK_Pin GPIO_PIN_14
#define TCK_SWCLK_GPIO_Port GPIOA
#define PIR_EN8_Pin GPIO_PIN_11
#define PIR_EN8_GPIO_Port GPIOC
#define PIR_EN7_Pin GPIO_PIN_12
#define PIR_EN7_GPIO_Port GPIOC
#define PIR_EN6_Pin GPIO_PIN_2
#define PIR_EN6_GPIO_Port GPIOD
#define PIR_EN5_Pin GPIO_PIN_3
#define PIR_EN5_GPIO_Port GPIOB
#define PIR_EN4_Pin GPIO_PIN_4
#define PIR_EN4_GPIO_Port GPIOB
#define PIR_EN3_Pin GPIO_PIN_5
#define PIR_EN3_GPIO_Port GPIOB
#define PIR_EN2_Pin GPIO_PIN_6
#define PIR_EN2_GPIO_Port GPIOB
#define PIR_EN1_Pin GPIO_PIN_7
#define PIR_EN1_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

/**
  * @}
  */ 

/**
  * @}
*/ 

#endif /* __MAIN_H */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
