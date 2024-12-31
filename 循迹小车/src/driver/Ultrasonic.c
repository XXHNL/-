#include "Ultrasonic.h"
#include "GPIO.h"

#define ECHO P33
#define TRIG P47

void Ultrasonic_Init(){
    GPIO_InitTypeDef	GPIO_InitStructure;		//结构定义
    GPIO_InitStructure.Pin  = GPIO_Pin_3;		//指定要初始化的IO,
    GPIO_InitStructure.Mode = GPIO_HighZ;	//指定IO的输入或输出方式,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
    GPIO_Inilize(GPIO_P3, &GPIO_InitStructure);//初始化

    GPIO_InitStructure.Pin  = GPIO_Pin_7;		//指定要初始化的IO,
    GPIO_InitStructure.Mode = GPIO_OUT_PP;	//指定IO的输入或输出方式,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
    GPIO_Inilize(GPIO_P4, &GPIO_InitStructure);//初始化

    ECHO = TRIG = 0;
}

void Delay10us(void)	//@24.000MHz
{
	unsigned char data i;

	i = 78;
	while (--i);
}

void Delay100us(void)	//@24.000MHz
{
	unsigned char data i, j;

	i = 4;
	j = 27;
	do
	{
		while (--j);
	} while (--i);
}


float Ultrasonic_GetDistance(){
    int count = 0;
    TRIG = 1;
    Delay10us();	//@24.000MHz
    Delay10us();//@24.000MHz
    TRIG = 0;

    do{
        count ++;
        Delay100us();
    }while (TRIG == 0 && ECHO ==0 );
    if (count >23){
        return -1;
    }
    count = 0;
    do{
        count ++;
        Delay100us();
        }while (ECHO == 1);
  //  printf("count = %d\n",count);
    return count * 100 /1000.0 * 17;
    

}