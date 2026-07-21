#include <reg52.h>
#include "Delay.h"

sbit Key1 = P3^1;
sbit Key2 = P3^2;
sbit Key3 = P3^3;
sbit Key4 = P3^4;

/**
  * @brief 获取独立按键键码
  * @param 无
  * @retval 按下按键的键码，范围0~4，无独立按键按下时返回值为0
  */
unsigned char Key(){
	unsigned char KeyNumber = 0;
	
	if(Key1 == 0){Delay(20);while(Key1 == 0);Delay(20);KeyNumber = 1;}
	if(Key2 == 0){Delay(20);while(Key2 == 0);Delay(20);KeyNumber = 2;}
	if(Key3 == 0){Delay(20);while(Key3 == 0);Delay(20);KeyNumber = 3;}
	if(Key4 == 0){Delay(20);while(Key4 == 0);Delay(20);KeyNumber = 4;}
	
	return KeyNumber;
}