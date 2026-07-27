#include <reg52.h>

sbit Key1 = P3^1;
sbit Key2 = P3^0;
sbit Key3 = P3^2;
sbit Key4 = P3^3; 

/**
  * @brief 获取独立按键键码
  * @param 无
  * @retval 按下按键的键码，范围0~4，无独立按键按下时返回值为0
  */
unsigned char Key(){
	static unsigned char lastState = 0x0F; // 记录上一次低4位状态（默认全高）
	unsigned char currentState = P3 & 0x0F; // 读取当前低4位
	unsigned char KeyNumber = 0;
	
	if((lastState & 0x02) && !(currentState & 0x02)){
      KeyNumber = 1;
	}else if((lastState & 0x01) && !(currentState & 0x01)){
	  KeyNumber = 2;
	}else if((lastState & 0x04) && !(currentState & 0x04)){
	  KeyNumber = 3;
	}else if((lastState & 0x08) && !(currentState & 0x08)){
	  KeyNumber = 4;
	}
	
	lastState = currentState;
	
	return KeyNumber;
}