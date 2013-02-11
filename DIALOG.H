// dialog.h : interface of All Dlg classes
//
// Copyright (C) 1993-1994 George Mills and Softronics, Inc. Corporation
// All rights reserved.
//

/////////////////////////////////////////////////////////////////////////////
// CRectDlg dialog

class CRectDlg : public CDialog
{
   // Construction
public:
   CRectDlg(CWnd* pParent = NULL); // standard constructor

   // Dialog Data
   //{{AFX_DATA(CRectDlg)
   enum { IDD = IDD_PROP_RECT }; //ignore//
   BOOL    m_bNoFill;
   UINT    m_penSize;
   //}}AFX_DATA

   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(CRectDlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

   // Implementation
protected:

   // Generated message map functions
   //{{AFX_MSG(CRectDlg)
   virtual BOOL OnInitDialog();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
}
;

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// CAndDlg dialog

class CAndDlg : public CDialog
{
   // Construction
public:
   CAndDlg(CWnd* pParent = NULL);	// standard constructor
   void RecalcBM();

   CBitmapButton m_bmBtn;

   // Dialog Data
   //{{AFX_DATA(CAndDlg)
   enum { IDD = IDD_PROP_AND }; //ignore//
   BOOL	m_bDemorgan;
   int		m_iInputs;
   //}}AFX_DATA

   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(CAndDlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

   // Implementation
protected:

   // Generated message map functions
   //{{AFX_MSG(CAndDlg)
   afx_msg void OnAnd2inputs();
   afx_msg void OnAnd3inputs();
   afx_msg void OnAnd4inputs();
   afx_msg void OnAndDemorgan();
   virtual BOOL OnInitDialog();
   afx_msg void OnHelp();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
}
;
/////////////////////////////////////////////////////////////////////////////
// CBuzzerDlg dialog

class CBuzzerDlg : public CDialog
{
   // Construction
public:
   CBuzzerDlg(CWnd* pParent = NULL);	// standard constructor

   CBitmapButton m_bmBtn;

   // Dialog Data
   //{{AFX_DATA(CBuzzerDlg)
   enum { IDD = IDD_PROP_BUZZER }; //ignore//
   int		m_iFreq;
   int		m_iDuration;
   //}}AFX_DATA

   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(CBuzzerDlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

   // Implementation
protected:

   // Generated message map functions
   //{{AFX_MSG(CBuzzerDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnBuzzerTest();
   afx_msg void OnHelp();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
}
;
/////////////////////////////////////////////////////////////////////////////
// CLedDlg dialog

class CLedDlg : public CDialog
{
   // Construction
public:
   CLedDlg(CWnd* pParent = NULL);	// standard constructor

   void RecalcBM();

   CBitmapButton m_bmBtn;

   // Dialog Data
   //{{AFX_DATA(CLedDlg)
   enum { IDD = IDD_PROP_LED }; //ignore//
   int		m_iRed;
   int		m_iBlink;
   //}}AFX_DATA

   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(CLedDlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

   // Implementation
protected:

   // Generated message map functions
   //{{AFX_MSG(CLedDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnLedGreen();
   afx_msg void OnLedRed();
   afx_msg void OnLedYellow();
   afx_msg void OnHelp();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
}
;
/////////////////////////////////////////////////////////////////////////////
// COrDlg dialog

class COrDlg : public CDialog
{
   // Construction
public:
   COrDlg(CWnd* pParent = NULL);	// standard constructor

   void RecalcBM();

   CBitmapButton m_bmBtn;

   // Dialog Data
   //{{AFX_DATA(COrDlg)
   enum { IDD = IDD_PROP_OR }; //ignore//
   int		m_iInputs;
   BOOL	m_bDemorgan;
   //}}AFX_DATA

   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(COrDlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

   // Implementation
protected:

   // Generated message map functions
   //{{AFX_MSG(COrDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnOr2inputs();
   afx_msg void OnOr3inputs();
   afx_msg void OnOr4inputs();
   afx_msg void OnOrDemorgan();
   afx_msg void OnHelp();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
}
;
/////////////////////////////////////////////////////////////////////////////
// COscillatorDlg dialog

class COscillatorDlg : public CDialog
{
   // Construction
public:
   COscillatorDlg(CWnd* pParent = NULL);	// standard constructor

   CBitmapButton m_bmBtn;

   // Dialog Data
   //{{AFX_DATA(COscillatorDlg)
   enum { IDD = IDD_PROP_OSCILLATOR }; //ignore//
   int		m_iOscillatorHi;
   int		m_iOscillatorLo;
   BOOL	m_bOscillatorStartLo;
   //}}AFX_DATA

   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(COscillatorDlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

   // Implementation
protected:

   // Generated message map functions
   //{{AFX_MSG(COscillatorDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnHelp();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
}
;
/////////////////////////////////////////////////////////////////////////////
// CSwitchDlg dialog

class CSwitchDlg : public CDialog
{
   // Construction
public:
   CSwitchDlg(CWnd* pParent = NULL);	// standard constructor

