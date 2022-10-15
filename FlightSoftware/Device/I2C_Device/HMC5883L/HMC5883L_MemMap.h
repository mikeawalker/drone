#ifndef HMC5883L_MemMap_H
#define HMC5883L_MemMap_H
namespace HMC5883LMap
{
static const unsigned int deviceId = 0x1e;
static const unsigned int CfgA = 0x0; // ReadWrite 
static const unsigned int CfgB = 0x1; // ReadWrite 
static const unsigned int Mode = 0x2; // ReadWrite 
static const unsigned int DataXMSB = 0x3; // Read 
static const unsigned int DataXLSB = 0x4; // Read 
static const unsigned int DataZMSB = 0x5; // Read 
static const unsigned int DataZLSB = 0x6; // Read 
static const unsigned int DataYMSB = 0x7; // Read 
static const unsigned int DataYLSB = 0x8; // Read 
static const unsigned int Status = 0x9; // Read 
static const unsigned int IdA = 0xA; // Read 
static const unsigned int IdB = 0xB; // Read 
static const unsigned int IdC = 0xC; // Read 
};
#endif