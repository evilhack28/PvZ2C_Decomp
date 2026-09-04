//
//  TcpClient.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-04.
//

#include "SexyAppFramework/Common.h"

#include "logServer/TcpClient.h"

#include <cstdio>
#include <string>
#include <unistd.h>

TcpClient::TcpClient()
{
	mSocket = -1;
	m_Endpoint = NULL;
}

TcpClient::~TcpClient()
{
	if (m_Endpoint)
		freeaddrinfo(m_Endpoint);
}

void TcpClient::CloseSocket()
{
	if (mSocket >= 0)
	{
		shutdown(mSocket, SHUT_RDWR);
		close(mSocket);
	}
	mSocket = -1;
}

int TcpClient::ConnetServer()
{
	mSocket = socket(m_Endpoint->ai_family, m_Endpoint->ai_socktype, m_Endpoint->ai_protocol);
	if (mSocket < 0)
	{
		puts("Failed to create socket");
		CloseSocket();
		return -1;
	}

	int on = 1;
	setsockopt(mSocket, SOL_SOCKET, NO_SIGNAL, &on, sizeof(on));

	if (connect(mSocket, m_Endpoint->ai_addr, m_Endpoint->ai_addrlen) == -1)
	{
		CloseSocket();
		puts("connect failed");
		return -1;
	}

	return 0;
}

int TcpClient::InitSocket(const char* ip, unsigned short port)
{
	addrinfo hints;
	memset(&hints, 0, sizeof(hints));
	hints.ai_flags = AF_INET;
	hints.ai_socktype = SOCK_STREAM;

	int rc = getaddrinfo(ip, std::to_string(port).c_str(), &hints, &m_Endpoint);
	if (rc != 0)
	{
		printf("getaddrinfo error: %s\n", gai_strerror(rc));
		return -1;
	}

	return 1;
}

int TcpClient::SentMsg(const char* msg, unsigned short len)
{
	int total = 0;

	if (ConnetServer() != 0)
	{
		puts(" ======connect error ");
		return -1;
	}

	do
	{
		int n = send(mSocket, msg + total, len, 0);
		len -= n;
		total += n;
		if (n <= 0)
		{
			printf(" error   send len = [%d]\n", n);
			CloseSocket();
			return -1;
		}
	} while (len > 0);

	CloseSocket();
	return total;
}
