#include "XPlatform.h"



bool XPlatform::BadFile(std::fstream *fp)
{
	bool bad;

#ifdef LINUX_DEVICE
	bad = *fp < 0 ;
#else
	bad = !fp->is_open();
#endif
	return bad;
}

bool XPlatform::BadFile(std::ofstream *fp)
{
	bool bad;

#ifdef LINUX_DEVICE
	bad = *fp < 0;
#else
	bad = !fp->is_open();
#endif
	return bad;
}

bool XPlatform::BadFile(std::ifstream *fp)
{
	bool bad;

#ifdef LINUX_DEVICE
	bad = *fp < 0;
#else
	bad = !fp->is_open();
#endif
	return bad;
}

bool XPlatform::BadFile(int *fp)
{
	return *fp < 0;
}


