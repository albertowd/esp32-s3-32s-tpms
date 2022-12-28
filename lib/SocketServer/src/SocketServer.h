#ifndef SOCKET_SERVER_H
#define SOCKET_SERVER_H

#include <lwip/sockets.h>
#include <string>
#include <vector>

class SocketServer
{
private:
    int clientId;
    int socketId;
    size_t port;
    struct sockaddr_in serverAddress;

    void addClient();
    void closeClient();

public:
    SocketServer(size_t port);
    ~SocketServer();

    void accetFirstClient();
    void initServer();
    void writeToClient(std::string data);
};

#endif