   void RecalcBM();

   CBitmapButton m_bmBtn;

   // Dialog Data
   //{{AFX_DATA(CSwitchDlg)
   enum { IDD = IDD_PROP_SWITCH }; //ignore//
   int		m_iOn;
   int		m_iToggle;
   //}}AFX_DATA

   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(CSwitchDlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

   // Implementation
protected:

   // Generated message map functions
   //{{AFX_MSG(CSwitchDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnSwitchOff();
   afx_msg void OnSwitchOn();
   afx_msg void OnSwitchMomentary();
   afx_msg void OnSwitchToggle();
   afx_msg void OnHelp();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
}
;
/////////////////////////////////////////////////////////////////////////////
// CLed7Dlg dialog

class CLed7Dlg : public CDialog
{
   // Construction
public:
   CLed7Dlg(CWnd* pParent = NULL);	// standard constructor

   void RecalcBM();

   CBitmapButton m_bmBtn;

   // Dialog Data
   //{{AFX_DATA(CLed7Dlg)
   enum { IDD = IDD_PROP_LED7 }; //ignore//
   int		m_iInputs;
   int		m_iRed;
   //}}AFX_DATA

   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(CLed7Dlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

   // Implementation
protected:

   // Generated message map functions
   //{{AFX_MSG(CLed7Dlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnLed74inputs();
   afx_msg void OnLed77inputs();
   afx_msg void OnHelp();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
}
;
/////////////////////////////////////////////////////////////////////////////
// CWireDlg dialog

class CWireDlg : public CDialog
{
   // Construction
public:
   CWireDlg(CWnd* pParent = NULL);	// standard constructor

   CBitmapButton m_bmBtn;

   // Dialog Data
   //{{AFX_DATA(CWireDlg)
   enum { IDD = IDD_PROP_WIRE }; //ignore//
   int		m_iRoute;
   BOOL	m_bHide;
   //}}AFX_DATA

   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(CAboutDlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

   // Implementation
protected:

   // Generated message map functions
   //{{AFX_MSG(CWireDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnHelp();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
}
;
/////////////////////////////////////////////////////////////////////////////
// CInvertDlg dialog

class CInvertDlg : public CDialog
{
   // Construction
public:
   CInvertDlg(CWnd* pParent = NULL);	// standard constructor

   void RecalcBM();

   CBitmapButton m_bmBtn;

   // Dialog Data
   //{{AFX_DATA(CInvertDlg)
   enum { IDD = IDD_PROP_INVERT }; //ignore//
   BOOL	m_bDemorgan;
   //}}AFX_DATA

   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(CInvertDlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

   // Implementation
protected:

   // Generated message map functions
   //{{AFX_MSG(CInvertDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnInvertDemorgan();
   afx_msg void OnHelp();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
}
;

/////////////////////////////////////////////////////////////////////////////
// CSetupDlg dialog

class CSetupDlg : public CDialog
{
   // Construction
public:
   CSetupDlg(CWnd* pParent = NULL);	// standard constructor

   // Dialog Data
   //{{AFX_DATA(CSetupDlg)
   enum { IDD = IDD_SIMULATE_SETUP };
   CEdit    m_ceSimRate;
   int		m_iUnconnected;
   int      m_iSimRateType;
   int      m_iSimRate;
   //}}AFX_DATA

   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(CSetupDlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

   // Implementation
protected:

   // Generated message map functions
   //{{AFX_MSG(CSetupDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnSimulateHelp();
   afx_msg void OnSimulateSpeedUpdate();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
}
;
/////////////////////////////////////////////////////////////////////////////
// CIoinDlg dialog

class CIoinDlg : public CDialog
{
   // Construction
public:
   CIoinDlg(CWnd* pParent = NULL);	// standard constructor

   CBitmapButton m_bmBtn;

   // Dialog Data
   //{{AFX_DATA(CIoinDlg)
   enum { IDD = IDD_PROP_IO_IN }; //ignore//
   UINT	m_iAddress;
   UINT	m_iInitial;
   //}}AFX_DATA

   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(CIoinDlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

   // Implementation
protected:

   // Generated message map functions
   //{{AFX_MSG(CIoinDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnHelp();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
}
;
/////////////////////////////////////////////////////////////////////////////
// CIooutDlg dialog

class CIooutDlg : public CDialog
{
   // Construction
public:
   CIooutDlg(CWnd* pParent = NULL);	// standard constructor

   CBitmapButton m_bmBtn;

