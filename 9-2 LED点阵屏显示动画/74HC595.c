#include <reg52.h>

sbit RCK = P3^5; // RCLK
sbit SCK = P3^6; // SRCLK
sbit SER = P3^4;

/**
  * @brief 74HC595写入一个字节
  * @param Byte 要写入的字节
  * @retval 无
  */
void _74HC595_WriteByte(unsigned char Byte){
	unsigned char i;
	for(i = 0;i < 8;i++){
		SER = Byte & (0x80>>i); // SER非0即1
	  SCK = 1;
	  SCK = 0;
	}
	RCK = 1;
	RCK = 0;
}