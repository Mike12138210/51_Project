#include <reg52.h>
#include "Timer0.h"
#include "MatrixLED.h"

#define MATRIX_LED_PORT P0

unsigned char currentFrame;
unsigned char frameCounter; // 用于控制帧切换速度（帧延时计数器）

// 存储图像帧数据
unsigned char code LEDAnimation[][8] = {
    {0x30, 0x48, 0x44, 0x22, 0x22, 0x44, 0x48, 0x30},
		{0x7E, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x7E},
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}
};

void main(){
	MatrixLED_Init();
	Timer0_Init();
	while(1){

	}
}

void Timer0_Routine() interrupt 1{
	static unsigned char currentColumn;
	static unsigned int frameDelay; // 帧切换计时器
  TL0 = 0x66; // 设置定时初值
  TH0 = 0xFC; // 设置定时初值
	
	MATRIX_LED_PORT = 0xFF;
	MatrixLED_ShowColumn(currentColumn,LEDAnimation[currentFrame][currentColumn]);
	
	currentColumn++;
	if(currentColumn >= 8) currentColumn = 0;
	
	frameDelay++;
	if(frameDelay >= 100){
		frameDelay = 0;
		currentFrame++;
		if(currentFrame >= 3){
			currentFrame = 0;
		}
	}
}