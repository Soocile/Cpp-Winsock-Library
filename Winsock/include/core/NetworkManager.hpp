
#ifndef NETWORKMANAGER_HPP
#define NETWORKMANAGER_HPP

#include <winsock2.h>
#include <ws2tcpip.h>
#include "core/NetworkError.hpp"

namespace Net {

	class NetworkManager {

	public:

		static void initialize();

		static void shutdown();


		NetworkManager(const NetworkManager&) = delete;
		NetworkManager& operator=(const NetworkManager&) = delete;

	private:

		NetworkManager() = default;
		~NetworkManager() = default;

		static bool m_isInitialized;
	};



}





#endif// End of file NetworkManager.hpp