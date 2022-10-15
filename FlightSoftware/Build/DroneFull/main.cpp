
#include <iostream>
#include "Hive.h"
#include "NavBlock.h"
#include "GuidanceBlock.h"
#include "ApBlock.h"
#include "FlightManagerBlock.h"


#include "Defines.h"
#ifdef REAL_DEVICE
	#include "FileTmBlock.h"
	#include "Serial_Interface.h"
	#include "Radio_Interface.h"
	#include "Fake_Interface.h"
	#include "GPIO_Device.h"
// Interrupt
#include "Interrupt.h"
#include "MagInterrupt.h"
	#include "I2C_Interface.h"
#elif defined ETHERNET_DEVICE
	#include "EnetTmBlock.h"
	#include "MagEnetBlock.h"
	#include "ImuEnetBlock.h"
	#include "GpsEnetBlock.h"
	#include "MotorEnetBlock.h"
	#include "GuiLinkBlock.h"
#else
#endif

//Timer
#include "Timer.h"


//
int main(int argc, char* argv[])
{
	int diagMode;
	bool calMode;
	Hive myHive;
	NavBlock myNav("Navigator");
	GuidanceBlock myGuide("Guide");
	ApBlock	myAutopilot("AutoPilot");
	FlightManagerBlock myManager("FlightManager");


	if (argc == 1)
	{
		std::cout << "Calibration Mode Enabled" << std::endl;
		calMode = true;
	}
	else
	{
		calMode = false;
	}

#ifdef REAL_DEVICE
	GPIO_Device diagPin("24", "in");
	diagMode = diagPin.read() == 1 ? 2 : 1 ;
	if (diagMode == 1)
	{
		std::cout << std::endl << "Diag Mode Enabled" << std::endl;
	}
	MagInterrupt magMsg_;
	I2C_Interface myI2C("I2C", calMode);
	Serial_Interface mySerial("Serial");
	Radio_Interface myRadio("Radio" , diagMode);
	Interrupt myInterrupt("Interrupt", &magMsg_ , "23");
	Timer myTimer(10 , myRadio.getMutex() );
	// Interrupts

#elif defined ETHERNET_DEVICE
	MagEnetBlock magEnet("MagEnet", 8200) ;
	ImuEnetBlock imuEnet("ImuEnet",8000);
	GpsEnetBlock gpsEnet("GpsEnet",8100);
	MotorEnetBlock motorEnet("MotorEnet",8300);
	GuiLinkBlock guiLink("GuiLink");
#else
	Fake_Interface myFake("Fake");
#endif

	myHive.addToHive(&myGuide);
	myHive.addToHive(&myAutopilot );
	myHive.addToHive(&myManager);
	myHive.addToHive(&myNav);
	
#ifdef REAL_DEVICE
        printf("Starting serial!\n");
    myHive.addToHive(&myI2C);
	myHive.addToHive(&mySerial);
	myHive.addToHive(&myRadio);
	myHive.addToHive(&myInterrupt);

#elif defined ETHERNET_DEVICE

	myHive.addToHive(&motorEnet);
	myHive.addToHive(&magEnet);
	myHive.addToHive(&imuEnet);
	myHive.addToHive(&gpsEnet);
	myHive.addToHive(&guiLink);
#else
//	myHive.addToHive("Fake", myFake.getMutex());
#endif
	//myHive.addToHive("Telem",myTm.getMutex() );
	
	

	


	
	myHive.start(12);

	std::cout << "Drone Started " << std::endl;
	bool okTogo = true;
	while( okTogo)
	{
		okTogo = !myHive.isDone();
		boost::this_thread::sleep(boost::posix_time::milliseconds(2000));
		
	}
		std::cout<<"END\n";
	myHive.join();

	std::cout<<"END\n";
	return 0;
}
