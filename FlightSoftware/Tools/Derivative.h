#ifndef DERIVATIVE_H_
#define DERIVATIVE_H_


template <class T2>
class Derivative
{
private:
	T2 last;
public:
	Derivative()
	{
		Reset();
	}
	~Derivative()
	{
	}
	void Reset()
	{
		int x = sizeof(T2);
		char* zero;
		for (int k = 0; k<x; k++)
		{
			zero = ((char*)&last)+k;
			*zero = 0;
		}
		
	}
	T2 iterate( T2 in , double dt) 
	{
		T2 out;
		out = ((in)-last)/dt;
		last = in;
		return out;
	}

};
#endif