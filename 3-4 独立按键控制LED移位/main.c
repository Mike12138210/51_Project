#include <reg52.h>
#include <intrins.h>

sbit LED1 = P2^0;  // 将P2.0命名为LED1（最左边）
sbit LED8 = P2^7;

unsigned char LEDNum; // 全局变量默认为0
bit isFirst = 1; // 首次标志，1表示尚未显示初始灯

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
		// 右移
		if(TXD == 0){ // sbit TXD   = P3^1;
			Delay(20);
			while(TXD == 0);
			Delay(20);

			if(isFirst){
				P2 = ~(0x01 << LEDNum); // LEDNum=0，显示0xFE
				isFirst = 0;
			}else{
				if(LEDNum == 7){
					LEDNum = 0;
				}else{
					LEDNum++;
				}
			P2 = ~(0x01 << LEDNum);
			}
		}
		
		// 左移
		if(RXD == 0){ // sbit RXD   = P3^0;
			Delay(20);
			while(RXD == 0);
			Delay(20);
		
				if(isFirst){
					P2 = ~(0x01 << LEDNum); // LEDNum = 0，显示0xFE
					isFirst = 0;
				}else{
					if(LEDNum == 0){
						LEDNum = 7;
					}else{
						LEDNum--;
					}
					P2 = ~(0x01 << LEDNum);
				}
		}
	}
}