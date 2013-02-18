# Microsoft Developer Studio Project File - Name="Logicl32" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Logicl32 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "MMLogic.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "MMLogic.mak" CFG="Logicl32 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Logicl32 - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "Logicl32 - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Logicl32 - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
InputFileName=mmlogic.hhp
# ADD BASE CPP /nologo /MDd /W4 /Gm /GX /ZI /Od /D "WIN32" /D "_WINDOWS" /D "_DEBUG" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /GZ /c
# ADD CPP /nologo /MDd /W4 /Gm /GX /ZI /Od /D "WIN32" /D "_WINDOWS" /D "_DEBUG" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /GZ /c
# SUBTRACT CPP /WX
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
# ADD BASE RSC /l 0x409 /i "$(IntDir)" /d "_DEBUG"
# ADD RSC /l 0x409 /i "$(IntDir)" /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib WinMM.lib /nologo /subsystem:windows /debug /machine:IX86 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib WinMM.lib /nologo /subsystem:windows /debug /machine:IX86 /pdbtype:sept

!ELSEIF  "$(CFG)" == "Logicl32 - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
InputFileName=mmlogic.hhp
# ADD BASE CPP /nologo /MD /W4 /GX /Zi /D "WIN32" /D "_WINDOWS" /D "NDEBUG" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W4 /GX /Zi /D "WIN32" /D "_WINDOWS" /D "NDEBUG" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
# ADD BASE RSC /l 0x409 /i "$(IntDir)" /d "NDEBUG"
# ADD RSC /l 0x409 /i "$(IntDir)" /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib WinMM.lib /nologo /subsystem:windows /debug /machine:IX86 /out:".\Release\Mmlogic.exe" /pdbtype:sept /libpath:"C:\Program Files\HTML Help Workshop\lib" /opt:ref /opt:icf /ignore:4089
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib WinMM.lib /nologo /subsystem:windows /debug /machine:IX86 /out:".\Release\Mmlogic.exe" /pdbtype:sept /libpath:"C:\Program Files\HTML Help Workshop\lib" /opt:ref /opt:icf /ignore:4089

!ENDIF 

# Begin Target

# Name "Logicl32 - Win32 Debug"
# Name "Logicl32 - Win32 Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;def;odl;idl;hpj;bat;asm;asmx"
# Begin Source File

SOURCE=Analyze.cpp
DEP_CPP_ANALY=\
	".\Analyze.h"\
	".\Autoscrl.h"\
	".\Cdib.h"\
	".\Dialog.h"\
	".\Engine.h"\
	".\hlp\\mmlogic.hh"\
	".\Logibmp.h"\
	".\Logicli.h"\
	".\Logidoc.h"\
	".\Logiobj.h"\
	".\Logitext.h"\
	".\Logitool.h"\
	".\Logivw.h"\
	".\Logiwire.h"\
	".\Mainfrm.h"\
	".\Network.h"\
	".\Palette.h"\
	".\Robot.h"\
	".\Socket.h"\
	".\Splitfrm.h"\
	".\stdafx.h"\
	".\Tipdlg.h"\
	".\toolbar.h"\
	".\Undo.h"\
	

!IF  "$(CFG)" == "Logicl32 - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Logicl32 - Win32 Release"

# ADD CPP /nologo /GX /O2 /Yu"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=Autoscrl.cpp
DEP_CPP_AUTOS=\
	".\Analyze.h"\
	".\Autoscrl.h"\
	".\Cdib.h"\
	".\Dialog.h"\
	".\Engine.h"\
	".\hlp\\mmlogic.hh"\
	".\Logibmp.h"\
	".\Logicli.h"\
	".\Logidoc.h"\
	".\Logiobj.h"\
	".\Logitext.h"\
	".\Logitool.h"\
	".\Logivw.h"\
	".\Logiwire.h"\
	".\Mainfrm.h"\
	".\Network.h"\
	".\Palette.h"\
	".\Robot.h"\
	".\Socket.h"\
	".\Splitfrm.h"\
	".\stdafx.h"\
	".\Tipdlg.h"\
	".\toolbar.h"\
	".\Undo.h"\
	

!IF  "$(CFG)" == "Logicl32 - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /Yu"stdafx.h" /GZ

!ELSEIF  "$(CFG)" == "Logicl32 - Win32 Release"

# ADD CPP /nologo /GX /O2 /Yu"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=Cdib.cpp
DEP_CPP_CDIB_=\
	".\Analyze.h"\
	".\Autoscrl.h"\
	".\Cdib.h"\
	".\Dialog.h"\
	".\Engine.h"\
	".\hlp\\mmlogic.hh"\
	".\Logibmp.h"\
	".\Logicli.h"\
	".\Logidoc.h"\
	".\Logiobj.h"\
	".\Logitext.h"\
	".\Logitool.h"\
	".\Logivw.h"\
	".\Logiwire.h"\
	".\Mainfrm.h"\
	".\Network.h"\
	".\Palette.h"\
	".\Robot.h"\
	".\Socket.h"\
	".\Splitfrm.h"\
	".\stdafx.h"\
	".\Tipdlg.h"\
	".\toolbar.h"\
	".\Undo.h"\
	

!IF  "$(CFG)" == "Logicl32 - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /Yu"stdafx.h" /GZ

!ELSEIF  "$(CFG)" == "Logicl32 - Win32 Release"

# ADD CPP /nologo /GX /O2 /Yu"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=DIALOG.CPP
DEP_CPP_DIALO=\
	".\Analyze.h"\
	".\Autoscrl.h"\
	".\Cdib.h"\
	".\Dialog.h"\
	".\Engine.h"\
	".\hlp\\mmlogic.hh"\
	".\Logibmp.h"\
	".\Logicli.h"\
	".\Logidoc.h"\
	".\Logiobj.h"\
	".\Logitext.h"\
	".\Logitool.h"\
	".\Logivw.h"\
	".\Logiwire.h"\
	".\Mainfrm.h"\
	".\Network.h"\
	".\Palette.h"\
	".\Robot.h"\
	".\Socket.h"\
	".\Splitfrm.h"\
	".\stdafx.h"\
	".\Tipdlg.h"\
	".\toolbar.h"\
	".\Undo.h"\
	

!IF  "$(CFG)" == "Logicl32 - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /Yu"stdafx.h" /GZ

!ELSEIF  "$(CFG)" == "Logicl32 - Win32 Release"

# ADD CPP /nologo /GX /O2 /Yu"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=ENGINE.CPP
DEP_CPP_ENGIN=\
	".\Analyze.h"\
	".\Autoscrl.h"\
	".\Cdib.h"\
	".\Dialog.h"\
	".\Engine.h"\
	".\hlp\\mmlogic.hh"\
	".\Logibmp.h"\
	".\Logicli.h"\
	".\Logidoc.h"\
	".\Logiobj.h"\
	".\Logitext.h"\
	".\Logitool.h"\
	".\Logivw.h"\
	".\Logiwire.h"\
	".\Mainfrm.h"\
	".\Network.h"\
	".\Palette.h"\
	".\Robot.h"\
	".\Socket.h"\
	".\Splitfrm.h"\
	".\stdafx.h"\
	".\Tipdlg.h"\
	".\toolbar.h"\
	".\Undo.h"\
	

!IF  "$(CFG)" == "Logicl32 - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /Yu"stdafx.h" /GZ

!ELSEIF  "$(CFG)" == "Logicl32 - Win32 Release"

# ADD CPP /nologo /GX /O2 /Yu"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=logibmp.cpp
DEP_CPP_LOGIB=\
	".\Analyze.h"\
	".\Autoscrl.h"\
	".\Cdib.h"\
	".\Dialog.h"\
	".\Engine.h"\
	".\hlp\\mmlogic.hh"\
	".\Logibmp.h"\
	".\Logicli.h"\
	".\Logidoc.h"\
	".\Logiobj.h"\
	".\Logitext.h"\
	".\Logitool.h"\
	".\Logivw.h"\
	".\Logiwire.h"\
	".\Mainfrm.h"\
	".\Network.h"\
	".\Palette.h"\
	".\Robot.h"\
	".\Socket.h"\
	".\Splitfrm.h"\
	".\stdafx.h"\
	".\Tipdlg.h"\
	".\toolbar.h"\
	".\Undo.h"\
	

!IF  "$(CFG)" == "Logicl32 - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /Yu"stdafx.h" /GZ

!ELSEIF  "$(CFG)" == "Logicl32 - Win32 Release"

