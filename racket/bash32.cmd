@echo OFF
setlocal
set PATH=PATH=C:\Users\user\.software\msys64\mingw32\bin;C:\Users\user\.software\msys64\usr\local\bin;C:\Users\user\.software\msys64\usr\bin;%PATH%
set MINGW_CHOST=i686-w64-mingw32
set MINGW_PACKAGE_PREFIX=mingw-w64-i686
set MINGW_PREFIX=/mingw32
set MSYSTEM_CARCH=i686
set MSYSTEM_CHOST=i686-w64-mingw32
set MSYSTEM_PREFIX=/mingw32
set MSYSTEM=MINGW32
bash.exe
endlocal