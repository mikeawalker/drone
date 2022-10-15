#ifndef HIVE_TYPES_H
#define HIVE_TYPES_H

#include <boost/interprocess/ipc/message_queue.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/scoped_ptr.hpp>
#include <vector>

typedef struct
{
	std::string name;
	std::vector<unsigned int> regList;
	boost::interprocess::message_queue *inQueue;
	boost::interprocess::message_queue *outQueue;
	boost::mutex *locker;
	bool pendingUnlock;
} BlockInfo;

static const unsigned int MAX_MSG_SIZE = 300;

typedef unsigned int BoostInt;

#endif HIVE_TYPES_H