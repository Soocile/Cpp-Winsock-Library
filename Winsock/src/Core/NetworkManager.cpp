#include "core/NetworkManager.hpp"

bool Net::NetworkManager::m_isInitialized = false;

void Net::NetworkManager::initialize()
{

	if (m_isInitialized) {
		return;//if its already started dont do anything
	}

	WSADATA wsadata;

	int result = WSAStartup(MAKEWORD(2, 2), &wsadata);

	if(result != 0) {
		throw NetworkError("WSAStartup failed with error: " + std::to_string(result));
	} 

		m_isInitialized = true;
}

void Net::NetworkManager::shutdown()
{

	if(!m_isInitialized) {
		return;//if its not started dont do anything
	}
	else {
		WSACleanup();
		m_isInitialized = false;
	}
}
