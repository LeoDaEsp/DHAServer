
#include "..\stdafx.h"
#include "stdafx.h"
#include "CLibClass.h"


#undef DEBUG_REMOTE_PROCESS

CLibClass::CLibClass(void)
{
	m_pIntVars = NULL;
	m_exePath = _T("");
	m_buf.reserve(RX_BUFFER_SIZ*2);
}

CLibClass::~CLibClass(void)
{
}

bool CLibClass::Start(char* pExePath,bool& bErrorOccurred, long& lErrorCode, char* pchErrorMsg)
{
	if(m_pIntVars)
		return false;

	m_pIntVars = new CInternalVars();


	bErrorOccurred = true;
	lErrorCode = -1;
	if (m_pIntVars->m_bInit)
	{
		delete m_pIntVars;
		m_pIntVars = NULL;
		return false;
	}
	m_pIntVars->m_bInit = TRUE;

	//Avvio il Server
	ServerTCPMng::CServerParam servPar;
	servPar.m_nPort = TCP_PORT;
	servPar.bDisableNagle = TRUE;
	servPar.bSetWindow = FALSE;
	servPar.bNoBlock = FALSE;
	servPar.id = 0;

	m_pIntVars->m_TCPServer.Listen(servPar);

	//Creo il Processo satellite	
	m_pIntVars->m_InitError = CreateEvent(NULL, TRUE, FALSE, NULL);
	//char path[2048] = { 0 };
	//char* out = GetThisPath(path, 4096);
	//if (!out)
	//{
	//	//Non deve mai fallire???!!!
	//	m_pIntVars->m_TCPServer.Disconnect();
	//	delete m_pIntVars;
	//	m_pIntVars = NULL;
	//	lErrorCode = -2;
	//	return false;
	//}
	//CString szMyPath(path);
	//CString szSlaveSWPath = szMyPath + _T("\\SmcMaintTestBench.exe");

	 
	CString szSlaveSWPath(pExePath);
	 m_exePath = szSlaveSWPath;
	m_pIntVars->m_bSlvProcessActive = FALSE;

#ifndef DEBUG_REMOTE_PROCESS
	int retry = 0;
	for (;;)
	{
		ResetEvent(m_pIntVars->m_InitError);
		//Avvia il processo figlio
		CString szCmdLine;
		szCmdLine.Format(_T("%s"), szSlaveSWPath);

		ZeroMemory(&(m_pIntVars->m_si), sizeof(m_pIntVars->m_si));
		m_pIntVars->m_si.cb = sizeof(m_pIntVars->m_si);
		ZeroMemory(&(m_pIntVars->m_pi), sizeof(m_pIntVars->m_pi));

		// Start the child process. 
		if (!CreateProcess(NULL,			// No module name (use command line)
			szCmdLine.GetBuffer(),			// Command line
			NULL,							// Process handle not inheritable
			NULL,							// Thread handle not inheritable
			FALSE,							// Set handle inheritance to FALSE
			0,								// No creation flags
			NULL,							// Use parent's environment block
			NULL,							// Use parent's starting directory 
			&(m_pIntVars->m_si),							// Pointer to STARTUPINFO structure
			&(m_pIntVars->m_pi))							// Pointer to PROCESS_INFORMATION structure
			)
		{
			szCmdLine.ReleaseBuffer();
			m_pIntVars->m_TCPServer.Disconnect();
			delete m_pIntVars;
			m_pIntVars = NULL;

			TRACE("CreateProcess failed (%d).\n", GetLastError());
			lErrorCode = -3;
			return false;
		}

		szCmdLine.ReleaseBuffer();
		m_pIntVars->m_bSlvProcessActive = TRUE;
		DWORD initErr = WaitForSingleObject(m_pIntVars->m_InitError, 10000);
		if (initErr != WAIT_TIMEOUT)
		{
			ResetEvent(m_pIntVars->m_InitError);
			if (TerminateProcess(m_pIntVars->m_pi.hProcess, -1) == 0)
			{
				CloseHandle(m_pIntVars->m_pi.hProcess);
				CloseHandle(m_pIntVars->m_pi.hThread);
				lErrorCode = -4;
				delete m_pIntVars;
				m_pIntVars = NULL;
				return false;
			}
			CloseHandle(m_pIntVars->m_pi.hProcess);
			CloseHandle(m_pIntVars->m_pi.hThread);

			Sleep(3000);
			retry++;
			if (retry > 6)
			{
				lErrorCode = -5;
				m_pIntVars->m_TCPServer.Disconnect();
				delete m_pIntVars;
				m_pIntVars = NULL;
				return false;
			}
		}
		else
		{
			break;
		}
	}
#else
	while(!m_pIntVars->m_TCPServer.IsConnected());
#endif

	if (m_pIntVars->m_TCPServer.IsConnected() == FALSE)
	{
		lErrorCode = -5;
		m_pIntVars->m_TCPServer.Disconnect();
		delete m_pIntVars;
		m_pIntVars = NULL;
		return false;
	}

	bErrorOccurred = false;
	lErrorCode = 0;
	return true;
}


