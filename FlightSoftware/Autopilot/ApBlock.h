#ifndef APBLOCK_H
#define APBLOCK_H


#include <string>
#include "AutoPilot.h"
#include "Block.h"

#include "GuideMsg.h"
#include "BladeCmdMsg.h"
#include "AutopilotReportMsg.h"
#include "EkfStateMsg.h"
class ApBlock : public Block
{

public:
	ApBlock(std::string bName );
	~ApBlock();
	void update();
	void CheckSend();
private:
	AutoPilot myAutopilot_;

	GuideMsg guideMsg_;
	BladeCmdMsg bladeCmdMsg_;
	EkfStateMsg ekfStateMsg_;
	AutopilotReportMsg apReportMsg_;

	ApGain rollGain;
	ApGain pitchGain;
	ApGain yawGain;

protected:

};



#endif