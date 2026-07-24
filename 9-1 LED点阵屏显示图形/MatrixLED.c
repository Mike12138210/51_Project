#include <reg52.h>
#include "74HC595.h"

#define MATRIX_LED_PORT P0

/**
  * @brief LED点阵屏显示一列数据
  * @param Column 要选择的列，范围：0~7，0在最左边
  * @param Data 选择列所显示的数据，高位在上，1为亮，0为灭
  * @retval 无
  */
void MatrixLED_ShowColumn(unsigned char Column,unsigned char Data){
	_74HC595_WriteByte(Data);
	MATRIX_LED_PORT = ~(0x80>>Column);
}