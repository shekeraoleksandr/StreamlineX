#include "client.h"

using namespace ObjectModel;

namespace Net
{
    Client::Client(int port, std::string ipaddress)
            : port(port),
              ipaddress(ipaddress),
              clientsocket(0),
              info{ 0 },
              infolength(sizeof(info))
    {
    }

    void Client::init()
    {
        info.sin_family = AF_INET;
        info.sin_port = htons(port);
        info.sin_addr.s_addr = inet_addr(ipaddress.c_str());

        printf("Creating socket\n");
        clientsocket = socket(AF_INET, SOCK_DGRAM, 0);
        assert(clientsocket >= 0 && "Couldn't create socket");
        printf("Success!\n");
    }

    void Client::connect()
    {
        init();

        for (;;)
        {
            send();
            receive();
            process();
        }
    }

    void Client::send()
    {
        printf("Enter a message:");
        std::getline(std::cin, message);

        if (message == "prim")
        {
            int32_t foo = 53;
            int16_t it = 0;
            std::unique_ptr<Primitive> p = Primitive::create("int32", Type::I32, foo);
            std::vector<uint8_t> result(p->getSize());
            p->pack(result, it);
            std::copy(result.begin(), result.end(), buffer);

            if (sendto(clientsocket, buffer, p->getSize(), 0, (struct sockaddr*)&info, infolength) < 0)
            {
                perror("send() failed");
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            if (sendto(clientsocket, message.c_str(), message.size(), 0, (struct sockaddr*)&info, infolength) < 0)
            {
                perror("send() failed");
                exit(EXIT_FAILURE);
            }
        }
    }

    void Client::receive()
    {
        if ((recvlength = recvfrom(clientsocket, buffer, SIZE, 0, (struct sockaddr*)&info, &infolength)) < 0)
        {
            perror("recv() failed");
            exit(EXIT_FAILURE);
        }
    }

    void Client::process()
    {
        printf("packet from:%s:%d\n", inet_ntoa(info.sin_addr), ntohs(info.sin_port));
        if (buffer[0] == 0x1)
        {
            std::vector<uint8_t> result(buffer, buffer + recvlength);

            int16_t it = 0;
            Primitive p = Primitive::unpack(result, it);

            printf("Primitive:\n");
            printf("\t |Name:%s\n", p.getName().c_str());
            printf("\t |Size:%d\n", p.getSize());
            printf("\t |Data:");

            for (auto i : p.getData())
            {
                printf("[%d]", i);
            }

            printf("\n");
        }
        else
        {
            printf("data:");
            for (int i = 0; i < recvlength; i++)
            {
                printf("%c", buffer[i]);
            }
            printf("\n");
        }
    }

    Client::~Client()
    {
        close(clientsocket);
    }
}