bool CLibClass::Finish(bool& bErrorOccurred, long& lErrorCode, char* pchErrorMsg)
{
	if (!m_pIntVars->m_bInit)
		return true;

	//In teoria il processo qua dovrebbe essere già terminato..

	DWORD res = WaitForSingleObject(m_pIntVars->m_pi.hProcess, 2000);
	if (res == WAIT_TIMEOUT)
	{
		TRACE(_T("ERROR: Slave process failed to exit\n"));

		// lo killo a mano..
		char path[2048] = { 0 };
		char* out = GetThisPath(path, 4096);
		if (!out)
		{
			lErrorCode = -2;
			return false;
		}
		CString szMyPath(path);
		CStringA szKill;
		//Se non lo è lo uccido io..
		szKill.Format("taskkill /F /IM SmcMaintTestBench.exe");
		system(szKill);
	}

#ifndef DEBUG_REMOTE_PROCESS
	CloseHandle(m_pIntVars->m_pi.hProcess);
	CloseHandle(m_pIntVars->m_pi.hThread);
#endif

	//if (m_pIntVars->m_TCPServer.IsConnected())
	//{
		m_pIntVars->m_TCPServer.Disconnect();
	//}
	
	m_pIntVars->m_bSlvProcessActive = FALSE;
	m_pIntVars->m_bInit = FALSE;

	//ripulisco tutto
	delete m_pIntVars;
	m_pIntVars = NULL;

	//Da qua sono pronto per ripartire pulito..

	return true;
}


int  CLibClass::_waitRemoteReply(int timeout_ms)
{
	//Blocco fin quando l'operazione non viene eseguita 
	int nSize = 0;
	std::clock_t startTime = std::clock();


	double x = ::GetTickCount64();

	std::vector<unsigned char> buf;
	std::vector<unsigned char> num = {0};
	float data;

	do
	{
		m_pIntVars->m_TCPServer.CIRCBUFF_GetData(m_buf);
		for(int i=0;i<m_buf.size();i++)
		{
			buf.push_back(m_buf[i]);
		}

		if (buf.size() > 2)
		{
			double elapsed = ((double)::GetTickCount64() - x);
			TRACE(_T("Reply in %u\n ms"), elapsed);
			if ((buf[0] == s_HeadId) && (buf[1] == '0') && (buf[2] == s_CompleteId))
			{
				return 0; // Reply FAIL
			}
			if ((buf[0] == s_HeadId) && (buf[1] == '1') && (buf[2] == s_CompleteId))
			{
				return 1; // Reply OK
			}
			if ((buf[0] == s_HeadId) && (buf[1] == '2') && (buf[2] == s_CompleteId))
			{
				return 2;
			}
			if ((buf[0] == s_HeadId) && (buf[1] == '3') && (buf[2] == s_CompleteId))
			{
				return 3;
			}
			if ((buf[0] == s_HeadId) && (buf[9] == s_CompleteId))
			{
				
				num[0] = { 0 };
				num[1] = buf[1];
				num[2] = buf[2];
				num[3] = buf[3];
				num[4] = buf[4];
				num[5] = buf[5];
				num[6] = buf[6];
				num[7] = buf[7];
				num[8] = buf[8];


				
				std::memcpy(&data, num.data(), sizeof(data));
				return data;
			}

		}
	
		
	} while (((double)::GetTickCount64() - x) < (timeout_ms));


	return 0;
}


bool CLibClass::_clearRxBuffer()
{
	int nSize = 0;
	if (m_pIntVars->m_TCPServer.IsConnected() == FALSE)
	{
		return false;
	}

	m_pIntVars->m_TCPServer.CIRCBUFF_GetData(m_buf);

	//Ripulisco la FIFO
	if (m_pIntVars->m_TCPServer.IsConnected() == FALSE)
	{
		return false;
	}

	return true;
}





