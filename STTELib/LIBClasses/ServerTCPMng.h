
#pragma once
#include "EthernetGlobals.h"
#include "Thrd.h"
#include <vector>

class ServerTCPMng : public Thrd
{            

public:
	ServerTCPMng(void);
	virtual ~ServerTCPMng(void);

	class CServerParam;

	BOOL Listen(CServerParam params);
	BOOL Disconnect();
	BOOL IsConnected();
	BOOL Send(unsigned char* pData, int size);
	

	class CServerParam
	{
	public:
		CServerParam()
		{
			m_nPort = 55555;
			bDisableNagle = TRUE;
			bSetWindow = FALSE;
			bNoBlock = FALSE;
			id = 0;
		}
		WORD m_nPort;
		BOOL bDisableNagle;
		BOOL bSetWindow;
		BOOL bNoBlock;
		int id;
	};

	int CIRCBUFF_GetBytesAvailForRead();
	void CIRCBUFF_GetData(std::vector<unsigned char>& v);

private:
	BOOL _Recv(unsigned char* pData, int& nSize, int nMaxAvlSize);
	CCriticalSection m_cs;
	BOOL m_bIsConnected;
	CServerParam m_ServerPar;
	SOCKET m_ConnectSocket;
	SOCKET m_ListenSocket;
	void _begin() override;
	void SetEvts(HANDLE newData);

#define TMP_RX_BUF_SIZ (1024)
	unsigned char m_rxTmpBuf[TMP_RX_BUF_SIZ];

#define RX_BUFFER_SIZ (1024*1024)
	std::vector<unsigned char> m_rxBuffer;

	//////////////////////////////////////////////////////////////////////////////////////////////

protected:
	void _loop() override;
	void _finished() override;
};

