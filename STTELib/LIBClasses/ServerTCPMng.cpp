#include "StdAfx.h"
#include "ServerTCPMng.h"


ServerTCPMng::ServerTCPMng(void)
{
	m_bIsConnected = FALSE;
	m_ConnectSocket = INVALID_SOCKET;
	m_rxBuffer.reserve(RX_BUFFER_SIZ*2); // per evitare reallocazione
}

ServerTCPMng::~ServerTCPMng(void)
{

}

BOOL ServerTCPMng::Listen(CServerParam params)
{
	m_ServerPar = params;
	CString szId;
	szId.Format(_T("SERVER %d"), m_ServerPar.id);

	m_bIsConnected = FALSE;
	WSADATA wsaData;
	int iResult;

	SOCKET ListenSocket = INVALID_SOCKET;
	SOCKET ClientSocket = INVALID_SOCKET;

	struct addrinfo* result = NULL;
	struct addrinfo hints;

	int iSendResult = 0;

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) 
	{
		TRACE(_T("WSAStartup failed with error: %d\n"), iResult);
		return FALSE;
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	// Resolve the server address and port
	CStringA szA;
	szA.Format(("%d"), m_ServerPar.m_nPort);
	iResult = getaddrinfo(NULL, szA, &hints, &result);
	if (iResult != 0) 
	{
		TRACE(_T("getaddrinfo failed with error: %d\n"), iResult);
		WSACleanup();
		return FALSE;
	}

	// Create a SOCKET for connecting to server
	ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (ListenSocket == INVALID_SOCKET) 
	{
		TRACE(_T("socket failed with error: %ld\n"), WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		return FALSE; 
	}

	if (m_ServerPar.bDisableNagle)
	{
		int iOptVal = 0;
		int iOptLen = sizeof(int);

		BOOL bOptVal = FALSE;
		int bOptLen = sizeof(BOOL);

		/* keep-alive off */
		//int iResult = setsockopt(m_Socket[0].Socket, SOL_SOCKET, SO_KEEPALIVE, (char*)& bOptVal, bOptLen);

		// Nagle's algorithm off 
		bOptVal = TRUE;
		iResult |= setsockopt(ListenSocket, SOL_SOCKET, TCP_NODELAY, (char*)& bOptVal, bOptLen);
		//iResult |= setsockopt(m_Socket[0].Socket, SOL_SOCKET, SO_SNDBUF, (char*)& iOptVal, iOptLen);
		//iOptVal = 1000; /* 1 sec timeout */
		//iResult |= setsockopt(m_Socket[0].Socket, SOL_SOCKET, SO_RCVTIMEO, (char*)& iOptVal, iOptLen);
		//iResult |= setsockopt(m_Socket[0].Socket, SOL_SOCKET, SO_SNDBUF, (char*)& iOptVal, iOptLen);
		if (iResult == SOCKET_ERROR)
		{
			WSACleanup();
			return FALSE;
		}
	}

	// Setup the TCP listening socket
	iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR) 
	{
		TRACE(_T("bind failed with error: %d\n"), WSAGetLastError());
		freeaddrinfo(result);
		closesocket(ListenSocket);
		WSACleanup();
		return FALSE;
	}

	freeaddrinfo(result);
	iResult = listen(ListenSocket, SOMAXCONN);
	if (iResult == SOCKET_ERROR) 
	{
		TRACE(_T("listen failed with error: %d\n"), WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return FALSE;
	}

	m_ListenSocket = ListenSocket;
	_startThread(szId);
	return TRUE;
}

void ServerTCPMng::_begin()
{
	// Accept a client socket
	m_ConnectSocket = accept(m_ListenSocket, NULL, NULL);
	if (m_ConnectSocket == INVALID_SOCKET)
	{
		TRACE(_T("accept failed with error: %d\n"), WSAGetLastError());
		closesocket(m_ListenSocket);
		WSACleanup();
		return;
	}

	// No longer need server socket
	closesocket(m_ListenSocket);
	m_cs.Lock();
	m_bIsConnected = TRUE;
	m_cs.Unlock();
}

BOOL ServerTCPMng::_Recv(unsigned char* pData, int& nSize, int nMaxAvlSize)
{
	m_cs.Lock();
	BOOL bConn = m_bIsConnected;
	m_cs.Unlock();

	if (!bConn)
		return FALSE;

	nSize = recv(m_ConnectSocket, (char*)pData, nMaxAvlSize, 0);
	if (nSize > 0) 
	{
		TRACE(_T("Bytes received: %d\n"), nSize);
	}
	else if (nSize == 0)
	{
		m_cs.Lock();
		m_bIsConnected = FALSE;
		m_cs.Unlock();
		return FALSE;
	}
	else 
	{
		m_cs.Lock();
		m_bIsConnected = FALSE;
		m_cs.Unlock();
		return FALSE;
	}

	return TRUE;
}

BOOL ServerTCPMng::IsConnected()
{
	m_cs.Lock();
	BOOL res = m_bIsConnected;
	m_cs.Unlock();
	return res;
}

BOOL ServerTCPMng::Send(unsigned char* pData, int nSize)
{
	m_cs.Lock();
	BOOL bConn = m_bIsConnected;
	m_cs.Unlock();

	if (!bConn)
		return FALSE;

	int iSendResult = send(m_ConnectSocket, (char*)pData, nSize, 0);
	if (iSendResult == SOCKET_ERROR) 
	{
		m_cs.Lock();
		m_bIsConnected = FALSE;
		m_cs.Unlock();
		return FALSE;
	}
	TRACE(_T("Bytes sent: %d\n"), iSendResult);

	return TRUE;
}

void ServerTCPMng::_finished()
{
}

BOOL ServerTCPMng::Disconnect()
{
	// shutdown the connection since we're done
	int iResult = shutdown(m_ConnectSocket, SD_SEND);
	if (iResult == SOCKET_ERROR) 
	{
		TRACE(_T("shutdown failed with error: %d\n"), WSAGetLastError());
	}

	closesocket(m_ConnectSocket);
	WSACleanup();
	m_cs.Lock();
	m_bIsConnected = FALSE;
	m_cs.Unlock();
	_stopThread();

	return TRUE;
}

void ServerTCPMng::_loop()
{
	int nSize = 0;
	BOOL bRes = _Recv(m_rxTmpBuf, nSize, TMP_RX_BUF_SIZ);
	if (bRes && (nSize > 0))
	{
		m_cs.Lock();
		for(int i=0;i<nSize;i++)
		{
			m_rxBuffer.push_back(m_rxTmpBuf[i]);
		}
		m_cs.Unlock();
	}
}

int ServerTCPMng::CIRCBUFF_GetBytesAvailForRead()
{
	m_cs.Lock();
	auto ret = m_rxBuffer.size();
	m_cs.Unlock();
	return (int)ret;
}

void ServerTCPMng::CIRCBUFF_GetData(std::vector<unsigned char>& v)
{
	v.clear();
	m_cs.Lock();
	v = m_rxBuffer;
	m_rxBuffer.clear();
	m_cs.Unlock();
}
