; Script generated with the Venis Install Wizard

; Define your application and company name
!define APPNAME "Catlooking"
!define APPNAMEANDVERSION "Catlooking 2.0"

; Main Install settings
Name "${APPNAMEANDVERSION}"
InstallDir "$PROGRAMFILES\Catlooking"
InstallDirRegKey HKLM "Software\${APPNAME}" ""
OutFile "..\..\InstallCatlooking.exe"

; Use compression
SetCompressor LZMA

; Modern interface settings
!include "MUI.nsh"

; Set custom styles
!define MUI_ICON "..\..\catlooking.ico"
!define MUI_WELCOMEFINISHPAGE_BITMAP ".\cat-nsis.bmp"

!define MUI_ABORTWARNING
!define MUI_FINISHPAGE_RUN "$INSTDIR\catlooking.exe"

!insertmacro MUI_PAGE_WELCOME
!insertmacro MUI_PAGE_LICENSE "..\..\COPYING"
!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_INSTFILES
!insertmacro MUI_PAGE_FINISH

!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES

; Set languages (first is default language)
!insertmacro MUI_LANGUAGE "English"
!insertmacro MUI_LANGUAGE "French"
!insertmacro MUI_LANGUAGE "Russian"
!insertmacro MUI_RESERVEFILE_LANGDLL

Section "Catlooking" Section1

	; Set Section properties
	SetOverwrite on

	; Set Section Files and Shortcuts
	SetOutPath "$INSTDIR\"
	File "..\..\build\windows\catlooking.exe"
	File "..\..\build\windows\libgcc_s_dw2-1.dll"
	File "..\..\build\windows\mingwm10.dll"
	File "..\..\build\windows\QtCore4.dll"
	File "..\..\build\windows\QtGui4.dll"
	File "..\..\build\windows\QtNetwork4.dll"
	File "..\..\build\windows\QtXml4.dll"
	SetOutPath "$INSTDIR\imageformats\"
	File "..\..\build\windows\imageformats\qjpeg4.dll"
	CreateShortCut "$DESKTOP\Catlooking.lnk" "$INSTDIR\catlooking.exe"
	CreateDirectory "$SMPROGRAMS\Catlooking"
	CreateShortCut "$SMPROGRAMS\Catlooking\Catlooking.lnk" "$INSTDIR\catlooking.exe"
	CreateShortCut "$SMPROGRAMS\Catlooking\Uninstall Catlooking.lnk" "$INSTDIR\uninstall.exe"

SectionEnd

Section -FinishSection

	WriteRegStr HKLM "Software\${APPNAME}" "" "$INSTDIR"
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APPNAME}" "DisplayName" "${APPNAME}"
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APPNAME}" "UninstallString" "$INSTDIR\uninstall.exe"
	WriteUninstaller "$INSTDIR\uninstall.exe"

SectionEnd

; Modern install component descriptions
!insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN
	!insertmacro MUI_DESCRIPTION_TEXT ${Section1} ""
!insertmacro MUI_FUNCTION_DESCRIPTION_END

;Uninstall section
Section Uninstall

	;Remove from registry...
	DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APPNAME}"
	DeleteRegKey HKLM "SOFTWARE\${APPNAME}"

	; Delete self
	Delete "$INSTDIR\uninstall.exe"

	; Delete Shortcuts
	Delete "$DESKTOP\Catlooking.lnk"
	Delete "$SMPROGRAMS\Catlooking\Catlooking.lnk"
	Delete "$SMPROGRAMS\Catlooking\Uninstall.lnk"

	; Clean up Catlooking
	Delete "$INSTDIR\catlooking.exe"
	Delete "$INSTDIR\libgcc_s_dw2-1.dll"
	Delete "$INSTDIR\mingwm10.dll"
	Delete "$INSTDIR\QtCore4.dll"
	Delete "$INSTDIR\QtGui4.dll"
	Delete "$INSTDIR\QtNetwork4.dll"
	Delete "$INSTDIR\QtXml4.dll"
	Delete "$INSTDIR\imageformats\qjpeg4.dll"

	; Remove remaining directories
	RMDir "$SMPROGRAMS\Catlooking"
	RMDir "$INSTDIR\imageformats\"
	RMDir "$INSTDIR\"

SectionEnd

BrandingText "Catlooking"

; eof