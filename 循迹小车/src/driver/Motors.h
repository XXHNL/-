
#ifndef	__MOTROS_H
#define	__MOTROS_H
#include "GPIO.h"


typedef struct{

	char LQ_Speed;
	char RQ_Speed;
	char LH_Speed;
	char RH_Speed;
	
}MotorsSpeed;

typedef enum{

	LEFT , MID , RIGHT
}MotorDirection;

void Motors_Init();

// speed :  0 ~ 100 
void Motors_Forward(u8 speed , MotorDirection md); // 0 ~ 100    , 2 
void Motors_Backward(u8 speed, MotorDirection md); // 0 ~ 10
void Motors_Stop();

// 左转和右转
void Motors_Left(u8 speed);
void Motors_Right(u8 speed);

//平移
void Motors_Translate(u8 speed, MotorDirection md);

void Motors_Around(u8 speed);
void Motors_Move(char x, char y);

#endif
