#pragma once
#include "ServerTCPMng.h"
#include "Thrd.h"
#include "LibGlobals.h"
#include "CLibClassIF.h"

class CLibClass
{
public:
	CLibClass(void);
	virtual ~CLibClass(void);

	bool Start(char* pExePath,bool& bErrorOccurred, long& lErrorCode, char* pchErrorMsg) ;
	bool Finish(bool& bErrorOccurred, long& lErrorCode, char* pchErrorMsg) ;
	BOOL Cmd(char* pCmd, char* pParams,int &addParams, bool& bErrorOccurred, long& lErrorCode, char* pchErrorMsg) ;
	// float CmdMod(char* pCmd, char* pParams, float& addParams, bool& bErrorOccurred, long& lErrorCode, char* pchErrorMsg);



private:
	int _waitRemoteReply(unsigned long long  timeout_ms);
	bool _clearRxBuffer();

	class CInternalVars
	{
	public:
		CInternalVars()
		{
			m_bInit = FALSE;
			m_InitError = NULL;
			m_bSlvProcessActive = FALSE;
		}
		BOOL m_bInit;
		HANDLE m_InitError;
		BOOL m_bSlvProcessActive;

		//Attributi del processo satellite
		STARTUPINFO m_si;
		PROCESS_INFORMATION m_pi;
		
		//Server pilota
		ServerTCPMng m_TCPServer;
	};
	CString m_exePath;
	CInternalVars *m_pIntVars;

	std::vector<unsigned char> m_buf; 

};
	


