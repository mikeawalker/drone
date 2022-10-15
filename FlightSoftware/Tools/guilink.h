#ifndef GUILINK_H
#define GUILINK_H
#include "guitmformat.h"
#include "Structs.h"
#include <boost/interprocess/ipc/message_queue.hpp>

#define _SCL_SECURE_NO_WARNINGS

class GuiLink
{
public:
    GuiLink();
    ~GuiLink();

    void postState( FullState *state);
	bool checkGuiCmds();
	GuiTypes::GuiCmds pullGuiCmd();
private:
    GuiTypes::GuiTm toSend;
    boost::interprocess::message_queue *guiQueue;
	boost::interprocess::message_queue *inQueue;

	
};

#endif // GUILINK_H
