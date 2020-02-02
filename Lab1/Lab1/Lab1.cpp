// Lab1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <ctime>
#include <vector>
#include <string>
#include <fstream>
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;

struct my_time
{
    int hour;   
    int min;
    int sec;
    int day;
    int month;
    int year;
    
    my_time(int hour, int min, int sec, int day, int month, int year)
    {
        this->hour = hour;
        this->min = min;
        this->sec = sec;
        this->day = day;
        this->month = month;
        this->year = year;
    }
};
int set_id();//оголошення функції
my_time set_time(char[]);// -||-
bool save_binary_file(string);// -||-
bool save_text_file(string);// -||-
void write_all_monsters();// -||-
struct info_monster
{
    int id ;
    string name;
    unsigned int xp;//1-50000
    int damage ;//1-1000
    float chance;//0-1 
    string type_of_attack;//збільшити пошкодження, повторити атаку,вилікувати себе, паралізувати супротивника; 
    my_time time_info =  my_time(0, 0, 0, 0, 0, 1970);
    info_monster(string name, unsigned int xp, int damage, float chance, string type_of_attack,my_time time_info = my_time(0, 0, 0, 0, 0, 1970), int id = -1)
    {   
        this->name = name;
        this->xp = xp;
        this->damage = damage;
        this->chance = chance;
        this->type_of_attack = type_of_attack; 
        if (time_info.year == 1970)
        {
            time_t seconds = time(NULL);
            char time_char[26];
            ctime_s(time_char, 26, &seconds);
            this->time_info = set_time(time_char);
        }
        else this->time_info = time_info;       
        if (id == -1) this->id = set_id();
        else this->id = id;
    }
};
string binary_file_name = "binary.txt", text_file_name = "text.txt";
vector<info_monster> all_monsters;//місце де зберігаються всі монстри
void clean_arr()//очищує масив
{
    int arr_size = all_monsters.size();
    for(int i = 0; i < arr_size;i++) all_monsters.erase(all_monsters.begin());
}
void my_cls()//очищує екран і виводить назву програми
{
    system("CLS");
    cout << "<The Forest of Monsters>" << endl << endl;
}
bool create_text_file()
{
    std::ifstream file(text_file_name);
    if (!file.is_open())
    {

        file.close();
        std::ofstream file_create(text_file_name);
        file_create.close();
        return false;
    }
    file.close();
    return true;
}
bool create_binary_file()
{
    std::ifstream file(binary_file_name);
    if (!file.is_open())
    {

        file.close();
        std::ofstream file_create(binary_file_name,std::ios_base::binary);
        file_create.close();
        return false;
    }
    file.close();
    return true;
}
void open_file(bool t_or_b)//переносить інформацію з файла в масив
{
    if (t_or_b)
    {
        if (!create_text_file())
        {
            my_cls();
            cout << "File not found!...\n";
            cout << "New file created!\n";  
            cout << "\nPress '0' to exit.\n";
            create_binary_file();
        not_null_t:
            if (_getch() != '0') goto not_null_t;
        }
        else
        {
            std::ifstream file(text_file_name);
            while (!file.eof())
            {
                string name = "", type_of_attack = "";
                unsigned int id = 0,xp = 0,damage = 0;
                float chance = 2;
                int hour = 0, min = 0, sec = 0, day = 0, month = 0, year = 0;
                file >> id;
                getline(file, name);
                if (name.size() == 0) getline(file, name);
                file >> xp;
                file >> damage;
                file >> chance;
                getline(file, type_of_attack);
                if(type_of_attack.size()==0) getline(file, type_of_attack);            
                file >> hour >> min >> sec >> day >> month >> year;        
                if (xp==0) break;
                else all_monsters.push_back(info_monster(name, xp, damage, chance, type_of_attack, my_time(hour, min, sec, day, month, year), id));
            }
            file.close();
        }  
    }
    else
    {
        if (!create_binary_file())
        {
            my_cls();
            cout << "File not found!...\n";
            cout << "New file created!\n";
            create_text_file();
            cout << "\nPress '0' to exit.\n";
        not_null_b:
            if (_getch() != '0') goto not_null_b;
        }
        else
        {
            std::ifstream file(binary_file_name, std::ios_base::binary);
            while (!file.eof())
            {
                info_monster monster("0", 0, 0, 0,"0", my_time (0, 0, 0, 0, 0, 1980),0);
                file.read((char*)&monster, sizeof(monster));
                all_monsters.push_back(monster);
            }
            file.close();
        }
    }
}
bool save_text_file(string path)//переносить інформацію з масиву в текстовий файл
{
    std::ofstream file(path);
    if(!file.is_open()) return false;
    for (unsigned int i = 0; i < all_monsters.size(); i++)
    {
        file << all_monsters[i].id << endl;
        file << all_monsters[i].name << endl;
        file << all_monsters[i].xp << endl;
        file << all_monsters[i].damage << endl;
        file << all_monsters[i].chance << endl;
        file << all_monsters[i].type_of_attack << endl;
        file << all_monsters[i].time_info.hour << " " << all_monsters[i].time_info.min << " " << all_monsters[i].time_info.sec << " "
             << all_monsters[i].time_info.day << " " << all_monsters[i].time_info.month << " " << all_monsters[i].time_info.year << endl;
    }
    file.close();
    return true;
}
bool add_in_text_file(info_monster monster,string path)//додає інформацію в кінець текстового файлу
{
    std::ofstream file(path,std::ios_base::app);
    if (!file.is_open()) return false;
        file << monster.id << endl;
        file << monster.name << endl;
        file << monster.xp << endl;
        file << monster.damage << endl;
        file << monster.chance << endl;
        file << monster.type_of_attack << endl;
        file << monster.time_info.hour << " "  << monster.time_info.min << " " << monster.time_info.sec << " "
            << monster.time_info.day << " " << monster.time_info.month << " " << monster.time_info.year << endl;
    file.close();
    return true;
}
bool save_binary_file(string path)//переносить інформацію з масиву в бінарний файл
{
    std::ofstream file(path, std::ios_base::binary);
    if (!file.is_open()) return false;
    for (unsigned int i = 0; i < all_monsters.size(); i++)
    {
        file.write((char*)&all_monsters[i], sizeof(all_monsters[i]));
    }
    file.close();
    return true;
}
bool add_in_binary_file(info_monster monster,string path)//додає інформацію в кінець текстового файлу
{
    std::ofstream file(path, std::ios_base::binary|std::ios_base::app);
    if (!file.is_open()) return false;
    file.write((char*)&monster, sizeof(monster));
    file.close();
    return true;
}
int stringtoint(char* string_months)//переводить місяць з string в int
{
    int int_months = 0;
    char all_months[12][4] = { "Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec" };
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
void write_time(my_time t)//вииводить на екран час
{
    cout << "Creation time and date: ";
    if (t.hour / 10 == 0) cout << "0" << t.hour << ":";
    else cout << t.hour << ":";
    if (t.min / 10 == 0) cout << "0" << t.min << ":";
    else cout << t.min << ":";
    if (t.sec / 10 == 0) cout << "0" << t.sec << "  ";
    else cout << t.sec << "  ";
    if (t.day / 10 == 0) cout << "0" << t.day << ".";
    else cout << t.day << ".";
    if (t.month / 10 == 0) cout << "0" << t.month << ".";
    else cout << t.month << ".";
    cout << t.year <<endl;
}
my_time set_time(char time_char[])//переводить дату з рядка в структуру
{
    char* string_months = new char[4];
    int hour, min, sec, day, month, year;
    day = (time_char[8] - '0') * 10 + (time_char[9] - '0');
    if ((day <= 0) || (day >= 31))  day = (time_char[9] - '0');
    string_months[0] = time_char[4];
    string_months[1] = time_char[5];
    string_months[2] = time_char[6];
    string_months[3] = '\0';
    month = stringtoint(string_months);
    year = (time_char[20] - '0') * 1000 + (time_char[21] - '0') * 100 + (time_char[22] - '0') * 10 + (time_char[23] - '0');
    hour = (time_char[11] - '0') * 10 + (time_char[12] - '0');
    min = (time_char[14] - '0') * 10 + (time_char[15] - '0');
    sec = (time_char[17] - '0') * 10 + (time_char[18] - '0');
    return my_time(hour,min,sec,day,month,year);
}
int set_id()//створює унікальний код
{
    srand(time(0));
    long int id_monster = (rand() % 9000 + 1000);
    bool flag = true;
    while (flag)
    {
        flag = false;
        for (unsigned int i = 0; i < all_monsters.size(); i++)
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
    string name,type_of_attack;
    unsigned int xp, damage;
    float chance;
    cout << "Enter a monster name: ";
    getline(cin,name);
    if (name.size() == 0) getline(cin,name);
    while (true)
    {
        cout << "Enter the number of monster health units (1-50000): ";
        unsigned int temp_xp = 0;
        cin >> temp_xp;
        if ((temp_xp < 1) || (temp_xp > 50000))
        {
            my_cls();
            cout << "Create your own monster!\n";
            cout << "Enter a monster name: " << name << endl;
        }
        else
        {
            xp = temp_xp;
            break;
        }
    }
    while (true)
    {
        cout << "Enter the number of monster attack units (1-1000): ";
        int temp_damage = 0;
        cin >> temp_damage;
        if ((temp_damage < 1) || (temp_damage > 1000))
        {
            my_cls();
            cout << "Create your own monster!\n";
            cout << "Enter a monster name: " << name << endl;
            cout << "Enter the number of monster health units (1-50000): " << xp << endl;
        }
        else
        {
            damage = temp_damage;
            break;
        }
    }
    while (true)
    {
        cout << "Enter the monster's chance to launch a special attack (0.00 - 1.00): ";
        float temp_chance = 0;
        cin >> temp_chance;
        if ((temp_chance < 0) || (temp_chance > 1))
        {
            my_cls();
            cout << "Create your own monster!\n";
            cout << "Enter a monster name: " << name << endl;
            cout << "Enter the number of monster health units (1-50000): " << xp << endl;
            cout << "Enter the number of monster attack units (1-1000): " << damage << endl;
        }
        else
        {
            chance = temp_chance;
            break;
        }
    }
    cout << "Choose one of the possible types of special monster attack:\n1)Increase damage.\n2)Repeat the attack.\n"
        << "3)Cure yourself.\n4)Paralyze the enemy.\n";
types_attack:
    switch (_getch())
    {
    case'1': type_of_attack = "Increase damage";
        break;
    case'2': type_of_attack = "Repeat the attack";
        break;
    case '3': type_of_attack = "Cure yourself";
        break;
    case'4': type_of_attack = "Paralyze the enemy";
        break;
    default: goto types_attack;
    }
    info_monster new_monster (name, xp, damage, chance,type_of_attack);
    my_cls();
    cout << "New monster created!\nHis personal ID: " << new_monster.id << endl;   
    write_time(new_monster.time_info);
    all_monsters.push_back(new_monster);
    if (!add_in_text_file(new_monster, text_file_name)|| !add_in_binary_file(new_monster, binary_file_name))
    {
        my_cls();
        cout << "Error saving file!...\n";
    }
    cout << "Press '0' to continue.\n";
not_null:
    if (_getch() != '0') goto not_null;
}
void delete_monster()//видаляє монстра з вказаним ід
{
    my_cls();
    cout << "Enter id of monster: ";
    unsigned int monster_id;
    int nomber_monster_death = -1;
    cin >> monster_id;
    my_cls();
    for (unsigned int i = 0; i < all_monsters.size(); i++)
    {
        if (monster_id == all_monsters[i].id)
        {
            nomber_monster_death = i;
            break;
        }
    }
    if (nomber_monster_death != -1)
    {
        all_monsters.erase(all_monsters.begin() + nomber_monster_death);
        cout << "The monster - removed!\n";
        if (!save_text_file(text_file_name) || !save_binary_file(binary_file_name))
        {
            my_cls();
            cout << "Error saving file!...\n";
        }
    }
    else cout << "Monster not found!\n";
    cout << "\nPress '0' to exit.\n";
not_null:
    if (_getch() != '0') goto not_null;
}
void write_monsters(std::vector<int> monsters_nombers)//виводить дані монстра на еран
{
    cout << "Monsters found:\n";
    for (unsigned int i = 0; i < monsters_nombers.size(); i++)
    {
        cout << "<" << i + 1 << ">\n";
        cout << "ID: " << all_monsters[monsters_nombers[i]].id << ".\n";
        cout << "Name: " << all_monsters[monsters_nombers[i]].name <<".\n";
        cout << "XP: " << all_monsters[monsters_nombers[i]].xp << ".\n";
        cout << "Damage: " << all_monsters[monsters_nombers[i]].damage << ".\n";
        cout << "Chance to launch a special attack: " << all_monsters[monsters_nombers[i]].chance << ".\n";
        cout << "Type of special monster attack: " << all_monsters[monsters_nombers[i]].type_of_attack << "." << endl;
        write_time(all_monsters[monsters_nombers[i]].time_info);
    }
}
void write_all_monsters()//видає на екран дані всіх монстрів
{
    my_cls();
    std::vector<int> nombers;
    for (unsigned int i = 0; i < all_monsters.size(); i++) nombers.push_back(i);
    write_monsters(nombers);
    cout << "\nPress '0' to exit.\n";
not_null:
    if (_getch() != '0') goto not_null;
}
void find_types_time()//пошук монстра по типу атки та часу створення
{
    my_cls();
    cout << "Enter one of the possible types of special monster attack:\n1)Increase damage.\n2)Repeat the attack.\n"
        << "3)Cure yourself.\n4)Paralyze the enemy.\n";
    string one_types_attack = "Increase damage";
types_attack:
    switch (_getch())
    {
    case '1': one_types_attack = "Increase damage";
        break;
    case '2': one_types_attack = "Repeat the attack";
        break;
    case '3': one_types_attack = "Cure yourself";
        break;
    case '4': one_types_attack = "Paralyze the enemy";
        break;
    default: goto types_attack;
        break;
    }
    cout << "Enter the maximum date and time the monster was created.\n";
    int hour, min, sec, day, month, year;
    cout << "Enter year(1970-....): ";
    cin >> year;
    cout << "Enter month(1-12): ";
    cin >> month;
    cout << "Enter day(1-31): ";
    cin >> day;
    cout << "Enter hour(0-23): ";
    cin >> hour;
    cout << "Enter minute(0-59): ";
    cin >> min;
    cout << "Enter second(0-59): ";
    cin >> sec;
    my_time find_time(hour, min, sec, day, month, year);
    my_cls();
    std::vector <int> nombers_monsters;
    for (unsigned int i = 0; i < all_monsters.size(); i++)
    {
        if (one_types_attack == all_monsters[i].type_of_attack)
        {
            my_time monster_time = all_monsters[i].time_info;
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
                        if (monster_time.hour > find_time.hour) continue;//1
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
    unsigned int min_xp = 1, max_damage = 1000;
    cin >> min_xp;
    cout << "Enter the maximum attack level of monster(1-1000): ";
    cin >> max_damage;
    my_cls();
    std::vector <int> nombers_monsters;
    for (unsigned int i = 0; i < all_monsters.size(); i++)
    {
        if ((min_xp <= all_monsters[i].xp) && (max_damage >= all_monsters[i].damage)) nombers_monsters.push_back(i);
    }
    if (nombers_monsters.size() == 0) cout << "Monster not found!\n";
    else write_monsters(nombers_monsters);
    cout << "\nPress '0' to exit.\n";
not_null:
    if (_getch() != '0') goto not_null;
}
void find_name()//пошук монстра по імені
{
    my_cls();
    cout << "Enter the full name or snippet of the monster name:\n";
    string fragment_name;
    vector <int> nombers_monsters;
    getline(cin, fragment_name);
    if (fragment_name.size() == 0) getline(cin, fragment_name);
    int fragment_size = fragment_name.size();
    my_cls();
    for (unsigned int i = 0; i < all_monsters.size(); i++)
    {
        string s = all_monsters[i].name;
        int name_size = s.size();
        if (fragment_size > name_size) break;
        else
        {
            int k = 0;
            for (int j = 0, j_save = 0; (j_save + fragment_size) < (name_size + 1); j++)
            {
                if (s[j] == fragment_name[k])
                {
                    k++;
                    if (k >= fragment_size) break;
                }
                else
                {
                    j_save++;
                    k = 0;
                    j = j_save;
                    j--;
                }
            }
            if (k == fragment_size) nombers_monsters.push_back(i);
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
    my_cls();
    cout << "Select the opening mode:\n1)Text mode.\n2)Binary mode.\n";
 file_mode: 
    switch (_getch())
    {
        case '1': open_file(true);
            break;
        case '2': open_file(false);
            break;
        default: goto file_mode;
    }
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
        cout << "Select Monster Search Mode:\n1)Search by Name.\n2)Search by xp and damage.\n"
            << "3)Search by type of special monster attack.\n4)Show all the monsters.\n";
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
        case '4':
        {
            write_all_monsters();
            goto next;
        }
        break;
        default: goto found_monstr;
        }
    }
    break;
    case '3':
    {
        delete_monster();
        goto next;
    }
    break;
    case '0': 
    {
        if (!save_text_file(text_file_name) || !save_binary_file(binary_file_name))
        {
            my_cls();
            cout << "Error saving file!...\n";
            cout << "Press '0' to continue.\n";
        not_null_file:
            if (_getch() != '0') goto not_null_file;
        }
        if (!save_text_file("copy_text.txt") || !save_binary_file("copy_binary.txt"))
        {
            my_cls();
            cout << "Error saving copy file!...\n";
            cout << "Press '0' to continue.\n";
        not_null_copy:
            if (_getch() != '0') goto not_null_copy;
        }    
        clean_arr();
    }
        break;
    default: goto menu;
    }   
}
int main()//no coments
{
next:
    my_cls();
    cout << "Select the application mode:\n1)Interactive dialog mode.\n2)Demo mode.\n3)Automatic benchmark mode.\n0)Exit.\n";
mode:
    switch (_getch())
    {
    case '1':
    {
        Interactive_dialog_mode();       
        goto next;
    }
    break;
    case '2':
    {
        goto next;
    }
    break;
    case '3':
    {
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
