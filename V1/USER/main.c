#include "sys.h"

//float AdcValue;                                    //��ص�ѹ������
float Pitch,Roll,Yaw;						      //�Ƕ�
short aacx,aacy,aacz;		                        //���ٶȴ�����ԭʼ����
short gyrox,gyroy,gyroz;	                        //������ԭʼ����
int PWM1;
int PWM_MAX=6500,PWM_MIN=-6500;	//PWM�޷�����
int Encoder_Motor;	//���������ݣ��ٶȣ�

int main(void)
{  
	  NVIC_Config();
   	delay_init();
//    Led_Init();
//    Beep_Init();
//    Wave_SRD_Init();
   	uart3_init(9600);
    OLED_Init();			//��ʼ��OLED  
    OLED_Clear();
	  adc_Init();
    MOTOR_1_Init();
    MOTOR_2_Init();
    PWM_Init_TIM3(7199,0);//��ʱ��3��ʼ��PWM 10KHZ���������������ֵ�� 
//    PWM_Init_TIM2(9999, 143);//��ʱ��2��ʼ��PWM 50HZ�������������
//    TIM_SetCompare1(TIM2, 790);//�����λ
    Init_TIM1(9998,7199);
    Encoder_Init_TIM4(65535,0);//��������ʼ��
    OLED_ShowString(25,4,"MPU6050...",16);
    MPU_Init();            //MPU6050��ʼ��  
    while(mpu_dmp_init())
 	{
		OLED_ShowString(25,4,"MPU6050 Error",16);
	}  
    OLED_ShowString(25,4,"MPU6050 OK!",16); 
//    Beep=1;
    delay_ms(400);
//    Beep=0;
    MPU6050_EXTI_Init();
    OLED_Clear();
 	  OLED_ShowString(0,0,"Roll :         C",16);//�Ƕ���ʾ
    OLED_ShowString(0,3,"Speed:         R ",16);//�ٶ���ʾ
//    OLED_ShowString(0,6,"Power:        V ",16); //��ѹ��ʾ   
    OLED_ShowString(0,6,"  xiaocainiao",16);  

    while(1)
    {	        
//        Wave_SRD_Strat();        
//        AdcValue=11.09*(3.3*Get_adc_Average(ADC_Channel_4,10)/0x0fff); //ADCֵ��ΧΪ��0-2^12=4095��111111111111��һ������¶�Ӧ��ѹΪ0-3.3V
        OLED_Showdecimal(55,0,Roll,9,16);  
        OLED_Showdecimal(55,3,Encoder_Motor*0.25,9,16);         
//        OLED_Showdecimal(50,6,AdcValue,9,16);       
	}
}
