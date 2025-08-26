

#ifndef NETWORK_ERROR_HPP
#define NETWORK_ERROR_HPP


#include <stdexcept>
#include <string>


class NetworkError : public std::runtime_error {


public:
	explicit NetworkError(const std::string& message) : std::runtime_error(message) {
	}

	static int getLastErrorcode() {
		return WSAGetLastError();
	}





};







#endif// End of file NetworkError.hpp