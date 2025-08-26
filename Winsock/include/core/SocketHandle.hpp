
#ifndef NET_SOCKETHANDLE_HPP
#define NET_SOCKETHANDLE_HPP

#include <winsock2.h>
#include <ws2tcpip.h>
#include<iostream>
#include<utility>

namespace Net {


	class SocketHandle {

	public:

		//default constructor creates an invalid socket handle
		SocketHandle();

		//constructor that takes a SOCKET and creates a SocketHandle from it
		explicit SocketHandle(SOCKET socket);


		
		SocketHandle(const SocketHandle&) = delete;

		SocketHandle(SocketHandle&& other) noexcept;


		//destructor
		~SocketHandle();

		SocketHandle& operator=(const SocketHandle&) = delete;

		SocketHandle& operator=(SocketHandle&& other) noexcept;

		SOCKET get() const {
			return m_socket;
		}

		explicit operator bool() const {
			return m_socket != INVALID_SOCKET;
		}


	private:
		SOCKET m_socket;

	};





}







#endif // End of file SocketHandle.hpp
