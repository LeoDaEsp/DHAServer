
// STTELib.h : file di intestazione principale per l'applicazione PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "includere 'stdafx.h' prima di includere questo file per PCH"
#endif

#include "resource.h"		// simboli principali


// CSTTELibApp:
// Vedere STTELib.cpp per l'implementazione di questa classe
//

class CSTTELibApp : public CWinApp
{
public:
	CSTTELibApp();

// Override
public:
	virtual BOOL InitInstance();

// Implementazione

	DECLARE_MESSAGE_MAP()
};

extern CSTTELibApp theApp;