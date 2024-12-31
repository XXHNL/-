#include "Track.h"
#include "GPIO.h"

#define LED0 P00
#define LED1 P01
#define LED2 P02
#define LED3 P03
#define LED4 P04

// 初始化
void Track_Init(){
    GPIO_InitTypeDef    GPIO_InitStructure;		//结构定义
    GPIO_InitStructure.Pin  = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;		//指定要初始化的IO,
    GPIO_InitStructure.Mode = GPIO_PullUp;	//指定IO的输入或输出方式,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
    GPIO_Inilize(GPIO_P0, &GPIO_InitStructure);//初始化
}
int last_count = 0 ;
// 扫描位置
int  Track_Scan(){
    	//1. 定义一个中间变量，用来累加总数值
	int count = 0 ;
	int num = 0;
	
	//2. 分别判断5个灯的亮灭状态 :: 判定灯没有亮 【代表LED下面的光敏电阻压着黑色的线了】
	if(LED0){
		 count += -64;
		 num++;
	}
	
	if(LED1){
		count += -32;
		num++;
	}
	
	if(LED2){
		count += 0;
		num++;
	}
	
	if(LED3){
	  count += 32;
		num++;
	}
		
	if(LED4){
	  count += 64;
		num++;
	}
	
	//2. 如果5个灯都亮【没有压着任何线的时候】，就返回上一次的值
	if(num == 0){
		return last_count;
	}
	
	//3. 直接求取平均值
	count /= num;
	//1. 返回之前，先记录一下这次的值！
	last_count = count;
	return count;
}