// src/server/UdpServer.cpp

#include "server/UDP_SERVER.hpp"
#include "core/Endpoint.hpp"
#include "core/Packet.hpp"
#include "core/NetworkError.hpp"

#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdexcept>
#include <string>
#include <iostream>

namespace Net {

    UDPServer::UDPServer(unsigned short port) : m_socket()
    {
        Endpoint bindEndpoint("127.0.0.1", port);

        if (!m_socket.bind(bindEndpoint)) {
            // Consistent error handling
            throw NetworkError("Failed to bind UDP socket to port " + std::to_string(port) + ": " + std::to_string(NetworkError::getLastErrorcode()));
        }
    }

    UDPServer::~UDPServer() {}

    int UDPServer::receiveFrom(Packet& packet, Endpoint& sender_endpoint)
    {
        // Corrected function call to receiveFrom
        return m_socket.receiveFrom(packet, sender_endpoint);
    }
}