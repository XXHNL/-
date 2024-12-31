
#ifndef	__LIGHT_H
#define	__LIGHT_H

typedef enum{
	LEFT1 , RIGHT1, ALL
}Light_Mode;


void Light_Init();

//¿ªµÆ
void Light_On(Light_Mode mode);

//¹ØµÆ
void Light_Off(Light_Mode mode);

#endif