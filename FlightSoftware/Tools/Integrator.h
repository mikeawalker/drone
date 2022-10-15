#ifndef INTEGRATOR_H_
#define INTEGRATOR_H_


#include <Eigen/Dense>

template <class T>
class Integrator
{
private:
	T val;
	T out;
public:
	Integrator( )
	{
		Reset();
	}
	~Integrator( )
	{
	}
	void Reset()
	{
		
		memset(&val, 0, sizeof(T));

		
	}

	T Integrate(  T in,  double dt ) 
	{
		out = val;
		val = val + dt*(in);
	
		return out;
	}
};

#endif