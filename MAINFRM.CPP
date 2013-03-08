// mainfrm.cpp : implementation of the CMainFrame class
//
// Copyright (C) 1993-1994 George Mills and Softronics, Inc. Corporation
// All rights reserved.
//

#include "stdafx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// extern "C" int foo();

/*
#ifdef	NDEBUG
extern "C" _CRTIMP unsigned long __cdecl _beginthreadex(void *, unsigned, unsigned (__stdcall *) (void *), void *, unsigned, unsigned *)
{
return 0;
}
extern "C" _CRTIMP void __cdecl _endthreadex(unsigned)
{
}
#endif
*/

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
   ON_WM_INITMENU()
   //{{AFX_MSG_MAP(CMainFrame)
   ON_WM_CREATE()
   ON_COMMAND(ID_HELP_TUTORIAL, OnHelpTutorial)
   ON_COMMAND(ID_HELP_EXAMPLES, OnHelpExamples)
   ON_COMMAND(ID_HELP_RELEASENOTES, OnHelpReleasenotes)
   //}}AFX_MSG_MAP
   // Global help commands
   ON_COMMAND(ID_HELP_INDEX, CMainFrame::OnHelpIndex)
   ON_COMMAND(ID_HELP, CMainFrame::OnHelp)
   ON_COMMAND(ID_CONTEXT_HELP, CMainFrame::OnContextHelp)
   ON_COMMAND(ID_DEFAULT_HELP, CMainFrame::OnHelpIndex)
   ON_COMMAND(ID_HELP_FINDER, CMainFrame::OnHelpFinder)

   ON_COMMAND(ON_SYSCOMMAND, OnSyscommand)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// arrays of IDs used to initialize control bars

// palette buttons - IDs are command buttons
static UINT BASED_CODE palette[] =
{
   // same order as in the bitmap 'palette.bmp'
   ID_DRAW_SELECTOR,
      ID_DRAW_WIRE,
      ID_DRAW_NULLGATE,
      ID_DRAW_ANDGATE,
      ID_DRAW_ORGATE,

      ID_DRAW_XORGATE,
      ID_DRAW_INVERTGATE,
      ID_DRAW_OSCILLATORGATE,
      ID_DRAW_LEDGATE,
      ID_DRAW_SWITCHGATE,

      ID_DRAW_BUZZERGATE,
      ID_DRAW_LED7GATE,
      ID_DRAW_ASCIIKEYBOARD,
      ID_DRAW_TEXT,
      ID_DRAW_FLIPFLOP,

      ID_DRAW_KEYPAD,
      ID_DRAW_ASCIIDISPLAY,
      ID_DRAW_SOUNDWAVE,
      ID_DRAW_SIGNALSENDER,
      ID_DRAW_SIGNALRECEIVER,

      ID_DRAW_GROUND,
      ID_DRAW_PLUS,
      ID_DRAW_BITMAP,
      ID_DRAW_WRITEFILE,
      ID_DRAW_READFILE,

      ID_DRAW_PORTOUT,
      ID_DRAW_PORTIN,
      ID_DRAW_COUNTER,
      ID_DRAW_BREAK,
      ID_DRAW_MUX,

      ID_DRAW_MEMORY,
      ID_DRAW_ALU,
      ID_DRAW_BITBUCKET,
      ID_DRAW_RANDOM,
      ID_DRAW_CLOCK,

      ID_DRAW_TIMER,
      ID_DRAW_ROBOT,
      ID_DRAW_NETWORK,
      ID_DRAW_SELECT,
      ID_DRAW_TRISTATE,

      ID_DRAW_BUS,
      ID_DRAW_ANALYZE,
      ID_DRAW_TAPEDRIVE,
      ID_DRAW_DUMMY1,
      ID_DRAW_DUMMY2
}
;



// toolbar buttons - IDs are command buttons
static UINT BASED_CODE buttons[] =
{
   // same order as in the bitmap 'toolbar.bmp'
   ID_FILE_NEW,
      ID_FILE_OPEN,
      ID_FILE_SAVE,
      ID_SEPARATOR,
      ID_EDIT_CUT,
      ID_EDIT_COPY,
      ID_EDIT_PASTE,
      ID_SEPARATOR,
      ID_SIMULATE_DRAW,
      ID_SIMULATE_PROBE,
      ID_SIMULATE_ANALYZE,
      ID_SEPARATOR,
      ID_SIMULATE_RUN,
      ID_SIMULATE_STOP,
      ID_SIMULATE_PAUSE,
      ID_SIMULATE_RESET,
      ID_SIMULATE_STEP,
      //   ID_SEPARATOR,
      //   ID_FILE_PRINT,
      //   ID_APP_ABOUT,
      ID_SEPARATOR,
      ID_VIEW_ZOOM_OUT,
      ID_VIEW_ZOOM_IN,
      ID_SEPARATOR,
      ID_VIEW_PREVIOUSPAGE,
      ID_VIEW_NEXTPAGE
}
;

