

// STTELibDlg.cpp : file di implementazione
//

#include "stdafx.h"
#include "STTELib.h"
#include "STTELibDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// finestra di dialogo CAboutDlg utilizzata per visualizzare le informazioni sull'applicazione.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dati della finestra di dialogo
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // supporto DDX/DDV

// Implementazione
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// finestra di dialogo CSTTELibDlg




CSTTELibDlg::CSTTELibDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSTTELibDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSTTELibDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSTTELibDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// gestori di messaggi di CSTTELibDlg

BOOL CSTTELibDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Aggiungere la voce di menu "Informazioni su..." al menu di sistema.

	// IDM_ABOUTBOX deve trovarsi tra i comandi di sistema.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Impostare l'icona per questa finestra di dialogo. Il framework non esegue questa operazione automaticamente
	//  se la finestra principale dell'applicazione non è una finestra di dialogo.
	SetIcon(m_hIcon, TRUE);			// Impostare icona grande.
	SetIcon(m_hIcon, FALSE);		// Impostare icona piccola.

	// TODO: aggiungere qui inizializzazione aggiuntiva.
	bool bErrorOccurred = false;
	long lErrorCode = 0;
	int addParams = 0;
	bool res = false; 
	
#if 0
	res	= CLibFunc::Start("C:\\Users\\saitec\\Desktop\\COMMIT_FERIE\\SMC OPCAL\\Tecnica\\SW\\Working\\1590SWP020 - RemoteProcessSW\\xSaitec SMC 03-09-2019\\xSaitec SMC 03-09-2019\\SmcMaintTestBench_SWCD_0018_2019_01_01\\Debug\\SmcMaintTestBench.exe",bErrorOccurred,lErrorCode,0);
	for(int i=0;i<3;i++){
		res = CLibFunc::Cmd("SETUP_LINK"				,"On"								,addParams,bErrorOccurred,lErrorCode,NULL);	
		if(res == true)
			break;
	}
	if(res == false)
	{
		AfxMessageBox(_T("ERRORE GRAVE"));
	}
	res = CLibFunc::Cmd("BACKLIGHT"					,"On"								    ,addParams,bErrorOccurred,lErrorCode,NULL);	
	res = CLibFunc::Cmd("SET_PATTERN"				,"LCD ON",							addParams,bErrorOccurred,lErrorCode,NULL);
	res = CLibFunc::Cmd("SET_PATTERN"				,"Green",								addParams,bErrorOccurred,lErrorCode,NULL);	
	res = CLibFunc::Cmd("MASTER_MODE"				,"On"								,addParams,bErrorOccurred,lErrorCode,NULL);	
	res = CLibFunc::Cmd("CFG_EXTRACT_DEF_POINTS"	,""									,addParams,bErrorOccurred,lErrorCode,NULL);	
	if(res == false)
	{
		AfxMessageBox(_T("ERRORE GRAVE"));
	}
	return TRUE;
#endif








