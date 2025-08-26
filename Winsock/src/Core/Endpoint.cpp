#include "core/Endpoint.hpp" // For Endpoint class
#include <winsock2.h>       // For sockaddr_in, AF_INET, htons, etc.
#include <ws2tcpip.h>       // For inet_pton, inet_ntop, INET_ADDRSTRLEN
#include <string>           // For std::string and std::to_string
#include <stdexcept>        // For std::invalid_argument
#include <string.h>         // For memset
#include <iostream>

namespace Net {

    Endpoint::Endpoint()
    {
        memset(&m_sockaddr, 0, sizeof(m_sockaddr));
        m_sockaddr.sin_family = AF_INET; // IPv4
    }

    Endpoint::Endpoint(const std::string& address, unsigned short port)
    {
        memset(&m_sockaddr, 0, sizeof(m_sockaddr));
        m_sockaddr.sin_family = AF_INET; // IPv4
        m_sockaddr.sin_port = htons(port); // Host to Network Short

        // Convert string IP address to binary form
        if (inet_pton(AF_INET, address.c_str(), &m_sockaddr.sin_addr) != 1)
        {
            throw std::invalid_argument("Invalid IP address format");
        }
    }

    Endpoint::Endpoint(const sockaddr_in& sockAddr)
    {
        m_sockaddr = sockAddr;
    }

    std::string Endpoint::GetIPaddress() const
    {
        char ipstr[INET_ADDRSTRLEN]; // INET_ADDRSTRLEN is 16 for IPv4
        inet_ntop(AF_INET, &m_sockaddr.sin_addr, ipstr, sizeof(ipstr));

        return std::string(ipstr);
    }

    unsigned short Endpoint::GetPort() const
    {
        return ntohs(m_sockaddr.sin_port); // Network to Host Short
    }

    sockaddr_in Endpoint::getSockAddr() const
    {
        return m_sockaddr;
    }

    void Endpoint::setAddress(const std::string& address, unsigned short port)
    {
        memset(&m_sockaddr, 0, sizeof(m_sockaddr));
        m_sockaddr.sin_family = AF_INET; // IPv4
        m_sockaddr.sin_port = htons(port); // Host to Network Short

        if (inet_pton(AF_INET, address.c_str(), &m_sockaddr.sin_addr) != 1)
        {
            throw std::invalid_argument("Invalid IP address format");
        }
    }

    Endpoint::~Endpoint() {}

} // namespace Net