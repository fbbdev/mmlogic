// Message.h : interface of the CLogiView class
//
// Copyright (C) 1993-1994 George Mills and Softronics, Inc. Corporation
// All rights reserved.
//

class CLogiNetworkGate;
class CLogiDoc;

class CSocketWnd : public CWnd
{
protected: // create from serialization only

public:
   CSocketWnd();
   DECLARE_DYNCREATE(CSocketWnd)

   // Attributes
public:

   // Operations
public:

   int iSocket;    // Current Handle Send Socket
   int iPort;    // Current requested send Port

   BOOL bConnected;    // Flag that send socket is connected
   BOOL bBusy;         // Flag that send socket is busy
   BOOL bNetworkOn;    // flag for send enabled (enables message processing)

   PHOSTENT phe;       // Pointer to Host Entry for send

   //   CLogiView *pView;
   CLogiDoc *pDoc;
   CLogiNetworkGate *pObj;

public:

   BOOL ConnectOn(int isocket, const char *networkaddress, CLogiDoc* pDoc, CLogiNetworkGate *pObj);
   void ConnectOff(void);
   //   void SetView(CLogiView *pView);
   BOOL SendData(char *Data);

   // Implementation
public:
   virtual ~CSocketWnd();

   // Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(CSocketWnd)
public:
   //}}AFX_VIRTUAL

public:
   // Generated message map functions
protected:
   //{{AFX_MSG(CSocketWnd)
   afx_msg LONG OnNetAcceptfinish(UINT wParam, LONG lParam);
   afx_msg LONG OnNetConnectack(UINT wParam, LONG lParam);
   afx_msg LONG OnNetConnectfinish(UINT wParam, LONG lParam);
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
}
;

/////////////////////////////////////////////////////////////////////////////

