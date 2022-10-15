

#ifndef CONTROLCONSTS_H
#define CONTROLCONSTS_H
namespace ControlConsts
{

// Guidance Hover Constants
static const double KPhover = 5;
static const double KIhover = 2;
static const double KDhover = 2;
//Guidance Position
static const double KPpos = 0.5;
static const double KIpos = 0.1;
static const double KDpos = 1;
// Control Lims
static const double BladeRateMax  = 10;
static const double MaxPitch = 45; // Deg
static const double MaxRoll = 45; // Deg
// Yaw Loop limits
static const double YawErrorLim = 20*M_PI/180; // Deg
}
#endif