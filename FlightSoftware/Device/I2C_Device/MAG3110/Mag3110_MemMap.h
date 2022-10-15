#ifndef MAG3110_MemMap_H
#define MAG3110_MemMap_H
namespace MAG3110Map
{
	static const unsigned int deviceId = 0x0E;
	static const unsigned int DR_STATUS = 0x00;// 0x01 0000 0000 Data ready status per axis
	static const unsigned int OUT_X_MSB = 0x01;// 0x02 (0x03) data Bits[15:8] of X measurement
	static const unsigned int OUT_X_LSB = 0x02;// 0x03 data Bits[7:0] of X measurement
	static const unsigned int OUT_Y_MSB = 0x03;// 0x04 (0x05) data Bits[15:8] of Y measurement
	static const unsigned int OUT_Y_LSB = 0x04;// 0x05 data Bits[7:0] of Y measurement
	static const unsigned int OUT_Z_MSB = 0x05;// 0x06 (0x07) data Bits[15:8] of Z measurement
	static const unsigned int OUT_Z_LSB = 0x06;// 0x07 data Bits[7:0] of Z measurement
	static const unsigned int WHO_AM_I = 0x07;// 0x08 0xC4 Device ID Number
	static const unsigned int SYSMOD = 0x08;// 0x09 data Current System Mode
	static const unsigned int OFF_X_MSB = 0X09;// 0x0A 0000 0000 Bits[14:7] of user X offset
	static const unsigned int OFF_X_LSB = 0X0A;// 0X0B 0000 0000 Bits[6:0] of user X offset
	static const unsigned int OFF_Y_MSB = 0X0B;// 0X0C 0000 0000 Bits[14:7] of user Y offset
	static const unsigned int OFF_Y_LSB = 0X0C;// 0X0D 0000 0000 Bits[6:0] of user Y offset
	static const unsigned int OFF_Z_MSB = 0X0D;// 0X0E 0000 0000 Bits[14:7] of user Z offset
	static const unsigned int OFF_Z_LSB = 0X0E;// 0X0F 0000 0000 Bits[6:0] of user Z offset
	static const unsigned int DIE_TEMP = 0X0F;// 0X10 data Temperature, signed 8 bits in °C
	static const unsigned int CTRL_REG1 = 0X10;// 0X11 0000 0000 Operation modes
	static const unsigned int CTRL_REG2 = 0X11;// 0x12 0000 0000 Operation modes
};
#endif
