// engine.cpp : implementation of the Anode class
//
// Copyright (C) 1993-1994 George Mills and Softronics, Inc. Corporation
// All rights reserved.
//

#include "stdafx.h"

Anode::Anode(int state, char *name, int drivestate)
{
   State = state;
   NextState = state;
   PrevState = state;
   Name = name;
   DriveState = drivestate;
   NextDriveState = drivestate;
   PrevDriveState = drivestate;
   LastCycle = -1;
}

void Anode::Update()
{
   PrevState = State;
   State = NextState;
   PrevDriveState = DriveState;
   DriveState = NextDriveState;
}

AKeyboardMessage::AKeyboardMessage(CLogiGate* plogigate, CLogiView* pview, BOOL bdown, UINT nchar)
{
   pLogiGate = plogigate;
   pView     = pview;
   bDown     = bdown;
   nChar     = nchar;
}

ANetworkMessage::ANetworkMessage(CLogiGate* plogigate, CLogiDoc* pdoc, LPARAM lparam, WPARAM wparam)
{
   pLogiGate = plogigate;
   pDoc      = pdoc;
   lParam    = lparam;
   wParam    = wparam;
}

AMouseMessage::AMouseMessage(CLogiGate* plogigate, CLogiView* pview, BOOL bdown, CPoint &apoint)
{
   pLogiGate = plogigate;
   pView  = pview;
   bDown  = bdown;
   aPoint = apoint;
}

LPSTR GetShellExecuteError(int iError)
{
   switch( iError )
   {
   case 0:
      return "The operating system is out of memory or resources.";
   case ERROR_FILE_NOT_FOUND:
      return "The specified file was not found.";
   case ERROR_PATH_NOT_FOUND:
      return "The specified path was not found.";
   case ERROR_BAD_FORMAT:
      return "The .EXE file is invalid (non-Win32 .EXE or error in .EXE image).";
   case SE_ERR_ACCESSDENIED:
      return "The operating system denied access to the specified file.";
   case SE_ERR_ASSOCINCOMPLETE:
      return "The filename association is incomplete or invalid.";
   case SE_ERR_DDEBUSY:
      return "The DDE transaction could not be completed because other DDE transactions were being processed.";
   case SE_ERR_DDEFAIL:
      return "The DDE transaction failed.";
   case SE_ERR_DDETIMEOUT:
      return "The DDE transaction could not be completed because the request timed out.";
   case SE_ERR_DLLNOTFOUND:
      return "The specified dynamic-link library was not found.";
      //      case SE_ERR_FNF:
      //      return "The specified file was not found.";
   case SE_ERR_NOASSOC:
      return "There is no application associated with the given filename extension.";
   case SE_ERR_OOM:
      return "There was not enough memory to complete the operation.";
      //      case SE_ERR_PNF:
      //      return "The specified path was not found.";
   case SE_ERR_SHARE:
      return "A sharing violation occurred.";
   default:
      return "Unknown reason.";
   }
}

void LaunchFile(CString &csFile)
{
   HINSTANCE hInstance = ShellExecute(AfxGetMainWnd()->GetSafeHwnd(), "open", csFile, NULL, NULL, SW_SHOWNORMAL);

   if (((int) hInstance) <= 32)
   {
      CString csMessage;
      csMessage = GetShellExecuteError((int) hInstance);
      csMessage += " ";
      csMessage += csFile;

      AfxMessageBox(csMessage);
   }
}

void CheckWindow(int *x,int *y, int *w, int *h)
{
   int MinX;
   int MinY;
   int MaxWidth;
   int MaxHeight;

   RECT MaxRect;

   SystemParametersInfo(SPI_GETWORKAREA, 0, &MaxRect, 0);

   MinX      = MaxRect.left;
   MinY      = MaxRect.top;
   MaxWidth  = MaxRect.right - MaxRect.left + 1;
   MaxHeight = MaxRect.bottom - MaxRect.top + 1;

   // sanity check window coordinates

   if (*x < MinX) *x = MinX;
   if (*y < MinY) *y = MinY;
   if (*w > MaxWidth) *w = MaxWidth;
   if (*h > MaxHeight) *h = MaxHeight;
   if ((*x+*w) > (MaxWidth+MinX)) *x = *x - (*x+*w-(MaxWidth+MinX));
   if ((*y+*h) > (MaxHeight+MinY)) *y = *y - (*y+*h-(MaxHeight+MinY));
}

void RelativeToFullPath(CString &csRelPath, CString &csBasePath, CString &csFullPath)
{
   char rdrive[_MAX_DRIVE];
   char rdir[_MAX_DIR];
   char rfname[_MAX_FNAME];
   char rext[_MAX_EXT];

   char bdrive[_MAX_DRIVE];
   char bdir[_MAX_DIR];

   char fpath[_MAX_PATH];

   char *fdrive;
   char *fdir;

   _splitpath(csRelPath, rdrive, rdir, rfname, rext);
   _splitpath(csBasePath, bdrive, bdir, NULL, NULL);

   if (strlen(rdrive) == 0) fdrive = bdrive; else fdrive = rdrive;
   if (strlen(rdir)   == 0)
   {
      fdir = bdir;
   }
   else
   {
      if (rdir[0] == '\\')
      {
         fdir = rdir;
      }
      else
      {
         fdir = bdir;
         strcat(fdir, rdir);
      }
   }

   _makepath(fpath, fdrive, fdir, rfname, rext);

   csFullPath = fpath;
}

BOOL TouchFile(CString &csFile)
{
   FILE *pFile;
   BOOL bStatus;

   bStatus = TRUE;

   pFile = fopen(csFile,"r");
   if (pFile == NULL) pFile = fopen(csFile,"w");

   //   if ((csFile == "\\NUL") || (pFile == NULL))
   //      {
   //      CString csMsg;
   //      csMsg.Format("Cannot edit %s",csFile);
   //      ::MessageBox(::GetFocus(), csMsg, "Error", MB_OK);
   //      bStatus = FALSE;
   //      }

   if (pFile != NULL) fclose(pFile);

   return bStatus;
}

BOOL MyBeep(DWORD dwFreq, DWORD dwDuration)
{
   unsigned char count_lo;
   unsigned char count_hi;
   WORD count;
   clock_t NumTicksToWait;

   if (dwFreq < 37) dwFreq = 37;

   count = (WORD) (1193180L / dwFreq);
   count_lo = LOBYTE(count);
   count_hi = HIBYTE(count);

   _asm
   {
      mov al, 0xB6
         out 0x43, al
         mov al, count_lo
         out 0x42, al
         mov al, count_hi
         out 0x42, al
         xor al, al
         in al, 0x61
         or al, 0x03
         out 0x61, al
   }

   NumTicksToWait = dwDuration + clock();
   while (NumTicksToWait > clock());

   _asm
   {
      xor al, al
         in al, 0x61
         xor al, 0x03
         out 0x61, al
   }

   return TRUE;

}

BOOL IsWindowsNT()
{
   OSVERSIONINFO VersionInformation;
   memset(&VersionInformation, 0, sizeof(OSVERSIONINFO));
   VersionInformation.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

   if (GetVersionEx(&VersionInformation))
      return VersionInformation.dwPlatformId == VER_PLATFORM_WIN32_NT;
   else
   {
      ASSERT(FALSE);
      return TRUE;
   }
}