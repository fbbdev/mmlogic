// palette.cpp : implementation of the Floating tool palette class
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1992-1995 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

#include "stdafx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPaletteBar

BEGIN_MESSAGE_MAP(CPaletteBar, CToolBar)
   //{{AFX_MSG_MAP(CPaletteBar)
   ON_WM_CREATE()
   ON_WM_DESTROY()
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPaletteBar construction/destruction

CPaletteBar::CPaletteBar()
{
   m_nColumns = 2;
   m_cxLeftBorder = 5;
   m_cyTopBorder = 5;
   m_cxRightBorder = 5;
   m_cyBottomBorder = 5;
}

CPaletteBar::~CPaletteBar()
{
}

/////////////////////////////////////////////////////////////////////////////
// CPaletteBar diagnostics

#ifdef _DEBUG
void CPaletteBar::AssertValid() const
{
   CToolBar::AssertValid();
}

void CPaletteBar::Dump(CDumpContext& dc) const
{
   CToolBar::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPaletteBar message handlers

void CPaletteBar::SetColumns(UINT nColumns)
{
   m_nColumns = nColumns;
   int nCount = GetToolBarCtrl().GetButtonCount();

   for (int i = 0; i < nCount; i++)
   {
      UINT nStyle = GetButtonStyle(i);
      BOOL bWrap = (((i + 1) % nColumns) == 0);
      if (bWrap)
         nStyle |= TBBS_WRAPPED;
      else
         nStyle &= ~TBBS_WRAPPED;
      SetButtonStyle(i, nStyle);
   }

   Invalidate();
   GetParentFrame()->RecalcLayout();
}

int CPaletteBar::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
   if (CToolBar::OnCreate(lpCreateStruct) == -1)
      return -1;

   // TODO: Add your specialized creation code here

   return 0;
}

void CPaletteBar::OnDestroy()
{
   CToolBar::OnDestroy();

   // TODO: Add your message handler code here

}
