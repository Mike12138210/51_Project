#include <reg52.h>

sfr AUXR = 0x8E;   // STC89C52RC 的 AUXR 寄存器地址

void UART_Init(){  //4800bps@11.0592MHz
	SCON = 0x40;
	PCON |= 0x80;
	
	// 配置定时器1
	AUXR &= 0x7F; // 定时器时钟12T模式（STC系列特有，保持兼容）
  TMOD &= 0x0F; // 保留高4位清零，低4位不变
  TMOD |= 0x20; // 设置定时器1为8位自动重装模式
	TL1 = 0xF4;		//设定定时初值
	TH1 = 0xF4;		//设定定时器重装值
	ET1 = 0;		  //禁止定时器1中断
	TR1 = 1;		  //启动定时器1
}

void UART_SendByte(unsigned char Byte){
	SBUF = Byte;
	while(TI == 0);
	TI = 0;
}