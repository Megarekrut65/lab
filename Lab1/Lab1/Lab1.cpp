#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <ctime>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>

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
    my_time()
    {
        this->hour = 0;
        this->min = 0;
        this->sec = 0;
        this->day = 0;
        this->month = 0;
        this->year = 1970;
    }
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
struct info_monster;
int set_id(vector<info_monster>);//оголошення функції
my_time set_time(char[]);// -||-
bool save_binary_file(string, vector<info_monster>);// -||-
bool save_text_file(string, vector<info_monster>);// -||-
void write_all_monsters(vector<info_monster>);// -||-
vector<int> find_types_time(string, my_time, vector<info_monster>);
vector<int> find_xp_damage(unsigned int, int, vector<info_monster>);
vector<int> find_name(string, vector<info_monster>);
struct info_monster
{
    int id;
    string name;
    unsigned int xp;
    int damage;
    double chance ; 
    string type_of_attack;
    my_time time_info;
    info_monster()
    {
        this->name = "NONE";
        this->xp = 0;
        this->damage = 0;
        this->chance = 0;
        this->type_of_attack = "NONE";
        this->time_info = my_time(0,0,0,0,0,1970);
        this->id = -1;
    }
    info_monster(vector<info_monster> all_monsters,string name, unsigned int xp, int damage, double chance, string type_of_attack,my_time time_info = my_time(0, 0, 0, 0, 0, 1970), int id = -1)
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
        if (id == -1) this->id = set_id(all_monsters);
        else this->id = id;
    }
};
struct result
{
    int number_n;
    float time;
    long int size;
};
string bin_file = "binary.bin", txt_file = "text.txt";//назви файлів
//vector<info_monster> all_monsters;//місце де зберігаються дані про всіх монстрів