# ADD CPP /nologo /GX /O2 /Yu"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=LOGICLI.CPP
DEP_CPP_LOGIC=\
	".\Analyze.h"\
	".\Autoscrl.h"\
	".\Cdib.h"\
	".\Dialog.h"\
	".\Engine.h"\
	".\hlp\\mmlogic.hh"\
	".\Logibmp.h"\
	".\Logicli.h"\
	".\Logidoc.h"\
	".\Logiobj.h"\
	".\Logitext.h"\
	".\Logitool.h"\
	".\Logivw.h"\
	".\Logiwire.h"\
	".\Mainfrm.h"\
	".\Network.h"\
	".\Palette.h"\
	".\Robot.h"\
	".\Socket.h"\
	".\Splitfrm.h"\
	".\stdafx.h"\
	".\Tipdlg.h"\
	".\toolbar.h"\
	".\Undo.h"\
	

!IF  "$(CFG)" == "Logicl32 - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /Yu"stdafx.h" /GZ

!ELSEIF  "$(CFG)" == "Logicl32 - Win32 Release"

# ADD CPP /nologo /GX /O2 /Yu"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=LOGICLI.RC
# End Source File
# Begin Source File

SOURCE=LOGIDOC.CPP
DEP_CPP_LOGID=\
	".\Analyze.h"\
	".\Autoscrl.h"\
	".\Cdib.h"\
	".\Dialog.h"\
	".\Engine.h"\
	".\hlp\\mmlogic.hh"\
	".\Logibmp.h"\
	".\Logicli.h"\
	".\Logidoc.h"\
	".\Logiobj.h"\
	".\Logitext.h"\
	".\Logitool.h"\
	".\Logivw.h"\
	".\Logiwire.h"\
	".\Mainfrm.h"\
	".\Network.h"\
	".\Palette.h"\
	".\Robot.h"\
	".\Socket.h"\
	".\Splitfrm.h"\
	".\stdafx.h"\
	".\Tipdlg.h"\
	".\toolbar.h"\
	".\Undo.h"\
	

!IF  "$(CFG)" == "Logicl32 - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /Yu"stdafx.h" /GZ

!ELSEIF  "$(CFG)" == "Logicl32 - Win32 Release"

# ADD CPP /nologo /GX /O2 /Yu"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=LOGIOBJ.CPP
DEP_CPP_LOGIO=\
	".\Analyze.h"\
	".\Autoscrl.h"\
	".\Cdib.h"\
	".\Dialog.h"\
	".\Engine.h"\
	".\hlp\\mmlogic.hh"\
	".\Logibmp.h"\
	".\Logicli.h"\
	".\Logidoc.h"\
	".\Logiobj.h"\
	".\Logitext.h"\
	".\Logitool.h"\
	".\Logivw.h"\
	".\Logiwire.h"\
	".\Mainfrm.h"\
	".\Network.h"\
	".\Palette.h"\
	".\Robot.h"\
	".\Socket.h"\
	".\Splitfrm.h"\
	".\stdafx.h"\
	".\Tipdlg.h"\
	".\toolbar.h"\
	".\Undo.h"\
	

!IF  "$(CFG)" == "Logicl32 - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /Yu"stdafx.h" /GZ

!ELSEIF  "$(CFG)" == "Logicl32 - Win32 Release"

# ADD CPP /nologo /GX /O2 /Yu"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=logitext.CPP
DEP_CPP_LOGIT=\
	".\Analyze.h"\
	".\Autoscrl.h"\
	".\Cdib.h"\
	".\Dialog.h"\
	".\Engine.h"\
	".\hlp\\mmlogic.hh"\
	".\Logibmp.h"\
	".\Logicli.h"\
	".\Logidoc.h"\
	".\Logiobj.h"\
	".\Logitext.h"\
	".\Logitool.h"\
	".\Logivw.h"\
	".\Logiwire.h"\
	".\Mainfrm.h"\
	".\Network.h"\
	".\Palette.h"\
	".\Robot.h"\
	".\Socket.h"\
	".\Splitfrm.h"\
	".\stdafx.h"\
	".\Tipdlg.h"\
	".\toolbar.h"\
	".\Undo.h"\
	

!IF  "$(CFG)" == "Logicl32 - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /Yu"stdafx.h" /GZ

!ELSEIF  "$(CFG)" == "Logicl32 - Win32 Release"

# ADD CPP /nologo /GX /O2 /Yu"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=LOGITOOL.CPP
DEP_CPP_LOGITO=\
	".\Analyze.h"\
	".\Autoscrl.h"\
	".\Cdib.h"\
	".\Dialog.h"\
	".\Engine.h"\
	".\hlp\\mmlogic.hh"\
	".\Logibmp.h"\
	".\Logicli.h"\
	".\Logidoc.h"\
	".\Logiobj.h"\
	".\Logitext.h"\
	".\Logitool.h"\
	".\Logivw.h"\
	".\Logiwire.h"\
	".\Mainfrm.h"\
	".\Network.h"\
	".\Palette.h"\
	".\Robot.h"\
	".\Socket.h"\
	".\Splitfrm.h"\
	".\stdafx.h"\
	".\Tipdlg.h"\
	".\toolbar.h"\
	".\Undo.h"\
	

!IF  "$(CFG)" == "Logicl32 - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /Yu"stdafx.h" /GZ

!ELSEIF  "$(CFG)" == "Logicl32 - Win32 Release"

# ADD CPP /nologo /GX /O2 /Yu"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=LOGIVW.CPP
DEP_CPP_LOGIV=\
	".\Analyze.h"\
	".\Autoscrl.h"\
	".\Cdib.h"\
	".\Dialog.h"\
	".\Engine.h"\
	".\hlp\\mmlogic.hh"\
	".\Logibmp.h"\
	".\Logicli.h"\
	".\Logidoc.h"\
	".\Logiobj.h"\
	".\Logitext.h"\
	".\Logitool.h"\
	".\Logivw.h"\
	".\Logiwire.h"\
	".\Mainfrm.h"\
	".\Network.h"\
	".\Palette.h"\
	".\Robot.h"\
	".\Socket.h"\
	".\Splitfrm.h"\
	".\stdafx.h"\
	".\Tipdlg.h"\
	".\toolbar.h"\
	".\Undo.h"\
	

!IF  "$(CFG)" == "Logicl32 - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /Yu"stdafx.h" /GZ

!ELSEIF  "$(CFG)" == "Logicl32 - Win32 Release"

# ADD CPP /nologo /GX /O2 /Yu"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=LOGIWIRE.CPP
DEP_CPP_LOGIW=\
	".\Analyze.h"\
	".\Autoscrl.h"\
	".\Cdib.h"\
	".\Dialog.h"\
	".\Engine.h"\
	".\hlp\\mmlogic.hh"\
	".\Logibmp.h"\
	".\Logicli.h"\
	".\Logidoc.h"\
	".\Logiobj.h"\
	".\Logitext.h"\
	".\Logitool.h"\
	".\Logivw.h"\
	".\Logiwire.h"\
	".\Mainfrm.h"\
	".\Network.h"\
	".\Palette.h"\
	".\Robot.h"\
	".\Socket.h"\
	".\Splitfrm.h"\
	".\stdafx.h"\
	".\Tipdlg.h"\
	".\toolbar.h"\
	".\Undo.h"\
	

!IF  "$(CFG)" == "Logicl32 - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /Yu"stdafx.h" /GZ

!ELSEIF  "$(CFG)" == "Logicl32 - Win32 Release"

# ADD CPP /nologo /GX /O2 /Yu"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=MAINFRM.CPP
DEP_CPP_MAINF=\
	".\Analyze.h"\
	".\Autoscrl.h"\
	".\Cdib.h"\
	".\Dialog.h"\
	".\Engine.h"\
	".\hlp\\mmlogic.hh"\
	".\Logibmp.h"\
	".\Logicli.h"\
	".\Logidoc.h"\
	".\Logiobj.h"\
	".\Logitext.h"\
	".\Logitool.h"\
	".\Logivw.h"\
	".\Logiwire.h"\
	".\Mainfrm.h"\
	".\Network.h"\
	".\Palette.h"\
	".\Robot.h"\
	".\Socket.h"\
	".\Splitfrm.h"\
	".\stdafx.h"\
	".\Tipdlg.h"\
	".\toolbar.h"\
	".\Undo.h"\
	
NODEP_CPP_MAINF=\
	".\tmlhelp.h"\
	

!IF  "$(CFG)" == "Logicl32 - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /Yu"stdafx.h" /GZ

