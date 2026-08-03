#include <reg52.h>
#include "OneWire.h"

#define DS18B20_SKIP_ROM         0xCC
#define DS18B20_CONVERT_T        0x44
#define DS18B20_READ_SCRATCCHPAD 0xBE

void DS18B20_ConvertT(){
	OneWire_Init();
	OneWire_SendByte(DS18B20_SKIP_ROM);
	OneWire_SendByte(DS18B20_CONVERT_T);
}

float DS18B20_ReadT(){
	unsigned char TLSB, TMSB;
	int Temp;
	float T;
	OneWire_Init();
	OneWire_SendByte(DS18B20_SKIP_ROM);
	OneWire_SendByte(DS18B20_READ_SCRATCCHPAD);
	TLSB = OneWire_ReceiveByte();
	TMSB = OneWire_ReceiveByte();
	Temp = (TMSB<<8) | TLSB;
	T = Temp * 0.0625;
	return T;
}