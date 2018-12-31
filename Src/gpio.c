/**
  ******************************************************************************
  * File Name          : gpio.c
  * Description        : This file provides code for the configuration
  *                      of all used GPIO pins.
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
#include "gpio.h"
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */
//�����ɿ�����־λ
GPIO_PinState lastbutton_1 = GPIO_PIN_SET;
GPIO_PinState lastbutton_2 = GPIO_PIN_SET;
GPIO_PinState lastbutton_3 = GPIO_PIN_SET;
GPIO_PinState lastbutton_4 = GPIO_PIN_SET;
GPIO_PinState lastbutton_9 = GPIO_PIN_SET;
GPIO_PinState lastbutton_12 = GPIO_PIN_SET;

int exit_state = 0;
/* USER CODE END 1 */

/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|NRF_CE_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(NRF_CS_GPIO_Port, NRF_CS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : PC0 PC6 PC7 PC9 
                           PC10 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_9 
                          |GPIO_PIN_10;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PC1 PC2 PC3 PC4 
                           PC5 PC8 */
  GPIO_InitStruct.Pin = GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4 
                          |GPIO_PIN_5|GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PB0 PBPin */
  GPIO_InitStruct.Pin = GPIO_PIN_0|NRF_CE_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = NRF_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(NRF_CS_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PC11 */
  GPIO_InitStruct.Pin = GPIO_PIN_11;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = NRF_IRQ_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(NRF_IRQ_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI1_IRQn);

  HAL_NVIC_SetPriority(EXTI2_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI2_IRQn);

  HAL_NVIC_SetPriority(EXTI3_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI3_IRQn);

  HAL_NVIC_SetPriority(EXTI4_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI4_IRQn);

  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

}

/* USER CODE BEGIN 2 */
//������ס�������ƺ���
//���������½��ص��жϻ���Ϊ������������ʧ�����⣬��˱�����ʹ�ñ�־λ
//��ס��һ�ε�pin״̬���ֶ��ж������غ��½��أ�ȷ��������ȫ��
void gpio_delayed_button_ctrl(GPIO_PinState *last, GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, char* str1, char* str2)
{
    if(*last == GPIO_PIN_RESET && HAL_GPIO_ReadPin(GPIOx,GPIO_Pin) == GPIO_PIN_SET)
      {
          can_send_msg(325, str1,3);
          nrf_send(str1,3);
          *last = GPIO_PIN_SET;
      }
      else if(*last == GPIO_PIN_SET && HAL_GPIO_ReadPin(GPIOx,GPIO_Pin) == GPIO_PIN_RESET)
      {
          can_send_msg(325, str2,3);
          nrf_send(str2,3);
          *last = GPIO_PIN_RESET;      
      }
}

//��Ӱ����������ƺ��������������main�����
void gpio_delayed_button()
{
    //gpio_delayed_button_ctrl(&lastbutton_1, GPIOC, GPIO_PIN_6, "fe", "fb");
    gpio_delayed_button_ctrl(&lastbutton_2, GPIOC, GPIO_PIN_5, "lre", "lrb");
    gpio_delayed_button_ctrl(&lastbutton_3, GPIOC, GPIO_PIN_4, "rre", "rrb");
    //gpio_delayed_button_ctrl(&lastbutton_4, GPIOC, GPIO_PIN_9, "re", "rb");
    //gpio_delayed_button_ctrl(&lastbutton_9, GPIOC, GPIO_PIN_11, "tle", "tlb");
    gpio_delayed_button_ctrl(&lastbutton_12, GPIOC, GPIO_PIN_0, "tre", "trb");
}

void exit_button()
{
    switch(exit_state)
    {
    case 1:
        nrf_send("0",1);
        exit_state = 0;
        break;
    case 2:
        nrf_send("1",1);
        exit_state = 0;
        break;
    case 3:
        nrf_send("4",1);
        exit_state = 0;
        break;
    case 4:
        nrf_send("3",1);
        exit_state = 0;
        break;
    case 5:
        nrf_send("2",1);
        exit_state = 0;
        break;
        
    }
}

//�ⲿ�жϵ�callback��PIN_x��Ӧÿһ����������������
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if(GPIO_Pin == GPIO_PIN_1)
  {
      //can_send_msg(325, "0",1);
      exit_state = 1;
  }
  else if(GPIO_Pin == GPIO_PIN_2)
  {
     // can_send_msg(325, "1",1);
        exit_state = 2;
  }
  else if(GPIO_Pin == GPIO_PIN_3)
  {
     // can_send_msg(325, "4",1);
    exit_state = 3;
  }
  else if(GPIO_Pin == GPIO_PIN_4)
  {
      //can_send_msg(325, "3",1);
    //exit_state = 4;
  }
  else if(GPIO_Pin == GPIO_PIN_5)
  {
      //can_send_msg(325, "2",1);
    //exit_state = 5;
  }       
  __HAL_GPIO_EXTI_CLEAR_IT(GPIO_Pin);
}
/* USER CODE END 2 */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
