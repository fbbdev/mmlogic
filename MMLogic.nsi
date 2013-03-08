;Multimedia Logic 1.6.2
;

;--------------------------------
;Defines

  !define APPLICATION_NAME "Multimedia Logic"
  !define APPLICATION_VERSION "1.6.2"
  !define APPLICATION_PUBLISHER ""
  !define APPLICATION_WEB_SITE "http://sourceforge.net/projects/multimedialogic/"
  !define INSTALL_LICENSE "LICENSE.TXT"
  !define INSTALL_PATH "$PROGRAMFILES\${APPLICATION_NAME}"
  !define INSTALL_GRAPHICS "nsis"

  !define APPLICATION_VERSION_MAJOR 1
  !define APPLICATION_VERSION_MINOR 6
  !define APPLICATION_VERSION_REVISION 2
;--------------------------------
;Include Modern UI

  !include "MUI.nsh"

;--------------------------------

;Configuration

  ;General
  Name "${APPLICATION_NAME} ${APPLICATION_VERSION}"
  OutFile "${APPLICATION_NAME}${APPLICATION_VERSION}.exe"

  ;Folder selection page
  InstallDir "${INSTALL_PATH}"

  ;Get install folder from registry if available
  InstallDirRegKey HKCU "Software\${APPLICATION_PUBLISHER}\${APPLICATION_NAME}" ""

  VIProductVersion "1.6.2.0"
  VIAddVersionKey "FileDescription" "${APPLICATION_NAME} Installer"
;  VIAddVersionKey "CompanyName" "${APPLICATION_PUBLISHER}"
  VIAddVersionKey "ProductName" "${APPLICATION_NAME} Installer"
  VIAddVersionKey "Comments" "${APPLICATION_NAME} Installer"
;  VIAddVersionKey "LegalCopyright" "${APPLICATION_PUBLISHER}"
  VIAddVersionKey "FileVersion" "${APPLICATION_VERSION}"

;--------------------------------
;Variables

  ;Var MUI_TEMP
  Var STARTMENU_FOLDER

;--------------------------------
;Interface Settings

  ;Generic settings
  !define MUI_ABORTWARNING

  ;Welcome page
  !define MUI_WELCOMEFINISHPAGE_BITMAP "${NSISDIR}\Contrib\Graphics\Wizard\nsis.bmp"
  ;!define MUI_WELCOMEPAGE_TITLE_3LINES

  ;Install pages
  !define MUI_HEADERIMAGE_BITMAP "${NSISDIR}\Contrib\Graphics\Header\nsis.bmp"
  !define MUI_HEADERIMAGE
  !define MUI_COMPONENTSPAGE_NODES

  ;Start Menu Folder Page Configuration
  !define MUI_STARTMENUPAGE_REGISTRY_ROOT "HKCU"
  !define MUI_STARTMENUPAGE_REGISTRY_KEY "Software\${APPLICATION_PUBLISHER}\${APPLICATION_NAME}"
  !define MUI_STARTMENUPAGE_REGISTRY_VALUENAME "Start Menu Folder"
  !define MUI_STARTMENUPAGE_DEFAULTFOLDER "${APPLICATION_NAME}"

  ;Finish page
  !define MUI_FINISHPAGE_LINK "Visit the ${APPLICATION_PUBLISHER} site for the latest news"
  !define MUI_FINISHPAGE_LINK_LOCATION "${APPLICATION_WEB_SITE}"
  !define MUI_FINISHPAGE_NOREBOOTSUPPORT
  ;!define MUI_FINISHPAGE_TITLE_3LINES

;--------------------------------
;Installer Pages

  !insertmacro MUI_PAGE_WELCOME
  !insertmacro MUI_PAGE_LICENSE "${INSTALL_LICENSE}"
  ;!insertmacro MUI_PAGE_COMPONENTS
  !insertmacro MUI_PAGE_DIRECTORY
  !insertmacro MUI_PAGE_STARTMENU Application $STARTMENU_FOLDER
  !insertmacro MUI_PAGE_INSTFILES
  !insertmacro MUI_PAGE_FINISH

