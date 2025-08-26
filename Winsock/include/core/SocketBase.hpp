
#ifndef NET_SOCKETBASE_HPP
#define NET_SOCKETBASE_HPP

#include"core/SocketHandle.hpp"
#include "core/Endpoint.hpp"
#include "core/NetworkError.hpp"
#include <vector>


namespace Net {

	class SocketBase {
	public:


		//virtual destructor
		virtual ~SocketBase();


		//Bind the socket to a specific endpoint (IP address and port)
		bool bind(const Endpoint& endPoint);


		//Delete copy constructor and copy assignment operator
		SocketBase(const SocketBase&) = delete;
		SocketBase& operator=(const SocketBase&) = delete;

		explicit operator bool() const {
			return static_cast<bool>(m_handle);
		}


	protected:

		//Protected constructor to be used by derived classes
		SocketBase(int addressFamily, int socketType, int protocol);

		//Socket handle object . Manages the lifetime of the underlying socket
		SocketHandle m_handle;


	};



}

#endif // End of file SocketBase_hpp