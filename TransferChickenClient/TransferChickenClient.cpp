
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

#include "Network/TCPClient.h"
#include "Network/TCPSocket.h"

int main(int argc, char* argv[])
{
    const TcpClient* Client = new TcpClient();
    const TcpSocket* Socket = Client->Connect("127.0.0.1", 8080);
    char Buffer[100000] = {};
    int Size = 0;
    while (true)
    {
        char TempBuffer[1024] = {};
        int BufferSize = Socket->Receive(TempBuffer);
        if (BufferSize <= 0)
        {
            break;
        }
        memcpy(&Buffer[Size], TempBuffer, BufferSize);
        Size += BufferSize;
    }
    std::cout << Size;
    FILE* File = fopen("C:/Work/Resource/chicken2.jpg", "wb");
    const int Result = fwrite(Buffer, sizeof(char), Size, File);
    fclose(File);

    return 0;
}
