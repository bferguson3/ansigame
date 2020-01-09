//#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char **argv)
{
    if(argc != 2) { 
        std::cout << "Usage:\n $ ./showans <ANSI filename>\n\n"; 
        return 0;
    }
    std::string line;
    std::ifstream myfile(argv[1]);
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            std::cout << line << '\n';
        }
        myfile.close();
    }
    
    return 1;
}