// DARIO
//#if 0
	// res	= CLibFunc::Start("C:\\Users\\ING_TEST\\Desktop\\BancoOtticoWestar - APP\\1590SWP120 - RemoteProcessSW Banco 2\\REMProcess\\Debug\\SmcMaintTestBench.exe",bErrorOccurred,lErrorCode,0);

	// res = CLibFunc::Start("C:\\Users\\ING_TEST\\Desktop\\DHA5x5\\DHA_16_05_25\\Dha5x5_STTE_r777\\Dha5x5_STTE_Srcs_r777\\Release\\dha5x5_STTE.exe", bErrorOccurred, lErrorCode, 0);
	res = CLibFunc::Start("C:\\Users\\ING_TEST\\Desktop\\Dha5x5_STTE_r856_mod\\Dha5x5_STTE_Srcs_r856\\Debug\\dha5x5_STTE.exe", bErrorOccurred, lErrorCode, 0);



	res = CLibFunc::Cmd("SYS_CONNECT" , "On" , addParams, bErrorOccurred, lErrorCode,NULL);

	res = CLibFunc::Cmd("CONNECT_COM", "On", addParams, bErrorOccurred, lErrorCode, NULL);

	res = CLibFunc::Cmd("CONNECT_COM", "Off", addParams, bErrorOccurred, lErrorCode, NULL);

	res = CLibFunc::Cmd("CMD__REBOOT", "", addParams, bErrorOccurred, lErrorCode, NULL);

	res = CLibFunc::Cmd("CONNECT_COM", "On", addParams, bErrorOccurred, lErrorCode, NULL);

	res = CLibFunc::Cmd("CONNECT_COM", "Off", addParams, bErrorOccurred, lErrorCode, NULL);

	// res = CLibFunc::Cmd("OPR_CRV_BRIGHTNESS_SET", "254", addParams, bErrorOccurred, lErrorCode, NULL);
	// 
	// res = CLibFunc::Cmd("IDC_OPER_BRT_MODE", "On", addParams, bErrorOccurred, lErrorCode, NULL);
	// 
	// 
	// res = CLibFunc::Cmd("BRIG_DUTY", "50000", addParams, bErrorOccurred, lErrorCode, NULL);
	// 
	// res = CLibFunc::Cmd("BRIG_CURRENT", "100", addParams, bErrorOccurred, lErrorCode, NULL);
	// 
	// res = CLibFunc::Cmd("BRIG_POTENTIOMETER", "1", addParams, bErrorOccurred, lErrorCode, NULL);
	// 
	// res = CLibFunc::Cmd("BRIG_DAY", "On", addParams, bErrorOccurred, lErrorCode, NULL);
	// 
	// res = CLibFunc::Cmd("LCD_PATTERN", "Crosshair", addParams, bErrorOccurred, lErrorCode, NULL);
	// 
	// res = CLibFunc::Cmd("LCD_PATTERN_COLOR_1", "W", addParams, bErrorOccurred, lErrorCode, NULL);
	// 
	// res = CLibFunc::Cmd("LCD_PATTERN_COLOR_2", "B", addParams, bErrorOccurred, lErrorCode, NULL);

	res = CLibFunc::Cmd("LDR_READ", "123\\123", addParams, bErrorOccurred, lErrorCode, NULL);


	res = CLibFunc::Cmd("BUILDER_OPEN", "123\\123", addParams, bErrorOccurred, lErrorCode, NULL);

	/////////////////////////////////////////////////////////
	// res = CLibFunc::Cmd("BUILDER_SET_MIN_DUTY_NVG", "0", addParams, bErrorOccurred, lErrorCode, NULL);

	// res = CLibFunc::Cmd("BUILDER_GET_MIN_DUTY_NVG", "", addParams, bErrorOccurred, lErrorCode, NULL);

	// res = CLibFunc::Cmd("BUILDER_SET_MAX_DUTY_NVG", "100", addParams, bErrorOccurred, lErrorCode, NULL);

	// res = CLibFunc::Cmd("BUILDER_GET_MAX_DUTY_NVG", "", addParams, bErrorOccurred, lErrorCode, NULL);
	
	

	//////////////////////////////////////////////////////

	// res = CLibFunc::Cmd("BUILDER_SET_MIN_DUTY_DAY", "1", addParams, bErrorOccurred, lErrorCode, NULL);
	// 
	// res = CLibFunc::Cmd("BUILDER_GET_MIN_DUTY_DAY", "", addParams, bErrorOccurred, lErrorCode, NULL);
	// 
	// res = CLibFunc::Cmd("BUILDER_SET_MAX_DUTY_DAY", "69", addParams, bErrorOccurred, lErrorCode, NULL);
	// 
	// res = CLibFunc::Cmd("BUILDER_GET_MAX_DUTY_DAY", "", addParams, bErrorOccurred, lErrorCode, NULL);
	
	

	//////////////////////////////////////////////////////

	res = CLibFunc::Cmd("BUILDER_INFO_DATE", "04-09-2025", addParams, bErrorOccurred, lErrorCode, NULL);

	res = CLibFunc::Cmd("BUILDER_INFO_CODE", "1234567890", addParams, bErrorOccurred, lErrorCode, NULL);

	res = CLibFunc::Cmd("BUILDER_SAVE", "new\\1234567890", addParams, bErrorOccurred, lErrorCode, NULL);


	res = CLibFunc::Cmd("FREE_RSC", "", addParams, bErrorOccurred, lErrorCode, NULL);
	
	return TRUE;
