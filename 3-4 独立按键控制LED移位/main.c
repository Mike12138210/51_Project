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

unsigned char LEDNum; // 全局变量默认为0

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
		if(TXD == 0){ // sbit TXD   = P3^1;
			Delay(20);
			while(TXD == 0);
			Delay(20);

			if(LEDNum == 8){
				LEDNum = 0;
			}
			P2 = ~(0x01<<LEDNum);
			LEDNum++;
		}
		if(RXD == 0){ // sbit RXD   = P3^0;
			Delay(20);
			while(RXD == 0);
			Delay(20);

			if(LEDNum == 0){
				LEDNum = 7;
			}else{
				LEDNum--;
			}
			P2 = ~(0x01<<LEDNum);
		}
	}
}