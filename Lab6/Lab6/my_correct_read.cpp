#include "my_correct_read.h"
#include <iostream>
#include <string>
#include <conio.h>

namespace correct
{
    double read_double(const std::string& sentence)
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
    std::size_t read_size_t(const std::string& sentence)
    {
        while (true)
        {
            std::cout << "\nEnter " << sentence << ": ";
            long long number;
            std::cin >> number;
            if ((!std::cin.good()) || (number < 0))
            {
                std::cin.clear();
                std::cin.ignore(200, '\n');
                std::cout << "\nThe data entered incorrectly!" << std::endl;
            }
            else
            {
                std::cin.clear();
                std::cin.ignore(200, '\n');
                return std::size_t(number);
            }
        }
    }
    unsigned read_unsigned(const std::string& sentence)
    {
        while (true)
        {
            std::cout << "\nEnter " << sentence << ": ";
            long number;
            std::cin >> number;
            if ((!std::cin.good()) || (number < 0))
            {
                std::cin.clear();
                std::cin.ignore(200, '\n');
                std::cout << "\nThe data entered incorrectly!" << std::endl;
            }
            else
            {
                std::cin.clear();
                std::cin.ignore(200, '\n');
                return unsigned(number);
            }
        }
    }
    long read_long(const std::string& sentence)
    {
        while (true)
        {
            std::cout << "\nEnter " << sentence << ": ";
            long number;
            std::cin >> number;
            if (!std::cin.good())
            {
                std::cin.clear();
                std::cin.ignore(200, '\n');
                std::cout << "\nThe data entered incorrectly!" << std::endl;
            }
            else
            {
                std::cin.clear();
                std::cin.ignore(200, '\n');
                return number;
            }
        }
    }
    bool read_bool(const std::string& sentence)
    {
        while (true)
        {
            std::cout << "\nSelect " << sentence << ":\n1)True.\n2)False." << std::endl;
            switch (_getch())
            {
            case '1': return true;
                break;
            case '2': return false;
                break;
            break;
            default: std::cout << "\nPress the correct key!" << std::endl;
            }
        }
    }
    int read_int(const std::string& sentence)
    {
        while (true)
        {
            std::cout << "\nEnter " << sentence << ": ";
            int number;
            std::cin >> number;
            if (!std::cin.good())
            {
                std::cin.clear();
                std::cin.ignore(200, '\n');
                std::cout << "\nThe data entered incorrectly!" << std::endl;
            }
            else
            {
                std::cin.clear();
                std::cin.ignore(200, '\n');
                return number;
            }
        }
    }
}