static UINT BASED_CODE indicators[] =
{
   ID_SEPARATOR,           // Status line indicator
      ////   ID_SEPARATOR,           // Status line indicator
      ////   ID_SEPARATOR,           // Status line indicator
      //   ID_INDICATOR_CAPS,
      //   ID_INDICATOR_NUM,
      //   ID_INDICATOR_SCRL,
      ID_INDICATOR_CYCLE,     // Cycle
      ID_INDICATOR_PAGE,      // Page
}
;

// Utility defined in this file

static HRESULT GetComCtlVersion(LPDWORD pdwMajor, LPDWORD pdwMinor);

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
   // TODO: add member initialization code here
}

CMainFrame::~CMainFrame()
{
}

BOOL CMainFrame::DestroyWindow()
{
   RECT rect;
   CRect crect;

   CWinApp *pWinApp = AfxGetApp();

   // Save main frame coordinates

   GetWindowRect(&rect);

   crect = rect;
   pWinApp->WriteProfileInt("Main", "X", crect.left);
   pWinApp->WriteProfileInt("Main", "Y", crect.top);
   pWinApp->WriteProfileInt("Main", "W", crect.Width());
   pWinApp->WriteProfileInt("Main", "H", crect.Height());

   // Save palette coordinates

   m_wndPaletteBar.GetParentFrame()->GetWindowRect(&rect);
   pWinApp->WriteProfileInt("Palette", "X", rect.left);
   pWinApp->WriteProfileInt("Palette", "Y", rect.top);

   if ((m_wndPaletteBar.GetStyle() & WS_VISIBLE) == 0)
   {
      pWinApp->WriteProfileInt("Palette", "Show", 0);
   }
   else
   {
      pWinApp->WriteProfileInt("Palette", "Show", 1);
   }

   if ((m_wndStatusBar.GetStyle() & WS_VISIBLE) == 0)
   {
      pWinApp->WriteProfileInt("Status", "Show", 0);
   }
   else
   {
      pWinApp->WriteProfileInt("Status", "Show", 1);
   }

   if ((m_wndToolBar.GetStyle() & WS_VISIBLE) == 0)
   {
      pWinApp->WriteProfileInt("Tool", "Show", 0);
   }
   else
   {
      pWinApp->WriteProfileInt("Tool", "Show", 1);
   }

   return(CWnd::DestroyWindow());
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
   int x;
   int y;
   int w;
   int h;

   RECT rect;
   CRect crect;

   CWinApp *pWinApp = AfxGetApp();

   if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1) return -1;

   //   foo.ConnectOn(NULL, NULL, this);
   //   foo.ShowWindow(SW_SHOW);
   //
   //   bar = new CMDIChildWnd;
   //
   //   bar->Create(NULL, "foo", WS_CHILD | WS_VISIBLE | WS_OVERLAPPEDWINDOW, rectDefault, this);

   // Use flat toolbar if Common Control version >= 4.70

   DWORD dwTlbStyleEx = 0;
   DWORD dwMajorVersion = 0;
   DWORD dwMinorVersion = 0;

   HRESULT hr = GetComCtlVersion(&dwMajorVersion, &dwMinorVersion);
   if (SUCCEEDED(hr))
   {
      if (dwMajorVersion > 4)
      {
         dwTlbStyleEx = TBSTYLE_FLAT;
      }
      else if (dwMajorVersion == 4 && dwMinorVersion >= 70)
      {
         dwTlbStyleEx = TBSTYLE_FLAT;
      }
   }

   if (!m_wndToolBar.CreateEx(this, dwTlbStyleEx, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_TOOLTIPS | CBRS_FLYBY) ||
      !m_wndToolBar.LoadBitmap(IDR_MAINFRAME) ||
      !m_wndToolBar.SetButtons(buttons, sizeof(buttons)/sizeof(UINT)))
   {
      TRACE("Failed to create toolbar\n");
      return -1;      // fail to create
   }

   if (!m_wndStatusBar.Create(this) ||
      !m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT)))
   {
      TRACE("Failed to create status bar\n");
      return -1;      // fail to create
   }

   m_wndStatusBar.SetPaneInfo( 1, ID_INDICATOR_CYCLE, SBPS_NORMAL, 120 );
   m_wndStatusBar.SetPaneInfo( 2, ID_INDICATOR_PAGE,  SBPS_NORMAL, 80 );

   EnableDocking(CBRS_ALIGN_ANY);

   if (!m_wndPaletteBar.CreateEx(this, dwTlbStyleEx, WS_CHILD | WS_VISIBLE | CBRS_SIZE_FIXED | CBRS_TOP | CBRS_TOOLTIPS | CBRS_FLYBY, CRect(0,0,0,0), ID_PALETTEBAR) ||
      !m_wndPaletteBar.LoadBitmap(IDR_PALETTE) ||
      !m_wndPaletteBar.SetButtons(palette, sizeof(palette)/sizeof(UINT)))
   {
      TRACE("Failed to create palettebar\n");
      return -1;      // fail to create
   }

   m_wndPaletteBar.SetWindowText(_T("Palette"));
   //m_wndPaletteBar.EnableDocking(CBRS_ALIGN_ANY);
   m_wndPaletteBar.EnableDocking(0);
   m_wndPaletteBar.SetColumns(3);

   // FloatControlBar insists on doing it visibly so do it off screen

   FloatControlBar(&m_wndPaletteBar, CPoint(-1000,0));

   // set not showing if the last saved setting was not showing

   if (pWinApp->GetProfileInt("Palette", "Show", 1) == 0)
   {
      ShowControlBar(&m_wndPaletteBar, FALSE, FALSE);
   }

   if (pWinApp->GetProfileInt("Tool", "Show", 1) == 0)
   {
      ShowControlBar(&m_wndToolBar, FALSE, FALSE);
   }

   if (pWinApp->GetProfileInt("Status", "Show", 1) == 0)
   {
      ShowControlBar(&m_wndStatusBar, FALSE, FALSE);
   }

   // Now validate get window width

   m_wndPaletteBar.GetParentFrame()->GetWindowRect(&rect);
   crect = rect;

   // Get palette position from .INI and width from actual hidden window

   x = pWinApp->GetProfileInt("Palette", "X", 0);
   y = pWinApp->GetProfileInt("Palette", "Y", 0);
   w = crect.Width();
   h = crect.Height();

   // now validate proposed site (this what the width was needed for)

   CheckWindow(&x, &y, &w, &h);

   // now move palette to validated site hidden or not

   m_wndPaletteBar.GetParentFrame()->SetWindowPos(NULL, x, y, 0, 0, SWP_NOSIZE);

   // Get and validate main window coordintes

   x = pWinApp->GetProfileInt("Main", "X", 0);
   y = pWinApp->GetProfileInt("Main", "Y", 0);
   w = pWinApp->GetProfileInt("Main", "W", GetSystemMetrics(SM_CXSCREEN));
   h = pWinApp->GetProfileInt("Main", "H", GetSystemMetrics(SM_CYSCREEN));

   CheckWindow(&x, &y, &w, &h);

   SetWindowPos(NULL, x, y, w, h, 0);

   return 0;
}


