#include "Buzzer.h"
#include "GPIO.h"
#include "STC8H_PWM.h"
#include "Switch.h"

#define BUZZER P34

void Buzzer_GPIO_Config(void) {
	GPIO_InitTypeDef	GPIO_InitStructure;		//结构定义
	GPIO_InitStructure.Pin  = GPIO_Pin_4;		//指定要初始化的IO,
	GPIO_InitStructure.Mode = GPIO_OUT_PP;	//指定IO的输入或输出方式,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	GPIO_Inilize(GPIO_P3, &GPIO_InitStructure);//初始化
	
	BUZZER = 0 ;
}


void	PWM_Config(u16 hz){
 
	PWMx_InitDefine init;
	
	u16 period = ( MAIN_Fosc / hz )  - 1;
	
	init.PWM_Mode = CCMRn_PWM_MODE2;			//模式,   CCMRn_FREEZE,CCMRn_MATCH_VALID,CCMRn_MATCH_INVALID,CCMRn_ROLLOVER,CCMRn_FORCE_INVALID,CCMRn_FORCE_VALID,CCMRn_PWM_MODE1,CCMRn_PWM_MODE2
	init.PWM_Period = period;		//周期时间,   0~65535
	init.PWM_Duty = period * 0.5 ;			//占空比时间, 0~Period
	init.PWM_DeadTime = 0;	//死区发生器设置, 0~255
	init.PWM_EnoSelect =ENO8P;		//输出通道选择,	ENO1P,ENO1N,ENO2P,ENO2N,ENO3P,ENO3N,ENO4P,ENO4N / ENO5P,ENO6P,ENO7P,ENO8P
	init.PWM_CEN_Enable = ENABLE;		//使能计数器, ENABLE,DISABLE
	init.PWM_MainOutEnable = ENABLE;//主输出使能,  ENABLE,DISABLE
	
	PWM_Configuration(PWM8,&init);
	PWM_Configuration(PWMB,&init);
	
	PWM8_SW(PWM8_SW_P34);
}

void Buzzer_Init(){
    Buzzer_GPIO_Config();
    EAXSFR();
}

void Buzzer_Play(u16 hz){
    PWM_Config(hz);
}

void Buzzer_Stop(){
    PWMx_InitDefine init;
	init.PWM_CEN_Enable = DISABLE;		//使能计数器, ENABLE,DISABLE
	init.PWM_MainOutEnable = DISABLE;//主输出使能,  ENABLE,DISABLE
	
	PWM_Configuration(PWM8,&init);
	PWM_Configuration(PWMB,&init);
}