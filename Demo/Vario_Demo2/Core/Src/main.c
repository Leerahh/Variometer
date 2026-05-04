/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stm32l4xx_nucleo_144.h"
#include <math.h>
#include <flights.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
static const Flight *flight = &CURRENT_FLIGHT;  /* selected at compile time */
static uint32_t sample_index    = 0;
static uint32_t last_sample_tick = 0;
static uint32_t last_blink_tick  = 0;
static uint32_t last_blue_tick   = 0;
static uint8_t  led_state        = 0;
static uint8_t  blue_state       = 0;
static uint8_t  red_phase = 0;   /* 0 = ON phase, 1 = OFF gap phase */
static float    current_rate_hpa = 0.0f;  /* hPa/s, negative = climb */
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void MX_GPIO_Init(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
static void LED_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();

    GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull  = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

    GPIO_InitStruct.Pin = LED1_PIN ;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = LED2_PIN | LED3_PIN;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* Start with all LEDs off */
    HAL_GPIO_WritePin(LED1_GPIO_PORT, LED1_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED3_GPIO_PORT,   LED3_PIN,   GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED2_GPIO_PORT,  LED2_PIN,  GPIO_PIN_RESET);
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
  /* USER CODE BEGIN 2 */
  MX_GPIO_Init();

  LED_Init();
      last_sample_tick = HAL_GetTick();
      last_blink_tick  = HAL_GetTick();
      last_blue_tick   = HAL_GetTick();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
/*HAL_GPIO_TogglePin(LED2_GPIO_PORT, LED2_PIN);
	  HAL_Delay(1000);*/
	  uint32_t now = HAL_GetTick();

	          /* --- 1. Advance dataset at 1 Hz --- */
	          if ((now - last_sample_tick) >= 1000u) {
	              last_sample_tick = now;

	              if (sample_index > 0) {
	                  /* pressure drops when climbing: rate negative = ascending */
	                  float delta = flight->data[sample_index]
								           - flight->data[sample_index - 1];
	                  current_rate_hpa = delta; /* hPa/s, sign retained */
	              }

	              sample_index++;
	              if (sample_index >= flight->length) {
	                  sample_index = 1;   /* loop, keep previous sample valid */
	              }
	          }

	          /* --- 2. Blue heartbeat every 500 ms --- */
	          if ((now - last_blue_tick) >= 500u) {
	              last_blue_tick = now;
	              blue_state ^= 1u;
	              HAL_GPIO_WritePin(LED2_GPIO_PORT, LED2_PIN,
	                                blue_state ? GPIO_PIN_SET : GPIO_PIN_RESET);
	          }

	          /* --- Variometer LED logic --- */
	         	  float rate = current_rate_hpa;

	         	  if (fabsf(rate) < VARIO_DEADBAND_HPA) {
	         	      /* Stable — both off, reset all blink state */
	         	      HAL_GPIO_WritePin(LED1_GPIO_PORT, LED1_PIN, GPIO_PIN_RESET);
	         	      HAL_GPIO_WritePin(LED3_GPIO_PORT,   LED3_PIN,   GPIO_PIN_RESET);
	         	      last_blink_tick = now;
	         	      led_state = 0;
	         	      red_phase = 0;

	         	  } else if (rate < 0.0f) {
	         	      /* ---- CLIMBING → green blinks, faster = faster blink ---- */
	         	      HAL_GPIO_WritePin(LED3_GPIO_PORT, LED3_PIN, GPIO_PIN_RESET);
	         	      red_phase = 0;

	         	      /* map rate to full blink period (on+off) */
	         	      float norm = -rate / CLIMB_SCALE_HPA;
	         	      if (norm > 1.0f) norm = 1.0f;
	         	      uint32_t period = (uint32_t)(LED1_BLINK_MAX_MS
	         	                      - norm * (LED1_BLINK_MAX_MS - LED1_BLINK_MIN_MS));

	         	      if ((now - last_blink_tick) >= period) {
	         	          last_blink_tick = now;
	         	          led_state ^= 1u;
	         	          HAL_GPIO_WritePin(LED1_GPIO_PORT, LED1_PIN,
	         	                            led_state ? GPIO_PIN_SET : GPIO_PIN_RESET);
	         	      }

	         	  } else {
	         	      /* ---- DESCENDING → red pulses, faster = longer ON time ---- */
	         	      HAL_GPIO_WritePin(LED1_GPIO_PORT, LED1_PIN, GPIO_PIN_RESET);
	         	      led_state = 0;

	         	      /* map rate to ON duration */
	         	      float norm = rate / CLIMB_SCALE_HPA;
	         	      if (norm > 1.0f) norm = 1.0f;
	         	      uint32_t on_ms = (uint32_t)(LED3_ON_MIN_MS
	         	                     + norm * (LED3_ON_MAX_MS - LED3_ON_MIN_MS));

	         	      if (red_phase == 0) {
	         	          /* ON phase — hold LED on for on_ms */
	         	          HAL_GPIO_WritePin(LED3_GPIO_PORT, LED3_PIN, GPIO_PIN_SET);
	         	          if ((now - last_blink_tick) >= on_ms) {
	         	              last_blink_tick = now;
	         	              red_phase = 1;   /* switch to OFF gap */
	         	              HAL_GPIO_WritePin(LED3_GPIO_PORT, LED3_PIN, GPIO_PIN_RESET);
	         	          }
	         	      } else {
	         	          /* OFF gap — always 200 ms, then back to ON */
	         	          if ((now - last_blink_tick) >= LED3_OFF_MS) {
	         	              last_blink_tick = now;
	         	              red_phase = 0;   /* back to ON phase */
	         	          }
	         	      }
	         	  }



  /* USER CODE END 3 */
}
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  LED2_GPIO_CLK_ENABLE();

  GPIO_InitStruct.Pin = LED2_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

  HAL_GPIO_Init(LED2_GPIO_PORT, &GPIO_InitStruct);
}

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
#ifdef USE_FULL_ASSERT
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