!ELSEIF  "$(CFG)" == "Logicl32 - Win32 Release"

# ADD CPP /nologo /GX /O2 /Yu"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=network.cpp
DEP_CPP_NETWO=\
	".\Analyze.h"\
	".\Autoscrl.h"\
	".\Cdib.h"\
	".\Dialog.h"\
	".\Engine.h"\
	".\hlp\\mmlogic.hh"\
	".\Logibmp.h"\
	".\Logicli.h"\
	".\Logidoc.h"\
	".\Logiobj.h"\
	".\Logitext.h"\
	".\Logitool.h"\
	".\Logivw.h"\
	".\Logiwire.h"\
	".\Mainfrm.h"\
	".\Network.h"\
	".\Palette.h"\
	".\Robot.h"\
	".\Socket.h"\
	".\Splitfrm.h"\
	".\stdafx.h"\
	".\Tipdlg.h"\
	".\toolbar.h"\
	".\Undo.h"\
	

!IF  "$(CFG)" == "Logicl32 - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /Yu"stdafx.h" /GZ

!ELSEIF  "$(CFG)" == "Logicl32 - Win32 Release"

# ADD CPP /nologo /GX /O2 /Yu"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=palette.CPP
DEP_CPP_PALET=\
	".\Analyze.h"\
	".\Autoscrl.h"\
	".\Cdib.h"\
	".\Dialog.h"\
	".\Engine.h"\
	".\hlp\\mmlogic.hh"\
	".\Logibmp.h"\
	".\Logicli.h"\
	".\Logidoc.h"\
	".\Logiobj.h"\
	".\Logitext.h"\
	".\Logitool.h"\
	".\Logivw.h"\
	".\Logiwire.h"\
	".\Mainfrm.h"\
	".\Network.h"\
	".\Palette.h"\
	".\Robot.h"\
	".\Socket.h"\
	".\Splitfrm.h"\
	".\stdafx.h"\
	".\Tipdlg.h"\
	".\toolbar.h"\
	".\Undo.h"\
	

!IF  "$(CFG)" == "Logicl32 - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /Yu"stdafx.h" /GZ

!ELSEIF  "$(CFG)" == "Logicl32 - Win32 Release"

# ADD CPP /nologo /GX /O2 /Yu"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=robot.CPP
DEP_CPP_ROBOT=\
	".\Analyze.h"\
	".\Autoscrl.h"\
	".\Cdib.h"\
	".\Dialog.h"\
	".\Engine.h"\
	".\hlp\\mmlogic.hh"\
	".\Logibmp.h"\
	".\Logicli.h"\
	".\Logidoc.h"\
	".\Logiobj.h"\
	".\Logitext.h"\
	".\Logitool.h"\
	".\Logivw.h"\
	".\Logiwire.h"\
	".\Mainfrm.h"\
	".\Network.h"\
	".\Palette.h"\
	".\Robot.h"\
	".\Socket.h"\
	".\Splitfrm.h"\
	".\stdafx.h"\
	".\Tipdlg.h"\
	".\toolbar.h"\
	".\Undo.h"\
	

!IF  "$(CFG)" == "Logicl32 - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /Yu"stdafx.h" /GZ

!ELSEIF  "$(CFG)" == "Logicl32 - Win32 Release"

# ADD CPP /nologo /GX /O2 /Yu"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=socket.cpp
DEP_CPP_SOCKE=\
	".\Analyze.h"\
	".\Autoscrl.h"\
	".\Cdib.h"\
	".\Dialog.h"\
	".\Engine.h"\
	".\hlp\\mmlogic.hh"\
	".\Logibmp.h"\
	".\Logicli.h"\
	".\Logidoc.h"\
	".\Logiobj.h"\
	".\Logitext.h"\
	".\Logitool.h"\
	".\Logivw.h"\
	".\Logiwire.h"\
	".\Mainfrm.h"\
	".\Network.h"\
	".\Palette.h"\
	".\Robot.h"\
	".\Socket.h"\
	".\Splitfrm.h"\
	".\stdafx.h"\
	".\Tipdlg.h"\
	".\toolbar.h"\
	".\Undo.h"\
	

!IF  "$(CFG)" == "Logicl32 - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /Yu"stdafx.h" /GZ

!ELSEIF  "$(CFG)" == "Logicl32 - Win32 Release"

# ADD CPP /nologo /GX /O2 /Yu"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=SPLITFRM.CPP
DEP_CPP_SPLIT=\
	".\Analyze.h"\
	".\Autoscrl.h"\
	".\Cdib.h"\
	".\Dialog.h"\
	".\Engine.h"\
	".\hlp\\mmlogic.hh"\
	".\Logibmp.h"\
	".\Logicli.h"\
	".\Logidoc.h"\
	".\Logiobj.h"\
	".\Logitext.h"\
	".\Logitool.h"\
	".\Logivw.h"\
	".\Logiwire.h"\
	".\Mainfrm.h"\
	".\Network.h"\
	".\Palette.h"\
	".\Robot.h"\
	".\Socket.h"\
	".\Splitfrm.h"\
	".\stdafx.h"\
	".\Tipdlg.h"\
	".\toolbar.h"\
	".\Undo.h"\
	

!IF  "$(CFG)" == "Logicl32 - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /Yu"stdafx.h" /GZ

!ELSEIF  "$(CFG)" == "Logicl32 - Win32 Release"

# ADD CPP /nologo /GX /O2 /Yu"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=STDAFX.CPP
DEP_CPP_STDAF=\
	".\Analyze.h"\
	".\Autoscrl.h"\
	".\Cdib.h"\
	".\Dialog.h"\
	".\Engine.h"\
	".\hlp\\mmlogic.hh"\
	".\Logibmp.h"\
	".\Logicli.h"\
	".\Logidoc.h"\
	".\Logiobj.h"\
	".\Logitext.h"\
	".\Logitool.h"\
	".\Logivw.h"\
	".\Logiwire.h"\
	".\Mainfrm.h"\
	".\Network.h"\
	".\Palette.h"\
	".\Robot.h"\
	".\Socket.h"\
	".\Splitfrm.h"\
	".\stdafx.h"\
	".\Tipdlg.h"\
	".\toolbar.h"\
	".\Undo.h"\
	

!IF  "$(CFG)" == "Logicl32 - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /Yc"stdafx.h" /GZ

!ELSEIF  "$(CFG)" == "Logicl32 - Win32 Release"

# ADD CPP /nologo /GX /O2 /Yc"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=TipDlg.cpp
DEP_CPP_TIPDL=\
	".\Analyze.h"\
	".\Autoscrl.h"\
	".\Cdib.h"\
	".\Dialog.h"\
	".\Engine.h"\
	".\hlp\\mmlogic.hh"\
	".\Logibmp.h"\
	".\Logicli.h"\
	".\Logidoc.h"\
	".\Logiobj.h"\
	".\Logitext.h"\
	".\Logitool.h"\
	".\Logivw.h"\
	".\Logiwire.h"\
	".\Mainfrm.h"\
	".\Network.h"\
	".\Palette.h"\
	".\Robot.h"\
	".\Socket.h"\
	".\Splitfrm.h"\
	".\stdafx.h"\
	".\Tipdlg.h"\
	".\toolbar.h"\
	".\Undo.h"\
	

!IF  "$(CFG)" == "Logicl32 - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /Yu"stdafx.h" /GZ

!ELSEIF  "$(CFG)" == "Logicl32 - Win32 Release"

# ADD CPP /nologo /GX /O2 /Yu"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=toolbar.cpp
DEP_CPP_TOOLB=\
	".\Analyze.h"\
	".\Autoscrl.h"\
	".\Cdib.h"\
	".\Dialog.h"\
	".\Engine.h"\
	".\hlp\\mmlogic.hh"\
	".\Logibmp.h"\
	".\Logicli.h"\
	".\Logidoc.h"\
	".\Logiobj.h"\
	".\Logitext.h"\
	".\Logitool.h"\
	".\Logivw.h"\
	".\Logiwire.h"\
	".\Mainfrm.h"\
	".\Network.h"\
	".\Palette.h"\
	".\Robot.h"\
	".\Socket.h"\
	".\Splitfrm.h"\
	".\stdafx.h"\
	".\Tipdlg.h"\
	".\toolbar.h"\
	".\Undo.h"\
	

!IF  "$(CFG)" == "Logicl32 - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /Yu"stdafx.h" /GZ

!ELSEIF  "$(CFG)" == "Logicl32 - Win32 Release"

