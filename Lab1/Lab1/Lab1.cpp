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

struct my_time
{
    int day;
    int month;
    int year;
    int sec;
    int min;
    int hour;  
};
struct info_monster
{
    unsigned int id;
    char name[200];
    unsigned int xp;//1-50000
    unsigned short int damage;//1-1000
    double chance;//0-1 
    short int type_of_attack;//збільшити пошкодження, повторити атаку,вилікувати себе, паралізувати супротивника; 
    char time_info[26];  
};
std:: vector<info_monster> all_monsters;//місце де зберігаються всі монстри
void my_cls()//очищує екран і виводить назву програми
{
    system("CLS");
    cout << "<The Forest of Monsters>"<< endl << endl;
}
void test_id()//temp
{
    srand(time(0));
    long int id_monster = (rand() % 90000 + 10000);
    cout << id_monster << endl;
    while (true)
    {
        srand(id_monster);
        id_monster = (rand() % 90000 + 10000);
        cout << id_monster << endl;
        cin.get();
    }
}
int stringtoint(char* string_months)//переводить місяць з string в int
{
    int int_months = 0;
    char all_months[12][4] = {"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
    for (int i = 0; i < 12; i++)
    {
        int k = 0;
        if (string_months[0] == all_months[i][0]) k++;
        if (string_months[0] == all_months[i][0]) k++;
        if (string_months[0] == all_months[i][0]) k++;
        if (k == 3)
        {
            int_months = i + 1;
            break;
        }
    }
    return int_months;
}
my_time set_time(int nomber_monster)//створює дату
{
    
    char* string_months = new char [4];
    my_time t;
    t.day = (all_monsters[nomber_monster].time_info[8] - '0') * 10 + (all_monsters[nomber_monster].time_info[9] - '0');
    string_months[0] = all_monsters[nomber_monster].time_info[4];
    string_months[1] = all_monsters[nomber_monster].time_info[5];
    string_months[2] = all_monsters[nomber_monster].time_info[6];
    string_months[3] = '\0';
    t.month = stringtoint(string_months);
    t.year = (all_monsters[nomber_monster].time_info[20] - '0')*1000 + (all_monsters[nomber_monster].time_info[21] - '0') * 100 + (all_monsters[nomber_monster].time_info[22] - '0') * 10 + (all_monsters[nomber_monster].time_info[23] - '0');
    t.hour = (all_monsters[nomber_monster].time_info[11] - '0') * 10 + (all_monsters[nomber_monster].time_info[12] - '0');
    t.min = (all_monsters[nomber_monster].time_info[14] - '0') * 10 + (all_monsters[nomber_monster].time_info[15] - '0');
    t.sec = (all_monsters[nomber_monster].time_info[17] - '0') * 10 + (all_monsters[nomber_monster].time_info[18] - '0');
    return t;
}
int set_id()//створює унікальний код
{
    srand(time(0));
    long int id_monster = (rand() % 90000 + 10000);
    bool flag = true;
    while (flag)
    {
        flag = false;
        for (int i = 0; i < all_monsters.size(); i++)
        {
            if (id_monster == all_monsters[i].id)
            {
                flag = true;
                srand(id_monster);
                id_monster = (rand() % 90000 + 10000);
                break;
            }
        }
    } 
    return id_monster;
}
void add_new_monster()//створює нового монстра
{
    my_cls();
    cout << "Create your own monster!\n";
    info_monster new_monster;
    cout << "Enter a monster name: ";
    gets_s(new_monster.name);
    if (strlen(new_monster.name) == 0) gets_s(new_monster.name);
    bool flag_xp = true, flag_damage = true, flag_chance = true;
    while (flag_xp)
    {
        cout << "Enter the number of monster health units (1-50000): ";
        int temp_xp = 0;
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
            flag_xp = false;
        }      
    }
    while (flag_damage)
    {
        cout << "Enter the number of monster attack units (1-1000): ";
        int temp_damage = 0;
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
            flag_damage = false;
        }
    }
    while (flag_chance)
    {
        cout << "Enter the monster's chance to launch a special attack (0.00 - 1.00): ";
        double temp_chance = 0;
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
            flag_chance = false;
        }
    }
    cout << "Choose one of the possible types of special monster attack:\n1)Increase damage.\n2)Repeat the attack.\n"
         << "3)Cure yourself.\n4)Paralyze the enemy.\n";
    types_attack:
    switch (_getch())
    {
    case'1': new_monster.type_of_attack = 1;
        break;
    case'2': new_monster.type_of_attack = 2;
        break;
    case '3': new_monster.type_of_attack = 3;
        break;
    case'4': new_monster.type_of_attack = 4;
        break;
    default: goto types_attack;
        break;
    }
    new_monster.id = set_id();
    my_cls();
    cout << "New monster created!\nHis personal ID: " << new_monster.id << endl;
    time_t seconds = time(NULL);
    ctime_s(new_monster.time_info, 26, &seconds);
    cout << "Creation date and time: " << new_monster.time_info << endl;
    all_monsters.push_back(new_monster);
    cout << "Press '0' to continue.\n";
    not_null:
    if (_getch() != '0') goto not_null;
}
void delete_monster()
{
    cout << "Enter id of monster: ";
    unsigned int monster_id;
    int nomber_monster_death = -1;
    cin >> monster_id;
    for (int i = 0; i < all_monsters.size(); i++)
    {
        if (monster_id == all_monsters[i].id)
        {
            nomber_monster_death = i;
            break;
        }
    }
    if (nomber_monster_death != -1)
    {

    }
}
void write_monsters(std::vector<int> monsters_nombers)//виводить дані монстра на еран
{
    char arr_types[][20] = {"Increase damage","Repeat the attack","Cure yourself","Paralyze the enemy"};
    cout << "Monsters found:\n";
    for (int i = 0; i < monsters_nombers.size(); i++) 
    {
        cout << i + 1 << ".\n";
        cout <<"ID: " << all_monsters[monsters_nombers[i]].id << endl;
        cout << "Name: " <<all_monsters[monsters_nombers[i]].name << endl;
        cout << "XP: " <<all_monsters[monsters_nombers[i]].xp << endl;
        cout << "Damage: " << all_monsters[monsters_nombers[i]].damage << endl;
        cout << "Chance to launch a special attack: " << all_monsters[monsters_nombers[i]].chance << endl;
        cout << "Type of special monster attack: " << arr_types[all_monsters[monsters_nombers[i]].type_of_attack - 1] << endl;
        cout << "Creation date and time: " << all_monsters[monsters_nombers[i]].time_info;
    }
}
void find_types_time()//пошук монстра по типу атки та часу створення
{
    my_cls();
    cout << "Enter one of the possible types of special monster attack:\n1)Increase damage.\n2)Repeat the attack.\n"
        << "3)Cure yourself.\n4)Paralyze the enemy.\n";
    int one_types_attack = 1;
types_attack:
    switch (_getch())
    {
    case '1': one_types_attack = 1;
        break;
    case '2': one_types_attack = 2;
        break;
    case '3': one_types_attack = 3;
        break;
    case '4': one_types_attack = 4;
        break;
    default: goto types_attack;
        break;
    }
    cout << "Enter the maximum date and time the monster was created.\n";
    my_time find_time;
    cout << "Enter year(1970-....): ";
    cin >> find_time.year;
    cout << "Enter month(1-12): ";
    cin >> find_time.month;
    cout << "Enter day(1-31): ";
    cin >> find_time.day;
    cout << "Enter hour(0-23): ";
    cin >> find_time.hour;
    cout << "Enter minute(0-59): ";
    cin >> find_time.min;
    cout << "Enter second(0-59): ";
    cin >> find_time.sec;
    my_cls();
    std::vector <int> nombers_monsters;
    for (int i = 0; i < all_monsters.size(); i++)
    {
        if (one_types_attack == all_monsters[i].type_of_attack)
        {
            my_time monster_time;
            monster_time = set_time(i);
            if (monster_time.year > find_time.year) continue;//1
            else
            {
                if (monster_time.year < find_time.year)//2
                {
                    nombers_monsters.push_back(i);
                    continue;
                }
                if (monster_time.month > find_time.month) continue;//1
                else
                {
                    if (monster_time.month < find_time.month)//2
                    {
                        nombers_monsters.push_back(i);
                        continue;
                    }
                    if (monster_time.day > find_time.day) continue;//1
                    else
                    {
                        if (monster_time.day < find_time.day)//2
                        {
                            nombers_monsters.push_back(i);
                            continue;
                        }
                        if(monster_time.hour > find_time.hour) continue;//1
                        else
                        {
                            if (monster_time.hour < find_time.hour)//2
                            {
                                nombers_monsters.push_back(i);
                                continue;
                            }
                            if (monster_time.min > find_time.min) continue;//1
                            else
                            {
                                if (monster_time.min < find_time.min)//2
                                {
                                    nombers_monsters.push_back(i);
                                    continue;
                                }
                                if (monster_time.sec > find_time.sec) continue;//1 
                                else
                                {
                                    if (monster_time.sec <= find_time.sec) nombers_monsters.push_back(i);//2
                                }
                            }
                        }
                    }
                }

            }
        }
    }
    if (nombers_monsters.size() == 0) cout << "Monster not found!\n";
    else write_monsters(nombers_monsters);
    cout << "\nPress '0' to exit.\n";
not_null:
    if (_getch() != '0') goto not_null;
}
void find_xp_damage()//пошук монстар по рівню життя і атаці
{
    my_cls();
    cout << "Enter minimum health level of monster(1-50000): ";
    int min_xp = 1,max_damage=1000;
    cin >> min_xp;
    cout << "Enter the maximum attack level of monster(1-1000): ";
    cin >> max_damage;
    my_cls();
    std::vector <int> nombers_monsters;
    for (int i = 0; i < all_monsters.size(); i++)
    {
        if ((min_xp <= all_monsters[i].xp) && (max_damage >= all_monsters[i].damage)) nombers_monsters.push_back(i);
    }
    if (nombers_monsters.size() == 0) cout << "Monster not found!\n";
    else write_monsters(nombers_monsters);
    cout << "/nPress '0' to exit.\n";
not_null:
    if (_getch() != '0') goto not_null;
}
void find_name()//пошук монстра по імені
{
    my_cls();
    cout << "Enter the full name or snippet of the monster name:\n";
    char fragment_name[200];
    std:: vector <int> nombers_monsters;
    gets_s(fragment_name);
    int fragment_size = strlen(fragment_name);
    if (fragment_size == 0) gets_s(fragment_name);
    my_cls();
    for (int i = 0; i < all_monsters.size(); i++)
    {
        char* p;
        p = all_monsters[i].name;
        int name_size = strlen(all_monsters[i].name);
        if (fragment_size > name_size) break;
        else
        {
            bool flag = true;
            for (int j = 0,k = 0,j_save = 0; (j_save + fragment_size) < name_size; j++)
            {
                if (p[j] == fragment_name[k])
                {
                    k++;
                    flag = true;
                    if (k >= fragment_size) break;
                }
                else
                {
                    k = 0;
                    j_save++;
                    j = j_save;
                    flag = false;
                }
            }
            if (flag) nombers_monsters.push_back(i);
        }
    }
    if (nombers_monsters.size() == 0) cout << "Monster not found!\n";
    else write_monsters(nombers_monsters);
    cout << "\nPress '0' to exit.\n";
not_null:
    if (_getch() != '0') goto not_null;
}
void Interactive_dialog_mode()
{
next:
    my_cls();
    cout << "Menu:\n";
    cout << "1)Add a new monster.\n2)Find an existing monster.\n3)Delete a monster.\n0)Back.\n";
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
        cout << "Select Monster Search Mode:\n1)Search by Name.\n2)Search by xp and damage.\n3)Search by type of special monster attack.\n";
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
                find_xp_damage();
                goto next;
            }
            break;
            case '3':
            {
                find_types_time();
                goto next;
            }
            break;
            default: goto found_monstr;
        }
    }
    break;
    case '3':
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
            test_id();
            goto next;
        }
        break;
        case '3':
        {
            my_time t;
            t = set_time(0);
            goto next;
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
