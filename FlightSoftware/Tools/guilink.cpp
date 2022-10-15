#include "guilink.h"
#define _SCL_SECURE_NO_WARNINGS

GuiLink::GuiLink()
{
    
	guiQueue = new boost::interprocess::message_queue(boost::interprocess::open_only, "GsToGui");
	inQueue = new boost::interprocess::message_queue(boost::interprocess::open_only, "GuiToGs");
}

GuiLink::~GuiLink()
{
    delete guiQueue;
	delete inQueue;
}

void GuiLink::postState(FullState *state)
{
    GuiTypes::GuiTm tm;

    double q1,q2,q3,q4;

    q1 = state->q[0];
	q2 = state->q[1];
	q3 = state->q[2];
	q4 = state->q[3];

    tm.pitch = 180 * atan( 2*(q4*q1+ q2*q3) / (1 -2*q1*q1 - 2*q2*q2) ) / M_PI;
	tm.roll = 180 * asin(2 * (q4*q2 - q3*q1)) / M_PI;
	tm.yaw = fmod(180 * atan2(2 * (q4*q3 + q1*q2), (1 - 2 * q2*q2 - 2 * q3*q3)) / M_PI , 360 );
	tm.yaw = (tm.yaw < 0) ? tm.yaw + 360 : tm.yaw;
	tm.pos[0] = state->pos[0];
	tm.pos[1] = state->pos[1];
	tm.pos[2] = state->pos[2];
    guiQueue->send( &tm , sizeof(GuiTypes::GuiTm), 0);
}

bool GuiLink::checkGuiCmds()
{
	int waiting;
	waiting = inQueue->get_num_msg();
	return waiting > 0;
}

GuiTypes::GuiCmds GuiLink::pullGuiCmd()
{
	GuiTypes::GuiCmds cmd;
	unsigned int rcvSize;
	//unsigned long long rcvSize;
	unsigned int pri = 0;
	inQueue->receive(&cmd, 1000, rcvSize, pri);//pull header into temp header)
	return cmd;
}