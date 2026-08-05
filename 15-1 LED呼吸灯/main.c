#include <reg52.h>

sbit LED = P2^0;

#define CYCLE 100

void Delay(unsigned int t);

void main(){
	unsigned char Time, i;
	while(1){
		for(Time = 0;Time < CYCLE;Time++){
			for(i = 0;i < 20;i++){
				LED = 0;
				Delay(Time);
				LED = 1;
				Delay(CYCLE-Time);
			}
		}
		for(Time = CYCLE;Time > 0;Time--){
			for(i = 0;i < 20;i++){
				LED = 0;
				Delay(Time);
				LED = 1;
				Delay(CYCLE-Time);
			}
		}
	}
}

void Delay(unsigned int t){
	while(t--);
}