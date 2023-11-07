/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f1xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f1xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "lcd.h"
#include "string.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
int Mode=0;
char binaryInput[9]={'\0'};
char character_input[100]={'\0'};
char input_huffman_code[100]={'\0'};
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern UART_HandleTypeDef huart1;
/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M3 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
  while (1)
  {
  }
  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Prefetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVCall_IRQn 0 */

  /* USER CODE END SVCall_IRQn 0 */
  /* USER CODE BEGIN SVCall_IRQn 1 */

  /* USER CODE END SVCall_IRQn 1 */
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F1xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f1xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles EXTI line0 interrupt.
  */
void EXTI0_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI0_IRQn 0 */

  /* USER CODE END EXTI0_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(KEY_WK_Pin);
  /* USER CODE BEGIN EXTI0_IRQn 1 */

  /* USER CODE END EXTI0_IRQn 1 */
}

/**
  * @brief This function handles EXTI line[9:5] interrupts.
  */
void EXTI9_5_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI9_5_IRQn 0 */

  /* USER CODE END EXTI9_5_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(KEY0_Pin);
  /* USER CODE BEGIN EXTI9_5_IRQn 1 */

  /* USER CODE END EXTI9_5_IRQn 1 */
}

/**
  * @brief This function handles USART1 global interrupt.
  */
void USART1_IRQHandler(void)
{
  /* USER CODE BEGIN USART1_IRQn 0 */

  /* USER CODE END USART1_IRQn 0 */
  HAL_UART_IRQHandler(&huart1);
  /* USER CODE BEGIN USART1_IRQn 1 */

  /* USER CODE END USART1_IRQn 1 */
}

/**
  * @brief This function handles EXTI line[15:10] interrupts.
  */
void EXTI15_10_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI15_10_IRQn 0 */

  /* USER CODE END EXTI15_10_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(KEY1_Pin);
  /* USER CODE BEGIN EXTI15_10_IRQn 1 */

  /* USER CODE END EXTI15_10_IRQn 1 */
}

/* USER CODE BEGIN 1 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	HAL_Delay(50);
	if(Mode ==1){
		size_t binary_length = strlen(binaryInput);
		if(binary_length ==8){
			char letter = strtol(binaryInput, NULL, 2);
			size_t character_length = strlen(character_input);
			if(character_length < sizeof(character_input) -1){
				character_input[character_length] = letter;
				character_input[character_length+1] = '\0';
				memset(binaryInput, '\0', sizeof(binaryInput));
				return;
			}
		}
	}
    switch(GPIO_Pin){
        case KEY0_Pin:
        	if(HAL_GPIO_ReadPin(KEY0_GPIO_Port, KEY0_Pin)== GPIO_PIN_RESET){
				HAL_GPIO_TogglePin(LED0_GPIO_Port, LED0_Pin);
				POINT_COLOR = BLACK;
        		if(Mode ==1){
        			size_t binary_length=strlen(binaryInput);
        			if(binary_length < sizeof(binaryInput) - 1){
        				binaryInput[binary_length] = '0'; // 在字符串末尾添加 '0'
        				binaryInput[binary_length + 1] = '\0';
        				LCD_ShowString(100, 36, 200, 16, 16, (uint8_t*)binaryInput);
        			}
        		}
        		else{
        			size_t huffman_code_length=strlen(input_huffman_code);
        			if(huffman_code_length < sizeof(input_huffman_code) - 1){
        				input_huffman_code[huffman_code_length] = '0'; // 在字符串末尾添加 '0'
        				input_huffman_code[huffman_code_length + 1] = '\0';
        				LCD_ShowString(10, 54, 200, 64, 16, (uint8_t*)input_huffman_code);
        			}
        		}
				HAL_Delay(10);
				HAL_GPIO_TogglePin(LED0_GPIO_Port, LED0_Pin);
				while(HAL_GPIO_ReadPin(KEY0_GPIO_Port, KEY0_Pin)== GPIO_PIN_RESET);
        	}
            break;

        case KEY1_Pin:
        	if(HAL_GPIO_ReadPin(KEY1_GPIO_Port, KEY1_Pin)== GPIO_PIN_RESET){
				HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
				POINT_COLOR = BLACK;
        		if(Mode ==1){
        			size_t binary_length=strlen(binaryInput);
        			if(binary_length < sizeof(binaryInput) - 1){
        				binaryInput[binary_length] = '1'; // 在字符串末尾添加 '0'
        				binaryInput[binary_length + 1] = '\0';
        				LCD_ShowString(100, 36, 200, 16, 16, (uint8_t*)binaryInput);
        			}
        		}
        		else{
        			size_t huffman_code_length=strlen(input_huffman_code);
        			if(huffman_code_length < sizeof(input_huffman_code) - 1){
        				input_huffman_code[huffman_code_length] = '1'; // 在字符串末尾添加 '0'
        				input_huffman_code[huffman_code_length + 1] = '\0';
        				LCD_ShowString(10, 54, 200, 64, 16, (uint8_t*)input_huffman_code);
        			}
        		}
				HAL_Delay(10);
				HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
				while(HAL_GPIO_ReadPin(KEY1_GPIO_Port, KEY1_Pin)== GPIO_PIN_RESET);
        	}
            break;
        case KEY_WK_Pin:
        	if(HAL_GPIO_ReadPin(KEY1_GPIO_Port, KEY1_Pin)== GPIO_PIN_RESET){

        	}
            break;
        default:
            break;
    }
}
/* USER CODE END 1 */
