#pragma once
#include <WinSock2.h>
#include <xstring>

class TcpSocket
{
public:
    TcpSocket(SOCKET Socket);

    static std::exception MakeException(const std::string& Message);

    int Receive(char* Buffer) const;

    void SendString(const std::string& Message) const;
    std::string ReceiveString() const;

    void SendFile(FILE* File) const;
    char* ReceiveFile() const;

private:
    SOCKET Socket;
};
