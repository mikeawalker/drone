#ifndef XPLATFORM_H
#define XPLATFORM_H

#include <fstream>
#include "Defines.h"
#include <cstdio>
#include <cstdlib>
#include <string>
#include <iostream>
namespace XPlatform
{
	bool BadFile(std::fstream *fp);
	bool BadFile(std::ofstream *fp);
	bool BadFile(std::ifstream *fp);
	bool BadFile(int *fp);
	bool NmeaCkSumOk(std::string toCk);
	void grabFirstNmea(std::string buff);
	void idNmea(std::string str);

	int readSome(char *ptr, int bytes);
};

#endif