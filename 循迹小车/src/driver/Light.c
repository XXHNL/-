#include "Light.h"
#include "GPIO.h"

#define LED_L  P07
#define LED_R  P52


void Light_Init(){
	GPIO_InitTypeDef	GPIO_InitStructure;		//结构定义
	GPIO_InitStructure.Pin  = GPIO_Pin_2;		//指定要初始化的IO,
	GPIO_InitStructure.Mode = GPIO_OUT_PP;	//指定IO的输入或输出方式,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	GPIO_Inilize(GPIO_P5, &GPIO_InitStructure);//初始化
	
	GPIO_InitStructure.Pin  = GPIO_Pin_7;		//指定要初始化的IO,
	GPIO_InitStructure.Mode = GPIO_OUT_PP;	//指定IO的输入或输出方式,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	GPIO_Inilize(GPIO_P0, &GPIO_InitStructure);//初始化
	
	LED_L = LED_R = 0;
}

//开灯
void Light_On(Light_Mode mode){
	if(mode == LEFT1){ // 开左灯
		LED_L = 1;
	}else if(mode == RIGHT1) { // 开右灯
		LED_R = 1;
	}else{  // 开所有灯
		LED_L = LED_R = 1;
	}
}

//关灯
void Light_Off(Light_Mode mode){

	if(mode == LEFT1){ // 开左灯
		LED_L = 0;
	}else if(mode == RIGHT1) { // 开右灯
		LED_R = 0;
	}else{  // 开所有灯
		LED_L = LED_R = 0;
	}
}