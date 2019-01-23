#include <iostream>
#include <string>

#include "TcpListener.h"
#include "Potd.h"

void handleMessage(TcpListener* listener, SOCKET clientSock, std::string msgReceived);

void main() {
    TcpListener server("127.0.0.1", 55555, handleMessage);

    if (server.init()) {
        server.run();
    }
}

void handleMessage(TcpListener* listener, SOCKET clientSock, std::string msgReceived) {
    static Potd potd("poems.txt");
    if (msgReceived == "POEM") {
        listener->sendMsg(clientSock, potd.getRandomPoem());
    }
}