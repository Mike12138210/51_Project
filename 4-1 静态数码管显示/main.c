#include <reg52.h>

sbit C = P2^4;  // ½«P2.4ÃüÃûÎªC
sbit B_PIN = P2^3;
sbit A = P2^2;

void main(){
	C = 1;
	B_PIN = 0;
	A = 1;
	P0 = 0x7D;
	while(1){
		
	}
}