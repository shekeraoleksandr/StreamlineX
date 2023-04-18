#include "server.h"
#pragma warning(disable: 4996)

namespace Net
{
	Server::Server(int port, std::string ipaddress)
		:
		wsa{ 0 },
		port(port),
		ipaddress(ipaddress),
		serversocket(INVALID_SOCKET),
		info{ 0 },
		infolength(sizeof(info)) {}

	void Server::init()
	{
		info.sin_family = AF_INET; //ip4
		info.sin_port = htons(port); //host to network (short)
		info.sin_addr.s_addr = inet_addr(ipaddress.c_str()); //ip adress

		printf("WSA init\n");
		assert(!(WSAStartup(514, &wsa)) && "Couldn`t init wsa"); //WSAStratrup return value 0
		printf("WSA success\n");

		printf("Creating socket\n");
		assert(!((serversocket = socket(AF_INET, SOCK_DGRAM, 0)) == SOCKET_ERROR) && "Couldn`t create socket");
		printf("Success!\n");

		printf("bind socket\n");
		assert(!(bind(serversocket, (struct sockaddr*) & info, infolength)) && "Couldn`t bind socket");
		printf("socket binded\n");

		printf("Server started at:%s:%d\n", inet_ntoa(info.sin_addr), ntohs(info.sin_port));
	}

	void Server::start()
	{
		init();

		for (;;)
		{
			receive();
			proccess();
			send();
		}
	}

	void Server::receive()
	{
		if ((recvlength = recvfrom(serversocket, buffer, SIZE, 0, (struct sockaddr*)&info, &infolength)) == SOCKET_ERROR)
		{
			printf("recv() failed...%d\n", WSAGetLastError());
			exit(EXIT_FAILURE);
		}
	}

	void Server::proccess()
	{
		printf("packet from:%s:%d\n", inet_ntoa(info.sin_addr), ntohs(info.sin_port));
		for (unsigned i = 0; i < recvlength; i++)
		{
			printf("%c", buffer[i]);
		}
		printf("\n");
	}

	void Server::send()
	{
		if ((sendto(serversocket, buffer, recvlength, 0, (struct sockaddr*)&info, infolength)) == SOCKET_ERROR)
		{
			printf("recv() failed...%d\n", WSAGetLastError());
			exit(EXIT_FAILURE);
		}
	}

	Server::~Server() 
	{
		WSACleanup();
		closesocket(serversocket);
	}
}