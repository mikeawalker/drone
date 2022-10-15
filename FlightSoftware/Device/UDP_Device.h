#ifndef UDP_DEVICE_H_
#define UDP_DEVICE_H_


#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <iostream>
using boost::asio::ip::udp;


class UDP_Device
{


public:
	UDP_Device();
	~UDP_Device();

	void Open(unsigned int localPort);
	void Open(std::string ip , unsigned int remotePort);
	void Close();
	int Send(void *buff , int bytes);
	int Recv(void *buff , int maxBytes);

private:
	
  bool sockOpen;

  boost::asio::io_service io_service;
  boost::asio::ip::udp::socket* local_socket;
  boost::asio::ip::udp::socket* remote_socket;
	void DieWithError(char *errorMessage) ;
protected:


};

#endif