#include "core/SocketBase.hpp"

Net::SocketBase::~SocketBase()
{
	//SocketHandle destructor will be called automatically
	// so we dont need to do something here
}

bool Net::SocketBase::bind(const Endpoint& endPoint)
{
	if (!m_handle) {
		std::cerr << "Error: Socket is not valid" << std::endl;
		return false;
	}

	const sockaddr_in sockaddr = endPoint.getSockAddr();

	if (::bind(m_handle.get(), reinterpret_cast<const SOCKADDR*>(&sockaddr), sizeof(sockaddr)) == SOCKET_ERROR) {

		std::cerr << "Bind failed with error: " << NetworkError::getLastErrorcode() << std::endl;
		return false;
	}

	return true;
}

Net::SocketBase::SocketBase(int addressFamily, int socketType, int protocol)
{
	SOCKET rawsocket = ::socket(addressFamily, socketType, protocol);

	if(rawsocket == INVALID_SOCKET) {
		throw NetworkError("Socket creation failed with error: " + std::to_string(NetworkError::getLastErrorcode()));
	}

	m_handle = SocketHandle(rawsocket);
}
