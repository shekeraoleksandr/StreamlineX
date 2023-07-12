#pragma once
#include <cassert>
#include <iostream>
#include <thread>
#include <unordered_map>
#include <vector>
#include <string>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "serialization.h"

#define SIZE 1024

namespace Net
{
    class Client
    {
    private:
        int clientsocket;
        std::string ipaddress;
        int port;
        char buffer[SIZE];
        std::string message;
        struct sockaddr_in info;
        socklen_t infolength;
        int recvlength;

    public:
        Client(int, std::string);
        ~Client();

    public:
        void connect();

    private:
        void init();
        void receive();
        void process();
        void send();
    };
}
