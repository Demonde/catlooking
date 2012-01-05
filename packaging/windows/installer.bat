@echo off
rem Make sure these paths are appropriate for your system:

SET mingw_dir=C:\Qt\qtcreator-2.3.1\mingw
SET qt_dir=C:\Qt\4.7.4

IF NOT EXIST build\windows MKDIR build\windows
COPY %mingw_dir%\bin\mingwm10.dll build\windows
COPY %mingw_dir%\bin\libgcc_s_dw2-1.dll build\windows
COPY %qt_dir%\bin\QtCore4.dll build\windows
COPY %qt_dir%\bin\QtGui4.dll build\windows
COPY %qt_dir%\bin\QtXml4.dll build\windows
COPY %qt_dir%\bin\QtNetwork4.dll build\windows
IF NOT EXIST build\windows\imageformats MKDIR build\windows\imageformats
COPY %qt_dir%\plugins\imageformats\qjpeg4.dll build\windows\imageformats
rem Copy resources to install dir
IF NOT EXIST resources\fonts MKDIR build\windows\fonts
COPY resources\fonts\chinese.ttc build\windows\fonts
COPY resources\fonts\designosaur-italic.ttf build\windows\fonts
