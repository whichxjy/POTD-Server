#include "TcpListener.h"
#include <iostream>

TcpListener::TcpListener(std::string ipAddress, int port, MessageHandler handler)
    : m_ipAddress(ipAddress), m_port(port), messageHandler(handler) {
    // Empty
}

TcpListener::~TcpListener() {
    cleanup();
}

// Send a message to the specified client
void TcpListener::sendMsg(SOCKET clientSock, std::string msg) {
    send(clientSock, msg.c_str(), msg.size() + 1, 0);
}

// Initialize winsock
bool TcpListener::init() {
    WSAData wsaData;
    WORD sockVersion = MAKEWORD(2, 2);
    return WSAStartup(sockVersion, &wsaData) == 0;
}

// The main processing loop
void TcpListener::run() {
    char buf[MAX_BUFFER_SIZE];

    // Create a listening socket
    SOCKET listenSock = socket(AF_INET, SOCK_STREAM, 0);
    if (listenSock == INVALID_SOCKET) {
        std::cerr << "Can't create a socket! Quitting" << std::endl;
        return;
    }

    SOCKADDR_IN serverAddr;
    ZeroMemory((char*)&serverAddr, sizeof(serverAddr)); // clear address structure

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(m_port);
    inet_pton(AF_INET, m_ipAddress.c_str(), &serverAddr.sin_addr);

    if (bind(listenSock, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        return;
    }

    if (listen(listenSock, SOMAXCONN) == SOCKET_ERROR) {
        return;
    }

    SOCKADDR_IN clientAddr;
    int clientAddrSize = sizeof(clientAddr);
    while (true) {
        // Wait for connection
        SOCKET client = accept(listenSock, (SOCKADDR *)&clientAddr, &clientAddrSize);
        if (client == INVALID_SOCKET) {
            break;
        }

        std::cout << "Client connected!" << std::endl;

        while (true) {
            ZeroMemory(buf, MAX_BUFFER_SIZE);
            int bytesReceived = recv(client, buf, MAX_BUFFER_SIZE, 0);
            if (bytesReceived > 0 && messageHandler != NULL) {
                messageHandler(this, client, std::string(buf));
            }
            else {
                break;
            }
        }

        closesocket(client);
    }

    closesocket(listenSock);
}

void TcpListener::cleanup() {
    WSACleanup();
}