// Lab1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <ctime>
#include <cstring>
#include <vector>
#include <stdio.h>
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
    char time_info[26];  //time_t seconds = time(NULL); tm* timeinfo = localtime(&seconds); cout << "Current Datetime:" << asctime(timeinfo) << endl;   
};
std:: vector<info_monster> all_monsters;//місце де зберігаються всі монстри
void my_cls()//очищує екран і виводить назву програми
{
    system("CLS");
    cout << "<The Forest of Monsters>"<< endl << endl;
}
int set_id()//створює унікальний код
{
    srand(time(0));
    long int id_monster=(rand()%90000 + 10000);
    return id_monster;
}
void add_new_monster()//створює нового монстра
{
    my_cls();
    cout << "Створіть власного монстра!\n";
    info_monster new_monster;
    cout << "Введіть ім'я монстра: ";
    scanf_s("%200s", new_monster.name, (unsigned)_countof(new_monster.name));
    cout << "Введіть кількість одиниць здоров'я монстра(1-50000): ";
    cin >> new_monster.xp;
    cout << "Введіть кількість одиниць атаки монстра(1-1000): ";
    cin >> new_monster.damage;
    cout << "Введіть шанс монстра виконати спеціальну атаку(0.00 - 1.00): ";
    cin >> new_monster.chance;
    cout << "Введіть один із можливих типів спеціальної атаки монстра(збільшити пошкодження,\n" 
         <<"повторити атаку, вилікувати себе, паралізувати супротивника): ";
    scanf_s("%100s", new_monster.type_of_attack, (unsigned)_countof(new_monster.type_of_attack));
    new_monster.id = set_id();
    my_cls();
    cout << "Новий монстр створений!\nЙого персональний ID: " << new_monster.id << endl;
    time_t seconds = time(NULL);
    ctime_s(new_monster.time_info,26,&seconds);
    all_monsters.push_back(new_monster);
    cout << "Дата та час створення: " << new_monster.time_info<< endl;
    cout << "Нажміть '0', щоб продовжити.\n";
    not_null:
    if (_getch() != '0') goto not_null;  
}
void write_monsters(std::vector<int> monsters_nombers)//виводить дані монстра на еран
{
    cout << "Знайдені монстри:\n";
    for (int i = 0; i < monsters_nombers.size(); i++) 
    {
        cout << i + 1 << ".\n";
        cout << all_monsters[monsters_nombers[i]].id << endl;
        cout << all_monsters[monsters_nombers[i]].name << endl;
        cout << all_monsters[monsters_nombers[i]].xp << endl;
        cout << all_monsters[monsters_nombers[i]].damage << endl;
        cout << all_monsters[monsters_nombers[i]].chance << endl;
        cout << all_monsters[monsters_nombers[i]].type_of_attack << endl;
        cout << all_monsters[monsters_nombers[i]].time_info;
    }
}
void faund_name()//пошук не працює
{
    my_cls();
    cout << "Введіть повне ім'я або фрагмент імені монстра: \n";
    char fragment_name[200];
    std:: vector <int> nombers_monsters;
    scanf_s("%200s", fragment_name, (unsigned)_countof(fragment_name));
    for (int i = 0; i < all_monsters.size(); i++)
    {
        char* p;
        p = all_monsters[i].name;
        cout << "p[" << i << "] = " << p << endl;
        int fragment_size = strlen(fragment_name), name_size = strlen(all_monsters[i].name);
        cout << "fragment_name = " << fragment_name << "||||||"<<endl;
        cout << "p = " << p << "||||||" << endl;
        cout << "fragment_size = " << fragment_size << endl;
        cout << "name_size = " << name_size << endl;
        if (fragment_size > name_size) break;
        else
        {
            bool flag = true;
            for (int j = 0,k = 0,j_save = 0; (j_save + fragment_size) < name_size; j++)
            {
                cout << "p[" << j << "] = " << p[j] << endl;
                cout << "fragment[" << k << "] = " << fragment_name[k] << endl;
                if (p[j] == fragment_name[k])
                {
                    k++;
                    cout << "k = " << k << endl;
                    flag = true;
                    if (k >= fragment_size) break;
                }
                else
                {
                    k = 0;
                    j_save++;
                    cout << "j_save = " << j_save << endl;
                    j = j_save;
                    flag = false;
                }
            }
            if (flag) nombers_monsters.push_back(i);
        }
    }
    int test;
    cin >> test;
    my_cls();
    if (nombers_monsters.size() == 0) cout << "Монстр не знайдений!\n";
    else write_monsters(nombers_monsters);
    cout << "Нажміть '0',щоб вийти.\n";
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
        my_cls();
        cout << "Виберіть режим пошуку монстра:\n1)Пошук по імені.\n2)Пошук по ID.\n";
        found_monstr:
        switch (_getch())
        {
            case '1':
            {
                faund_name();
                goto next;
            }
            break;
            case '2':
            {

            }
            break;
            default: goto found_monstr;
        }
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