   // Dialog Data
   //{{AFX_DATA(CIooutDlg)
   enum { IDD = IDD_PROP_IO_OUT }; //ignore//
   UINT	m_iAddress;
   UINT	m_iInitial;
   //}}AFX_DATA

   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(CIooutDlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

   // Implementation
protected:

   // Generated message map functions
   //{{AFX_MSG(CIooutDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnHelp();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
}
;
/////////////////////////////////////////////////////////////////////////////
// CNoneDlg dialog

class CNoneDlg : public CDialog
{
   // Construction
public:
   CNoneDlg(CWnd* pParent = NULL);	// standard constructor

   // Dialog Data
   //{{AFX_DATA(CNoneDlg)
   enum { IDD = IDD_PROP_NONE }; //ignore//
   // NOTE: the ClassWizard will add data members here
   //}}AFX_DATA

   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(CNoneDlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

   // Implementation
protected:

   // Generated message map functions
   //{{AFX_MSG(CNoneDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnHelp();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
}
;
/////////////////////////////////////////////////////////////////////////////
// CSoundDlg dialog

class CSoundDlg : public CDialog
{
   // Construction
public:
   CSoundDlg(CWnd* pParent = NULL);	// standard constructor

   CBitmapButton m_bmBtn;
   CString m_csPathName;

   // Dialog Data
   //{{AFX_DATA(CSoundDlg)
   enum { IDD = IDD_PROP_SOUND }; //ignore//
   CButton	m_cbEdit;
   CButton	m_cbBrowse;
   CString	m_csFileName;
   BOOL	m_bWait;
   //}}AFX_DATA

   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(CSoundDlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

   // Implementation
protected:

   // Generated message map functions
   //{{AFX_MSG(CSoundDlg)
   afx_msg void OnBrowse();
   virtual BOOL OnInitDialog();
   afx_msg void OnHelp();
   afx_msg void OnEdit();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
}
;
/////////////////////////////////////////////////////////////////////////////
// CFileinDlg dialog

class CFileinDlg : public CDialog
{
   // Construction
public:
   CFileinDlg(CWnd* pParent = NULL);	// standard constructor

   CBitmapButton m_bmBtn;
   CString m_csPathName;

   // Dialog Data
   //{{AFX_DATA(CFileinDlg)
   enum { IDD = IDD_PROP_FILE_IN };
   CString	m_csFileName;
   int		m_iFormat;
   //}}AFX_DATA

   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(CFileinDlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

   // Implementation
protected:

   // Generated message map functions
   //{{AFX_MSG(CFileinDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnBrowse();
   afx_msg void OnHelp();
   afx_msg void OnEdit();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
}
;
/////////////////////////////////////////////////////////////////////////////
// CFileoutDlg dialog

class CFileoutDlg : public CDialog
{
   // Construction
public:
   CFileoutDlg(CWnd* pParent = NULL);	// standard constructor

   CBitmapButton m_bmBtn;
   CString m_csPathName;

   // Dialog Data
   //{{AFX_DATA(CFileoutDlg)
   enum { IDD = IDD_PROP_FILE_OUT };
   CString	m_csFileName;
   int		m_iFormat;
   //}}AFX_DATA

   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(CFileoutDlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

   // Implementation
protected:

   // Generated message map functions
   //{{AFX_MSG(CFileoutDlg)
   afx_msg void OnBrowse();
   virtual BOOL OnInitDialog();
   afx_msg void OnHelp();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
}
;
/////////////////////////////////////////////////////////////////////////////
// CBitmapDlg dialog

class CBitmapDlg : public CDialog
{
   // Construction
public:
   CBitmapDlg(CWnd* pParent = NULL);   // standard constructor
   void RecalcBM();

   CBitmapButton m_bmBtn;
   CString m_csPathName;

   // Dialog Data
   //{{AFX_DATA(CBitmapDlg)
   enum { IDD = IDD_PROP_BMP }; //ignore//
   CButton	m_cbPlayground;
   CEdit	m_ceFileName;
   CButton	m_cbEdit;
   CButton	m_cbBrowse;
   CString	m_csFileName;
   int		m_iStyle;
   BOOL	m_bPlayground;
   //}}AFX_DATA

   // Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(CBitmapDlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

   // Implementation
protected:

   // Generated message map functions
   //{{AFX_MSG(CBitmapDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnBrowse();
   afx_msg void OnHelp();
   afx_msg void OnBmpSingle();
   afx_msg void OnBmpMultiple();
   afx_msg void OnEdit();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
}
;
/////////////////////////////////////////////////////////////////////////////
// CMemoryDlg dialog

class CMemoryDlg : public CDialog
{
   // Construction
public:
   CMemoryDlg(CWnd* pParent = NULL);   // standard constructor
   void RecalcBM();

   CBitmapButton m_bmBtn;
   CString m_csPathName;

   // Dialog Data
   //{{AFX_DATA(CMemoryDlg)
   enum { IDD = IDD_PROP_MEMORY };
   CButton	m_cbEdit;
   CButton	m_cbBrowse;
   int		m_iBinaryMode;
   int  m_iAddressMode;
   CString	m_csFileName;
   //}}AFX_DATA


   // Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(CMemoryDlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

   // Implementation
protected:

   // Generated message map functions
   //{{AFX_MSG(CMemoryDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnMem8Bits();
   afx_msg void OnMem16Bits();
   afx_msg void OnBrowse();
   afx_msg void OnHelp();
   afx_msg void OnEdit();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
}
;
/////////////////////////////////////////////////////////////////////////////
// CTextDlg dialog

class CTextDlg : public CDialog
{
   // Construction
public:
   CTextDlg(CWnd* pParent = NULL);   // standard constructor

   void RecalcBM();

   CBitmapButton m_bmBtn;
   CString m_csPathName;

   // Dialog Data
   //{{AFX_DATA(CTextDlg)
   enum { IDD = IDD_PROP_TEXT }; //ignore//
   CButton	m_cbEdit;
   CButton	m_cbBrowse;
   CEdit	m_ceFileName;
   CString	m_pTextText;
   int		m_iStyle;
   CString	m_csFileName;
   //}}AFX_DATA


   // Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(CTextDlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

   // Implementation
protected:

   // Generated message map functions
   //{{AFX_MSG(CTextDlg)
   afx_msg void OnHelp();
   afx_msg void OnTextMultiple();
   afx_msg void OnTextSingle();
   afx_msg void OnBrowse();
   virtual BOOL OnInitDialog();
   afx_msg void OnEdit();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
}
;
/////////////////////////////////////////////////////////////////////////////
// CMuxDlg dialog

class CMuxDlg : public CDialog
{
   // Construction
public:
   CMuxDlg(CWnd* pParent = NULL);   // standard constructor

   void RecalcBM();

   CBitmapButton m_bmBtn;

   // Dialog Data
   //{{AFX_DATA(CMuxDlg)
   enum { IDD = IDD_PROP_MUX }; //ignore//
   BOOL	m_bDeMux;
   int		m_iStyle;
   //}}AFX_DATA


   // Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(CMuxDlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

   // Implementation
protected:

   // Generated message map functions
   //{{AFX_MSG(CMuxDlg)
   afx_msg void OnMuxDemux();
   virtual BOOL OnInitDialog();
   afx_msg void OnHelp();
   afx_msg void OnMuxDemux1to2();
   afx_msg void OnMuxDemux2to4();
   afx_msg void OnMuxDemux3to8();
   afx_msg void OnMuxMux2to1();
   afx_msg void OnMuxMux4to1();
   afx_msg void OnMuxMux8to1();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
}
;
/////////////////////////////////////////////////////////////////////////////
// CRandomDlg dialog

class CRandomDlg : public CDialog
{
   // Construction
public:
   CRandomDlg(CWnd* pParent = NULL);   // standard constructor

   CBitmapButton m_bmBtn;

   // Dialog Data
   //{{AFX_DATA(CRandomDlg)
   enum { IDD = IDD_PROP_RANDOM }; //ignore//
   UINT	m_uSeed;
   int		m_iSpare;
   //}}AFX_DATA


   // Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(CRandomDlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

   // Implementation
protected:

   // Generated message map functions
   //{{AFX_MSG(CRandomDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnHelp();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
}
;
/////////////////////////////////////////////////////////////////////////////
// CXorDlg dialog

class CXorDlg : public CDialog
{
   // Construction
public:
   CXorDlg(CWnd* pParent = NULL);   // standard constructor
   void RecalcBM();

   CBitmapButton m_bmBtn;

   // Dialog Data
   //{{AFX_DATA(CXorDlg)
   enum { IDD = IDD_PROP_XOR }; //ingore//
   int		m_i2Inputs;
   BOOL	m_bDemorgan;
   //}}AFX_DATA


   // Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(CXorDlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

   // Implementation
protected:

   // Generated message map functions
   //{{AFX_MSG(CXorDlg)
   afx_msg void OnHelp();
   virtual BOOL OnInitDialog();
   afx_msg void OnXor2inputs();
   afx_msg void OnXor3inputs();
   afx_msg void OnXor4inputs();
   afx_msg void OnXorDemorgan();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
}
;
/////////////////////////////////////////////////////////////////////////////
// CClockDlg dialog

class CClockDlg : public CDialog
{
   // Construction
public:
   CClockDlg(CWnd* pParent = NULL);   // standard constructor

   CBitmapButton m_bmBtn;

   // Dialog Data
   //{{AFX_DATA(CClockDlg)
   enum { IDD = IDD_PROP_CLOCK }; //ignore//
   int		m_iSeconds;
   BOOL	m_bSpare;
   //}}AFX_DATA


   // Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(CClockDlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

   // Implementation
protected:

   // Generated message map functions
   //{{AFX_MSG(CClockDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnHelp();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
}
;
/////////////////////////////////////////////////////////////////////////////
// CTimerDlg dialog

class CTimerDlg : public CDialog
{
   // Construction
public:
   CTimerDlg(CWnd* pParent = NULL);   // standard constructor

