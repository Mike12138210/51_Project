#include <reg52.h>

sbit DS1302_SCLK = P3^6;
sbit DS1302_IO = P3^4;
sbit DS1302_CE = P3^5;

#define DS1302_SECOND 0x80
#define DS1302_MINUTE 0x82
#define DS1302_HOUR 0x84
#define DS1302_DATE 0x86
#define DS1302_MONTH 0x88
#define DS1302_DAY 0x8A
#define DS1302_YEAR 0x8C
#define DS1302_WP 0x8E

unsigned char DS1302_Time[] = {26,7,26,20,37,55,7}; // 年 月 日 时 分 秒 星期

/**
  * @brief  DS1302初始化
  * @param  无
  * @retval 无
  */
void DS1302_Init(){
	DS1302_CE = 0;
	DS1302_SCLK = 0;
}

/**
  * @brief  将十进制数转换为BCD码（用于写入芯片）
  * @param  Dec 要转换的十进制数，范围：0~99
  * @retval BCD码
  */
static unsigned char DS1302_DecToBCD(unsigned char Dec){
	return (Dec / 10 * 16 + Dec % 10);
}

/**
  * @brief  将BCD码转换为十进制数（用于读取芯片）
  * @param  BCD 要转换的BCD码
  * @retval 十进制数
  */
static unsigned char DS1302_BCDToDec(unsigned char BCD){
	return (BCD / 16 * 10 + BCD % 16);
}

/**
  * @brief  DS1302写入一个字节
  * @param  Command 要写入的命令
  * @param  Data    要写入的数据
  * @retval 无
  */
void DS1302_WriteByte(unsigned char Command,unsigned char Data){
	unsigned char i;
	DS1302_CE = 1;
	for(i = 0;i < 8;i++){
	  DS1302_IO = Command & (0x01<<i); // 依次取出8位数据的每一位
	  DS1302_SCLK = 1;
	  DS1302_SCLK = 0;
	}
	for(i = 0;i < 8;i++){
	  DS1302_IO = Data & (0x01<<i); // 依次取出8位数据的每一位
	  DS1302_SCLK = 1;
	  DS1302_SCLK = 0;
	}
	DS1302_CE = 0;
}

/**
  * @brief  DS1302读取一个字节
  * @param  Command 要发送的命令
  * @retval 读出的数据
  */
unsigned char DS1302_ReadByte(unsigned char Command){
	unsigned char i, Data = 0x00;
	DS1302_CE = 1;
	for(i = 0;i < 8;i++){
	  DS1302_IO = Command & (0x01<<i); // 依次取出8位数据的每一位
	  DS1302_SCLK = 0;
	  DS1302_SCLK = 1;
	}
	for(i = 0;i < 8;i++){
	  DS1302_SCLK = 1;
	  DS1302_SCLK = 0;
	  if(DS1302_IO){Data |= (0x01<<i);} // 将Data每一位依次置一
	}
	DS1302_CE = 0;
	DS1302_IO = 0;
	return Data;
}

/**
  * @brief  设置DS1302内部时间
  * @note   此函数会将时间写入芯片内部，如需保持时间，
  *         烧录完程序后应将其注释掉，防止每次上电都重置时间。
  * @param  无
  * @retval 无
  */
void DS1302_SetTime(){
	DS1302_WriteByte(DS1302_WP,0x00); // 关闭写保护
	DS1302_WriteByte(DS1302_YEAR,DS1302_DecToBCD(DS1302_Time[0]));
	DS1302_WriteByte(DS1302_MONTH,DS1302_DecToBCD(DS1302_Time[1]));
	DS1302_WriteByte(DS1302_DATE,DS1302_DecToBCD(DS1302_Time[2]));
	DS1302_WriteByte(DS1302_HOUR,DS1302_DecToBCD(DS1302_Time[3]));
	DS1302_WriteByte(DS1302_MINUTE,DS1302_DecToBCD(DS1302_Time[4]));
	DS1302_WriteByte(DS1302_SECOND,DS1302_DecToBCD(DS1302_Time[5]));
	DS1302_WriteByte(DS1302_DAY,DS1302_DecToBCD(DS1302_Time[6]));
	DS1302_WriteByte(DS1302_WP,0x80); // 打开写保护
}

/**
  * @brief  从DS1302读取当前时间并存入DS1302_Time数组
  * @param  无
  * @retval 无
  */
void DS1302_ReadTime(){
	unsigned char Temp;
	Temp = DS1302_ReadByte(DS1302_YEAR + 1);
	DS1302_Time[0] = DS1302_BCDToDec(Temp);
	Temp = DS1302_ReadByte(DS1302_MONTH + 1);
	DS1302_Time[1] = DS1302_BCDToDec(Temp);
	Temp = DS1302_ReadByte(DS1302_DATE + 1);
	DS1302_Time[2] = DS1302_BCDToDec(Temp);
	Temp = DS1302_ReadByte(DS1302_HOUR + 1);
	DS1302_Time[3] = DS1302_BCDToDec(Temp);
	Temp = DS1302_ReadByte(DS1302_MINUTE + 1);
	DS1302_Time[4] = DS1302_BCDToDec(Temp);
	Temp = DS1302_ReadByte(DS1302_SECOND + 1);
	DS1302_Time[5] = DS1302_BCDToDec(Temp);
	Temp = DS1302_ReadByte(DS1302_DAY + 1);
	DS1302_Time[6] = DS1302_BCDToDec(Temp);
}