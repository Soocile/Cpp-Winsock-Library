
//*************************************************************************
//*********************************EXAMPLE*********************************
// ************************************************************************




//TCP SERVER  example using Net library.


#include<iostream>
#include"Net.hpp"
#include<vector>


void startTCPServer() {

	try {
		//start the winsock with the networkmanager
		Net::NetworkManager::initialize();
		while (true) {
			Net::TCPServer server("127.0.0.1",8080);
			std::cout << "TCP server is starting and listening on port 8080" << std::endl;

			if (!server.listen()) {
				std::cerr << "Failed to start listening on port 8080" << std::endl;
				return;
			}

			Net::TcpSocket clientSocket = server.accept();

			std::cout << "new client connected. address:" << clientSocket.getRemoteEndpoint().GetIPaddress() << std::endl;

			//can be added the rest of the server logic to  send/receive data...


			clientSocket.close();
			Net::NetworkManager::shutdown();
			std::cout << "Connection closed." << std::endl;

		}


	}
	catch (std::exception& e) {
		std::cerr << "Exception: " << e.what() << std::endl;
	}
}



	int main() {

		startTCPServer();

		return 0;

	}


