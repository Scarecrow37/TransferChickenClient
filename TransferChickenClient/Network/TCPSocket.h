#pragma once
#include <WinSock2.h>
#include <xstring>

class TcpSocket
{
public:
    TcpSocket(SOCKET Socket);

    static std::exception MakeException(const std::string& Message);

    void SendString(const std::string& Message) const;
    std::string ReceiveString() const;

    void SendFile(FILE* File) const;
    FILE* ReceiveFile() const;

private:
    SOCKET Socket;
};
