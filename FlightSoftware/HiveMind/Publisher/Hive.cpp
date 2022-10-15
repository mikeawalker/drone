#include "Hive.h"



Hive::Hive()
{

	stop =false;
		boost::interprocess::message_queue::remove("HiveQ");
	hiveQueue = new boost::interprocess::message_queue( boost::interprocess::create_only,"HiveQ"
													 , 20 ,MessageTypes::MAX_DATA_SIZE);
	blockOrder = 1;
}


Hive::~Hive()
{
	delete hiveQueue;
}

void Hive::start(int N)
{
	myThread_ = boost::thread( &Hive::run , this   );
}

void Hive::join()
{
	myThread_.join();
}

void Hive::run()
{
	int runCnt=0;
	while(!stop)
	{
		CheckBlocks();
		freeBlocks();
		//if( runCnt++ > 100 )
		//{
		//	//TODO: This is a temp fix until I fix the unlock/lock race condition
		//	for( int k =0 ; k < myBlocks.size() ; k++ )
		//	{
		//		runCnt = 0;
		//		myBlocks[k].locker->unlock();
		//	}
		//}
		//boost::this_thread::sleep(boost::posix_time::microseconds(200));
		
	}
	std::cout<<"Exiting Hive\n";
}

void Hive::addToHive(std::string blockName , boost::mutex *theMutex) 
{
	BlockInfo newBlock;
	std::string inQName;
	std::string outQName;
	inQName = "InQ"+blockName;
	outQName = "OutQ"+blockName;
	newBlock.name = blockName;
	newBlock.locker = theMutex;
	newBlock.pendingUnlock = false;
	//newBlock.outQueue = new boost::interprocess::message_queue( boost::interprocess::open_only 
	//													,outQName.c_str());
	newBlock.inQueue = new boost::interprocess::message_queue( boost::interprocess::open_only ,
														inQName.c_str());
	
	myBlocks.push_back(newBlock);
}

void Hive::addToHive(Block *block)
{
	addToHive(block->getName(), block->getMutex());
	block->start(blockOrder++);

}

void Hive::destroyQueues()
{
	for( int k = 0 ; k < myBlocks.size() ; k++ )
	{
	//	delete myBlocks[k].inQueue;
	//	delete myBlocks[k].outQueue;
	}
}

void Hive::checkQueue( boost::interprocess::message_queue *queue)
{
	bool isRegister;
	bool isQuit;
	bool msgWaiting;
	unsigned int idToRegister;
	   unsigned int numMsgs;

 numMsgs = queue->get_num_msg();
//	{
		//
		pullHeader( queue );

		isRegister = ( tmpHeader_.messageId == MessageTypes::REGISTRATION_MSG ) ;
		isQuit = ( tmpHeader_.messageId == MessageTypes::QUIT_MSG );
		//
		if( isRegister )
		{	
			printf("Handling Registration of: %x with %s\n", tmpHeader_.extra,tmpHeader_.sender);
			handleRegister(tmpHeader_ );
		}
		else if( isQuit ) 
		{
			stop = true;
			distributeQuit();
		}
		else
		{
		
			distributeMessage();
		}

//	}
}


void Hive::handleRegister( MessageTypes::MessageHeader header)
{
	for( int k=0; k < myBlocks.size() ; k++ )
	{
		if( strcmp(myBlocks[k].name.c_str(), header.sender)==0 ) 
		{
			myBlocks[k].regList.push_back( header.extra );
		}
	}

}
void Hive::pullHeader(boost::interprocess::message_queue *queue)
{
	
	unsigned int priority;
	queue->receive(tmpData_  ,  MessageTypes::MAX_DATA_SIZE , tmpMsgSize , priority ) ;

	memcpy( &tmpHeader_ , tmpData_ , sizeof( MessageTypes::MessageHeader ) );
}


void Hive::CheckBlocks( )
{
	checkQueue( hiveQueue );
}


void Hive::distributeMessage( )
{
	unsigned int sendSize;
	//loop through blocks

	for( int k=0; k < myBlocks.size() ; k++ )
	{
	
		if( std::find( myBlocks[k].regList.begin() ,
			myBlocks[k].regList.end(),
			tmpHeader_.messageId) != myBlocks[k].regList.end())
		{
	
			// send header
			myBlocks[k].inQueue->send( tmpData_ , tmpMsgSize , 0 );

			// set a pending thing
			myBlocks[k].pendingUnlock = true;; 
		
		}
	}

}

void Hive::distributeQuit()
{
	unsigned int sendSize;
	//loop through blocks
	for (int k = 0; k < myBlocks.size(); k++)
	{
		
			// send header
			myBlocks[k].inQueue->send(tmpData_, tmpMsgSize, 0);

			// set a pending thing
			myBlocks[k].pendingUnlock = true;;
	}

}

void Hive::freeBlocks()
{
	BlockInfo *currBlock;
	for( int k =0 ; k < myBlocks.size() ; k++ )
	{
			currBlock = &myBlocks[k];
			
			if( currBlock->pendingUnlock ) 
			{
				
				if(currBlock->locker->try_lock() )
				{
					//if we can lock the thread its bad, its in action...unlock it and dont clear the pend
					currBlock->locker->unlock();
					//std::cout << "Free Blocks err " <<  currBlock->name <<std::endl;
				}
				else
				{
					// if it is locked the task is waiting...this is good...unlock it and clear the pend
					currBlock->pendingUnlock = false;
					currBlock->locker->unlock();
				}
			}
		
	}
}