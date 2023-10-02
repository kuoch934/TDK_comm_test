#include "mainpp.h"
#include "ros.h"
#include "std_msgs/Int64.h"
#include "STM32Hardware.h"

int count;
std_msgs::Int64 test;


void callback(const std_msgs::Int64 &msg)
{
   count = msg.data;
}

ros::NodeHandle nh;
ros::Subscriber<std_msgs::Int64> sub("counting", callback);
ros::Publisher pub("text", &test);

void publish(){
	test.data = 1;
	pub.publish(&test);
}
/* UART Communication */
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

static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 57600;
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

void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart){
    if(huart == &huart2){
    // set velocity 0 before uart reinitialization
    	count = 0;

		HAL_UART_DeInit(&huart2);
		MX_USART2_UART_Init();
		nh.getHardware()->init();
    }
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    nh.getHardware()->flush();
}

void setup(void)
{
    nh.initNode();
    nh.subscribe(sub);
    nh.advertise(pub);
}
void loop(void)
{
    nh.spinOnce();
}




