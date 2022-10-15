#include "LookupTable.h"


LookupTable::LookupTable()
{

}



LookupTable::~LookupTable()
{



}



void LookupTable::Load(double *t, double *x, int len)
{
	// setup values
	tableLen = len;
	tTable = t;
	xTable = x;
	// make sure table in monotonic in time
	for( int k=1; k<tableLen; k++) 
	{
		try
		{
			if( tTable[k] <= tTable[k-1] ) 
			{
				throw 20;
			}
			
		}
		catch(int e)
		{
			std::cout<<"Exception "<<e<<": Lookup Table not Monotonic"<<std::endl;
			exit(1);
		}
	}


}

bool LookupTable::timeInBounds(double t)
{
	return (t <= tTable[tableLen - 1]);
}


double LookupTable::endValue()
{
	return xTable[tableLen - 1];
}
double LookupTable::CalcValue(double t)
{
	int ind = -1;
	double xVal;
	double dx;
	double dt;
	double dtTable;
	
	for( int lcv = 0 ; lcv < tableLen; lcv++)
	{
		if( tTable[lcv] >= t ) 
		{
			ind = lcv;
			lcv = tableLen;
		}
		
	}

	
	if(ind == -1)
	{
		// Covers Out of bounds t>table time ---- use end point
		xVal = xTable[tableLen - 1];

	}
	else if( ind == 0 )
	{
		// Covers Out of bounds t<=tabletime ---- use end point
		xVal = xTable[0];
	}
	else
	{
		// do linear interp
		dt = t - tTable[ind-1];
		dtTable = tTable[ind] - tTable[ind-1];
		dx = xTable[ind] - xTable[ind-1];
		xVal  = dx*dt/dtTable + xTable[ind-1]; 
	}

	return xVal; 
}