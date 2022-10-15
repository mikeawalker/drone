#ifndef ADXL345_Settings_H
#define  ADXL345_Settings_H

namespace ADXL345_Settings
{
	static const unsigned char RATE_3200 = 0xF;
	static const unsigned char RATE_1600 = 0xE;
	static const unsigned char RATE_800  = 0xD;
	static const unsigned char RATE_400  = 0xC;
	static const unsigned char RATE_200  = 0xB;
	static const unsigned char RATE_100  = 0xA;
	static const unsigned char RATE_50   = 0x9;
	static const unsigned char RATE_25  = 0x8;
	static const unsigned char RATE_12p5  = 0x7;
	static const unsigned char RATE_6p25  = 0x6;

	static const unsigned char RANGE_2G_PM = 0x0; //plus minus 2g
	static const unsigned char RANGE_4G_PM = 0x1; //plus minus 2g
	static const unsigned char RANGE_8G_PM = 0x2; //plus minus 2g
	static const unsigned char RANGE_16G_PM = 0x3; //plus minus 2g

	static const unsigned char FIFO_BYPASS = 0x0;
	static const unsigned char FIFO_MODE = 0x1;
	static const unsigned char FIFO_STREAM = 0x2;
	static const unsigned char FIFO_TRIGGER = 0x3;

	static const float FULL_RES_SCALE = 0.004; // 4 mg per LSB

	static const float OFFSET_SCALE = 0.0156; // 15.6 mg's per bit

	
};
#endif