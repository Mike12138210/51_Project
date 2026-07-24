#include <reg52.h>
#include "Timer0.h"
#include "MatrixLED.h"

sbit RCK = P3^5; // RCLK
sbit SCK = P3^6; // SRCLK
sbit SER = P3^4;

#define MATRIX_LED_PORT P0

// 存储图像数据（每一列对应一个字节）
unsigned char code LEDImage[] = {
    0x30, 0x48, 0x44, 0x22, 
    0x22, 0x44, 0x48, 0x30
}; // 0x08,0x53,0xFE,0xFE,0x52,0x1D,0x0C

void main(){
	SCK = 0;
	RCK = 0;
	Timer0_Init();
	while(1){

	}
}

void Timer0_Routine() interrupt 1{
	static unsigned char currentColumn;
  TL0 = 0x66; // 设置定时初值
  TH0 = 0xFC; // 设置定时初值
	
	MATRIX_LED_PORT = 0xFF;
	MatrixLED_ShowColumn(currentColumn,LEDImage[currentColumn]);
	
	currentColumn++;
	if(currentColumn >= 8) currentColumn = 0;
}