// splitfra.h : header file
//
// Copyright (C) 1993-1994 George Mills and Softronics, Inc. Corporation
// All rights reserved.
//

/////////////////////////////////////////////////////////////////////////////
// CSplitFrame frame with splitter

class CSplitFrame : public CMDIChildWnd
{
   DECLARE_DYNCREATE(CSplitFrame)
protected:
   CSplitFrame();          // protected constructor used by dynamic creation

   // Attributes
protected:
   CSplitterWnd    m_wndSplitter;
public:

   // Operations
public:

   // Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(CSplitFrame)
   virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
   //}}AFX_VIRTUAL

   // Implementation
public:
   virtual ~CSplitFrame();
   void CSplitFrame::OnSysCommand(UINT nID, LONG lParam);
   HACCEL m_haccel;

   // Generated message map functions
   //{{AFX_MSG(CSplitFrame)
   // NOTE - the ClassWizard will add and remove member functions here.
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
}
;

/////////////////////////////////////////////////////////////////////////////
