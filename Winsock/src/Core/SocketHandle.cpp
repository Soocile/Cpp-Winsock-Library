#include "core/SocketHandle.hpp"

Net::SocketHandle::SocketHandle() 
{
	m_socket = INVALID_SOCKET;
}

Net::SocketHandle::SocketHandle(SOCKET socket)
{
	m_socket = socket;
}

Net::SocketHandle::SocketHandle(SocketHandle&& other) noexcept
{
	m_socket = other.m_socket;
	other.m_socket = INVALID_SOCKET;
}

Net::SocketHandle::~SocketHandle()
{
	if (*this) {
		::closesocket(m_socket);
	}
}

Net::SocketHandle& Net::SocketHandle::operator=(SocketHandle&& other) noexcept
{
	if (this != &other) {

		if (*this) {
			::closesocket(m_socket);

		}
		m_socket = other.m_socket;
		other.m_socket = INVALID_SOCKET;

	}

	return *this;

}

