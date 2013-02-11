// dialog.cpp : implementation file
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
// CRectDlg dialog

CRectDlg::CRectDlg(CWnd* pParent /*=NULL*/)
: CDialog(CRectDlg::IDD, pParent)
{
   //{{AFX_DATA_INIT(CRectDlg)
   m_bNoFill = FALSE;
   m_penSize = 0;
   //}}AFX_DATA_INIT
}

void CRectDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(CRectDlg)
   DDX_Check(pDX, IDC_NOFILL, m_bNoFill);
   DDX_Text(pDX, IDC_WEIGHT, m_penSize);
   DDV_MinMaxUInt(pDX, m_penSize, 0, 32767);
   //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CRectDlg, CDialog)
   //{{AFX_MSG_MAP(CRectDlg)
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRectDlg message handlers
/////////////////////////////////////////////////////////////////////////////
// CAndDlg dialog


CAndDlg::CAndDlg(CWnd* pParent /*=NULL*/)
: CDialog(CAndDlg::IDD, pParent)
{
   //{{AFX_DATA_INIT(CAndDlg)
   m_bDemorgan = FALSE;
   m_iInputs = -1;
   //}}AFX_DATA_INIT
}

void CAndDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(CAndDlg)
   DDX_Check(pDX, IDC_AND_DEMORGAN, m_bDemorgan);
   DDX_Radio(pDX, IDC_AND_2INPUTS, m_iInputs);
   //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAndDlg, CDialog)
   //{{AFX_MSG_MAP(CAndDlg)
   ON_BN_CLICKED(IDC_AND_2INPUTS, OnAnd2inputs)
   ON_BN_CLICKED(IDC_AND_3INPUTS, OnAnd3inputs)
   ON_BN_CLICKED(IDC_AND_4INPUTS, OnAnd4inputs)
   ON_BN_CLICKED(IDC_AND_DEMORGAN, OnAndDemorgan)
   ON_BN_CLICKED(ID_HELP, OnHelp)
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CAndDlg message handlers
/////////////////////////////////////////////////////////////////////////////
// CBuzzerDlg dialog


CBuzzerDlg::CBuzzerDlg(CWnd* pParent /*=NULL*/)
: CDialog(CBuzzerDlg::IDD, pParent)
{
   //{{AFX_DATA_INIT(CBuzzerDlg)
   m_iFreq = 0;
   m_iDuration = 0;
   //}}AFX_DATA_INIT
}

void CBuzzerDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(CBuzzerDlg)
   DDX_Text(pDX, IDC_BUZZER_FREQ, m_iFreq);
   DDX_Text(pDX, IDC_BUZZER_DURATION, m_iDuration);
   //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CBuzzerDlg, CDialog)
   //{{AFX_MSG_MAP(CBuzzerDlg)
   ON_BN_CLICKED(IDC_BUZZER_TEST, OnBuzzerTest)
   ON_BN_CLICKED(ID_HELP, OnHelp)
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CBuzzerDlg message handlers
/////////////////////////////////////////////////////////////////////////////
// CLedDlg dialog


CLedDlg::CLedDlg(CWnd* pParent /*=NULL*/)
: CDialog(CLedDlg::IDD, pParent)
{
   //{{AFX_DATA_INIT(CLedDlg)
   m_iRed = -1;
   m_iBlink = -1;
   //}}AFX_DATA_INIT
}

void CLedDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(CLedDlg)
   DDX_Radio(pDX, IDC_LED_RED, m_iRed);
   DDX_Radio(pDX, IDC_LED_BLINK, m_iBlink);
   //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CLedDlg, CDialog)
   //{{AFX_MSG_MAP(CLedDlg)
   ON_BN_CLICKED(IDC_LED_GREEN, OnLedGreen)
   ON_BN_CLICKED(IDC_LED_RED, OnLedRed)
   ON_BN_CLICKED(IDC_LED_YELLOW, OnLedYellow)
   ON_BN_CLICKED(ID_HELP, OnHelp)
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CLedDlg message handlers
/////////////////////////////////////////////////////////////////////////////
// COrDlg dialog


COrDlg::COrDlg(CWnd* pParent /*=NULL*/)
: CDialog(COrDlg::IDD, pParent)
{
   //{{AFX_DATA_INIT(COrDlg)
   m_iInputs = -1;
   m_bDemorgan = FALSE;
   //}}AFX_DATA_INIT
}

void COrDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(COrDlg)
   DDX_Radio(pDX, IDC_OR_2INPUTS, m_iInputs);
   DDX_Check(pDX, IDC_OR_DEMORGAN, m_bDemorgan);
   //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(COrDlg, CDialog)
   //{{AFX_MSG_MAP(COrDlg)
   ON_BN_CLICKED(IDC_OR_2INPUTS, OnOr2inputs)
   ON_BN_CLICKED(IDC_OR_3INPUTS, OnOr3inputs)
   ON_BN_CLICKED(IDC_OR_4INPUTS, OnOr4inputs)
   ON_BN_CLICKED(IDC_OR_DEMORGAN, OnOrDemorgan)
   ON_BN_CLICKED(ID_HELP, OnHelp)
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// COrDlg message handlers
/////////////////////////////////////////////////////////////////////////////
// COscillatorDlg dialog


COscillatorDlg::COscillatorDlg(CWnd* pParent /*=NULL*/)
: CDialog(COscillatorDlg::IDD, pParent)
{
   //{{AFX_DATA_INIT(COscillatorDlg)
   m_iOscillatorHi = 0;
   m_iOscillatorLo = 0;
   m_bOscillatorStartLo = FALSE;
   //}}AFX_DATA_INIT
}

void COscillatorDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(COscillatorDlg)
   DDX_Text(pDX, IDC_OSCILLATOR_HI, m_iOscillatorHi);
   DDX_Text(pDX, IDC_OSCILLATOR_LO, m_iOscillatorLo);
   DDX_Check(pDX, IDC_OSCILLATOR_STARTLO, m_bOscillatorStartLo);
   //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(COscillatorDlg, CDialog)
   //{{AFX_MSG_MAP(COscillatorDlg)
   ON_BN_CLICKED(ID_HELP, OnHelp)
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// COscillatorDlg message handlers
/////////////////////////////////////////////////////////////////////////////
// CSwitchDlg dialog


CSwitchDlg::CSwitchDlg(CWnd* pParent /*=NULL*/)
: CDialog(CSwitchDlg::IDD, pParent)
{
   //{{AFX_DATA_INIT(CSwitchDlg)
   m_iOn = -1;
   m_iToggle = -1;
   //}}AFX_DATA_INIT
}

void CSwitchDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(CSwitchDlg)
   DDX_Radio(pDX, IDC_SWITCH_ON, m_iOn);
   DDX_Radio(pDX, IDC_SWITCH_TOGGLE, m_iToggle);
   //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSwitchDlg, CDialog)
   //{{AFX_MSG_MAP(CSwitchDlg)
   ON_BN_CLICKED(IDC_SWITCH_OFF, OnSwitchOff)
   ON_BN_CLICKED(IDC_SWITCH_ON, OnSwitchOn)
   ON_BN_CLICKED(IDC_SWITCH_MOMENTARY, OnSwitchMomentary)
   ON_BN_CLICKED(IDC_SWITCH_TOGGLE, OnSwitchToggle)
   ON_BN_CLICKED(ID_HELP, OnHelp)
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CSwitchDlg message handlers

/////////////////////////////////////////////////////////////////////////////
// CLed7Dlg dialog

CLed7Dlg::CLed7Dlg(CWnd* pParent /*=NULL*/)
: CDialog(CLed7Dlg::IDD, pParent)
{
   //{{AFX_DATA_INIT(CLed7Dlg)
   m_iInputs = -1;
   m_iRed = -1;
   //}}AFX_DATA_INIT
}

void CLed7Dlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(CLed7Dlg)
   DDX_Radio(pDX, IDC_LED7_7INPUTS, m_iInputs);
   DDX_Radio(pDX, IDC_LED7_RED, m_iRed);
   //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CLed7Dlg, CDialog)
   //{{AFX_MSG_MAP(CLed7Dlg)
   ON_BN_CLICKED(IDC_LED7_4INPUTS, OnLed74inputs)
   ON_BN_CLICKED(IDC_LED7_7INPUTS, OnLed77inputs)
   ON_BN_CLICKED(ID_HELP, OnHelp)
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CLed7Dlg message handlers
/////////////////////////////////////////////////////////////////////////////
// CWireDlg dialog


CWireDlg::CWireDlg(CWnd* pParent /*=NULL*/)
: CDialog(CWireDlg::IDD, pParent)
{
   //{{AFX_DATA_INIT(CWireDlg)
   m_iRoute = -1;
   m_bHide = FALSE;
   //}}AFX_DATA_INIT
}

void CWireDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(CWireDlg)
   DDX_Radio(pDX, IDC_WIRE_UPPERLEFT, m_iRoute);
   DDX_Check(pDX, IDC_WIRE_HIDE, m_bHide);
   //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CWireDlg, CDialog)
   //{{AFX_MSG_MAP(CWireDlg)
   ON_BN_CLICKED(ID_HELP, OnHelp)
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CWireDlg message handlers
/////////////////////////////////////////////////////////////////////////////
// CInvertDlg dialog


CInvertDlg::CInvertDlg(CWnd* pParent /*=NULL*/)
: CDialog(CInvertDlg::IDD, pParent)
{
   //{{AFX_DATA_INIT(CInvertDlg)
   m_bDemorgan = FALSE;
   //}}AFX_DATA_INIT
}

void CInvertDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(CInvertDlg)
   DDX_Check(pDX, IDC_INVERT_DEMORGAN, m_bDemorgan);
   //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CInvertDlg, CDialog)
   //{{AFX_MSG_MAP(CInvertDlg)
   ON_BN_CLICKED(IDC_INVERT_DEMORGAN, OnInvertDemorgan)
   ON_BN_CLICKED(ID_HELP, OnHelp)
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CInvertDlg message handlers
/////////////////////////////////////////////////////////////////////////////
// CSetupDlg dialog


CSetupDlg::CSetupDlg(CWnd* pParent /*=NULL*/)
: CDialog(CSetupDlg::IDD, pParent)
{
   //{{AFX_DATA_INIT(CSetupDlg)
   m_iUnconnected = -1;
   m_iSimRateType = -1;
   m_iSimRate = 0;
   //}}AFX_DATA_INIT
}

void CSetupDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(CSetupDlg)
   DDX_Control(pDX, IDC_SETUP_SIMRATE, m_ceSimRate);
   DDX_Radio(pDX, IDC_SETUP_UNKNOWN, m_iUnconnected);
   DDX_Radio(pDX, IDC_SETUP_MAXSPEED, m_iSimRateType);
   DDX_Text(pDX, IDC_SETUP_SIMRATE, m_iSimRate);
   //}}AFX_DATA_MAP
   if (m_iSimRateType == 1) // sim rate specified
   {
      // SimRate has microsecond resolution,
      // so the maximum theoretical rate supported
      // by the implementation is 1000000 Hz.
      DDV_MinMaxInt(pDX, m_iSimRate, 1, 1000000);
   }
}

BEGIN_MESSAGE_MAP(CSetupDlg, CDialog)
   //{{AFX_MSG_MAP(CSetupDlg)
   ON_BN_CLICKED(IDC_SIMULATE_HELP, OnSimulateHelp)
   ON_BN_CLICKED(IDC_SETUP_MAXSPEED, OnSimulateSpeedUpdate)
   ON_BN_CLICKED(IDC_SETUP_SPECIFYRATE, OnSimulateSpeedUpdate)
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()
int MUST_FIX_ABOVE;

/////////////////////////////////////////////////////////////////////////////
// CSetupDlg message handlers
/////////////////////////////////////////////////////////////////////////////

void CSetupDlg::OnSimulateSpeedUpdate()
{
   UpdateData();
   m_ceSimRate.EnableWindow(m_iSimRateType == 1);
}

// CIoinDlg dialog


CIoinDlg::CIoinDlg(CWnd* pParent /*=NULL*/)
: CDialog(CIoinDlg::IDD, pParent)
{
   //{{AFX_DATA_INIT(CIoinDlg)
   m_iAddress = 0;
   m_iInitial = 0;
   //}}AFX_DATA_INIT
}

void CIoinDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(CIoinDlg)
   DDX_Text(pDX, IDC_IO_IN_ADDRESS, m_iAddress);
   DDV_MinMaxUInt(pDX, m_iAddress, 0, 65535);
   DDX_Text(pDX, IDC_IO_IN_INITIAL, m_iInitial);
   DDV_MinMaxUInt(pDX, m_iInitial, 0, 255);
   //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CIoinDlg, CDialog)
   //{{AFX_MSG_MAP(CIoinDlg)
   ON_BN_CLICKED(ID_HELP, OnHelp)
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CIoinDlg message handlers
/////////////////////////////////////////////////////////////////////////////
// CIooutDlg dialog


CIooutDlg::CIooutDlg(CWnd* pParent /*=NULL*/)
: CDialog(CIooutDlg::IDD, pParent)
{
   //{{AFX_DATA_INIT(CIooutDlg)
   m_iAddress = 0;
   m_iInitial = 0;
   //}}AFX_DATA_INIT
}

void CIooutDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(CIooutDlg)
   DDX_Text(pDX, IDC_IO_OUT_ADDRESS, m_iAddress);
   DDV_MinMaxUInt(pDX, m_iAddress, 0, 65535);
   DDX_Text(pDX, IDC_IO_OUT_INITIAL, m_iInitial);
   DDV_MinMaxUInt(pDX, m_iInitial, 0, 255);
   //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CIooutDlg, CDialog)
   //{{AFX_MSG_MAP(CIooutDlg)
   ON_BN_CLICKED(ID_HELP, OnHelp)
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CIooutDlg message handlers
/////////////////////////////////////////////////////////////////////////////
// CNoneDlg dialog


