@echo off

rem options checking
:loop
if not "%1"=="" (
    if "%1"=="-clean" (
        set clean=true
		echo Clean should be set.
    )
    shift
    goto :loop
)

if "%clean%" == "true" (
	echo Directories with object files will be cleaned.
) else (
	echo Directories with object files will not be cleaned to fast rebuild in future.
)

:theend

rem Make sure these paths are appropriate for your system:
path = %PATH%;C:\QtSDK\Desktop\Qt\4.8.1\mingw\bin;C:\QtSDK\mingw\bin
qmake catlooking.pro
mingw32-make release
if "%clean%" == "true" (
	rmdir /s /q debug
	rmdir /s /q release
)

