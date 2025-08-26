#include "core/TcpSocket.hpp"
#include "core/NetworkError.hpp"
#include "core/SocketHandle.hpp"
#include "core/Packet.hpp"
#include "core/Endpoint.hpp"

#include <winsock2.h>
#include <ws2tcpip.h>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <string>

namespace Net {

    SOCKET TcpSocket::get() const {
        return m_handle.get();
    }

    Endpoint TcpSocket::getRemoteEndpoint() const {
        if (!m_handle) {
            return Endpoint();
        }
        sockaddr_in remoteAddr;
        int addrlen = sizeof(remoteAddr);

        if (::getpeername(m_handle.get(), reinterpret_cast<SOCKADDR*>(&remoteAddr), &addrlen) == SOCKET_ERROR) {
            std::cerr << "getpeername failed with error: " << NetworkError::getLastErrorcode() << std::endl;
            return Endpoint(); // Return an invalid endpoint on failure.
        }

        return Endpoint(remoteAddr);
    }

    void TcpSocket::close() {
        if (m_handle) {
            ::closesocket(m_handle.get());
            m_handle = SocketHandle(); // Reset to an invalid state
        }
    }

    int TcpSocket::send(const Packet& packet) const
    {
        const auto& buffer = packet.getBytes();
        int bytesSent = ::send(m_handle.get(), buffer.data(), static_cast<int>(buffer.size()), 0);

        if (bytesSent == SOCKET_ERROR) {
            std::cerr << "send failed with error:" << NetworkError::getLastErrorcode() << std::endl;
            return -1;
        }
        return bytesSent;
    }

    int TcpSocket::receive(Packet& packet) const
    {
        // Step 1: Receive the Packet Header
        packetheader header;
        int headerBytes = ::recv(m_handle.get(), reinterpret_cast<char*>(&header), sizeof(header), 0);

        if (headerBytes <= 0) {
            return headerBytes; // connection is closed or error occurred
        }

        // step 2 Get the payload
        std::vector<char> payloadBuffer;
        payloadBuffer.resize(header.payloadsize);
        int payloadBytes = ::recv(m_handle.get(), payloadBuffer.data(), static_cast<int>(payloadBuffer.size()), 0);

        if (payloadBytes <= 0) {
            return payloadBytes; // connection is closed or error occurred
        }

        // step 3: write the data to the packet object
        packet.clear(); // clear any existing data
        packet.add(header.packet_type); // add the packet type
        packet.add(payloadBuffer); // add the payload data

        return headerBytes + payloadBytes;
    }

    TcpSocket::TcpSocket() : SocketBase(AF_INET, SOCK_STREAM, IPPROTO_TCP) {}

    TcpSocket::TcpSocket(SOCKET socket) : SocketBase(AF_INET, SOCK_STREAM, IPPROTO_TCP)
    {
        m_handle = SocketHandle(socket);
    }

    bool TcpSocket::connect(const Endpoint& endpoint)
    {
        const sockaddr_in sockaddr = endpoint.getSockAddr();

        if (::connect(m_handle.get(), reinterpret_cast<const SOCKADDR*>(&sockaddr), sizeof(sockaddr)) == SOCKET_ERROR) {
            std::cerr << "Connect failed with error: " << NetworkError::getLastErrorcode() << std::endl;
            return false;
        }
        return true;
    }

    TcpSocket TcpSocket::accept() const
    {
        sockaddr_in clientAddr;
        int addrLen = sizeof(clientAddr);
        SOCKET clientSocket = ::accept(m_handle.get(), reinterpret_cast<SOCKADDR*>(&clientAddr), &addrLen);
        if (clientSocket == INVALID_SOCKET) {
            throw NetworkError("Accept failed with error: " + std::to_string(NetworkError::getLastErrorcode()));
        }
        return TcpSocket(clientSocket);
    }
} // namespace Net