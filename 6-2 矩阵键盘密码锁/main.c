#include <reg52.h>
#include "Delay.h"
#include "LCD1602.h"
#include "MatrixKey.h"

unsigned char KeyNum;
unsigned int Password,Count;

void main(){
	LCD_Init();
	LCD_ShowString(1,1,"Password:");
	while(1){
		KeyNum = MatrixKey();
		if(KeyNum){
			if(KeyNum <= 10){
				if(Count < 4){
					unsigned char digit = KeyNum % 10;
					Password = Password * 10 + digit; // 密码左移一位
					Count++;
				}
				LCD_ShowNum(2,1,Password,Count);
				if(Count < 4){
					LCD_ShowNum(2,1+Count,0,4-Count); // 覆盖右侧未输入位
				}
			}
			
			if(KeyNum == 11){ // s11，确认
				if(Count == 4 && Password == 2345){
					LCD_ShowString(1,14," OK");
				}else{
					LCD_ShowString(1,14,"ERR");
				}
				Password = 0;
				Count = 0;
				LCD_ShowNum(2,1,Password,4);
			}
			
			if(KeyNum == 12){ // s12，退格
				if(Count > 0){
					Password = Password / 10;
					Count--;
					
				}
				if(Count == 0){
				  LCD_ShowNum(2,1,0,1);
				}else{
					LCD_ShowNum(2,1,Password,Count);
				}
				if(Count < 4){
					LCD_ShowNum(2,1+Count,0,4-Count);
				}
			}
		}
	}
}