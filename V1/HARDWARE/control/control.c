#include "control.h" 

float Med_Angle;	//��е��ֵ��---�������޸���Ļ�е��ֵ���ɡ�
float 
//	Vertical_Kp=0,//ֱ����KP��KD
//	Vertical_Kd=0;
	Vertical_Kp=950,//ֱ����KP��KD  810 4.5
	Vertical_Kd=5;

float 
	Velocity_Kp=85,//�ٶȻ�KP��KI  58  0.25
	Velocity_Ki=0.25;
//	Velocity_Kp=0,//�ٶȻ�KP��KI
//	Velocity_Ki=0;


int Vertical_out,Velocity_out,Turn_out;//ֱ����&�ٶȻ�&ת�� ���������

int Vertical(float Med,float Angle,float gyro_x);//��������
int Velocity(int encoder_motor);
int Turn(int gyro_Z); 

void EXTI9_5_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line5)!=0)//һ���ж�
	{
		if(PBin(5)==0)//�����ж�
		{
            
			EXTI_ClearITPendingBit(EXTI_Line5);//����жϱ�־λ
            
			//1.�ɼ�����������&MPU6050�Ƕ���Ϣ��
			Encoder_Motor=Read_Encoder_TIM4();
			
			mpu_dmp_get_data(&Pitch,&Roll,&Yaw);			//�Ƕ�
			MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);	//�����ǽ��ٶ�
			MPU_Get_Accelerometer(&aacx,&aacy,&aacz);	//���ٶ�
            
            Vertical_out=Vertical(Med_Angle,Roll,gyrox);			//ֱ����
            Velocity_out=Velocity(Encoder_Motor);	//�ٶȻ�
			
			//�Ƕ��ж�
			if(Roll>-100&&Roll<-70)
			{Med_Angle=-85;}
			else if(Roll>-20&&Roll<10)
			{Med_Angle=-4;}
			else if(Roll>70&&Roll<100)
			{Med_Angle=86;}
			else if((Roll>170&&Roll<180)||(Roll<-160&&Roll>-180))
			{Med_Angle=-173;}
			else
			{Vertical_out=0,Velocity_out=0;}



            
			//3.�ѿ�����������ص�����ϣ�������յĵĿ��ơ�
            PWM1=Vertical_out+Velocity_out;//�������
			Limit(&PWM1);	 //PWM�޷�			
			Load(-PWM1);		 //���ص�����ϡ�
			Stop(&Med_Angle,&Roll);		            
		}
	}
}


/*********************
ֱ����PD��������Kp*Ek+Kd*Ek_D

��ڣ������Ƕȡ���ʵ�Ƕȡ���ʵ���ٶ�
���ڣ�ֱ�������
*********************/
int Vertical(float Med,float Angle,float gyro_x)
{
	int PWM_out1;
	PWM_out1=Vertical_Kp*(Angle-Med)+Vertical_Kd*(gyro_x);
	return PWM_out1;
}

/*********************
�ٶȻ�PI��Kp*Ek+Ki*Ek_S
*********************/
int Velocity (int encoder_motor)
{
	static int Encoder_S,EnC_Err_Lowout_last,PWM_out2,Encoder_Err,EnC_Err_Lowout;
	float a=0.7;
	
	//1.�����ٶ�ƫ��
	Encoder_Err=encoder_motor;
    
	//2.���ٶ�ƫ����е�ͨ�˲�:low_out=(1-a)*Ek+a*low_out_last
	EnC_Err_Lowout=(1-a)*Encoder_Err+a*EnC_Err_Lowout_last;//ʹ�ò��θ���ƽ�����˳���Ƶ���ţ���ֹ�ٶ�ͻ�䡣0.3��ǰ�ٶȼ�0.7�ϴ��ٶ�
	EnC_Err_Lowout_last=EnC_Err_Lowout;                     //��ֹ�ٶȹ����Ӱ��ֱ����������������
    
	//3.���ٶ�ƫ����֣����ֳ�λ��
	Encoder_S+=EnC_Err_Lowout;
	//4.�����޷�
	Encoder_S=Encoder_S>10000?10000:(Encoder_S<(-10000)?(-10000):Encoder_S);//�������ƣ�-10000��10000
	
	//5.�ٶȻ������������
	PWM_out2=Velocity_Kp*EnC_Err_Lowout+Velocity_Ki*Encoder_S;
	return PWM_out2;
}



