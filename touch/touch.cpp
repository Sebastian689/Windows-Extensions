#include <fstream>
#include <iostream>

int main(int argc, char** argv)
{
    char* f = argv[1];
    std::ofstream file(f);
    if (!file.is_open())
    {
        std::cout << "failed to create file" << "\n";
        return 1;
    }

    return 0;
}