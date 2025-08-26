#ifndef NET_DNSRESOLVER_HPP
#define NET_DNSRESOLVER_HPP

#include "core/Endpoint.hpp"
#include <string>
#include <vector>

namespace Net {

    class DnsResolver {
    public:
		// converts the hostname and port to an IP address and port.
        static std::vector<Endpoint> resolve(const std::string& hostname, const std::string& port);

		//converts the IP address and port to a hostname and port.
        static std::string reverseResolve(const Endpoint& endPoint);

    private:
		// Prevent instantiation of this class
        DnsResolver() = delete;
    };

} // namespace Net

#endif // NET_DNSRESOLVER_HPP

