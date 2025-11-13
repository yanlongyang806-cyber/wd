#include "nw_network.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>

#pragma comment(lib, "ws2_32.lib")

bool ConnectToServer(const std::string& ip, int port)
{
    WSADATA wsaData;
    SOCKET sock = INVALID_SOCKET;

    sockaddr_in service{};

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        std::cout << "[!] WSAStartup failed\n";
        return false;
    }

    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (sock == INVALID_SOCKET)
    {
        std::cout << "[!] Create socket failed\n";
        WSACleanup();
        return false;
    }

    service.sin_family = AF_INET;
    service.sin_addr.s_addr = inet_addr(ip.c_str());
    service.sin_port = htons(port);

    std::cout << "[+] Connecting " << ip << ":" << port << "...\n";

    int result = connect(sock, (SOCKADDR*)&service, sizeof(service));

    if (result == SOCKET_ERROR)
    {
        std::cout << "[!] Connection failed\n";
        closesocket(sock);
        WSACleanup();
        return false;
    }

    std::cout << "[+] OK\n";

    closesocket(sock);
    WSACleanup();
    return true;
}