void my_cls()//очищує екран і виводить назву програми
{
    system("CLS");
    cout << "<The Forest of Monsters>" << endl << endl;
}
bool create_text_file(string path)
{
    std::ifstream file(path);
    if (!file.is_open())
    {
        file.close();
        std::ofstream file_create(path);
        file_create.close();
        return false;
    }
    file.close();
    return true;
}
void open_text_file(string path,vector<info_monster>&all_monsters)//переносить інформацію з текстового файла в масив
{
    if (!create_text_file(path))
    {
        my_cls();
        cout << "File not found!...\n";
        cout << "New file created!\n";
        cout << "\nPress '0' to exit.\n";
    not_zero:
        if (_getch() != '0') goto not_zero;
    }
    else
    {
        std::ifstream file(path);
        while (!file.eof())
        {
            string name = "", type_of_attack = "";
            unsigned int id = 0, xp = 0, damage = 0;
            double chance = 2;
            int hour = 0, min = 0, sec = 0, day = 0, month = 0, year = 0;
            file >> id;
            getline(file, name);
            if (name.size() == 0) getline(file, name);
            file >> xp;
            file >> damage;
            file >> chance;
            getline(file, type_of_attack);
            if (type_of_attack.size() == 0) getline(file, type_of_attack);
            file >> hour >> min >> sec >> day >> month >> year;
            if (xp == 0) break;
            else all_monsters.push_back(info_monster(all_monsters,name, xp, damage, chance, type_of_attack, my_time(hour, min, sec, day, month, year), id));
        }
        file.close();
    }
}
bool save_text_file(string path, vector<info_monster> all_monsters)//переносить інформацію з масиву в текстовий файл
{
    std::ofstream file(path);
    if (!file.is_open()) return false;
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
bool add_in_text_file(info_monster monster, string path)//додає інформацію в кінець текстового файлу
{
    std::ofstream file(path, std::ios_base::app);
    if (!file.is_open()) return false;
    file << monster.id << endl;
    file << monster.name << endl;
    file << monster.xp << endl;
    file << monster.damage << endl;
    file << monster.chance << endl;
    file << monster.type_of_attack << endl;
    file << monster.time_info.hour << " " << monster.time_info.min << " " << monster.time_info.sec << " "
        << monster.time_info.day << " " << monster.time_info.month << " " << monster.time_info.year << endl;
    file.close();
    return true;
}
bool create_binary_file(string path)
{
    std::ifstream file(path, std::ios_base::binary);
    if (!file.is_open())
    {

        file.close();
        std::ofstream file_create(path, std::ios_base::binary);
        file_create.close();
        return false;
    }
    file.close();
    return true;
}
void open_binary_file(string path,vector<info_monster>& all_monsters)//переносить інформацію з бінарного файла в масив
{
    if (!create_binary_file(path))
    {
        my_cls();
        cout << "File not found!...\n";
        cout << "New file created!\n";
        cout << "\nPress '0' to exit.\n";
    not_zero:
        if (_getch() != '0') goto not_zero;
    }
    else
    {
        std::ifstream file(path, std::ios_base::binary);
        info_monster monster;
        while (!file.eof())
        {
            file.read((char*)&(monster.id), sizeof(monster.id));
            if (file.eof()) break;
            std::size_t size_name;
            file.read((char*)&size_name, sizeof(size_name));
            char* buffer_name = new char[size_name + 1];
            file.read(buffer_name, size_name);
            buffer_name[size_name] = '\0';
            monster.name = buffer_name;
            file.read((char*)&(monster.xp), sizeof(monster.xp));
            file.read((char*)&(monster.damage), sizeof(monster.damage));
            file.read((char*)&(monster.chance), sizeof(monster.chance));
            std::size_t size_type;
            file.read((char*)&size_type, sizeof(size_type));
            char* buffer_type = new char[size_type + 1];
            file.read(buffer_type, size_type);
            buffer_type[size_type] = '\0';
            monster.type_of_attack = buffer_type;
            file.read((char*)&(monster.time_info.hour), sizeof(monster.time_info.hour));
            file.read((char*)&(monster.time_info.min), sizeof(monster.time_info.min));
            file.read((char*)&(monster.time_info.sec), sizeof(monster.time_info.sec));
            file.read((char*)&(monster.time_info.day), sizeof(monster.time_info.day));
            file.read((char*)&(monster.time_info.month), sizeof(monster.time_info.month));
            file.read((char*)&(monster.time_info.year), sizeof(monster.time_info.year));
            all_monsters.push_back(monster);
            delete[] buffer_name;
            delete[] buffer_type;
        }
        file.close();
    }  
}
bool save_binary_file(string path, vector<info_monster> all_monsters)//переносить інформацію з масиву в бінарний файл
{
    std::ofstream file(path, std::ios_base::binary);
    if (!file.is_open()) return false;
    for (unsigned int i = 0; i < all_monsters.size(); i++)
    {
        file.write((char*)&(all_monsters[i].id), sizeof(all_monsters[i].id));
        std::size_t size_name = all_monsters[i].name.size();
        file.write((char*)&size_name, sizeof(size_name));
        const char* buffer_name = all_monsters[i].name.c_str();
        file.write(buffer_name, size_name);
        file.write((char*)&(all_monsters[i].xp), sizeof(all_monsters[i].xp));
        file.write((char*)&(all_monsters[i].damage), sizeof(all_monsters[i].damage));
        file.write((char*)&(all_monsters[i].chance), sizeof(all_monsters[i].chance));
        std::size_t size_type = all_monsters[i].type_of_attack.size();
        file.write((char*)&size_type, sizeof(size_type));
        const char* buffer_type = all_monsters[i].type_of_attack.c_str();
        file.write(buffer_type, size_type);
        file.write((char*)&(all_monsters[i].time_info.hour), sizeof(all_monsters[i].time_info.hour));
        file.write((char*)&(all_monsters[i].time_info.min), sizeof(all_monsters[i].time_info.min));
        file.write((char*)&(all_monsters[i].time_info.sec), sizeof(all_monsters[i].time_info.sec));
        file.write((char*)&(all_monsters[i].time_info.day), sizeof(all_monsters[i].time_info.day));
        file.write((char*)&(all_monsters[i].time_info.month), sizeof(all_monsters[i].time_info.month));
        file.write((char*)&(all_monsters[i].time_info.year), sizeof(all_monsters[i].time_info.year));
    }
    file.close();
    return true;
}
bool add_in_binary_file(info_monster monster,string path)//додає інформацію в кінець текстового файлу
{
    std::ofstream file(path, std::ios_base::binary|std::ios_base::app);
    if (!file.is_open()) return false;
    std::size_t size = sizeof(monster);
    file.write((char*)&(monster.id), sizeof(monster.id));
    std::size_t size_name = monster.name.size();
    file.write((char*)&size_name, sizeof(size_name));
    const char* buffer_name = monster.name.c_str();
    file.write(buffer_name, size_name);
    file.write((char*)&(monster.xp), sizeof(monster.xp));
    file.write((char*)&(monster.damage), sizeof(monster.damage));
    file.write((char*)&(monster.chance), sizeof(monster.chance));
    std::size_t size_type = monster.type_of_attack.size();
    file.write((char*)&size_type, sizeof(size_type));
    const char* buffer_type = monster.type_of_attack.c_str();
    file.write(buffer_type, size_type);
    file.write((char*)&(monster.time_info.hour), sizeof(monster.time_info.hour));
    file.write((char*)&(monster.time_info.min), sizeof(monster.time_info.min));
    file.write((char*)&(monster.time_info.sec), sizeof(monster.time_info.sec));
    file.write((char*)&(monster.time_info.day), sizeof(monster.time_info.day));
    file.write((char*)&(monster.time_info.month), sizeof(monster.time_info.month));
    file.write((char*)&(monster.time_info.year), sizeof(monster.time_info.year));
    file.close();
    return true;
}
void delete_file(const char* path)//видаляє файл
{
    std::remove(path);
}
int stringtoint(char* char_months)//переводить місяць з char[] в int
{
    char all_months[12][4] = { "Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec" };
    for (unsigned int i = 0; i < 12; i++)
    {
        int k = 0;
        if (char_months[0] == all_months[i][0]) k++;
        if (char_months[1] == all_months[i][1]) k++;
        if (char_months[2] == all_months[i][2]) k++;
        if (k == 3) return (i + 1);
    }
    return -1;
}
void write_time(my_time t)//виводить час на екран
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
    delete[] string_months;
    return my_time(hour,min,sec,day,month,year);
}
int set_id(vector<info_monster> all_monsters)//створює унікальний id
{
    srand(time(0));
    int id_monster = (rand() % 9000 + 1000);
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
                id_monster = (rand() % 9000 + 1000);
                break;
            }
        }
    }
    return id_monster;
}
void add_new_monster(vector<info_monster>& all_monsters)//створює нового монстра
{
    my_cls();
    cout << "Create your own monster!\n";
    string name,type_of_attack;
    unsigned int xp, damage;
    double chance;
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
        double temp_chance = 0;
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
    info_monster new_monster (all_monsters,name, xp, damage, chance,type_of_attack);
    my_cls();
    cout << "New monster created!\nHis personal ID: " << new_monster.id << endl;   
    write_time(new_monster.time_info);
    all_monsters.push_back(new_monster);
    if (!add_in_text_file(new_monster, txt_file)|| !add_in_binary_file(new_monster, bin_file))
    {
        my_cls();
        cout << "Error saving file!...\n";
    }
    cout << "\nPress '0' to continue.\n";
not_zero:
    if (_getch() != '0') goto not_zero;
}
void write_monsters(vector<int> monsters_nombers, vector<info_monster> all_monsters)//виводить дані монстрів на еран
{
    cout << "Monster(s) found:\n\n";
    for (unsigned int i = 0; i < monsters_nombers.size(); i++)
    {
        cout << "<" << i + 1 << ">\n";
        cout << "ID: " << all_monsters[monsters_nombers[i]].id << ".\n";
        cout << "Name: " << all_monsters[monsters_nombers[i]].name << ".\n";
        cout << "XP: " << all_monsters[monsters_nombers[i]].xp << ".\n";
        cout << "Damage: " << all_monsters[monsters_nombers[i]].damage << ".\n";
        cout << "Chance to launch a special attack: " << all_monsters[monsters_nombers[i]].chance << ".\n";
        cout << "Type of special monster attack: " << all_monsters[monsters_nombers[i]].type_of_attack << "." << endl;
        write_time(all_monsters[monsters_nombers[i]].time_info);
    }
}
void write_monster(int i, vector<info_monster> all_monsters)//виводить дані монстра на еран
{
    cout << "Monster found:\n\n";
    cout << "ID: " << all_monsters[i].id << ".\n";
    cout << "Name: " << all_monsters[i].name << ".\n";
    cout << "XP: " << all_monsters[i].xp << ".\n";
    cout << "Damage: " << all_monsters[i].damage << ".\n";
    cout << "Chance to launch a special attack: " << all_monsters[i].chance << ".\n";
    cout << "Type of special monster attack: " << all_monsters[i].type_of_attack << "." << endl;
    write_time(all_monsters[i].time_info);
}
int find_id(vector<info_monster> all_monsters)//шукає монстра по id
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
    if (nomber_monster_death != -1) return nomber_monster_death;

    return -1;
}
void edit_monster(vector<info_monster>& all_monsters)
{
    int number = find_id(all_monsters);
    my_cls();
    if (number != -1)
    {
    edit:
        my_cls();
        write_monster(number, all_monsters);
        cout << "\nSelect the option you want to edit:\n";
        cout << "1)Name.\n2)XP.\n3)Damage.\n4)Chance to launch a special attack.\n5)Type of special monster attack.\n0)Exit." <<endl;
        switch (_getch())
        {
            case '1':
            {
                my_cls();
                write_monster(number, all_monsters);
                cout << "\nEnter a new Name of monster: ";
                string new_name;
                getline(cin, new_name);
                if(new_name.size() == 0) getline(cin, new_name);
                all_monsters[number].name = new_name;
                goto edit;
            }
            break;
            case '2':
            {
                my_cls();
                write_monster(number, all_monsters);
                cout << "\nEnter a new XP of monster: ";
                unsigned int new_xp;
                cin >> new_xp;
                if ((new_xp >= 1) && (new_xp <= 50000)) all_monsters[number].xp = new_xp;
                goto edit;
            }
            break;
            case '3':
            {
                my_cls();
                write_monster(number, all_monsters);
                cout << "\nEnter a new Damage of monster: ";
                int new_damage;
                cin >> new_damage;
                if ((new_damage >= 1) && (new_damage <= 1000)) all_monsters[number].damage = new_damage;
                goto edit;
            }
            break;
            case '4':
            {
                my_cls();
                write_monster(number, all_monsters);
                cout << "\nEnter a new Chance of monster: ";
                double new_chance;
                cin >> new_chance;
                if ((new_chance >= 0) && (new_chance <= 1)) all_monsters[number].chance = new_chance;
                goto edit;
            }
            break;
            case '5':
            {
                my_cls();
                write_monster(number, all_monsters);
                cout << "\nChoose one of the possible types of special monster attack:\n1)Increase damage.\n2)Repeat the attack.\n"
                    << "3)Cure yourself.\n4)Paralyze the enemy.\n";
                string new_type;
            types_attack:
                switch (_getch())
                {
                case'1': new_type = "Increase damage";
                    break;
                case'2': new_type = "Repeat the attack";
                    break;
                case '3': new_type = "Cure yourself";
                    break;
                case'4': new_type = "Paralyze the enemy";
                    break;
                default: goto types_attack;
                }
                all_monsters[number].type_of_attack = new_type;
                goto edit;
            }
            break;
            case '0':
            break;
            default: goto edit;
        }
        if (!save_text_file(txt_file, all_monsters) || !save_binary_file(bin_file, all_monsters))
        {
            my_cls();
            cout << "Error saving file!...\n";
            cout << "\nPress '0' to exit.\n";
        file_err:
            if (_getch() != '0') goto  file_err;
        }     
    }
    else
    {
        cout << "Monster not found!\n";
        cout << "\nPress '0' to exit.\n";
    not_found:
        if (_getch() != '0') goto not_found;
    }
}
void delete_monster(vector<info_monster> &all_monsters)//видаляє монстра з вказаним ід
{
    int id = find_id(all_monsters);
    my_cls();
    if (id != -1)
    {
        all_monsters.erase(all_monsters.begin() + id);
        cout << "The monster - removed!\n";
        if (!save_text_file(txt_file, all_monsters) || !save_binary_file(bin_file, all_monsters))
        {
            my_cls();
            cout << "Error saving file!...\n";
        }
    }
    else cout << "Monster not found!\n";
    cout << "\nPress '0' to exit.\n";
not_zero:
    if (_getch() != '0') goto not_zero;
      
}
void write_all_monsters(vector<info_monster> all_monsters)//видає на екран дані всіх монстрів
{
    my_cls();
    std::vector<int> nombers;
    for (unsigned int i = 0; i < all_monsters.size(); i++) nombers.push_back(i);
    write_monsters(nombers, all_monsters);
    cout << "\nPress '0' to exit.\n";
not_null:
    if (_getch() != '0') goto not_null;
}
void find_types_time_menu(vector<info_monster> all_monsters)//меню для пошуку
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
    std::vector <int> numbers;
    numbers = find_types_time(one_types_attack, find_time, all_monsters);
    if (numbers.size() == 0) cout << "Monster not found!\n";
    else write_monsters(numbers, all_monsters);
    cout << "\nPress '0' to exit.\n";
