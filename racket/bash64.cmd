@echo OFF
setlocal
set PATH=PATH=C:\Users\user\.software\msys64\mingw64\bin;C:\Users\user\.software\msys64\usr\local\bin;C:\Users\user\.software\msys64\usr\bin;%PATH%
set MINGW_CHOST=x86_64-w64-mingw32
set MINGW_PACKAGE_PREFIX=mingw-w64-x86_64
set MINGW_PREFIX=/mingw64
set MSYSTEM_CARCH=x86_64
set MSYSTEM_CHOST=x86_64-w64-mingw32
set MSYSTEM_PREFIX=/mingw64
set MSYSTEM=MINGW64
bash.exe
endlocal