# ADD CPP /nologo /GX /O2 /Yu"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=Undo.cpp
DEP_CPP_UNDO_=\
	".\Analyze.h"\
	".\Autoscrl.h"\
	".\Cdib.h"\
	".\Dialog.h"\
	".\Engine.h"\
	".\hlp\\mmlogic.hh"\
	".\Logibmp.h"\
	".\Logicli.h"\
	".\Logidoc.h"\
	".\Logiobj.h"\
	".\Logitext.h"\
	".\Logitool.h"\
	".\Logivw.h"\
	".\Logiwire.h"\
	".\Mainfrm.h"\
	".\Network.h"\
	".\Palette.h"\
	".\Robot.h"\
	".\Socket.h"\
	".\Splitfrm.h"\
	".\stdafx.h"\
	".\Tipdlg.h"\
	".\toolbar.h"\
	".\Undo.h"\
	

!IF  "$(CFG)" == "Logicl32 - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /Yu"stdafx.h" /GZ

!ELSEIF  "$(CFG)" == "Logicl32 - Win32 Release"

# ADD CPP /nologo /GX /O2 /Yu"stdafx.h"

!ENDIF 

# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;inc;xsd"
# Begin Source File

SOURCE=Analyze.h
# End Source File
# Begin Source File

SOURCE=Autoscrl.h
# End Source File
# Begin Source File

SOURCE=Cdib.h
# End Source File
# Begin Source File

SOURCE=Dialog.h
# End Source File
# Begin Source File

SOURCE=Engine.h
# End Source File
# Begin Source File

SOURCE=Logibmp.h
# End Source File
# Begin Source File

SOURCE=Logicli.h
# End Source File
# Begin Source File

SOURCE=Logidoc.h
# End Source File
# Begin Source File

SOURCE=Logiobj.h
# End Source File
# Begin Source File

SOURCE=Logitext.h
# End Source File
# Begin Source File

SOURCE=Logitool.h
# End Source File
# Begin Source File

SOURCE=Logivw.h
# End Source File
# Begin Source File

SOURCE=Logiwire.h
# End Source File
# Begin Source File

SOURCE=Mainfrm.h
# End Source File
# Begin Source File

SOURCE=.\MMLogic.h
# End Source File
# Begin Source File

SOURCE=Network.h
# End Source File
# Begin Source File

SOURCE=Palette.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h

!IF  "$(CFG)" == "Logicl32 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Generating map file for help compiler...
InputPath=.\Resource.h

"hlp\HTMLDefines.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	echo // Generated Help Map file.  Used by MMLogic.HHP. > "hlp\HTMLDefines.h" 
	echo. > "hlp\HTMLDefines.h" 
	echo // Commands (ID_* and IDM_*) >> "hlp\HTMLDefines.h" 
	makehm /h ID_,HID_,0x10000 IDM_,HIDM_,0x10000 "$(InputFileName)" >> "hlp\HTMLDefines.h" 
	echo. >> "hlp\HTMLDefines.h" 
	echo // Prompts (IDP_*) >> "hlp\HTMLDefines.h" 
	makehm /h IDP_,HIDP_,0x30000 "$(InputFileName)" >> "hlp\HTMLDefines.h" 
	echo. >> "hlp\HTMLDefines.h" 
	echo // Resources (IDR_*) >> "hlp\HTMLDefines.h" 
	makehm /h IDR_,HIDR_,0x20000 "$(InputFileName)" >> "hlp\HTMLDefines.h" 
	echo. >> "hlp\HTMLDefines.h" 
	echo // Dialogs (IDD_*) >> "hlp\HTMLDefines.h" 
	makehm /h IDD_,HIDD_,0x20000 "$(InputFileName)" >> "hlp\HTMLDefines.h" 
	echo. >> "hlp\HTMLDefines.h" 
	echo // Frame Controls (IDW_*) >> "hlp\HTMLDefines.h" 
	makehm /h /a afxhh.h IDW_,HIDW_,0x50000 "$(InputFileName)" >> "hlp\HTMLDefines.h" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "Logicl32 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Generating map file for help compiler...
InputPath=.\Resource.h

"hlp\HTMLDefines.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	echo // Generated Help Map file.  Used by MMLogic.HHP. > "hlp\HTMLDefines.h" 
	echo. > "hlp\HTMLDefines.h" 
	echo // Commands (ID_* and IDM_*) >> "hlp\HTMLDefines.h" 
	makehm /h ID_,HID_,0x10000 IDM_,HIDM_,0x10000 "$(InputFileName)" >> "hlp\HTMLDefines.h" 
	echo. >> "hlp\HTMLDefines.h" 
	echo // Prompts (IDP_*) >> "hlp\HTMLDefines.h" 
	makehm /h IDP_,HIDP_,0x30000 "$(InputFileName)" >> "hlp\HTMLDefines.h" 
	echo. >> "hlp\HTMLDefines.h" 
	echo // Resources (IDR_*) >> "hlp\HTMLDefines.h" 
	makehm /h IDR_,HIDR_,0x20000 "$(InputFileName)" >> "hlp\HTMLDefines.h" 
	echo. >> "hlp\HTMLDefines.h" 
	echo // Dialogs (IDD_*) >> "hlp\HTMLDefines.h" 
	makehm /h IDD_,HIDD_,0x20000 "$(InputFileName)" >> "hlp\HTMLDefines.h" 
	echo. >> "hlp\HTMLDefines.h" 
	echo // Frame Controls (IDW_*) >> "hlp\HTMLDefines.h" 
	makehm /h /a afxhh.h IDW_,HIDW_,0x50000 "$(InputFileName)" >> "hlp\HTMLDefines.h" 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=Robot.h
# End Source File
# Begin Source File

SOURCE=Socket.h
# End Source File
# Begin Source File

SOURCE=Splitfrm.h
# End Source File
# Begin Source File

SOURCE=.\stdafx.h
# End Source File
# Begin Source File

SOURCE=Stdafx.h
# End Source File
# Begin Source File

SOURCE=Tipdlg.h
# End Source File
# Begin Source File

SOURCE=toolbar.h
# End Source File
# Begin Source File

SOURCE=Undo.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "rc;ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe;resx"
# Begin Source File

SOURCE=RES\ALU.BMP
# End Source File
# Begin Source File

SOURCE=RES\ALUB.BMP
# End Source File
# Begin Source File

SOURCE=RES\ANALYZE.BMP
# End Source File
# Begin Source File

SOURCE=RES\AND2.BMP
# End Source File
# Begin Source File

SOURCE=RES\AND2B.BMP
# End Source File
# Begin Source File

SOURCE=RES\AND3.BMP
# End Source File
# Begin Source File

SOURCE=RES\AND3B.BMP
# End Source File
# Begin Source File

SOURCE=RES\AND4.BMP
# End Source File
# Begin Source File

SOURCE=RES\AND4B.BMP
# End Source File
# Begin Source File

SOURCE=RES\BITBUCK.BMP
# End Source File
# Begin Source File

SOURCE=RES\BITBUCKB.BMP
# End Source File
# Begin Source File

SOURCE=Res\BITMAP1.BMP
# End Source File
# Begin Source File

SOURCE=RES\BMP.BMP
# End Source File
# Begin Source File

SOURCE=RES\BMPB.BMP
# End Source File
# Begin Source File

SOURCE=RES\BMPSB.BMP
# End Source File
# Begin Source File

SOURCE=RES\BREAK.BMP
# End Source File
# Begin Source File

SOURCE=RES\BREAKB.BMP
# End Source File
# Begin Source File

SOURCE=RES\BREAKON.BMP
# End Source File
# Begin Source File

SOURCE=RES\BUFFER.BMP
# End Source File
# Begin Source File

SOURCE=RES\BUFFERB.BMP
# End Source File
# Begin Source File

SOURCE=RES\BUS_2.BMP
# End Source File
# Begin Source File

SOURCE=RES\BUS_2B.BMP
# End Source File
# Begin Source File

SOURCE=RES\BUS_4.BMP
# End Source File
# Begin Source File

SOURCE=RES\BUS_4B.BMP
# End Source File
# Begin Source File

SOURCE=RES\BUS_8.BMP
# End Source File
# Begin Source File

SOURCE=RES\BUS_8B.BMP
# End Source File
# Begin Source File

SOURCE=RES\BUZZER_F.BMP
# End Source File
# Begin Source File

SOURCE=RES\BUZZER_O.BMP
# End Source File
# Begin Source File

SOURCE=RES\BUZZERFB.BMP
# End Source File
# Begin Source File

