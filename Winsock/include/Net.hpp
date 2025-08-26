// NetLibrary/include/Net.hpp

#ifndef NET_HPP
#define NET_HPP

// Core Classes
#include "Core/EndPoint.hpp"
#include "Core/NetworkError.hpp"
#include "Core/NetworkManager.hpp"
#include "Core/SocketHandle.hpp"
#include "Core/SocketBase.hpp"
#include "Core/UDPSocket.hpp"
#include "Core/TCPSocket.hpp"
#include "core/DNS_RESOLVER.hpp"

// Packet Classes
#include "core/PacketHeader.hpp"
#include "core/Packet.hpp"

// Client Classes
#include "Client/UDPClient.hpp"
#include "Client/TCPClient.hpp"

// Server Classes
#include "Server/UDP_SERVER.hpp"
#include "Server/TCPServer.hpp"

// Utility Classes
#include "Utils/NonCopyable.hpp"

#endif // NET_HPP