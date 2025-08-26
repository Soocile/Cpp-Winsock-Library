#include "server/Tcpserver.hpp"
#include "core/NetworkError.hpp"
#include "core/Endpoint.hpp"
#include "core/TcpSocket.hpp"

#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <string>
#include <stdexcept>
#include <system_error>

namespace Net {

    TCPServer::TCPServer(unsigned short port)
        : m_socket()
    {
        Endpoint bindEndpoint("127.0.0.1", port);
        if (!m_socket.bind(bindEndpoint)) {
            throw NetworkError("Failed to bind socket to port " + std::to_string(port) + ": "+ std::to_string(NetworkError::getLastErrorcode()));
        }
    }

    TCPServer::TCPServer(const std::string& ipAddress, unsigned short port)
        : m_socket()
    {
        Endpoint bindEndpoint(ipAddress, port);
        if (!m_socket.bind(bindEndpoint)) {
            throw std::runtime_error("Failed to bind TCP server socket to " + ipAddress);
        }
    }

    bool TCPServer::listen(int backlog) {

        if (::listen(m_socket.get(), backlog) == SOCKET_ERROR) {
            // throw the NetworkError with a clear message
            throw NetworkError("Failed to listen on socket: " + NetworkError::getLastErrorcode());
        }

        return true;
    }

    TcpSocket TCPServer::accept() const {
        sockaddr_in clientAddr;
        int client_addr_size = sizeof(clientAddr);
        SOCKET clientSocket = ::accept(m_socket.get(), reinterpret_cast<sockaddr*>(&clientAddr), &client_addr_size);

        if (clientSocket == INVALID_SOCKET) {
            throw NetworkError("Failed to accept connection: " + NetworkError::getLastErrorcode());
        }

        return TcpSocket(clientSocket);
    }

} // namespace Net