#include <reg52.h>
#include "Nixie.h"
#include "Timer0.h"
#include "Key_Int.h"
#include "AT24C02.h"

unsigned char KeyNum;
unsigned char Min,Sec,MiniSec;
unsigned char RunFlag;

void main(){
	Timer0_Init();
	while(1){
		KeyNum = Key();
		switch(KeyNum){
			case 1:{
				RunFlag = !RunFlag;
				break;
			}
			case 2:{
				Min = 0;
				Sec = 0;
				MiniSec = 0;
				break;
			}
			case 3:{
				AT24C02_WriteByte(0,Min);
				AT24C02_WriteByte(1,Sec);
				AT24C02_WriteByte(2,MiniSec);
				break;
			}
			case 4:{
				Min = AT24C02_ReadByte(0);
				Sec = AT24C02_ReadByte(1);
				MiniSec = AT24C02_ReadByte(2);
				break;
			}
		}
		Nixie_Show(1,Min/10);
		Nixie_Show(2,Min%10);
		Nixie_Show(3,11);
		Nixie_Show(4,Sec/10);
		Nixie_Show(5,Sec%10);
		Nixie_Show(6,11);
		Nixie_Show(7,MiniSec/10);
		Nixie_Show(8,MiniSec%10);
	}
}

void Sec_Loop(){
	if(RunFlag){
		MiniSec++;
		if(MiniSec >= 100){
			MiniSec = 0;
			Sec++;
			if(Sec >= 60){
				Sec = 0;
				Min++;
				if(Min >= 60){Min = 0;}
			}
		}
	}
}

void Timer0_Routine() interrupt 1{
	static unsigned int T0Count1, T0Count2, T0Count3;
  TL0 = 0x66; // 设置定时初值
  TH0 = 0xFC; // 设置定时初值
	T0Count1++;
	if(T0Count1 >= 20){
		T0Count1 = 0;
		Key_Loop();
	}
	T0Count2++;
	if(T0Count2 >= 2){
		T0Count2 = 0;
		Nixie_Loop();
	}
	T0Count3++;
	if(T0Count3 >= 10){
		T0Count3 = 0;
		Sec_Loop();
	}
}