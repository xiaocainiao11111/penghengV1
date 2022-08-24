#include "motor.h"
static int turn=790;

void MOTOR_1_Init(void)//��ʼ�������ֵ������������������ת������
{
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);  //ʹ��GPIOB��ʱ��

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;         //�������
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9;   //PB8 PB9
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruct);
}

void MOTOR_2_Init(void)//��ʼ���˶��������������ת������
{
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);  //ʹ��GPIOB��ʱ��

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;         //�������
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6;   //PA5 PA6
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
}



/*�޷�����*/
void Limit(int *pwm)
{
	if(*pwm>PWM_MAX)*pwm=PWM_MAX;
	if(*pwm<PWM_MIN)*pwm=PWM_MIN;
}

/*��ֵ����*/
/*��ڲ�����PID������ɺ������PWMֵ*/
/*����abs�������ֵ*/
void Load(int pwm)
{
	//1.�о������ţ���Ӧ����ת
	if(pwm>0)   EN=1,DIR=1;//��ת
	else        EN=1,DIR=0;//��ת
	//2.�о�PWMֵ
	TIM_SetCompare2(TIM3,abs(pwm));
}

void Stop(float *Med_Jiaodu,float *Jiaodu)
{   
//    if(*Jiaodu>5)Led1=1,Led2=0;
//    if(*Jiaodu<(-10))Led1=0,Led2=1;
	if(abs(*Jiaodu-*Med_Jiaodu)>12)Load(0);
}

/*�˶�������ƺ���*/
void Forward(void)
{
    Ain1=0,Ain2=1;
    TIM_SetCompare3(TIM3,3500);
}

void Backward(void)
{
    Ain1=1,Ain2=0;
    TIM_SetCompare3(TIM3,3500);
}

void Stopped(void)
{
    Ain1=0,Ain2=0;
}


void Right(void)
{
    turn+=25;
    if(turn>1000)turn=1000;
    TIM_SetCompare1(TIM2, turn);
}

void Left(void)
{
    turn-=25;
    if(turn<580)turn=580;
    TIM_SetCompare1(TIM2, turn);
}

void Goright(void)
{
    turn+=25;
    if(turn>1000)turn=1000;
    TIM_SetCompare1(TIM2, turn);
    Forward();
}

void Goleft(void)
{
    turn-=25;
	if(turn<580)turn=580;
    TIM_SetCompare1(TIM2, turn);
    Forward();
}


