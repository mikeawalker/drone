#ifndef TEST_TYPES_H
#define TEST_TYPES_H


namespace TestTypes
{
	typedef struct
	{
		int a;
		int b;
		double c;
		char d;
	} TypeA;
	
	typedef struct
	{
		double mathResult;
		char str[4];
	} TypeB;


	static const unsigned int MSG_A_ID = 0x0001;
	static const unsigned int MSG_B_ID = 0x0003;

};


#endif