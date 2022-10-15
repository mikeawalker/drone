#include "FIR.h"



FIR::FIR(int length , int depth):
myFir(length,depth),
myCoefs(length)
{
	myLength = length;
	myDepth = depth;
	Reset();
}

FIR::~FIR()
{

}

void FIR::Reset()
{
	myIndex = 0;
	for( int z=0 ; z<myDepth; z++)
	{
		for( int k=0 ; k< myLength ; k++)
		{
			myFir(k,z) = 0.0;
		}
	}
}


bool FIR::setCoefs( double *coefs , int length )
{
	bool ret = true;
	if( length == myLength )
	{
		for(int k=0; k<length; k++ )
		{
			myCoefs(k) = coefs[k];
		}
	}
	else
	{
		ret = false;
	}
	return ret;
}

bool FIR::setCoefs( double coef)
{
	for( int k=0; k< myLength ; k++ )
	{
		myCoefs(k) = coef;
	}
	return true;
}

bool FIR::push(double *arr, int depth, double *out)
{
	
	// Add value
	if( depth != myDepth )
	{
		return false;
	}
	for( int k=0; k< myDepth ; k++)
	{
		myFir(myIndex,k) = arr[k];
	}

	myIndex = (myIndex+1)%myLength;
	// Calculate
	for(int z=0; z<myDepth; z++)
	{
		out[z] = 0.0;
	}
	for( int k=0; k<myLength ; k++ )
	{
		for(int z=0; z<myDepth; z++)
		{
			out[z]+= myFir(k,z)*myCoefs(k);
		}
	}



}



