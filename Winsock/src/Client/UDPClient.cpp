

#include"client/UDPClient.hpp"
#include<iostream>

namespace Net {


	UDPClient::UDPClient() :m_udpsocket(){


		//UDPsocket constructor already handles socket creation so nothing to do here

	}


	int UDPClient::sendTo(const Packet& packet, const std::string& hostname, unsigned short port) {

		auto endpoints = DnsResolver::resolve(hostname, std::to_string(port));

		if(endpoints.empty()) {
			std::cerr << "failed to resolve hostname: " << hostname << std::endl;
			return -1;
		}

		int sentBytes;

		//getting the first address is not always the best option so we will try to send to all resolved addresses until one works
		
		for (Endpoint& endpoint : endpoints) {

			sentBytes = m_udpsocket.sendTo(packet, endpoint);

			if (sentBytes > 0) {

							std::cout << "sent " << sentBytes << " bytes to " << endpoint.GetIPaddress() << ":" << endpoint.GetPort() << std::endl;
							return sentBytes;
			}

			std::cerr << "failed to send packet to " << endpoint.GetIPaddress() << ":" << endpoint.GetPort() << " Error: " << NetworkError::getLastErrorcode() << std::endl;


		}

		std::cerr << "failed to send packet to any resolved address for hostname: " << hostname << std::endl;

		return -1;


	}

	int UDPClient::receive(Packet& packet, Endpoint& sender) {

		//call the UDPSocket's receiveFrom method
		return m_udpsocket.receiveFrom(packet, sender);
	}

}