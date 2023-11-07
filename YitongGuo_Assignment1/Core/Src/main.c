/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "lcd.h"
#include "string.h"
#include <ctype.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
typedef struct {
    char character;
    char code[10];
} HuffmanCode;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
extern int Mode;
char decoded_error_buffer[24]={'\0'};
char encoded_error_buffer[24]={'\0'};
extern char binaryInput[9];
int exist=0;
extern char character_input[100];
char encoded_output[100]={'\0'};
extern char input_huffman_code[100];
char decoded_output[100]={'\0'};
/* USER CODE BEGIN PV */
HuffmanCode encodingTable[] = {
    {'A', "000"}, {'B', "101001"}, {'C', "00101"}, {'D', "11011"},
    {'E', "011"}, {'F', "01000"}, {'G', "001001"}, {'H', "0011"},
    {'I', "1100"}, {'J', "00100011"}, {'K', "0010000"}, {'L', "11010"},
    {'M', "01001"}, {'N', "1011"}, {'O', "1110"}, {'P', "101011"},
    {'Q', "0010001001"}, {'R', "0101"}, {'S', "1000"}, {'T', "1111"},
    {'U', "10011"}, {'V', "101000"}, {'W', "101010"}, {'X', "001000101"},
    {'Y', "10010"}, {'Z', "0010001000"}
};
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void encode(char* character_input){
	memset(encoded_output,0,sizeof(encoded_output));
    size_t length=strlen(character_input);
    int i,j=0;
    for (i = 0; i<length; ++i) {
            for (j = 0; j < sizeof(encodingTable) / sizeof(HuffmanCode); ++j) {
                if (toupper(character_input[i]) == encodingTable[j].character) {
                	strcat(encoded_output, encodingTable[j].code);
                    break;
                }
            }
//            char* error_message="Encode error:";
//            char* temp;
//            *temp=character_input[i];
//            strcpy(encoded_error_buffer,error_message);
//            strcat(encoded_error_buffer,temp);

    }
    return;
}
char decodeChar(char* code){
	for (int i = 0; i < sizeof(encodingTable) / sizeof(HuffmanCode); ++i) {
	        if (strcmp(code, encodingTable[i].code) == 0) {
	        	exist=1;
	        	//LED_0 LED_1 first blink
	        	HAL_GPIO_TogglePin(LED0_GPIO_Port, LED0_Pin);
	        	HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
	        	HAL_Delay(300);
	        	HAL_GPIO_TogglePin(LED0_GPIO_Port, LED0_Pin);
	        	HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
	        	HAL_Delay(300);
	        	//LED_0 LED_1 second blink
	        	HAL_GPIO_TogglePin(LED0_GPIO_Port, LED0_Pin);
	        	HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
	        	HAL_Delay(300);
	        	HAL_GPIO_TogglePin(LED0_GPIO_Port, LED0_Pin);
	        	HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
	            return encodingTable[i].character;
	        }
	    }
	    exist=0;
	    return '\0';  // Return null character if not found
}
void decode(char* decoded_input){
	char buffer[11];
	int i, j = 0, k = 0;
	size_t length=strlen(decoded_input);
	for (i = 0; i<length;++i) {
	        buffer[j++] = decoded_input[i];
	        buffer[j] = '\0';
	        exist=0;
	        char decodedChar = decodeChar(buffer);
	        if(exist==0){//"找不到“
	        	char* error_message="Decode error:";
	        	strcpy(decoded_error_buffer,error_message);
	        	strcat(decoded_error_buffer,buffer);
	        }
	        //找到了，要清空error_buffer以及改变j，还有加入到decoded_output中
	        else{
	        	memset(decoded_error_buffer,0,sizeof(decoded_error_buffer));
	        	j=0;
	        	decoded_output[k++]=decodedChar;
	        }
	}
	    decoded_output[k] = '\0';
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
  LCD_Init();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  BACK_COLOR = WHITE;
  POINT_COLOR = RED;
  HAL_GPIO_TogglePin(LED0_GPIO_Port, LED0_Pin);
  HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
  while (1)
  {
    /* USER CODE END WHILE */
	    // use as confirm key or mode switch key
	 	  if(HAL_GPIO_ReadPin(KEY_WK_GPIO_Port, KEY_WK_Pin)== GPIO_PIN_RESET){
	 		  if(Mode ==1){
	 			  if(strlen(character_input)>0){// confirm key
	 				  //When receiving successive 0 and 1 after pressing Confirmation key, LED0 and LED1 should blink in order
//	 				  strncat(code_ofAlpha, encode(character_input), sizeof(code_ofAlpha) - strlen(code_ofAlpha) - 1);
	 				  encode(character_input);
	 				  memset(character_input, '\0', sizeof(character_input));

	 			  }
	 			  else{//Mode switch key
	 				  Mode =0;

	 			  }
	 		  }
	 		  else if(Mode ==0){
	 			  if(strlen(input_huffman_code)>0){ //confirm key, decode character
	 				  for(int i=0;i<strlen(input_huffman_code);i++){
	 					  if(input_huffman_code[i]=='0'){
	 						  //LED_0 blink
	 						  HAL_GPIO_TogglePin(LED0_GPIO_Port, LED0_Pin);
	 						  HAL_Delay(300);
	 						  HAL_GPIO_TogglePin(LED0_GPIO_Port, LED0_Pin);
	 						  HAL_Delay(300);
	 					  }
	 					  else if(input_huffman_code[i]=='1'){
	 						  //LED_1 blink
	 						  HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
	 						  HAL_Delay(300);
	 						  HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
	 						  HAL_Delay(300);
	 					  }
	 				  }
	 				  decode(input_huffman_code);
	 				  memset(input_huffman_code, '\0', sizeof(input_huffman_code));
	 			  }
	 			  else{ //Mode switch
	 				  Mode =1;

	 			  }
	 		  }
	 		  LCD_Clear(WHITE);
	 		  if(Mode ==1){
	 			  POINT_COLOR = RED;
	 			  LCD_ShowString(10, 10, 200, 24, 24, (uint8_t*)"Encode mode");
	 			  POINT_COLOR = BLACK;
	 			  LCD_ShowString(10, 36, 90, 16, 16, (uint8_t*)"InputHex:");
	 			  LCD_ShowString(100, 36, 200, 16, 16, (uint8_t*)binaryInput);
	 			  LCD_ShowString(10, 148, 200, 16, 16, (uint8_t*)"Output:");
	 			  LCD_ShowString(80, 148, 200, 16, 16, (uint8_t*)encoded_error_buffer);
	 			  LCD_ShowString(10, 166, 200, 64, 16, (uint8_t*)encoded_output);
	 			  for(int i=0;i<strlen(encoded_output);i++){
	 				  if(encoded_output[i]=='0'){
	 					  //LED_0 blink
	 					  HAL_GPIO_TogglePin(LED0_GPIO_Port, LED0_Pin);
	 					  HAL_Delay(300);
	 					  HAL_GPIO_TogglePin(LED0_GPIO_Port, LED0_Pin);
	 					  HAL_Delay(300);
	 			 	  }
	 			 	  else if(encoded_output[i]=='1'){
	 			 	 	   //LED_1 blink
	 			 	 	  HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
	 			 	 	  HAL_Delay(300);
	 			 	 	  HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
	 			 	 	  HAL_Delay(300);
	 			 	 }

	 			 }
	 		  }
	 		  if(Mode ==0){
	 			  POINT_COLOR = RED;
	 			  LCD_ShowString(10, 10, 200, 24, 24, (uint8_t*)"Decode mode");
	 			  POINT_COLOR = BLACK;
	 			  LCD_ShowString(10, 36, 200, 16, 16, (uint8_t*)"Input:");
	 			  LCD_ShowString(10, 54, 200, 64, 16, (uint8_t*)input_huffman_code);
	 			  LCD_ShowString(10, 148, 200, 16, 16, (uint8_t*)"Output:");
	 			  LCD_ShowString(80, 148, 200, 16, 16, (uint8_t*)decoded_error_buffer);
	 			  if(exist==0){//there is one error
	 				      //LED0 on;
	 				      HAL_GPIO_TogglePin(LED0_GPIO_Port, LED0_Pin);
	 				      //first blink
	 				      HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
	 				      HAL_Delay(300);
	 				      HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
	 				      //second blink
	 				      HAL_Delay(300);
	 				      HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
	 				      HAL_Delay(300);
	 				      HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
	 				      //third blink;
	 				      HAL_Delay(300);
	 				      HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
	 				      HAL_Delay(300);
	 				      HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
	 				      //LED0 off
	 				      HAL_GPIO_TogglePin(LED0_GPIO_Port, LED0_Pin);
	 			  }
	 			  LCD_ShowString(10, 166, 200, 64, 16, (uint8_t*)decoded_output);
	 		  }
	 		  while(HAL_GPIO_ReadPin(KEY_WK_GPIO_Port, KEY_WK_Pin)== GPIO_PIN_RESET);
	 	  }
    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */

void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
