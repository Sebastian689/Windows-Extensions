#include <iostream>
#include <filesystem>
#include <fstream>
#include "stdint.h"
#include <string>
#include <cstring>

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
    size_t result;
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

namespace fs = std::filesystem;

int main(int argc, char** argv)
{
    const char* file_to_find = argv[1];
    const size_t length = strlen(file_to_find);
    std::cout << "file to find: " << file_to_find << "\n";
    std::cout << "Current root path: " << fs::current_path().root_path() << "\n";
    std::cout << "Searching for files..." << "\n";

    std::cout << "Program files" << "\n";
    auto it = fs::recursive_directory_iterator(L"C:\\Program Files", fs::directory_options::skip_permission_denied);
    try {
        while (it != fs::recursive_directory_iterator())
        {
            //std::cout << it->path() << "\n";
            std::string file_name = it->path().filename().string();
            
            const char* c_file_name = file_name.c_str();
            const size_t length_b = strlen(c_file_name);

            size_t distance = lehveinstein(file_to_find, length, c_file_name, length_b);

            if (distance < 4)
                std::cout << "file path: " << it->path() << " with distance: " << distance << "\n";
            ++it;
        }
    } catch (const fs::filesystem_error& e) {
        std::cout << e.what() << "\n";
        try {
            ++it;
        } catch (fs::filesystem_error& e) {
            std::cout << "bro what is happening" << "\n";
        }
    }

    // std::cout << "Program files (x86)" << "\n";
    // auto it_86 = fs::recursive_directory_iterator(L"C:\\Program Files (x86)", fs::directory_options::skip_permission_denied);
    // try {
    //     while (it_86 != fs::recursive_directory_iterator())
    //     {
    //         // std::cout << it->path() << "\n";
    //         std::string file_name = it->path().filename().string();
    //         
    //         const char* c_file_name = file_name.c_str();
    //         const size_t length_b = strlen(c_file_name);

    //         size_t distance = lehveinstein(file_to_find, length, c_file_name, length_b);

    //         if (distance < 4)
    //             std::cout << "file path: " << it->path() << " with distance: " << distance << "\n";
    //         ++it;
    //     }
    // } catch (const fs::filesystem_error& e) {
    //     std::cout << "Could not access folder" << "\n";  
    // }
    // try {
    //     for (const auto& dir_entry : fs::recursive_directory_iterator(L"C:\\Program Files", fs::directory_options::skip_permission_denied)) 
    //     {
    //         try {
    //             std::cout << dir_entry << "\n";

    //             std::string file_name = dir_entry.path().filename().string();
    //             if (file_name.find("Windows Defender") != std::string::npos)
    //             {
    //                 continue;
    //             }

    //             const char* c_file_name = file_name.c_str();
    //             const size_t length_b = strlen(c_file_name);

    //             size_t distance = lehveinstein(file_to_find, length, c_file_name, length_b);

    //             if (distance < 2)
    //                 std::cout << "file path: " << dir_entry << " with distance: " << distance << "\n";
    //         } catch (const fs::filesystem_error& e) {
    //             std::cerr << "Skipping: " << e.what() << "\n";
    //             continue;
    //         }
    //     }
    // } catch (const fs::filesystem_error& e) {
    //     std::cout << "Failed to enter folder" << "\n";
    // }

    // std::cout << "Program files (x86)" << "\n";
    // for (const auto& dir_entry : fs::recursive_directory_iterator(L"C:\\Program Files (x86)", fs::directory_options::skip_permission_denied)) 
    // {
    //     // std::cout << dir_entry << "\n";

    //     std::string file_name = dir_entry.path().filename().string();
    //     const char* c_file_name = file_name.c_str();
    //     const size_t length_b = strlen(c_file_name);

    //     size_t distance = lehveinstein(file_to_find, length, c_file_name, length_b);

    //     if (distance < 2)
    //         std::cout << "file path: " << dir_entry << " with distance: " << distance << "\n";

    // }

    // std::cout << "ProgramData" << "\n";
    // for (const auto& dir_entry : fs::recursive_directory_iterator(L"C:\\ProgramData", fs::directory_options::skip_permission_denied)) 
    // {
    //     //std::cout << dir_entry << "\n";

    //     
    //     std::string file_name = dir_entry.path().filename().string();
    //     const char* c_file_name = file_name.c_str();
    //     const size_t length_b = strlen(c_file_name);

    //     size_t distance = lehveinstein(file_to_find, length, c_file_name, length_b);

    //     if (distance < 2)
    //         std::cout << "file path: " << dir_entry << " with distance: " << distance << "\n";
    //         
    // }


    // std::cout << "tmp" << "\n";
    // for (const auto& dir_entry : fs::recursive_directory_iterator(L"C:\\tmp", fs::directory_options::skip_permission_denied)) 
    // {
    //     //std::cout << dir_entry << "\n";

    //     
    //     std::string file_name = dir_entry.path().filename().string();
    //     const char* c_file_name = file_name.c_str();
    //     const size_t length_b = strlen(c_file_name);

    //     size_t distance = lehveinstein(file_to_find, length, c_file_name, length_b);

    //     if (distance < 2)
    //         std::cout << "file path: " << dir_entry << " with distance: " << distance << "\n";
    //         
    // }

    // std::cout << "Users" << "\n";
    // for (const auto& dir_entry : fs::recursive_directory_iterator(L"C:\\Users", fs::directory_options::skip_permission_denied)) 
    // {
    //     //std::cout << dir_entry << "\n";

    //     
    //     std::string file_name = dir_entry.path().filename().string();
    //     const char* c_file_name = file_name.c_str();
    //     const size_t length_b = strlen(c_file_name);

    //     size_t distance = lehveinstein(file_to_find, length, c_file_name, length_b);

    //     if (distance < 2)
    //         std::cout << "file path: " << dir_entry << " with distance: " << distance << "\n";
    //         
    // }
    
    // std::cout << "Windows" << "\n";
    // for (const auto& dir_entry : fs::recursive_directory_iterator(L"C:\\Windows", fs::directory_options::skip_permission_denied)) 
    // {
    //     std::string file_name = dir_entry.path().filename().string();
    //     const char* c_file_name = file_name.c_str();
    //     const size_t length_b = strlen(c_file_name);

    //     size_t distance = lehveinstein(file_to_find, length, c_file_name, length_b);

    //     if (distance < 2)
    //         std::cout << "file path: " << dir_entry << " with distance: " << distance << "\n";
    //         
    // }

    // fs::remove_all("sandbox");

    return 0;
}