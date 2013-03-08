// splitfra.cpp : implementation file
//
// Copyright (C) 1992-1993 George Mills and Softronics, Inc. Corporation
// All rights reserved.
//

#include "stdafx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSplitFrame

IMPLEMENT_DYNCREATE(CSplitFrame, CMDIChildWnd)

CSplitFrame::CSplitFrame()
{
}

CSplitFrame::~CSplitFrame()
{
}

BOOL CSplitFrame::OnCreateClient(LPCREATESTRUCT /*lpcs*/, CCreateContext* pContext)
{
   m_haccel = LoadAccelerators(AfxGetInstanceHandle() ,MAKEINTRESOURCE(IDR_LOGICLTYPE_CNTR_IP));
   return m_wndSplitter.Create(this,
      2, 2,       // TODO: adjust the number of rows, columns
      CSize(10, 10),  // TODO: adjust the minimum pane size
      pContext);
}

BEGIN_MESSAGE_MAP(CSplitFrame, CMDIChildWnd)
   //{{AFX_MSG_MAP(CSplitFrame)
   // NOTE - the ClassWizard will add and remove mapping macros here.
   //}}AFX_MSG_MAP
   ON_WM_SYSCOMMAND()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSplitFrame message handlers
void CSplitFrame::OnSysCommand(UINT nID, LONG lParam)
{
   if ( ( nID & 0x0FFF0 ) != SC_CLOSE )
   {
      //Pass through any messages other than SC_CLOSE
      CMDIChildWnd::OnSysCommand( nID, lParam );
   } else
   {
      //
      CMDIFrameWnd *pFrame = 
         (CMDIFrameWnd*)AfxGetApp()->m_pMainWnd;

      // Get the active MDI child window.
      CMDIChildWnd *pChild = 
         (CMDIChildWnd *) pFrame->GetActiveFrame();

      // Send ID_FILE_CLOSE to the active MDI child window where CLogiDoc::OnFileClose
      // will set m_bCloseNotExit=TRUE and let CDocument::OnFileClose take over.
      pChild->SendMessage(WM_COMMAND,ID_FILE_CLOSE);
   }
}
