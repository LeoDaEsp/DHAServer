#pragma once


 





class __declspec(dllexport) CLibFunc
{
public:
	static BOOL Start(const char* pExePath,bool& bErrorOccurred, long& lErrorCode, char* pchErrorMsg);
	static BOOL Cmd(const char* pCmd,const char* pParams,int &addParams, bool& bErrorOccurred, long& lErrorCode, char* pchErrorMsg);
	// static float CmdMod(const char* pCmd, const char* pParams, float& addParams, bool& bErrorOccurred, long& lErrorCode, char* pchErrorMsg);
	static BOOL Finish(bool& bErrorOccurred, long& lErrorCode, char* pchErrorMsg);
};




/**

//ATTENZIONE:
Nella directory della libreria devono essere presenti i file:
LFMT_Data.dll
LFMT_Hdw.dll
Config.ini
SmcMaintTestBench.exe
ed il file:
SMC_LUTxxx.bin con le calibrazioni iniziali

Di seguito riportato un esempio di utilizzo delle chiamate esportate in questa libreria:

------------------------------------------------------------------------------------------------
bool bErrorOccurred = false;
long lErrorCode = 0;
int addParams = 0;
bool res = false; 		

for(int u=0;u<10;u++)
{
	res	= CLibFunc::Start("C:\Users\saitec\Desktop\TSD_PROJECT\CPP\STTELib\x64\Debug\SmcMaintTestBench.exe",bErrorOccurred,lErrorCode,0);

	res = CLibFunc::Cmd("CFG_ERASE_MEM"			,""									,addParams,bErrorOccurred,lErrorCode,NULL);
	res = CLibFunc::Cmd("CFG_WRITE_CALIB"			,"Default"							,addParams,bErrorOccurred,lErrorCode,NULL);	
	res = CLibFunc::Cmd("CFG_VERIFY_MEM"			,"Default"							,addParams,bErrorOccurred,lErrorCode,NULL);	

	res = CLibFunc::Cmd("CFG_EXTRACT_DEF_POINTS"	,""									,addParams,bErrorOccurred,lErrorCode,NULL);	

	res = CLibFunc::Cmd("SETUP_LINK"				,"On"								,addParams,bErrorOccurred,lErrorCode,NULL);	
	res = CLibFunc::Cmd("SETUP_LINK"				,"Off"								,addParams,bErrorOccurred,lErrorCode,NULL);	

	res = CLibFunc::Cmd("MASTER_MODE"				,"On"								,addParams,bErrorOccurred,lErrorCode,NULL);	
	res = CLibFunc::Cmd("MASTER_MODE"				,"Off"								,addParams,bErrorOccurred,lErrorCode,NULL);	

	res = CLibFunc::Cmd("BACKLIGHT"				,"On"								,addParams,bErrorOccurred,lErrorCode,NULL);	
	res = CLibFunc::Cmd("BACKLIGHT"				,"Off"								,addParams,bErrorOccurred,lErrorCode,NULL);	

	res = CLibFunc::Cmd("SET_PATTERN"				,""									,addParams,bErrorOccurred,lErrorCode,NULL);	

	res = CLibFunc::Cmd("SET_PATTERN"				,"Red",								addParams,bErrorOccurred,lErrorCode,NULL);	
	res = CLibFunc::Cmd("SET_PATTERN"				,"Green",							addParams,bErrorOccurred,lErrorCode,NULL);	
	res = CLibFunc::Cmd("SET_PATTERN"				,"Blue",							addParams,bErrorOccurred,lErrorCode,NULL);	
	res = CLibFunc::Cmd("SET_PATTERN"				,"White",							addParams,bErrorOccurred,lErrorCode,NULL);	
	res = CLibFunc::Cmd("SET_PATTERN"				,"Black",							addParams,bErrorOccurred,lErrorCode,NULL);	
	res = CLibFunc::Cmd("SET_PATTERN"				,"Amber",							addParams,bErrorOccurred,lErrorCode,NULL);	
	res = CLibFunc::Cmd("SET_PATTERN"				,"Cyan",							addParams,bErrorOccurred,lErrorCode,NULL);	
	res = CLibFunc::Cmd("SET_PATTERN"				,"Magenta",							addParams,bErrorOccurred,lErrorCode,NULL);	
	res = CLibFunc::Cmd("SET_PATTERN"				,"ATP Grid",						addParams,bErrorOccurred,lErrorCode,NULL);	
	res = CLibFunc::Cmd("SET_PATTERN"				,"Palette",							addParams,bErrorOccurred,lErrorCode,NULL);	
	res = CLibFunc::Cmd("SET_PATTERN"				,"Image Retention",					addParams,bErrorOccurred,lErrorCode,NULL);	
	res = CLibFunc::Cmd("SET_PATTERN"				,"Cross Talk",						addParams,bErrorOccurred,lErrorCode,NULL);	
	res = CLibFunc::Cmd("SET_PATTERN"				,"Vertical Color Bars",				addParams,bErrorOccurred,lErrorCode,NULL);	
	res = CLibFunc::Cmd("SET_PATTERN"				,"Horizontal Color Bars",			addParams,bErrorOccurred,lErrorCode,NULL);	
	res = CLibFunc::Cmd("SET_PATTERN"				,"Horizontal Stripes",				addParams,bErrorOccurred,lErrorCode,NULL);	
	res = CLibFunc::Cmd("SET_PATTERN"				,"Keys Aligment",					addParams,bErrorOccurred,lErrorCode,NULL);	
	res = CLibFunc::Cmd("SET_PATTERN"				,"OVTP Grid",						addParams,bErrorOccurred,lErrorCode,NULL);	
	res = CLibFunc::Cmd("SET_PATTERN"				,"Border",							addParams,bErrorOccurred,lErrorCode,NULL);	
	res = CLibFunc::Cmd("SET_PATTERN"				,"LCD ON",							addParams,bErrorOccurred,lErrorCode,NULL);	
	res = CLibFunc::Cmd("SET_PATTERN"				,"LCD OFF",							addParams,bErrorOccurred,lErrorCode,NULL);

	res = CLibFunc::Cmd("RESIZE_CURVE"			,"Init" 	                        ,addParams,bErrorOccurred,lErrorCode,NULL);

	double extimated_lum = 0.0f;
	CStringA szLum;
	while(1)
	{
		if(!CLibFunc::Cmd("RESIZE_CURVE"			,"50.501"	                        ,addParams,bErrorOccurred,lErrorCode,NULL))
			break;

		if(addParams == 2)
			break;
	}

	res = CLibFunc::Cmd("SET_LUM_FROM_INDEX"		,"0"								,addParams,bErrorOccurred,lErrorCode,NULL);
	res = CLibFunc::Cmd("SET_LUM_FROM_INDEX"		,"1"							    ,addParams,bErrorOccurred,lErrorCode,NULL);
	res = CLibFunc::Cmd("SET_LUM_FROM_INDEX"		,"2"							    ,addParams,bErrorOccurred,lErrorCode,NULL);
	res = CLibFunc::Cmd("SET_LUM_FROM_INDEX"		,"3"							    ,addParams,bErrorOccurred,lErrorCode,NULL);
	res = CLibFunc::Cmd("SET_LUM_FROM_INDEX"		,"4"							    ,addParams,bErrorOccurred,lErrorCode,NULL);
	res = CLibFunc::Cmd("SET_LUM_FROM_INDEX"		,"5"							    ,addParams,bErrorOccurred,lErrorCode,NULL);
	res = CLibFunc::Cmd("SET_LUM_FROM_INDEX"		,"6"							    ,addParams,bErrorOccurred,lErrorCode,NULL);
	res = CLibFunc::Cmd("SET_LUM_FROM_INDEX"		,"7"							    ,addParams,bErrorOccurred,lErrorCode,NULL);
	res = CLibFunc::Cmd("SET_LUM_FROM_INDEX"		,"8"							    ,addParams,bErrorOccurred,lErrorCode,NULL);
	res = CLibFunc::Cmd("SET_LUM_FROM_INDEX"		,"9"							    ,addParams,bErrorOccurred,lErrorCode,NULL);
	res = CLibFunc::Cmd("SET_LUM_FROM_INDEX"		,"29"							    ,addParams,bErrorOccurred,lErrorCode,NULL);
	res = CLibFunc::Cmd("SET_LUM_FROM_INDEX"		,"30"							    ,addParams,bErrorOccurred,lErrorCode,NULL);
	res = CLibFunc::Cmd("SET_LUM_FROM_INDEX"		,"31"							    ,addParams,bErrorOccurred,lErrorCode,NULL);

	res = CLibFunc::Cmd("CREATE_FILE_CALIB"		,""			                        ,addParams,bErrorOccurred,lErrorCode,NULL);
	res = CLibFunc::Cmd("CFG_ERASE_MEM"			,""									,addParams,bErrorOccurred,lErrorCode,NULL);
	res = CLibFunc::Cmd("CFG_WRITE_CALIB"			,"Calib"							,addParams,bErrorOccurred,lErrorCode,NULL);	
	res = CLibFunc::Cmd("CFG_VERIFY_MEM"			,"Calib"							,addParams,bErrorOccurred,lErrorCode,NULL);
	res = CLibFunc::Cmd("FREE_RESOURCES"			,""			                        ,addParams,bErrorOccurred,lErrorCode,NULL);
		
	res = CLibFunc::Finish(bErrorOccurred,lErrorCode,0);
}

------------------------------------------------------------------------------------------------
*/