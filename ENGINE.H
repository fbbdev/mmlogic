// Logivw.h : interface of the CLogiView class
//
// Copyright (C) 1993-1994 George Mills and Softronics, Inc. Corporation
// All rights reserved.
//

#define UNKNOWN 2
#define HI 1
#define LO 0

#define DRIVE 0
#define FLOAT 1

extern void CheckWindow(int *x,int *y, int *w, int *h);
extern void LaunchFile(CString &csFile);
extern void RelativeToFullPath(CString &csRelPath, CString &csBasePath, CString &csFullPath);
extern BOOL TouchFile(CString &csFile);
extern BOOL MyBeep(DWORD dwFreq, DWORD dwDuration);
extern BOOL IsWindowsNT();

class Anode : public CObject
{
public:

   int State;
   int NextState;
   int PrevState;
   int DriveState;
   int NextDriveState;
   int PrevDriveState;
   long LastCycle;
   CString Name;
   CObList DeviceList;
   CLogiGate* pDriverGate;

   Anode(int state, char *name, int drivestate);
   void Update();
}
;

class AKeyboardMessage : public CObject
{
public:

   CLogiGate* pLogiGate;
   CLogiView* pView;
   BOOL bDown;
   UINT nChar;

   AKeyboardMessage(CLogiGate* pLogigate, CLogiView* pView, BOOL bDown, UINT nChar);
}
;

class ANetworkMessage : public CObject
{
public:

   CLogiGate* pLogiGate;
   CLogiDoc* pDoc;
   LPARAM lParam;
   WPARAM wParam;

   ANetworkMessage(CLogiGate* pLogigate, CLogiDoc* pDoc, LPARAM lParam, WPARAM wParam);
}
;

class AMouseMessage : public CObject
{
public:

   CLogiGate* pLogiGate;
   CLogiView* pView;
   BOOL bDown;
   CPoint aPoint;

   AMouseMessage(CLogiGate* pLogigate, CLogiView* pView, BOOL bDown, CPoint &aPoint);
}
;
