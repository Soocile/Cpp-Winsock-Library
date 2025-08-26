#pragma once

#ifndef NET_TCPSERVER_HPP
#define NET_TCPSERVER_HPP

#include<string>
#include "core/TcpSocket.hpp"
#include "core/Endpoint.hpp"
#include <vector>
#include "core/Packet.hpp"

namespace Net {

    class TCPServer {
    public:
        // Constructor function which listens on the defined port
        TCPServer(unsigned short port);

        TCPServer(const std::string& ip_addr, unsigned short port);

        // starts connecting new connections
        // backlog: the size of the pending connection queue
        bool listen(int backlog = 5);

        // connects the new connection and returns new socket
        TcpSocket accept() const;

    private:
        TcpSocket m_socket;
    };

} // namespace Net

#endif // NET_TCPSERVER_HPP
