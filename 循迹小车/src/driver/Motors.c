#include "Motors.h"
#include "GPIO.h"
#include "STC8H_PWM.h"
#include "Switch.h"


void Motors_GPIO_Config(void) {
	GPIO_InitTypeDef	GPIO_InitStructure;		//�ṹ����
	GPIO_InitStructure.Pin  = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;		//ָ��Ҫ��ʼ����IO,
	GPIO_InitStructure.Mode = GPIO_PullUp;	//ָ��IO������������ʽ,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	GPIO_Inilize(GPIO_P1, &GPIO_InitStructure);//��ʼ��
	
	GPIO_InitStructure.Pin  = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;		//ָ��Ҫ��ʼ����IO,
	GPIO_InitStructure.Mode = GPIO_PullUp;	//ָ��IO������������ʽ,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	GPIO_Inilize(GPIO_P2, &GPIO_InitStructure);//��ʼ��
}


/*
	�������ӵ��ٶȣ�����������ӵ�ռ�ձ�
	�����ٶ�ֵ��  0��MIN��          ---------               100 ��MAX��
  ���ӵ��ٶȣ�  -100                  0                      100 ��MAX��
	ռ�ձ�   :      0      -----        50      ----------     100

	ռ�ձ� = speed / 2 + 50 ;
*/
u8 Speed2Duty(char speed){
	return speed / 2 + 50;
}


