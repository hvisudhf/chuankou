/****************
1������ʱ�ӡ�GPIOAʱ��ʹ��
2��GPIOA�˿�ģʽ����
3�����ڲ�����ʼ��
4�������жϲ��ҳ�ʼ��NVIC
5��ʹ�ܴ���
6����д�жϴ�������
******************/
#include "sys.h"  //������Ҫ��ͷ�ļ�

void My_USART1(void)
{
	
	GPIO_InitTypeDef GPIO_InitStruct;
	USART_InitTypeDef USART1_InitStrue;
	//1������ʱ�ӡ�GPIOAʱ��ʹ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_USART1, ENABLE);
	
	//2��GPIOA�˿�ģʽ����
	GPIO_InitStruct.GPIO_Pin = USART1_GPIO_PIN_TX;//PA9
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = USART1_GPIO_PIN_RX;//PA10
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	//GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_Init(GPIOA, &GPIO_InitStruct);	
	
	//3�����ڲ�����ʼ��
	
	USART1_InitStrue.USART_BaudRate = 9600;
	USART1_InitStrue.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART1_InitStrue.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;
	USART1_InitStrue.USART_Parity = USART_Parity_No;
	USART1_InitStrue.USART_StopBits=USART_StopBits_1;
	USART1_InitStrue.USART_WordLength = USART_WordLength_8b;
	
	USART_Init( USART1, &USART1_InitStrue);
	//4�������жϲ��ҳ�ʼ��NVIC
	
	
	//5��ʹ�ܴ���
	USART_Cmd(USART1,ENABLE);
	
	//6����д�жϴ�������	
	
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