;--------------------------------
; Uninstaller Pages
  !insertmacro MUI_UNPAGE_CONFIRM
  !insertmacro MUI_UNPAGE_INSTFILES
  ;!insertmacro MUI_UNPAGE_FINISH

;--------------------------------
;Languages

  !insertmacro MUI_LANGUAGE "English"
  Icon "${NSISDIR}\Contrib\Graphics\Icons\modern-install.ico"
  UninstallIcon "${NSISDIR}\Contrib\Graphics\Icons\modern-uninstall.ico"

;--------------------------------
;Installler Secions

Section "Install"

  ;Store install folder
  WriteRegStr HKCU "Software\${APPLICATION_PUBLISHER}\${APPLICATION_NAME}" "" $INSTDIR

  ;Files
  SetOutPath "$INSTDIR"
  File "Release\Mmlogic.exe"
  File "Release\mmlogic.chm"
  File /r "Examples"
  File "LICENSE.TXT"
  File "README.TXT"
  File "TIPS.TXT"

  ;Shortcuts
  CreateDirectory "$SMPROGRAMS\$STARTMENU_FOLDER"
  CreateShortCut "$SMPROGRAMS\$STARTMENU_FOLDER\Multimedia Logic.lnk" "$INSTDIR\MMLogic.exe"
  CreateShortCut "$SMPROGRAMS\$STARTMENU_FOLDER\Multimedia Logic Examples.lnk" "$INSTDIR\Examples"

  ;File association
  WriteRegStr HKCR ".lgi" "" "MMLogic.File"
  WriteRegStr HKCR "MMLogic.File\DefaultIcon" "" "$INSTDIR\MMLogic.exe,2"
  WriteRegStr HKCR "MMLogic.File\Shell\Open\Command" "" '$INSTDIR\MMLogic.exe "%1"'
  WriteRegStr HKCR "MMLogic.File\Shell\Open\ddeexec" "" '[open("%1")]'

  ;Create uninstaller
  WriteUninstaller "Uninstall.exe"
  CreateShortCut "$SMPROGRAMS\$STARTMENU_FOLDER\Uninstall ${APPLICATION_NAME}.lnk" "$INSTDIR\Uninstall.exe"
  WriteRegExpandStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APPLICATION_NAME}" "UninstallString" '"$INSTDIR\Uninstall.exe"'
  WriteRegExpandStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APPLICATION_NAME}" "InstallLocation" "$INSTDIR"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APPLICATION_NAME}" "DisplayName" "${APPLICATION_NAME} ${APPLICATION_VERSION}"
  ;WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APPLICATION_NAME}" "DisplayIcon" "$INSTDIR\Screening.exe,0"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APPLICATION_NAME}" "DisplayVersion" "${APPLICATION_VERSION}"
  ;WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APPLICATION_NAME}" "HelpLink" "${APP_URL}"
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APPLICATION_NAME}" "VersionMajor" "${APPLICATION_VERSION_MAJOR}"
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APPLICATION_NAME}" "VersionMinor" "${APPLICATION_VERSION_MINOR}.${APPLICATION_VERSION_REVISION}"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APPLICATION_NAME}" "Publisher" "${APPLICATION_PUBLISHER}"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APPLICATION_NAME}" "URLInfoAbout" "${APPLICATION_WEB_SITE}"
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APPLICATION_NAME}" "NoModify" "1"
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APPLICATION_NAME}" "NoRepair" "1"

SectionEnd

;--------------------------------
;Uninstall Files