SOURCE=RES\CLOCK.BMP
# End Source File
# Begin Source File

SOURCE=RES\CLOCKB.BMP
# End Source File
# Begin Source File

SOURCE=Res\Count4.bmp
# End Source File
# Begin Source File

SOURCE=Res\Count4b.bmp
# End Source File
# Begin Source File

SOURCE=Res\Count8.bmp
# End Source File
# Begin Source File

SOURCE=Res\Count8b.bmp
# End Source File
# Begin Source File

SOURCE=RES\COUNTER.BMP
# End Source File
# Begin Source File

SOURCE=Res\Counter8.bmp
# End Source File
# Begin Source File

SOURCE=RES\COUNTERB.BMP
# End Source File
# Begin Source File

SOURCE=RES\DEMUX12.BMP
# End Source File
# Begin Source File

SOURCE=RES\DEMUX12B.BMP
# End Source File
# Begin Source File

SOURCE=RES\DEMUX24.BMP
# End Source File
# Begin Source File

SOURCE=RES\DEMUX24B.BMP
# End Source File
# Begin Source File

SOURCE=RES\DEMUX38.BMP
# End Source File
# Begin Source File

SOURCE=RES\DEMUX38B.BMP
# End Source File
# Begin Source File

SOURCE=RES\DISPLAY.BMP
# End Source File
# Begin Source File

SOURCE=RES\DISPLAYB.BMP
# End Source File
# Begin Source File

SOURCE=RES\FF_CRS.BMP
# End Source File
# Begin Source File

SOURCE=Res\FF_CRS_PC.BMP
# End Source File
# Begin Source File

SOURCE=Res\FF_CRS_PCB.BMP
# End Source File
# Begin Source File

SOURCE=RES\FF_CRSB.BMP
# End Source File
# Begin Source File

SOURCE=RES\FF_CRSE.BMP
# End Source File
# Begin Source File

SOURCE=Res\FF_CRSE_PC.BMP
# End Source File
# Begin Source File

SOURCE=Res\FF_CRSE_PCB.BMP
# End Source File
# Begin Source File

SOURCE=RES\FF_CRSEB.BMP
# End Source File
# Begin Source File

SOURCE=RES\FF_DL.BMP
# End Source File
# Begin Source File

SOURCE=Res\FF_DL_PC.BMP
# End Source File
# Begin Source File

SOURCE=Res\FF_DL_PCB.BMP
# End Source File
# Begin Source File

SOURCE=RES\FF_DLB.BMP
# End Source File
# Begin Source File

SOURCE=RES\FF_DLE.BMP
# End Source File
# Begin Source File

SOURCE=Res\FF_DLE_PC.BMP
# End Source File
# Begin Source File

SOURCE=Res\FF_DLE_PCB.BMP
# End Source File
# Begin Source File

SOURCE=RES\FF_DLEB.BMP
# End Source File
# Begin Source File

SOURCE=RES\FF_JK.BMP
# End Source File
# Begin Source File

SOURCE=Res\FF_JK_PC.BMP
# End Source File
# Begin Source File

SOURCE=Res\FF_JK_PCB.BMP
# End Source File
# Begin Source File

SOURCE=RES\FF_JKB.BMP
# End Source File
# Begin Source File

SOURCE=RES\FF_JKE.BMP
# End Source File
# Begin Source File

SOURCE=Res\FF_JKE_PC.BMP
# End Source File
# Begin Source File

SOURCE=Res\FF_JKE_PCB.BMP
# End Source File
# Begin Source File

SOURCE=RES\FF_JKEB.BMP
# End Source File
# Begin Source File

SOURCE=RES\FF_MSDL.BMP
# End Source File
# Begin Source File

SOURCE=Res\FF_MSDL_PC.BMP
# End Source File
# Begin Source File

SOURCE=Res\FF_MSDL_PCB.BMP
# End Source File
# Begin Source File

SOURCE=RES\FF_MSDLB.BMP
# End Source File
# Begin Source File

SOURCE=RES\FF_MSDLE.BMP
# End Source File
# Begin Source File

SOURCE=Res\FF_MSDLE_PC.BMP
# End Source File
# Begin Source File

SOURCE=Res\FF_MSDLE_PCB.BMP
# End Source File
# Begin Source File

SOURCE=RES\FF_MSRS.BMP
# End Source File
# Begin Source File

SOURCE=Res\FF_MSRS_PC.BMP
# End Source File
# Begin Source File

SOURCE=Res\FF_MSRS_PCB.BMP
# End Source File
# Begin Source File

SOURCE=RES\FF_MSRSB.BMP
# End Source File
# Begin Source File

SOURCE=RES\FF_MSRSE.BMP
# End Source File
# Begin Source File

SOURCE=Res\FF_MSRSE_PC.BMP
# End Source File
# Begin Source File

SOURCE=Res\FF_MSRSE_PCB.BMP
# End Source File
# Begin Source File

SOURCE=RES\FF_RS.BMP
# End Source File
# Begin Source File

SOURCE=Res\FF_RS_PC.BMP
# End Source File
# Begin Source File

SOURCE=Res\FF_RS_PCB.BMP
# End Source File
# Begin Source File

SOURCE=RES\FF_RSB.BMP
# End Source File
# Begin Source File

SOURCE=RES\FFMSDLEB.BMP
# End Source File
# Begin Source File

SOURCE=RES\FFMSRSEB.BMP
# End Source File
# Begin Source File

SOURCE=RES\FILE_IN.BMP
# End Source File
# Begin Source File

SOURCE=RES\FILE_INB.BMP
# End Source File
# Begin Source File

SOURCE=RES\FILE_OUT.BMP
# End Source File
# Begin Source File

SOURCE=RES\FILEO_IN.BMP
# End Source File
# Begin Source File

SOURCE=RES\FILEO_OU.BMP
# End Source File
# Begin Source File

SOURCE=RES\FILEOUTB.BMP
# End Source File
# Begin Source File

SOURCE=RES\GROUND.BMP
# End Source File
# Begin Source File

SOURCE=RES\GROUNDB.BMP
# End Source File
# Begin Source File

SOURCE=RES\HELP.BMP
# End Source File
# Begin Source File

SOURCE=RES\INVERT.BMP
# End Source File
# Begin Source File

SOURCE=RES\INVERTB.BMP
# End Source File
# Begin Source File

SOURCE=RES\IO_IN.BMP
# End Source File
# Begin Source File

SOURCE=RES\IO_INB.BMP
# End Source File
# Begin Source File

SOURCE=RES\IO_OUT.BMP
# End Source File
# Begin Source File

SOURCE=RES\IO_OUTB.BMP
# End Source File
# Begin Source File

SOURCE=Res\JK_PCB.BMP
# End Source File
# Begin Source File

SOURCE=RES\KEYBRDF.BMP
# End Source File
# Begin Source File

SOURCE=RES\KEYBRDFB.BMP
# End Source File
# Begin Source File

SOURCE=RES\KEYBRDO.BMP
# End Source File
# Begin Source File

SOURCE=RES\KEYPAD.BMP
# End Source File
# Begin Source File

SOURCE=RES\KEYPAD_0.BMP
# End Source File
# Begin Source File

SOURCE=RES\KEYPAD_1.BMP
# End Source File
# Begin Source File

SOURCE=RES\KEYPAD_2.BMP
# End Source File
# Begin Source File

SOURCE=RES\KEYPAD_3.BMP
# End Source File
# Begin Source File

SOURCE=RES\KEYPAD_4.BMP
# End Source File
# Begin Source File

SOURCE=RES\KEYPAD_5.BMP
# End Source File
# Begin Source File

SOURCE=RES\KEYPAD_6.BMP
# End Source File
# Begin Source File

SOURCE=RES\KEYPAD_7.BMP
# End Source File
# Begin Source File

SOURCE=RES\KEYPAD_8.BMP
# End Source File
# Begin Source File

SOURCE=RES\KEYPAD_9.BMP
# End Source File
# Begin Source File

SOURCE=RES\KEYPAD_A.BMP
# End Source File
# Begin Source File

SOURCE=RES\KEYPAD_B.BMP
# End Source File
# Begin Source File

SOURCE=RES\KEYPAD_C.BMP
# End Source File
# Begin Source File

SOURCE=RES\KEYPAD_D.BMP
# End Source File
# Begin Source File

SOURCE=RES\KEYPAD_E.BMP
# End Source File
# Begin Source File

SOURCE=RES\KEYPAD_F.BMP
# End Source File
# Begin Source File