#define PERIOD (MAIN_Fosc / 1000 - 1)
void Motors_PWM_Config(MotorsSpeed ms){
//	PWMx_InitDefine init;
	
	
	
	//=========================== ����4�����ӵ��ٶ� Ϊ 4�����ӵ�ռ�ձ�==================
	int LQ_Duty = Speed2Duty(ms.LQ_Speed);
	int RQ_Duty = Speed2Duty(ms.RQ_Speed);
	int LH_Duty = Speed2Duty(ms.LH_Speed);
	int RH_Duty = Speed2Duty(ms.RH_Speed); 
	
	PWMx_InitDefine init;
	
	//�����Ļ��ߴ�������ã�
	init.PWM_Period = PERIOD - 1;		//����ʱ��,   0~65535

	init.PWM_DeadTime = 10;	//��������������, 0~255
	init.PWM_CEN_Enable = ENABLE;		//ʹ�ܼ�����, ENABLE,DISABLE
	init.PWM_MainOutEnable = ENABLE;//�����ʹ��,  ENABLE,DISABLE
	PWM_Configuration(PWMA , &init);
	
	//ÿһ����������ã�
	
	//LQ  :  P13  P14
	init.PWM_Duty = PERIOD * LQ_Duty / 100;			//ռ�ձ�ʱ��, 0~Period
	init.PWM_Mode = CCMRn_PWM_MODE1;			//ģʽ,   CCMRn_FREEZE,CCMRn_MATCH_VALID,CCMRn_MATCH_INVALID,CCMRn_ROLLOVER,CCMRn_FORCE_INVALID,CCMRn_FORCE_VALID,CCMRn_PWM_MODE1,CCMRn_PWM_MODE2
	init.PWM_EnoSelect =ms.LQ_Speed ? ENO3P|ENO3N : 0 ;		//���ͨ��ѡ��,	ENO1P,ENO1N,ENO2P,ENO2N,ENO3P,ENO3N,ENO4P,ENO4N / ENO5P,ENO6P,ENO7P,ENO8P
	PWM_Configuration(PWM3 , &init);
	
	
	//RQ  :  P16  P17
	init.PWM_Duty = PERIOD * RQ_Duty / 100;			//ռ�ձ�ʱ��, 0~Period
	init.PWM_Mode = CCMRn_PWM_MODE2;			//ģʽ,   CCMRn_FREEZE,CCMRn_MATCH_VALID,CCMRn_MATCH_INVALID,CCMRn_ROLLOVER,CCMRn_FORCE_INVALID,CCMRn_FORCE_VALID,CCMRn_PWM_MODE1,CCMRn_PWM_MODE2
	init.PWM_EnoSelect =ms.RQ_Speed ? ENO4P|ENO4N : 0 ;		//���ͨ��ѡ��,	ENO1P,ENO1N,ENO2P,ENO2N,ENO3P,ENO3N,ENO4P,ENO4N / ENO5P,ENO6P,ENO7P,ENO8P
	PWM_Configuration(PWM4 , &init);
	
	
	
	//LH  :  P20  P21
	init.PWM_Duty = PERIOD * LH_Duty / 100;		//ռ�ձ�ʱ��, 0~Period
	init.PWM_Mode = CCMRn_PWM_MODE1;			//ģʽ,   CCMRn_FREEZE,CCMRn_MATCH_VALID,CCMRn_MATCH_INVALID,CCMRn_ROLLOVER,CCMRn_FORCE_INVALID,CCMRn_FORCE_VALID,CCMRn_PWM_MODE1,CCMRn_PWM_MODE2
	init.PWM_EnoSelect =ms.LH_Speed ? ENO1P|ENO1N : 0 ;		//���ͨ��ѡ��,	ENO1P,ENO1N,ENO2P,ENO2N,ENO3P,ENO3N,ENO4P,ENO4N / ENO5P,ENO6P,ENO7P,ENO8P
	PWM_Configuration(PWM1 , &init);
	
	
	//RH  :  P22  P23
	init.PWM_Duty = PERIOD * RH_Duty / 100;		//ռ�ձ�ʱ��, 0~Period
	init.PWM_Mode = CCMRn_PWM_MODE2;			//ģʽ,   CCMRn_FREEZE,CCMRn_MATCH_VALID,CCMRn_MATCH_INVALID,CCMRn_ROLLOVER,CCMRn_FORCE_INVALID,CCMRn_FORCE_VALID,CCMRn_PWM_MODE1,CCMRn_PWM_MODE2
	init.PWM_EnoSelect =ms.RH_Speed ? ENO2P|ENO2N : 0;		//���ͨ��ѡ��,	ENO1P,ENO1N,ENO2P,ENO2N,ENO3P,ENO3N,ENO4P,ENO4N / ENO5P,ENO6P,ENO7P,ENO8P
	PWM_Configuration(PWM2 , &init);
	
	
	PWM1_SW(PWM1_SW_P20_P21);
	PWM2_SW(PWM2_SW_P22_P23);
	PWM3_SW(PWM3_SW_P14_P15);
	PWM4_SW(PWM4_SW_P16_P17);
	
}




void Motors_Init(){
	Motors_GPIO_Config();
	EAXSFR();
}

void Motors_Forward(u8 speed, MotorDirection md){ // 100;
	
	//1. ��װ4�����ӵ��ٶ�
	MotorsSpeed ms ;
	
	if(md == LEFT){ // ��ǰ
		ms.LQ_Speed = speed - 5;
		ms.RQ_Speed = speed;
		ms.LH_Speed = speed;
		ms.RH_Speed = speed - 5;
		
	}else if(md == RIGHT){ // ��ǰ
		
		ms.LQ_Speed = speed;
		ms.RQ_Speed = speed - 5;
		ms.LH_Speed = speed - 5;
		ms.RH_Speed = speed;
		
	}else { // ��ǰ
		ms.LQ_Speed = speed;
		ms.RQ_Speed = speed;
		ms.LH_Speed = speed;
		ms.RH_Speed = speed;
	
	}

	//2. �ѽṹ�崫�ݸ� PWM_Config
	Motors_PWM_Config(ms);
}


