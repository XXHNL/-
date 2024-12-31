#include "Key.h"
#include "GPIO.h"

#define KEY  P05

void Key_Init(){
	GPIO_InitTypeDef	GPIO_InitStructure;		//结构定义
	GPIO_InitStructure.Pin  = GPIO_Pin_5;		//指定要初始化的IO,
	GPIO_InitStructure.Mode = GPIO_HighZ;	//指定IO的输入或输出方式,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	GPIO_Inilize(GPIO_P0, &GPIO_InitStructure);//初始化
}


u8 status = 1;
void Key_Scan( void(*down)() , void (*up)() ){
		if(KEY == 0 && status == 1){
			
			if(down != NULL) down();
			
			status = 0 ;
		}else if(KEY == 1 && status == 0){
			
			if(up!= NULL) up();
			
			status = 1;
		}
}