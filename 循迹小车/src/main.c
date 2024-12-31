#include "RTX51TNY.h"
#include "Light.h"
#include "Key.h"
#include "Ultrasonic.h"
#include "Battery.h"
#include "Buzzer.h"
#include "Motors.h"
#include "Track.h"
#include "ADC.h"
#include "Bluetooth.h"
#include "UART.h"


#define TASK_MAIN 		0 
#define TASK_LED  		1
#define TASK_KEY 		2
#define TASK_ULTRASONIC 3
#define TASK_BUZZER 	4
#define TASK_TRACK 		5
#define TASK_VOLTAGE 	6
#define TASK_BT 		7

//系统配置
void sys_config(){

    Light_Init();
	Key_Init();
	Battery_Init();
	Buzzer_Init();
	Motors_Init();
	Ultrasonic_Init();
	Track_Init();
	//开启总中断
	EA =1;
	Bluetooth_GPIO_Config();
	Bluetooth_UART_Config();
	
}

void task_main() _task_ TASK_MAIN{
	
	//1. 系统配置
	sys_config();

	//2. 启动其他任务
	os_create_task(TASK_LED);
	os_create_task(TASK_KEY);
	os_create_task(TASK_BT);
//	os_create_task(TASK_ULTRASONIC);
//	os_create_task(TASK_BUZZER);
//	os_create_task(TASK_TRACK);
//	os_create_task(TASK_VOLTAGE);
	//3. 干掉自己
	os_delete_task(TASK_MAIN);
	
}

int countA = 0;
void handle_bt_data( u8 dat[]){
	char x = dat[2];
	char y = dat[3];
	if(dat[4]){
		if(countA % 2 == 0){
			Motors_Forward(30, MID);
			Light_On(ALL);
		}
	}else if(dat[5]){
		if(countA % 2 == 0){
			Motors_Forward(30,LEFT);
			Light_On(ALL);
		} else  {
			Motors_Stop();
			Light_Off( RIGHT);
		}
		countA++;
	}else if(dat[6]){
		if(countA % 2 == 0){
			Motors_Forward(30, RIGHT);
			Light_On(ALL);
		} else  {
			Motors_Stop();
			Light_Off( RIGHT);
		}
		countA++;
	}else if(dat[7]){
		if(countA % 2 == 0){
			os_create_task(TASK_BUZZER);
			Light_On(ALL);
		} else  {
			Motors_Stop();
			Light_Off( RIGHT);
		}
		countA++;
	}else{
		Light_Off( ALL);
	}
	
	Motors_Move(x,y);
}

//蓝牙
void task_bt() _task_ TASK_BT{
	
	while(1){
		void task_bluetooth();
		os_wait2(K_TMO, 4);
	}
}
//LED灯的任务
void  task_led() _task_ TASK_LED{
	while(1){
		Light_On( LEFT);
		os_wait2(K_TMO, 200);
		Light_Off( LEFT);
		os_wait2(K_TMO, 200);
	}

}

 void down(){
	 sys_config();
	 Light_On( RIGHT);
	 os_create_task(TASK_TRACK);
 }
 void up(){
	 Light_Off( RIGHT);
 }
//按键任务
void task_key() _task_ TASK_KEY{

	while(1){
		Key_Scan(down,up);
		os_wait2(K_TMO, 4);
	}
}

void task_Ultrasonic() _task_ TASK_ULTRASONIC{
	while(1){
		float distance = Ultrasonic_GetDistance();
		if (distance > 20 ){
			os_create_task( TASK_TRACK );
			printf("%.2f\n",distance);
		} else {	
			Motors_Translate(30, RIGHT);
			os_wait2(K_TMO, 200);
			Motors_Translate(30, LEFT);
			os_wait2(K_TMO, 200);
//			printf( );
		}
		os_wait2(K_TMO, 4);

	}
}

u16 hz[] = {1047, 1175, 1319, 1397, 1568, 1760, 1976, 2093};
void task_buzzer() _task_ TASK_BUZZER{
	
	int i = 0 ;
	while(1){
		
	
		for( i = 0 ; i < sizeof(hz) / sizeof(u16) ; i++){
			Buzzer_Play(hz[i]);
			
			os_wait2(K_TMO , 100);
		}
		
		Buzzer_Stop();
		
		os_wait2(K_TMO , 200);
		os_wait2(K_TMO , 200);
		os_wait2(K_TMO , 200);
	}

}

// 循迹任务
void task_track() _task_ TASK_TRACK{

	while(1){
		
		//1. 获取车的位置
		int count = Track_Scan();
		
		//2. 判断位置，驱动车前进
		if(count < -32){ // 左边LED压着黑色线，左转
			Motors_Left(30); // 调整速度为20，避免冲出赛道
	//		Motors_Translate(15, LEFT);
		} else if(count < 0 && count >= -32) { // 左边LED压着黑色线，轻微左转
			Motors_Left(18);
		} else if(count > 32) { // 右边LED灯压着黑色线，右转
			Motors_Right(30); // 调整速度为20，避免冲出赛道
	//		Motors_Translate(15, RIGHT);
		} else if(count > 0 && count <= 32) { // 右边LED灯压着黑色线，轻微右转
			Motors_Right(18);
		} else { // 直走
			Motors_Forward(30, MID); // 调整速度为30，避免冲出赛道
		}
		
		os_wait2(K_TMO , 4); // 每4ms 去看看5个灯是什么状态
	}
}
//测量电压
//void task_voltage() _task_ TASK_VOLTAGE{
//
//	while(1){
//		float adc_v = Battery_GetVoltage();
//		//3. 打印
//		printf("adc_v6666= %.2f\n" , adc_v);
//		
//		os_wait2(K_TMO , 200);
//	}
//}
