#include "StdAfx.h"
#include "Thrd.h"


Thrd::Thrd(void)
{
	m_szID = _T("NO_ID");
	m_pThread = NULL;
	for(int i=0;i<TRD_NUM_OF_EVT;i++)
	{
		m_arrThrEvt[i] = NULL;
		m_arrThrEvt[i] = CreateEvent(NULL, FALSE, FALSE, NULL); //No manual reset
	}
	m_IdleTime = THRD_DEAFULT_IDLE_TIME;
}

Thrd::~Thrd(void)
{
}



void Thrd::_stopThread()
{
	if(m_pThread)
	{
		TRACE(_T("Thrd %s -> Closing\n"), m_szID);
		HANDLE hThread = m_pThread->m_hThread;
		SetEvent(m_arrThrEvt[THRD_EVT_TERMINATE]);
		DWORD RetVal = ::WaitForSingleObject(hThread, THRD_WAIT_FOR_FINISH_TIME);

		TRACE(_T("Thrd %s -> Closed\n"), m_szID);
		//delete m_pThread;
		//m_pThread = NULL;
	}
}

void Thrd::_startThread(CString szId)
{
	if (m_pThread)
		return;
	m_szID = szId;
	m_pThread = AfxBeginThread(ThreadFunc, this, THREAD_PRIORITY_ABOVE_NORMAL);
}

UINT Thrd::ThreadFunc(LPVOID pParam)
{
	Thrd *pSelf;
	pSelf = (Thrd *)pParam;
	DWORD Wait = 0;
	TRACE(_T("Thrd %s -> Started\n"), pSelf->m_szID);
	pSelf->_begin();
	while (1)
    {
		Wait = WaitForMultipleObjects(TRD_NUM_OF_EVT,pSelf->m_arrThrEvt,FALSE, THRD_DEAFULT_IDLE_TIME);
		Wait = Wait - WAIT_OBJECT_0;
		switch(Wait)
		{
		case THRD_EVT_TERMINATE:
			pSelf->_finished();
			return 0;

		default:
			pSelf->_loop();
			break;
		}
	}
	
	
    return 0;
}


