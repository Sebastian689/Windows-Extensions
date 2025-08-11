#include "windows.h"
#include "stdio.h"
#include "Shlwapi.h"
#include <iostream>

DWORD SearchFolder(char *folder)
{
    WIN32_FIND_DATAA FindFileData;
    char mask[MAX_PATH+3], filePath[MAX_PATH];
    DWORD fileError_initial = 0;
    DWORD dwError, dwResult;

    PathCombineA(mask, folder, "*");

    HANDLE hFind = FindFirstFileA(mask, &FindFileData);
    if (hFind == INVALID_HANDLE_VALUE)
        return GetLastError();
    
    dwResult = ERROR_NO_MORE_FILES;

    if (hFind == INVALID_HANDLE_VALUE)
    {
        return fileError_initial;
    }
    else
    {
        do
        {
            if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            {
                if (strcmp(FindFileData.cFileName, ".") == 0 || strcmp(FindFileData.cFileName, "..") == 0)
                    continue;
                
                PathCombineA(filePath, folder, FindFileData.cFileName);
                dwError = SearchFolder(FindFileData.cFileName);

                if (dwError != NO_ERROR && dwError != ERROR_NO_MORE_FILES) {
                    SetLastError(dwError);
                    break;
                }
            }
            else
            {
                printf("filename %s\n", FindFileData.cFileName);
                dwResult = NO_ERROR;
            }
        } 
        while (FindNextFileA(hFind, &FindFileData)); 
    }

    dwError = GetLastError();
    FindClose(hFind);

    if (dwError != ERROR_NO_MORE_FILES)
        return dwError;

    return dwResult;
}

int main(int argc, char **argv)
{
    DWORD result = SearchFolder(".\\test_folder");
    std::cout << result << "\n";
    return 0;
}