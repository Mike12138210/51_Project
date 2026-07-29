#include <reg52.h>
#include <intrins.h>

// 蜂鸣器端口
sbit Buzzer = P2^5;

/**
  * @brief 蜂鸣器私有延时函数，延时500us @11.0592MHz
  * @param 无
  * @retval 
  */
void Buzzer_Delay500us(){
	unsigned char i;
	_nop_();
	i = 227;
	while (--i);
}

/**
  * @brief 蜂鸣器鸣响
  * @param ms 发声的时长
  * @retval 无
  */
void Buzzer_Time(unsigned int ms){
	unsigned int i;
	for(i = 0;i < ms*2;i++){
		Buzzer = !Buzzer;
		Buzzer_Delay500us();
	}
}