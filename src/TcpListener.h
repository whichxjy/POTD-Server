#pragma once

#include <string>
#include <WS2tcpip.h>

#pragma comment(lib, "ws2_32.lib") // Winsock library file

#define MAX_BUFFER_SIZE 50000

// Forward declaration of class
class TcpListener;

// Callback to data received
using MessageHandler = void (*)(TcpListener* listener, SOCKET socket, std::string msgReceived);

class TcpListener {
public:
    // Constructor
    TcpListener(std::string ipAddress, int port, MessageHandler handler);

    // Destructor
    ~TcpListener();

    // Send a message to the specified client
    void sendMsg(SOCKET clientSocket, std::string msg);

    // Initialize winsock
    bool init();

    // The main processing loop
    void run();

    // Clean up after using the service
    void cleanup();

private:
    // Address of the server
    std::string m_ipAddress;

    // Listening port
    int m_port;

    // Message received event handler
    MessageHandler messageHandler;
};