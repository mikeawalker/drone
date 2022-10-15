#include "MotorEnetBlock.h"
#include "MyTime.h"

MotorEnetBlock::MotorEnetBlock( std::string bName  , unsigned int portNum)
							: Block( bName , 10 , 10 ) 
{
	
	registerMessage(DroneMsgTypes::BladeCmdMsgId);
	std::string ip = "127.0.0.1";
	updDevice_.Open(ip,portNum);
	firstUpdate_ = true;

}

MotorEnetBlock::~MotorEnetBlock() 
{


}



void MotorEnetBlock::update()
{
	unsigned int header;
	double pwm[4];
	if( firstUpdate_ )
	{
		bladeMsg_.myData.rate1 =1;
		bladeMsg_.myData.rate2 = 1;
		bladeMsg_.myData.rate3 = 1;
		bladeMsg_.myData.rate4 = 1;
		updDevice_.Send( (void*)(&bladeMsg_.myData) , sizeof(BladeCmd) ); 
		//Sleep(1);
		MyTime::sSleep(1);

		updDevice_.Send((void*)(&bladeMsg_.myData), sizeof(BladeCmd));
		firstUpdate_ = false;
	}

	

	while( waitingMessages() )
	{
		header = pullHeader();

		switch( header )
		{	
		case DroneMsgTypes::BladeCmdMsgId:
			rcvMessage( &bladeMsg_ );

			pwm[0] = (abs(bladeMsg_.myData.rate1 ) )*( 4 - 1 )  + 1 ;
			pwm[1] = (abs(bladeMsg_.myData.rate2)) * (4 - 1) + 1;
			pwm[2] = (abs(bladeMsg_.myData.rate3 )) * (4 - 1) + 1;
			pwm[3] = (abs(bladeMsg_.myData.rate4)) * (4 - 1) + 1;
			//printf("Motor  %f %f %f %f \n", pwm[0], pwm[1], pwm[2], pwm[3]);
			updDevice_.Send( &pwm, sizeof(double) *4); 
			//std::cout<<"\nMOTOR";
			break;
		default:
			std::cout<<"Bad Message Id [Motor]\n";
			break;
		}
	}

}