/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
   CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
   CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::OnInitMenu(CMenu* pMenu)
{
   CMDIFrameWnd::OnInitMenu(pMenu);

   /*
   // CG: This block added by 'Tip of the Day' component.
   {
   // TODO: This code adds the "Tip of the Day" menu item
   // on the fly.  It may be removed after adding the menu
   // item to all applicable menu items using the resource
   // editor.

   // Add Tip of the Day menu item on the fly!
   static CMenu* pSubMenu = NULL;

   CString strHelp; strHelp.LoadString(CG_IDS_TIPOFTHEDAYHELP);
   CString strMenu;
   int nMenuCount = pMenu->GetMenuItemCount();
   BOOL bFound = FALSE;
   for (int i=0; i < nMenuCount; i++)
   {
   pMenu->GetMenuString(i, strMenu, MF_BYPOSITION);
   if (strMenu == strHelp)
   {
   pSubMenu = pMenu->GetSubMenu(i);
   bFound = TRUE;
   ASSERT(pSubMenu != NULL);
   }
   }

   CString strTipMenu;
   strTipMenu.LoadString(CG_IDS_TIPOFTHEDAYMENU);
   if (!bFound)
   {
   // Help menu is not available. Please add it!
   if (pSubMenu == NULL)
   {
   // The same pop-up menu is shared between mainfrm and frame
   // with the doc.
   static CMenu popUpMenu;
   pSubMenu = &popUpMenu;
   pSubMenu->CreatePopupMenu();
   pSubMenu->InsertMenu(0, MF_STRING|MF_BYPOSITION,
   CG_IDS_TIPOFTHEDAY, strTipMenu);
   }
   pMenu->AppendMenu(MF_STRING|MF_BYPOSITION|MF_ENABLED|MF_POPUP,
   (UINT)pSubMenu->m_hMenu, strHelp);
   DrawMenuBar();
   }
   else
   {
   // Check to see if the Tip of the Day menu has already been added.
   pSubMenu->GetMenuString(0, strMenu, MF_BYPOSITION);

   if (strMenu != strTipMenu)
   {
   // Tip of the Day submenu has not been added to the
   // first position, so add it.
   pSubMenu->InsertMenu(0, MF_BYPOSITION);  // Separator
   pSubMenu->InsertMenu(0, MF_STRING|MF_BYPOSITION,
   CG_IDS_TIPOFTHEDAY, strTipMenu);
   }
   }
   }
   */
}

