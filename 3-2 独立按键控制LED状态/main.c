#include <reg52.h>
#include <intrins.h>

sbit LED1 = P2^0;  // 将P2.0命名为LED1
sbit LED2 = P2^1;
sbit LED3 = P2^2;
sbit LED4 = P2^3;
sbit LED5 = P2^4;
sbit LED6 = P2^5;
sbit LED7 = P2^6;
sbit LED8 = P2^7;

void Delay(unsigned int xms)		//@11.0592MHz
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
		while(1){
			LED1 = 0; // 点亮
			Delay(500);
			LED1 = 1; // 熄灭
			Delay(500);
		}
}