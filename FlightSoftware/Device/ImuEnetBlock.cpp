#include "ImuEnetBlock.h"


ImuEnetBlock::ImuEnetBlock( std::string bName  , unsigned int portNum)
							: Block( bName , 10 , 10 ) 
{
	updDevice_.Open(portNum);
}

ImuEnetBlock::~ImuEnetBlock() 
{


}

void ImuEnetBlock::update()
{

		updDevice_.Recv(&imuMsg_.myData, sizeof(imuMsg_.myData) );
		//printf("IMU: %f %f %f\n", imuMsg_.myData.a_b1, imuMsg_.myData.a_b2, imuMsg_.myData.a_b3);
		sendMessage( &imuMsg_ );
		
		mtx.unlock(); 

}

