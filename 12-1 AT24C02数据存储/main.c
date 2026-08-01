#include <reg52.h>
#include "LCD1602.h"
#include "Delay.h"
#include "Key.h"
#include "AT24C02.h"

unsigned char KeyNum;
unsigned int Num;

void main(){
	LCD_Init();
	LCD_ShowNum(1,1,Num,5);
	while(1){
		KeyNum = Key();
		switch(KeyNum){
			case 1:{
				Num++;
				LCD_ShowNum(1,1,Num,5);
				break;
			}
			case 2:{
				Num--;
				LCD_ShowNum(1,1,Num,5);
				break;
			}
			case 3:{
				AT24C02_WriteByte(0,Num%256);
				AT24C02_WriteByte(1,Num/256);
				LCD_ShowString(2,1,"Write OK");
				Delay(1000);
				LCD_ShowString(2,1,"        ");
				break;
			}
			case 4:{
				Num = AT24C02_ReadByte(0);
				Num |= AT24C02_ReadByte(1)<<8;
				LCD_ShowNum(1,1,Num,5);
				LCD_ShowString(2,1,"Read OK");
				Delay(1000);
				LCD_ShowString(2,1,"        ");
				break;
			}
		}
	}
}