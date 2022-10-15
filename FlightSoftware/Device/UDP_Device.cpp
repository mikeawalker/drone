#include "UDP_Device.h"    /* for socket(),... */ 


#include <boost/lexical_cast.hpp>
UDP_Device::UDP_Device() 
{
	sockOpen = false;

}

UDP_Device::~UDP_Device()
{

	if(sockOpen)
	{
		local_socket->close();
		remote_socket->close();
	}
  if (local_socket != 0)
    delete local_socket;

  if (remote_socket != 0)
    delete remote_socket;

}

void UDP_Device::Close()
{


}

void UDP_Device::Open(unsigned int localPort)
{


	//udp::resolver resolver(io_service);
	//udp::resolver::query query(udp::v4(), localPort, "apot");
	//udp::endpoint receiver_endpoint = *resolver.resolve(query);



	//udp::endpoint local_endpoint(udp::v4(), localPort);

	if(!sockOpen)
	{
		try
		{
			local_socket = new udp::socket(io_service, udp::endpoint(udp::v4(), localPort));
		 if( !local_socket->is_open() )
		 {
			 DieWithError("OPEN FAIL");
		 }
		 sockOpen= true;
		}
		catch (std::exception& e)
	 {
			std::cout << e.what() << std::endl;
	 }

	}
   
}


void UDP_Device::Open( std::string ip ,unsigned int remotePort)
{
  udp::endpoint
	  remote_endpoint(boost::asio::ip::address::from_string(ip), remotePort);

  if (!sockOpen)
    {
      remote_socket = new udp::socket(io_service);

      try
        {
          remote_socket->connect(remote_endpoint);
        }
		catch (std::exception& e)
	 {
			std::cout << e.what() << std::endl;
	 }

    

     sockOpen=true;
    }
}
int UDP_Device::Recv(void *buff, int maxRcv)
{
	unsigned int bytes=0;
	//if (local_socket->available() > 0)
	{
	
	try
	{
		bytes = local_socket->receive(boost::asio::buffer(buff, maxRcv));
	}	
	catch (const boost::system::system_error& err)
	 {
		std::cout << err.what() << std::endl;
	 }
	}
	return bytes;
}


int UDP_Device::Send(void *buff, int bytes)
{
	if( !sockOpen ) 
	{
		return 0;
	}
	try
	{
		remote_socket->send( boost::asio::buffer(buff , bytes));
	}
		catch (const boost::system::system_error& err)
	 {
		 std::cout << err.what() << std::endl;
	 }
	
	return bytes;
}


void UDP_Device::DieWithError(char *errorMessage) 
{ 
  //  fprintf(stderr,"%s: %d\n", errorMessage, WSAGetLastError()); 
	fprintf(stderr,"%s \n", errorMessage);
    exit(1); 
} 