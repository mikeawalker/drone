#ifndef ADXL345_MemMap_H
#define ADXL345_MemMap_H
namespace ADXL345Map
{
static const unsigned int deviceId = 0x53;
static const unsigned int DEVID = 0x00; // R Device ID.
static const unsigned int THRESH_TAP = 0x1D; // R/W Tap threshold.
static const unsigned int OFSX = 0x1E; // R/W X-axis offset.
static const unsigned int OFSY = 0x1F; // R/W Y-axis offset.
static const unsigned int OFSZ = 0x20; // R/W Z-axis offset.
static const unsigned int DUR = 0x21; // R/W Tap duration.
static const unsigned int Latent = 0x22; // R/W Tap latency.
static const unsigned int Window = 0x23; // R/W Tap window.
static const unsigned int THRESH_ACT = 0x24; // R/W Activity threshold.
static const unsigned int THRESH_INACT = 0x25; // R/W Inactivity threshold.
static const unsigned int TIME_INACT = 0x26; // R/W Inactivity time.
static const unsigned int ACT_INACT_CTL = 0x27; // R/W Axis enable control for activity and inactivity detection.
static const unsigned int THRESH_FF = 0x28; // R/W Free-fall threshold.
static const unsigned int TIME_FF = 0x29; // R/W Free-fall time.
static const unsigned int TAP_AXES = 0x2A; // R/W Axis control for tap/double tap.
static const unsigned int ACT_TAP_STATUS = 0x2B; // R Source of tap/double tap.
static const unsigned int BW_RATE = 0x2C; // R/W Data rate and power mode control.
static const unsigned int POWER_CTL = 0x2D; // R/W Power-saving features control.
static const unsigned int INT_ENABLE = 0x2E; // R/W Interrupt enable control.
static const unsigned int INT_MAP = 0x2F; // R/W Interrupt mapping control.
static const unsigned int INT_SOURCE = 0x30; // R Source of interrupts.
static const unsigned int DATA_FORMAT = 0x31; // R/W Data format control.
static const unsigned int DATAX0 = 0x32; // R X-Axis Data 0.
static const unsigned int DATAX1 = 0x33; // R X-Axis Data 1.
static const unsigned int DATAY0 = 0x34; // R Y-Axis Data 0.
static const unsigned int DATAY1 = 0x35; // R Y-Axis Data 1.
static const unsigned int DATAZ0 = 0x36; // R Z-Axis Data 0.
static const unsigned int DATAZ1 = 0x37; // R Z-Axis Data 1.
static const unsigned int FIFO_CTL = 0x38; // R/W FIFO control.
static const unsigned int FIFO_STATUS = 0x39; // R FIFO status
};
#endif