#include "client/TcpClient.hpp"
#include<iostream>


Net::TCPClient::TCPClient() : m_socket(){}



bool Net::TCPClient::connect(const std::string& hostname, unsigned short port)
{
	auto endpoints = DnsResolver::resolve(hostname, std::to_string(port));

	if (endpoints.empty()) {
		std::cerr << "failed to resolve hostname: " << hostname << std::endl;	
		return false;
	}

	//try to make connection for every ip address that was resolved
	for (const Endpoint& ep : endpoints) {

		//try to connect to the server
		if (m_socket.connect(ep)) {
			std::cout << "connected to " << ep.GetIPaddress() << ":" << ep.GetPort() << std::endl;
			return true;
		}
	}

	std::cerr << "falied to connect to any resolved address for hostname: " << hostname << std::endl;
	return false;

}

void Net::TCPClient::disconnect()
{
	m_socket.close();
}

bool Net::TCPClient::isConnected() const
{
	return static_cast<bool>(m_socket);
}


// new methods ****

int Net::TCPClient::send(const Packet& packet) {

	return m_socket.send(packet);
}

int Net::TCPClient::receive(Packet& packet) {
	return m_socket.receive(packet);
}