CNoneDlg::CNoneDlg(CWnd* pParent /*=NULL*/)
: CDialog(CNoneDlg::IDD, pParent)
{
   //{{AFX_DATA_INIT(CNoneDlg)
   // NOTE: the ClassWizard will add member initialization here
   //}}AFX_DATA_INIT
}

void CNoneDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(CNoneDlg)
   // NOTE: the ClassWizard will add DDX and DDV calls here
   //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CNoneDlg, CDialog)
   //{{AFX_MSG_MAP(CNoneDlg)
   ON_BN_CLICKED(ID_HELP, OnHelp)
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CNoneDlg message handlers
/////////////////////////////////////////////////////////////////////////////
// CSoundDlg dialog


CSoundDlg::CSoundDlg(CWnd* pParent /*=NULL*/)
: CDialog(CSoundDlg::IDD, pParent)
{
   //{{AFX_DATA_INIT(CSoundDlg)
   m_csFileName = "";
   m_bWait = FALSE;
   //}}AFX_DATA_INIT
}

void CSoundDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(CSoundDlg)
   DDX_Control(pDX, ID_EDIT, m_cbEdit);
   DDX_Control(pDX, ID_BROWSE, m_cbBrowse);
   DDX_Text(pDX, IDC_SOUND_COMMANDS, m_csFileName);
   DDX_Check(pDX, IDC_SOUND_WAIT, m_bWait);
   //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSoundDlg, CDialog)
   //{{AFX_MSG_MAP(CSoundDlg)
   ON_BN_CLICKED(ID_BROWSE, OnBrowse)
   ON_BN_CLICKED(ID_HELP, OnHelp)
   ON_BN_CLICKED(ID_EDIT, OnEdit)
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CSoundDlg message handlers
/////////////////////////////////////////////////////////////////////////////
// CFileinDlg dialog


CFileinDlg::CFileinDlg(CWnd* pParent /*=NULL*/)
: CDialog(CFileinDlg::IDD, pParent)
{
   //{{AFX_DATA_INIT(CFileinDlg)
   m_csFileName = "";
   m_iFormat = -1;
   //}}AFX_DATA_INIT
}

void CFileinDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(CFileinDlg)
   DDX_Text(pDX, IDC_FILEIN_FILENAME, m_csFileName);
   DDX_Radio(pDX, IDC_FILEIN_BINARY, m_iFormat);
   //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFileinDlg, CDialog)
   //{{AFX_MSG_MAP(CFileinDlg)
   ON_BN_CLICKED(ID_BROWSE, OnBrowse)
   ON_BN_CLICKED(ID_HELP, OnHelp)
   ON_BN_CLICKED(ID_EDIT, OnEdit)
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CFileinDlg message handlers
/////////////////////////////////////////////////////////////////////////////
// CFileoutDlg dialog


CFileoutDlg::CFileoutDlg(CWnd* pParent /*=NULL*/)
: CDialog(CFileoutDlg::IDD, pParent)
{
   //{{AFX_DATA_INIT(CFileoutDlg)
   m_csFileName = "";
   m_iFormat = -1;
   //}}AFX_DATA_INIT
}

void CFileoutDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(CFileoutDlg)
   DDX_Text(pDX, IDC_FILEOUT_FILENAME, m_csFileName);
   DDX_Radio(pDX, IDC_FILEOUT_BINARY, m_iFormat);
   //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFileoutDlg, CDialog)
   //{{AFX_MSG_MAP(CFileoutDlg)
   ON_BN_CLICKED(ID_BROWSE, OnBrowse)
   ON_BN_CLICKED(ID_HELP, OnHelp)
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CFileoutDlg message handlers

void CFileoutDlg::OnBrowse()
{
   UpdateData();

   CString csFullPath;

   char szFilter[] = "Text Files (*.TXT)|*.TXT|All Files (*.*)|*.*||";

   RelativeToFullPath(m_csFileName, m_csPathName, csFullPath);

   CFileDialog cfBrowse(TRUE, "TXT", csFullPath, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter);

   if (cfBrowse.DoModal() == IDOK)
   {
      m_csFileName = cfBrowse.GetPathName();
      UpdateData(FALSE);
   }

}

void CSoundDlg::OnBrowse()
{
   UpdateData();

   CString csFullPath;

   char szFilter[] = "Sound Wave Files (*.WAV)|*.WAV||";

   RelativeToFullPath(m_csFileName, m_csPathName, csFullPath);

   CFileDialog cfBrowse(TRUE, "WAV", csFullPath, /* OFN_FILEMUSTEXIST | */ OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter);

   if (cfBrowse.DoModal() == IDOK)
   {
      m_csFileName = cfBrowse.GetPathName();
      UpdateData(FALSE);
   }

}

void CAndDlg::RecalcBM()
{
   UpdateData();

   if (m_bDemorgan)
   {
      switch (m_iInputs)
      {
      case 0: m_bmBtn.LoadBitmaps(IDB_NAND2B); break;
      case 1: m_bmBtn.LoadBitmaps(IDB_NAND3B); break;
      case 2: m_bmBtn.LoadBitmaps(IDB_NAND4B); break;
      }
   }
   else
   {
      switch (m_iInputs)
      {
      case 0: m_bmBtn.LoadBitmaps(IDB_AND2B); break;
      case 1: m_bmBtn.LoadBitmaps(IDB_AND3B); break;
      case 2: m_bmBtn.LoadBitmaps(IDB_AND4B); break;
      }
   }
}

void CAndDlg::OnAnd2inputs()
{
   RecalcBM();
   m_bmBtn.Invalidate();
}

void CAndDlg::OnAnd3inputs()
{
   RecalcBM();
   m_bmBtn.Invalidate();
}

void CAndDlg::OnAnd4inputs()
{
   RecalcBM();
   m_bmBtn.Invalidate();
}

void CAndDlg::OnAndDemorgan()
{
   RecalcBM();
   m_bmBtn.Invalidate();
}

BOOL CAndDlg::OnInitDialog()
{
   CDialog::OnInitDialog();

   m_bmBtn.SubclassDlgItem(IDC_AND_BMBTN, this);
   RecalcBM();

   return TRUE;  // return TRUE  unless you set the focus to a control
}

BOOL CBuzzerDlg::OnInitDialog()
{
   CDialog::OnInitDialog();

   m_bmBtn.SubclassDlgItem(IDC_BUZZER_BMBTN, this);
   m_bmBtn.LoadBitmaps(IDB_BUZZER_OFFB);

   return TRUE;  // return TRUE  unless you set the focus to a control
}

BOOL CFileinDlg::OnInitDialog()
{
   CDialog::OnInitDialog();

   m_bmBtn.SubclassDlgItem(IDC_FILEIN_BMBTN, this);
   m_bmBtn.LoadBitmaps(IDB_FILE_INB);

   return TRUE;  // return TRUE  unless you set the focus to a control
}

BOOL CFileoutDlg::OnInitDialog()
{
   CDialog::OnInitDialog();

   m_bmBtn.SubclassDlgItem(IDC_FILEOUT_BMBTN, this);
   m_bmBtn.LoadBitmaps(IDB_FILE_OUTB);

   return TRUE;  // return TRUE  unless you set the focus to a control
}

void CInvertDlg::RecalcBM()
{
   UpdateData();

   if (m_bDemorgan)
   {
      m_bmBtn.LoadBitmaps(IDB_BUFFERB);
   }
   else
   {
      m_bmBtn.LoadBitmaps(IDB_INVERTB);
   }

}

BOOL CInvertDlg::OnInitDialog()
{
   CDialog::OnInitDialog();

   m_bmBtn.SubclassDlgItem(IDC_INVERT_BMBTN, this);
   RecalcBM();

   return TRUE;  // return TRUE  unless you set the focus to a control
}

BOOL CIoinDlg::OnInitDialog()
{
   CDialog::OnInitDialog();

   m_bmBtn.SubclassDlgItem(IDC_IOIN_BMBTN, this);
   m_bmBtn.LoadBitmaps(IDB_IO_INB);

   return TRUE;  // return TRUE  unless you set the focus to a control
}

BOOL CIooutDlg::OnInitDialog()
{
   CDialog::OnInitDialog();

   m_bmBtn.SubclassDlgItem(IDC_IOOUT_BMBTN, this);
   m_bmBtn.LoadBitmaps(IDB_IO_OUTB);

   return TRUE;  // return TRUE  unless you set the focus to a control
}

void CLed7Dlg::RecalcBM()
{
   UpdateData();

   switch (m_iInputs)
   {
   case 0: m_bmBtn.LoadBitmaps(IDB_LED7_OFFB); break;
   case 1: m_bmBtn.LoadBitmaps(IDB_LED4_OFFB); break;
   }

}

BOOL CLed7Dlg::OnInitDialog()
{
   CDialog::OnInitDialog();

   m_bmBtn.SubclassDlgItem(IDC_LED7_BMBTN, this);
   RecalcBM();

   return TRUE;  // return TRUE  unless you set the focus to a control
}

void CLedDlg::RecalcBM()
{
   UpdateData();

   switch (m_iRed)
   {
   case 0: m_bmBtn.LoadBitmaps(IDB_LED_ONRB); break;
   case 1: m_bmBtn.LoadBitmaps(IDB_LED_ONGB); break;
   case 2: m_bmBtn.LoadBitmaps(IDB_LED_ONYB); break;
   }

}

BOOL CLedDlg::OnInitDialog()
{
   CDialog::OnInitDialog();

   m_bmBtn.SubclassDlgItem(IDC_LED_BMBTN, this);
   RecalcBM();

   return TRUE;  // return TRUE  unless you set the focus to a control
}

BOOL CNoneDlg::OnInitDialog()
{
   CDialog::OnInitDialog();

   return TRUE;  // return TRUE  unless you set the focus to a control
}

void COrDlg::RecalcBM()
{
   UpdateData();

   if (m_bDemorgan)
   {
      switch (m_iInputs)
      {
      case 0: m_bmBtn.LoadBitmaps(IDB_NOR2B); break;
      case 1: m_bmBtn.LoadBitmaps(IDB_NOR3B); break;
      case 2: m_bmBtn.LoadBitmaps(IDB_NOR4B); break;
      }
   }
   else
   {
      switch (m_iInputs)
      {
      case 0: m_bmBtn.LoadBitmaps(IDB_OR2B); break;
      case 1: m_bmBtn.LoadBitmaps(IDB_OR3B); break;
      case 2: m_bmBtn.LoadBitmaps(IDB_OR4B); break;
      }
   }

}

BOOL COrDlg::OnInitDialog()
{
   CDialog::OnInitDialog();

   m_bmBtn.SubclassDlgItem(IDC_OR_BMBTN, this);
   RecalcBM();

   return TRUE;  // return TRUE  unless you set the focus to a control
}

BOOL COscillatorDlg::OnInitDialog()
{
   CDialog::OnInitDialog();

   m_bmBtn.SubclassDlgItem(IDC_OSCILLATOR_BMBTN, this);
   m_bmBtn.LoadBitmaps(IDB_OSCILLATORB);

   return TRUE;  // return TRUE  unless you set the focus to a control
}

BOOL CRectDlg::OnInitDialog()
{
   CDialog::OnInitDialog();

   return TRUE;  // return TRUE  unless you set the focus to a control
}

BOOL CSetupDlg::OnInitDialog()
{
   CDialog::OnInitDialog();
   OnSimulateSpeedUpdate(); // disable sim rate text box as needed

   // TODO: Add extra initialization here

   return TRUE;  // return TRUE  unless you set the focus to a control
}

