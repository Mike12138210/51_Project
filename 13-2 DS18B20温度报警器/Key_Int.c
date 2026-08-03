#include <reg52.h>

sbit Key1 = P3^1;
sbit Key2 = P3^0;
sbit Key3 = P3^2;
sbit Key4 = P3^3; 

unsigned char Key_KeyNum;

/**
  * @brief  获取按键键码
  * @param  无
  * @retval 按键键码（1~4），无按键按下时返回0
  */
unsigned char Key(){
	unsigned char Temp = 0;
	Temp = Key_KeyNum;
	Key_KeyNum = 0;
	return Temp;
}

/**
  * @brief  获取当前按键的实时状态
  * @param  无
  * @retval 当前按下的按键键码（1~4），无按键按下时返回0
  */
unsigned char Key_GetState(){
	unsigned char KeyNumber = 0;
	
	if(Key1 == 0){KeyNumber = 1;}
	if(Key2 == 0){KeyNumber = 2;}
	if(Key3 == 0){KeyNumber = 3;}
	if(Key4 == 0){KeyNumber = 4;}

	return KeyNumber;
}

/**
  * @brief  按键驱动函数（由定时器中断周期性调用）
  * @param  无
  * @retval 无
  */
void Key_Loop(){
	static unsigned char NowState, LastState;
	LastState = NowState;
	NowState = Key_GetState();
	
	if(LastState == 1 && NowState == 0){
		Key_KeyNum = 1;
	}
	if(LastState == 2 && NowState == 0){
		Key_KeyNum = 2;
	}
	if(LastState == 3 && NowState == 0){
		Key_KeyNum = 3;
	}
	if(LastState == 4 && NowState == 0){
		Key_KeyNum = 4;
	}
}