//#endif













#if 0
	res	= CLibFunc::Start("C:\\Users\\ING_TEST\\Desktop\\BancoOtticoWestar - DLL\\1590SWP120 - RemoteProcessSW Banco 2\\REMProcess\\Debug\\SmcMaintTestBench.exe",bErrorOccurred,lErrorCode,0);
	res = CLibFunc::Cmd("SETUP_LINK"				,"On"								,addParams,bErrorOccurred,lErrorCode,NULL);	
	res = CLibFunc::Cmd("SETUP_LINK"				,"Off"								,addParams,bErrorOccurred,lErrorCode,NULL);
	
	res = CLibFunc::Cmd("CMD_CALIB_STATUS_OK",""								,addParams,bErrorOccurred,lErrorCode,NULL);
	
	res = CLibFunc::Cmd("FREE_RESOURCES"				,"On"								,addParams,bErrorOccurred,lErrorCode,NULL);	
	
	res = CLibFunc::Finish(bErrorOccurred,lErrorCode,NULL);	
	return TRUE;

	res &= CLibFunc::Cmd("CREATE_FILE_CALIB"				,"pippo#pluto"									,addParams,bErrorOccurred,lErrorCode,NULL);

	for(int i=0;i<1;i++)
	{
		res &= CLibFunc::Cmd("CFG_ERASE_MEM"				,""									,addParams,bErrorOccurred,lErrorCode,NULL);
		res &= CLibFunc::Cmd("CFG_WRITE_CALIB"			,"Default"							,addParams,bErrorOccurred,lErrorCode,NULL);	
		res &= CLibFunc::Cmd("CFG_VERIFY_MEM"			,"Default"							,addParams,bErrorOccurred,lErrorCode,NULL);	

		if(res == 0)
		{
			int xxx=0;
			xxx=0;
		}

		res &= CLibFunc::Cmd("CFG_ERASE_MEM"				,""									,addParams,bErrorOccurred,lErrorCode,NULL);
		res &= CLibFunc::Cmd("CFG_WRITE_CALIB"			,"NoDefault"						,addParams,bErrorOccurred,lErrorCode,NULL);	
		res &= CLibFunc::Cmd("CFG_VERIFY_MEM"			,"NoDefault"						,addParams,bErrorOccurred,lErrorCode,NULL);	
	
		if(res == 0)
		{
			int xxx=0;
			xxx=0;
		}
	}

	res &= CLibFunc::Cmd("FREE_RESOURCES","",addParams,bErrorOccurred,lErrorCode,NULL);
	
	return TRUE;
