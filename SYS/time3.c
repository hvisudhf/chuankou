#include "sys.h"
/********************
��ʹ�ܶ�ʱ��ʱ�ӡ�
RCC_APB1PeriphClockCmd();
�� ��ʼ����ʱ��������ARR,PSC��
TIM_TimeBaseInit();
�۶�ʱ���ж����ã�ͬʱ����NVIC��
void TIM_ITConfig();
NVIC_Init();
��ʹ�ܶ�ʱ����
TIM_Cmd();
�ݱ�д�жϷ�������
TIMx_IRQHandler();
*****************/

void TIM3_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStruct;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	
	TIM_TimeBaseStructure.TIM_Period = arr;
	TIM_TimeBaseStructure.TIM_Prescaler = psc;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);
	
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
	
	NVIC_InitStruct.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	
	NVIC_Init(&NVIC_InitStruct);
	TIM_Cmd(TIM3, ENABLE);
}

void TIM3_IRQHandler(void)
{
static u8 i =0 ;
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ 
		{
			switch (i)
			{
				case 0:GPIO_ResetBits(LED_GPIO_PORT, LED_GPIO_PIN);i++;break;
				case 1:GPIO_SetBits(LED_GPIO_PORT, LED_GPIO_PIN);i=0;break;
			
			}
			
			TIM_ClearITPendingBit(TIM3, TIM_IT_Update);  //���TIMx���жϴ�����λ:TIM �ж�Դ 
			
		}

}