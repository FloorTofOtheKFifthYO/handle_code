
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2018 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4xx_hal.h"
#include "adc.h"
#include "can.h"
#include "dma.h"
#include "spi.h"
#include "usart.h"
#include "gpio.h"
#include "fsmc.h"

/* USER CODE BEGIN Includes */
#include <assert.h>
#include "nrf24l01.h"
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */
void TEST_FUNC(CanRxMsgTypeDef* pRxMsg);
void TEST_FUNC2(CanRxMsgTypeDef* pRxMsg);
void adc_exe();
int main_flag = 0;
uint32_t ADC_Value[150];

int adc_flag = 0;
//NRF_Dev NRF24l01;
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  *
  * @retval None
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

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
  MX_DMA_Init();
  MX_USART1_UART_Init();
  MX_CAN1_Init();
  MX_ADC1_Init();
  MX_FSMC_Init();
  MX_SPI3_Init();
  /* USER CODE BEGIN 2 */
  can_init();
  can_add_callback(325, TEST_FUNC);
  can_add_callback(324, TEST_FUNC2);
  //can_send_msg(325, "hello",6);
  //HAL_ADC_Start_DMA(&hadc1, (uint32_t*)&ADC_Value, 100);
  HAL_ADC_Start_DMA(&hadc1, (uint32_t*)&ADC_Value, 150);

  NRF_Init(&NRF24l01);
  main_flag = 1;
  uprintf("start...\r\n");
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */
      //nrf_send("hellworl",8);
     /* char str[13] = {'\0'} ;
      strcpy(str,"helloworld");
      add_crc_check((unsigned char *)str, 11);
      NRF24l01.tx_data = str;
      NRF24l01.tx_len = 13;
      nrf_send_message(&NRF24l01);
      HAL_Delay(20);*/
      
      
      adc_exe();
      exit_button();
      gpio_delayed_button();
      //nrf_send("helloo",6);
  }
  /* USER CODE END 3 */

}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

    /**Configure the main internal regulator output voltage 
    */
  __HAL_RCC_PWR_CLK_ENABLE();

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* USER CODE BEGIN 4 */
//can���жϽ��մ�����
void TEST_FUNC(CanRxMsgTypeDef* pRxMsg)
{
    uint8_t Data[8];
    int i;
    for(i = 0; i < 8; i++)
    {
        Data[i] = pRxMsg->Data[i];
    }
    uprintf("%s\r\n",Data);  
}

void TEST_FUNC2(CanRxMsgTypeDef* pRxMsg)
{
    uint8_t Data[6];
    int i;
    for(i = 0; i < 6; i++)
    {
        Data[i] = pRxMsg->Data[i];
    }
    uprintf("%d %d %d\r\n",Data[0]*128 + Data[1], Data[2]*128 + Data[3], Data[4]*128 + Data[5]);
}

void adc_exe()
{
    if(adc_flag == 0) return;
    uint32_t ad[3] = {0};
    for(int i = 0; i < 150;)
            {//yzx
            ad[0] += ADC_Value[i++];
            ad[1] += ADC_Value[i++];
            ad[2] += ADC_Value[i++];
            }/*
            uint32_t ad1 = 0, ad2 = 0;
            for(int i = 0; i < 100;)
            {  
                ad1 += ADC_Value[i++];
                ad2 += ADC_Value[i++];
            }
            ad1 /= 50;
            ad2 /= 50;
            ad1 /= 16;
            ad2 /= 16;*/
        //data��0��5�ֱ���ad1��λ��λ��ad2��λ��λ��ad3��λ��λ
        uint8_t adc_data[7];
        adc_data[0] = 'R';
        
        for(int i = 0; i <= 2; i++)
        {
            ad[i] /= 50;
            ad[i] /= 16;
            adc_data[2*i + 1 + 1] = ad[i] % 128;
            adc_data[2*i + 1] = ad[i] / 128;
        }
        /*
        for(int i = 2; i >= 0; i--)
        {
            data[i] = '0' + ad1 % 10;
            ad1 /= 10;
            data[i + 3] = '0' + ad2 % 10;
            ad2 /= 10;
        }*/
        
        //can_send_msg(324,data,6);//ҡ��id324
        nrf_send(adc_data,7);
    adc_flag = 0;
}

void HAL_SYSTICK_Callback(void){
    static int time_1ms_cnt = 0;
    if(main_flag == 1)
    {
        time_1ms_cnt++;
        
        if(time_1ms_cnt % 50 == 0)
        {
            adc_flag = 1;  
        }
        if(time_1ms_cnt >= 65530)
        {
            time_1ms_cnt = 0;
        }
    }  
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  file: The file name as string.
  * @param  line: The line in file as a number.
  * @retval None
  */
void _Error_Handler(char *file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1)
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
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
