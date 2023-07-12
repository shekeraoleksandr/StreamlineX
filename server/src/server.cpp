#include "server.h"


namespace Net
{
    Server::Server(int port, std::string ipaddress)
            : port(port),
              ipaddress(ipaddress),
              serversocket(0),
              info{ 0 },
              infolength(sizeof(info)) {}

    void Server::init()
    {
        info.sin_family = AF_INET;
        info.sin_port = htons(port);
        info.sin_addr.s_addr = inet_addr(ipaddress.c_str());

        printf("Creating socket\n");
        serversocket = socket(AF_INET, SOCK_DGRAM, 0);
        assert(serversocket >= 0 && "Couldn't create socket");
        printf("Success!\n");

        printf("bind socket\n");
        assert(bind(serversocket, (struct sockaddr*)&info, infolength) >= 0 && "Couldn't bind socket");
        printf("socket binded\n");

        printf("Server started at:%s:%d\n", inet_ntoa(info.sin_addr), ntohs(info.sin_port));
    }

	void Server::start()
	{
		init();

		for (;;)
		{
			receive();
			process();
			send();
		}
	}

    void Server::receive()
    {
        if ((recvlength = recvfrom(serversocket, buffer, SIZE, 0, (struct sockaddr*)&info, &infolength)) < 0)
        {
            perror("recv() failed");
            exit(EXIT_FAILURE);
        }
    }

    void Server::process()
    {
        printf("packet from:%s:%d\n", inet_ntoa(info.sin_addr), ntohs(info.sin_port));
        if (buffer[0] == 0x1)
        {
            std::vector<uint8_t> result(buffer, buffer + recvlength);

            int16_t it = 0;
            Primitive p = Primitive::unpack(result, it);
            primitives.insert(std::make_pair(p.getName(), p));
            current = p.getName();

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

    void Server::send()
    {
        if (primitives.empty())
        {
            if (sendto(serversocket, buffer, recvlength, 0, (struct sockaddr*)&info, infolength) < 0)
            {
                perror("send() failed");
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            int16_t it = 0;
            std::unique_ptr<Primitive> p = modify(current);
            std::vector<uint8_t> result(p->getSize());
            p->pack(result, it);
            std::copy(result.begin(), result.end(), buffer);

            if (sendto(serversocket, buffer, p->getSize(), 0, (struct sockaddr*)&info, infolength) < 0)
            {
                perror("send() failed");
                exit(EXIT_FAILURE);
            }

            primitives.erase(current);
        }
    }

    std::unique_ptr<Primitive> Server::modify(std::string key)
    {
        primitives.erase(key);

        int16_t bar = 75;
        std::unique_ptr<Primitive> p(Primitive::create("int16", Type::I16, bar));
        primitives.insert(std::make_pair(p->getName(), *p));

        current = p->getName();

        return p;
    }

    Server::~Server()
    {
        close(serversocket);
    }
}