#include <reg52.h>
#include "Timer0.h"
#include "MatrixLED.h"

#define MATRIX_LED_PORT P0

unsigned int offset; // 当前滑动窗口的起始位置（从0开始）

// 存储图像帧数据
unsigned char code StringData[] = {
	 0x00,0xFF,0x08,0x08,0x08,0xFF,0x00,0x0E,0x15,0x15,0x09,0x00,0x00,0xFE,0x01,0x02,
   0x00,0xFE,0x01,0x02,0x00,0x0E,0x11,0x11,0x11,0x0E,0x00,0x7D,0x00,0x00,0x00,0x00
};

#define STRING_COLS 32 // 字符的列数
#define DISPLAY_WIDTH 8 // 点阵屏列数
#define TOTAL_COLS (STRING_COLS + DISPLAY_WIDTH) // 总列数

void main(){
	MatrixLED_Init();
	Timer0_Init();
	while(1){

	}
}

void Timer0_Routine() interrupt 1{
	static unsigned char currentColumn;
	static unsigned int scrollDelay; // 滑动计时器
  TL0 = 0x66; // 设置定时初值
  TH0 = 0xFC; // 设置定时初值
	
	MATRIX_LED_PORT = 0xFF;
	MatrixLED_ShowColumn(currentColumn,StringData[(offset + currentColumn) % STRING_COLS]);
	
	currentColumn++;
	if(currentColumn >= 8) currentColumn = 0;
	
	scrollDelay++;
	if(scrollDelay >= 150){
		scrollDelay = 0;
		offset++; // 窗口向右滑动
		if(offset >= STRING_COLS){
			offset = 0;
		}
	}
}