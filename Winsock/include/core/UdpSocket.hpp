
#ifndef NET_UDPSOCKET_HPP
#define NET_UDPSOCKET_HPP

#include "SocketBase.hpp"
#include "Endpoint.hpp"
#include "Packet.hpp"   
#include <winsock2.h> 
#include <ws2tcpip.h> 
#include <string>
#include <vector>

namespace Net {

    class UDPSocket : public SocketBase {
    public:

		//*********************************************************
		//new methods for sending and receiving packets
        int sendTo(const Packet& packet, const Endpoint& destination);
        
        int receiveFrom(Packet& packet, Endpoint& sender);

        //*********************************************************
  
       
        // Constructor : it creates the udp socket
        UDPSocket();

        //sending data function
        int sendTo(const std::vector<char>& data, const Endpoint& destination);

      //receiving data function
        int receiveFrom(std::vector<char>& buffer, Endpoint& sender);

        SOCKET get() const {
            return m_handle.get();
        }

    };

} // namespace Net

#endif // NET_UDPSOCKET_HPP