   CBitmapButton m_bmBtn;

   // Dialog Data
   //{{AFX_DATA(CTimerDlg)
   enum { IDD = IDD_PROP_TIMER }; //ignore//
   UINT	m_uDelay;
   BOOL	m_bSpare;
   //}}AFX_DATA


   // Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(CTimerDlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

   // Implementation
protected:

   // Generated message map functions
   //{{AFX_MSG(CTimerDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnHelp();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
}
;
/////////////////////////////////////////////////////////////////////////////
// CSignalreceiverDlg dialog

class CSignalreceiverDlg : public CDialog
{
   // Construction
public:
   CSignalreceiverDlg(CWnd* pParent = NULL);   // standard constructor

   CBitmapButton m_bmBtn;

   // Dialog Data
   //{{AFX_DATA(CSignalreceiverDlg)
   enum { IDD = IDD_PROP_SIGNALRECEIVER }; //ignore//
   CString	m_csSignalName;
   int		m_iDummy;
   //}}AFX_DATA


   // Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(CSignalreceiverDlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

   // Implementation
protected:

   // Generated message map functions
   //{{AFX_MSG(CSignalreceiverDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnHelp();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
}
;
/////////////////////////////////////////////////////////////////////////////
// CSignalsenderDlg dialog

class CSignalsenderDlg : public CDialog
{
   // Construction
public:
   CSignalsenderDlg(CWnd* pParent = NULL);   // standard constructor

   CBitmapButton m_bmBtn;

   // Dialog Data
   //{{AFX_DATA(CSignalsenderDlg)
   enum { IDD = IDD_PROP_SIGNALSENDER }; //ingore//
   CString	m_csSignalName;
   int		m_iDummy;
   //}}AFX_DATA


   // Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(CSignalsenderDlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

   // Implementation
protected:

   // Generated message map functions
   //{{AFX_MSG(CSignalsenderDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnHelp();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
}
;
/////////////////////////////////////////////////////////////////////////////
// CKeyboardDlg dialog

class CKeyboardDlg : public CDialog
{
   // Construction
public:
   CKeyboardDlg(CWnd* pParent = NULL);   // standard constructor

   CBitmapButton m_bmBtn;

   // Dialog Data
   //{{AFX_DATA(CKeyboardDlg)
   enum { IDD = IDD_PROP_KEYBOARD }; //ignore//
   BOOL	m_bAscii;
   //}}AFX_DATA


   // Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(CKeyboardDlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

   // Implementation
protected:

   // Generated message map functions
   //{{AFX_MSG(CKeyboardDlg)
   afx_msg void OnHelp();
   virtual BOOL OnInitDialog();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
}
;
/////////////////////////////////////////////////////////////////////////////
// CNetworkDlg dialog

class CNetworkDlg : public CDialog
{
   // Construction
public:
   CNetworkDlg(CWnd* pParent = NULL);   // standard constructor
   void RecalcBM();

   CBitmapButton m_bmBtn;

   // Dialog Data
   //{{AFX_DATA(CNetworkDlg)
   enum { IDD = IDD_PROP_NETWORK }; //ignore//
   CEdit	m_ceName;
   int		m_iDirection;
   CString	m_csName;
   UINT	m_uPort;
   //}}AFX_DATA


   // Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(CNetworkDlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

   // Implementation
protected:

   // Generated message map functions
   //{{AFX_MSG(CNetworkDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnHelp();
   afx_msg void OnNetworkListen();
   afx_msg void OnNetworkMake();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
}
;
/////////////////////////////////////////////////////////////////////////////
// CNodeDlg dialog

class CNodeDlg : public CDialog
{
   // Construction
public:
   CNodeDlg(CWnd* pParent = NULL);   // standard constructor
   void RecalcBM();

   CBitmapButton m_bmBtn;

   // Dialog Data
   //{{AFX_DATA(CNodeDlg)
   enum { IDD = IDD_PROP_NODE };
   int		m_iPass;
   int		m_iFloat;
   //}}AFX_DATA


   // Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(CNodeDlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

   // Implementation
protected:

   // Generated message map functions
   //{{AFX_MSG(CNodeDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnHelp();
   afx_msg void OnNodePass();
   afx_msg void OnNodePulldown();
   afx_msg void OnNodePullup();
   afx_msg void OnNodeZero();
   afx_msg void OnNodeFloat();
   afx_msg void OnNodeOne();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
}
;
/////////////////////////////////////////////////////////////////////////////
// CFlipflopDlg dialog

class CFlipflopDlg : public CDialog
{
   // Construction
public:
   CFlipflopDlg(CWnd* pParent = NULL);   // standard constructor
   void RecalcBM();

   CBitmapButton m_bmBtn;

