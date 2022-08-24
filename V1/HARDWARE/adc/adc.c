#include "adc.h"
#include "delay.h"

//ADC��ʼ������
void adc_Init()
{
  GPIO_InitTypeDef GPIO_InitStructure; //����һ�����ų�ʼ���Ľṹ��  
  ADC_InitTypeDef ADC_InitStructure; //����һ��ADC��ʼ���Ľṹ�� 
  
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); //ʹ��CPIOBʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE); //ʹ��TIM4ʱ��
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4; //����0
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AIN; //�����������ģʽΪģ������ģʽ
	GPIO_Init(GPIOA, &GPIO_InitStructure); //�����������úõ�GPIO_InitStructure��������ʼ������GPIOA_PIN0

	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //����ADC��Ƶ����6 72M/6=12,ADC���ʱ�䲻�ܳ���14M
	ADC_DeInit(ADC1);  //��λADC1,������ ADC1 ��ȫ���Ĵ�������Ϊȱʡֵ
	
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC����ģʽ:ADC1��ADC2�����ڶ���ģʽ
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;	//�Ƿ�Ϊɨ�裨һ�飩ģʽ���񣺵�ͨ��ģʽ
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	//�Ƿ�Ϊ����ת��ģʽ���񣺵���ת��ģʽ
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//ת��������������ⲿ��������
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC���ݶ���ģʽ���Ҷ���
	ADC_InitStructure.ADC_NbrOfChannel = 1;	//˳����й���ת����ADCͨ������Ŀ
	ADC_Init(ADC1, &ADC_InitStructure);	//����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���  
	
	ADC_Cmd(ADC1, ENABLE);
	
	ADC_ResetCalibration(ADC1);	//ʹ�ܸ�λУ׼   
	while(ADC_GetResetCalibrationStatus(ADC1));	//�ȴ���λУ׼����
	
	ADC_StartCalibration(ADC1);	 //����ADУ׼
	while(ADC_GetCalibrationStatus(ADC1));	 //�ȴ�У׼����
	
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//ʹ��ָ����ADC1�����ת����������
}

//�ɼ�ADCֵ�������������ΪADCͨ��
u16 Get_adc(u8 chn)
{
	ADC_RegularChannelConfig(ADC1, chn, 1, ADC_SampleTime_239Cycles5 );	//ADC1,chn��ADCͨ������3���������ø�ͨ����ת��˳�򣨶�ͨ��ģʽ�£�
	                                                                  //����ʱ��Ϊ239.5����=239.5/ADCCLOK��ADCCLOK=72/6MHZ(6����ADC��ʼ��ʱ�ķ�Ƶϵ��)		    
  
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//ʹ��ָ����ADC1�����ת����������	
	 
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//�ȴ�ת������
	return ADC_GetConversionValue(ADC1);	//�������һ��ADC1�������ת�����
}

//�ɼ����ADCֵ��ƽ��ֵ�������������ΪADCͨ���Ͳɼ�����
u16 Get_adc_Average(u8 chn, u8 times)
{
  u32 temp_val=0;
	u8 t;
	for(t=0;t<times;t++)
	{
		temp_val+=Get_adc(chn);
		delay_ms(5);
	}
	return temp_val/times;
}

