#include <reg52.h>
#include <intrins.h>

// 定义数组，存放LED流水灯的所有状态
// 使用code关键字将数组定义在程序存储器（ROM）中，不占用内部RAM
unsigned char code LED_State[] = {0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F};

void Delay1ms(unsigned int xms)		//@11.0592MHz
{
	unsigned char i, j;
	while(xms){
		_nop_();
	  i = 2;
	  j = 199;
	  do
	  {
		  while (--j);
	  } while (--i);
		xms--;
	}
	
}


void main(){
	unsigned char i;
	while(1){
	  for(i = 0;i < 8;i++){
			P2 = LED_State[i];
			Delay1ms(500);
		}
	}
}