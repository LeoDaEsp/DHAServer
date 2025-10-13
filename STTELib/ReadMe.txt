================================================================================
    LIBRERIA MFC: cenni preliminari sul progetto STTELib
================================================================================

La creazione guidata applicazione ha creato l'applicazione 
STTELib.  Tale applicazione illustra le nozioni fondamentali 
sull'utilizzo delle classi MFC (Microsoft Foundation Class) e costituisce un 
punto di partenza per la scrittura dell'applicazione.

Questo file contiene un riepilogo del contenuto di ciascun file che fa parte
dell'applicazione STTELib.

STTELib.vcxproj
    File di progetto principale per i progetti VC++ generati tramite una 
    creazione guidata applicazione. 
    Contiene informazioni sulla versione di Visual C++ che ha generato il file e 
    informazioni sulle piattaforme, le configurazioni e le caratteristiche del 
    progetto selezionate con la creazione guidata applicazione.

STTELib.vcxproj.filters
    File dei filtri per i progetti VC++ generati tramite una Creazione guidata 
    applicazione. 
    Contiene informazioni sull'associazione tra i file del progetto e i filtri. 
    Tale associazione viene utilizzata nell'IDE per la visualizzazione di
    raggruppamenti di file con estensioni simili in un nodo specifico, ad 
    esempio: i file con estensione cpp sono associati al filtro "File di 
    origine".

STTELib.h
    File di intestazione principale per l'applicazione.  Include altre
    intestazioni specifiche del progetto quale Resource.h e dichiara la
    classe di applicazione CSTTELibApp.

STTELib.cpp
    File di origine principale dell'applicazione contenente la classe di
    applicazione CSTTELibApp.

STTELib.rc
    Elenco di tutte le risorse Microsoft Windows utilizzate dal
    programma.  Include le icone, le bitmap e i cursori memorizzati
    nella sottodirectory RES.  Questo file può essere modificato direttamente
    in Microsoft Visual C++. Le risorse del progetto sono in 1040.

res\STTELib.ico
    File di icona utilizzato come icona dell'applicazione.  Tale
    icona è inclusa dal file di risorse principale STTELib.rc.

res\STTELib.rc2
    Questo file contiene le risorse non modificate da Microsoft
    Visual C++. Inserire in questo file tutte le risorse non modificabili
    dall'editor di risorse.


/////////////////////////////////////////////////////////////////////////////

La creazione guidata applicazione crea una classe di finestre di dialogo:

STTELibDlg.h, STTELibDlg.cpp, la finestra di dialogo
    Questi file contengono la classe CSTTELibDlg.  Tale classe 
    definisce il comportamento della finestra di dialogo principale 
    dell'applicazione. Il modello della finestra di dialogo si trova in 
    STTELib.rc e può essere modificato in Microsoft Visual C++.


/////////////////////////////////////////////////////////////////////////////

Altre funzionalità:

Controlli ActiveX
    L'applicazione include il supporto per utilizzare i controlli ActiveX.

/////////////////////////////////////////////////////////////////////////////

Altri file standard:

StdAfx.h, StdAfx.cpp
    Tali file vengono utilizzati per generare il file di intestazione
    precompilato STTELib.pch e il file dei tipi precompilato 
    StdAfx.obj.

Resource.h
    File di intestazione principale standard che definisce i nuovi ID 
    risorse.
    Tale file viene letto e aggiornato da Microsoft Visual C++.

STTELib.manifest
    I file manifesto delle applicazioni vengono utilizzati da Windows XP per 
    descrivere una dipendenza delle applicazioni per versioni specifiche di 
    assembly affiancati. Queste informazioni vengono utilizzate per il 
    caricamento dell'assembly appropriato dalla cache o privatamente 
    dall'applicazione. Il manifesto dell'applicazione potrebbe essere incluso 
    per la ridistribuzione come un file manifest esterno installato nella 
    stessa cartella dell'eseguibile 
dell'applicazione o potrebbe essere 
    compreso nell'eseguibile sotto forma di risorsa. 
/////////////////////////////////////////////////////////////////////////////

Altre note:

la creazione guidata applicazione utilizza il prefisso "TODO:" per indicare 
le parti del codice sorgente da aggiungere o personalizzare.

Se l’applicazione utilizza MFC in una DLL condivisa, sarà necessario 
ridistribuire le DLL MFC. Se l’applicazione è in una lingua diversa da quella 
del sistema operativo, sarà inoltre necessario ridistribuire il file 
MFC100XXX.DLL delle risorse corrispondenti localizzate. 
Per ulteriori informazioni su entrambi gli argomenti, vedere la sezione 
relativa alla ridistribuzione di applicazioni Visual C++ nella documentazione 
MSDN.

/////////////////////////////////////////////////////////////////////////////
