#pragma once
#include <WinSock2.h>

class TcpSocket;

class TcpClient
{
public:
    TcpClient();
    ~TcpClient();

    TcpSocket* Connect(const char* Address, u_short Port) const;
};
