#ifndef ENDPOINT_HPP
#define ENDPOINT_HPP

#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>
#include<iostream>


namespace Net {


	class Endpoint {

	public:

		Endpoint();
		Endpoint(const std::string& address, unsigned short port);
		Endpoint(const sockaddr_in& sockAddr);

		std::string GetIPaddress() const;

		unsigned short GetPort() const;

		sockaddr_in getSockAddr() const;


		void setAddress(const std::string& address, unsigned short port);


		~Endpoint();



	private:

		sockaddr_in m_sockaddr;



	};






}//namespace Net










#endif// End of file Endpoint.hpp