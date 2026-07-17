#include <reg52.h>
#include "Delay.h"

sbit P1_0 = P1^0;
sbit P1_1 = P1^1;
sbit P1_2 = P1^2;
sbit P1_3 = P1^3;
sbit P1_4 = P1^4;
sbit P1_5 = P1^5;
sbit P1_6 = P1^6;
sbit P1_7 = P1^7;

/**
  * @brief  矩阵键盘读取按键键码
  * @param  无
  * @retval KeyNumber 按下按键的键码值
            如果按键按下不放，程序会停留在此函数，松手的一瞬间，返回按键键码，没有按键按下时，返回0
  */
unsigned char MatrixKey(){
	unsigned char KeyNumber = 0;
	
	// 第一列
	P1 = 0xFF; // P1全部高电平
	P1_3 = 0;
	if(P1_7 == 0){Delay(20);while(P1_7 == 0);Delay(20);KeyNumber = 1;}
	if(P1_6 == 0){Delay(20);while(P1_6 == 0);Delay(20);KeyNumber = 5;}
	if(P1_5 == 0){Delay(20);while(P1_5 == 0);Delay(20);KeyNumber = 9;}
	if(P1_4 == 0){Delay(20);while(P1_4 == 0);Delay(20);KeyNumber = 13;}
	
	// 第二列
	P1 = 0xFF; // P1全部高电平
	P1_2 = 0;
	if(P1_7 == 0){Delay(20);while(P1_7 == 0);Delay(20);KeyNumber = 2;}
	if(P1_6 == 0){Delay(20);while(P1_6 == 0);Delay(20);KeyNumber = 6;}
	if(P1_5 == 0){Delay(20);while(P1_5 == 0);Delay(20);KeyNumber = 10;}
	if(P1_4 == 0){Delay(20);while(P1_4 == 0);Delay(20);KeyNumber = 14;}
	
	// 第三列
	P1 = 0xFF; // P1全部高电平
	P1_1 = 0;
	if(P1_7 == 0){Delay(20);while(P1_7 == 0);Delay(20);KeyNumber = 3;}
	if(P1_6 == 0){Delay(20);while(P1_6 == 0);Delay(20);KeyNumber = 7;}
	if(P1_5 == 0){Delay(20);while(P1_5 == 0);Delay(20);KeyNumber = 11;}
	if(P1_4 == 0){Delay(20);while(P1_4 == 0);Delay(20);KeyNumber = 15;}
	
	// 第四列
	P1 = 0xFF; // P1全部高电平
	P1_0 = 0;
	if(P1_7 == 0){Delay(20);while(P1_7 == 0);Delay(20);KeyNumber = 4;}
	if(P1_6 == 0){Delay(20);while(P1_6 == 0);Delay(20);KeyNumber = 8;}
	if(P1_5 == 0){Delay(20);while(P1_5 == 0);Delay(20);KeyNumber = 12;}
	if(P1_4 == 0){Delay(20);while(P1_4 == 0);Delay(20);KeyNumber = 16;}
	
	return KeyNumber;
}