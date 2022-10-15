#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include "Includes.h"


class Controller
{
public:
	Controller();
	~Controller();
	virtual void Reset();
	virtual double Iterate(double error);

private:


protected:

};


#endif