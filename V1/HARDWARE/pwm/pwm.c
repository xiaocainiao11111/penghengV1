#include "pwm.h"

void PWM_Init_TIM3(u16 arr,u16 psc) //��ʼ�������֡��˶����pwm�������
{		 	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_OCInitTypeDef TIM_OCInitStruct;
	GPIO_InitTypeDef GPIOA_InitStruct;
    GPIO_InitTypeDef GPIOB_InitStruct;    

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);   //ʹ�ܶ�ʱ��3ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB,ENABLE);  //ʹ��GPIOB��ʱ��

	GPIOA_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;          //�������
	GPIOA_InitStruct.GPIO_Pin = GPIO_Pin_7;                //PA7
	GPIOA_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIOA_InitStruct);
    
    GPIOB_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;          //�������
	GPIOB_InitStruct.GPIO_Pin = GPIO_Pin_0;                //PB0
	GPIOB_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIOB_InitStruct);

	TIM_TimeBaseInitStruct.TIM_Period = arr;              //�趨�������Զ���װֵ 
	TIM_TimeBaseInitStruct.TIM_Prescaler  = psc;          //�趨Ԥ��Ƶ��
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;//TIM���ϼ���ģʽ
	TIM_TimeBaseInitStruct.TIM_ClockDivision = 0;         //����ʱ�ӷָ�
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStruct);       //��ʼ����ʱ��

	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;             //ѡ��PWM1ģʽ
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStruct.TIM_Pulse = 0;                            //���ô�װ�벶��ȽϼĴ���������ֵ
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_Low;      //�����������
	TIM_OC2Init(TIM3,&TIM_OCInitStruct);                       //��ʼ������Ƚϲ���
    TIM_OC3Init(TIM3,&TIM_OCInitStruct);                       //��ʼ������Ƚϲ���
	TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable);   //CH2ʹ��Ԥװ�ؼĴ���
    TIM_OC3PreloadConfig(TIM3,TIM_OCPreload_Enable);   //CH2ʹ��Ԥװ�ؼĴ���
	TIM_ARRPreloadConfig(TIM3, ENABLE);                //ʹ��TIM1��ARR�ϵ�Ԥװ�ؼĴ���

	TIM_Cmd(TIM3,ENABLE);                              //ʹ�ܶ�ʱ��3
} 

void PWM_Init_TIM2(u16 arr, u16 psc)//��ʼ�����pwm�������
{
	GPIO_InitTypeDef GPIO_InitStructure; //����һ�����ų�ʼ���Ľṹ��
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStrue; //����һ����ʱ�жϵĽṹ��	
	TIM_OCInitTypeDef TIM_OCInitTypeStrue; //����һ��PWM����Ľṹ��
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); //ʹ��GPIOAʱ�ӣ���STM32��ʹ��IO��ǰ��Ҫʹ�ܶ�Ӧʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //ʹ��ͨ�ö�ʱ��2ʱ�ӣ�A0���Ŷ�ӦTIM2CHN1
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;//����0
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP; //�����������ģʽ����ʱ������ΪA0���Ÿ��ù���
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz; //�������������ٶ�Ϊ50MHZ
    GPIO_Init(GPIOA, &GPIO_InitStructure); //��ʼ������GPIOA0
	 
	TIM_TimeBaseInitStrue.TIM_Period=arr; //����ģʽΪ���ϼ���ʱ����ʱ����0��ʼ����������������arrʱ������ʱ�жϷ�����
	TIM_TimeBaseInitStrue.TIM_Prescaler=psc; //Ԥ��Ƶϵ��������ÿһ��������ʱ��
	TIM_TimeBaseInitStrue.TIM_CounterMode=TIM_CounterMode_Up; //����ģʽ�����ϼ���
	TIM_TimeBaseInitStrue.TIM_ClockDivision=0; //һ�㲻ʹ�ã�Ĭ��TIM_CKD_DIV1
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStrue); //����TIM_TimeBaseInitStrue�Ĳ�����ʼ����ʱ��TIM2
	
	TIM_OCInitTypeStrue.TIM_OCMode=TIM_OCMode_PWM1; //PWMģʽ1������ʱ������С��TIM_Pulseʱ����ʱ����ӦIO�����Ч��ƽ
	TIM_OCInitTypeStrue.TIM_OCPolarity=TIM_OCNPolarity_High; //�����Ч��ƽΪ�ߵ�ƽ
	TIM_OCInitTypeStrue.TIM_OutputState=TIM_OutputState_Enable; //ʹ��PWM���
	TIM_OCInitTypeStrue.TIM_Pulse = 0; //���ô�װ�벶��ȽϼĴ���������ֵ
	TIM_OC1Init(TIM2, &TIM_OCInitTypeStrue); //��TIM_OCInitTypeStrue������ʼ����ʱ��2ͨ��1

	TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Disable); //CH1Ԥװ��ʹ��
	
	TIM_ARRPreloadConfig(TIM2, ENABLE); //CH1Ԥװ��ʹ��
	
    //TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE); //ʹ��TIM2�жϣ��ж�ģʽΪ�����жϣ�TIM_IT_Update
    
	TIM_Cmd(TIM2, ENABLE); //ʹ�ܶ�ʱ��TIM2
}
void Init_TIM1(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef    TIM_TimeBaseInitSture;
	NVIC_InitTypeDef           NVIC_InitSture;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);//ʹ��TIM3
	
	//��ʼ����ʱ��
	TIM_TimeBaseInitSture.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitSture.TIM_Period=arr;
	TIM_TimeBaseInitSture.TIM_Prescaler=psc;
	TIM_TimeBaseInitSture.TIM_ClockDivision=0;
	TIM_TimeBaseInit(TIM1,&TIM_TimeBaseInitSture);
	
	//��������жϣ�������ʽ�ж�
	TIM_ITConfig(TIM1,TIM_IT_Update,ENABLE);
	TIM_ITConfig(TIM1,TIM_IT_Trigger,ENABLE);
		
	//TIM_Cmd(TIM1,ENABLE);
}

void TIM1_UP_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM1,TIM_IT_Update)!=RESET)
	{
		TIM_ClearITPendingBit(TIM1,TIM_IT_Update);
		
	}
}

void TIM2_IRQHandler()
{   
    static int count=0;
    if(TIM_GetITStatus(TIM2, TIM_IT_Update)==1) //�������ж�ʱ״̬�Ĵ���(TIMx_SR)��bit0�ᱻӲ����1
	{
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update); //״̬�Ĵ���(TIMx_SR)��bit0��0
        count++;      
        if(Distance<8)
        {
            Beep=1,Led1=0,Led2=0;
            Backward();
            TIM_SetCompare1(TIM2, 790);//�����λ
        }
        else Beep=0;
        if(count==25)
        {
            Stopped();count=0;           
        }            
	}
}



