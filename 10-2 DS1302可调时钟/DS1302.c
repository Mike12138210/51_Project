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

/**
  * @brief  根据年/月/日计算星期（基姆拉尔森公式）
  * @param  year  年份（如 26 表示 2026年）
  * @param  month 月份（1~12）
  * @param  day   日期（1~31）
  * @retval 星期值，1~7（1表示周一，7表示周日）
  */
unsigned char DS1302_CalculateWeek(unsigned char Year,unsigned char Month,unsigned char Day){
    unsigned int year = 2000 + Year; // 转换为完整年份
    unsigned char month = Month;
    unsigned char day = Day;
    unsigned char week;
    
    // 将 1月、2月 视为上一年的 13月、14月
    if(month == 1 || month == 2){
        month += 12;
        year--;
    }
    
    week = (day + 2*month + 3*(month+1)/5 + year + year/4 - year/100 + year/400 + 1) % 7;
    
    // 转换结果：0（周日）→ 7，1~6 保持不变
    if(week == 0) week = 7;
    return week;
}

/**
  * @brief  将 DS1302_Time[] 数组中的时间写入 DS1302 芯片
  * @param  无
  * @retval 无
  */
void DS1302_WriteTime(){
	DS1302_Time[6] = DS1302_CalculateWeek(DS1302_Time[0],DS1302_Time[1],DS1302_Time[2]);
	
    DS1302_WriteByte(DS1302_WP, 0x00); // 关闭写保护
    DS1302_WriteByte(DS1302_YEAR, DS1302_DecToBCD(DS1302_Time[0]));
    DS1302_WriteByte(DS1302_MONTH, DS1302_DecToBCD(DS1302_Time[1]));
    DS1302_WriteByte(DS1302_DATE, DS1302_DecToBCD(DS1302_Time[2]));
    DS1302_WriteByte(DS1302_HOUR, DS1302_DecToBCD(DS1302_Time[3]));
    DS1302_WriteByte(DS1302_MINUTE, DS1302_DecToBCD(DS1302_Time[4]));
    DS1302_WriteByte(DS1302_SECOND, DS1302_DecToBCD(DS1302_Time[5]));
    DS1302_WriteByte(DS1302_DAY, DS1302_DecToBCD(DS1302_Time[6]));
    DS1302_WriteByte(DS1302_WP, 0x80); // 打开写保护
}

/**
  * @brief  获取指定月份的天数（考虑闰年）
  * @param  year  年份（如 26 表示 2026年）
  * @param  month 月份（1~12）
  * @retval 该月的天数（28~31）
  */
unsigned char DS1302_GetDaysInMonth(unsigned char year, unsigned char month){
    unsigned char days;
    switch(month){
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            days = 31; break;
        case 4: case 6: case 9: case 11:
            days = 30; break;
        case 2:
            // 判断闰年：年份能被4整除且不能被100整除，或者能被400整除
            if((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)){
                days = 29;
            } else {
                days = 28;
            }
            break;
        default: days = 0; break;
    }
    return days;
}

/**
  * @brief  日期加一天（自动处理月、年进位）
  * @param  无
  * @retval 无
  */
void DS1302_AddOneDay(){
    unsigned char maxDay = DS1302_GetDaysInMonth(DS1302_Time[0], DS1302_Time[1]);
    if(DS1302_Time[2] < maxDay){
        DS1302_Time[2]++;
    } else {
        DS1302_Time[2] = 1;
        if(DS1302_Time[1] < 12){
            DS1302_Time[1]++;
        } else {
            DS1302_Time[1] = 1;
            if(DS1302_Time[0] < 99)
                DS1302_Time[0]++;
            else
                DS1302_Time[0] = 0;
        }
    }
    DS1302_Time[6] = DS1302_CalculateWeek(DS1302_Time[0], DS1302_Time[1], DS1302_Time[2]);
}

/**
  * @brief  日期减一天（自动处理月、年借位）
  * @param  无
  * @retval 无
  */
void DS1302_SubOneDay(){
    if(DS1302_Time[2] > 1){
        DS1302_Time[2]--;
    } else {
        if(DS1302_Time[1] > 1){
            DS1302_Time[1]--;
        } else {
            DS1302_Time[1] = 12;
            if(DS1302_Time[0] > 0)
                DS1302_Time[0]--;
            else
                DS1302_Time[0] = 99;
        }
        DS1302_Time[2] = DS1302_GetDaysInMonth(DS1302_Time[0], DS1302_Time[1]);
    }
    DS1302_Time[6] = DS1302_CalculateWeek(DS1302_Time[0], DS1302_Time[1], DS1302_Time[2]);
}

/**
  * @brief  小时加1（自动进位到天）
  * @param  无
  * @retval 无
  */
void DS1302_AddOneHour(){
    if(DS1302_Time[3] < 23){
        DS1302_Time[3]++;
    } else {
        DS1302_Time[3] = 0;
        DS1302_AddOneDay();  // 进位到天
    }
}

/**
  * @brief  小时减1（自动借位到天）
  * @param  无
  * @retval 无
  */
void DS1302_SubOneHour(){
    if(DS1302_Time[3] > 0){
        DS1302_Time[3]--;
    } else {
        DS1302_Time[3] = 23;
        DS1302_SubOneDay();  // 借位到天
    }
}

/**
  * @brief  分钟加1（自动进位到小时）
  * @param  无
  * @retval 无
  */
void DS1302_AddOneMinute(){
    if(DS1302_Time[4] < 59){
        DS1302_Time[4]++;
    } else {
        DS1302_Time[4] = 0;
        DS1302_AddOneHour();  // 进位到小时
    }
}

/**
  * @brief  分钟减1（自动借位到小时）
  * @param  无
  * @retval 无
  */
void DS1302_SubOneMinute(){
    if(DS1302_Time[4] > 0){
        DS1302_Time[4]--;
    } else {
        DS1302_Time[4] = 59;
        DS1302_SubOneHour();  // 借位到小时
    }
}

/**
  * @brief  秒加1（自动进位到分钟）
  * @param  无
  * @retval 无
  */
void DS1302_AddOneSecond(){
    if(DS1302_Time[5] < 59){
        DS1302_Time[5]++;
    } else {
        DS1302_Time[5] = 0;
        DS1302_AddOneMinute();  // 进位到分钟
    }
}

/**
  * @brief  秒减1（自动借位到分钟）
  * @param  无
  * @retval 无
  */
void DS1302_SubOneSecond(){
    if(DS1302_Time[5] > 0){
        DS1302_Time[5]--;
    } else {
        DS1302_Time[5] = 59;
        DS1302_SubOneMinute();  // 借位到分钟
    }
}

/**
  * @brief  修正日期，确保日期不超过当月最大天数
  * @param  无
  * @retval 无
  */
void DS1302_FixDate(){
    unsigned char maxDay = DS1302_GetDaysInMonth(DS1302_Time[0], DS1302_Time[1]);
    if(DS1302_Time[2] > maxDay){
        DS1302_Time[2] = maxDay;
    }
}