void Motors_Backward(u8 speed, MotorDirection md){ // 100
	
	//1. ��װ4�����ӵ��ٶ�
	MotorsSpeed ms ;
	
	if(md == LEFT) { // ���
		ms.LQ_Speed = -speed;
		ms.RQ_Speed = 0;
		ms.LH_Speed = 0;
		ms.RH_Speed = -speed;
 		
	}else if(md == RIGHT){ // �Һ�
		ms.LQ_Speed = 0;
		ms.RQ_Speed = -speed;
		ms.LH_Speed = -speed;
		ms.RH_Speed = 0;
		
	}else { // ����
		ms.LQ_Speed = -speed;
		ms.RQ_Speed = -speed;
		ms.LH_Speed = -speed;
		ms.RH_Speed = -speed;
	}

	
	//2. �ѽṹ�崫�ݸ� PWM_Config
	Motors_PWM_Config(ms);
}


void Motors_Left(u8 speed){
	//1. ��װ4�����ӵ��ٶ�
	MotorsSpeed ms ;
	
	ms.LQ_Speed = speed - 15;
	ms.RQ_Speed = speed;
	ms.LH_Speed = speed - 15;
	ms.RH_Speed = speed;
	
	//2. �ѽṹ�崫�ݸ� PWM_Config
	Motors_PWM_Config(ms);
}
void Motors_Right(u8 speed){
	//1. ��װ4�����ӵ��ٶ�
	MotorsSpeed ms ;
	
	ms.LQ_Speed = speed;
	ms.RQ_Speed = speed - 15;
	ms.LH_Speed = speed;
	ms.RH_Speed = speed - 15;
	
	//2. �ѽṹ�崫�ݸ� PWM_Config
	Motors_PWM_Config(ms);
}

void Motors_Around(u8 speed){
	//1. ��װ4�����ӵ��ٶ�
	MotorsSpeed ms ;
	
	ms.LQ_Speed = -speed;
	ms.RQ_Speed = speed;
	ms.LH_Speed = -speed;
	ms.RH_Speed = speed;
	
	//2. �ѽṹ�崫�ݸ� PWM_Config
	Motors_PWM_Config(ms);
}

void Motors_Translate(u8 speed, MotorDirection md){
	//1. ��װ4�����ӵ��ٶ�
	MotorsSpeed ms ;

	if(md == LEFT){
		
		ms.LQ_Speed = -speed;
		ms.RQ_Speed = speed;
		ms.LH_Speed = speed;
		ms.RH_Speed = -speed;
		
	}else if(md == RIGHT){
		
		ms.LQ_Speed = speed;
		ms.RQ_Speed = -speed;
		ms.LH_Speed = -speed;
		ms.RH_Speed = speed;
	
	}else { // ����ֵ�ˣ�
	
		ms.LQ_Speed = 0;
		ms.RQ_Speed = 0;
		ms.LH_Speed = 0;
		ms.RH_Speed = 0;
	}
	
	//2. �ѽṹ�崫�ݸ� PWM_Config
	Motors_PWM_Config(ms);
	
}

void Motors_Stop(){
	//1. ��װ4�����ӵ��ٶ�
	MotorsSpeed ms ;
	
	ms.LQ_Speed = 0;
	ms.RQ_Speed = 0;
	ms.LH_Speed = 0;
	ms.RH_Speed = 0;
	
	//2. �ѽṹ�崫�ݸ� PWM_Config
	Motors_PWM_Config(ms);
}

char LimitSpeed(int value){
	if (value >= 100){
		return 100;
	}else if(value <= -100){
		return -100;
	}
	return value;
}
void Motors_Move(char x,char y){
	//1. ��װ4�����ӵ��ٶ�
	MotorsSpeed ms ;
	
	ms.LQ_Speed = 0.4 * LimitSpeed(y + x);
	ms.RQ_Speed = 0.4 * LimitSpeed(y - x);
	ms.LH_Speed = 0.4 * LimitSpeed(y - x);
	ms.RH_Speed = 0.4 * LimitSpeed(y + x);
	
	//2. �ѽṹ�崫�ݸ� PWM_Config
	Motors_PWM_Config(ms);
}