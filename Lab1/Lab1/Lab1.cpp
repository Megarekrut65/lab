// Lab1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <ctime>
#include <cstring>
#include <vector>
#include <stdio.h>
#include <string>
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
    std:: string type_of_attack;//збільшити пошкодження, повторити атаку,вилікувати себе, паралізувати супротивника; 
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
    cout << "Create your own monster!\n";
    info_monster new_monster;
    cout << "Enter a monster name: ";
    cin.get(new_monster.name, 200);
    //scanf_s("%200s", new_monster.name, (unsigned)_countof(new_monster.name));//при вводі двох слів зависає
    while (true)
    {
        cout << "Enter the number of monster health units (1-50000): ";
        int temp_xp;
        cin >> temp_xp;
        if ((temp_xp < 1) || (temp_xp > 50000))
        {
            my_cls();
            cout << "Create your own monster!\n";
            cout << "Enter a monster name: " << new_monster.name << endl;
        }
        else
        {
            new_monster.xp = temp_xp;
            break;
        }      
    }
    while (true)
    {
        cout << "Enter the number of monster attack units (1-1000): ";
        int temp_damage;
        cin >> temp_damage;
        if ((temp_damage < 1) || (temp_damage > 1000))
        {
            my_cls();
            cout << "Create your own monster!\n";
            cout << "Enter a monster name: " << new_monster.name << endl;
            cout << "Enter the number of monster health units (1-50000): " << new_monster.xp << endl;
        }
        else
        {
            new_monster.damage = temp_damage;
            break;
        }
    }
    while (true)
    {
        cout << "Enter the monster's chance to launch a special attack (0.00 - 1.00): ";
        double temp_chance;
        cin >> temp_chance;
        if ((temp_chance < 0) || (temp_chance > 1))
        {
            my_cls();
            cout << "Create your own monster!\n";
            cout << "Enter a monster name: " << new_monster.name << endl;
            cout << "Enter the number of monster health units (1-50000): " << new_monster.xp << endl;
            cout << "Enter the number of monster attack units (1-1000): " << new_monster.damage << endl;
        }
        else
        {
            new_monster.chance = temp_chance;
            break;
        }
    }
    cout << "Choose one of the possible types of special monster attack:\n1)Increase damage.\n2)Repeat the attack.\n"
         << "3)Cure yourself.\n4)Paralyze the enemy.\n";
types_attack:
    switch (_getch())
    {
    case'1': new_monster.type_of_attack = "Increase damage";
        break;
    case'2': new_monster.type_of_attack = "Repeat the attack";
        break;
    case '3': new_monster.type_of_attack = "Cure yourself";
        break;
    case'4': new_monster.type_of_attack = "Paralyze the enemy";
        break;
    default: goto types_attack;
        break;
    }
    new_monster.id = set_id();
    my_cls();
    cout << "New monster created!\nHis personal ID: " << new_monster.id << endl;
    time_t seconds = time(NULL);
    ctime_s(new_monster.time_info,26,&seconds);
    all_monsters.push_back(new_monster);
    cout << "Creation date and time: " << new_monster.time_info<< endl;
    cout << "Press '0' to continue.\n";
    not_null:
    if (_getch() != '0') goto not_null;  
}
void write_monsters(std::vector<int> monsters_nombers)//виводить дані монстра на еран
{
    cout << "Monsters found:\n";
    for (int i = 0; i < monsters_nombers.size(); i++) 
    {
        cout << i + 1 << ".\n";
        cout <<"ID: " << all_monsters[monsters_nombers[i]].id << endl;
        cout << "Name: " <<all_monsters[monsters_nombers[i]].name << endl;
        cout << "XP: " <<all_monsters[monsters_nombers[i]].xp << endl;
        cout << "Damage: " << all_monsters[monsters_nombers[i]].damage << endl;
        cout << "Chance to launch a special attack: " << all_monsters[monsters_nombers[i]].chance << endl;
        cout << "Type of special monster attack: " << all_monsters[monsters_nombers[i]].type_of_attack << endl;
        cout << "Creation date and time: " << all_monsters[monsters_nombers[i]].time_info;
    }
}
void find_name()//пошук монстра по імені
{
    my_cls();
    cout << "Enter the full name or snippet of the monster name:\n";
    char fragment_name[200];
    std:: vector <int> nombers_monsters;
    scanf_s("%200s",fragment_name, (unsigned)_countof(fragment_name));
    int fragment_size = strlen(fragment_name);
    for (int i = 0; i < all_monsters.size(); i++)
    {
        char* p;
        p = all_monsters[i].name;
        cout << "p[" << i << "] = " << p << endl;
        int name_size = strlen(all_monsters[i].name);
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
    my_cls();
    if (nombers_monsters.size() == 0) cout << "Monster not found!\n";
    else write_monsters(nombers_monsters);
    cout << "Press '0' to exit.\n";
    not_null:
    if (_getch() != '0') goto not_null;

}
void Interactive_dialog_mode()
{
    next:
    my_cls();
    cout << "Menu:\n";
    cout << "1)Add a new monster.\n2)Find an existing monster.\n0)Back.\n";
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
        cout << "Select Monster Search Mode:\n1)Search by Name.\n2)Search by ID.\n";
        found_monstr:
        switch (_getch())
        {
            case '1':
            {
                find_name();
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
    next:
    my_cls();
    cout << "Select the application mode:\n1)Interactive dialog mode.\n2)Demo mode.\n3)Automatic benchmark mode.\n0)Exit.\n";
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
            cout << "Exit...";
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
