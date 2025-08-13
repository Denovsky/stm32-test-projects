/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file    stm32f4xx_it.c
 * @brief   Interrupt Service Routines.
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "cmdhandler.h"
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

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/

/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M4 Processor Interruption and Exception Handlers          */
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
 * @brief This function handles Pre-fetch fault, memory access fault.
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
/* STM32F4xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f4xx.s).                    */
/******************************************************************************/

/* USER CODE BEGIN 1 */

// void UART4_IRQHandler(void)
// {

// uint32_t sr = UART4->SR;
// uint8_t RXNE_flag = sr & USART_SR_RXNE;
// uint8_t TXE_flag = sr & USART_SR_TXE;
// uint8_t IDLE_flag = sr & USART_SR_IDLE;

// if (RXNE_flag)
// {
//   UART4->DR = 'r';
//   // uint8_t d = UART4->DR;

//   // if (d == '\n')
//   // {
//   //   *(RX_data_buffer + index) = '\0';
//   //   index = 0;
//   // }
// }
// if (TXE_flag)
// {
//   UART4->DR = 't';
// }
// if (IDLE_flag)
// {
//   UART4->DR = 'c';
// }
// }

/*
По русски, мы прерыванием вызываем командный handler, который за нас по-символьно считывает uart.
Дело в том, что програмно может стоять задержка, которая будет удерживать поток в прерывании.
Чтобы избежать этого, нужно сделать вызов прервания по изменению состояния флагов SR, а уже потом считывать
*/

uint16_t RX_data_buffer_size = 10;
uint16_t index = 0;
char *RX_data_buffer = NULL;
char *TX_data_buffer = NULL;

/*----------*/
/* main command processing funcs: */
void led_handler(char **);
void help_handler(char **);
void echo_handler(char **);
/*----------*/

map_t cmds[] = {
    {"led", led_handler},
    {"help", help_handler},
    {"echo", echo_handler}};

void UART4_IRQHandler(void)
{
  uint32_t sr = UART4->SR;
  uint8_t RXNE_flag = sr & USART_SR_RXNE;
  uint8_t IDLE_flag = sr & USART_SR_IDLE;
  // uint8_t TXE_flag = sr & USART_SR_TXE;
  if (RXNE_flag)
  {
    char dr = UART4->DR;
    if (index == 0)
    {
      RX_data_buffer_size = 10;
      RX_data_buffer = malloc_(RX_data_buffer_size);
    }

    if (index >= RX_data_buffer_size)
    {
      RX_data_buffer_size += 10;
      RX_data_buffer = realloc_(RX_data_buffer, RX_data_buffer_size);
    }

    *(RX_data_buffer + index) = dr;
    index++;
    UART4->CR1 |= USART_CR1_IDLEIE; // Register is faster than RAM
  }
  if (IDLE_flag)
  {
    index = 0;
    uint8_t cmds_size = sizeof(cmds) / (sizeof(const char *) + sizeof(void (*)(char **)));
    char *main_command = getMainCommand(RX_data_buffer);
    char *sub_command = getSubCommand(RX_data_buffer);

    uint8_t isWork = 0;
    for (uint8_t i = 0; i < cmds_size; i++)
    {
      if (compareStr(cmds[i].key, main_command))
      {
        char *args[] = {"", &cmds_size, sub_command};
        isWork = 1;
        cmds[i].handler(args);
      }
    }
    if (!isWork)
    {
      TX_data_buffer = setOutput("No such command");
      // включить прерывание TXE, выключить IDLE. В TXEIE включить RXNEIE после передачи
    }
  }
}

/* USER CODE END 1 */