SOURCE=RES\KEYPADB.BMP
# End Source File
# Begin Source File

SOURCE=RES\LED4_OFF.BMP
# End Source File
# Begin Source File

SOURCE=RES\LED4_ON0.BMP
# End Source File
# Begin Source File

SOURCE=RES\LED4_ON1.BMP
# End Source File
# Begin Source File

SOURCE=RES\LED4_ON2.BMP
# End Source File
# Begin Source File

SOURCE=RES\LED4_ON3.BMP
# End Source File
# Begin Source File

SOURCE=RES\LED4_ON4.BMP
# End Source File
# Begin Source File

SOURCE=RES\LED4_ON5.BMP
# End Source File
# Begin Source File

SOURCE=RES\LED4_ON6.BMP
# End Source File
# Begin Source File

SOURCE=RES\LED4_ON7.BMP
# End Source File
# Begin Source File

SOURCE=RES\LED4_ON8.BMP
# End Source File
# Begin Source File

SOURCE=RES\LED4_ON9.BMP
# End Source File
# Begin Source File

SOURCE=RES\LED4_ONA.BMP
# End Source File
# Begin Source File

SOURCE=RES\LED4_ONB.BMP
# End Source File
# Begin Source File

SOURCE=RES\LED4_ONC.BMP
# End Source File
# Begin Source File

SOURCE=RES\LED4_OND.BMP
# End Source File
# Begin Source File

SOURCE=RES\LED4_ONE.BMP
# End Source File
# Begin Source File

SOURCE=RES\LED4_ONF.BMP
# End Source File
# Begin Source File

SOURCE=RES\LED4_ONU.BMP
# End Source File
# Begin Source File

SOURCE=RES\LED4OFFB.BMP
# End Source File
# Begin Source File

SOURCE=RES\LED4PON0.BMP
# End Source File
# Begin Source File

SOURCE=RES\LED4PON1.BMP
# End Source File
# Begin Source File

SOURCE=RES\LED4PON2.BMP
# End Source File
# Begin Source File

SOURCE=RES\LED4PON3.BMP
# End Source File
# Begin Source File

SOURCE=RES\LED4PON4.BMP
# End Source File
# Begin Source File

SOURCE=RES\LED4PON5.BMP
# End Source File
# Begin Source File

SOURCE=RES\LED4PON6.BMP
# End Source File
# Begin Source File

SOURCE=RES\LED4PON7.BMP
# End Source File
# Begin Source File

SOURCE=RES\LED4PON8.BMP
# End Source File
# Begin Source File

SOURCE=RES\LED4PON9.BMP
# End Source File
# Begin Source File

SOURCE=RES\LED4PONA.BMP
# End Source File
# Begin Source File

SOURCE=RES\LED4PONB.BMP
# End Source File
# Begin Source File

SOURCE=RES\LED4PONC.BMP
# End Source File
# Begin Source File

SOURCE=RES\LED4POND.BMP
# End Source File
# Begin Source File

SOURCE=RES\LED4PONE.BMP
# End Source File
# Begin Source File

SOURCE=RES\LED4PONF.BMP
# End Source File
# Begin Source File

SOURCE=RES\LED4PONU.BMP
# End Source File
# Begin Source File

SOURCE=RES\LED7_OF0.BMP
# End Source File
# Begin Source File

SOURCE=RES\LED7_OF1.BMP
# End Source File
# Begin Source File

SOURCE=RES\LED7_OF2.BMP
# End Source File
# Begin Source File

SOURCE=RES\LED7_OF3.BMP
# End Source File
# Begin Source File

SOURCE=RES\LED7_OF4.BMP
# End Source File
# Begin Source File

SOURCE=RES\LED7_OF5.BMP
# End Source File
# Begin Source File

SOURCE=RES\LED7_OF6.BMP
# End Source File
# Begin Source File

SOURCE=RES\LED7_OF7.BMP
# End Source File
# Begin Source File

SOURCE=RES\LED7_OFF.BMP
# End Source File
# Begin Source File

SOURCE=RES\LED7_ON0.BMP
# End Source File
# Begin Source File

SOURCE=RES\LED7_ON1.BMP
# End Source File
# Begin Source File

SOURCE=RES\LED7_ON2.BMP
# End Source File
# Begin Source File

SOURCE=RES\LED7_ON3.BMP
# End Source File
# Begin Source File

SOURCE=RES\LED7_ON4.BMP
# End Source File
# Begin Source File

SOURCE=RES\LED7_ON5.BMP
# End Source File
# Begin Source File

SOURCE=RES\LED7_ON6.BMP
# End Source File
# Begin Source File

SOURCE=RES\LED7_ON7.BMP
# End Source File
# Begin Source File

SOURCE=res\led7offb.bmp
# End Source File
# Begin Source File

SOURCE=RES\LED_OFF.BMP
# End Source File
# Begin Source File

SOURCE=RES\LED_ONG.BMP
# End Source File
# Begin Source File

SOURCE=RES\LED_ONGB.BMP
# End Source File
# Begin Source File

SOURCE=RES\LED_ONR.BMP
# End Source File
# Begin Source File

SOURCE=RES\LED_ONRB.BMP
# End Source File
# Begin Source File

SOURCE=RES\LED_ONY.BMP
# End Source File
# Begin Source File

SOURCE=RES\LED_ONYB.BMP
# End Source File
# Begin Source File

SOURCE=RES\LED_UNKN.BMP
# End Source File
# Begin Source File

SOURCE=res\litebulb.bmp
# End Source File
# Begin Source File

SOURCE=res\LOGICLI.ICO
# End Source File
# Begin Source File

SOURCE=res\LOGICLI.RC2
# End Source File
# Begin Source File

SOURCE=RES\LOGIDOC.ICO
# End Source File
# Begin Source File

SOURCE=RES\MEMORY.BMP
# End Source File
# Begin Source File

SOURCE=Res\MEMORY16.BMP
# End Source File
# Begin Source File

SOURCE=Res\MEMORY16B.BMP
# End Source File
# Begin Source File

SOURCE=res\memoryb.bmp
# End Source File
# Begin Source File

SOURCE=RES\MOUSE.BMP
# End Source File
# Begin Source File

SOURCE=RES\MUX2TO1.BMP
# End Source File
# Begin Source File

SOURCE=RES\MUX2TO1B.BMP
# End Source File
# Begin Source File

SOURCE=RES\MUX4TO1.BMP
# End Source File
# Begin Source File

SOURCE=RES\MUX4TO1B.BMP
# End Source File
# Begin Source File

SOURCE=RES\MUX8TO1.BMP
# End Source File
# Begin Source File

SOURCE=RES\MUX8TO1B.BMP
# End Source File
# Begin Source File

SOURCE=RES\NAND2.BMP
# End Source File
# Begin Source File

SOURCE=res\nand2b.bmp
# End Source File
# Begin Source File

SOURCE=RES\NAND3.BMP
# End Source File
# Begin Source File

SOURCE=res\nand3b.bmp
# End Source File
# Begin Source File

SOURCE=RES\NAND4.BMP
# End Source File
# Begin Source File

SOURCE=res\nand4b.bmp
# End Source File
# Begin Source File

SOURCE=RES\NETCALL.BMP
# End Source File
# Begin Source File

SOURCE=RES\NETCALLB.BMP
# End Source File
# Begin Source File

SOURCE=res\netwait.bmp
# End Source File
# Begin Source File

SOURCE=RES\NETWAITB.BMP
# End Source File
# Begin Source File

SOURCE=RES\NETWORK.BMP
# End Source File
# Begin Source File

SOURCE=RES\NETWORKB.BMP
# End Source File
# Begin Source File

SOURCE=RES\NOR2.BMP
# End Source File
# Begin Source File

SOURCE=res\nor2b.bmp
# End Source File
# Begin Source File

SOURCE=RES\NOR3.BMP
# End Source File
# Begin Source File

SOURCE=res\nor3b.bmp
# End Source File
# Begin Source File

SOURCE=RES\NOR4.BMP
# End Source File
# Begin Source File

SOURCE=res\nor4b.bmp
# End Source File
# Begin Source File

SOURCE=RES\NULL.BMP
# End Source File
# Begin Source File

SOURCE=res\null_0.bmp
# End Source File
# Begin Source File

SOURCE=res\null_0b.bmp
# End Source File
# Begin Source File

SOURCE=res\null_1.bmp
# End Source File
# Begin Source File

SOURCE=res\null_1b.bmp
# End Source File
# Begin Source File

