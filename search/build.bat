@echo off
REM If no argument is given, default to Debug
if "%~1"=="" (
    set "CONFIG=Debug"
) else (
    set "CONFIG=%~1"
)

echo Building in %CONFIG% mode...

if /I "%CONFIG%"=="release" (
    echo Running Release build...
    cl /W4 /WX /O2 search.cpp /link Shlwapi.lib
) else (
    echo Running Debug build...
    cl /W4 /Zi search.cpp /link Shlwapi.lib
)
