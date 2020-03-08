#include "my_correct_read.h"
#include <iostream>
#include <string>
namespace correct
{
    double read(const std::string& sentence)
    {   
        while (true)
        {
            std::cout << "\nEnter " << sentence << ": ";
            std::string line;
            getline(std::cin, line);
            while (line.size() == 0) getline(std::cin, line);
            char* p;
            double number;
            if (line.find(",") != std::string::npos)
            {
                line.replace(line.find(","), 1, ".");
            }
            number = strtod(line.c_str(), &p);
            if (*p == 0) return number;
            else std::cout << "\nThe data entered incorrectly!" << std::endl;
        }
    }
}