SOURCE=RES\NULL_PD.BMP
# End Source File
# Begin Source File

SOURCE=res\null_pd0.bmp
# End Source File
# Begin Source File

SOURCE=res\null_pd1.bmp
# End Source File
# Begin Source File

SOURCE=RES\NULL_PDB.BMP
# End Source File
# Begin Source File

SOURCE=RES\NULL_PU.BMP
# End Source File
# Begin Source File

SOURCE=res\null_pu0.bmp
# End Source File
# Begin Source File

SOURCE=res\null_pu1.bmp
# End Source File
# Begin Source File

SOURCE=RES\NULL_PUB.BMP
# End Source File
# Begin Source File

SOURCE=res\nullb.bmp
# End Source File
# Begin Source File

SOURCE=res\nullpd0b.bmp
# End Source File
# Begin Source File

SOURCE=res\nullpd1b.bmp
# End Source File
# Begin Source File

SOURCE=res\nullpu0b.bmp
# End Source File
# Begin Source File

SOURCE=res\nullpu1b.bmp
# End Source File
# Begin Source File

SOURCE=RES\OR2.BMP
# End Source File
# Begin Source File

SOURCE=res\or2b.bmp
# End Source File
# Begin Source File

SOURCE=RES\OR3.BMP
# End Source File
# Begin Source File

SOURCE=res\or3b.bmp
# End Source File
# Begin Source File

SOURCE=RES\OR4.BMP
# End Source File
# Begin Source File

SOURCE=res\or4b.bmp
# End Source File
# Begin Source File

SOURCE=RES\OSC.BMP
# End Source File
# Begin Source File

SOURCE=res\OSCB.bmp
# End Source File
# Begin Source File

SOURCE=RES\PAGE_IN.BMP
# End Source File
# Begin Source File

SOURCE=res\page_inb.bmp
# End Source File
# Begin Source File

SOURCE=RES\PAGE_OUT.BMP
# End Source File
# Begin Source File

SOURCE=res\PAGEOUTB.bmp
# End Source File
# Begin Source File

SOURCE=RES\PALETTE.BMP
# End Source File
# Begin Source File

SOURCE=RES\PENCIL.CUR
# End Source File
# Begin Source File

SOURCE=RES\PLUS.BMP
# End Source File
# Begin Source File

SOURCE=res\plusb.bmp
# End Source File
# Begin Source File

SOURCE=RES\PROBE_FL.CUR
# End Source File
# Begin Source File

SOURCE=RES\PROBE_MI.CUR
# End Source File
# Begin Source File

SOURCE=RES\PROBE_NU.CUR
# End Source File
# Begin Source File

SOURCE=RES\PROBE_OF.CUR
# End Source File
# Begin Source File

SOURCE=RES\PROBE_ON.CUR
# End Source File
# Begin Source File

SOURCE=RES\PROBE_PL.CUR
# End Source File
# Begin Source File

SOURCE=RES\PROBE_UN.CUR
# End Source File
# Begin Source File

SOURCE=res\random.bmp
# End Source File
# Begin Source File

SOURCE=RES\RANDOMB.BMP
# End Source File
# Begin Source File

SOURCE=RES\ROBOT.BMP
# End Source File
# Begin Source File

SOURCE=RES\ROBOTB.BMP
# End Source File
# Begin Source File

SOURCE=RES\ROBOTD.BMP
# End Source File
# Begin Source File

SOURCE=RES\ROBOTDB.BMP
# End Source File
# Begin Source File

SOURCE=RES\SELECT0B.BMP
# End Source File
# Begin Source File

SOURCE=RES\SELECT1B.BMP
# End Source File
# Begin Source File

SOURCE=RES\SELECT2B.BMP
# End Source File
# Begin Source File

SOURCE=RES\SELECT3B.BMP
# End Source File
# Begin Source File

SOURCE=RES\SELECT4B.BMP
# End Source File
# Begin Source File

SOURCE=RES\SELECT5B.BMP
# End Source File
# Begin Source File

SOURCE=RES\SELECT6B.BMP
# End Source File
# Begin Source File

SOURCE=RES\SELECT7B.BMP
# End Source File
# Begin Source File

SOURCE=RES\SELECT8B.BMP
# End Source File
# Begin Source File

SOURCE=RES\SELECT9B.BMP
# End Source File
# Begin Source File

SOURCE=RES\SELECT_0.BMP
# End Source File
# Begin Source File

SOURCE=RES\SELECT_1.BMP
# End Source File
# Begin Source File

SOURCE=RES\SELECT_2.BMP
# End Source File
# Begin Source File

SOURCE=RES\SELECT_3.BMP
# End Source File
# Begin Source File

SOURCE=RES\SELECT_4.BMP
# End Source File
# Begin Source File

SOURCE=RES\SELECT_5.BMP
# End Source File
# Begin Source File

SOURCE=RES\SELECT_6.BMP
# End Source File
# Begin Source File

SOURCE=RES\SELECT_7.BMP
# End Source File
# Begin Source File

SOURCE=RES\SELECT_8.BMP
# End Source File
# Begin Source File

SOURCE=RES\SELECT_9.BMP
# End Source File
# Begin Source File

SOURCE=RES\SELECT_A.BMP
# End Source File
# Begin Source File

SOURCE=RES\SELECT_B.BMP
# End Source File
# Begin Source File

SOURCE=RES\SELECT_C.BMP
# End Source File
# Begin Source File

SOURCE=RES\SELECT_D.BMP
# End Source File
# Begin Source File

SOURCE=RES\SELECT_E.BMP
# End Source File
# Begin Source File

SOURCE=RES\SELECT_F.BMP
# End Source File
# Begin Source File

SOURCE=RES\SELECTAB.BMP
# End Source File
# Begin Source File

SOURCE=RES\SELECTBB.BMP
# End Source File
# Begin Source File

SOURCE=RES\SELECTCB.BMP
# End Source File
# Begin Source File

SOURCE=RES\SELECTDB.BMP
# End Source File
# Begin Source File

SOURCE=RES\SELECTEB.BMP
# End Source File
# Begin Source File

SOURCE=RES\SELECTFB.BMP
# End Source File
# Begin Source File

SOURCE=RES\STACK.BMP
# End Source File
# Begin Source File

SOURCE=RES\SWITCH_F.BMP
# End Source File
# Begin Source File

SOURCE=RES\SWITCH_O.BMP
# End Source File
# Begin Source File

SOURCE=RES\SWITCH_S.BMP
# End Source File
# Begin Source File

SOURCE=res\SWITCHFB.bmp
# End Source File
# Begin Source File

SOURCE=RES\SWITCHMF.BMP
# End Source File
# Begin Source File

SOURCE=RES\SWITCHMO.BMP
# End Source File
# Begin Source File

SOURCE=res\SWITCHOB.bmp
# End Source File
# Begin Source File

SOURCE=RES\SWTCHMFB.BMP
# End Source File
# Begin Source File

SOURCE=RES\SWTCHMOB.BMP
# End Source File
# Begin Source File

SOURCE=Res\Tape.bmp
# End Source File
# Begin Source File

SOURCE=Res\Tapeb.bmp
# End Source File
# Begin Source File

SOURCE=RES\TEXT.BMP
# End Source File
# Begin Source File

SOURCE=RES\TEXTMB.BMP
# End Source File
# Begin Source File

SOURCE=RES\TEXTSB.BMP
# End Source File
# Begin Source File

SOURCE=RES\TIMER.BMP
# End Source File
# Begin Source File

SOURCE=RES\TIMERB.BMP
# End Source File
# Begin Source File

SOURCE=res\TOOLBAR.BMP
# End Source File
# Begin Source File

SOURCE=RES\TRIBUFH.BMP
# End Source File
# Begin Source File

SOURCE=RES\TRIBUFHB.BMP
# End Source File
# Begin Source File

SOURCE=RES\TRIBUFL.BMP
# End Source File
# Begin Source File

SOURCE=RES\TRIBUFLB.BMP
# End Source File
# Begin Source File

SOURCE=RES\TRIINVH.BMP
# End Source File
# Begin Source File

SOURCE=RES\TRIINVHB.BMP
# End Source File
# Begin Source File

SOURCE=RES\TRIINVL.BMP
# End Source File
# Begin Source File

SOURCE=RES\TRIINVLB.BMP
# End Source File
# Begin Source File

SOURCE=RES\TURING.BMP
# End Source File
# Begin Source File

SOURCE=RES\TURTLE.BMP
# End Source File
# Begin Source File

