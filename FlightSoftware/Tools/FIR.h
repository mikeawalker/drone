#ifndef FIR_H_
#define FIR_H_

#include <Eigen/Dense>

class FIR
{
public: 
	FIR(int length , int depth);
	~FIR();
	bool setCoefs( double *coefs , int length );
	bool setCoefs( double coef);
	void Reset();
	bool push(double *arr , int length , double *out);

private:
	int myLength;
	int myDepth;
	int myIndex;
	Eigen::MatrixXd myFir;
	Eigen::VectorXd myCoefs;

};


#endif