#include "Block.h"
#include "MessageTypes.h"
Block::Block(std::string bName, int inLen, int outLen)
{

	inQueueName = "InQ" + bName;
	outQueueName = "HiveQ";//"OutQ"+bName;
	thisBlock = bName;
	if (thisBlock.length() > MessageTypes::MAX_SENDER_ID_SIZE)
	{
		thisBlock = thisBlock.substr(0, MessageTypes::MAX_SENDER_ID_SIZE);
	}
	inMessages = inLen;
	outMessages = outLen;
	stop = false;
	rcvSize=0;
	// Create new QUEUE
	boost::interprocess::message_queue::remove(inQueueName.c_str());

	
	inQueue.reset(new  boost::interprocess::message_queue( boost::interprocess::create_only ,inQueueName.c_str()  , inMessages ,MessageTypes::MAX_DATA_SIZE ));
	outQueue.reset(new boost::interprocess::message_queue( boost::interprocess::open_only ,outQueueName.c_str() ));
}


Block::~Block()
{
}

void Block::join()
{
	myThread_.join();
}

void Block::start(int N)
{
	std::cout << "Starting " << thisBlock << std::endl;
	myThread_ = boost::thread( &Block::mrun , this  );
	
}


void Block::mrun()
{
	
	while( !stop )
	{
		
		mtx.lock();
		bEnter();
		update();
		bExit();
	}
	std::cout<<"Exiting Block" << thisBlock <<" \n";
	
}


void Block::sendMessage( Message *msg) 
{
	unsigned int msgSize;
	unsigned int headerEnd = sizeof(MessageTypes::MessageHeader);
	strcpy( msg->myHeader.sender , thisBlock.c_str());
	msgSize = sizeof(MessageTypes::MessageHeader)  + msg->myHeader.dataSize;
	memcpy( &tmpDataOut[0] , &msg->myHeader , headerEnd);
	memcpy( &tmpDataOut[headerEnd] , msg->ldata , msg->getSize() ) ;
	outQueue->send(tmpDataOut,msgSize,0);
}


unsigned int Block::pullHeader()
{
	unsigned int priority;
	inQueue->receive( tmpData , MessageTypes::MAX_DATA_SIZE , rcvSize , priority );//pull header into temp header
	
	memcpy( &tempHeader_ , tmpData , sizeof(MessageTypes::MessageHeader ) );
	if( tempHeader_.messageId ==  MessageTypes::QUIT_MSG ) 
	{
		stop = true;
	}
	return tempHeader_.messageId;
}


void Block::rcvMessage(Message *msg)
{
	
	
	unsigned int priority;
	unsigned int startLoc =  sizeof(MessageTypes::MessageHeader);
	msg->myHeader = tempHeader_;
	memcpy( msg->ldata , &tmpData[startLoc] , msg->getSize());
	if( msg->getSize() != rcvSize-sizeof(MessageTypes::MessageHeader) )
	{
		std::cout<<"Message Size Error"<<std::endl;
	}

}

bool Block::waitingMessages()
{	
	int waiting;
	waiting = inQueue->get_num_msg();
	return waiting > 0 ;
}


void Block::registerMessage(unsigned int id)
{
	MessageTypes::MessageHeader reg;
	reg.messageId = MessageTypes::REGISTRATION_MSG;
	reg.extra = id;
	strcpy( reg.sender , thisBlock.c_str() );
	outQueue->send(&reg , sizeof(reg) , 0);

}


boost::mutex* Block::getMutex()
{
	return &mtx;
}

std::string Block::getName()
{
	return thisBlock;
}
void Block::bExit()
{
#ifdef BLOCK_DEBUG
	std::cout << "Exiting " << thisBlock << std::endl;
#endif
}

void Block::bEnter()
{
#ifdef BLOCK_DEBUG
	std::cout << "Entering " << thisBlock << std::endl;
#endif
}