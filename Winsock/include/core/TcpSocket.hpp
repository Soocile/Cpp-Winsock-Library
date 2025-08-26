#ifndef TcpSocket_HPP
#define TcpSocket_HPP

#include "core/SocketBase.hpp"
#include "core/Endpoint.hpp"
#include "core/Packet.hpp"

#include <winsock2.h>
#include <ws2tcpip.h>
#include <concepts>
#include <string>
#include <string_view>
#include <iostream>

namespace Net {

    template<typename T>
    concept StringLike = requires(T t) {
        { t.size() } -> std::convertible_to<std::size_t>;
        { t.data() } -> std::convertible_to<const char*>;
    } || std::same_as<T, std::string> || std::same_as<T, std::string_view> || std::same_as<T, const char*>;

    class TcpSocket : public SocketBase {
    public:

        // Declarations only.
        SOCKET get() const;
        Endpoint getRemoteEndpoint() const;
        void close();

        // Methods for sending and receiving Packet objects
        int send(const Packet& packet) const;
        int receive(Packet& packet) const;

        // Constructors
        TcpSocket();
        TcpSocket(SOCKET socket);

        // Connection methods
        bool connect(const Endpoint& endpoint);
        TcpSocket accept() const;

        // Template functions for sending and receiving string-like data
        template<StringLike T>
        inline int send(const T& data) const {
            int bytesSent = ::send(m_handle.get(), reinterpret_cast<const char*>(data.data()),
                static_cast<int>(data.size()), 0);

            if (bytesSent == SOCKET_ERROR) {
                std::cerr << "Send failed with error: " << NetworkError::getLastErrorcode() << std::endl;
                return -1;
            }
            return bytesSent;
        }

        template<StringLike T>
        inline int receive(T& buffer) const {
            buffer.resize(1024); // Resize buffer to hold incoming data
            int bytesReceived = ::recv(m_handle.get(), reinterpret_cast<char*>(buffer.data()),
                static_cast<int>(buffer.size()), 0);

            if (bytesReceived > 0) {
                buffer.resize(bytesReceived); // Resize buffer to actual data size
            }
            else if (bytesReceived == 0) {
                return 0; // Connection closed
            }
            else {
                std::cerr << "Receive failed with error: " << NetworkError::getLastErrorcode() << std::endl;
                return -1;
            }
            return bytesReceived;
        }
    };

} // namespace Net

#endif // TCPSOCKET_HPP