#include "lab2b_task_number_three.h"
#include "lab2b_task_number_twelve.h"
#include "lab2b_task_number_twenty_six.h"
#include <iostream>
#include <conio.h>
int main()
{
    while (true)
    {
        std::cout << "Select a task:\n1)Task 3.\n2)Task 12.\n3)Task 26.\n0)Exit." << std::endl;
        switch (_getch())
        {
        case '1': three::menu();
            break;
        case'2': twelve::menu();
            break;
        case'3':  twenty_six::menu();
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
