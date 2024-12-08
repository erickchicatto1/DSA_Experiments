#include "main.h"

I2C_HandleTypeDef hi2c1;
TIM_HandleTypeDef htim1;
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_I2C1_Init(void);
static void MX_TIM1_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE BEGIN 0 */
#define PCA9685_ADDRESS              0x80
// Datasheet link --> https://cdn-shop.adafruit.com/datasheets/PCA9685.pdf
#define PCA9685_MODE1                0x0         // as in the datasheet page no 10/52
#define PCA9685_PRE_SCALE            0xFE        // as in the datasheet page no 13/52
#define PCA9685_LED0_ON_L            0x6         // as in the datasheet page no 10/52
#define PCA9685_MODE1_SLEEP_BIT      4    // as in the datasheet page no 14/52
#define PCA9685_MODE1_AI_BIT         5    // as in the datasheet page no 14/52
#define PCA9685_MODE1_RESTART_BIT    7    // as in the datasheet page no 14/52

#define NUM_STATES				     4
#define NUM_EVENTS      			 4

//State machine
typedef enum State{
  StateInitial,
  Tibia14,
  Tibia12,
  Tibia11,
  Tibia10
}State;

typedef enum Event{
	EventStartTibia14,
	EventStartTibia12,
	EventStartTibia11,
	EventStartTibia10,
	EventNone
}Event;

uint32_t lastTime = 0;


int USART2_write(int ch);
int __io_putchar(int ch);
void PCA9685_SetServoAngle(uint8_t Channel, float Angle);
void PCA9685_SetPWM(uint8_t Channel, uint16_t OnTime, uint16_t OffTime);
void PCA9685_Init(uint16_t frequency);
void PCA9685_SetPWMFrequency(uint16_t frequency);
void PCA9685_SetBit(uint8_t Register,uint8_t Bit, uint8_t Value);

//State Machine
State state_initial(State currentState, Event event);

// Variables globales
State currentState = StateInitial;
Event currentEvent = EventNone;

