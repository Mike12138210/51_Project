#include <reg52.h>
#include "Delay.h"

sbit C = P2^4;  // 将P2^4命名为C
sbit B_PIN = P2^3;
sbit A = P2^2;

unsigned char NixieBuff[9] = {0,10,10,10,10,10,10,10,10};

unsigned char NixieTable[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 
	                            0x6D, 0x7D, 0x07, 0x7F, 0x6F,
                              0x00, 0x40}; 
                              // 0,1,2,3,4,5,6,7,8,9,空,-

/**
  * @brief  向显示缓冲区写入数据
  * @param  Location 要写入的位置（1~8）
  * @param  Number   要显示的数字（0~9，或10=空，11=横杠）
  * @retval 无
  * @note   此函数仅更新缓冲区，实际显示由定时器中断中的 Nixie_Loop() 完成
  */
void Nixie_Show(unsigned char Location,unsigned char Number){
	NixieBuff[Location] = Number;
}
		
/**
  * @brief  扫描并显示一位数码管
  * @param  Location 要扫描的位置（1~8）
  * @param  Number   该位置要显示的数字（0~9，或10=空，11=横杠）
  * @retval 无
  */
void Nixie_Scan(unsigned char Location,unsigned char Number){
	P0 = 0x00; // 清空（消隐）
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
}

/**
  * @brief  数码管动态扫描函数（由定时器中断调用）
  * @param  无
  * @retval 无
  */
void Nixie_Loop(){
	static unsigned char i = 1;
	Nixie_Scan(i,NixieBuff[i]);
	i++;
	if(i > 8){i = 1;}
}