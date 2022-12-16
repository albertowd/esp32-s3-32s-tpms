#include <Arduino.h>

#include <errno.h>

#include "SocketServer.h"

SocketServer::SocketServer(size_t port) : clientId(0), socketId(0), port(port)
{
    this->serverAddress.sin_family = AF_INET;
    this->serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    this->serverAddress.sin_port = htons(this->port);
}

SocketServer::~SocketServer()
{
    if (this->socketId)
    {
        if (this->clientId) {
            Serial.printf("Closing client... %d\n", this->clientId);
            const int closeRet(close(this->clientId));
            if (closeRet)
            {
                Serial.printf("Closing client error: %d %s\n", closeRet, strerror(errno));
            }
            this->clientId = 0;
        }

        Serial.printf("Shutind down server socket %d...\n", this->socketId);
        if (shutdown(this->socketId, SHUT_RDWR))
        {
            Serial.printf("Socket creation error: %d %s\n", this->socketId, strerror(errno));
            exit(errno);
        }
        this->socketId = 0;
    }
}

void SocketServer::accetFirstClient()
{
    int newClientId(0);
    struct sockaddr_in clientAddress;
    socklen_t clientAddressLength = sizeof(clientAddress);
    this->clientId = accept(this->socketId, (sockaddr *)&clientAddress, &clientAddressLength);
    if (0 >= this->clientId)
    {
        Serial.printf("Accepting new client error: %d %s\n", this->clientId, strerror(errno));
    }
    else
    {
        char ipStr[24];
        inet_ntop(AF_INET, &(clientAddress.sin_addr), ipStr, 24);
        Serial.printf("New client: %d IP: %s\n", this->clientId, ipStr);
    }
}

void SocketServer::initServer()
{
    this->socketId = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (this->socketId < 0)
    {
        this->socketId = 0;
        Serial.printf("Socket creation error: %d %s\n", this->socketId, strerror(errno));
        exit(errno);
    }

    const int bindRet(bind(this->socketId, (struct sockaddr *)&this->serverAddress, sizeof(this->serverAddress)));
    if (bindRet)
    {
        Serial.printf("Socket bind error: %d %s\n", bindRet, strerror(errno));
        exit(errno);
    }

    const int listenRet(listen(this->socketId, 1));
    if (listenRet)
    {
        Serial.printf("Listen error: %d %s\n", listenRet, strerror(errno));
        exit(errno);
    }
}

void SocketServer::writeToClient(std::string data)
{
    if (this->clientId && this->socketId) {
        const char *dataPtr(data.c_str());
        const size_t dataSize(data.length());

        Serial.printf("Sending message %s", dataPtr, this->clientId);
        send(this->clientId, dataPtr, dataSize, 0);
    }
}
