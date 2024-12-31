#include "Track.h"
#include "GPIO.h"

#define LED0 P00
#define LED1 P01
#define LED2 P02
#define LED3 P03
#define LED4 P04

// ��ʼ��
void Track_Init(){
    GPIO_InitTypeDef    GPIO_InitStructure;		//�ṹ����
    GPIO_InitStructure.Pin  = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;		//ָ��Ҫ��ʼ����IO,
    GPIO_InitStructure.Mode = GPIO_PullUp;	//ָ��IO������������ʽ,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
    GPIO_Inilize(GPIO_P0, &GPIO_InitStructure);//��ʼ��
}
int last_count = 0 ;
// ɨ��λ��
int  Track_Scan(){
    	//1. ����һ���м�����������ۼ�����ֵ
	int count = 0 ;
	int num = 0;
	
	//2. �ֱ��ж�5���Ƶ�����״̬ :: �ж���û���� ������LED����Ĺ�������ѹ�ź�ɫ�����ˡ�
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
	
	//2. ���5���ƶ�����û��ѹ���κ��ߵ�ʱ�򡿣��ͷ�����һ�ε�ֵ
	if(num == 0){
		return last_count;
	}
	
	//3. ֱ����ȡƽ��ֵ
	count /= num;
	//1. ����֮ǰ���ȼ�¼һ����ε�ֵ��
	last_count = count;
	return count;
}