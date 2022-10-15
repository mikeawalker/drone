#ifndef HMC5883L_Settings_H
#define HMC5883L_Settings_H

namespace HMC5883L_Settings
{
	//-----------Config Registers ------------------
	// gain stuff
	typedef struct
	{
		char gainSetting;
		unsigned int gain;
	} GainSetting;

	
	enum GainIndex
	{
		PM_0p88_Gauss = 0,
		PM_1p3_Gauss ,
		PM_1p9_Gauss ,
		PM_2p5_Gauss ,
		PM_4p0_Gauss ,
		PM_4p7_Gauss ,
		PM_5p6_Gauss ,
		PM_8p1_Gauss 
	};
	static const GainSetting gainTable[] =
	{
		{0x0 , 1370},
		{0x1 , 1090},
		{0x2 , 820},
		{0x3 , 660},
		{0x4 , 440},
		{0x5 , 390},
		{0x6 , 330},
		{0x7 , 230}
	};
	// output rate
	static const unsigned char RATE_0p75_Hz  = 0x0;
	static const unsigned char RATE_1p5_Hz  = 0x1;
	static const unsigned char RATE_3_Hz  = 0x2;
	static const unsigned char RATE_7p5_Hz  = 0x3;
	static const unsigned char RATE_15_Hz  = 0x4;
	static const unsigned char RATE_30_Hz  = 0x5;
	static const unsigned char RATE_75_Hz  = 0x6;
	// measurement modes
	static const unsigned char MODE_NORMAL = 0x0;
	static const unsigned char MODE_POSBIAS = 0x1;
	static const unsigned char MODE_NEGBIAS = 0x2;
	//averaging modes 
	static const unsigned char AVG_1 = 0x0;
	static const unsigned char AVG_2 = 0x1;
	static const unsigned char AVG_4 = 0x2;
	static const unsigned char AVG_8 = 0x3;
	typedef struct
	{
		GainIndex gainInd;
		unsigned char mode;
		unsigned char rate;
		unsigned char avg;

	} MagSetup;
	//--------------- MODE REGISTER ---------------//
	static const unsigned char MEAUSRE_SINGLE = 0x1;
	static const unsigned char MEASURE_CONT = 0x0;
	static const unsigned char MEASURE_IDLE = 0x3;
};

#endif