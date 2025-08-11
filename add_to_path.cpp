// append the executables to the system path
#include <windows.h>
#include <string>
#include <iostream>
#include <filesystem>
namespace fs = std::filesystem;

int main()
{
    std::cout << "Current path: " << fs::current_path() << "\n";
    std::cout << "Current path2: " << std::getenv("PATH") << "\n";

    return 0;
}