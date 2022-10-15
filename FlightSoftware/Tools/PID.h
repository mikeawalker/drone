#ifndef PID_H_
#define PID_H_

#include "Integrator.h"
#include "Derivative.h"
#include "Controller.h"
template <class T1>
class PID 
{

private: 
	double KI;
	double KD;
	double KP;
	T1 Out;
	Integrator<T1> myIntegrator;
	Derivative<T1> myDeriv;
public:
	PID(  )
	{
		Reset();
	}
	~PID()
	{
	}
	void SetCoef( double Kp , double Ki ,double Kd)
	{
		KP = Kp;
		KI = Ki;
		KD = Kd;
	}
	void Reset()
	{
		
		myIntegrator.Reset();
		myDeriv.Reset();
	}
	
	T1 Iterate( T1 in , double dt)
	{
		T1 iOut;
		T1 dOut;
		iOut = myIntegrator.Integrate( in , dt);
		dOut = myDeriv.iterate( in , dt);
		Out = KI*iOut + KP*(in) + KD*dOut; 
		return Out;
	}

};




#endif;

