#ifndef ITG3200_MemMap_H
#define ITG3200_MemMap_H
namespace ITG3200Map
{
static const unsigned int deviceId = 0x68;
static const unsigned int WHO_AM_I = 0x0; //  
static const unsigned int SMPLRT_DIV = 0x15; //  
static const unsigned int DLPF_FS = 0x16; //  
static const unsigned int INT_CFG = 0x17; //  
static const unsigned int INT_STATUS = 0x1A; //  
static const unsigned int TEMP_OUT_H = 0x1B; //  
static const unsigned int TEMP_OUT_L = 0x1C; //  
static const unsigned int GYRO_XOUT_H = 0x1D; //  
static const unsigned int GYRO_XOUT_L = 0x1E; //  
static const unsigned int GYRO_YOUT_H = 0x1F; //  
static const unsigned int GYRO_YOUT_L = 0x20; //  
static const unsigned int GYRO_ZOUT_H = 0x21; //  
static const unsigned int GYRO_ZOUT_L = 0x22; //  
static const unsigned int PWR_MGM = 0x3E; //  
};
#endif