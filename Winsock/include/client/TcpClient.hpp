

#ifndef TCPCLIENT_HPP
#define TCPCLIENT_HPP

#include "core/TcpSocket.hpp"
#include"core/Endpoint.hpp"
#include "core/DNS_RESOLVER.hpp"
#include <string>
#include <vector>


namespace Net {

	class TCPClient {
	
	public:

		//new methods for sending and receiving packets

		int send(const Packet& packet);
		int receive(Packet& packet);



		//constructor function which will start the client object
		TCPClient();

		bool connect(const std::string& hostname, unsigned short port);

		template<StringLike T>
		int send(const T& data);

		template<StringLike T>
		int receive(T& buffer);

		void disconnect();

		bool isConnected() const;


	private:

		TcpSocket m_socket;


	};





	template<StringLike T>
	inline int TCPClient::send(const T& data)
	{
		return m_socket.send(data);
	}

	template<StringLike T>
	inline int TCPClient::receive(T& buffer)
	{
		return m_socket.receive(buffer);
	}

}//namespace Net







#endif// End of file TcpClient.hpp