   // Dialog Data
   //{{AFX_DATA(CFlipflopDlg)
   enum { IDD = IDD_PROP_FLIPFLOP }; //ignore//
   int		m_iStyle;
   BOOL m_bPresetClear;
   BOOL	m_bEdge;
   //}}AFX_DATA


   // Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(CFlipflopDlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

   // Implementation
protected:

   // Generated message map functions
   //{{AFX_MSG(CFlipflopDlg)
   afx_msg void OnHelp();
   virtual BOOL OnInitDialog();
   afx_msg void OnFlipflopCrs();
   afx_msg void OnFlipflopDl();
   afx_msg void OnFlipflopJk();
   afx_msg void OnFlipflopMsdl();
   afx_msg void OnFlipflopMsrs();
   afx_msg void OnFlipflopRs();
   afx_msg void OnFlipflopPresetClear();
   afx_msg void OnFlipflopEdge();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
}
;
/////////////////////////////////////////////////////////////////////////////
// CRobotDlg dialog

class CRobotDlg : public CDialog
{
   // Construction
public:
   CRobotDlg(CWnd* pParent = NULL);   // standard constructor
   void RecalcBM();

   CString m_csPathName;
   CBitmapButton m_bmBtn;

   // Dialog Data
   //{{AFX_DATA(CRobotDlg)
   enum { IDD = IDD_PROP_ROBOT };
   CEdit	m_cePositionY;
   CEdit	m_cePositionX;
   CEdit	m_ceHotspotY;
   CEdit	m_ceHotspotX;
   CString	m_csFileName;
   int		m_iStyle;
   int		m_iHotspot;
   int		m_iPosition;
   int		m_iHotspotX;
   int		m_iHotspotY;
   int		m_iPositionX;
   int		m_iPositionY;
   //}}AFX_DATA


   // Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(CRobotDlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

   // Implementation
protected:

   // Generated message map functions
   //{{AFX_MSG(CRobotDlg)
   afx_msg void OnBrowse();
   afx_msg void OnHelp();
   virtual BOOL OnInitDialog();
   afx_msg void OnEdit();
   afx_msg void OnHotspotCenter();
   afx_msg void OnHotspotCt();
   afx_msg void OnHotspotLl();
   afx_msg void OnHotspotLr();
   afx_msg void OnHotspotUl();
   afx_msg void OnHotspotUr();
   afx_msg void OnPositionCenter();
   afx_msg void OnPositionCt();
   afx_msg void OnPositionLl();
   afx_msg void OnPositionLr();
   afx_msg void OnPositionUl();
   afx_msg void OnPositionUr();
   afx_msg void OnStyleDrawing();
   afx_msg void OnStyleSeeing();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
}
;
/////////////////////////////////////////////////////////////////////////////
// CSelectDlg dialog

class CSelectDlg : public CDialog
{
   // Construction
public:
   CSelectDlg(CWnd* pParent = NULL);   // standard constructor

   void RecalcBM();

   CBitmapButton m_bmBtn;

   // Dialog Data
   //{{AFX_DATA(CSelectDlg)
   enum { IDD = IDD_PROP_SELECT }; //ignore//
   int		m_iInitial;
   //}}AFX_DATA


   // Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(CSelectDlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

   // Implementation
protected:

   // Generated message map functions
   //{{AFX_MSG(CSelectDlg)
   afx_msg void OnSelect0();
   afx_msg void OnSelect1();
   afx_msg void OnSelect2();
   afx_msg void OnSelect3();
   afx_msg void OnSelect4();
   afx_msg void OnSelect5();
   afx_msg void OnSelect6();
   afx_msg void OnSelect7();
   afx_msg void OnSelect8();
   afx_msg void OnSelect9();
   afx_msg void OnSelectA();
   afx_msg void OnSelectB();
   afx_msg void OnSelectC();
   afx_msg void OnSelectD();
   afx_msg void OnSelectE();
   afx_msg void OnSelectF();
   virtual BOOL OnInitDialog();
   afx_msg void OnHelp();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
}
;
class CGridDlg : public CDialog
{
   // Construction
public:
   CGridDlg(CWnd* pParent = NULL);   // standard constructor

   // Dialog Data
   //{{AFX_DATA(CGridDlg)
   enum { IDD = IDD_GRID };
   BOOL	m_bEnable;
   UINT	m_uHeight;
   UINT	m_uWidth;
   UINT  m_uCanvasHeight;
   UINT  m_uCanvasWidth;
   //}}AFX_DATA


   // Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(CGridDlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

   // Implementation
protected:

   // Generated message map functions
   //{{AFX_MSG(CGridDlg)
   // NOTE: the ClassWizard will add member functions here
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
// CTristateDlg dialog

class CTristateDlg : public CDialog
{
   // Construction
public:
   CTristateDlg(CWnd* pParent = NULL);   // standard constructor
   void RecalcBM();

   CBitmapButton m_bmBtn;

