#include "core/UdpSocket.hpp"

Net::UDPSocket::UDPSocket() : SocketBase(AF_INET, SOCK_DGRAM, IPPROTO_UDP){}


int Net::UDPSocket::sendTo(const std::vector<char>& data, const Endpoint& destination)
{
	if (!m_handle) {
		std::cerr << "Error: Socket is not valid" << std::endl;
		return -1;

 }

	const sockaddr_in sockaddr = destination.getSockAddr();
	
	int bytes_sent = ::sendto(m_handle.get(),data.data(),static_cast<int>(data.size()),MSG_DONTROUTE,
		reinterpret_cast<const SOCKADDR*>(&sockaddr), sizeof(sockaddr));

	if(bytes_sent == SOCKET_ERROR) {
		std::cerr << "sendto failed with error: " << NetworkError::getLastErrorcode() << std::endl;
		return -1;
	}

	return bytes_sent;
}

int Net::UDPSocket::receiveFrom(std::vector<char>& buffer, Endpoint& sender)
{
	if (!m_handle) {
		std::cerr << "Error: Socket is not valid" << std::endl;
		return -1;

	}

	sockaddr_in serveraddr;

	int senderaddrsize = sizeof(serveraddr);

	buffer.resize(1024); // Resize buffer to hold incoming data

	int bytesReceived = ::recvfrom(m_handle.get(), buffer.data(), static_cast<int>(buffer.size()), 0,
		reinterpret_cast<SOCKADDR*>(&serveraddr), &senderaddrsize);

	if (bytesReceived == SOCKET_ERROR) {
		std::cerr << "recvfrom failed with error: " << NetworkError::getLastErrorcode() << std::endl;
		return -1;
	}
	else if (bytesReceived == 0) {
		std::cerr << "Connection closed by the sender." << std::endl;
		return 0;
	}
	else {
		buffer.resize(bytesReceived); // Resize buffer to actual data size
		sender = Endpoint(serveraddr); // Update sender endpoint
	}

	return bytesReceived;
}


//*************************************************

int Net::UDPSocket::sendTo(const Packet& packet, const Endpoint& destination) {

	if (!m_handle) {

		std::cerr << "Error: Socket is not valid " << std::endl;

			return -1;
	}

	const auto& buffer = packet.getBytes();

	const sockaddr_in sockaddr = destination.getSockAddr();

	int bytes_sent = ::sendto(m_handle.get(), buffer.data(), static_cast<int>(buffer.size()), MSG_DONTROUTE,
		reinterpret_cast<const SOCKADDR*>(&sockaddr), sizeof(sockaddr)); //preferring MSG_DONTROUTE for UDP also can be choosen 0

	if (bytes_sent == SOCKET_ERROR) {

		std::cerr << "sendto failed with error: " << NetworkError::getLastErrorcode() << std::endl;
		return -1;
	}

	return bytes_sent;
}

int Net::UDPSocket::receiveFrom(Packet& packet, Endpoint& sender) {

	if (!m_handle) {

		std::cerr << "Error: Socket is not valid " << std::endl;
		return -1;
	}

	sockaddr_in senderAddr;
	int senderAddrSize = sizeof(senderAddr);

	// Create a temporary buffer for the received data.
   // A standard size is used, as UDP packets have a max size (around 512-1500 bytes).

	std::vector<char> tempBuffer(1024); // 1 KB buffer

	int bytesReceived = ::recvfrom(m_handle.get(), tempBuffer.data(), static_cast<int>(tempBuffer.size()), 0,
		reinterpret_cast<SOCKADDR*>(&senderAddr), &senderAddrSize);
	if (bytesReceived == SOCKET_ERROR) {
		std::cerr << "failed to receive data. Error code: " << NetworkError::getLastErrorcode() << std::endl;
		return -1;
	}
	else if (bytesReceived == 0) {

		// A return value of 0 indicates the connection was gracefully closed,
	   // which is not typical for UDP, but handled as a safeguard.
		std::cerr << "Connection closed by the sender." << std::endl;
		
		return 0;
	}
	else {

		//Create a new packet from the received raw bytes.
		Packet receivedPacket;
		
		for (size_t i = 0; i < bytesReceived; ++i) {

			receivedPacket.add(tempBuffer[i]);
		}

		packet = receivedPacket; // Assign the received packet to the output parameter.
		sender = Endpoint(senderAddr); // Update the sender endpoint with the actual sender's address.
	


	}

	return bytesReceived;

}