BOOL CLibClass::Cmd(char* pCmd, char* pParams,int &addParams, bool& bErrorOccurred, long& lErrorCode, char* pchErrorMsg)
{

	lErrorCode = -1;
	bErrorOccurred = false;
	addParams = 0;


	if(CStringA(pCmd) == "DEBUG")
	{
		ASSERT(0);
		return TRUE;
	}

	if(CStringA(pCmd) == "DEBUG1")
	{
		return TRUE;
	}

	if (!_clearRxBuffer())
		return FALSE;

	//Costruisco il messaggio da inviare
	CStringA msg = "";
	msg += CStringA(s_HeadId);
	msg += CStringA(pCmd);
	msg += CStringA(s_SeparatorId);
	msg += CStringA(pParams);
	msg += CStringA(s_CompleteId);

	BYTE buf[MAX_BUF_SIZE];
	memset(buf, 0, MAX_BUF_SIZE);
	if (msg.GetLength() > (MAX_BUF_SIZE - 1))
	{
		return FALSE;
	}
	memcpy(buf, msg, msg.GetLength());
	m_pIntVars->m_TCPServer.Send(buf, MAX_BUF_SIZE);


	if (m_pIntVars->m_TCPServer.IsConnected() == FALSE)
	{
		return FALSE;
	}

	if(CStringA(pCmd) == "RESIZE_CURVE")
	{
		//ATTENZIONE: problemi nel passaggio dati DLL a TESTSTAND!!!!
		// da risolvere in futuro..
		// Per adesso in caso di errore nella procedura blocco tutto..

		int bOK = _waitRemoteReply(20000);
		return (bOK!=0);
	}
	else if(CStringA(pCmd) == "CMD__LDR_WRITE")
	{
		//Sleep(15000);
		int bOK = _waitRemoteReply(10000);
		Sleep(300); //Necessrio ad applicare il comando??!!
		if(bOK > 1)
			addParams = bOK;

		return (bOK!=0);
	}
	else if(CStringA(pCmd) == "CMD__LDR_READ")
	{
		int bOK = _waitRemoteReply(10000);
		Sleep(300); //Necessrio ad applicare il comando??!!
		if(bOK > 1)
			addParams = bOK;

		return (bOK!=0);
	}
	//Blocco fin quando l'operazione non viene eseguita //ex 10 sec
	else if(CStringA(pCmd) == "FREE_RSC")
	{
		int bOK = _waitRemoteReply(2000);
		if(bOK > 1)
			addParams = bOK;

		return TRUE;
	}
	else
	{
		int bOK = _waitRemoteReply(3000);

		addParams = bOK;
		lErrorCode = (int)bOK;
		return (bOK!=0);
	}
}

// float CLibClass::CmdMod(char* pCmd, char* pParams, float& addParams, bool& bErrorOccurred, long& lErrorCode, char* pchErrorMsg)
// {
// 
// 	lErrorCode = -1;
// 	bErrorOccurred = false;
// 	addParams = 0;
// 
// 
// 	if (CStringA(pCmd) == "DEBUG")
// 	{
// 		ASSERT(0);
// 		return TRUE;
// 	}
// 
// 	if (CStringA(pCmd) == "DEBUG1")
// 	{
// 		return TRUE;
// 	}
// 
// 	if (!_clearRxBuffer())
// 		return FALSE;
// 
// 	//Costruisco il messaggio da inviare
// 	CStringA msg = "";
// 	msg += CStringA(s_HeadId);
// 	msg += CStringA(pCmd);
// 	msg += CStringA(s_SeparatorId);
// 	msg += CStringA(pParams);
// 	msg += CStringA(s_CompleteId);
// 
// 	BYTE buf[MAX_BUF_SIZE];
// 	memset(buf, 0, MAX_BUF_SIZE);
// 	if (msg.GetLength() > (MAX_BUF_SIZE - 1))
// 	{
// 		return FALSE;
// 	}
// 	memcpy(buf, msg, msg.GetLength());
// 	m_pIntVars->m_TCPServer.Send(buf, MAX_BUF_SIZE);
// 
// 
// 	if (m_pIntVars->m_TCPServer.IsConnected() == FALSE)
// 	{
// 		return FALSE;
// 	}
// 
// 	float bOK = _waitRemoteReply(20000);
// 
// 	addParams = bOK;
// 	lErrorCode = (int)bOK;
// 	// return (bOK != 0);
// 	return bOK;
// 
// 	
// }




static CLibClass g_LIB_Class;
BOOL CLibFunc::Start(const char* pExePath,bool& bErrorOccurred, long& lErrorCode, char* pchErrorMsg) 
{
	return g_LIB_Class.Start((char*)pExePath,bErrorOccurred, lErrorCode, pchErrorMsg);
}

BOOL CLibFunc::Cmd(const char* pCmd, const char* pParams,int &addParams, bool& bErrorOccurred, long& lErrorCode, char* pchErrorMsg)
{
	return g_LIB_Class.Cmd((char*)pCmd,(char*)pParams,addParams,bErrorOccurred,lErrorCode,pchErrorMsg);
}


// float CLibFunc::CmdMod(const char* pCmd, const char* pParams, float& addParams, bool& bErrorOccurred, long& lErrorCode, char* pchErrorMsg)
// {
// 	return g_LIB_Class.CmdMod((char*)pCmd, (char*)pParams, addParams, bErrorOccurred, lErrorCode, pchErrorMsg);
// }

BOOL CLibFunc::Finish(bool& bErrorOccurred, long& lErrorCode, char* pchErrorMsg)
{
	return g_LIB_Class.Finish(bErrorOccurred, lErrorCode, pchErrorMsg);
}

