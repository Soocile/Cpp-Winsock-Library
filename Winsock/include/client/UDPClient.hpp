

#ifndef UDPCLIENT_HPP

#define UDPCLIENT_HPP

#include<string>
#include<iostream>
#include"core/Packet.hpp"
#include"core/Endpoint.hpp"
#include"core/DNS_RESOLVER.hpp"
#include"core/UDPSocket.hpp"

#include "core/NetworkError.hpp"
namespace Net {


	class UDPClient {

	public:

		UDPClient();

		//sends a packet to a specified hostname and port
		//packet: the packet object to send
		//hostname: the hostname or IP address of the destination
		//port: the port number of the destination
		int sendTo(const Packet& packet, const std::string& hostname, unsigned short port);

		//receives a packet and fills the sender's endpoint information
		//packet: the packet object to write the received data into
		//sender : the endpoint object to be filled with the senders info
		int receive(Packet& packet, Endpoint& sender);


	private:
		
		UDPSocket m_udpsocket;

	};



}//namespace Net








#endif// UDPCLIENT_HPP