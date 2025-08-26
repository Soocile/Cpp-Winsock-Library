#ifndef UDP_SERVER_HPP
#define UDP_SERVER_HPP

#include "core/UdpSocket.hpp"
#include "core/Endpoint.hpp"
#include "core/Packet.hpp"
#include <vector>
#include<WinSock2.h>



namespace Net {

    class UDPServer {

    public:

        UDPServer(unsigned short port);
        ~UDPServer();

        // New method for receiving data, consistent with the .cpp file
        int receiveFrom(Packet& packet, Endpoint& sender_endpoint);

    private:

        UDPSocket m_socket;
    };

} // namespace Net

#endif // UDP_SERVER_HPP