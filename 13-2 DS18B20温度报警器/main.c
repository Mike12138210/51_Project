#include <reg52.h>
#include "LCD1602.h"
#include "Delay.h"
#include "AT24C02.h"
#include "Key_Int.h"
#include "DS18B20.h"
#include "Timer0.h"
#include "Buzzer.h"

#define THDefault 20
#define TLDefault 15

float T, TShow;
char TLow, THigh;
unsigned char KeyNum;

void main(){
	DS18B20_ConvertT();
	Delay(1000);
	THigh = AT24C02_ReadByte(0);
	TLow = AT24C02_ReadByte(1);
	if(THigh > 125 || TLow < -55 || THigh <= TLow){
		THigh = THDefault;
		TLow = TLDefault;
	}
	
	LCD_Init();
	LCD_ShowString(1,1,"T:");
	LCD_ShowString(2,1,"TH:");
	LCD_ShowString(2,9,"TL:");
	LCD_ShowSignedNum(2,4,THigh,3);
	LCD_ShowSignedNum(2,12,TLow,3);
	Timer0_Init();
	
	while(1){
		KeyNum = Key();
		/*温度读取及显示*/
		DS18B20_ConvertT();
		Delay(750);
		T = DS18B20_ReadT();
		if(T < 0){
			LCD_ShowChar(1,3,'-');
			TShow = -T;
		}else{
			LCD_ShowChar(1,3,'+');
			TShow = T;
		 }
		LCD_ShowNum(1,4,TShow,3);
		LCD_ShowChar(1,7,'.');
		LCD_ShowNum(1,8,(unsigned long)(TShow*100)%100,2);
		 
		/*阈值判断及显示*/
		if(KeyNum){
			switch(KeyNum){
				case 1:{THigh++; if(THigh > 125){THigh = 125;} break;}
				case 2:{THigh--; if(THigh <= TLow){THigh++;} break;}
				case 3:{TLow++; if(TLow >= THigh){TLow--;} break;}
				case 4:{TLow--; if(TLow < -55){TLow = -55;} break;}
			}
			LCD_ShowSignedNum(2,4,THigh,3);
		  LCD_ShowSignedNum(2,12,TLow,3);
			AT24C02_WriteByte(0,THigh);
			AT24C02_WriteByte(1,TLow);
		}
		if(T > THigh){
			LCD_ShowString(1,13,"OV:H");
			Buzzer_Time(100);
		}else if(T < TLow){
			LCD_ShowString(1,13,"OV:L");
			Buzzer_Time(100);
		 }else{
			 LCD_ShowString(1,13,"    ");
		  }
	}
}

void Timer0_Routine() interrupt 1{
	static unsigned int T0Count;
  TL0 = 0x66; // 设置定时初值
  TH0 = 0xFC; // 设置定时初值
	T0Count++;
	if(T0Count >= 20){
		T0Count = 0;
		Key_Loop();
	}
}