int main(void){

  HAL_Init();

  SystemClock_Config();

  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_I2C1_Init();
  MX_TIM1_Init();

  //Init the PCA Driver
  PCA9685_Init(50);

  HAL_TIM_Base_Start(&htim1);


  while (1){

	  uint32_t currentTime = __HAL_TIM_GET_COUNTER(&htim1); // Para contar

	  if(currentTime - lastTime >= 1000){
		  lastTime = currentTime;

		  currentTime = EventStartTibia14;
	  }

	  currentState = state_initial(currentState, currentEvent);
	  currentEvent = EventNone;
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
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
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

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_IC_InitTypeDef sConfigIC = {0};
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 72-1;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 0xffff - 1;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_IC_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
  sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
  sConfigIC.ICPrescaler = TIM_ICPSC_DIV1;
  sConfigIC.ICFilter = 0;
  if (HAL_TIM_IC_ConfigChannel(&htim1, &sConfigIC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LD2_Pin */
  GPIO_InitStruct.Pin = LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PC9 */
  GPIO_InitStruct.Pin = GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
//Driver PCA9685

void PCA9685_SetBit(uint8_t Register,uint8_t Bit, uint8_t Value){

	uint8_t readValue;
	HAL_StatusTypeDef status;
	uint8_t bitArray[8];

	// Read all 8 bits and set only one bit to 0/1 and write all 8 bits back
	if(HAL_I2C_Mem_Read(&hi2c1, PCA9685_ADDRESS, Register, 1, &readValue, 1, 10) != HAL_OK){
	  return;
	}

	for(uint8_t i = 0 ; i<8;i++){
		bitArray[i] = (readValue >> i) & 1; // Extraer cada bit
	}

	// Imprimir bits originales
	printf("Bits originales: \n");
	for (int i = 7; i >= 0; i--) {
		USART2_write(bitArray[i]);
	    printf("%d \n", bitArray[i]);
	}
    printf("\n");


	if(Value==0){
	  readValue &= ~(1<<Bit);
	}

	else{
	  readValue |= (1<<Bit);
	}


	// Convertir nuevamente a bits para mostrar el cambio
	for (uint8_t i = 0; i < 8; i++) {
	   bitArray[i] = (readValue >> i) & 1;
    }

	    // Imprimir bits modificados
	printf("Bits modificados: \n");
    for (int i = 7; i >= 0; i--) {
	        printf("%d \n", bitArray[i]);
	}
    printf("\n");


	status = HAL_I2C_Mem_Write(&hi2c1, PCA9685_ADDRESS, Register, 1, &readValue, 1, 10);

	if(status == HAL_OK){
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
	}
	else{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
	}

	HAL_Delay(1);

}


void PCA9685_SetPWMFrequency(uint16_t frequency){

	uint8_t prescale;

	if(frequency >= 1526){
		prescale = 0x03;
	}
	else if(frequency <= 24){
		prescale = 0xFF;
	}

	else{
		prescale = 	25000000 / (4096 * frequency);
	}
	 // prescale changes 3 to 255 for 1526Hz to 24Hz as in the datasheet page no 1/52
	 PCA9685_SetBit(PCA9685_MODE1, PCA9685_MODE1_SLEEP_BIT, 1);
	 HAL_I2C_Mem_Write(&hi2c1, PCA9685_ADDRESS, PCA9685_PRE_SCALE, 1, &prescale, 1, 10);
	 PCA9685_SetBit(PCA9685_MODE1, PCA9685_MODE1_SLEEP_BIT, 0);
	 PCA9685_SetBit(PCA9685_MODE1, PCA9685_MODE1_RESTART_BIT, 1);


}

void PCA9685_Init(uint16_t frequency){
  PCA9685_SetPWMFrequency(frequency); // 50 Hz for servo
  PCA9685_SetBit(PCA9685_MODE1, PCA9685_MODE1_AI_BIT, 1);
}

void PCA9685_SetPWM(uint8_t Channel, uint16_t OnTime, uint16_t OffTime){

	uint8_t registerAddress;
	uint8_t pwm[4];

	registerAddress = PCA9685_LED0_ON_L + (4 * Channel); // Calculate the starting address of the LED channel´s register

	pwm[0] = OnTime & 0xFF;	// Extract the lower 8 bits
	pwm[1] = OnTime>>8;     // Extract the higher 8 bits
	pwm[2] = OffTime & 0xFF;
	pwm[3] = OffTime>>8;

	HAL_I2C_Mem_Write(&hi2c1, PCA9685_ADDRESS, registerAddress, 1, pwm, 4, 10);

}


void PCA9685_SetServoAngle(uint8_t Channel, float Angle){

	float Value;
	Value =(Angle * (511.9 - 102.4) / 180.0) + 102.4;
	PCA9685_SetPWM(Channel, 0, (uint16_t)Value);


}

//Ultrasonic

//UART

int __io_putchar(int ch){
	HAL_UART_Transmit(&huart2, (uint8_t*)&ch, 1, 0xFFFF);
	return ch;
}

int USART2_write(int ch){

	while(!(USART2->SR & 0x0080)){}
	USART2->DR = (ch & 0xFF);

	return ch;
}
//For the state machine
State state_initial(State currentState, Event event){

	switch(event){

	 case EventStartTibia14:
		 //Servo Motor 14 Tibia
	     PCA9685_SetServoAngle(14, 0);
		 PCA9685_SetServoAngle(14, 36);
		 PCA9685_SetServoAngle(14, 72);
		 PCA9685_SetServoAngle(14, 108);
		 PCA9685_SetServoAngle(14, 180);
		 PCA9685_SetServoAngle(14, 0);
		 PCA9685_SetServoAngle(14, 108);
		 PCA9685_SetServoAngle(14, -90);
	  return Tibia14;

	 case EventStartTibia12:
		 //Servo Motor 12 Tibia
	     PCA9685_SetServoAngle(12, 0);
		 PCA9685_SetServoAngle(12, 36);
		 PCA9685_SetServoAngle(12, 72);
		 PCA9685_SetServoAngle(12, 108);
		 PCA9685_SetServoAngle(12, 180);
		 PCA9685_SetServoAngle(12, 0);
		 PCA9685_SetServoAngle(12, 108);
		 PCA9685_SetServoAngle(12, -90);
	 return Tibia12;

	 case EventStartTibia10:
	     PCA9685_SetServoAngle(10, 0);
		 PCA9685_SetServoAngle(10, 36);
		 PCA9685_SetServoAngle(10, 72);
		 PCA9685_SetServoAngle(10, 108);
		 PCA9685_SetServoAngle(10, 180);
		 PCA9685_SetServoAngle(10, 0);
		 PCA9685_SetServoAngle(10, 108);
		 PCA9685_SetServoAngle(10, -90);
	 return Tibia10;

	 case EventStartTibia11:
	     PCA9685_SetServoAngle(11, 0);
		 PCA9685_SetServoAngle(11, 36);
		 PCA9685_SetServoAngle(11, 72);
		 PCA9685_SetServoAngle(11, 108);
		 PCA9685_SetServoAngle(11, 180);
		 PCA9685_SetServoAngle(11, 0);
		 PCA9685_SetServoAngle(11, 108);
		 PCA9685_SetServoAngle(11, -90);
	 return Tibia11;

	 default:
		 return currentState;
	}

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
