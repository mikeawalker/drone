#ifndef LOOKUPTABLE_H
#define LOOKUPTABLE_H

#include "Includes.h"


class LookupTable
{

public:
	LookupTable();
	~LookupTable();
	void Load( double *t , double *x, int len);
	double CalcValue( double t );
	double endValue();
	bool timeInBounds(double t);

private:
	double *xTable;
	double *tTable;
	int tableLen;
protected:

};

#endif