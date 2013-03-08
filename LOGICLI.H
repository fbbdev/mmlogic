// Logicli.h : main header file for the LOGICLI application
//
// Copyright (C) 1993-1994 George Mills and Softronics, Inc. Corporation
// All rights reserved.
//

#ifndef __AFXWIN_H__
#error include 'stdafx.h' before including this file for PCH
#endif

/////////////////////////////////////////////////////////////////////////////
// CLogiApp:
// See Logicli.cpp for the implementation of this class
//

class CLogiApp : public CWinApp
{
public:
   CLogiApp();
   BOOL m_bReadOnly;

   // Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(CLogiApp)
public:
   virtual BOOL InitInstance();
   //}}AFX_VIRTUAL
   // Overrides

   // Implementation
protected:
   //{{AFX_MSG(CLogiApp)
   afx_msg void OnAppAbout();
   afx_msg void OnHelpAboutms();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
private:
   void ShowTipAtStartup(void);
private:
   void ShowTipOfTheDay(void);
}
;

enum LogiShape
{
   selector,
   wire,
   ole,
   andgate,
   orgate,
   invertgate,
   oscillatorgate,
   ledgate,
   switchgate,
   buzzergate,
   nullgate,
   led7gate,
   asciidisplaygate,
   asciikeyboardgate,
   groundgate,
   plusgate,
   portingate,
   portoutgate,
   readfilegate,
   signalreceivergate,
   signalsendergate,
   soundwavegate,
   textgate,
   writefilegate,
   flipflopgate,
   keypadgate,
   bitmapgate,
   countergate,
   memorygate,
   breakgate,
   endgate,
   muxgate,
   bitbucketgate,
   alugate,
   randomgate,
   xorgate,
   clockgate,
   timergate,
   pagechange,
   pagecolor,
   pagegrid,
   version,
   networkgate,
   robotgate,
   selectgate,
   tristategate,
   busgate,
   unconnected,
   analyzegate,
   tapedrivegate,
   canvassize,
   simrate,
   pagename
}
;

#define XVIEWSIZE 100
#define YVIEWSIZE 100
#define MAXZOOMFACTOR 5
#define XDEFAULTDOCSIZE 800
#define YDEFAULTDOCSIZE 600
#define DEFAULTSIMRATE 100

#define BITX 49
#define BITY 49
#define BITX_BITMAP2 14
#define BITY_BITMAP2 49
#define BITX_TXT 14
#define BITY_TXT 25
#define BITX_LED 27
#define BITY_LED 98
#define BITX_NUL 17
#define BITY_NUL 17
#define BITX_KP  107
#define BITY_KP  96
#define BITX_TAP 105
#define BITY_TAP 103
#define BITX_MEM BITX
#define BITY_MEM 115
#define BITX_MEM16 BITX
#define BITY_MEM16 163
#define BITX_CNT BITX
#define BITY_CNT 73
#define BITX_RBT BITX
#define BITY_RBT 98
#define BITX_KB BITX
#define BITY_KB 61
#define BITX_ALU BITX
#define BITY_ALU 139
#define BITX_DSP 151
#define BITY_DSP 125
#define BITX_SCR 129
#define BITY_SCR 103
#define BITX_NAM 42
#define BITY_NAM 14
#define BITX_SIG 59
#define BITY_SIG 19
#define BITX_MUX BITX
#define BITY_MUX 85
#define BITX_FFPC BITX
#define BITY_FFPC 72

#define CONTACT_OUT_Y_1_1 25

#define CONTACT_IN_Y_1_1 25

#define CONTACT_IN_Y_2_1 11
#define CONTACT_IN_Y_2_2 39

#define CONTACT_IN_Y_3_1 11
#define CONTACT_IN_Y_3_2 25
#define CONTACT_IN_Y_3_3 39

#define CONTACT_IN_Y_4_1 11
#define CONTACT_IN_Y_4_2 20
#define CONTACT_IN_Y_4_3 30
#define CONTACT_IN_Y_4_4 39

#define CONTACT_NULL_X 9
#define CONTACT_NULL_Y 9

#define CONTACT_OUT_Y_5_5 40
#define CONTACT_OUT_Y_5_4 28
#define CONTACT_OUT_Y_5_3 22
#define CONTACT_OUT_Y_5_2 16
#define CONTACT_OUT_Y_5_1 10

#define CONTACT_X_IN      1

#define CONTACT_X_IN_FFPC 14

#define CONTACT_X_OUT     46
#define CONTACT_X_OUT_SIG 56
#define CONTACT_X_OUT_TAP 102
#define CONTACT_X_OUT_KP  104

#define CONTACT_Y_32 190
#define CONTACT_Y_31 184
#define CONTACT_Y_30 178
#define CONTACT_Y_29 172
#define CONTACT_Y_28 166
#define CONTACT_Y_27 160
#define CONTACT_Y_26 154
#define CONTACT_Y_25 148

#define CONTACT_Y_24 142
#define CONTACT_Y_23 136
#define CONTACT_Y_22 130
#define CONTACT_Y_21 124
#define CONTACT_Y_20 118
#define CONTACT_Y_19 112
#define CONTACT_Y_18 106
#define CONTACT_Y_17 100

#define CONTACT_Y_16 94
#define CONTACT_Y_15 88
#define CONTACT_Y_14 82
#define CONTACT_Y_13 76
#define CONTACT_Y_12 70
#define CONTACT_Y_11 64
#define CONTACT_Y_10 58
#define CONTACT_Y_9 52

#define CONTACT_Y_8 46
#define CONTACT_Y_7 40
#define CONTACT_Y_6 34
#define CONTACT_Y_5 28
#define CONTACT_Y_4 22
#define CONTACT_Y_3 16
#define CONTACT_Y_2 10
#define CONTACT_Y_1 4

#define VERSION_MAJOR 2
#define VERSION_MINOR 0

/////////////////////////////////////////////////////////////////////////////
