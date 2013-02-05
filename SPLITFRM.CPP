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
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSplitFrame message handlers