void CMainFrame::OnHelpTutorial()
{
   ::HtmlHelp(::GetDesktopWindow(), "mmlogic.chm", HH_DISPLAY_TOPIC, (DWORD) "html\\tutorial.htm");
}

void CMainFrame::OnHelpExamples()
{
   CString csFullPath;
   CString csHelpPath;
   CString csFilePath;

   csHelpPath = AfxGetApp()->m_pszHelpFilePath;
   csFilePath = "Examples\\Examples.Txt";

   RelativeToFullPath(csFilePath, csHelpPath, csFullPath);

   LaunchFile(csFullPath);
}

void CMainFrame::OnHelpReleasenotes()
{
   CString csFullPath;
   CString csHelpPath;
   CString csFilePath;

   csHelpPath = AfxGetApp()->m_pszHelpFilePath;
   csFilePath = "README.TXT";

   RelativeToFullPath(csFilePath, csHelpPath, csFullPath);

   LaunchFile(csFullPath);
}

void CMainFrame::OnDDECommand()
{
   ::MessageBox(::GetFocus(),"Who opened an LGI file?","Error", MB_OK | MB_ICONEXCLAMATION);
}

/*void WinHelp(DWORD dwData, UINT nCmd) 
{
switch (nCmd)
{
case HELP_CONTEXT: 
HtmlHelp(NULL, ".\\hlp\\mmlogic.chm",HH_HELP_CONTEXT, dwData );
break;
case HELP_INDEX: 
HtmlHelp(NULL, ".\\hlp\\mmlogic.chm",HH_DISPLAY_TOPIC, 0);
break;
case HELP_FINDER: 
HtmlHelp(NULL, ".\\hlp\\mmlogic.chm",HH_DISPLAY_TOPIC, 0);
break;	
}
}
*/


// The following function is given in the Microsoft Platform SDK/
// It retrieves the version number of Windows Common Controls.

static HRESULT GetComCtlVersion(LPDWORD pdwMajor, LPDWORD pdwMinor)
{
   HINSTANCE   hComCtl;

   if(   IsBadWritePtr(pdwMajor, sizeof(DWORD)) || 
      IsBadWritePtr(pdwMinor, sizeof(DWORD)))
      return E_INVALIDARG;

   //load the DLL
   hComCtl = LoadLibrary(TEXT("comctl32.dll"));

   if(hComCtl)
   {
      HRESULT           hr = S_OK;
      DLLGETVERSIONPROC pDllGetVersion;

      /*
      You must get this function explicitly because earlier versions of the DLL 
      don't implement this function. That makes the lack of implementation of the 
      function a version marker in itself.
      */
      pDllGetVersion = (DLLGETVERSIONPROC)GetProcAddress(hComCtl, TEXT("DllGetVersion"));

      if(pDllGetVersion)
      {
         DLLVERSIONINFO    dvi;

         ZeroMemory(&dvi, sizeof(dvi));
         dvi.cbSize = sizeof(dvi);

         hr = (*pDllGetVersion)(&dvi);

         if(SUCCEEDED(hr))
         {
            *pdwMajor = dvi.dwMajorVersion;
            *pdwMinor = dvi.dwMinorVersion;
         }
         else
         {
            hr = E_FAIL;
         }   
      }
      else
      {
         /*
         If GetProcAddress failed, then the DLL is a version previous to the one 
         shipped with IE 3.x.
         */
         *pdwMajor = 4;
         *pdwMinor = 0;
      }

      FreeLibrary(hComCtl);

      return hr;
   }

   return E_FAIL;
}
//void CMainFrame::OnHelpIndex()
//{
//HWND hWnd = ::GetWindow(AfxGetApp()->m_pMainWnd->m_hWnd, GW_HWNDFIRST);
//
//   ::HtmlHelp(NULL, "mmlogic.chm", HH_DISPLAY_INDEX, 0);
//}

void CMainFrame::OnHelp()
{
   ::HtmlHelp(NULL, "mmlogic.chm", HH_DISPLAY_TOC, NULL);
}

void CMainFrame::OnContextHelp()
{
   ::HtmlHelp(NULL, "mmlogic.chm", HH_DISPLAY_INDEX, 0);
}

//void CMainFrame::OnHelpFinder()
//{
//   ::HtmlHelp(NULL, "mmlogic.chm", HH_HELP_FINDER, NULL);
//}


void CMainFrame::OnSyscommand()
{
CMDIFrameWnd::OnHelpFinder();
//CWinApp::OnHelpFinder();
//CWnd::OnHelpFinder();
}
