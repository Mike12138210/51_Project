#include <reg52.h>
#include "Delay.h"

sbit C = P2^4;  // 将P2^4命名为C
sbit B_PIN = P2^3;
sbit A = P2^2;

unsigned char NixieTable[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 
	                             0x6D, 0x7D, 0x07, 0x7F, 0x6F}; 
                              // 0,1,2,3,4,5,6,7,8,9

void Nixie(unsigned char Location,unsigned char Number){
	switch(Location){
		case 1:C = 1; B_PIN = 1; A = 1; break; // 111->7，对应Y7，LED8（最左边）
		case 2:C = 1; B_PIN = 1; A = 0; break;
		case 3:C = 1; B_PIN = 0; A = 1; break;
		case 4:C = 1; B_PIN = 0; A = 0; break;
		case 5:C = 0; B_PIN = 1; A = 1; break;
		case 6:C = 0; B_PIN = 1; A = 0; break;
		case 7:C = 0; B_PIN = 0; A = 1; break;
		case 8:C = 0; B_PIN = 0; A = 0; break;
	}
	P0 = NixieTable[Number];
	Delay(1);
	P0 = 0x00; // 清空
}