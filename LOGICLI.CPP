// Logicli.cpp : Defines the class behaviors for the application.
//
// Copyright (C) 1993-1994 George Mills and Softronics, Inc. Corporation
// All rights reserved.
//

#include "stdafx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLogiApp

BEGIN_MESSAGE_MAP(CLogiApp, CWinApp)
   ON_COMMAND(CG_IDS_TIPOFTHEDAY, ShowTipOfTheDay)
   //{{AFX_MSG_MAP(CLogiApp)
   ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
   ON_COMMAND(ID_HELP_ABOUTMS, OnHelpAboutms)
   //}}AFX_MSG_MAP
   // Standard file based document commands
   ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
   ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
   // Standard print setup command
   ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLogiApp construction

CLogiApp::CLogiApp()
{
   	EnableHtmlHelp();
   // TODO: add construction code here,
   // Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CLogiApp object

CLogiApp NEAR theApp;

/////////////////////////////////////////////////////////////////////////////
// CLogiApp initialization

BOOL CLogiApp::InitInstance()
{
   SetRegistryKey(_T("Softronics"));

   m_bReadOnly = FALSE;

   // Initialize OLE 2.0 libraries
   if (!AfxOleInit())
   {
      AfxMessageBox(IDP_OLE_INIT_FAILED);
      return FALSE;
   }

   // Standard initialization
   // If you are not using these features and wish to reduce the size
   //  of your final executable, you should remove from the following
   //  the specific initialization routines you do not need.

   //   SetDialogBkColor();        // set dialog background color to gray
   LoadStdProfileSettings();  // Load standard INI file options (including MRU)

   // Register the application's document templates.  Document templates
   //  serve as the connection between documents, frame windows and views.

   CMultiDocTemplate* pDocTemplate;
   pDocTemplate = new CMultiDocTemplate(
      IDR_LOGICLTYPE,
      RUNTIME_CLASS(CLogiDoc),
      RUNTIME_CLASS(CSplitFrame),
      //   RUNTIME_CLASS(CMDIChildWnd),
      RUNTIME_CLASS(CLogiView));
   pDocTemplate->SetContainerInfo(IDR_LOGICLTYPE_CNTR_IP);
   AddDocTemplate(pDocTemplate);

   // create main MDI Frame window
   CMainFrame* pMainFrame = new CMainFrame;
   if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
   {
      // frame window creation failed.
      return FALSE;
   }
   m_pMainWnd = pMainFrame;

   // enable file manager drag/drop and DDE Execute open
   m_pMainWnd->DragAcceptFiles();
   EnableShellOpen();
   RegisterShellFileTypes(TRUE);

   // simple command line parsing
   if (m_lpCmdLine[0] == '\0')
   {
      // create a new (empty) document
      OnFileNew();
   }
   else
   {
      // open an existing document
      OpenDocumentFile(m_lpCmdLine);
   }

   OnIdle(0);  // updates buttons before showing the window

   // the main window has been initialized, so show and update it.

   pMainFrame->ShowWindow(m_nCmdShow);
   pMainFrame->UpdateWindow();

   // CG: This line inserted by 'Tip of the Day' component.
   ShowTipAtStartup();

   // Change extension for help file
   CString strHelpFile = m_pszHelpFilePath;
   strHelpFile.Replace(".HLP", ".chm");
   free((void*)m_pszHelpFilePath);
   m_pszHelpFilePath = _tcsdup(strHelpFile);

   return TRUE;
}

/*
// In this override of OnIdle we are doing UI for our app.
// Since this needs to be as fast as possible to give the user
// the best result we do our updates first when lCount is zero
// then we call the library to do its work.
BOOL CLogiApp::OnIdle(LONG lCount)
{

if (lCount == 0)
{
//      if (m_pMainWnd != NULL)
{
ASSERT(m_pMainWnd != NULL);

// look for any top-level windows owned by us
// we use 'HWND's to avoid generation of too many temporary CWnds
for (HWND hWnd = ::GetWindow(m_pMainWnd->m_hWnd, GW_HWNDFIRST);
hWnd != NULL; hWnd = ::GetNextWindow(hWnd, GW_HWNDNEXT))
{
if (::GetParent(hWnd) == m_pMainWnd->m_hWnd)
{
// if owned window is active, move the activation to the
//   application window
if (GetActiveWindow() == hWnd && (::GetCapture() == NULL))
m_pMainWnd->SetActiveWindow();

// also update the buttons for the top-level window
SendMessage(hWnd, WM_IDLEUPDATECMDUI, (WPARAM)TRUE, 0L);
}
}
}
}

return CWinApp::OnIdle(lCount);
}
*/

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
   CAboutDlg();

   // Dialog Data
   //{{AFX_DATA(CAboutDlg)
   enum { IDD = IDD_ABOUTBOX }; //ignore//
   //}}AFX_DATA

   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(CAboutDlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

   // Implementation
protected:
   //{{AFX_MSG(CAboutDlg)
   // No message handlers
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
}
;

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
   //{{AFX_DATA_INIT(CAboutDlg)
   //}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(CAboutDlg)
   //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
   //{{AFX_MSG_MAP(CAboutDlg)
   // No message handlers
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CLogiApp::OnAppAbout()
{
   CAboutDlg aboutDlg;
   aboutDlg.DoModal();
}

void CLogiApp::OnHelpAboutms()
{
   CAboutMSDlg aboutMSDlg;
   aboutMSDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CLogiApp commands


void CLogiApp::ShowTipAtStartup(void)
{
   // CG: This function added by 'Tip of the Day' component.

   CCommandLineInfo cmdInfo;
   ParseCommandLine(cmdInfo);
   if (cmdInfo.m_bShowSplash)
   {
      CTipDlg dlg;
      if (dlg.m_bStartup)
         dlg.DoModal();
   }

}

void CLogiApp::ShowTipOfTheDay(void)
{
   // CG: This function added by 'Tip of the Day' component.

   CTipDlg dlg;
   dlg.DoModal();

}
