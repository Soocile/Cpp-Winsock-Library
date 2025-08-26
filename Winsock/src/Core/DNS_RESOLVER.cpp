#include "core/DNS_RESOLVER.hpp"

#include"core/NetworkError.hpp"
#include<WinSock2.h>
#include <WS2tcpip.h>
#include<iostream>


namespace Net {



    std::vector<Endpoint> DnsResolver::resolve(const std::string& hostname, const std::string& port) {

        addrinfo hints = {};
        hints.ai_family = AF_INET; // IPv4
        hints.ai_socktype = SOCK_STREAM; // SOCK_STREAM for TCP

        addrinfo* result = nullptr;
        int status = getaddrinfo(hostname.c_str(), port.c_str(), &hints, &result);

        if (status != 0) {
            throw NetworkError("getaddrinfo failed: " + std::string(gai_strerrorA(status)));

        }

        std::vector<Endpoint> endPoints;
        for (addrinfo* p = result; p != nullptr; p = p->ai_next) {
            Endpoint ep(*reinterpret_cast<sockaddr_in*>(p->ai_addr));
            endPoints.push_back(ep);
        }

        freeaddrinfo(result);

        return endPoints;
    }

    std::string DnsResolver::reverseResolve(const Endpoint& endPoint) {
        char host[NI_MAXHOST];      // Buffer to store the resolved hostname
        char service[NI_MAXSERV];   // Buffer to store the service (port) name

        // Get sockaddr_in structure from the Endpoint
        const sockaddr_in sockaddr = endPoint.getSockAddr();

        // Call getnameinfo to perform reverse DNS lookup
        int status = getnameinfo(
            reinterpret_cast<const SOCKADDR*>(&sockaddr), // Cast to generic sockaddr pointer
            sizeof(sockaddr),                             // Size of the sockaddr structure
            host,                                         // Hostname output buffer
            sizeof(host),                                 // Size of the hostname buffer
            service,                                      // Service (port) output buffer
            sizeof(service),                              // Size of the service buffer
            NI_NAMEREQD                                   // Require hostname, fail if not found
        );

        // Check if getnameinfo failed
        if (status != 0) {
            std::cerr << "getnameinfo failed: " << gai_strerrorA(status) << std::endl;
            // On failure, return fallback string: IP:port
            return endPoint.GetIPaddress() + ":" + std::to_string(endPoint.GetPort());
        }

        // Success: return hostname:service string
        return std::string(host) + ":" + std::string(service);
    }

}