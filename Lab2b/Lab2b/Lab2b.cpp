#include "lab2b_task_number_three.h"
#include "lab2b_task_number_twelve.h"
#include "lab2b_task_number_twenty_six.h"
#include <iostream>
#include <conio.h>
int main()
{
    while (true)
    {
        std::cout << "Select a task:" << std::endl;
        switch (_getch())
        {
        case '1': three::menu();
            break;
        case'2': twelve::menu();
            break;
        case'3':  twenty_six::write();
            break;
        case'0':
        {
            std::cout << "Exit..." << std::endl;
            return 0;
        }
        default: std::cout << "\nPress the correct key!\n" << std::endl;
        }
    }
     
    return 0;
}