   // Dialog Data
   //{{AFX_DATA(CTristateDlg)
   enum { IDD = IDD_PROP_TRISTATE };
   BOOL	m_bAssertLO;
   BOOL	m_bDemorgan;
   //}}AFX_DATA


   // Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(CTristateDlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

   // Implementation
protected:

   // Generated message map functions
   //{{AFX_MSG(CTristateDlg)
   afx_msg void OnTristateAssertLo();
   afx_msg void OnTristateDemorgan();
   virtual BOOL OnInitDialog();
   afx_msg void OnHelp();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
// CBusDlg dialog

class CBusDlg : public CDialog
{
   // Construction
public:
   CBusDlg(CWnd* pParent = NULL);   // standard constructor
   void RecalcBM();

   CBitmapButton m_bmBtn;

   // Dialog Data
   //{{AFX_DATA(CBusDlg)
   enum { IDD = IDD_PROP_BUS };
   int		m_iInputs;
   //}}AFX_DATA


   // Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(CBusDlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

   // Implementation
protected:

   // Generated message map functions
   //{{AFX_MSG(CBusDlg)
   afx_msg void OnBus2inputs();
   afx_msg void OnBus4inputs();
   afx_msg void OnBus8inputs();
   virtual BOOL OnInitDialog();
   afx_msg void OnHelp();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
// CAluDlg dialog

class CAluDlg : public CDialog
{
   // Construction
public:
   CAluDlg(CWnd* pParent = NULL);   // standard constructor

   CBitmapButton m_bmBtn;

   // Dialog Data
   //{{AFX_DATA(CAluDlg)
   enum { IDD = IDD_PROP_ALU };
   // NOTE: the ClassWizard will add data members here
   //}}AFX_DATA


   // Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(CAluDlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

   // Implementation
protected:

   // Generated message map functions
   //{{AFX_MSG(CAluDlg)
   afx_msg void OnHelp();
   virtual BOOL OnInitDialog();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
// CBitBucketDlg dialog

class CBitBucketDlg : public CDialog
{
   // Construction
public:
   CBitBucketDlg(CWnd* pParent = NULL);   // standard constructor

   CBitmapButton m_bmBtn;

   // Dialog Data
   //{{AFX_DATA(CBitBucketDlg)
   enum { IDD = IDD_PROP_BITBUCKET };
   // NOTE: the ClassWizard will add data members here
   //}}AFX_DATA


   // Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(CBitBucketDlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

   // Implementation
protected:

   // Generated message map functions
   //{{AFX_MSG(CBitBucketDlg)
   afx_msg void OnHelp();
   virtual BOOL OnInitDialog();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
// CPauseDlg dialog

class CPauseDlg : public CDialog
{
   // Construction
public:
   CPauseDlg(CWnd* pParent = NULL);   // standard constructor

   CBitmapButton m_bmBtn;

   // Dialog Data
   //{{AFX_DATA(CPauseDlg)
   enum { IDD = IDD_PROP_PAUSE };
   // NOTE: the ClassWizard will add data members here
   //}}AFX_DATA


   // Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(CPauseDlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

   // Implementation
protected:

   // Generated message map functions
   //{{AFX_MSG(CPauseDlg)
   afx_msg void OnHelp();
   virtual BOOL OnInitDialog();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
// CDisplayDlg dialog

class CDisplayDlg : public CDialog
{
   // Construction
public:
   CDisplayDlg(CWnd* pParent = NULL);   // standard constructor

   CBitmapButton m_bmBtn;

   // Dialog Data
   //{{AFX_DATA(CDisplayDlg)
   enum { IDD = IDD_PROP_DISPLAY };
   // NOTE: the ClassWizard will add data members here
   //}}AFX_DATA


   // Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(CDisplayDlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

   // Implementation
protected:

   // Generated message map functions
   //{{AFX_MSG(CDisplayDlg)
   afx_msg void OnHelp();
   virtual BOOL OnInitDialog();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
// CGroundDlg dialog

class CGroundDlg : public CDialog
{
   // Construction
public:
   CGroundDlg(CWnd* pParent = NULL);   // standard constructor

   CBitmapButton m_bmBtn;

   // Dialog Data
   //{{AFX_DATA(CGroundDlg)
   enum { IDD = IDD_PROP_GROUND };
   // NOTE: the ClassWizard will add data members here
   //}}AFX_DATA


   // Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(CGroundDlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

   // Implementation
protected:

   // Generated message map functions
   //{{AFX_MSG(CGroundDlg)
   afx_msg void OnHelp();
   virtual BOOL OnInitDialog();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
// CKeypadDlg dialog

class CKeypadDlg : public CDialog
{
   // Construction
public:
   CKeypadDlg(CWnd* pParent = NULL);   // standard constructor

   CBitmapButton m_bmBtn;

   // Dialog Data
   //{{AFX_DATA(CKeypadDlg)
   enum { IDD = IDD_PROP_KEYPAD };
   // NOTE: the ClassWizard will add data members here
   //}}AFX_DATA


   // Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(CKeypadDlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

   // Implementation
protected:

   // Generated message map functions
   //{{AFX_MSG(CKeypadDlg)
   afx_msg void OnHelp();
   virtual BOOL OnInitDialog();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
// CCounterDlg dialog

class CCounterDlg : public CDialog
{
   // Construction
public:
   CCounterDlg(CWnd* pParent = NULL);   // standard constructor
   void RecalcBM();

   CBitmapButton m_bmBtn;

   // Dialog Data
   //{{AFX_DATA(CCounterDlg)
   enum { IDD = IDD_PROP_COUNTER };
   UINT	m_iInit;
   int		m_iSize;
   //}}AFX_DATA


   // Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(CCounterDlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

   // Implementation
protected:

   // Generated message map functions
   //{{AFX_MSG(CCounterDlg)
   afx_msg void OnHelp();
   virtual BOOL OnInitDialog();
   afx_msg void OnCounter4bit();
   afx_msg void OnCounter8bit();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
// CPlusDlg dialog

class CPlusDlg : public CDialog
{
   // Construction
public:
   CPlusDlg(CWnd* pParent = NULL);   // standard constructor

   CBitmapButton m_bmBtn;

   // Dialog Data
   //{{AFX_DATA(CPlusDlg)
   enum { IDD = IDD_PROP_PLUS };
   // NOTE: the ClassWizard will add data members here
   //}}AFX_DATA


   // Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(CPlusDlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

   // Implementation
protected:

   // Generated message map functions
   //{{AFX_MSG(CPlusDlg)
   afx_msg void OnHelp();
   virtual BOOL OnInitDialog();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
// CAnalyzeDlg dialog

class CAnalyzeDlg : public CDialog
{
   // Construction
public:
   CAnalyzeDlg(CWnd* pParent = NULL);   // standard constructor

   // Dialog Data
   //{{AFX_DATA(CAnalyzeDlg)
   enum { IDD = IDD_PROP_ANALYZE };
   CString	m_csSignalName;
   int		m_iDummy;
   //}}AFX_DATA


   // Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(CAnalyzeDlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

   // Implementation
protected:

   // Generated message map functions
   //{{AFX_MSG(CAnalyzeDlg)
   // NOTE: the ClassWizard will add member functions here
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
public:
   afx_msg void OnBnClickedHelp();
};
/////////////////////////////////////////////////////////////////////////////
// CTapedriveDlg dialog

class CTapedriveDlg : public CDialog
{
   // Construction
public:
   CTapedriveDlg(CWnd* pParent = NULL);   // standard constructor

   CBitmapButton m_bmBtn;
   CString m_csPathName;

   // Dialog Data
   //{{AFX_DATA(CTapedriveDlg)
   enum { IDD = IDD_PROP_TAPEDRIVE };
   CButton	m_cbEdit;
   CButton	m_cbBrowse;
   int		m_iFormat;
   UINT	m_uCapacity;
   CString	m_csFileName;
   UINT	m_uStartPosition;
   //}}AFX_DATA


   // Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(CTapedriveDlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

   // Implementation
protected:

   // Generated message map functions
   //{{AFX_MSG(CTapedriveDlg)
   afx_msg void OnBrowse();
   afx_msg void OnEdit();
   afx_msg void OnHelp();
   virtual BOOL OnInitDialog();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
// CAboutMSDlg dialog

class CAboutMSDlg : public CDialog
{
   // Construction
public:
   CAboutMSDlg(CWnd* pParent = NULL);   // standard constructor

   // Dialog Data
   //{{AFX_DATA(CAboutMSDlg)
   enum { IDD = IDD_ABOUTMS };
   // NOTE: the ClassWizard will add data members here
   //}}AFX_DATA


   // Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(CAboutMSDlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

   // Implementation
protected:

   // Generated message map functions
   //{{AFX_MSG(CAboutMSDlg)
   // NOTE: the ClassWizard will add member functions here
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CAnalyzeDlg dialog

class CGotoPageDlg : public CDialog
{
   // Construction
public:
   CGotoPageDlg(CWnd* pParent = NULL);   // standard constructor

   // Dialog Data
   //{{AFX_DATA(CGotoPageDlg)
   enum { IDD = IDD_GOTOPAGE };
   CEdit    m_cePageNumber;
   CEdit    m_cePageName;
   CListBox m_clPageList;
   int		m_iPageNumber;
   int      m_iPageCount;
   CStringArray *m_pPageNames;
   //}}AFX_DATA


   // Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(CGotoPageDlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

   // Implementation
protected:

   // Generated message map functions
   //{{AFX_MSG(CGotoPageDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnPageNumberChanged();
   afx_msg void OnPageNameChanged();
   afx_msg void OnPageSelect();
   afx_msg void OnPageDoubleClick();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
};