SOURCE=RES\WAV.BMP
# End Source File
# Begin Source File

SOURCE=res\wavb.bmp
# End Source File
# Begin Source File

SOURCE=RES\WAVPLAY.BMP
# End Source File
# Begin Source File

SOURCE=RES\WIREB.BMP
# End Source File
# Begin Source File

SOURCE=res\xnor2.bmp
# End Source File
# Begin Source File

SOURCE=res\xnor2b.bmp
# End Source File
# Begin Source File

SOURCE=res\xnor3.bmp
# End Source File
# Begin Source File

SOURCE=res\xnor3b.bmp
# End Source File
# Begin Source File

SOURCE=res\xnor4.bmp
# End Source File
# Begin Source File

SOURCE=res\xnor4b.bmp
# End Source File
# Begin Source File

SOURCE=res\xor2.bmp
# End Source File
# Begin Source File

SOURCE=res\xor2b.bmp
# End Source File
# Begin Source File

SOURCE=res\xor3.bmp
# End Source File
# Begin Source File

SOURCE=res\xor3b.bmp
# End Source File
# Begin Source File

SOURCE=res\xor4.bmp
# End Source File
# Begin Source File

SOURCE=res\xor4b.bmp
# End Source File
# End Group
# Begin Group "HTML Help Files"

# PROP Default_Filter "hhp;hhc;hhk;gif;jpg"
# Begin Source File

SOURCE=.\hlp\MMLOGIC.hhk
# End Source File
# Begin Source File

SOURCE=.\hlp\mmlogic.hhp

!IF  "$(CFG)" == "Logicl32 - Win32 Debug"

# PROP Ignore_Default_Tool 1
USERDEP__MMLOG="hlp\HTMLDefines.h"	
# Begin Custom Build - Making help file...
OutDir=.\Debug
InputPath=.\hlp\mmlogic.hhp

"$(OutDir)\$(ProjectName).chm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	start /wait hhc "hlp\mmlogic.hhp" 
	if not exist "hlp\mmlogic.chm" goto :HelpError 
	copy "hlp\mmlogic.chm" "$(OutDir)\mmlogic.chm" 
	goto :HelpDone 
	:HelpError 
	echo hlp\mmlogic.hhp(1) : error:Problem encountered creating help file 
	echo. 
	:HelpDone 
	echo. 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "Logicl32 - Win32 Release"

# PROP Ignore_Default_Tool 1
USERDEP__MMLOG="hlp\HTMLDefines.h"	
# Begin Custom Build - Making help file...
OutDir=.\Release
InputPath=.\hlp\mmlogic.hhp

"$(OutDir)\$(ProjectName).chm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	start /wait hhc "hlp\mmlogic.hhp" 
	if not exist "hlp\mmlogic.chm" goto :HelpError 
	copy "hlp\mmlogic.chm" "$(OutDir)\mmlogic.chm" 
	goto :HelpDone 
	:HelpError 
	echo hlp\mmlogic.hhp(1) : error:Problem encountered creating help file 
	echo. 
	:HelpDone 
	echo. 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\hlp\Table of Contents.hhc"
# End Source File
# End Group
# Begin Group "HTML Help Topics"

# PROP Default_Filter "htm;html"
# Begin Source File

SOURCE=.\hlp\html\alu_device.htm
# End Source File
# Begin Source File

SOURCE=.\hlp\Html\analyze_tool.htm
# End Source File
# Begin Source File

SOURCE=.\hlp\html\and_gate.htm
# End Source File
# Begin Source File

SOURCE=.\hlp\html\ascii_display_device.htm
# End Source File
# Begin Source File

SOURCE=.\hlp\html\bit_bucket_device.htm
# End Source File
# Begin Source File

SOURCE=.\hlp\html\bitmap_device.htm
# End Source File
# Begin Source File

SOURCE=.\hlp\html\bus_tool.htm
# End Source File
# Begin Source File

SOURCE=.\hlp\html\buzzer_device.htm
# End Source File
# Begin Source File

SOURCE=.\hlp\html\changing_device_options.htm
# End Source File
# Begin Source File

SOURCE=.\hlp\html\clock_device.htm
# End Source File
# Begin Source File

SOURCE=.\hlp\html\counter_device.htm
# End Source File
# Begin Source File

SOURCE=.\hlp\html\file_formats.htm
# End Source File
# Begin Source File

SOURCE=.\hlp\html\flipflop_device.htm
# End Source File
# Begin Source File

SOURCE=.\hlp\html\ground_device.htm
# End Source File
# Begin Source File

SOURCE=.\hlp\html\introduction.htm
# End Source File
# Begin Source File

SOURCE=.\hlp\html\inverter_gate.htm
# End Source File
# Begin Source File

SOURCE=.\hlp\html\keyboard_device.htm
# End Source File
# Begin Source File

SOURCE=.\hlp\html\keypad_device.htm
# End Source File
# Begin Source File

SOURCE=.\hlp\html\led_device.htm
# End Source File
# Begin Source File

SOURCE=.\hlp\html\managing_pages.htm
# End Source File
# Begin Source File

SOURCE=.\hlp\html\memory_device.htm
# End Source File
# Begin Source File

SOURCE=.\hlp\html\modes_of_operation.htm
# End Source File
# Begin Source File

SOURCE=.\hlp\html\multiplexer_device.htm
# End Source File
# Begin Source File

SOURCE=.\hlp\html\network_device.htm
# End Source File
# Begin Source File

SOURCE=.\hlp\html\networking_setup_basics.htm
# End Source File
# Begin Source File

SOURCE=.\hlp\html\node_tool.htm
# End Source File
# Begin Source File

SOURCE=.\hlp\html\or_gate.htm
# End Source File
# Begin Source File

SOURCE=.\hlp\html\oscillator_device.htm
# End Source File
# Begin Source File

SOURCE=.\hlp\html\pause_simulator_device.htm
# End Source File
# Begin Source File

SOURCE=.\hlp\html\plus_device.htm
# End Source File
# Begin Source File

SOURCE=.\hlp\html\pointer_tool.htm
# End Source File
# Begin Source File

SOURCE=.\hlp\html\port_in_device.htm
# End Source File
# Begin Source File

SOURCE=.\hlp\html\port_out_device.htm
# End Source File
# Begin Source File

SOURCE=.\hlp\html\probe_tool.htm
# End Source File
# Begin Source File

SOURCE=.\hlp\html\random_device.htm
# End Source File
# Begin Source File

SOURCE=.\hlp\html\read_file.htm
# End Source File
# Begin Source File

SOURCE=.\hlp\html\robot_device.htm
# End Source File
# Begin Source File

SOURCE=.\hlp\html\select_device.htm
# End Source File
# Begin Source File

SOURCE=.\hlp\html\signal_receiver_device.htm
# End Source File
# Begin Source File

SOURCE=.\hlp\html\signal_sender_device.htm
# End Source File
# Begin Source File

SOURCE=.\hlp\html\simulation_setup.htm
# End Source File
# Begin Source File

SOURCE=.\hlp\html\sound_wave_device.htm
# End Source File
# Begin Source File

SOURCE=.\hlp\html\states_of_a_node.htm
# End Source File
# Begin Source File

SOURCE=.\hlp\html\switch_device.htm
# End Source File
# Begin Source File

SOURCE=.\hlp\html\tapedrive_device.htm
# End Source File
# Begin Source File

SOURCE=.\hlp\html\text.htm
# End Source File
# Begin Source File

SOURCE=.\hlp\html\timer_device.htm
# End Source File
# Begin Source File

SOURCE=.\hlp\html\tristate_gate.htm
# End Source File
# Begin Source File

SOURCE=.\hlp\html\tutorial.htm
# End Source File
# Begin Source File

SOURCE=.\hlp\html\what_is_a_multimedia_logic_simulator.htm
# End Source File
# Begin Source File

SOURCE=.\hlp\html\wiring_tool.htm
# End Source File
# Begin Source File

SOURCE=.\hlp\html\write_file_device.htm
# End Source File
# Begin Source File

SOURCE=.\hlp\html\xor_gate.htm
# End Source File
# End Group
# Begin Source File

SOURCE=.\License.txt
# End Source File
# Begin Source File

SOURCE=.\res\MMLogic.manifest
# End Source File
# Begin Source File

SOURCE=.\MMLogic.nsi
# End Source File
# Begin Source File

SOURCE=".\README.TXT"
# End Source File
# Begin Source File

SOURCE=.\Tips.txt
# End Source File
# End Target
# End Project
