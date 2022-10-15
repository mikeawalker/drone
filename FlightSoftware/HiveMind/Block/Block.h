#ifndef BLOCK_H
#define BLOCK_H

#include "MessageTypes.h"
#include "Message.h"
#include "HiveTypes.h"
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/interprocess/ipc/message_queue.hpp>
#include <string>
#include <vector>

//#define BLOCK_DEBUG



class Block
{

public:
	Block(std::string bName , int inLen , int outLen );
	~Block();

	void sendMessage( Message *msg);
	unsigned int  pullHeader();
	void rcvMessage(Message *msg );
	void join();
	virtual void start(int N);
	virtual void mrun();
	bool waitingMessages();
	boost::mutex* getMutex( );
	std::string getName(); 


	boost::scoped_ptr<boost::interprocess::message_queue> inQueue;
	boost::scoped_ptr<boost::interprocess::message_queue> outQueue;
	std::string inQueueName;
	std::string outQueueName;
	boost::thread myThread_;
	int inMessages;
	int outMessages;
	int maxInMsgs;
	int maxOutMsgs;
	virtual void update() = 0 ;
	void registerMessage(unsigned int id);
	boost::mutex mtx;
	bool stop;
private:
	MessageTypes::MessageHeader tempHeader_;
	char tmpData[MAX_MSG_SIZE];
	char tmpDataOut[MAX_MSG_SIZE];
	BoostInt rcvSize;
	std::string thisBlock;
	void bEnter();
	void bExit();
	
protected:
	
	


	


};


#endif