#include <reg52.h>
sfr AUXR = 0x8E;   // STC89C52RC 的 AUXR 寄存器地址

/**
  * @brief 定时器0初始化 1毫秒 @ 11.0592MHz
  * @param 无
  * @retval 无
  */
void Timer0_Init(){
    AUXR &= 0x7F;        // 定时器时钟12T模式（STC系列特有，保持兼容）
    TMOD &= 0xF0;  // 保留高4位不变，低4位清零
    TMOD |= 0x01;  // 设置定时器0为模式1
    TL0 = 0x66;         // 设置定时初值（软件计算的精确值）
    TH0 = 0xFC;         // 设置定时初值（软件计算的精确值）
    TF0 = 0;            // 清除TF0标志
    TR0 = 1;            // 定时器0开始计时
    
    ET0 = 1;            // 开启定时器0中断
    EA = 1;             // 开启总中断
	  PT0 = 0;            // 优先级默认为0
}

/* 定时器中断函数模板
void Timer0_Routine() interrupt 1{
	static unsigned int T0Count;
  TL0 = 0x66; // 设置定时初值
  TH0 = 0xFC; // 设置定时初值
	T0Count++;
	if(T0Count >= 1000/2){
		T0Count = 0;
		
	}
}
*/