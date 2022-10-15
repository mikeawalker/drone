#ifndef HIVE_H
#define HIVE_H

#include <vector>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/interprocess/ipc/message_queue.hpp>
#include <string>
#include "Block.h"
#include "MessageTypes.h"
#include "HiveTypes.h"
class Hive
{
public:
	Hive();
	~Hive();

	void start(int N);
	void join();

	void checkQueue( boost::interprocess::message_queue *queue  );
	void pullHeader( boost::interprocess::message_queue *queue ) ;
	void CheckBlocks( );
	void distributeMessage( );
	void distributeQuit();
	void freeBlocks();

	void destroyQueues();
	void addToHive(std::string blockName , boost::mutex *theMutex);
	void addToHive(Block *block);
	void run();
	bool isDone() {return stop;}
private:
	void handleRegister( MessageTypes::MessageHeader header );

	BoostInt tmpMsgSize;
	boost::thread myThread_;
	MessageTypes::MessageHeader tmpHeader_;
	boost::interprocess::message_queue *hiveQueue;
	char tmpData_[MessageTypes::MAX_DATA_SIZE];
	BlockInfo *currBlock;
	std::vector<BlockInfo> myBlocks;
	bool stop;
	int blockOrder;

protected:
	
};

#endif