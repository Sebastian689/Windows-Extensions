#include "windows.h"
#include "pathcch.h"
#include "stdio.h"
#include "Shlwapi.h"
#include <iostream>

#define UNICODE
#define _UNICODE

size_t lehveinstein(const char* file_to_find, const size_t length_a, const char* current_file, const size_t length_b)
{
    if (file_to_find == current_file) return 0; 
    if (length_a == 0) return length_b;
    if (length_b == 0) return length_a;

    size_t *cache = (size_t *)calloc(length_a, sizeof(size_t));
    size_t index = 0;
    size_t b_index = 0;
    size_t distance;
    size_t b_distance;
    size_t result = 500;
    char code;

    while (index < length_a)
    {
        cache[index] = index + 1;
        index++;
    }

        
    while (b_index < length_b)
    {
        code = current_file[b_index];
        result = distance = b_index++;
        index = SIZE_MAX;

        while (++index < length_a)
        {
            b_distance = code == file_to_find[index] ? distance : distance + 1;
            distance = cache[index];

            cache[index] = result = distance > result
                ? b_distance > result
                    ? result + 1
                    : b_distance
                : b_distance > distance
                    ? distance + 1
                    : b_distance;
        }
    }

    free (cache);

    return result;
}

struct filescore {
    char filename[1024];
    size_t score;
};

#define MAX_CANDIDATES 10000
filescore candidates[MAX_CANDIDATES];
int counter = 0;

DWORD SearchFolder(const char *folder, const char *file, const size_t length)
{
    WIN32_FIND_DATAA FindFileData;
    char mask[MAX_PATH+3], filePath[MAX_PATH];
    DWORD fileError_initial = 0;
    DWORD dwError = ERROR_SUCCESS;

    // PathCchCombineEx(mask, MAX_PATH+3, folder, L"*", PATHCCH_NONE);
    PathCombineA(mask, folder, "*");

    HANDLE hFind = FindFirstFileA(mask, &FindFileData);
    
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
                // PathCombine(mask, folder, FindFileData.cFileName);
                dwError = SearchFolder(filePath, file, length);

                if (dwError != NO_ERROR && dwError != ERROR_NO_MORE_FILES) {
                    SetLastError(dwError);
                    break;
                }
            }
            else
            {
                size_t length_b = strlen(FindFileData.cFileName);
                size_t score = lehveinstein(file, length, FindFileData.cFileName, length_b);
                if (score < 5)
                {
                    if (counter < MAX_CANDIDATES) 
                    {
                        filescore candidate = {};
                        strncpy_s(candidate.filename, FindFileData.cFileName, sizeof(candidate.filename) - 1);
                        // candidate.filename[sizeof(candidate.filename) - 1] = '\0';
                        candidate.score = score;

                        candidates[counter] = candidate;
                        counter++;
                    }
                    else
                    {
                        printf("Too many candidates. Narrow your search");
                        exit(1);
                    }
                }
                dwError = NO_ERROR;
            }
        } 
        while (FindNextFileA(hFind, &FindFileData)); 
    }

    dwError = GetLastError();
    FindClose(hFind);
    return dwError;
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Enter the name of file to search for");
        return 0;
    }
    size_t length = strlen(argv[1]);
    DWORD result = SearchFolder("C:\\", argv[1], length);
    for (int i = 0; i < counter; ++i) 
    {
        // std::cout << "Candidate " << candidates[i].filename << " with score " << candidates[i].score << "\n";
        printf("Candidate %s with score %zu\n", candidates[i].filename, candidates[i].score);
    }
    return result;
}