#include <reg52.h>
#include "UART.h"

void UART_Routine();

void main(){
	UART_Init();
	while(1){
		
	}
}

void UART_Routine() interrupt 4{
	if(RI == 1){
		P2 = ~SBUF;
		UART_SendByte(SBUF);
		RI = 0;
	}
}