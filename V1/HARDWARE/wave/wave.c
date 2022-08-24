#include "wave.h"
#include "delay.h"

#define Trig GPIO_Pin_9
#define Echo GPIO_Pin_10

float Distance;

void Wave_SRD_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitSture;
	EXTI_InitTypeDef  EXTI_InitSture;
	NVIC_InitTypeDef  NVIC_InitSture;
	//����ⲿ�жϵĻ���һ��ʹ��AFIO���ù���
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOA,ENABLE);
	
	
	//����IO�˿�
	GPIO_InitSture.GPIO_Mode=GPIO_Mode_Out_PP;   //�������ģʽ
	GPIO_InitSture.GPIO_Pin=Trig;                //��PA9��Trig����
	GPIO_InitSture.GPIO_Speed=GPIO_Speed_50MHz;  
	GPIO_Init(GPIOA,&GPIO_InitSture);
	
	GPIO_InitSture.GPIO_Mode=GPIO_Mode_IPD;      //������ģʽ
	GPIO_InitSture.GPIO_Pin=Echo;                //��PA10��Echo����
	GPIO_InitSture.GPIO_Speed=GPIO_Speed_50MHz;  
	GPIO_Init(GPIOA,&GPIO_InitSture);
	
	//�жϺ�6�˿�ӳ��һ��
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource10);
	
	//�ⲿ�ж�����
	EXTI_InitSture.EXTI_Line=EXTI_Line10;
	EXTI_InitSture.EXTI_LineCmd=ENABLE;
	EXTI_InitSture.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitSture.EXTI_Trigger=EXTI_Trigger_Rising;
	EXTI_Init(&EXTI_InitSture);
	
}

void EXTI15_10_IRQHandler(void)
{   
	delay_us(10);		
	if(EXTI_GetITStatus(EXTI_Line10)!=RESET)
	{
		TIM_SetCounter(TIM1,0);
		TIM_Cmd(TIM1,ENABLE);
		
		while(GPIO_ReadInputDataBit(GPIOA,Echo));  //�ȴ��͵�ƽ	
		TIM_Cmd(TIM1,DISABLE);
		
		Distance=(float)(TIM_GetCounter(TIM1)*340)/200;			
		EXTI_ClearITPendingBit(EXTI_Line10);
	}
}

void Wave_SRD_Strat(void)
{
	GPIO_SetBits(GPIOA,Trig);   //��Trig����Ϊ�ߵ�ƽ
	delay_us(20);               //��������10us����������������ģ�鹤��
	GPIO_ResetBits(GPIOA,Trig); 	
}

