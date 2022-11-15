#include "sys.h"

int main(void)
{
		LED_GPIO_Config();
		delay_init();
		//KEY_GPIO_Config();
		//TIM2_Init(4999,7199);
	    My_USART1();

		while(1)			
		{
	    USART_SendString(USART1, "Hello World£¡");
		delay_ms(500);
		
		};
}
