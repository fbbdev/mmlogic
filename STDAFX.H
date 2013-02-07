// Copyright (C) 1993-1994 George Mills and Softronics, Inc. Corporation
// All rights reserved.
//

// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//
#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions (including VB)
#include <afxcmn.h>         // MFC common controls
#include <afxole.h>         // MFC OLE 2.0 support
#include <afxpriv.h>        // for idle-update windows message
#include <afxtempl.h>

#include <winreg.h>
#include <sys\stat.h>
#include <sys\types.h>
#include <conio.h>
#include <stdio.h>

#include <mmsystem.h>
#include <winsock.h>
#include <shlwapi.h>

#include "toolbar.h"
#include "palette.h"
#include "cdib.h"

#include "autoscrl.h"
#include "resource.h"
#include "Socket.h"
#include "Logicli.h"
#include "Logiobj.h"
#include "Undo.h"
#include "Logidoc.h"
#include "Logivw.h"
#include "Logiwire.h"
#include "Logitext.h"
#include "Logibmp.h"
#include "Robot.h"
#include "Logitool.h"
#include "network.h"
#include "dialog.h"
#include "engine.h"
#include "mainfrm.h"
#include "splitfrm.h"
#include "hlp\\mmlogic.hh"
#include "TipDlg.h"
#include "Analyze.h"

#ifndef DWORD_PTR
#define DWORD_PTR DWORD*
#endif

#include <htmlhelp.h>
#pragma comment(lib, "htmlhelp.lib")


