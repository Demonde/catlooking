@echo off
rem Make sure these paths are appropriate for your system:

SET mingw_dir=C:\QtSDK\mingw
SET qt_dir=C:\QtSDK\Desktop\Qt\4.8.1\mingw

IF NOT EXIST build\windows MKDIR build\windows
COPY %mingw_dir%\bin\mingwm10.dll build\windows
COPY %mingw_dir%\bin\libgcc_s_dw2-1.dll build\windows
COPY %qt_dir%\bin\QtCore4.dll build\windows
COPY %qt_dir%\bin\QtGui4.dll build\windows
COPY %qt_dir%\bin\QtXml4.dll build\windows
COPY %qt_dir%\bin\QtNetwork4.dll build\windows
IF NOT EXIST build\windows\imageformats MKDIR build\windows\imageformats
COPY %qt_dir%\plugins\imageformats\qjpeg4.dll build\windows\imageformats
