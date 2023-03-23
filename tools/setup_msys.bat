@echo off

set CHECK_PATH=.\tools\msys\bin\bash.exe

IF NOT EXIST %CHECK_PATH% (
    .\tools\7z\7za.exe x -y -r -aoa -o./tools ./tools/w800/toolchain/msys.7z
    xcopy .\tools\msys-dlls\*.dll .\tools\msys\bin\ /H /Y
    echo  - setup msys done !
) else (
    echo  - found msys !, path: %CHECK_PATH%
)
