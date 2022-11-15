/****************
1、串口时钟、GPIOA时钟使能
2、GPIOA端口模式设置
3、串口参数初始化
4、开启中断并且初始化NVIC
5、使能串口
6、编写中断处理函数
******************/
#include "sys.h"  //包含需要的头文件

void My_USART1(void)
{
	
	GPIO_InitTypeDef GPIO_InitStruct;
	USART_InitTypeDef USART1_InitStrue;
	//1、串口时钟、GPIOA时钟使能
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_USART1, ENABLE);
	
	//2、GPIOA端口模式设置
	GPIO_InitStruct.GPIO_Pin = USART1_GPIO_PIN_TX;//PA9
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = USART1_GPIO_PIN_RX;//PA10
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	//GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_Init(GPIOA, &GPIO_InitStruct);	
	
	//3、串口参数初始化
	
	USART1_InitStrue.USART_BaudRate = 9600;
	USART1_InitStrue.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART1_InitStrue.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;
	USART1_InitStrue.USART_Parity = USART_Parity_No;
	USART1_InitStrue.USART_StopBits=USART_StopBits_1;
	USART1_InitStrue.USART_WordLength = USART_WordLength_8b;
	
	USART_Init( USART1, &USART1_InitStrue);
	//4、开启中断并且初始化NVIC
	
	
	//5、使能串口
	USART_Cmd(USART1,ENABLE);
	
	//6、编写中断处理函数	
	
}

void USART_SendByte(USART_TypeDef* USARTx, uint16_t Data)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_DATA(Data)); 
    
  /* Transmit Data */
  USARTx->DR = (Data & (uint16_t)0x01FF);
  while (USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET);

}

void USART_SendString( USART_TypeDef * USARTx, char *str)
{
     while(*str!='\0')
     {
         USART_SendByte( USARTx, *str++ );	
     }
     while(USART_GetFlagStatus(USARTx,USART_FLAG_TC)==RESET);
}


