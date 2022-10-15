#ifndef FILETMBLOCK_H
#define FILETMBLOCK_H


#include <string>
#include <fstream>
#include "Block.h"

#include "ImuMsg.h"
#include "MagMsg.h"
#include "EkfStateMsg.h"
#include "GpsPvtMsg.h"
class FileTmBlock : public Block
{

public:
	FileTmBlock(std::string bName);
	~FileTmBlock();
	void update();
	void ULock();
private:
	bool firstUpdate_;

	MagMsg magMsg_;
	ImuMsg imuMsg_;
	EkfStateMsg stateMsg_;
	GpsPvtMsg gpsMsg_;

	FILE *ekfFile;
	FILE *gpsFile;

protected:

};



#endif