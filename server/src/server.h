#pragma once
#include <cassert>
#include <iostream>
#include <thread>
#include <unordered_map>
#include <vector>
#include <WinSock2.h>

#pragma comment(lib, "Ws2_32.lib")

#define SIZE 1024

namespace Net
{
	class Server
	{
	private:
		WSADATA wsa;
		SOCKET serversocket;
		std::string ipaddress;
		int port;
		char buffer[SIZE];
		std::string message;
		struct sockaddr_in info;
		int infolength;
		int recvlength;
	public:
		Server(int, std::string);
		~Server();
	public:
		void start();
		//void stop();
	private:
		void init();
		void receive();
		void proccess();
		void send();
	};
}