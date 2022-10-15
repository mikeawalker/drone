#ifndef TOOLS_H
#define TOOLS_H

#include <Eigen/Dense>
#include <math.h>
#include "Defines.h"


double Saturate( double in ,double lower, double upper );

Eigen::Vector4d CalcQuatDiff( const Eigen::Vector4d &qk , const Eigen::Vector4d &qm);
Eigen::Vector4d CalcQuatError( const Eigen::Vector4d &q1m , const Eigen::Vector4d &q2m);
Eigen::Vector3d CalcAngVel( const Eigen::Vector4d &dq, double dt);
double constrainAngle(double x);

// convert to [-360,360]
double angleConv(double angle);
double angleDiff(double a, double b);
double unwrap(double previousAngle, double newAngle);

double sind( double in);
double cosd( double in) ;

double calcAccel(double x1, double x2, double x3, double t1,double t2, double t3);

#endif