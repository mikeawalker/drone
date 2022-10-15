#include "Radio_Interface.h"



Radio_Interface::Radio_Interface(std::string bName , int tmMode) : Block(bName, 10, 10) 
//,myTimer(1000, getMutex() ) 
{

	switch (tmMode)
	{
	case 2:
		registerMessage(DroneMsgTypes::ImuMsgId);
		registerMessage(DroneMsgTypes::MagMsgId);
		break;
	case 1:
		registerMessage(DroneMsgTypes::EkfStateMsgId);
		registerMessage(DroneMsgTypes::GpsPvtMsgId);
		break;
	default:
		
		break;
	}
	
	
	 

	//For some reason the serial port is causing threads to lock???



	firstMeasure = true;
	msCtr = 1;
	
	mySerial_.Open("/dev/ttyUSB0");
	mySerial_.Configure(56700);
	
	myRadio_.linkSerial( &mySerial_ );
	myRadio_.setupRadio();


//	myTimer.start(22);
	std::cout << " Radio Setup Done " << std::endl;
}

Radio_Interface::~Radio_Interface()
{
}

void Radio_Interface::update()
{
	int t1, t2;
	t1 = clock(); 
	
	myRadio_.readRadio();
	CheckMessages();
	CheckSend();
	//std::cout << "Message update " << std::endl;

	t2 = clock();
	//std::cout<<"T1 T2: "<< t1 <<  t2 << " DT: "<<(float)(t2-t1) / CLOCKS_PER_SEC<<std::endl;

}


void Radio_Interface::CheckMessages()
{
	unsigned int header;
	while (waitingMessages())
	{
		header = pullHeader();
		switch (header)
		{
		case DroneMsgTypes::EkfStateMsgId:
			
			rcvMessage(&stateMsg);
			if (msCtr++ % 50 == 0)
			{

				myRadio_.sendMsg(stateMsg.myData);
				//std::cout << "Pos: " << stateMsg.myData.pos << " Vel: " << stateMsg.myData.vel << " Quat: " << stateMsg.myData.q << std::endl;
			}
			break;
		case DroneMsgTypes::ImuMsgId:
			rcvMessage(&imuMsg);
			//std::cout << "Imu " << sizeof(imuMsg.myData) << std::endl;
			if (msCtr++ % 10 == 0)
			{
				myRadio_.sendMsg(imuMsg.myData);
			}

			break;
		case DroneMsgTypes::MagMsgId:
			rcvMessage(&magMsg);
			myRadio_.sendMsg(&magMsg.myData, LINK_MAG, sizeof(magMsg.myData));
			break;
		case DroneMsgTypes::GpsPvtMsgId:
			rcvMessage(&gpsMsg);
			myRadio_.sendMsg(&gpsMsg.myData, LINK_GPS, sizeof(gpsMsg.myData));
			break;
		default:
			break;
		}
	}
}


void Radio_Interface::CheckSend()
{
	if (myRadio_.getOutput(heartBeatMsg_.myData))
	{
		sendMessage(&heartBeatMsg_);

		std::cout << "HeartBeat Rcv " << cmdMsg_.myData.cmd << std::endl;
	}
	if (myRadio_.getOutput(cmdMsg_.myData))
	{
		std::cout << "Cmd Rcv " << cmdMsg_.myData.cmd << std::endl;
		sendMessage(&cmdMsg_);
	}
}