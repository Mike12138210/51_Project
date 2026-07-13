#include <reg52.h>

sbit LED1 = P2^0;  // 将P2.0命名为LED1
sbit LED2 = P2^1;
sbit LED3 = P2^2;
sbit LED4 = P2^3;
sbit LED5 = P2^4;
sbit LED6 = P2^5;
sbit LED7 = P2^6;
sbit LED8 = P2^7;

void Delay(unsigned int t){ while(t--); } // 简单延时

void main(){
	while(1){
		if(TXD == 0){          // 检测到按下
      Delay(1000);       // 延时约10ms,跳过抖动
      if(TXD == 0){      // 再次确认确实按下了
        LED1 = 0;
        LED2 = 0;
      }else{
        // 松开后熄灭
        LED1 = 1;
        LED2 = 1;
        Delay(1000);
      } 
//		if(TXD == 0){ // sbit TXD = P3^1;
//			LED1 = 0; // 点亮
//		}else{
//		  LED1 = 1; // 熄灭
//		}
	}
}