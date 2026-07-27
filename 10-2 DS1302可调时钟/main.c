#include <reg52.h>
#include "LCD1602.h"
#include "DS1302.h"
#include "Key.h"
#include "Timer0.h"
#include "Delay.h"

unsigned char KeyNum, MODE;
unsigned char TimeSetSelect = 1; 
unsigned char TimeSetFlashFlag;
code unsigned char* WeekAbbr[] = {"Mon","Tue","Wed","Thu","Fri","Sat","Sun"};

void TimeShow();
void TimeSet();

void main(){
	LCD_Init();
	DS1302_Init();
	Timer0_Init();
	
	LCD_ShowString(1,1,"  -  -  ");
	LCD_ShowString(2,1,"  :  :  ");
	
	DS1302_SetTime();
	
	while(1){
		KeyNum = Key();
		if(KeyNum){
			if(KeyNum == 1){
				if(MODE == 0){
				  MODE = 1;
				}else if(MODE == 1){
					DS1302_WriteTime(); // 退出设置模式前，把当前修改后的时间写入芯片
					LCD_ShowString(2, 10, "  ");
					MODE = 0;
				 }
			}
		}
	  switch(MODE){
			case 0:TimeShow();break;
			case 1:TimeSet();break;
		}
	}
}

void TimeShow(){
	DS1302_ReadTime();
	LCD_ShowNum(1, 1, DS1302_Time[0], 2);
  LCD_ShowNum(1, 4, DS1302_Time[1], 2);
	LCD_ShowNum(1, 7, DS1302_Time[2], 2);
	LCD_ShowString(1,10,WeekAbbr[DS1302_Time[6]-1]);
		
	LCD_ShowNum(2, 1, DS1302_Time[3], 2);
	LCD_ShowNum(2, 4, DS1302_Time[4], 2);
	LCD_ShowNum(2, 7, DS1302_Time[5], 2);
}

void TimeSet(){
	if(KeyNum == 2){
		// 范围限制为1~6 1=年，2=月，3=日，4=时，5=分，6=秒
		TimeSetSelect++;
		if(TimeSetSelect > 6){TimeSetSelect = 1;} 
	}else if(KeyNum == 3){
		switch(TimeSetSelect){
      case 1:{
				if(DS1302_Time[0] < 99){
				  DS1302_Time[0]++;
				}else{
					DS1302_Time[0] = 0;
				 }
				DS1302_FixDate();
				DS1302_Time[6] = DS1302_CalculateWeek(DS1302_Time[0], DS1302_Time[1], DS1302_Time[2]);
				break;
			}
			case 2:{
				if(DS1302_Time[1] < 12){
				  DS1302_Time[1]++;
				}else{
					DS1302_Time[1] = 1;
					if(DS1302_Time[0] < 99){
						DS1302_Time[0]++;
					}else{
						DS1302_Time[0] = 0;
					 }
				 }
				DS1302_FixDate();
				DS1302_Time[6] = DS1302_CalculateWeek(DS1302_Time[0], DS1302_Time[1], DS1302_Time[2]);
				break;
			}
			case 3:DS1302_AddOneDay(); break;
			case 4:DS1302_AddOneHour(); break;
			case 5:DS1302_AddOneMinute(); break;
			case 6:DS1302_AddOneSecond(); break;
		}
	}else if(KeyNum == 4){
		switch(TimeSetSelect){
      case 1:{
				if(DS1302_Time[0] > 0){
					DS1302_Time[0]--;
				}else{
					DS1302_Time[0] = 99;
				 }
				DS1302_FixDate();
				DS1302_Time[6] = DS1302_CalculateWeek(DS1302_Time[0], DS1302_Time[1], DS1302_Time[2]);
			break;
			}
			case 2:{
				if(DS1302_Time[1] > 1){
				  DS1302_Time[1]--;
			  }else{
				  DS1302_Time[1] = 12;
					if(DS1302_Time[0] > 0){
					  DS1302_Time[0]--;
				  }else{
					  DS1302_Time[0] = 99;
				   }
				 }
				DS1302_FixDate();
				DS1302_Time[6] = DS1302_CalculateWeek(DS1302_Time[0], DS1302_Time[1], DS1302_Time[2]);
				break;
			}
			case 3:DS1302_SubOneDay(); break;
			case 4:DS1302_SubOneHour(); break;
			case 5:DS1302_SubOneMinute(); break;
			case 6:DS1302_SubOneSecond(); break;
	  }
	}
	
	if(TimeSetSelect == 1 && TimeSetFlashFlag == 1){
	  LCD_ShowString(1,1,"  ");
	}else{
		LCD_ShowNum(1, 1, DS1302_Time[0], 2);
	 }
	if(TimeSetSelect == 2 && TimeSetFlashFlag == 1){
	  LCD_ShowString(1,4,"  ");
	}else{
		LCD_ShowNum(1, 4, DS1302_Time[1], 2);
	 }
	if(TimeSetSelect == 3 && TimeSetFlashFlag == 1){
	  LCD_ShowString(1,7,"  ");
	}else{
		LCD_ShowNum(1, 7, DS1302_Time[2], 2);
	 }
	if(TimeSetSelect == 4 && TimeSetFlashFlag == 1){
	  LCD_ShowString(2,1,"  ");
	}else{
		LCD_ShowNum(2, 1, DS1302_Time[3], 2);
	 }
	if(TimeSetSelect == 5 && TimeSetFlashFlag == 1){
	  LCD_ShowString(2,4,"  ");
	}else{
		LCD_ShowNum(2, 4, DS1302_Time[4], 2);
	 }
	if(TimeSetSelect == 6 && TimeSetFlashFlag == 1){
	  LCD_ShowString(2,7,"  ");
	}else{
		LCD_ShowNum(2, 7, DS1302_Time[5], 2);
	 }
	
  LCD_ShowString(1,10,WeekAbbr[DS1302_Time[6]-1]);	
}

void Timer0_Routine() interrupt 1{
	static unsigned int T0Count;
  TL0 = 0x66; // 设置定时初值
  TH0 = 0xFC; // 设置定时初值
	T0Count++;
	if(T0Count >= 1000/2){
		T0Count = 0;
		TimeSetFlashFlag = !TimeSetFlashFlag;
	}
}