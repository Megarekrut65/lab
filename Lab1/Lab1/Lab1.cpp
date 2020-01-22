// Lab1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <ctime>
#include <cstring>
#include <vector>
using std::cout;
using std::cin;
using std::endl;

struct info_monster
{
    unsigned int id;
    char name[200];
    unsigned int xp;//1-50000
    unsigned short int damage;//1-1000
    double chance;//0-1 
    char type_of_attack[100];//збільшити пошкодження, повторити атаку,вилікувати себе, паралізувати супротивника; 
    //tm *time_info;  //time_t seconds = time(NULL); tm* timeinfo = localtime(&seconds); cout << "Current Datetime:" << asctime(timeinfo) << endl;   
};
std:: vector<info_monster> all_monster;
void my_cls()
{
    system("CLS");
    cout << "<The Forest of Monsters>"<< endl << endl;
}
int set_id()
{
    srand(time(0));
    long int id_monster=(rand()%90000 + 10000);
    return id_monster;
}
void add_new_monster()
{
    cout << "Створіть власного монстра!\n";
    info_monster new_monster;
    cout << "Введіть ім'я монстра: ";
    puts(new_monster.name);//тут
    cout << "Введіть кількість одиниць здоров'я монстра(1-50000): ";
    cin >> new_monster.xp;
    cout << "Введіть кількість одиниць атаки монстра(1-1000): ";
    cin >> new_monster.damage;
    cout << "Введіть шанс монстра виконати спеціальну атаку(0.00 - 1.00): ";
    cin >> new_monster.chance;
    cout << "Введіть один із можливих типів спеціальної атаки монстра(збільшити пошкодження, повторити атаку, вилікувати себе, паралізувати супротивника): ";
    puts(new_monster.type_of_attack);//тут
    new_monster.id = set_id();
    my_cls;
    cout << "Новий монстр створений!\nЙого персональний ID: " << new_monster.id << endl;
    //time_t seconds = time(NULL);//тут
    //new_monster.time_info = localtime(&seconds);//тут
    all_monster.push_back(new_monster);
   // cout << "Дата та час створення: " << asctime(new_monster.time_info )<< endl;
    cout << "Нажміть '0', щоб продовжити.\n";
    not_null:
    if (_getch() != '0') goto not_null;  
}
void Interactive_dialog_mode()
{
    next:
    my_cls();
    cout << "Меню:\n";
    cout << "1)Додати нового монстра.\n2)Знайти існуючого монстра.\n0)Назад.\n";
    menu:
    switch (_getch())
    {
    case '1':
    {
        add_new_monster();
        goto next;
    }
    break;
    case '2':
    {

    }
    break;
    case '0':
    break;
    default: goto menu;
    }

}
int main()
{
    SetConsoleOutputCP(1251);
    next:
    my_cls();
    cout << "Виберіть режим роботи програми:\n1)Інтерактивний діалоговий режим.\n2)Демонстраційний режим.\n3)Автоматичний режим “benchmark”\n0)Вихід.\n";
    mode:
    switch(_getch())
    {
        case '1':
        {
            Interactive_dialog_mode();
            goto next;
        }
        break;
        case '2':
        {

        }
        break;
        case '3':
        {
            
        }
        break;
        case '0':
        {
            my_cls();
            cout << "Вихід...";
            return 0;
        }
        break;
        default: goto mode;
    }

    
   return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
