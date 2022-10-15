#ifndef GUITMFORMAT
#define GUITMFORMAT

namespace GuiTypes
{

typedef struct
{
    double pos[3];
    double vel[3];
    double roll;
    double pitch;
    double yaw;
}GuiTm;

typedef enum
{
    none = 0,
    takeoff,
    start,
    rtb,
    land,
    override,
    up,
    down,
    north,
    east,
    south,
    west,
    kill,
    heartbeat,
} GuiCmds;

};
#endif // GUITMFORMAT

