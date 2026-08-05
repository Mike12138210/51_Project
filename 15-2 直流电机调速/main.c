#include <reg52.h>
#include "Delay.h"
#include "Key_Int.h"
#include "Nixie.h"
#include "Timer0.h"

sbit Motor = P1^0;

unsigned char Counter, Compare;
unsigned char KeyNum, Speed;

void main(){
	Timer0_Init();
	while(1){
		KeyNum = Key();
		if(KeyNum == 1){
			Speed++;
			if(Speed >= 4){Speed = 0;}
			switch(Speed){
				case 0: Compare = 0; break;
				case 1: Compare = 50; break;
				case 2: Compare = 75; break;
				case 3: Compare = 100; break;
				default: Compare = 0;
			}
		}
		Nixie_Show(1,Speed);
	}
}

void Timer0_Routine() interrupt 1{
	static unsigned int T0Count1, T0Count2;
  TL0 = 0xA4; // 设置定时初值
  TH0 = 0xFF; // 设置定时初值
	
	// PWM控制（每0.1ms执行）
	Counter++;
	if(Counter >= 100) Counter = 0;
	if(Counter < Compare){
		Motor = 1;
	}else{
		Motor = 0;
	 }
	
	// 按键扫描（每10ms执行）
	T0Count1++;
	if(T0Count1 >= 100){ // 0.1ms * 100 = 10ms
		T0Count1 = 0;
		Key_Loop();
	}
	
	// 数码管扫描（每2ms执行）
	T0Count2++;
	if(T0Count2 >= 20){ // 0.1ms * 20 = 2ms
		T0Count2 = 0;
		Nixie_Loop();
	}
}