#endif

	for(int u=0;u<10;u++)
	{
		
		res	= CLibFunc::Start("C:\\Users\\saitec\\Desktop\\COMMIT_FERIE\\SMC OPCAL\\Tecnica\\SW\\Working\\1590SWP020 - RemoteProcessSW\\xSaitec SMC 03-09-2019\\xSaitec SMC 03-09-2019\\SmcMaintTestBench_SWCD_0018_2019_01_01\\Debug\\SmcMaintTestBench.exe",bErrorOccurred,lErrorCode,0);
		res = CLibFunc::Cmd("SETUP_LINK"				,"On"								,addParams,bErrorOccurred,lErrorCode,NULL);	
		res = CLibFunc::Cmd("BACKLIGHT"					,"On"								    ,addParams,bErrorOccurred,lErrorCode,NULL);	
		res = CLibFunc::Cmd("SET_PATTERN"				,"LCD ON",							addParams,bErrorOccurred,lErrorCode,NULL);
		Sleep(1000);
		

		
		res = CLibFunc::Cmd("SET_PATTERN"				,"Green",								addParams,bErrorOccurred,lErrorCode,NULL);	
		Sleep(1000);
		res = CLibFunc::Cmd("SET_PATTERN"				,"Red",							addParams,bErrorOccurred,lErrorCode,NULL);	
		Sleep(1000);
		res = CLibFunc::Cmd("SET_PATTERN"				,"Blue",							addParams,bErrorOccurred,lErrorCode,NULL);	
		Sleep(1000);
		res = CLibFunc::Cmd("SET_PATTERN"				,"White",							addParams,bErrorOccurred,lErrorCode,NULL);
		Sleep(1000);
		res = CLibFunc::Cmd("SET_PATTERN"				,"Black",							addParams,bErrorOccurred,lErrorCode,NULL);	
		Sleep(1000);
		res = CLibFunc::Cmd("SET_PATTERN"				,"Amber",							addParams,bErrorOccurred,lErrorCode,NULL);	
		Sleep(1000);
		res = CLibFunc::Cmd("SET_PATTERN"				,"Cyan",							addParams,bErrorOccurred,lErrorCode,NULL);	
		Sleep(1000);
		res = CLibFunc::Cmd("SET_PATTERN"				,"Magenta",							addParams,bErrorOccurred,lErrorCode,NULL);	
		Sleep(1000);
		res = CLibFunc::Cmd("SET_PATTERN"				,"ATP Grid",						addParams,bErrorOccurred,lErrorCode,NULL);	
		Sleep(1000);
		res = CLibFunc::Cmd("SET_PATTERN"				,"Palette",							addParams,bErrorOccurred,lErrorCode,NULL);
		Sleep(1000);
		res = CLibFunc::Cmd("SET_PATTERN"				,"Image Retention",					addParams,bErrorOccurred,lErrorCode,NULL);	
		Sleep(1000);
		res = CLibFunc::Cmd("SET_PATTERN"				,"Cross Talk",						addParams,bErrorOccurred,lErrorCode,NULL);	
		Sleep(1000);
		res = CLibFunc::Cmd("SET_PATTERN"				,"Vertical Color Bars",				addParams,bErrorOccurred,lErrorCode,NULL);	
		Sleep(1000);
		res = CLibFunc::Cmd("SET_PATTERN"				,"Horizontal Color Bars",			addParams,bErrorOccurred,lErrorCode,NULL);	
		Sleep(1000);
		res = CLibFunc::Cmd("SET_PATTERN"				,"Horizontal Stripes",				addParams,bErrorOccurred,lErrorCode,NULL);	
		Sleep(1000);
		res = CLibFunc::Cmd("SET_PATTERN"				,"Keys Aligment",					addParams,bErrorOccurred,lErrorCode,NULL);	
		Sleep(1000);
		res = CLibFunc::Cmd("SET_PATTERN"				,"OVTP Grid",						addParams,bErrorOccurred,lErrorCode,NULL);
		Sleep(1000);
		res = CLibFunc::Cmd("SET_PATTERN"				,"Border",							addParams,bErrorOccurred,lErrorCode,NULL);	
		Sleep(1000);
		res = CLibFunc::Cmd("SET_PATTERN"				,"LCD OFF",							addParams,bErrorOccurred,lErrorCode,NULL);
		Sleep(1000);
		res = CLibFunc::Cmd("BACKLIGHT"					,"Off"								    ,addParams,bErrorOccurred,lErrorCode,NULL);	
		res = CLibFunc::Cmd("SETUP_LINK"				,"Off"								,addParams,bErrorOccurred,lErrorCode,NULL);	
		Sleep(1000);
		res = CLibFunc::Cmd("SETUP_LINK"				,"On"								,addParams,bErrorOccurred,lErrorCode,NULL);	
		res = CLibFunc::Cmd("BACKLIGHT"					,"On"								    ,addParams,bErrorOccurred,lErrorCode,NULL);	
		res = CLibFunc::Cmd("SET_PATTERN"				,"LCD ON",							addParams,bErrorOccurred,lErrorCode,NULL);	
		res = CLibFunc::Cmd("SET_PATTERN"				,"ATP Grid",						addParams,bErrorOccurred,lErrorCode,NULL);	
		res = CLibFunc::Cmd("MASTER_MODE"				,"On"								,addParams,bErrorOccurred,lErrorCode,NULL);	
		res = CLibFunc::Cmd("CFG_EXTRACT_DEF_POINTS"	,""									,addParams,bErrorOccurred,lErrorCode,NULL);	
		res = CLibFunc::Cmd("SET_LUM_FROM_INDEX"		,"31"							    ,addParams,bErrorOccurred,lErrorCode,NULL);
		Sleep(200);
		res = CLibFunc::Cmd("SET_LUM_FROM_INDEX"		,"1"							    ,addParams,bErrorOccurred,lErrorCode,NULL);
		Sleep(200);
		res = CLibFunc::Cmd("SET_LUM_FROM_INDEX"		,"2"							    ,addParams,bErrorOccurred,lErrorCode,NULL);
		Sleep(1000);
		res = CLibFunc::Cmd("SET_LUM_FROM_INDEX"		,"3"							    ,addParams,bErrorOccurred,lErrorCode,NULL);
		Sleep(1000);
		res = CLibFunc::Cmd("SET_LUM_FROM_INDEX"		,"4"							    ,addParams,bErrorOccurred,lErrorCode,NULL);
		Sleep(1000);
		res = CLibFunc::Cmd("SET_LUM_FROM_INDEX"		,"5"							    ,addParams,bErrorOccurred,lErrorCode,NULL);
		Sleep(1000);
		res = CLibFunc::Cmd("SET_LUM_FROM_INDEX"		,"6"							    ,addParams,bErrorOccurred,lErrorCode,NULL);
		Sleep(1000);
		res = CLibFunc::Cmd("SET_LUM_FROM_INDEX"		,"7"							    ,addParams,bErrorOccurred,lErrorCode,NULL);
		Sleep(1000);
		res = CLibFunc::Cmd("SET_LUM_FROM_INDEX"		,"8"							    ,addParams,bErrorOccurred,lErrorCode,NULL);
		Sleep(1000);
		res = CLibFunc::Cmd("SET_LUM_FROM_INDEX"		,"9"							    ,addParams,bErrorOccurred,lErrorCode,NULL);
		Sleep(1000);
		res = CLibFunc::Cmd("SET_LUM_FROM_INDEX"		,"29"							    ,addParams,bErrorOccurred,lErrorCode,NULL);
		Sleep(1000);
		res = CLibFunc::Cmd("SET_LUM_FROM_INDEX"		,"30"							    ,addParams,bErrorOccurred,lErrorCode,NULL);
		Sleep(1000);
		res = CLibFunc::Cmd("SET_LUM_FROM_INDEX"		,"31"							    ,addParams,bErrorOccurred,lErrorCode,NULL);
		Sleep(1000);
		res = CLibFunc::Cmd("MASTER_MODE"				,"Off"								,addParams,bErrorOccurred,lErrorCode,NULL);	
		Sleep(1000);
		res = CLibFunc::Cmd("SET_PATTERN"				,"LCD OFF",							addParams,bErrorOccurred,lErrorCode,NULL);
		Sleep(1000);
		res = CLibFunc::Cmd("BACKLIGHT"					,"Off"								    ,addParams,bErrorOccurred,lErrorCode,NULL);	
		res = CLibFunc::Cmd("SETUP_LINK"				,"Off"								,addParams,bErrorOccurred,lErrorCode,NULL);	
			
	}


	return TRUE;  // restituisce TRUE a meno che non venga impostato lo stato attivo su un controllo.
}

void CSTTELibDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// Se si aggiunge alla finestra di dialogo un pulsante di riduzione a icona, per trascinare l'icona sarà necessario
//  il codice sottostante. Per le applicazioni MFC che utilizzano il modello documento/visualizzazione,
//  questa operazione viene eseguita automaticamente dal framework.

void CSTTELibDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // contesto di dispositivo per il disegno

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Centrare l'icona nel rettangolo client.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Disegnare l'icona
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Il sistema chiama questa funzione per ottenere la visualizzazione del cursore durante il trascinamento
//  della finestra ridotta a icona.
HCURSOR CSTTELibDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

