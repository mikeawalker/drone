#ifndef PCA9685MemMap_H
#define PCA9685MemMap_H


namespace PCA9685Map
{
	static const unsigned int deviceId = 0x40;
	static const unsigned int	MODE1 = 0x0;
	static const unsigned int	MODE2 = 0x1;
	static const unsigned int	SUBADR1 = 0x2;
	static const unsigned int	SUBADR2 = 0x3;
	static const unsigned int	SUBADR3 = 0x4;
	static const unsigned int	ALLCALLADR = 0x5;
	static const unsigned int	LED0_ON_L = 0x6;
	static const unsigned int	LED0_ON_H = 0x7;
	static const unsigned int	LED0_OFF_L = 0x8;
	static const unsigned int	LED0_OFF_H = 0x9;
	static const unsigned int	LED1_ON_L = 0x0A;
	static const unsigned int	LED1_ON_H = 0x0B;
	static const unsigned int	LED1_OFF_L = 0x0C;
	static const unsigned int	LED1_OFF_H = 0x0D;
	static const unsigned int	LED2_ON_L = 0x0E;
	static const unsigned int	LED2_ON_H = 0x0F;
	static const unsigned int	LED2_OFF_L = 0x10;
	static const unsigned int	LED2_OFF_H = 0x11;
	static const unsigned int	LED3_ON_L = 0x12;
	static const unsigned int	LED3_ON_H = 0x13;
	static const unsigned int	LED3_OFF_L = 0x14;
	static const unsigned int	LED3_OFF_H = 0x15;
	static const unsigned int	LED4_ON_L = 0x16;
	static const unsigned int	LED4_ON_H = 0x17;
	static const unsigned int	LED4_OFF_L = 0x18;
	static const unsigned int	LED4_OFF_H = 0x19;
	static const unsigned int	LED5_ON_L = 0x1A;
	static const unsigned int	LED5_ON_H = 0x1B;
	static const unsigned int	LED5_OFF_L = 0x1C;
	static const unsigned int	LED5_OFF_H = 0x1D;
	static const unsigned int	LED6_ON_L = 0x1E;
	static const unsigned int	LED6_ON_H = 0x1F;
	static const unsigned int	LED6_OFF_L = 0x20;
	static const unsigned int	LED6_OFF_H = 0x21;
	static const unsigned int	LED7_ON_L = 0x22;
	static const unsigned int	LED7_ON_H = 0x23;
	static const unsigned int	LED7_OFF_L = 0x24;
	static const unsigned int	LED7_OFF_H = 0x25;
	static const unsigned int	LED8_ON_L = 0x26;
	static const unsigned int	LED8_ON_H = 0x27;
	static const unsigned int	LED8_OFF_L = 0x28;
	static const unsigned int	LED8_OFF_H = 0x29;
	static const unsigned int	LED9_ON_L = 0x2A;
	static const unsigned int	LED9_ON_H = 0x2B;
	static const unsigned int	LED9_OFF_L = 0x2C;
	static const unsigned int	LED9_OFF_H = 0x2D;
	static const unsigned int	LED10_ON_L = 0x2E;
	static const unsigned int	LED10_ON_H = 0x2F;
	static const unsigned int	LED10_OFF_L = 0x30;
	static const unsigned int	LED10_OFF_H = 0x31;
	static const unsigned int	LED11_ON_L = 0x32;
	static const unsigned int	LED11_ON_H = 0x33;
	static const unsigned int	LED11_OFF_L = 0x34;
	static const unsigned int	LED11_OFF_H = 0x35;
	static const unsigned int	LED12_ON_L = 0x36;
	static const unsigned int	LED12_ON_H = 0x37;
	static const unsigned int	LED12_OFF_L = 0x38;
	static const unsigned int	LED12_OFF_H = 0x39;
	static const unsigned int	LED13_ON_L = 0x3A;
	static const unsigned int	LED13_ON_H = 0x3B;
	static const unsigned int	LED13_OFF_L = 0x3C;
	static const unsigned int	LED13_OFF_H = 0x3D;
	static const unsigned int	LED14_ON_L = 0x3E;
	static const unsigned int	LED14_ON_H = 0x3F;
	static const unsigned int	LED14_OFF_L = 0x40;
	static const unsigned int	LED14_OFF_H = 0x41;
	static const unsigned int	LED15_ON_L = 0x42;
	static const unsigned int	LED15_ON_H = 0x43;
	static const unsigned int	LED15_OFF_L = 0x44;
	static const unsigned int	LED15_OFF_H = 0x45;
	static const unsigned int	ALL_LED_ON_L = 0xFA;
	static const unsigned int	ALL_LED_ON_H = 0xFB;
	static const unsigned int	ALL_LED_OFF_L = 0xFC;
	static const unsigned int   ALL_LED_OFF_H = 0xFD;
	static const unsigned int   PRE_SCALE = 0xFE;
	static const unsigned int   TestMode = 0xFF;
};

#endif