BOOL CSoundDlg::OnInitDialog()
{
   CDialog::OnInitDialog();

   m_bmBtn.SubclassDlgItem(IDC_SOUND_BMBTN, this);
   m_bmBtn.LoadBitmaps(IDB_WAVB);

   return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSwitchDlg::RecalcBM()
{
   UpdateData();

   switch (m_iToggle)
   {
   case 0:
      {
         switch (m_iOn)
         {
         case 0: m_bmBtn.LoadBitmaps(IDB_SWITCH_ONB); break;
         case 1: m_bmBtn.LoadBitmaps(IDB_SWITCH_OFFB); break;
         }
         break;
      }
   case 1:
      {
         switch (m_iOn)
         {
         case 0: m_bmBtn.LoadBitmaps(IDB_SWITCHM_ONB); break;
         case 1: m_bmBtn.LoadBitmaps(IDB_SWITCHM_OFFB); break;
         }
         break;
      }
   }
}

BOOL CSwitchDlg::OnInitDialog()
{
   CDialog::OnInitDialog();

   m_bmBtn.SubclassDlgItem(IDC_SWITCH_BMBTN, this);
   RecalcBM();

   return TRUE;  // return TRUE  unless you set the focus to a control
}

BOOL CWireDlg::OnInitDialog()
{
   CDialog::OnInitDialog();

   m_bmBtn.SubclassDlgItem(IDC_WIRE_BMBTN, this);
   m_bmBtn.LoadBitmaps(IDB_WIREB);

   return TRUE;  // return TRUE  unless you set the focus to a control
}

/////////////////////////////////////////////////////////////////////////////
// CBitmapDlg dialog

CBitmapDlg::CBitmapDlg(CWnd* pParent /*=NULL*/)
: CDialog(CBitmapDlg::IDD, pParent)
{
   //{{AFX_DATA_INIT(CBitmapDlg)
   m_csFileName = _T("");
   m_iStyle = -1;
   m_bPlayground = FALSE;
   //}}AFX_DATA_INIT
}


void CBitmapDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(CBitmapDlg)
   DDX_Control(pDX, IDC_CHECK_PLAYGROUND, m_cbPlayground);
   DDX_Control(pDX, IDC_BMP_FILENAME, m_ceFileName);
   DDX_Control(pDX, ID_EDIT, m_cbEdit);
   DDX_Control(pDX, ID_BROWSE, m_cbBrowse);
   DDX_Text(pDX, IDC_BMP_FILENAME, m_csFileName);
   DDX_Radio(pDX, IDC_BMP_SINGLE, m_iStyle);
   DDX_Check(pDX, IDC_CHECK_PLAYGROUND, m_bPlayground);
   //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBitmapDlg, CDialog)
   //{{AFX_MSG_MAP(CBitmapDlg)
   ON_BN_CLICKED(ID_BROWSE, OnBrowse)
   ON_BN_CLICKED(ID_HELP, OnHelp)
   ON_BN_CLICKED(IDC_BMP_SINGLE, OnBmpSingle)
   ON_BN_CLICKED(IDC_BMP_MULTIPLE, OnBmpMultiple)
   ON_BN_CLICKED(ID_EDIT, OnEdit)
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBitmapDlg message handlers

BOOL CBitmapDlg::OnInitDialog()
{
   CDialog::OnInitDialog();

   m_bmBtn.SubclassDlgItem(IDC_BMP_BMBTN, this);
   RecalcBM();

   return TRUE;  // return TRUE unless you set the focus to a control
   // EXCEPTION: OCX Property Pages should return FALSE
}
/////////////////////////////////////////////////////////////////////////////
// CMemoryDlg dialog


CMemoryDlg::CMemoryDlg(CWnd* pParent /*=NULL*/)
: CDialog(CMemoryDlg::IDD, pParent)
{
   //{{AFX_DATA_INIT(CMemoryDlg)
   m_iBinaryMode= -1;
   m_iAddressMode = -1;
   m_csFileName = _T("");
   //}}AFX_DATA_INIT
}


void CMemoryDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(CMemoryDlg)
   DDX_Control(pDX, ID_EDIT, m_cbEdit);
   DDX_Control(pDX, ID_BROWSE, m_cbBrowse);
   DDX_Radio(pDX, IDC_MEMORY_BINARY, m_iBinaryMode);
   DDX_Radio(pDX, IDC_MEMORY_8BITS, m_iAddressMode);
   DDX_Text(pDX, IDC_MEMORY_FILENAME, m_csFileName);
   //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMemoryDlg, CDialog)
   //{{AFX_MSG_MAP(CMemoryDlg)
   ON_BN_CLICKED(IDC_MEMORY_8BITS, OnMem8Bits)
   ON_BN_CLICKED(IDC_MEMORY_16BITS, OnMem16Bits)
   ON_BN_CLICKED(ID_BROWSE, OnBrowse)
   ON_BN_CLICKED(ID_HELP, OnHelp)
   ON_BN_CLICKED(ID_EDIT, OnEdit)
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMemoryDlg message handlers

void CMemoryDlg::RecalcBM()
{
   UpdateData();

   switch (m_iAddressMode)
   {
   case 0: m_bmBtn.LoadBitmaps(IDB_MEMORYB); break;
   case 1: m_bmBtn.LoadBitmaps(IDB_MEMORY16B); break;
   }

}

BOOL CMemoryDlg::OnInitDialog()
{
   CDialog::OnInitDialog();
   m_bmBtn.SubclassDlgItem(IDC_MEMORY_BMBTN, this);
   m_bmBtn.LoadBitmaps(IDB_MEMORYB);
   RecalcBM();

   return TRUE;  // return TRUE unless you set the focus to a control
   // EXCEPTION: OCX Property Pages should return FALSE
}

void CMemoryDlg::OnMem8Bits()
{
   RecalcBM();
   m_bmBtn.Invalidate();
}

void CMemoryDlg::OnMem16Bits()
{
   RecalcBM();
   m_bmBtn.Invalidate();
}

/////////////////////////////////////////////////////////////////////////////
// CTextDlg dialog


CTextDlg::CTextDlg(CWnd* pParent /*=NULL*/)
: CDialog(CTextDlg::IDD, pParent)
{
   //{{AFX_DATA_INIT(CTextDlg)
   m_pTextText = _T("");
   m_iStyle = -1;
   m_csFileName = _T("");
   //}}AFX_DATA_INIT
}


void CTextDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(CTextDlg)
   DDX_Control(pDX, ID_EDIT, m_cbEdit);
   DDX_Control(pDX, ID_BROWSE, m_cbBrowse);
   DDX_Control(pDX, IDC_TEXT_FILENAME, m_ceFileName);
   DDX_Text(pDX, IDC_TEXT_TEXT, m_pTextText);
   DDV_MaxChars(pDX, m_pTextText, 1000);
   DDX_Radio(pDX, IDC_TEXT_SINGLE, m_iStyle);
   DDX_Text(pDX, IDC_TEXT_FILENAME, m_csFileName);
   //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTextDlg, CDialog)
   //{{AFX_MSG_MAP(CTextDlg)
   ON_BN_CLICKED(ID_HELP, OnHelp)
   ON_BN_CLICKED(IDC_TEXT_MULTIPLE, OnTextMultiple)
   ON_BN_CLICKED(IDC_TEXT_SINGLE, OnTextSingle)
   ON_BN_CLICKED(ID_BROWSE, OnBrowse)
   ON_BN_CLICKED(ID_EDIT, OnEdit)
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTextDlg message handlers

void COrDlg::OnOr2inputs()
{
   RecalcBM();
   m_bmBtn.Invalidate();
}

void COrDlg::OnOr3inputs()
{
   RecalcBM();
   m_bmBtn.Invalidate();
}

void COrDlg::OnOr4inputs()
{
   RecalcBM();
   m_bmBtn.Invalidate();
}

void COrDlg::OnOrDemorgan()
{
   RecalcBM();
   m_bmBtn.Invalidate();
}

void CInvertDlg::OnInvertDemorgan()
{
   RecalcBM();
   m_bmBtn.Invalidate();
}

void CLed7Dlg::OnLed74inputs()
{
   RecalcBM();
   m_bmBtn.Invalidate();
}

void CLed7Dlg::OnLed77inputs()
{
   RecalcBM();
   m_bmBtn.Invalidate();
}

void CLedDlg::OnLedGreen()
{
   RecalcBM();
   m_bmBtn.Invalidate();
}

void CLedDlg::OnLedRed()
{
   RecalcBM();
   m_bmBtn.Invalidate();
}

void CLedDlg::OnLedYellow()
{
   RecalcBM();
   m_bmBtn.Invalidate();
}

void CSwitchDlg::OnSwitchOff()
{
   RecalcBM();
   m_bmBtn.Invalidate();
}

void CSwitchDlg::OnSwitchOn()
{
   RecalcBM();
   m_bmBtn.Invalidate();
}
/////////////////////////////////////////////////////////////////////////////
// CMuxDlg dialog


CMuxDlg::CMuxDlg(CWnd* pParent /*=NULL*/)
: CDialog(CMuxDlg::IDD, pParent)
{
   //{{AFX_DATA_INIT(CMuxDlg)
   m_bDeMux = FALSE;
   m_iStyle = -1;
   //}}AFX_DATA_INIT
}


void CMuxDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(CMuxDlg)
   DDX_Check(pDX, IDC_MUX_DEMUX, m_bDeMux);
   DDX_Radio(pDX, IDC_MUX_MUX8TO1, m_iStyle);
   //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMuxDlg, CDialog)
   //{{AFX_MSG_MAP(CMuxDlg)
   ON_BN_CLICKED(IDC_MUX_DEMUX, OnMuxDemux)
   ON_BN_CLICKED(ID_HELP, OnHelp)
   ON_BN_CLICKED(IDC_MUX_DEMUX1TO2, OnMuxDemux1to2)
   ON_BN_CLICKED(IDC_MUX_DEMUX2TO4, OnMuxDemux2to4)
   ON_BN_CLICKED(IDC_MUX_DEMUX3TO8, OnMuxDemux3to8)
   ON_BN_CLICKED(IDC_MUX_MUX2TO1, OnMuxMux2to1)
   ON_BN_CLICKED(IDC_MUX_MUX4TO1, OnMuxMux4to1)
   ON_BN_CLICKED(IDC_MUX_MUX8TO1, OnMuxMux8to1)
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMuxDlg message handlers

void CMuxDlg::OnMuxDemux()
{
   RecalcBM();
   m_bmBtn.Invalidate();
}

void CMuxDlg::RecalcBM()
{
   UpdateData();

   switch (m_iStyle)
   {
   case 0: m_bmBtn.LoadBitmaps(IDB_MUX_8TO1B); break;
   case 1: m_bmBtn.LoadBitmaps(IDB_MUX_4TO1B); break;
   case 2: m_bmBtn.LoadBitmaps(IDB_MUX_2TO1B); break;
   case 3: m_bmBtn.LoadBitmaps(IDB_DEMUX_3TO8B); break;
   case 4: m_bmBtn.LoadBitmaps(IDB_DEMUX_2TO4B); break;
   case 5: m_bmBtn.LoadBitmaps(IDB_DEMUX_1TO2B); break;
   }
}

void CBuzzerDlg::OnBuzzerTest()
{

   long frequency;

   OSVERSIONINFO VersionInformation;
   memset(&VersionInformation, 0, sizeof(OSVERSIONINFO));
   VersionInformation.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

   frequency = m_iFreq;

   GetVersionEx(&VersionInformation);
   if (VersionInformation.dwPlatformId == VER_PLATFORM_WIN32_NT)
   {
      Beep(frequency, m_iDuration);
   }
   else
   {
      MyBeep(frequency, m_iDuration);
   }
}

void CFileinDlg::OnBrowse()
{
   UpdateData();

   CString csFullPath;

   char szFilter[] = "Text Files (*.TXT)|*.TXT|All Files (*.*)|*.*||";

   RelativeToFullPath(m_csFileName, m_csPathName, csFullPath);

   CFileDialog cfBrowse(TRUE, "TXT", csFullPath, /* OFN_FILEMUSTEXIST | */ OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter);

   if (cfBrowse.DoModal() == IDOK)
   {
      m_csFileName = cfBrowse.GetPathName();
      UpdateData(FALSE);
   }

}

//TODO: Should we use m_iBinaryMode to dynamically set filter for drop down?
//I am leaning toward making dropdown be "Memory Files (*.TXT;*.BIN)" followed by option for "All Files (*.*)"
//We would then eliminate *.TXT and *.BIN as separate filter choices in the drop down.
//
//Is there any advantage to using the full path? Seems it would be better to use relative path.
//this would benefit when sending zipped MMLogic project that has WAV, BMP, TXT etc files so receiver 
//does not have to manually select file location since they most likely are using different directory structure.
void CMemoryDlg::OnBrowse()
{
   UpdateData();

   CString csFullPath;

   char szFilter[] = "Memory Files (*.TXT;*.BIN)|*.TXT;*.BIN|Text Files (*.TXT)|*.TXT|Binary Files (*.BIN)|*.BIN|All Files (*.*)|*.*||";

   RelativeToFullPath(m_csFileName, m_csPathName, csFullPath);

   CFileDialog cfBrowse(TRUE, "TXT", csFullPath, /* OFN_FILEMUSTEXIST | */ OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter);

   if (cfBrowse.DoModal() == IDOK)
   {
      m_csFileName = cfBrowse.GetPathName();
      UpdateData(FALSE);
   }

}

BOOL CMuxDlg::OnInitDialog()
{
   CDialog::OnInitDialog();

   m_bmBtn.SubclassDlgItem(IDC_MUX_BMBTN, this);
   RecalcBM();

   return TRUE;  // return TRUE  unless you set the focus to a control
}

void CBitmapDlg::RecalcBM()
{
   UpdateData();

   switch (m_iStyle)
   {
   case 0:
      {
         m_bmBtn.LoadBitmaps(IDB_BMPSB);
         m_cbPlayground.EnableWindow(TRUE);
         //         m_ceFileName.EnableWindow(FALSE);
         //         m_cbEdit.EnableWindow(FALSE);
         //         m_cbBrowse.EnableWindow(FALSE);
         break;
      }
   case 1:
      {
         m_bmBtn.LoadBitmaps(IDB_BMPB);
         m_cbPlayground.EnableWindow(FALSE);
         //         m_ceFileName.EnableWindow(TRUE);
         //         m_cbEdit.EnableWindow(TRUE);
         //         m_cbBrowse.EnableWindow(TRUE);
         break;
      }
   }
}

void CBitmapDlg::OnBrowse()
{
   UpdateData();

   if (m_iStyle == 1)
   {
      CString csFullPath;

      char szFilter[] = "Bitmap Files (*.BMP)|*.BMP||";

      RelativeToFullPath(m_csFileName, m_csPathName, csFullPath);

      CFileDialog cfBrowse(TRUE, "BMP", csFullPath, /* OFN_FILEMUSTEXIST | */ OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter);

      if (cfBrowse.DoModal() == IDOK)
      {
         m_csFileName = cfBrowse.GetPathName();
         UpdateData(FALSE);
         if (m_csFileName.Right(5).CompareNoCase("0.BMP") != 0)
         {
            MessageBox("File name must be in the form Name0.BMP","Error");
         }
      }
   }
   else
   {
      CFileDialog cfBrowse(TRUE,"BMP","*.BMP", OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT);

      if (cfBrowse.DoModal() == IDOK)
      {
         m_csFileName = cfBrowse.GetPathName();
         UpdateData(FALSE);
         if (m_csFileName.Right(4).CompareNoCase(".BMP") != 0)
         {
            MessageBox("File name must be in the form Name.BMP","Error");
         }
      }
   }
}

void CSwitchDlg::OnSwitchMomentary()
{
   RecalcBM();
   m_bmBtn.Invalidate();
}

void CSwitchDlg::OnSwitchToggle()
{
   RecalcBM();
   m_bmBtn.Invalidate();
}

void CAndDlg::OnHelp()
{
   ::HtmlHelp(NULL, "mmlogic.chm", HH_DISPLAY_TOPIC, (DWORD) "html\\and_gate.htm");
}

void CBitmapDlg::OnHelp()
{
   ::HtmlHelp(NULL, "mmlogic.chm", HH_DISPLAY_TOPIC, (DWORD) "html\\bitmap_device.htm");
}

void CBuzzerDlg::OnHelp()
{
   ::HtmlHelp(NULL, "mmlogic.chm", HH_DISPLAY_TOPIC, (DWORD) "html\\buzzer_device.htm");
}

void CFileinDlg::OnHelp()
{
   ::HtmlHelp(NULL, "mmlogic.chm", HH_DISPLAY_TOPIC, (DWORD) "html\\read_file.htm");
}

void CFileoutDlg::OnHelp()
{
   ::HtmlHelp(NULL, "mmlogic.chm", HH_DISPLAY_TOPIC, (DWORD) "html\\write_file_device.htm");
}

void CInvertDlg::OnHelp()
{
   ::HtmlHelp(NULL, "mmlogic.chm", HH_DISPLAY_TOPIC, (DWORD) "html\\inverter_gate.htm");
}

void CIoinDlg::OnHelp()
{
   ::HtmlHelp(NULL, "mmlogic.chm", HH_DISPLAY_TOPIC, (DWORD) "html\\port_in_device.htm");
}

void CIooutDlg::OnHelp()
{
   ::HtmlHelp(NULL, "mmlogic.chm", HH_DISPLAY_TOPIC, (DWORD) "html\\port_out_device.htm");
}

void CLedDlg::OnHelp()
{
   ::HtmlHelp(NULL, "mmlogic.chm", HH_DISPLAY_TOPIC, (DWORD) "html\\led_device.htm");
}

void CLed7Dlg::OnHelp()
{
   ::HtmlHelp(NULL, "mmlogic.chm", HH_DISPLAY_TOPIC, (DWORD) "html\\7_segment_led_device.htm");
}

void CMemoryDlg::OnHelp()
{
   ::HtmlHelp(NULL, "mmlogic.chm", HH_DISPLAY_TOPIC, (DWORD) "html\\memory_device.htm");
}

void CMuxDlg::OnHelp()
{
   ::HtmlHelp(NULL, "mmlogic.chm", HH_DISPLAY_TOPIC, (DWORD) "html\\multiplexer_device.htm");
}

void CNoneDlg::OnHelp()
{
   //In previous version that used WinHelp, this seems to be where
   //the help for the Analyze Tool was called. May not need this at all.
   MessageBox("Here we are in CNoneDlg::OnHelp in DIALOG.CPP","Error");
}

void COrDlg::OnHelp()
{
   ::HtmlHelp(NULL, "mmlogic.chm", HH_DISPLAY_TOPIC, (DWORD) "html\\or_gate.htm");
}

void COscillatorDlg::OnHelp()
{
   ::HtmlHelp(NULL, "mmlogic.chm", HH_DISPLAY_TOPIC, (DWORD) "html\\oscillator_device.htm");
}

void CSoundDlg::OnHelp()
{
   ::HtmlHelp(NULL, "mmlogic.chm", HH_DISPLAY_TOPIC, (DWORD) "html\\sound_wave_device.htm");
}

void CSwitchDlg::OnHelp()
{
   ::HtmlHelp(NULL, "mmlogic.chm", HH_DISPLAY_TOPIC, (DWORD) "html\\switch_device.htm");
}

void CTextDlg::OnHelp()
{
   ::HtmlHelp(NULL, "mmlogic.chm", HH_DISPLAY_TOPIC, (DWORD) "html\\text.htm");
}

void CWireDlg::OnHelp()
{
   ::HtmlHelp(NULL, "mmlogic.chm", HH_DISPLAY_TOPIC, (DWORD) "html\\wiring_tool.htm");
}

void CSetupDlg::OnSimulateHelp()
{
   ::HtmlHelp(NULL, "mmlogic.chm", HH_DISPLAY_TOPIC, (DWORD) "html\\simulation_setup.htm");
}
/////////////////////////////////////////////////////////////////////////////
// CRandomDlg dialog


CRandomDlg::CRandomDlg(CWnd* pParent /*=NULL*/)
: CDialog(CRandomDlg::IDD, pParent)
{
   //{{AFX_DATA_INIT(CRandomDlg)
   m_uSeed = 0;
   m_iSpare = 0;
   //}}AFX_DATA_INIT
}


void CRandomDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(CRandomDlg)
   DDX_Text(pDX, IDC_RANDOM_SEED, m_uSeed);
   DDX_Text(pDX, IDC_RANDOM_SPARE, m_iSpare);
   //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRandomDlg, CDialog)
   //{{AFX_MSG_MAP(CRandomDlg)
   ON_BN_CLICKED(ID_HELP, OnHelp)
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRandomDlg message handlers

BOOL CRandomDlg::OnInitDialog()
{
   CDialog::OnInitDialog();

   m_bmBtn.SubclassDlgItem(IDC_RANDOM_BMBTN, this);
   m_bmBtn.LoadBitmaps(IDB_RANDOMB);

   return TRUE;  // return TRUE unless you set the focus to a control
   // EXCEPTION: OCX Property Pages should return FALSE
}
/////////////////////////////////////////////////////////////////////////////
// CXorDlg dialog


CXorDlg::CXorDlg(CWnd* pParent /*=NULL*/)
: CDialog(CXorDlg::IDD, pParent)
{
   //{{AFX_DATA_INIT(CXorDlg)
   m_i2Inputs = -1;
   m_bDemorgan = FALSE;
   //}}AFX_DATA_INIT
}


void CXorDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(CXorDlg)
   DDX_Radio(pDX, IDC_XOR_2INPUTS, m_i2Inputs);
   DDX_Check(pDX, IDC_XOR_DEMORGAN, m_bDemorgan);
   //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CXorDlg, CDialog)
   //{{AFX_MSG_MAP(CXorDlg)
   ON_BN_CLICKED(ID_HELP, OnHelp)
   ON_BN_CLICKED(IDC_XOR_2INPUTS, OnXor2inputs)
   ON_BN_CLICKED(IDC_XOR_3INPUTS, OnXor3inputs)
   ON_BN_CLICKED(IDC_XOR_4INPUTS, OnXor4inputs)
   ON_BN_CLICKED(IDC_XOR_DEMORGAN, OnXorDemorgan)
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXorDlg message handlers

void CXorDlg::OnHelp()
{
   ::HtmlHelp(NULL, "mmlogic.chm", HH_DISPLAY_TOPIC, (DWORD) "html\\xor_gate.htm");
}

BOOL CXorDlg::OnInitDialog()
{
   CDialog::OnInitDialog();

   m_bmBtn.SubclassDlgItem(IDC_XOR_BMBTN, this);
   RecalcBM();

   return TRUE;  // return TRUE unless you set the focus to a control
   // EXCEPTION: OCX Property Pages should return FALSE
}

void CXorDlg::OnXor2inputs()
{
   RecalcBM();
   m_bmBtn.Invalidate();
}

void CXorDlg::OnXor3inputs()
{
   RecalcBM();
   m_bmBtn.Invalidate();
}

void CXorDlg::OnXor4inputs()
{
   RecalcBM();
   m_bmBtn.Invalidate();
}

void CXorDlg::OnXorDemorgan()
{
   RecalcBM();
   m_bmBtn.Invalidate();
}

void CXorDlg::RecalcBM()
{
   UpdateData();

   if (m_bDemorgan)
   {
      switch (m_i2Inputs)
      {
      case 0: m_bmBtn.LoadBitmaps(IDB_XNOR2B); break;
      case 1: m_bmBtn.LoadBitmaps(IDB_XNOR3B); break;
      case 2: m_bmBtn.LoadBitmaps(IDB_XNOR4B); break;
      }
   }
   else
   {
      switch (m_i2Inputs)
      {
      case 0: m_bmBtn.LoadBitmaps(IDB_XOR2B); break;
      case 1: m_bmBtn.LoadBitmaps(IDB_XOR3B); break;
      case 2: m_bmBtn.LoadBitmaps(IDB_XOR4B); break;
      }
   }

}

/////////////////////////////////////////////////////////////////////////////
// CClockDlg dialog


CClockDlg::CClockDlg(CWnd* pParent /*=NULL*/)
: CDialog(CClockDlg::IDD, pParent)
{
   //{{AFX_DATA_INIT(CClockDlg)
   m_iSeconds = -1;
   m_bSpare = FALSE;
   //}}AFX_DATA_INIT
}


void CClockDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(CClockDlg)
   DDX_Radio(pDX, IDC_CLOCK_SECONDS, m_iSeconds);
   DDX_Check(pDX, IDC_CLOCK_SPARE, m_bSpare);
   //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CClockDlg, CDialog)
   //{{AFX_MSG_MAP(CClockDlg)
   ON_BN_CLICKED(ID_HELP, OnHelp)
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClockDlg message handlers
/////////////////////////////////////////////////////////////////////////////
// CTimerDlg dialog


CTimerDlg::CTimerDlg(CWnd* pParent /*=NULL*/)
: CDialog(CTimerDlg::IDD, pParent)
{
   //{{AFX_DATA_INIT(CTimerDlg)
   m_uDelay = 0;
   m_bSpare = FALSE;
   //}}AFX_DATA_INIT
}


void CTimerDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(CTimerDlg)
   DDX_Text(pDX, IDC_DELAY, m_uDelay);
   DDX_Check(pDX, IDC_TIMER_SPARE, m_bSpare);
   //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTimerDlg, CDialog)
   //{{AFX_MSG_MAP(CTimerDlg)
   ON_BN_CLICKED(ID_HELP, OnHelp)
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTimerDlg message handlers

BOOL CClockDlg::OnInitDialog()
{
   CDialog::OnInitDialog();

   m_bmBtn.SubclassDlgItem(IDC_CLOCK_BMBTN, this);
   m_bmBtn.LoadBitmaps(IDB_CLOCKB);

   return TRUE;  // return TRUE unless you set the focus to a control
   // EXCEPTION: OCX Property Pages should return FALSE
}

void CClockDlg::OnHelp()
{
   ::HtmlHelp(NULL, "mmlogic.chm", HH_DISPLAY_TOPIC, (DWORD) "html\\clock_device.htm");
}

BOOL CTimerDlg::OnInitDialog()
{
   CDialog::OnInitDialog();

   m_bmBtn.SubclassDlgItem(IDC_TIMER_BMBTN, this);
   m_bmBtn.LoadBitmaps(IDB_TIMERB);

   return TRUE;  // return TRUE unless you set the focus to a control
   // EXCEPTION: OCX Property Pages should return FALSE
}

void CTimerDlg::OnHelp()
{
   ::HtmlHelp(NULL, "mmlogic.chm", HH_DISPLAY_TOPIC, (DWORD) "html\\timer_device.htm");
}
/////////////////////////////////////////////////////////////////////////////
// CSignalreceiverDlg dialog


CSignalreceiverDlg::CSignalreceiverDlg(CWnd* pParent /*=NULL*/)
: CDialog(CSignalreceiverDlg::IDD, pParent)
{
   //{{AFX_DATA_INIT(CSignalreceiverDlg)
   m_csSignalName = _T("");
   m_iDummy = -1;
   //}}AFX_DATA_INIT
}


void CSignalreceiverDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(CSignalreceiverDlg)
   DDX_Text(pDX, IDC_SIGNALRECEIVER_SIGNALNAME, m_csSignalName);
   DDX_Radio(pDX, IDC_SIGNALRECEIVER_DUMMY, m_iDummy);
   //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSignalreceiverDlg, CDialog)
   //{{AFX_MSG_MAP(CSignalreceiverDlg)
   ON_BN_CLICKED(ID_HELP, OnHelp)
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSignalreceiverDlg message handlers
/////////////////////////////////////////////////////////////////////////////
// CSignalsenderDlg dialog


CSignalsenderDlg::CSignalsenderDlg(CWnd* pParent /*=NULL*/)
: CDialog(CSignalsenderDlg::IDD, pParent)
{
   //{{AFX_DATA_INIT(CSignalsenderDlg)
   m_csSignalName = _T("");
   m_iDummy = -1;
   //}}AFX_DATA_INIT
}


void CSignalsenderDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(CSignalsenderDlg)
   DDX_Text(pDX, IDC_SIGNALSENDER_SIGNALNAME, m_csSignalName);
   DDX_Radio(pDX, IDC_SIGNALSENDER_DUMMY, m_iDummy);
   //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSignalsenderDlg, CDialog)
   //{{AFX_MSG_MAP(CSignalsenderDlg)
   ON_BN_CLICKED(ID_HELP, OnHelp)
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSignalsenderDlg message handlers

BOOL CSignalreceiverDlg::OnInitDialog()
{
   CDialog::OnInitDialog();

   m_bmBtn.SubclassDlgItem(IDC_SIGNALRECEIVER_BMBTN, this);
   m_bmBtn.LoadBitmaps(IDB_PAGE_INB);

   return TRUE;  // return TRUE unless you set the focus to a control
   // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CSignalsenderDlg::OnInitDialog()
{
   CDialog::OnInitDialog();

   m_bmBtn.SubclassDlgItem(IDC_SIGNALSENDER_BMBTN, this);
   m_bmBtn.LoadBitmaps(IDB_PAGE_OUTB);

   return TRUE;  // return TRUE unless you set the focus to a control
   // EXCEPTION: OCX Property Pages should return FALSE
}

void CSignalreceiverDlg::OnHelp()
{
   ::HtmlHelp(NULL, "mmlogic.chm", HH_DISPLAY_TOPIC, (DWORD) "html\\signal_receiver_device.htm");
}

void CSignalsenderDlg::OnHelp()
{
   ::HtmlHelp(NULL, "mmlogic.chm", HH_DISPLAY_TOPIC, (DWORD) "html\\signal_sender_device.htm");
}
/////////////////////////////////////////////////////////////////////////////
// CKeyboardDlg dialog


CKeyboardDlg::CKeyboardDlg(CWnd* pParent /*=NULL*/)
: CDialog(CKeyboardDlg::IDD, pParent)
{
   //{{AFX_DATA_INIT(CKeyboardDlg)
   m_bAscii = FALSE;
   //}}AFX_DATA_INIT
}


void CKeyboardDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(CKeyboardDlg)
   DDX_Check(pDX, IDC_KEYBOARD_ASCII, m_bAscii);
   //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CKeyboardDlg, CDialog)
   //{{AFX_MSG_MAP(CKeyboardDlg)
   ON_BN_CLICKED(ID_HELP, OnHelp)
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKeyboardDlg message handlers

void CKeyboardDlg::OnHelp()
{
   ::HtmlHelp(NULL, "mmlogic.chm", HH_DISPLAY_TOPIC, (DWORD) "html\\keyboard_device.htm");
}

BOOL CKeyboardDlg::OnInitDialog()
{
   CDialog::OnInitDialog();

   m_bmBtn.SubclassDlgItem(IDC_KEYBOARD_BMBTN, this);
   m_bmBtn.LoadBitmaps(IDB_KEYBOARD_OFFB);

   return TRUE;  // return TRUE unless you set the focus to a control
   // EXCEPTION: OCX Property Pages should return FALSE
}

void CRandomDlg::OnHelp()
{
   ::HtmlHelp(NULL, "mmlogic.chm", HH_DISPLAY_TOPIC, (DWORD) "html\\random_device.htm");
}
/////////////////////////////////////////////////////////////////////////////
// CNetworkDlg dialog


CNetworkDlg::CNetworkDlg(CWnd* pParent /*=NULL*/)
: CDialog(CNetworkDlg::IDD, pParent)
{
   //{{AFX_DATA_INIT(CNetworkDlg)
   m_iDirection = -1;
   m_csName = _T("");
   m_uPort = 0;
   //}}AFX_DATA_INIT
}


void CNetworkDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(CNetworkDlg)
   DDX_Control(pDX, IDC_NETWORK_NAME, m_ceName);
   DDX_Radio(pDX, IDC_NETWORK_MAKE, m_iDirection);
   DDX_Text(pDX, IDC_NETWORK_NAME, m_csName);
   DDX_Text(pDX, IDC_NETWORK_SOCKET, m_uPort);
   //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNetworkDlg, CDialog)
   //{{AFX_MSG_MAP(CNetworkDlg)
   ON_BN_CLICKED(ID_HELP, OnHelp)
   ON_BN_CLICKED(IDC_NETWORK_LISTEN, OnNetworkListen)
   ON_BN_CLICKED(IDC_NETWORK_MAKE, OnNetworkMake)
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNetworkDlg message handlers

BOOL CNetworkDlg::OnInitDialog()
{
   CDialog::OnInitDialog();

   m_bmBtn.SubclassDlgItem(IDC_NETWORK_BMBTN, this);
   RecalcBM();

   return TRUE;  // return TRUE unless you set the focus to a control
   // EXCEPTION: OCX Property Pages should return FALSE
}

void CNetworkDlg::OnHelp()
{
   ::HtmlHelp(NULL, "mmlogic.chm", HH_DISPLAY_TOPIC, (DWORD) "html\\network_device.htm");
}

void CNetworkDlg::OnNetworkListen()
{
   RecalcBM();
   m_bmBtn.Invalidate();
}

void CNetworkDlg::OnNetworkMake()
{
   RecalcBM();
   m_bmBtn.Invalidate();
}

void CNetworkDlg::RecalcBM()
{
   UpdateData();

   if (m_iDirection == 0) // make call
   {
      m_bmBtn.LoadBitmaps(IDB_NETWORK_CALLB);
      m_ceName.EnableWindow(TRUE);
   }
   else
   {
      m_bmBtn.LoadBitmaps(IDB_NETWORK_WAITB);
      m_ceName.EnableWindow(FALSE);
   }

}

/////////////////////////////////////////////////////////////////////////////
// CNodeDlg dialog


CNodeDlg::CNodeDlg(CWnd* pParent /*=NULL*/)
: CDialog(CNodeDlg::IDD, pParent)
{
   //{{AFX_DATA_INIT(CNodeDlg)
   m_iPass = -1;
   m_iFloat = -1;
   //}}AFX_DATA_INIT
}


void CNodeDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(CNodeDlg)
   DDX_Radio(pDX, IDC_NODE_PASS, m_iPass);
   DDX_Radio(pDX, IDC_NODE_FLOAT, m_iFloat);
   //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNodeDlg, CDialog)
   //{{AFX_MSG_MAP(CNodeDlg)
   ON_BN_CLICKED(ID_HELP, OnHelp)
   ON_BN_CLICKED(IDC_NODE_PASS, OnNodePass)
   ON_BN_CLICKED(IDC_NODE_PULLDOWN, OnNodePulldown)
   ON_BN_CLICKED(IDC_NODE_PULLUP, OnNodePullup)
   ON_BN_CLICKED(IDC_NODE_ZERO, OnNodeZero)
   ON_BN_CLICKED(IDC_NODE_FLOAT, OnNodeFloat)
   ON_BN_CLICKED(IDC_NODE_ONE, OnNodeOne)
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNodeDlg message handlers

BOOL CNodeDlg::OnInitDialog()
{
   CDialog::OnInitDialog();

   m_bmBtn.SubclassDlgItem(IDC_NODE_BMBTN, this);
   RecalcBM();

   return TRUE;  // return TRUE unless you set the focus to a control
   // EXCEPTION: OCX Property Pages should return FALSE
}
/////////////////////////////////////////////////////////////////////////////
// CFlipflopDlg dialog


CFlipflopDlg::CFlipflopDlg(CWnd* pParent /*=NULL*/)
: CDialog(CFlipflopDlg::IDD, pParent)
{
   //{{AFX_DATA_INIT(CFlipflopDlg)
   m_iStyle = -1;
   m_bPresetClear = FALSE;
   m_bEdge = FALSE;
   //}}AFX_DATA_INIT
}


void CFlipflopDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(CFlipflopDlg)
   DDX_Radio(pDX, IDC_FLIPFLOP_RS, m_iStyle);
   DDX_Check(pDX, IDC_FLIPFLOP_PC, m_bPresetClear);
   DDX_Check(pDX, IDC_FLIPFLOP_EDGE, m_bEdge);
   //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFlipflopDlg, CDialog)
   //{{AFX_MSG_MAP(CFlipflopDlg)
   ON_BN_CLICKED(ID_HELP, OnHelp)
   ON_BN_CLICKED(IDC_FLIPFLOP_CRS, OnFlipflopCrs)
   ON_BN_CLICKED(IDC_FLIPFLOP_DL, OnFlipflopDl)
   ON_BN_CLICKED(IDC_FLIPFLOP_JK, OnFlipflopJk)
   ON_BN_CLICKED(IDC_FLIPFLOP_MSDL, OnFlipflopMsdl)
   ON_BN_CLICKED(IDC_FLIPFLOP_MSRS, OnFlipflopMsrs)
   ON_BN_CLICKED(IDC_FLIPFLOP_RS, OnFlipflopRs)
   ON_BN_CLICKED(IDC_FLIPFLOP_PC, OnFlipflopPresetClear)
   ON_BN_CLICKED(IDC_FLIPFLOP_EDGE, OnFlipflopEdge)
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFlipflopDlg message handlers

void CFlipflopDlg::OnHelp()
{
   ::HtmlHelp(NULL, "mmlogic.chm", HH_DISPLAY_TOPIC, (DWORD) "html\\flipflop_device.htm");
}

void CNodeDlg::OnHelp()
{
   ::HtmlHelp(NULL, "mmlogic.chm", HH_DISPLAY_TOPIC, (DWORD) "html\\node_tool.htm");
}

void CFlipflopDlg::RecalcBM()
{
   UpdateData();

   if (m_bEdge)
   {
      if (m_bPresetClear)
      {
         switch (m_iStyle)
         {
         case 0: m_bmBtn.LoadBitmaps(IDB_FF_RS_PCB); break;
         case 1: m_bmBtn.LoadBitmaps(IDB_FF_DLE_PCB); break;
         case 2: m_bmBtn.LoadBitmaps(IDB_FF_CRSE_PCB); break;
         case 3: m_bmBtn.LoadBitmaps(IDB_FF_MSRSE_PCB); break;
         case 4: m_bmBtn.LoadBitmaps(IDB_FF_MSDLE_PCB); break;
         case 5: m_bmBtn.LoadBitmaps(IDB_FF_JKE_PCB); break;
         }
      }
      else
      {
         switch (m_iStyle)
         {
         case 0: m_bmBtn.LoadBitmaps(IDB_FF_RSB); break;
         case 1: m_bmBtn.LoadBitmaps(IDB_FF_DLEB); break;
         case 2: m_bmBtn.LoadBitmaps(IDB_FF_CRSEB); break;
         case 3: m_bmBtn.LoadBitmaps(IDB_FF_MSRSEB); break;
         case 4: m_bmBtn.LoadBitmaps(IDB_FF_MSDLEB); break;
         case 5: m_bmBtn.LoadBitmaps(IDB_FF_JKEB); break;
         }
      }
   }
   else
   {
      if (m_bPresetClear)
      {
         switch (m_iStyle)
         {
         case 0: m_bmBtn.LoadBitmaps(IDB_FF_RS_PCB); break;
         case 1: m_bmBtn.LoadBitmaps(IDB_FF_DL_PCB); break;
         case 2: m_bmBtn.LoadBitmaps(IDB_FF_CRS_PCB); break;
         case 3: m_bmBtn.LoadBitmaps(IDB_FF_MSRS_PCB); break;
         case 4: m_bmBtn.LoadBitmaps(IDB_FF_MSDL_PCB); break;
         case 5: m_bmBtn.LoadBitmaps(IDB_FF_JK_PCB); break;
         }
      }
      else
      {
         switch (m_iStyle)
         {
         case 0: m_bmBtn.LoadBitmaps(IDB_FF_RSB); break;
         case 1: m_bmBtn.LoadBitmaps(IDB_FF_DLB); break;
         case 2: m_bmBtn.LoadBitmaps(IDB_FF_CRSB); break;
         case 3: m_bmBtn.LoadBitmaps(IDB_FF_MSRSB); break;
         case 4: m_bmBtn.LoadBitmaps(IDB_FF_MSDLB); break;
         case 5: m_bmBtn.LoadBitmaps(IDB_FF_JKB); break;
         }
      }
   }
}

BOOL CFlipflopDlg::OnInitDialog()
{
   CDialog::OnInitDialog();

   m_bmBtn.SubclassDlgItem(IDC_FLIPFLOP_BMBTN, this);
   RecalcBM();

   return TRUE;  // return TRUE unless you set the focus to a control
   // EXCEPTION: OCX Property Pages should return FALSE
}

void CFlipflopDlg::OnFlipflopCrs()
{
   RecalcBM();
   m_bmBtn.Invalidate();
}

void CFlipflopDlg::OnFlipflopDl()
{
   RecalcBM();
   m_bmBtn.Invalidate();
}

void CFlipflopDlg::OnFlipflopJk()
{
   RecalcBM();
   m_bmBtn.Invalidate();
}

void CFlipflopDlg::OnFlipflopMsdl()
{
   RecalcBM();
   m_bmBtn.Invalidate();
}

void CFlipflopDlg::OnFlipflopMsrs()
{
   RecalcBM();
   m_bmBtn.Invalidate();
}

void CFlipflopDlg::OnFlipflopRs()
{
   RecalcBM();
   m_bmBtn.Invalidate();
}

void CNodeDlg::OnNodePass()
{
   RecalcBM();
   m_bmBtn.Invalidate();
}

void CNodeDlg::OnNodePulldown()
{
   RecalcBM();
   m_bmBtn.Invalidate();
}

void CNodeDlg::OnNodePullup()
{
   RecalcBM();
   m_bmBtn.Invalidate();
}

void CNodeDlg::RecalcBM()
{
   UpdateData();

   switch (m_iFloat)
   {
   case 0:
      {
         switch (m_iPass)
         {
         case 0: m_bmBtn.LoadBitmaps(IDB_NULLB); break;
         case 1: m_bmBtn.LoadBitmaps(IDB_NULL_1B); break;
         case 2: m_bmBtn.LoadBitmaps(IDB_NULL_0B); break;
         }
         break;
      }
   case 1:
      {
         switch (m_iPass)
         {
         case 0: m_bmBtn.LoadBitmaps(IDB_NULL_PUB); break;
         case 1: m_bmBtn.LoadBitmaps(IDB_NULL_PU1B); break;
         case 2: m_bmBtn.LoadBitmaps(IDB_NULL_PU0B); break;
         }
         break;
      }
   case 2:
      {
         switch (m_iPass)
         {
         case 0: m_bmBtn.LoadBitmaps(IDB_NULL_PDB); break;
         case 1: m_bmBtn.LoadBitmaps(IDB_NULL_PD1B); break;
         case 2: m_bmBtn.LoadBitmaps(IDB_NULL_PD0B); break;
         }
         break;
      }
   }
}


void CFlipflopDlg::OnFlipflopPresetClear()
{
   RecalcBM();
   m_bmBtn.Invalidate();
}

void CFlipflopDlg::OnFlipflopEdge()
{
   RecalcBM();
   m_bmBtn.Invalidate();
}

void CMuxDlg::OnMuxDemux1to2()
{
   RecalcBM();
   m_bmBtn.Invalidate();
}

void CMuxDlg::OnMuxDemux2to4()
{
   RecalcBM();
   m_bmBtn.Invalidate();
}

void CMuxDlg::OnMuxDemux3to8()
{
   RecalcBM();
   m_bmBtn.Invalidate();
}

void CMuxDlg::OnMuxMux2to1()
{
   RecalcBM();
   m_bmBtn.Invalidate();
}

void CMuxDlg::OnMuxMux4to1()
{
   RecalcBM();
   m_bmBtn.Invalidate();
}

void CMuxDlg::OnMuxMux8to1()
{
   RecalcBM();
   m_bmBtn.Invalidate();
}
/////////////////////////////////////////////////////////////////////////////
// CRobotDlg dialog


CRobotDlg::CRobotDlg(CWnd* pParent /*=NULL*/)
: CDialog(CRobotDlg::IDD, pParent)
{
   //{{AFX_DATA_INIT(CRobotDlg)
   m_csFileName = _T("");
   m_iStyle = -1;
   m_iHotspot = -1;
   m_iPosition = -1;
   m_iHotspotX = 0;
   m_iHotspotY = 0;
   m_iPositionX = 0;
   m_iPositionY = 0;
   //}}AFX_DATA_INIT
}


void CRobotDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(CRobotDlg)
   DDX_Control(pDX, IDC_POSITION_Y, m_cePositionY);
   DDX_Control(pDX, IDC_POSITION_X, m_cePositionX);
   DDX_Control(pDX, IDC_HOTSPOT_Y, m_ceHotspotY);
   DDX_Control(pDX, IDC_HOTSPOT_X, m_ceHotspotX);
   DDX_Text(pDX, IDC_ROBOT_FILENAME, m_csFileName);
   DDX_Radio(pDX, IDC_STYLE_SEEING, m_iStyle);
   DDX_Radio(pDX, IDC_HOTSPOT_CENTER, m_iHotspot);
   DDX_Radio(pDX, IDC_POSITION_CENTER, m_iPosition);
   DDX_Text(pDX, IDC_HOTSPOT_X, m_iHotspotX);
   DDX_Text(pDX, IDC_HOTSPOT_Y, m_iHotspotY);
   DDX_Text(pDX, IDC_POSITION_X, m_iPositionX);
   DDX_Text(pDX, IDC_POSITION_Y, m_iPositionY);
   //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRobotDlg, CDialog)
   //{{AFX_MSG_MAP(CRobotDlg)
   ON_BN_CLICKED(ID_BROWSE, OnBrowse)
   ON_BN_CLICKED(ID_HELP, OnHelp)
   ON_BN_CLICKED(ID_EDIT, OnEdit)
   ON_BN_CLICKED(IDC_HOTSPOT_CENTER, OnHotspotCenter)
   ON_BN_CLICKED(IDC_HOTSPOT_CT, OnHotspotCt)
   ON_BN_CLICKED(IDC_HOTSPOT_LL, OnHotspotLl)
   ON_BN_CLICKED(IDC_HOTSPOT_LR, OnHotspotLr)
   ON_BN_CLICKED(IDC_HOTSPOT_UL, OnHotspotUl)
   ON_BN_CLICKED(IDC_HOTSPOT_UR, OnHotspotUr)
   ON_BN_CLICKED(IDC_POSITION_CENTER, OnPositionCenter)
   ON_BN_CLICKED(IDC_POSITION_CT, OnPositionCt)
   ON_BN_CLICKED(IDC_POSITION_LL, OnPositionLl)
   ON_BN_CLICKED(IDC_POSITION_LR, OnPositionLr)
   ON_BN_CLICKED(IDC_POSITION_UL, OnPositionUl)
   ON_BN_CLICKED(IDC_POSITION_UR, OnPositionUr)
   ON_BN_CLICKED(IDC_STYLE_DRAWING, OnStyleDrawing)
   ON_BN_CLICKED(IDC_STYLE_SEEING, OnStyleSeeing)
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRobotDlg message handlers

void CTextDlg::RecalcBM()
{
   UpdateData();

   switch (m_iStyle)
   {
   case 0:
      {
         m_bmBtn.LoadBitmaps(IDB_TEXTSB);
         m_ceFileName.EnableWindow(FALSE);
         m_cbBrowse.EnableWindow(FALSE);
         m_cbEdit.EnableWindow(FALSE);
         break;
      }
   case 1:
      {
         m_bmBtn.LoadBitmaps(IDB_TEXTMB);
         m_ceFileName.EnableWindow(TRUE);
         m_cbBrowse.EnableWindow(TRUE);
         m_cbEdit.EnableWindow(TRUE);
         break;
      }
   }
}

void CRobotDlg::OnBrowse()
{
   UpdateData();

   CString csFullPath;

   char szFilter[] = "Bitmap Files (*.BMP)|*.BMP||";

   RelativeToFullPath(m_csFileName, m_csPathName, csFullPath);

   CFileDialog cfBrowse(TRUE, "BMP", csFullPath, /* OFN_FILEMUSTEXIST | */ OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter);

   if (cfBrowse.DoModal() == IDOK)
   {
      m_csFileName = cfBrowse.GetPathName();
      UpdateData(FALSE);
   }
}

void CRobotDlg::OnHelp()
{
   ::HtmlHelp(NULL, "mmlogic.chm", HH_DISPLAY_TOPIC, (DWORD) "html\\robot_device.htm");
}

void CBitmapDlg::OnBmpSingle()
{
   RecalcBM();
   m_bmBtn.Invalidate();
}

void CBitmapDlg::OnBmpMultiple()
{
   RecalcBM();
   m_bmBtn.Invalidate();
}

void CTextDlg::OnTextMultiple()
{
   RecalcBM();
   m_bmBtn.Invalidate();
}

void CTextDlg::OnTextSingle()
{
   RecalcBM();
   m_bmBtn.Invalidate();
}

void CTextDlg::OnBrowse()
{
   UpdateData();

   CString csFullPath;

   char szFilter[] = "Text Files (*.TXT)|*.TXT||";

   RelativeToFullPath(m_csFileName, m_csPathName, csFullPath);

   CFileDialog cfBrowse(TRUE, "TXT", csFullPath, /* OFN_FILEMUSTEXIST | */ OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter);

   if (cfBrowse.DoModal() == IDOK)
   {
      m_csFileName = cfBrowse.GetPathName();
      UpdateData(FALSE);
   }
}

BOOL CTextDlg::OnInitDialog()
{
   CDialog::OnInitDialog();

   m_bmBtn.SubclassDlgItem(IDC_TEXT_BMBTN, this);
   RecalcBM();

   return TRUE;  // return TRUE unless you set the focus to a control
   // EXCEPTION: OCX Property Pages should return FALSE
}

void CMemoryDlg::OnEdit()
{
   UpdateData();

   CString csFullPath;

   RelativeToFullPath(m_csFileName, m_csPathName, csFullPath);

   if (!TouchFile(csFullPath)) return;

   LaunchFile(csFullPath);
}

void CBitmapDlg::OnEdit()
{
   UpdateData();

   CString csFullPath;

   RelativeToFullPath(m_csFileName, m_csPathName, csFullPath);

   if (!TouchFile(csFullPath)) return;

   LaunchFile(csFullPath);
}

void CSoundDlg::OnEdit()
{
   UpdateData();

   CString csFullPath;

   RelativeToFullPath(m_csFileName, m_csPathName, csFullPath);

   if (!TouchFile(csFullPath)) return;

   LaunchFile(csFullPath);
}

void CTextDlg::OnEdit()
{
   UpdateData();

   CString csFullPath;

   RelativeToFullPath(m_csFileName, m_csPathName, csFullPath);

   if (!TouchFile(csFullPath)) return;

   LaunchFile(csFullPath);
}

void CFileinDlg::OnEdit()
{
   UpdateData();

   CString csFullPath;

   RelativeToFullPath(m_csFileName, m_csPathName, csFullPath);

   if (!TouchFile(csFullPath)) return;

   LaunchFile(csFullPath);
}
/////////////////////////////////////////////////////////////////////////////
// CSelectDlg dialog


CSelectDlg::CSelectDlg(CWnd* pParent /*=NULL*/)
: CDialog(CSelectDlg::IDD, pParent)
{
   //{{AFX_DATA_INIT(CSelectDlg)
   m_iInitial = -1;
   //}}AFX_DATA_INIT
}


void CSelectDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(CSelectDlg)
   DDX_Radio(pDX, IDC_SELECT_0, m_iInitial);
   //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSelectDlg, CDialog)
   //{{AFX_MSG_MAP(CSelectDlg)
   ON_BN_CLICKED(IDC_SELECT_0, OnSelect0)
   ON_BN_CLICKED(IDC_SELECT_1, OnSelect1)
   ON_BN_CLICKED(IDC_SELECT_2, OnSelect2)
   ON_BN_CLICKED(IDC_SELECT_3, OnSelect3)
   ON_BN_CLICKED(IDC_SELECT_4, OnSelect4)
   ON_BN_CLICKED(IDC_SELECT_5, OnSelect5)
   ON_BN_CLICKED(IDC_SELECT_6, OnSelect6)
   ON_BN_CLICKED(IDC_SELECT_7, OnSelect7)
   ON_BN_CLICKED(IDC_SELECT_8, OnSelect8)
   ON_BN_CLICKED(IDC_SELECT_9, OnSelect9)
   ON_BN_CLICKED(IDC_SELECT_A, OnSelectA)
   ON_BN_CLICKED(IDC_SELECT_B, OnSelectB)
   ON_BN_CLICKED(IDC_SELECT_C, OnSelectC)
   ON_BN_CLICKED(IDC_SELECT_D, OnSelectD)
   ON_BN_CLICKED(IDC_SELECT_E, OnSelectE)
   ON_BN_CLICKED(IDC_SELECT_F, OnSelectF)
   ON_BN_CLICKED(ID_HELP, OnHelp)
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSelectDlg message handlers

void CSelectDlg::OnSelect0()
{
   RecalcBM();
   m_bmBtn.Invalidate();
}

void CSelectDlg::OnSelect1()
{
   RecalcBM();
   m_bmBtn.Invalidate();
}

void CSelectDlg::OnSelect2()
{
   RecalcBM();
   m_bmBtn.Invalidate();
}

void CSelectDlg::OnSelect3()
{
   RecalcBM();
   m_bmBtn.Invalidate();
}

void CSelectDlg::OnSelect4()
{
   RecalcBM();
   m_bmBtn.Invalidate();
}

void CSelectDlg::OnSelect5()
{
   RecalcBM();
   m_bmBtn.Invalidate();
}

void CSelectDlg::OnSelect6()
{
   RecalcBM();
   m_bmBtn.Invalidate();
}

void CSelectDlg::OnSelect7()
{
   RecalcBM();
   m_bmBtn.Invalidate();
}

void CSelectDlg::OnSelect8()
{
   RecalcBM();
   m_bmBtn.Invalidate();
}

void CSelectDlg::OnSelect9()
{
   RecalcBM();
   m_bmBtn.Invalidate();
}

void CSelectDlg::OnSelectA()
{
   RecalcBM();
   m_bmBtn.Invalidate();
}

void CSelectDlg::OnSelectB()
{
   RecalcBM();
   m_bmBtn.Invalidate();
}

void CSelectDlg::OnSelectC()
{
   RecalcBM();
   m_bmBtn.Invalidate();
}

void CSelectDlg::OnSelectD()
{
   RecalcBM();
   m_bmBtn.Invalidate();
}

void CSelectDlg::OnSelectE()
{
   RecalcBM();
   m_bmBtn.Invalidate();
}

void CSelectDlg::OnSelectF()
{
   RecalcBM();
   m_bmBtn.Invalidate();
}

BOOL CSelectDlg::OnInitDialog()
{
   CDialog::OnInitDialog();

   m_bmBtn.SubclassDlgItem(IDC_SELECT_BMBTN, this);
   RecalcBM();

   return TRUE;  // return TRUE unless you set the focus to a control
   // EXCEPTION: OCX Property Pages should return FALSE
}

void CSelectDlg::RecalcBM()
{
   UpdateData();

   m_bmBtn.LoadBitmaps(IDB_SELECT_0B + m_iInitial);
}

void CSelectDlg::OnHelp()
{
   ::HtmlHelp(NULL, "mmlogic.chm", HH_DISPLAY_TOPIC, (DWORD) "html\\select_device.htm");
}

BOOL CRobotDlg::OnInitDialog()
{
   CDialog::OnInitDialog();

   m_bmBtn.SubclassDlgItem(IDC_ROBOT_BMBTN, this);
   RecalcBM();

   return TRUE;  // return TRUE unless you set the focus to a control
   // EXCEPTION: OCX Property Pages should return FALSE
}

void CRobotDlg::OnEdit()
{
   UpdateData();

   CString csFullPath;

   RelativeToFullPath(m_csFileName, m_csPathName, csFullPath);

   if (!TouchFile(csFullPath)) return;

   LaunchFile(csFullPath);
}
/////////////////////////////////////////////////////////////////////////////
// CGridDlg dialog


CGridDlg::CGridDlg(CWnd* pParent /*=NULL*/)
: CDialog(CGridDlg::IDD, pParent)
{
   //{{AFX_DATA_INIT(CGridDlg)
   m_bEnable = FALSE;
   m_uHeight = 0;
   m_uWidth = 0;
   //}}AFX_DATA_INIT
}


void CGridDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(CGridDlg)
   DDX_Check(pDX, IDC_GRID_ENABLE, m_bEnable);
   DDX_Text(pDX, IDC_GRID_HEIGHT, m_uHeight);
   DDV_MinMaxUInt(pDX, m_uHeight, 2, 200);
   DDX_Text(pDX, IDC_GRID_WIDTH, m_uWidth);
   DDV_MinMaxUInt(pDX, m_uWidth, 2, 200);
   DDX_Text(pDX, IDC_GRID_CANVASHEIGHT, m_uCanvasHeight);
   DDV_MinMaxUInt(pDX, m_uCanvasHeight, 100, 4096);
   DDX_Text(pDX, IDC_GRID_CANVASWIDTH, m_uCanvasWidth);
   DDV_MinMaxUInt(pDX, m_uCanvasWidth, 100, 4096);
   //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGridDlg, CDialog)
   //{{AFX_MSG_MAP(CGridDlg)
   // NOTE: the ClassWizard will add message map macros here
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGridDlg message handlers

void CNodeDlg::OnNodeZero()
{
   RecalcBM();
   m_bmBtn.Invalidate();
}

void CNodeDlg::OnNodeFloat()
{
   RecalcBM();
   m_bmBtn.Invalidate();
}

void CNodeDlg::OnNodeOne()
{
   RecalcBM();
   m_bmBtn.Invalidate();
}
/////////////////////////////////////////////////////////////////////////////
// CTristateDlg dialog


CTristateDlg::CTristateDlg(CWnd* pParent /*=NULL*/)
: CDialog(CTristateDlg::IDD, pParent)
{
   //{{AFX_DATA_INIT(CTristateDlg)
   m_bAssertLO = FALSE;
   m_bDemorgan = FALSE;
   //}}AFX_DATA_INIT
}


void CTristateDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(CTristateDlg)
   DDX_Check(pDX, IDC_TRISTATE_ASSERT_LO, m_bAssertLO);
   DDX_Check(pDX, IDC_TRISTATE_DEMORGAN, m_bDemorgan);
   //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTristateDlg, CDialog)
   //{{AFX_MSG_MAP(CTristateDlg)
   ON_BN_CLICKED(IDC_TRISTATE_ASSERT_LO, OnTristateAssertLo)
   ON_BN_CLICKED(IDC_TRISTATE_DEMORGAN, OnTristateDemorgan)
   ON_BN_CLICKED(ID_HELP, OnHelp)
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTristateDlg message handlers

void CTristateDlg::RecalcBM()
{
   UpdateData();

   if (m_bAssertLO)
   {
      if (m_bDemorgan)
      {
         m_bmBtn.LoadBitmaps(IDB_TRISTATE_BUFFER_LOB);
      }
      else
      {
         m_bmBtn.LoadBitmaps(IDB_TRISTATE_INVERT_LOB);
      }
   }
   else
   {
      if (m_bDemorgan)
      {
         m_bmBtn.LoadBitmaps(IDB_TRISTATE_BUFFER_HIB);
      }
      else
      {
         m_bmBtn.LoadBitmaps(IDB_TRISTATE_INVERT_HIB);
      }
   }

}

void CTristateDlg::OnTristateAssertLo()
{
   RecalcBM();
   m_bmBtn.Invalidate();
}

void CTristateDlg::OnTristateDemorgan()
{
   RecalcBM();
   m_bmBtn.Invalidate();
}

BOOL CTristateDlg::OnInitDialog()
{
   CDialog::OnInitDialog();

   m_bmBtn.SubclassDlgItem(IDC_TRISTATE_BMBTN, this);
   RecalcBM();

   return TRUE;  // return TRUE unless you set the focus to a control
   // EXCEPTION: OCX Property Pages should return FALSE
}
/////////////////////////////////////////////////////////////////////////////
// CBusDlg dialog


CBusDlg::CBusDlg(CWnd* pParent /*=NULL*/)
: CDialog(CBusDlg::IDD, pParent)
{
   //{{AFX_DATA_INIT(CBusDlg)
   m_iInputs = -1;
   //}}AFX_DATA_INIT
}


void CBusDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(CBusDlg)
   DDX_Radio(pDX, IDC_BUS_2INPUTS, m_iInputs);
   //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBusDlg, CDialog)
   //{{AFX_MSG_MAP(CBusDlg)
   ON_BN_CLICKED(IDC_BUS_2INPUTS, OnBus2inputs)
   ON_BN_CLICKED(IDC_BUS_4INPUTS, OnBus4inputs)
   ON_BN_CLICKED(IDC_BUS_8INPUTS, OnBus8inputs)
   ON_BN_CLICKED(ID_HELP, OnHelp)
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBusDlg message handlers

void CBusDlg::RecalcBM()
{
   UpdateData();

   switch (m_iInputs)
   {
   case 0: m_bmBtn.LoadBitmaps(IDB_BUS_2B); break;
   case 1: m_bmBtn.LoadBitmaps(IDB_BUS_4B); break;
   case 2: m_bmBtn.LoadBitmaps(IDB_BUS_8B); break;
   }

}

void CBusDlg::OnBus2inputs()
{
   RecalcBM();
   m_bmBtn.Invalidate();
}

void CBusDlg::OnBus4inputs()
{
   RecalcBM();
   m_bmBtn.Invalidate();
}

void CBusDlg::OnBus8inputs()
{
   RecalcBM();
   m_bmBtn.Invalidate();
}

BOOL CBusDlg::OnInitDialog()
{
   CDialog::OnInitDialog();

   m_bmBtn.SubclassDlgItem(IDC_BUS_BMBTN, this);
   RecalcBM();

   return TRUE;  // return TRUE unless you set the focus to a control
   // EXCEPTION: OCX Property Pages should return FALSE
}

void CRobotDlg::OnHotspotCenter()
{
   RecalcBM();
   m_bmBtn.Invalidate();
}

void CRobotDlg::OnHotspotCt()
{
   RecalcBM();
   m_bmBtn.Invalidate();
}

void CRobotDlg::OnHotspotLl()
{
   RecalcBM();
   m_bmBtn.Invalidate();
}

void CRobotDlg::OnHotspotLr()
{
   RecalcBM();
   m_bmBtn.Invalidate();
}

void CRobotDlg::OnHotspotUl()
{
   RecalcBM();
   m_bmBtn.Invalidate();
}

void CRobotDlg::OnHotspotUr()
{
   RecalcBM();
   m_bmBtn.Invalidate();
}

void CRobotDlg::OnPositionCenter()
{
   RecalcBM();
   m_bmBtn.Invalidate();
}

void CRobotDlg::OnPositionCt()
{
   RecalcBM();
   m_bmBtn.Invalidate();
}

void CRobotDlg::OnPositionLl()
{
   RecalcBM();
   m_bmBtn.Invalidate();
}

void CRobotDlg::OnPositionLr()
{
   RecalcBM();
   m_bmBtn.Invalidate();
}

void CRobotDlg::OnPositionUl()
{
   RecalcBM();
   m_bmBtn.Invalidate();
}

void CRobotDlg::OnPositionUr()
{
   RecalcBM();
   m_bmBtn.Invalidate();
}

void CRobotDlg::RecalcBM()
{
   UpdateData();

   switch (m_iStyle)
   {
   case 0:
      {
         m_bmBtn.LoadBitmaps(IDB_ROBOTB);
         break;
      }
   case 1:
      {
         m_bmBtn.LoadBitmaps(IDB_ROBOTDB);
         break;
      }
   }

   switch (m_iPosition)
   {
   case 0:
   case 1:
   case 2:
   case 3:
   case 4:
      {
         m_cePositionX.EnableWindow(FALSE);
         m_cePositionY.EnableWindow(FALSE);
         break;
      }
   case 5:
      {
         m_cePositionX.EnableWindow(TRUE);
         m_cePositionY.EnableWindow(TRUE);
         break;
      }
   }

   switch (m_iHotspot)
   {
   case 0:
   case 1:
   case 2:
   case 3:
   case 4:
      {
         m_ceHotspotX.EnableWindow(FALSE);
         m_ceHotspotY.EnableWindow(FALSE);
         break;
      }
   case 5:
      {
         m_ceHotspotX.EnableWindow(TRUE);
         m_ceHotspotY.EnableWindow(TRUE);
         break;
      }
   }



}


void CRobotDlg::OnStyleDrawing()
{
   RecalcBM();
   m_bmBtn.Invalidate();
}

void CRobotDlg::OnStyleSeeing()
{
   RecalcBM();
   m_bmBtn.Invalidate();
}
/////////////////////////////////////////////////////////////////////////////
// CAluDlg dialog


CAluDlg::CAluDlg(CWnd* pParent /*=NULL*/)
: CDialog(CAluDlg::IDD, pParent)
{
   //{{AFX_DATA_INIT(CAluDlg)
   // NOTE: the ClassWizard will add member initialization here
   //}}AFX_DATA_INIT
}


void CAluDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(CAluDlg)
   // NOTE: the ClassWizard will add DDX and DDV calls here
   //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAluDlg, CDialog)
   //{{AFX_MSG_MAP(CAluDlg)
   ON_BN_CLICKED(ID_HELP, OnHelp)
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAluDlg message handlers

void CAluDlg::OnHelp()
{
   ::HtmlHelp(NULL, "mmlogic.chm", HH_DISPLAY_TOPIC, (DWORD) "html\\alu_device.htm");
}

BOOL CAluDlg::OnInitDialog()
{
   CDialog::OnInitDialog();

   m_bmBtn.SubclassDlgItem(IDC_ALU_BMBTN, this);
   m_bmBtn.LoadBitmaps(IDB_ALUB);

   return TRUE;  // return TRUE unless you set the focus to a control
   // EXCEPTION: OCX Property Pages should return FALSE
}
/////////////////////////////////////////////////////////////////////////////
// CBitBucketDlg dialog


CBitBucketDlg::CBitBucketDlg(CWnd* pParent /*=NULL*/)
: CDialog(CBitBucketDlg::IDD, pParent)
{
   //{{AFX_DATA_INIT(CBitBucketDlg)
   // NOTE: the ClassWizard will add member initialization here
   //}}AFX_DATA_INIT
}


void CBitBucketDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(CBitBucketDlg)
   // NOTE: the ClassWizard will add DDX and DDV calls here
   //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBitBucketDlg, CDialog)
   //{{AFX_MSG_MAP(CBitBucketDlg)
   ON_BN_CLICKED(ID_HELP, OnHelp)
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBitBucketDlg message handlers

void CBitBucketDlg::OnHelp()
{
   ::HtmlHelp(NULL, "mmlogic.chm", HH_DISPLAY_TOPIC, (DWORD) "html\\bit_bucket_device.htm");
}

BOOL CBitBucketDlg::OnInitDialog()
{
   CDialog::OnInitDialog();

   m_bmBtn.SubclassDlgItem(IDC_BITBUCKET_BMBTN, this);
   m_bmBtn.LoadBitmaps(IDB_BITBUCKETB);

   return TRUE;  // return TRUE unless you set the focus to a control
   // EXCEPTION: OCX Property Pages should return FALSE
}
/////////////////////////////////////////////////////////////////////////////
// CPauseDlg dialog


CPauseDlg::CPauseDlg(CWnd* pParent /*=NULL*/)
: CDialog(CPauseDlg::IDD, pParent)
{
   //{{AFX_DATA_INIT(CPauseDlg)
   // NOTE: the ClassWizard will add member initialization here
   //}}AFX_DATA_INIT
}


void CPauseDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(CPauseDlg)
   // NOTE: the ClassWizard will add DDX and DDV calls here
   //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPauseDlg, CDialog)
   //{{AFX_MSG_MAP(CPauseDlg)
   ON_BN_CLICKED(ID_HELP, OnHelp)
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPauseDlg message handlers

void CPauseDlg::OnHelp()
{
   ::HtmlHelp(NULL, "mmlogic.chm", HH_DISPLAY_TOPIC, (DWORD) "html\\pause_simulator_device.htm");
}

BOOL CPauseDlg::OnInitDialog()
{
   CDialog::OnInitDialog();

   m_bmBtn.SubclassDlgItem(IDC_PAUSE_BMBTN, this);
   m_bmBtn.LoadBitmaps(IDB_BREAKB);

   return TRUE;  // return TRUE unless you set the focus to a control
   // EXCEPTION: OCX Property Pages should return FALSE
}
/////////////////////////////////////////////////////////////////////////////
// CDisplayDlg dialog


CDisplayDlg::CDisplayDlg(CWnd* pParent /*=NULL*/)
: CDialog(CDisplayDlg::IDD, pParent)
{
   //{{AFX_DATA_INIT(CDisplayDlg)
   // NOTE: the ClassWizard will add member initialization here
   //}}AFX_DATA_INIT
}


void CDisplayDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(CDisplayDlg)
   // NOTE: the ClassWizard will add DDX and DDV calls here
   //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDisplayDlg, CDialog)
   //{{AFX_MSG_MAP(CDisplayDlg)
   ON_BN_CLICKED(ID_HELP, OnHelp)
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDisplayDlg message handlers

void CDisplayDlg::OnHelp()
{
   ::HtmlHelp(NULL, "mmlogic.chm", HH_DISPLAY_TOPIC, (DWORD) "html\\ascii_display_device.htm");
}

BOOL CDisplayDlg::OnInitDialog()
{
   CDialog::OnInitDialog();

   m_bmBtn.SubclassDlgItem(IDC_DISPLAY_BMBTN, this);
   m_bmBtn.LoadBitmaps(IDB_DISPLAYB);

   return TRUE;  // return TRUE unless you set the focus to a control
   // EXCEPTION: OCX Property Pages should return FALSE
}
/////////////////////////////////////////////////////////////////////////////
// CGroundDlg dialog


CGroundDlg::CGroundDlg(CWnd* pParent /*=NULL*/)
: CDialog(CGroundDlg::IDD, pParent)
{
   //{{AFX_DATA_INIT(CGroundDlg)
   // NOTE: the ClassWizard will add member initialization here
   //}}AFX_DATA_INIT
}


void CGroundDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(CGroundDlg)
   // NOTE: the ClassWizard will add DDX and DDV calls here
   //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGroundDlg, CDialog)
   //{{AFX_MSG_MAP(CGroundDlg)
   ON_BN_CLICKED(ID_HELP, OnHelp)
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGroundDlg message handlers

void CGroundDlg::OnHelp()
{
   ::HtmlHelp(NULL, "mmlogic.chm", HH_DISPLAY_TOPIC, (DWORD) "html\\ground_device.htm");
}

BOOL CGroundDlg::OnInitDialog()
{
   CDialog::OnInitDialog();

   m_bmBtn.SubclassDlgItem(IDC_GROUND_BMBTN, this);
   m_bmBtn.LoadBitmaps(IDB_GROUNDB);

   return TRUE;  // return TRUE unless you set the focus to a control
   // EXCEPTION: OCX Property Pages should return FALSE
}
/////////////////////////////////////////////////////////////////////////////
// CKeypadDlg dialog


CKeypadDlg::CKeypadDlg(CWnd* pParent /*=NULL*/)
: CDialog(CKeypadDlg::IDD, pParent)
{
   //{{AFX_DATA_INIT(CKeypadDlg)
   // NOTE: the ClassWizard will add member initialization here
   //}}AFX_DATA_INIT
}


void CKeypadDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(CKeypadDlg)
   // NOTE: the ClassWizard will add DDX and DDV calls here
   //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CKeypadDlg, CDialog)
   //{{AFX_MSG_MAP(CKeypadDlg)
   ON_BN_CLICKED(ID_HELP, OnHelp)
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKeypadDlg message handlers

void CKeypadDlg::OnHelp()
{
   ::HtmlHelp(NULL, "mmlogic.chm", HH_DISPLAY_TOPIC, (DWORD) "html\\keypad_device.htm");
}

BOOL CKeypadDlg::OnInitDialog()
{
   CDialog::OnInitDialog();

   m_bmBtn.SubclassDlgItem(IDC_KEYPAD_BMBTN, this);
   m_bmBtn.LoadBitmaps(IDB_KEYPADB);

   return TRUE;  // return TRUE unless you set the focus to a control
   // EXCEPTION: OCX Property Pages should return FALSE
}
/////////////////////////////////////////////////////////////////////////////
// CCounterDlg dialog


CCounterDlg::CCounterDlg(CWnd* pParent /*=NULL*/)
: CDialog(CCounterDlg::IDD, pParent)
{
   //{{AFX_DATA_INIT(CCounterDlg)
   m_iInit = 0;
   m_iSize = -1;
   //}}AFX_DATA_INIT
}


void CCounterDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(CCounterDlg)
   DDX_Text(pDX, IDC_COUNTER_INIT, m_iInit);
   DDX_Radio(pDX, IDC_COUNTER_4BIT, m_iSize);
   //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCounterDlg, CDialog)
   //{{AFX_MSG_MAP(CCounterDlg)
   ON_BN_CLICKED(ID_HELP, OnHelp)
   ON_BN_CLICKED(IDC_COUNTER_4BIT, OnCounter4bit)
   ON_BN_CLICKED(IDC_COUNTER_8BIT, OnCounter8bit)
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCounterDlg message handlers

void CCounterDlg::OnHelp()
{
   ::HtmlHelp(NULL, "mmlogic.chm", HH_DISPLAY_TOPIC, (DWORD) "html\\counter_device.htm");
}

void CCounterDlg::RecalcBM()
{
   UpdateData();

   switch (m_iSize)
   {
   case 0: m_bmBtn.LoadBitmaps(IDB_COUNTER4B); break;
   case 1: m_bmBtn.LoadBitmaps(IDB_COUNTER8B); break;
   }
}

BOOL CCounterDlg::OnInitDialog()
{
   CDialog::OnInitDialog();

   m_bmBtn.SubclassDlgItem(IDC_COUNTER_BMBTN, this);
   RecalcBM();

   return TRUE;  // return TRUE unless you set the focus to a control
   // EXCEPTION: OCX Property Pages should return FALSE
}
/////////////////////////////////////////////////////////////////////////////
// CPlusDlg dialog


CPlusDlg::CPlusDlg(CWnd* pParent /*=NULL*/)
: CDialog(CPlusDlg::IDD, pParent)
{
   //{{AFX_DATA_INIT(CPlusDlg)
   // NOTE: the ClassWizard will add member initialization here
   //}}AFX_DATA_INIT
}


void CPlusDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(CPlusDlg)
   // NOTE: the ClassWizard will add DDX and DDV calls here
   //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPlusDlg, CDialog)
   //{{AFX_MSG_MAP(CPlusDlg)
   ON_BN_CLICKED(ID_HELP, OnHelp)
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPlusDlg message handlers

void CPlusDlg::OnHelp()
{
   ::HtmlHelp(NULL, "mmlogic.chm", HH_DISPLAY_TOPIC, (DWORD) "html\\plus_device.htm");
}

BOOL CPlusDlg::OnInitDialog()
{
   CDialog::OnInitDialog();

   m_bmBtn.SubclassDlgItem(IDC_PLUS_BMBTN, this);
   m_bmBtn.LoadBitmaps(IDB_PLUSB);

   return TRUE;  // return TRUE unless you set the focus to a control
   // EXCEPTION: OCX Property Pages should return FALSE
}

void CTristateDlg::OnHelp()
{
   ::HtmlHelp(NULL, "mmlogic.chm", HH_DISPLAY_TOPIC, (DWORD) "html\\tristate_gate.htm");
}

void CBusDlg::OnHelp()
{
   ::HtmlHelp(NULL, "mmlogic.chm", HH_DISPLAY_TOPIC, (DWORD) "html\\bus_tool.htm");
}
/////////////////////////////////////////////////////////////////////////////
// CAnalyzeDlg dialog


CAnalyzeDlg::CAnalyzeDlg(CWnd* pParent /*=NULL*/)
: CDialog(CAnalyzeDlg::IDD, pParent)
{
   //{{AFX_DATA_INIT(CAnalyzeDlg)
   m_csSignalName = _T("");
   m_iDummy = -1;
   //}}AFX_DATA_INIT
}


void CAnalyzeDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(CAnalyzeDlg)
   DDX_Text(pDX, IDC_ANALYZE_SIGNALNAME, m_csSignalName);
   DDX_Radio(pDX, IDC_ANALYZE_DUMMY, m_iDummy);
   //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAnalyzeDlg, CDialog)
   //{{AFX_MSG_MAP(CAnalyzeDlg)
   // NOTE: the ClassWizard will add message map macros here
   //}}AFX_MSG_MAP
   ON_BN_CLICKED(ID_HELP, OnBnClickedHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAnalyzeDlg message handlers

void CCounterDlg::OnCounter4bit()
{
   RecalcBM();
   m_bmBtn.Invalidate();
}

void CCounterDlg::OnCounter8bit()
{
   RecalcBM();
   m_bmBtn.Invalidate();
}

/////////////////////////////////////////////////////////////////////////////
// CTapedriveDlg dialog


CTapedriveDlg::CTapedriveDlg(CWnd* pParent /*=NULL*/)
: CDialog(CTapedriveDlg::IDD, pParent)
{
   //{{AFX_DATA_INIT(CTapedriveDlg)
   m_iFormat = -1;
   m_uCapacity = 0;
   m_csFileName = _T("");
   m_uStartPosition = 0;
   //}}AFX_DATA_INIT
}


void CTapedriveDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(CTapedriveDlg)
   DDX_Control(pDX, ID_EDIT, m_cbEdit);
   DDX_Control(pDX, ID_BROWSE, m_cbBrowse);
   DDX_Radio(pDX, IDC_TAPEDRIVE_BINARY, m_iFormat);
   DDX_Text(pDX, IDC_TAPEDRIVE_CAPACITY, m_uCapacity);
   DDX_Text(pDX, IDC_TAPEDRIVE_FILENAME, m_csFileName);
   DDX_Text(pDX, IDC_TAPEDRIVE_STARTPOSITION, m_uStartPosition);
   //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTapedriveDlg, CDialog)
   //{{AFX_MSG_MAP(CTapedriveDlg)
   ON_BN_CLICKED(ID_BROWSE, OnBrowse)
   ON_BN_CLICKED(ID_EDIT, OnEdit)
   ON_BN_CLICKED(ID_HELP, OnHelp)
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTapedriveDlg message handlers

void CTapedriveDlg::OnBrowse()
{
   UpdateData();

   CString csFullPath;

   char szFilter[] = "Text Files (*.TXT)|*.TXT|All Files (*.*)|*.*||";

   RelativeToFullPath(m_csFileName, m_csPathName, csFullPath);

   CFileDialog cfBrowse(TRUE, "TXT", csFullPath, /* OFN_FILEMUSTEXIST | */ OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter);

   if (cfBrowse.DoModal() == IDOK)
   {
      m_csFileName = cfBrowse.GetPathName();
      UpdateData(FALSE);
   }
}

void CTapedriveDlg::OnEdit()
{
   UpdateData();

   CString csFullPath;

   RelativeToFullPath(m_csFileName, m_csPathName, csFullPath);

   if (!TouchFile(csFullPath)) return;

   LaunchFile(csFullPath);
}

void CTapedriveDlg::OnHelp()
{
   ::HtmlHelp(NULL, "mmlogic.chm", HH_DISPLAY_TOPIC, (DWORD) "html\\tapedrive_device.htm");
}

BOOL CTapedriveDlg::OnInitDialog()
{
   CDialog::OnInitDialog();

   m_bmBtn.SubclassDlgItem(IDC_TAPEDRIVE_BMBTN, this);
   m_bmBtn.LoadBitmaps(IDB_TAPEDRIVEB);

   return TRUE;  // return TRUE unless you set the focus to a control
   // EXCEPTION: OCX Property Pages should return FALSE
}
/////////////////////////////////////////////////////////////////////////////
// CAboutMSDlg dialog


CAboutMSDlg::CAboutMSDlg(CWnd* pParent /*=NULL*/)
: CDialog(CAboutMSDlg::IDD, pParent)
{
   //{{AFX_DATA_INIT(CAboutMSDlg)
   // NOTE: the ClassWizard will add member initialization here
   //}}AFX_DATA_INIT
}


void CAboutMSDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(CAboutMSDlg)
   // NOTE: the ClassWizard will add DDX and DDV calls here
   //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAboutMSDlg, CDialog)
   //{{AFX_MSG_MAP(CAboutMSDlg)
   // NOTE: the ClassWizard will add message map macros here
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAboutMSDlg message handlers

/////////////////////////////////////////////////////////////////////////////
// CGotoPageDlg dialog


CGotoPageDlg::CGotoPageDlg(CWnd* pParent /*=NULL*/)
: CDialog(CGotoPageDlg::IDD, pParent)
{
   //{{AFX_DATA_INIT(CGotoPageDlg)
   m_iPageNumber = 1;
   m_iPageCount = 0;
   m_pPageNames = NULL;
   //}}AFX_DATA_INIT
}


void CGotoPageDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   DDX_Control(pDX, IDC_PAGENUMBER, m_cePageNumber);
   DDX_Control(pDX, IDC_PAGENAME, m_cePageName);
   DDX_Control(pDX, IDC_PAGELIST, m_clPageList);
   DDX_Text(pDX, IDC_PAGENUMBER, m_iPageNumber);
   DDV_MinMaxInt(pDX, m_iPageNumber, 1, 4096);
}


BEGIN_MESSAGE_MAP(CGotoPageDlg, CDialog)
   //{{AFX_MSG_MAP(CAnalyzeDlg)
   ON_EN_CHANGE(IDC_PAGENUMBER, OnPageNumberChanged)
   ON_EN_CHANGE(IDC_PAGENAME, OnPageNameChanged)
   ON_LBN_SELCHANGE(IDC_PAGELIST, OnPageSelect)
   ON_LBN_DBLCLK(IDC_PAGELIST, OnPageDoubleClick)
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGotoPageDlg message handlers

BOOL CGotoPageDlg::OnInitDialog()
{
   CDialog::OnInitDialog();

   int pos;
   for (pos = 0; pos <= m_pPageNames->GetUpperBound(); pos++)
   {
      CString sNewString;
      sNewString.Format("%d - %s", pos+1, m_pPageNames->GetAt(pos));
      m_clPageList.AddString(sNewString);
      m_iPageCount++;
   }

   // Do initial selection
   OnPageNumberChanged();

   return TRUE;
}

void CGotoPageDlg::OnPageNumberChanged()
{
   CString sPagenum;
   int iPagenum;
   m_cePageNumber.GetWindowText(sPagenum);
   int iParsed = sscanf(sPagenum, "%d", &iPagenum);

   if (iParsed == 1 && iPagenum > 0 && iPagenum <= m_iPageCount)
   {
      m_clPageList.SetCurSel(iPagenum - 1);
      m_cePageName.EnableWindow(TRUE);
      m_cePageName.SetWindowText(m_pPageNames->GetAt(iPagenum-1));
   }
   else
   {
      m_cePageName.SetWindowText("");
      m_cePageName.EnableWindow(FALSE);
   }
}

void CGotoPageDlg::OnPageNameChanged()
{
   CString sPagename;
   m_cePageName.GetWindowText(sPagename);
   sPagename = sPagename.Left(128);

   CString sPagenum;
   int iPagenum;
   m_cePageNumber.GetWindowText(sPagenum);
   sscanf(sPagenum, "%d", &iPagenum);

   CString sNewString;
   sNewString.Format("%d - %s", iPagenum, sPagename);

   if (iPagenum > 0 && iPagenum <= m_iPageCount)
   {
      m_pPageNames->SetAt(iPagenum-1, sPagename);
      m_clPageList.DeleteString(iPagenum-1);
      m_clPageList.InsertString(iPagenum-1, sNewString);
      m_clPageList.SetCurSel(iPagenum-1);
   }
}

void CGotoPageDlg::OnPageSelect()
{
   if (m_clPageList.GetCurSel() == LB_ERR)
      return;

   CString pagenum;
   pagenum.Format("%d", m_clPageList.GetCurSel()+1);

   m_cePageNumber.SetWindowText(pagenum);
}

void CGotoPageDlg::OnPageDoubleClick()
{
   OnOK();
}

void CAnalyzeDlg::OnBnClickedHelp()
{
   ::HtmlHelp(NULL, "mmlogic.chm", HH_DISPLAY_TOPIC, (DWORD) "html\\analyze_tool.htm");
}
