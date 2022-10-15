#include "MagEnetBlock.h"


MagEnetBlock::MagEnetBlock( std::string bName  , unsigned int portNum)
							: Block( bName , 10 , 10 ) 
{
	updDevice_.Open(portNum);
}

MagEnetBlock::~MagEnetBlock() 
{


}

void MagEnetBlock::update()
{
	double magMag;
		updDevice_.Recv(&magMsg_.myData, sizeof(magMsg_.myData) );


		sendMessage( &magMsg_ );
		//printf("Mag: %f %f %f\n", magMsg_.myData.mag1_x, magMsg_.myData.mag1_y, magMsg_.myData.mag1_z);
			mtx.unlock(); 

}
