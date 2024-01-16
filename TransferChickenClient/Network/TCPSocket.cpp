#include "TCPSocket.h"

#include <iostream>
#include <string>


TcpSocket::TcpSocket(const SOCKET Socket) : Socket(Socket)
{
}

void TcpSocket::SendString(const std::string& Message) const
{
    const int Byte = send(Socket, Message.c_str(), static_cast<int>(Message.size()), 0);
    if (Byte < 0)
    {
        throw MakeException("Send fail.");
    }
    if (Byte == 0)
    {
        throw MakeException("Disconnected.");
    }
}

std::string TcpSocket::ReceiveString() const
{
    char Buffer[1024] = {};
    const int Byte = recv(Socket, Buffer, sizeof(Buffer), 0);
    std::string ReceiveMessage(Buffer);
    return ReceiveMessage;
}

void TcpSocket::SendFile(FILE* File) const
{
    char Buffer[1024] = {};
    const int Result = fread(Buffer, sizeof(FILE), 1, File);
    if (Result == 0)
    {
        throw MakeException("File read fail.");
    }
    const int Byte = send(Socket, Buffer, 1024, 0);
    if (Byte < 0)
    {
        throw MakeException("Send fail.");
    }
    if (Byte == 0)
    {
        throw MakeException("Disconnected.");
    }
}

FILE* TcpSocket::ReceiveFile() const
{
    return nullptr;
}

std::exception TcpSocket::MakeException(const std::string& Message)
{
    const DWORD ErrorCode = GetLastError();
    std::string ExceptionMessage;
    ExceptionMessage.append("[");
    ExceptionMessage.append(std::to_string(ErrorCode));
    ExceptionMessage.append("] ");
    ExceptionMessage.append(Message);
    return std::exception(ExceptionMessage.c_str());
}
