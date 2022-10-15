#ifndef ITG3200_Settings_H
#define ITG3200_Settings_H

namespace ITG3200_Settings
{

	typedef struct
	{
		char setting;
		int bw;
		int fastSampleRate;
	} GyroFilterCfg;

	static const GyroFilterCfg ITG3200_Filter[] = 
	{
		{0x0 , 256 , 8000},
		{0x1 , 188 , 1000},
		{0x2 , 98 , 1000},
		{0x3 , 42 , 1000},
		{0x4 , 20 , 1000},
		{0x5 , 10 , 1000},
		{0x6 , 5 , 1000}
	};

	enum ITG_FilterType
	{
		Filter_256KHZ,
		Filter_188KHZ,
		Filter_98KHZ,
		Filter_42KHZ,
		Filter_20KHZ,
		Filter_10KHZ,
		Filter_5KHZ
	};

	static const unsigned char FULLSCALE_RANGE = 0x3;
	static const float FULLSCALE_FACTOR = 0.06103515625; // 4000/(2^16)  for +- 2000 deg/s

};
#endif