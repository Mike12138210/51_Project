#include <reg52.h>
#include "Delay.h"
#include "LCD1602.h"
#include "Timer0.h"
#include "Key.h"

unsigned char Sec,Min,Hour;
unsigned char KeyNum;
bit PauseFlag = 0;
bit PauseDisplayFlag = 0;

void main(){
	LCD_Init();
	Timer0_Init();
	LCD_ShowString(1,1,"Clock:"); 
	
	while(1){
		KeyNum = Key();
		if(KeyNum == 1){
			PauseFlag = !PauseFlag;
			PauseDisplayFlag = PauseFlag;
			KeyNum = 0;
		}
		
		LCD_ShowNum(2,1,Hour,2);
		LCD_ShowChar(2,3,':');
		LCD_ShowNum(2,4,Min,2);
		LCD_ShowChar(2,6,':');
		LCD_ShowNum(2,7,Sec,2);
		
		if(PauseDisplayFlag){
			LCD_ShowString(1,12,"Pause");
		}else{
			LCD_ShowString(1,12,"     ");
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
		if(PauseFlag == 0){
		  Sec++;
		  if(Sec >= 60){
			  Sec = 0;
			  Min++;
				if(Min >= 60){
			    Min = 0;
			    Hour++;
					if(Hour >= 24) Hour = 0;
		    }
		  }
		}
	}
}