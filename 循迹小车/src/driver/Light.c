#include "Light.h"
#include "GPIO.h"

#define LED_L  P07
#define LED_R  P52


void Light_Init(){
	GPIO_InitTypeDef	GPIO_InitStructure;		//�ṹ����
	GPIO_InitStructure.Pin  = GPIO_Pin_2;		//ָ��Ҫ��ʼ����IO,
	GPIO_InitStructure.Mode = GPIO_OUT_PP;	//ָ��IO������������ʽ,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	GPIO_Inilize(GPIO_P5, &GPIO_InitStructure);//��ʼ��
	
	GPIO_InitStructure.Pin  = GPIO_Pin_7;		//ָ��Ҫ��ʼ����IO,
	GPIO_InitStructure.Mode = GPIO_OUT_PP;	//ָ��IO������������ʽ,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	GPIO_Inilize(GPIO_P0, &GPIO_InitStructure);//��ʼ��
	
	LED_L = LED_R = 0;
}

//����
void Light_On(Light_Mode mode){
	if(mode == LEFT1){ // �����
		LED_L = 1;
	}else if(mode == RIGHT1) { // ���ҵ�
		LED_R = 1;
	}else{  // �����е�
		LED_L = LED_R = 1;
	}
}

//�ص�
void Light_Off(Light_Mode mode){

	if(mode == LEFT1){ // �����
		LED_L = 0;
	}else if(mode == RIGHT1) { // ���ҵ�
		LED_R = 0;
	}else{  // �����е�
		LED_L = LED_R = 0;
	}
}