#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
        
#include <iostream>
#include <WinSock2.h>

#pragma comment(lib, "ws2_32")


int main()
{
    WSAData WsaData;
    WSAStartup(MAKEWORD(2,2), &WsaData);
    SOCKET ServerSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    SOCKADDR_IN ServerAddress = {};
    ServerAddress.sin_family = AF_INET;
    ServerAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    ServerAddress.sin_port = htons(8080);
    connect(ServerSocket, reinterpret_cast<SOCKADDR*>(&ServerAddress), sizeof(ServerAddress));
    char Buffer[100000] = {};
    int Size = 0;
    while (true)
    {
        char TempBuffer[1024] = {};
        int ReceiveByte = recv(ServerSocket, TempBuffer, sizeof(TempBuffer), 0);
        if (ReceiveByte <= 0)
        {
            break;
        }
        memcpy(&Buffer[Size], TempBuffer, ReceiveByte);
        Size += ReceiveByte;
    }
    FILE* ChickenImage = {};
    fopen_s(&ChickenImage, "./Resource/chicken.jpg", "wb");
    fwrite(Buffer, sizeof(char), Size, ChickenImage);
    fclose(ChickenImage);
    WSACleanup();
    return 0;
}
