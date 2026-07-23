#include <reg52.h>
#include "UART.h"
#include "Timer0.h"

void Timer0_Routine();

unsigned char Sec;
bit SendFlag = 0;

void main(){
	UART_Init();
	Timer0_Init();
	while(1){
		if(SendFlag){
			SendFlag = 0;
		  UART_SendByte(Sec);
		  Sec++;
		}
	}
}

void Timer0_Routine() interrupt 1{
	static unsigned int T0Count;
  TL0 = 0x66; // 设置定时初值
  TH0 = 0xFC; // 设置定时初值
	T0Count++;
	if(T0Count >= 1000){
		T0Count = 0;
		SendFlag = 1;
	}
}