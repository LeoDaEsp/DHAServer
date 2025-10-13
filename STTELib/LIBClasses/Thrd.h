#pragma once
#include <afxmt.h>


class Thrd
{
public:
	Thrd(void);
	virtual ~Thrd(void);

	


protected:
	void _startThread(CString szID = _T("NO_ID"));
	void _stopThread();
	virtual void _begin() = 0;
	virtual void _loop() = 0;
	virtual void _finished() = 0;
	int m_IdleTime;

	typedef enum enmThrdEvt
	{
		THRD_EVT_TERMINATE =0,
		//...
		TRD_NUM_OF_EVT
	} enmThrdEvt_t;

	HANDLE m_arrThrEvt[TRD_NUM_OF_EVT];

private:


	
	CWinThread *m_pThread;
	static UINT ThreadFunc(LPVOID pParam);
	

	typedef enum
	{
		THRD_DEAFULT_IDLE_TIME			=10,//ms  
		THRD_WAIT_FOR_FINISH_TIME		=5000 //ms
	} enmThrdPar;

	CString m_szID;

};
