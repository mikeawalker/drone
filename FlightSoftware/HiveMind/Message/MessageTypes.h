#ifndef MESSAGE_TYPES_H
#define MESSAGE_TYPES_H

#include "string.h"

namespace MessageTypes
{

static const unsigned int MSG_PREAMBLE = 0xDEAD;
static const unsigned int MSG_POSTFIX = 0xBEEF;
static const unsigned int BIG_E = 0x0001;
static const unsigned int LITTLE_E = 0xFFFF;
static const unsigned int DEFAULT_DATA_SIZE = 0;
static const unsigned int END_OF_MSG_QUEUE =  0xCAFE;
static const unsigned int REGISTRATION_MSG = 0xF0F0;
static const unsigned int QUIT_MSG = 0xFFFF;
static const unsigned int MAX_SENDER_ID_SIZE = 20;

static const unsigned int MAX_DATA_SIZE  =  1000;
typedef struct
{
	unsigned int preamble;
	unsigned int messageId;
	char sender[MAX_SENDER_ID_SIZE];
	unsigned int dataSize;
	unsigned int endian;
	unsigned int extra;

	/*MessageHeader()
	{
		preamble = MSG_PREAMBLE;
		postfix = MSG_POSTFIX;
	};*/

} MessageHeader;



typedef struct
{
	void *msgBuffer;
	unsigned int numMsgs;
} BlockMessageInfo;

};
#endif