Section "Uninstall"

  !insertmacro MUI_STARTMENU_GETFOLDER Application $STARTMENU_FOLDER
  Delete "$INSTDIR\Mmlogic.exe"
  Delete "$INSTDIR\mmlogic.chm"
  RMDir /r "$INSTDIR\Examples"
  Delete "$INSTDIR\LICENSE.TXT"
  Delete "$INSTDIR\README.TXT"
  Delete "$INSTDIR\Multimedia Logic Pre-Release notes.txt"
  Delete "$INSTDIR\Release Notes.txt"
  Delete "$SMPROGRAMS\$STARTMENU_FOLDER\Multimedia Logic.lnk"
  Delete "$SMPROGRAMS\$STARTMENU_FOLDER\Uninstall ${APPLICATION_NAME}.lnk"
  RMDir "$SMPROGRAMS\$STARTMENU_FOLDER\"
  Delete "$INSTDIR\Uninstall.exe"
  RMDir "$INSTDIR\"

  DeleteRegKey /ifempty HKCU "Software\${APPLICATION_PUBLISHER}\${APPLICATION_NAME}"
  DeleteRegKey /ifempty HKCU "Software\${APPLICATION_PUBLISHER}"
  DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APPLICATION_NAME}"
  ;TODO ${unregisterExtension} ".lgi" "Logic Projecto"

SectionEnd

Function .onInit
  ;Check if version 1.4 is installed
  ReadRegStr $R0 HKLM \
  "Software\Microsoft\Windows\CurrentVersion\Uninstall\{1F9A5CFA-BF15-46E7-A723-A654EA29D6F7}" \
  "UninstallString"
  StrCmp $R0 "" checkPre1_6
 
  MessageBox MB_OKCANCEL|MB_ICONEXCLAMATION \
  "${APPLICATION_NAME} 1.4 is currently installed. $\n$\nClick `OK` to remove the \
  previous version or `Cancel` to cancel this upgrade." \
  IDOK uninstV1.4
  Abort
 
checkPre1_6:
  ;Check if Pre1.6 is installed
  ReadRegStr $R0 HKLM \
  "Software\Microsoft\Windows\CurrentVersion\Uninstall\MultiMedia Logic" \
  "UninstallString"
  StrCmp $R0 "" done

  ReadRegStr $R1 HKLM \
  "Software\Microsoft\Windows\CurrentVersion\Uninstall\MultiMedia Logic" \
  "DisplayVersion"

  MessageBox MB_OKCANCEL|MB_ICONEXCLAMATION \
  "${APPLICATION_NAME} $R1 is currently installed. $\n$\nClick `OK` to remove the \
  previous version or `Cancel` to cancel this upgrade." \
  IDOK uninst
  Abort

checkOtherVersions:
  ;Check if any version as early as 1.6.1 or newer is installed
  ReadRegStr $R0 HKLM \
  "Software\Microsoft\Windows\CurrentVersion\Uninstall\Multimedia Logic" \
  "UninstallString"
  StrCmp $R0 "" done

  ReadRegStr $R1 HKLM \
  "Software\Microsoft\Windows\CurrentVersion\Uninstall\Multimedia Logic" \
  "DisplayVersion"

  MessageBox MB_OKCANCEL|MB_ICONEXCLAMATION \
  "${APPLICATION_NAME} $R1 is currently installed. $\n$\nClick `OK` to remove the \
  previous version or `Cancel` to cancel this upgrade." \
  IDOK uninst
  Abort
 
;Run the uninstaller
uninst:
  ClearErrors
  ExecWait '$R0 _?=$INSTDIR' ;Do not copy the uninstaller to a temp file
 
  IfErrors no_remove_uninstaller done
    ;You can either use Delete /REBOOTOK in the uninstaller or add some code
    ;here to remove the uninstaller. Use a registry key to check
    ;whether the user has chosen to uninstall. If you are using an uninstaller
    ;components page, make sure all sections are uninstalled.

;Run the uninstaller
uninstV1.4:
  ClearErrors
  ExecWait '$R0 _?=$INSTDIR' ;Do not copy the uninstaller to a temp file
 
  IfErrors no_remove_uninstaller checkOtherVersions
    ;You can either use Delete /REBOOTOK in the uninstaller or add some code
    ;here to remove the uninstaller. Use a registry key to check
    ;whether the user has chosen to uninstall. If you are using an uninstaller
    ;components page, make sure all sections are uninstalled.
  no_remove_uninstaller:
 
done:
 
FunctionEnd