not_zero:
    if (_getch() != '0') goto not_zero;
}
vector <int> find_types_time(string one_types_attack,my_time find_time,vector<info_monster>all_monsters)//пошук монстра по типу атки та часу створення
{  
    std::vector <int> numbers_monsters;
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
                    numbers_monsters.push_back(i);
                    continue;
                }
                if (monster_time.month > find_time.month) continue;//1
                else
                {
                    if (monster_time.month < find_time.month)//2
                    {
                        numbers_monsters.push_back(i);
                        continue;
                    }
                    if (monster_time.day > find_time.day) continue;//1
                    else
                    {
                        if (monster_time.day < find_time.day)//2
                        {
                            numbers_monsters.push_back(i);
                            continue;
                        }
                        if (monster_time.hour > find_time.hour) continue;//1
                        else
                        {
                            if (monster_time.hour < find_time.hour)//2
                            {
                                numbers_monsters.push_back(i);
                                continue;
                            }
                            if (monster_time.min > find_time.min) continue;//1
                            else
                            {
                                if (monster_time.min < find_time.min)//2
                                {
                                    numbers_monsters.push_back(i);
                                    continue;
                                }
                                if (monster_time.sec > find_time.sec) continue;//1 
                                else
                                {
                                    if (monster_time.sec <= find_time.sec) numbers_monsters.push_back(i);//2
                                }
                            }
                        }
                    }
                }

            }
        }
    }
   
    return numbers_monsters;
}
void find_xp_damage_menu(vector<info_monster> all_monsters)//меню для пошуку
{
    my_cls();
    cout << "Enter minimum health level of monster(1-50000): ";
    unsigned int min_xp = 1;
    int max_damage = 1000;
    cin >> min_xp;
    cout << "Enter the maximum attack level of monster(1-1000): ";
    cin >> max_damage;
    my_cls();
    vector <int> numbers;
    numbers = find_xp_damage(min_xp, max_damage, all_monsters);
    if (numbers.size() == 0) cout << "Monster not found!\n";
    else write_monsters(numbers, all_monsters);
    cout << "\nPress '0' to exit.\n";
not_zero:
    if (_getch() != '0') goto not_zero;
}
vector <int> find_xp_damage(unsigned int min_xp,int max_damage,vector<info_monster> all_monsters)//пошук монстар по рівню життя і атаки
{
    std::vector <int> numbers_monsters;
    for (unsigned int i = 0; i < all_monsters.size(); i++)
    {
        if ((min_xp <= all_monsters[i].xp) && (max_damage >= all_monsters[i].damage)) numbers_monsters.push_back(i);
    }   
    return numbers_monsters;
}
void find_name_menu(vector<info_monster> all_monsters)//меню для пошуку
{
    my_cls();
    cout << "Enter the full name or snippet of the monster name:\n";
    string fragment_name;
    getline(cin, fragment_name);
    if (fragment_name.size() == 0) getline(cin, fragment_name);
    my_cls();
    vector <int> numbers;
    numbers = find_name(fragment_name, all_monsters);
    if (numbers.size() == 0) cout << "Monster not found!\n";
    else write_monsters(numbers, all_monsters);
    cout << "\nPress '0' to exit.\n";
not_zero:
    if (_getch() != '0') goto not_zero;
}
vector <int> find_name(string fragment_name,vector<info_monster> all_monsters)//пошук монстра по імені
{
    vector <int> numbers_monsters;
    int fragment_size = fragment_name.size();
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
                    j = j_save - 1;
                }
            }
            if (k == fragment_size) numbers_monsters.push_back(i);
        }
    }
    return numbers_monsters;
}
void Interactive_dialog_mode()//інтерактивний діалоговий режим
{
    vector<info_monster> all_monsters;
    my_cls();
    cout << "Select the opening mode:\n1)Text mode.\n2)Binary mode.\n";
 file_mode: 
    switch (_getch())
    {
        case '1': open_text_file(txt_file,all_monsters);
            break;
        case '2': open_binary_file(bin_file,all_monsters);
            break;
        default: goto file_mode;
    }
menu:
    my_cls();
    cout << "Menu:\n1)Add a new monster.\n2)Find an existing monster.\n3)Edit a monster.\n4)Delete a monster.\n0)Back.\n";
    switch (_getch())
    {
    case '1':
    {
        add_new_monster(all_monsters);
        goto menu;
    }
    break;
    case '2':
    {
        my_cls();
        cout << "Select Monster Search Mode:\n1)Search by Name.\n2)Search by xp and damage.\n"
            << "3)Search by type of special monster attack and date.\n4)Show all the monsters.\n";
    found_monster:
        switch (_getch())
        {
        case '1':
        {
            find_name_menu(all_monsters);
            goto menu;
        }
        break;
        case '2':
        {
            find_xp_damage_menu(all_monsters);
            goto menu;
        }
        break;
        case '3':
        {
            find_types_time_menu(all_monsters);
            goto menu;
        }
        break;
        case '4':
        {
            write_all_monsters(all_monsters);
            goto menu;
        }
        break;
        default: goto found_monster;
        }
    }
    break;
    case '3':
    {
        edit_monster(all_monsters);
        goto menu;
    }
    case '4':
    {
        delete_monster(all_monsters);
        goto menu;
    }
    break;
    case '0': 
    {
        if (!save_text_file(txt_file,all_monsters) || !save_binary_file(bin_file,all_monsters))
        {
            my_cls();
            cout << "Error saving file!...\n";
            cout << "Press '0' to continue.\n";
        err_file:
            if (_getch() != '0') goto err_file;
        }  
        if (!save_text_file("copy_text.txt", all_monsters) || !save_binary_file("copy_binary.bin", all_monsters))
        {
            my_cls();
            cout << "Error saving copy file!...\n";
            cout << "Press '0' to continue.\n";
        err_copy:
            if (_getch() != '0') goto err_copy;
        }
        if (all_monsters.size() == 0)
        {
            delete_file("text.txt");
            delete_file("binary.bin");
            delete_file("copy_text.txt");
            delete_file("copy_binary.bin");
        }
        all_monsters.clear();
    }
        break;
    default: goto menu;
    }   
}
bool demo_cls(int n)//очищення екрану та затримка для демонстраційного режиму
{
    Sleep(n);
    my_cls();
    cout << "Demo mode (press any key to exit).\n\n";
    if (_kbhit()) return true;
    return false;
}
void demo_mode()//демонстраційний режим
{
    for (int j = 0; j < 1; j++)
    {
        int n = 1800;
        vector<info_monster> demo_monsters;
        srand(time(0));
        int id = set_id(demo_monsters);
        unsigned int demo_xp = (rand() % 50000 + 1);
        srand(time(0));
        int demo_damage = (rand() % 1000 + 1);
        srand(time(0));
        double demo_chance = 0.01 * (rand() % 100 + 1);
        string demo_type = "Increase damage";
        my_cls();
        cout << "Enter playback speed(normal = 1800): ";
        cin >> n;
        if (demo_cls(0)) continue;
        cout << "Select the application mode:\n1)Interactive dialog mode.\n2)Demo mode.\n3)Automatic benchmark mode.\n0)Exit.\n";
        if (demo_cls(n)) continue;
        cout << "Select the application mode:\n1)Interactive dialog mode. <- press\n2)Demo mode.\n3)Automatic benchmark mode.\n0)Exit.\n";
        //file mode
        if (demo_cls(n)) continue;
        cout << "Select the opening mode:\n1)Text mode.\n2)Binary mode.\n";
        if (demo_cls(n)) continue;
        cout << "Select the opening mode:\n1)Text mode. <- press\n2)Binary mode.\n";
        //add monster
        if (demo_cls(n)) continue;
        cout << "Menu:\n1)Add a new monster.\n2)Find an existing monster.\n3)Edit a monster.\n4)Delete a monster.\n0)Back.\n";
        if (demo_cls(n)) continue;
        cout << "Menu:\n1)Add a new monster. <- press\n2)Find an existing monster.\n3)Edit a monster.\n4)Delete a monster.\n0)Back.\n";
        if (demo_cls(n)) continue;
        cout << "Create your own monster!\nEnter a monster name: \n";
        if (demo_cls(n)) continue;
        cout << "Create your own monster!\nEnter a monster name: <- write a name and press <Enter>\n";
        if (demo_cls(n)) continue;
        cout << "Create your own monster!\nEnter a monster name: Name1\n";
        cout << "Enter the number of monster health units (1-50000): \n";
        if (demo_cls(n)) continue;
        cout << "Create your own monster!\nEnter a monster name: Name1\n";
        cout << "Enter the number of monster health units (1-50000): <- write a xp and press <Enter>\n";
        if (demo_cls(n)) continue;
        cout << "Create your own monster!\nEnter a monster name: Name1\n";
        cout << "Enter the number of monster health units (1-50000): " << demo_xp << endl;
        cout << "Enter the number of monster attack units (1-1000): \n";
        if (demo_cls(n)) continue;
        cout << "Create your own monster!\nEnter a monster name: Name1\n";
        cout << "Enter the number of monster health units (1-50000): " << demo_xp << endl;
        cout << "Enter the number of monster attack units (1-1000): <- write a damage and press <Enter>\n";
        if (demo_cls(n)) continue;
        cout << "Create your own monster!\nEnter a monster name: Name1\n";
        cout << "Enter the number of monster health units (1-50000): " << demo_xp << endl;
        cout << "Enter the number of monster attack units (1-1000): " << demo_damage << endl;
        cout << "Enter the monster's chance to launch a special attack (0.00 - 1.00): \n";
        if (demo_cls(n)) continue;
        cout << "Create your own monster!\nEnter a monster name: Name1\n";
        cout << "Enter the number of monster health units (1-50000): " << demo_xp << endl;
        cout << "Enter the number of monster attack units (1-1000): " << demo_damage << endl;
        cout << "Enter the monster's chance to launch a special attack (0.00 - 1.00): <- write a chance and press <Enter>\n";
        if (demo_cls(n)) continue;
        cout << "Create your own monster!\nEnter a monster name: Name1\n";
        cout << "Enter the number of monster health units (1-50000): " << demo_xp << endl;
        cout << "Enter the number of monster attack units (1-1000): " << demo_damage << endl;
        cout << "Enter the monster's chance to launch a special attack (0.00 - 1.00): " << demo_chance << endl;
        cout << "Choose one of the possible types of special monster attack:\n1)Increase damage.\n2)Repeat the attack.\n"
            << "3)Cure yourself.\n4)Paralyze the enemy.\n";
        if (demo_cls(n)) continue;
        cout << "Create your own monster!\nEnter a monster name: Name1\n";
        cout << "Enter the number of monster health units (1-50000): " << demo_xp << endl;
        cout << "Enter the number of monster attack units (1-1000): " << demo_damage << endl;
        cout << "Enter the monster's chance to launch a special attack (0.00 - 1.00): " << demo_chance << endl;
        cout << "Choose one of the possible types of special monster attack:\n1)Increase damage. <- press\n2)Repeat the attack.\n"
            << "3)Cure yourself.\n4)Paralyze the enemy.\n";
        if (demo_cls(n)) continue;
        cout << "New monster created!\nHis personal ID: " << id << endl;
        time_t seconds = time(NULL);
        char c[26];
        ctime_s(c, 26, &seconds);
        my_time t = set_time(c);
        info_monster monster = info_monster(demo_monsters,"Name1", demo_xp, demo_damage, demo_chance, "Increase damage", t, id);
        demo_monsters.push_back(monster);
        vector <int>number(1, 0);
        write_time(t);
        cout << "\nPress '0' to continue.\n";
        if (demo_cls(n)) continue;
        cout << "New monster created!\nHis personal ID: " << id << endl;
        write_time(t);
        cout << "\nPress '0' to continue. <- press\n";
        //find monster by name
        if (demo_cls(2*n)) continue;
        cout << "Menu:\n1)Add a new monster.\n2)Find an existing monster.\n3)Edit a monster.\n4)Delete a monster.\n0)Back.\n";
        if (demo_cls(n)) continue;
        cout << "Menu:\n1)Add a new monster.\n2)Find an existing monster. <- press\n3)Edit a monster.\n4)Delete a monster.\n0)Back.\n";
        if (demo_cls(n)) continue;
        cout << "Select Monster Search Mode:\n1)Search by Name.\n2)Search by xp and damage.\n"
            << "3)Search by type of special monster attack and date.\n4)Show all the monsters.\n";
        if (demo_cls(n)) continue;
        cout << "Select Monster Search Mode:\n1)Search by Name. <- press\n2)Search by xp and damage.\n"
            << "3)Search by type of special monster attack and date.\n4)Show all the monsters.\n";
        if (demo_cls(n)) continue;
        cout << "Enter the full name or snippet of the monster name:\n";
        if (demo_cls(n)) continue;
        cout << "Enter the full name or snippet of the monster name:\n   <- write a snippet and press <Enter>";
        if (demo_cls(n)) continue;
        cout << "Enter the full name or snippet of the monster name:\name";
        if (demo_cls(n)) continue;
        write_monsters(number,demo_monsters);
        cout << "\nPress '0' to continue.\n";
        if (demo_cls(n)) continue;
        write_monsters(number, demo_monsters);
        cout << "\nPress '0' to continue. <- press\n";
        if (demo_cls(2*n)) continue;
        //find monster by xp and damage
        cout << "Menu:\n1)Add a new monster.\n2)Find an existing monster.\n3)Edit a monster.\n4)Delete a monster.\n0)Back.\n";
        if (demo_cls(n)) continue;
        cout << "Menu:\n1)Add a new monster.\n2)Find an existing monster. <- press\n3)Edit a monster.\n4)Delete a monster.\n0)Back.\n";
        if (demo_cls(n)) continue;
        cout << "Select Monster Search Mode:\n1)Search by Name.\n2)Search by xp and damage.\n"
            << "3)Search by type of special monster attack and date.\n4)Show all the monsters.\n";
        if (demo_cls(n)) continue;
        cout << "Select Monster Search Mode:\n1)Search by Name.\n2)Search by xp and damage. <- press\n"
            << "3)Search by type of special monster attack and date.\n4)Show all the monsters.\n";
        if (demo_cls(n)) continue;
        cout << "Enter minimum health level of monster(1-50000): \n";
        if (demo_cls(n)) continue;
        cout << "Enter minimum health level of monster(1-50000): <- write a min xp and press <Enter>\n";
        if (demo_cls(n)) continue;
        cout << "Enter minimum health level of monster(1-50000): " << demo_xp << endl;
        cout << "Enter the maximum attack level of monster(1-1000): \n";
        if (demo_cls(n)) continue;
        cout << "Enter minimum health level of monster(1-50000): " << demo_xp << endl;
        cout << "Enter the maximum attack level of monster(1-1000): <- write a max damage and press <Enter>\n";
        if (demo_cls(n)) continue;
        cout << "Enter minimum health level of monster(1-50000): " << demo_xp << endl;
        cout << "Enter the maximum attack level of monster(1-1000): " << demo_damage << endl;
        if (demo_cls(n)) continue;
        write_monsters(number, demo_monsters);
        cout << "\nPress '0' to continue.\n";
        if (demo_cls(n)) continue;
        write_monsters(number, demo_monsters);
        cout << "\nPress '0' to continue. <- press\n";
        if (demo_cls(2*n)) continue;
        //find monster by type of special monster attack
        cout << "Menu:\n1)Add a new monster.\n2)Find an existing monster.\n3)Edit a monster.\n4)Delete a monster.\n0)Back.\n";
        if (demo_cls(n)) continue;
        cout << "Menu:\n1)Add a new monster.\n2)Find an existing monster. <- press\n3)Edit a monster.\n4)Delete a monster.\n0)Back.\n";
        if (demo_cls(n)) continue;
        cout << "Select Monster Search Mode:\n1)Search by Name.\n2)Search by xp and damage.\n"
            << "3)Search by type of special monster attack and date.\n4)Show all the monsters.\n";
        if (demo_cls(n)) continue;
        cout << "Select Monster Search Mode:\n1)Search by Name.\n2)Search by xp and damage.\n"
            << "3)Search by type of special monster attack and date. <- press\n4)Show all the monsters.\n";
        if (demo_cls(n)) continue;
        cout << "Enter one of the possible types of special monster attack:\n1)Increase damage.\n2)Repeat the attack.\n"
            << "3)Cure yourself.\n4)Paralyze the enemy.\n";
        if (demo_cls(n)) continue;
        cout << "Enter one of the possible types of special monster attack:\n1)Increase damage. <- press\n2)Repeat the attack.\n"
            << "3)Cure yourself.\n4)Paralyze the enemy.\n";
        if (demo_cls(n)) continue;
        cout << "Enter one of the possible types of special monster attack:\n1)Increase damage.\n2)Repeat the attack.\n"
            << "3)Cure yourself.\n4)Paralyze the enemy.\n";
        cout << "Enter the maximum date and time the monster was created.\n";
        cout << "Enter year(1970-....): \n";
        if (demo_cls(n)) continue;
        cout << "Enter one of the possible types of special monster attack:\n1)Increase damage.\n2)Repeat the attack.\n"
            << "3)Cure yourself.\n4)Paralyze the enemy.\n";
        cout << "Enter the maximum date and time the monster was created.\n";
        cout << "Enter year(1970-....): <- write max year and press <Enter>\n";
        if (demo_cls(n)) continue;
        cout << "Enter one of the possible types of special monster attack:\n1)Increase damage.\n2)Repeat the attack.\n"
            << "3)Cure yourself.\n4)Paralyze the enemy.\n";
        cout << "Enter the maximum date and time the monster was created.\n";
        cout << "Enter year(1970-....): 2030\n";
        cout << "Enter month(1-12): \n";
        if (demo_cls(n)) continue;
        cout << "Enter one of the possible types of special monster attack:\n1)Increase damage.\n2)Repeat the attack.\n"
            << "3)Cure yourself.\n4)Paralyze the enemy.\n";
        cout << "Enter the maximum date and time the monster was created.\n";
        cout << "Enter year(1970-....): 2030\n";
        cout << "Enter month(1-12): <- write max month and press <Enter>\n";
        if (demo_cls(n)) continue;
        cout << "Enter one of the possible types of special monster attack:\n1)Increase damage.\n2)Repeat the attack.\n"
            << "3)Cure yourself.\n4)Paralyze the enemy.\n";
        cout << "Enter the maximum date and time the monster was created.\n";
        cout << "Enter year(1970-....): 2030\n";
        cout << "Enter month(1-12): 12\n";
        cout << "Enter day(1-31): \n";
        if (demo_cls(n)) continue;
        cout << "Enter one of the possible types of special monster attack:\n1)Increase damage.\n2)Repeat the attack.\n"
            << "3)Cure yourself.\n4)Paralyze the enemy.\n";
        cout << "Enter the maximum date and time the monster was created.\n";
        cout << "Enter year(1970-....): 2030\n";
        cout << "Enter month(1-12): 12\n";
        cout << "Enter day(1-31): <- write max day and press <Enter>\n";
        if (demo_cls(n)) continue;
        cout << "Enter one of the possible types of special monster attack:\n1)Increase damage.\n2)Repeat the attack.\n"
            << "3)Cure yourself.\n4)Paralyze the enemy.\n";
        cout << "Enter the maximum date and time the monster was created.\n";
        cout << "Enter year(1970-....): 2030\n";
        cout << "Enter month(1-12): 12\n";
        cout << "Enter day(1-31): 31\n";
        cout << "Enter hour(0-23): \n";
        if (demo_cls(n)) continue;
        cout << "Enter one of the possible types of special monster attack:\n1)Increase damage.\n2)Repeat the attack.\n"
            << "3)Cure yourself.\n4)Paralyze the enemy.\n";
        cout << "Enter the maximum date and time the monster was created.\n";
        cout << "Enter year(1970-....): 2030\n";
        cout << "Enter month(1-12): 12\n";
        cout << "Enter day(1-31): 31\n";
        cout << "Enter hour(0-23): <- write max hour and press <Enter>\n";
        if (demo_cls(n)) continue;
        cout << "Enter one of the possible types of special monster attack:\n1)Increase damage.\n2)Repeat the attack.\n"
            << "3)Cure yourself.\n4)Paralyze the enemy.\n";
        cout << "Enter the maximum date and time the monster was created.\n";
        cout << "Enter year(1970-....): 2030\n";
        cout << "Enter month(1-12): 12\n";
        cout << "Enter day(1-31): 31\n";
        cout << "Enter hour(0-23): 23\n";
        cout << "Enter minute(0-59): \n";
        if (demo_cls(n)) continue;
        cout << "Enter one of the possible types of special monster attack:\n1)Increase damage.\n2)Repeat the attack.\n"
            << "3)Cure yourself.\n4)Paralyze the enemy.\n";
        cout << "Enter the maximum date and time the monster was created.\n";
        cout << "Enter year(1970-....): 2030\n";
        cout << "Enter month(1-12): 12\n";
        cout << "Enter day(1-31): 31\n";
        cout << "Enter hour(0-23): 23\n";
        cout << "Enter minute(0-59): <- write max min and press <Enter>\n";
        if (demo_cls(n)) continue;
        cout << "Enter one of the possible types of special monster attack:\n1)Increase damage.\n2)Repeat the attack.\n"
            << "3)Cure yourself.\n4)Paralyze the enemy.\n";
        cout << "Enter the maximum date and time the monster was created.\n";
        cout << "Enter year(1970-....): 2030\n";
        cout << "Enter month(1-12): 12\n";
        cout << "Enter day(1-31): 31\n";
        cout << "Enter hour(0-23): 23\n";
        cout << "Enter minute(0-59): 59\n";
        cout << "Enter second(0-59): \n";
        if (demo_cls(n)) continue;
        cout << "Enter one of the possible types of special monster attack:\n1)Increase damage.\n2)Repeat the attack.\n"
            << "3)Cure yourself.\n4)Paralyze the enemy.\n";
        cout << "Enter the maximum date and time the monster was created.\n";
        cout << "Enter year(1970-....): 2030\n";
        cout << "Enter month(1-12): 12\n";
        cout << "Enter day(1-31): 31\n";
        cout << "Enter hour(0-23): 23\n";
        cout << "Enter minute(0-59): 59\n";
        cout << "Enter second(0-59): <- write max sec and press <Enter>\n";
        if (demo_cls(n)) continue;
        cout << "Enter one of the possible types of special monster attack:\n1)Increase damage.\n2)Repeat the attack.\n"
            << "3)Cure yourself.\n4)Paralyze the enemy.\n";
        cout << "Enter the maximum date and time the monster was created.\n";
        cout << "Enter year(1970-....): 2030\n";
        cout << "Enter month(1-12): 12\n";
        cout << "Enter day(1-31): 31\n";
        cout << "Enter hour(0-23): 23\n";
        cout << "Enter minute(0-59): 59\n";
        cout << "Enter second(0-59): 59\n";
        if (demo_cls(n)) continue;
        write_monsters(number, demo_monsters);
        cout << "\nPress '0' to continue.\n";
        if (demo_cls(n)) continue;
        write_monsters(number, demo_monsters);
        cout << "\nPress '0' to continue. <- press\n";
        if (demo_cls(2*n)) continue;
        //Show all the monsters
        cout << "Menu:\n1)Add a new monster.\n2)Find an existing monster.\n3)Edit a monster.\n4)Delete a monster.\n0)Back.\n";
        if (demo_cls(n)) continue;
        cout << "Menu:\n1)Add a new monster.\n2)Find an existing monster. <- press\n3)Edit a monster.\n4)Delete a monster.\n0)Back.\n";
        if (demo_cls(n)) continue;
        cout << "Select Monster Search Mode:\n1)Search by Name.\n2)Search by xp and damage.\n"
            << "3)Search by type of special monster attack and date.\n4)Show all the monsters.\n";
        if (demo_cls(n)) continue;
        cout << "Select Monster Search Mode:\n1)Search by Name.\n2)Search by xp and damage.\n"
            << "3)Search by type of special monster attack and date.\n4)Show all the monsters. <- press\n";
        if (demo_cls(n)) continue;
        write_monsters(number, demo_monsters);
        cout << "\nPress '0' to continue.\n";
        if (demo_cls(n)) continue;
        write_monsters(number, demo_monsters);
        cout << "\nPress '0' to continue. <- press\n";
        if (demo_cls(2*n)) continue;
        //edit monster
        cout << "Menu:\n1)Add a new monster.\n2)Find an existing monster.\n3)Edit a monster.\n4)Delete a monster.\n0)Back.\n";
        if (demo_cls(n)) continue;
        cout << "Menu:\n1)Add a new monster.\n2)Find an existing monster.\n3)Edit a monster. <- press\n4)Delete a monster.\n0)Back.\n";
        if (demo_cls(n)) continue;
        cout << "Enter id of monster: ";
        if (demo_cls(n)) continue;
        cout << "Enter id of monster: <- write the id and press <Enter>";
        if (demo_cls(n)) continue;
        cout << "Enter id of monster: " << id;
        if (demo_cls(n)) continue;
        write_monster(0, demo_monsters);
        cout << "\nSelect the option you want to edit:\n";
        cout << "1)Name.\n2)XP.\n3)Damage.\n4)Chance to launch a special attack.\n5)Type of special monster attack.\n0)Exit." << endl;
        if (demo_cls(n)) continue;
        write_monster(0, demo_monsters);
        cout << "\nSelect the option you want to edit:\n";
        cout << "1)Name <- press.\n2)XP.\n3)Damage.\n4)Chance to launch a special attack.\n5)Type of special monster attack.\n0)Exit." << endl;
        if (demo_cls(n)) continue;
        write_monster(0, demo_monsters);
        cout << "\nEnter a new Name of monster: ";
        if (demo_cls(n)) continue;
        write_monster(0, demo_monsters);
        cout << "\nEnter a new Name of monster: <- write a new Name and press <Enter>";
        if (demo_cls(n)) continue;
        write_monster(0, demo_monsters);
        cout << "\nEnter a new Name of monster: Name2";
        demo_monsters[0].name = "Name2";
        if (demo_cls(n)) continue;
        write_monster(0, demo_monsters);
        cout << "\nSelect the option you want to edit:\n";
        cout << "1)Name.\n2)XP. <- press\n3)Damage.\n4)Chance to launch a special attack.\n5)Type of special monster attack.\n0)Exit." << endl;
        if (demo_cls(n)) continue;
        write_monster(0, demo_monsters);
        cout << "\nEnter a new XP of monster: ";
        if (demo_cls(n)) continue;
        write_monster(0, demo_monsters);
        cout << "\nEnter a new XP of monster: <- write a new XP and press <Enter>";
        if (demo_cls(n)) continue;
        write_monster(0, demo_monsters);
        cout << "\nEnter a new XP of monster: 20000";
        demo_monsters[0].xp = 20000;
        if (demo_cls(n)) continue;
        write_monster(0, demo_monsters);
        cout << "\nSelect the option you want to edit:\n";
        cout << "1)Name.\n2)XP.\n3)Damage. <- press\n4)Chance to launch a special attack.\n5)Type of special monster attack.\n0)Exit." << endl;
        if (demo_cls(n)) continue;
        write_monster(0, demo_monsters);
        cout << "\nEnter a new Damage of monster: ";
        if (demo_cls(n)) continue;
        write_monster(0, demo_monsters);
        cout << "\nEnter a new Damage of monster: <- write a new Damage and press <Enter>";
        if (demo_cls(n)) continue;
        write_monster(0, demo_monsters);
        cout << "\nEnter a new Damage of monster: 100";
        demo_monsters[0].damage = 100;
        if (demo_cls(n)) continue;
        write_monster(0, demo_monsters);
        cout << "\nSelect the option you want to edit:\n";
        cout << "1)Name.\n2)XP.\n3)Damage.\n4)Chance to launch a special attack. <- press\n5)Type of special monster attack.\n0)Exit." << endl;
        if (demo_cls(n)) continue;
        write_monster(0, demo_monsters);
        cout << "\nEnter a new Chance of monster: ";
        if (demo_cls(n)) continue;
        write_monster(0, demo_monsters);
        cout << "\nEnter a new Chance of monster: <- write a new Chence and press <Enter>";
        if (demo_cls(n)) continue;
        write_monster(0, demo_monsters);
        cout << "\nEnter a new Chance of monster: 0.11";
        demo_monsters[0].chance = 0.11;
        if (demo_cls(n)) continue;
        write_monster(0, demo_monsters);
        cout << "\nSelect the option you want to edit:\n";
        cout << "1)Name.\n2)XP.\n3)Damage.\n4)Chance to launch a special attack.\n5)Type of special monster attack. <- press\n0)Exit." << endl;
        if (demo_cls(n)) continue;
        write_monster(0, demo_monsters);
        cout << "Enter one of the possible types of special monster attack:\n1)Increase damage.\n2)Repeat the attack.\n"
            << "3)Cure yourself.\n4)Paralyze the enemy.\n";
        if (demo_cls(n)) continue;
        write_monster(0, demo_monsters);
        cout << "Enter one of the possible types of special monster attack:\n1)Increase damage.\n2)Repeat the attack. <- press\n"
            << "3)Cure yourself.\n4)Paralyze the enemy.\n";
        demo_monsters[0].type_of_attack = "Repeat the attack";
        if (demo_cls(n)) continue;
        write_monster(0, demo_monsters);
        cout << "\nSelect the option you want to edit:\n";
        cout << "1)Name.\n2)XP.\n3)Damage.\n4)Chance to launch a special attack.\n5)Type of special monster attack.\n0)Exit." << endl;
        if (demo_cls(n)) continue;
        write_monster(0, demo_monsters);
        cout << "\nSelect the option you want to edit:\n";
        cout << "1)Name.\n2)XP.\n3)Damage.\n4)Chance to launch a special attack.\n5)Type of special monster attack.\n0)Exit. <- press" << endl;
        if (demo_cls(2*n)) continue;
        //delete monster
        cout << "Menu:\n1)Add a new monster.\n2)Find an existing monster.\n3)Edit a monster.\n4)Delete a monster.\n0)Back.\n";
        if (demo_cls(n)) continue;
        cout << "Menu:\n1)Add a new monster.\n2)Find an existing monster.\n3)Edit a monster.\n4)Delete a monster. <- press\n0)Back.\n";
        if (demo_cls(n)) continue;
        cout << "Enter id of monster: ";
        if (demo_cls(n)) continue;
        cout << "Enter id of monster: <- write the id and press <Enter>";
        if (demo_cls(n)) continue;
        cout << "Enter id of monster: " << id;
        demo_monsters.erase(demo_monsters.begin());
        if (demo_cls(n)) continue;
        cout << "The monster - removed!\n";
        cout << "\nPress '0' to continue.\n";
        if (demo_cls(n)) continue;
        cout << "The monster - removed!\n";
        cout << "\nPress '0' to continue. <- press\n";
        if (demo_cls(n)) continue;
        //exit
        cout << "Menu:\n1)Add a new monster.\n2)Find an existing monster.\n3)Edit a monster.\n4)Delete a monster.\n0)Back.\n";
        if (demo_cls(n)) continue;
        cout << "Menu:\n1)Add a new monster.\n2)Find an existing monster.\n3)Edit a monster.\n4)Delete a monster.\n0)Back. <- press\n";
        if (demo_cls(n)) continue;
        cout << "Select the application mode:\n1)Interactive dialog mode.\n2)Demo mode.\n3)Automatic benchmark mode.\n0)Exit.\n";
        if (demo_cls(n)) continue;
        cout << "Select the application mode:\n1)Interactive dialog mode.\n2)Demo mode.\n3)Automatic benchmark mode.\n0)Exit. <- press\n";
        my_cls();
    }
    cout << "Demo mode is over!" << endl;
    Sleep(1800);
}
void monster_generator(vector<info_monster> save_monsters)//створює монстра з рандомними параметрами
{
    string name;
    int n = (rand() % 30 + 5), m = n;
    char* buff = new char[n + 1];
    for (int i = 0; i < n; i++)
    {
        srand(time(0) + m);
        m += 10;
        buff[i] = 'a' + (rand() % 26);
    }
    buff[n] = '\0';
    name = buff;
    unsigned int xp = (rand() % 50000 + 1);
    int damage = (rand() % 1000 + 1);
    double chance = 0.01 * (rand() % 100 + 1);
    string type;
    int k = (rand() % 4 + 1);
    switch (k)
    {
    case 1: type = "Increase damage";
        break;
    case 2: type = "Repeat the attack";
        break;
    case 3: type = "Cure yourself";
        break;
    case 4: type = "Paralyze the enemy";
        break;
    }
    save_monsters.push_back(info_monster(save_monsters,name, xp, damage, chance, type));
}
int size_file(string path)//вимірює розмір файла в байтах
{
    std::ifstream file(path);
    file.seekg(0, std::ios::end);
    int sizef = file.tellg();
    file.seekg(0, std::ios::beg);
    file.close();
    return sizef;
}
void add_program_test(string path,result date)//додає в файл інформацію про виміри
{
    bool f = create_text_file(path);
    if (f)
    {
        std::ofstream file(path, std::ios_base::app);
        file << "N: " << date.number_n << endl;
        file << "Time: " << date.time << endl;
        if(date.size != -1) file << "Size file:" << date.size << endl << endl;
        file.close();
    }
}
void benchmark_mode()// режим benchmark
{
    my_cls();
    int n;
    result name_find, xp_damage_find, time_type_find, open_bin, open_txt, save_bin, save_txt;
    name_find.size = -1;
    xp_damage_find.size = -1;
    time_type_find.size = -1;
    open_bin.size = -1;
    open_txt.size = -1;
    delete_file("result_save_txt_file.txt");
    delete_file("result_open_txt_file.txt");
    delete_file("result_save_binary_file.txt");
    delete_file("result_open_binary_file.txt");
    delete_file("result_name_find.txt");
    delete_file("result_xp_damage_find.txt");
    delete_file("result_time_type_find.txt");
    cout << "Enter N(1-...): ";
    cin >> n;
    auto the_start = std::chrono::high_resolution_clock::now();
    auto the_end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> duration;
    vector<info_monster> save_monsters;
    vector<info_monster> open_monsters;
    int m = n, k = 2;
    while (true)
    {
        for (int i = 0; i < m; i++) monster_generator(save_monsters);
        int k = save_monsters.size();
        cout << "\n\n        <N = " << k << ">\n";
        the_start = std::chrono::high_resolution_clock::now();
        save_text_file("benchmark_text.txt", save_monsters);
        the_end = std::chrono::high_resolution_clock::now();
        duration = the_end - the_start;
        save_txt.number_n = k;
        save_txt.time = duration.count();
        save_txt.size = size_file("benchmark_text.txt");
        add_program_test("result_save_txt_file.txt", save_txt);
        cout << "Time of save txt = " << save_txt.time << endl;
        cout << "Size of save txt = " << save_txt.size << endl;
        if (save_txt.time >= 10) break;
        //
        the_start = std::chrono::high_resolution_clock::now();
        open_text_file("benchmark_text.txt", open_monsters);
        the_end = std::chrono::high_resolution_clock::now();
        duration = the_end - the_start;
        open_txt.number_n = k;
        open_txt.time = duration.count();
        add_program_test("result_open_txt_file.txt", open_txt);
        cout << "Time of open txt = " << open_txt.time << endl;
        //
        vector <int> number;
        the_start = std::chrono::high_resolution_clock::now();
        number = find_name(open_monsters[k - 1].name, open_monsters);
        the_end = std::chrono::high_resolution_clock::now();
        duration = the_end - the_start;
        name_find.number_n = k;
        name_find.time = duration.count();
        add_program_test("result_name_find.txt", name_find);
        cout << "Time of find by name = " << name_find.time << endl;
        //
        the_start = std::chrono::high_resolution_clock::now();
        number = find_xp_damage(open_monsters[k - 1].xp, open_monsters[k - 1].damage, open_monsters);
        the_end = std::chrono::high_resolution_clock::now();
        duration = the_end - the_start;
        xp_damage_find.number_n = k;
        xp_damage_find.time = duration.count();
        add_program_test("result_xp_damage_find.txt", xp_damage_find);
        cout << "Time of find by xp and damage = " << xp_damage_find.time << endl;
        //
        the_start = std::chrono::high_resolution_clock::now();
        number = find_types_time(open_monsters[k - 1].type_of_attack, open_monsters[k - 1].time_info, open_monsters);
        the_end = std::chrono::high_resolution_clock::now();
        duration = the_end - the_start;
        time_type_find.number_n = k;
        time_type_find.time = duration.count();
        add_program_test("result_time_type_find.txt", time_type_find);
        cout << "Time of find by types of attack and time = " << time_type_find.time << endl;
        open_monsters.clear();
    }
    save_monsters.clear();
    while(true)
    {
        for (int j = 0; j < m; j++) (monster_generator(save_monsters));
        int k = save_monsters.size();
        cout << "\n\n        <N = " << k << ">\n";
        the_start = std::chrono::high_resolution_clock::now();
        save_binary_file("benchmark_binary.bin", save_monsters);
        the_end = std::chrono::high_resolution_clock::now();
        duration = the_end - the_start;
        save_bin.number_n = k;
        save_bin.time = duration.count();
        save_bin.size = size_file("benchmark_binary.bin");
        add_program_test("result_save_binary_file.txt", save_bin);
        cout << "Time save binary = " << save_bin.time << endl;
        cout << "Size save binary = " << save_bin.size << endl;     
        if (save_bin.time >= 10) break;
        //
        the_start = std::chrono::high_resolution_clock::now();
        open_binary_file("benchmark_binary.bin",open_monsters);
        the_end = std::chrono::high_resolution_clock::now();
        duration = the_end - the_start;
        open_bin.number_n = k;
        open_bin.time = duration.count();
        add_program_test("result_open_binary_file.txt", open_bin);
        cout <<"Time open binary = " << open_bin.time << endl;
        open_monsters.clear();
    }
    save_monsters.clear();
    cout << "\nResults of measurements of program in the following files:"
        << "\nresult_save_txt_file.txt\nresult_open_txt_file.txt\nresult_save_binary_file.txt\nresult_open_binary_file.txt"
        << "\nresult_name_find.txt\nresult_xp_damage_find.txt\nresult_time_type_find.txt" << endl;
    cout << "\nPress '0' to exit.\n";
not_zero:
    if (_getch() != '0') goto not_zero;
    delete_file("benchmark_text.txt");
    delete_file("benchmark_binary.bin");   
}
int main()//no coments
{
next:
    my_cls();
    cout << "Select the application mode:\n1)Interactive dialog mode.\n2)Demo mode.\n3)Automatic benchmark mode.\n0)Exit.\n";
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
        demo_mode();
        goto next;
    }
    break;
    case '3':
    {
        benchmark_mode();
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
    default: goto next;
    }

    return 0;
}

