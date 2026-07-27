#ifndef __DS1302_H__
#define __DS1302_H__

extern unsigned char DS1302_Time[];

void DS1302_Init();
void DS1302_WriteByte(unsigned char Command,unsigned char Data);
unsigned char DS1302_ReadByte(unsigned char Command);
void DS1302_SetTime();
void DS1302_ReadTime();
unsigned char DS1302_CalculateWeek(unsigned char Year,unsigned char Month,unsigned char Day);
void DS1302_WriteTime();
unsigned char DS1302_GetDaysInMonth(unsigned char year, unsigned char month);
void DS1302_AddOneDay();
void DS1302_SubOneDay();
void DS1302_AddOneHour();
void DS1302_SubOneHour();
void DS1302_AddOneMinute();
void DS1302_SubOneMinute();
void DS1302_AddOneSecond();
void DS1302_SubOneSecond();
void DS1302_FixDate();

#endif