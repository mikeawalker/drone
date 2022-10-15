#include "Tools.h"


Eigen::Vector4d CalcQuatDiff(const Eigen::Vector4d &q ,const Eigen::Vector4d &qd)
{
	double q1,q2,q3,q4;
	
	Eigen::Vector4d qc;
	Eigen::Vector4d qerr;
	Eigen::Matrix4d Q;
	Eigen::Vector4d zeroRot;
	zeroRot << 0,0,0,1;
	q1 = qd(0);
	q2 = qd(1);
	q3 = qd(2);
	q4 = qd(3);
	
	Q << q4, q3 , -q2, q1 ,
		-q3 , q4 , q1 , q2 ,
		q2, -q1 , q4 , q3 ,
		-q1 , -q2 , -q3 , q4;
	
	qc << -q(0) , -q(1) , -q(2) , q(3); 
	
	qerr = Q*qc;
	
	qerr = -qerr+ zeroRot;
	return qerr;
}

Eigen::Vector4d CalcQuatError( const Eigen::Vector4d &q1m , const Eigen::Vector4d &q2m)
{
	Eigen::Matrix4d Q;
	Eigen::Vector4d qconj;
	Eigen::Vector4d qerr;
	double q1, q2 , q3, q4;
	q1 = q2m(0);
	q2 = q2m(1);
	q3 = q2m(2);
	q4 = q2m(3);

	Q << q4, q3 , -q2, q1 , -q3 , q4 , q1 , q2 , q2, -q1 , q4 , q3 , -q1 , -q2 , -q3 , q4;

	q1 = q1m(0);
	q2 = q1m(1);
	q3 = q1m(2);
	q4 = q1m(3);
	qconj << -q1 , -q2 , -q3 , q4;
	qerr =  Q*qconj;
	return qerr;
}


Eigen::Vector3d CalcAngVel(const Eigen::Vector4d &dq , double dt)
{
	Eigen::Vector3d q3;
	Eigen::Vector3d omega;
	double qmag, th , d;
	double conv;
	q3 << dq(0) , dq(1) , dq(2);
	d =  q3.dot(q3);
	qmag = sqrt( d ) ;
	if( qmag == 0 )
	{
		omega << 0 , 0 , 0;
	}
	else
	{
		th = 2*asin( qmag );
		omega = (th/dt) * (q3/qmag  ) ;
	}
	return omega;

}


double Saturate( double in ,double lower, double upper )
{	

	double outVal;
	
	outVal  =in;

	if(outVal < lower)
	{
		outVal = lower;
	}
	if(outVal > upper)
	{
		outVal = upper;
	}
	return outVal;
}

double sind( double in )
{
	return sin( in*DEG2RAD );
}

double cosd( double in )
{
	return cos( in*DEG2RAD );
}

double constrainAngle(double x){
	x = fmod(x + PI, 2 * PI);
	if (x < 0)
		x += 2 * PI;
	return x - PI;
}
// convert to [-360,360]
double angleConv(double angle){
	return fmod(constrainAngle(angle), 2*PI);
}
double angleDiff(double a, double b){
	double dif = fmod(b - a + PI, 2 * PI);
	if (dif < 0)
		dif += 2 * PI;
	return dif - PI;
}
double unwrap(double previousAngle, double newAngle){
	return previousAngle - angleDiff(newAngle, angleConv(previousAngle));
}


double calcAccel(double x1, double x2, double x3, double t1, double t2, double t3)
{
	double v1, v2;

	v1 = (x2 - x1) / (t2 - t1);
	v2 = (x3 - x2) / (t3 - t2);

	return (v2 - v1) / (t3 - t2);
}