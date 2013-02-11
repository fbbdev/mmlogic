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
      //for now just keep from closing at all
      //later we will set bool var to let it be known user try to close document
		CMDIChildWnd::OnSysCommand( nID, lParam );
	} else
   {
//      CLogiDoc::UserReqCloseDoc();
      ::MessageBox(::GetFocus(),"This is where we would notify ClogiDoc that the user wants to close the document, not exit the program.", "Error", MB_OK | MB_ICONEXCLAMATION);
   }
}
