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

enum types_of_attack{INCREASE,REPEAT,CURE,PARALYZE};
struct info_monster;
bool create_text_file(string);
void open_text_file(string);
bool save_text_file(string);
bool add_in_text_file(info_monster, string);
bool create_binary_file(string);
void open_binary_file(string);
bool save_binary_file(string);
bool add_in_binary_file(info_monster, string);
int string_to_int(char*);
unsigned set_id();
void add_new_monster();
void write_monster(int);
void write_monsters_menu(vector<int>);
void write_all_monsters();
void edit_monster();
void delete_monster();
void find_types_time_menu();
void find_xp_damage_menu();
void find_name_menu();
bool is_time(const int*, const int*, int);
vector <int> find_types_time(types_of_attack, const int*);
vector <int> find_xp_damage(unsigned, unsigned);
vector <int> find_name(string);
int find_id(unsigned);
void interactive_dialog_mode();

struct info_monster
{
    unsigned id;
    string name;
    unsigned hp;
    unsigned damage;
    double chance;
    types_of_attack type_of_attack;
    struct std::tm time_info;
    info_monster()
    {
        this->name = "NONE";
        this->hp = 0;
        this->damage = 0;
        this->chance = 0;
        this->type_of_attack = types_of_attack::INCREASE;
        this->time_info;
        this->id = -1;
    }
    info_monster(string name, unsigned hp, unsigned damage, double chance, types_of_attack type_of_attack, struct std::tm time_info, unsigned id = -1)
    {
        this->name = name;
        this->hp = hp;
        this->damage = damage;
        this->chance = chance;
        this->type_of_attack = type_of_attack;
        this->time_info = time_info;
        this->id = id;
    }
    info_monster(string name, unsigned hp, unsigned damage, double chance, types_of_attack type_of_attack)
    {
        this->name = name;
        this->hp = hp;
        this->damage = damage;
        this->chance = chance;
        this->type_of_attack = type_of_attack;
        time_t second = time(nullptr);
        struct std::tm timeinfo;
        localtime_s(&timeinfo, &second);
        this->time_info = timeinfo;
        this->id = set_id();
    }
};
struct result
{
    int number_n;
    float time;
    long int size;
};
string bin_file = "binary.bin", txt_file = "text.txt";//назви файлів
vector<info_monster> all_monsters;//місце де зберігаються дані про всіх монстрів

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
void open_text_file(string path)//переносить інформацію з текстового файла в масив
{
    if (!create_text_file(path))
    {
        cout << "File not found!...\n";
        cout << "New file created!\n";
    }
    else
    {
        std::ifstream file(path);
        while (!file.eof())
        {
            string name;
            types_of_attack type_of_attack;
            unsigned id, hp = 0, damage, type;
            double chance;
            struct std::tm time_info;
            file >> id;
            getline(file, name);
            if (name.size() == 0) getline(file, name);
            file >> hp;
            file >> damage;
            file >> chance;
            file >> type;
            switch (type)
            {
                case 0: type_of_attack = INCREASE;
                break;
                case 1: type_of_attack = REPEAT;
                break;
                case 2: type_of_attack = CURE;
                break;
                case 3: type_of_attack = PARALYZE;
            }
            file >> time_info.tm_hour >> time_info.tm_min >> time_info.tm_sec 
                 >> time_info.tm_mday >> time_info.tm_mon >> time_info.tm_year;
            if (hp == 0) break;
            else all_monsters.push_back(info_monster(name, hp, damage, chance, type_of_attack, time_info, id));
        }
        file.close();
    }
}
bool save_text_file(string path)//переносить інформацію з масиву в текстовий файл
{
    std::ofstream file(path);
    if (!file.is_open()) return false;
    for (unsigned i = 0; i < all_monsters.size(); i++)
    {
        file << all_monsters[i].id << endl;
        file << all_monsters[i].name << endl;
        file << all_monsters[i].hp << endl;
        file << all_monsters[i].damage << endl;
        file << all_monsters[i].chance << endl;
        file << all_monsters[i].type_of_attack << endl;
        file << all_monsters[i].time_info.tm_hour << " " << all_monsters[i].time_info.tm_min << " " << all_monsters[i].time_info.tm_sec << " "
            << all_monsters[i].time_info.tm_mday << " " << all_monsters[i].time_info.tm_mon << " " << all_monsters[i].time_info.tm_year << endl;
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
    file << monster.hp << endl;
    file << monster.damage << endl;
    file << monster.chance << endl;
    file << monster.type_of_attack << endl;
    file << monster.time_info.tm_hour << " " << monster.time_info.tm_min << " " << monster.time_info.tm_sec << " "
        << monster.time_info.tm_mday << " " << monster.time_info.tm_mon << " " << monster.time_info.tm_year << endl;
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
void open_binary_file(string path)//переносить інформацію з бінарного файла в масив
{
    if (!create_binary_file(path))
    {
        cout << "File not found!...\n";
        cout << "New file created!\n";
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
            file.read((char*)&(monster.hp), sizeof(monster.hp));
            file.read((char*)&(monster.damage), sizeof(monster.damage));
            file.read((char*)&(monster.chance), sizeof(monster.chance));
            file.read((char*)&(monster.type_of_attack), sizeof(monster.type_of_attack));       
            file.read((char*)&(monster.time_info.tm_hour), sizeof(monster.time_info.tm_hour));
            file.read((char*)&(monster.time_info.tm_min), sizeof(monster.time_info.tm_min));
            file.read((char*)&(monster.time_info.tm_sec), sizeof(monster.time_info.tm_sec));
            file.read((char*)&(monster.time_info.tm_mday), sizeof(monster.time_info.tm_mday));
            file.read((char*)&(monster.time_info.tm_mon), sizeof(monster.time_info.tm_mon));
            file.read((char*)&(monster.time_info.tm_year), sizeof(monster.time_info.tm_year));
            all_monsters.push_back(monster);
            delete[] buffer_name;
        }
        file.close();
    }
}
bool save_binary_file(string path)//переносить інформацію з масиву в бінарний файл
{
    std::ofstream file(path, std::ios_base::binary);
    if (!file.is_open()) return false;
    for (unsigned i = 0; i < all_monsters.size(); i++)
    {
        file.write((char*)&(all_monsters[i].id), sizeof(all_monsters[i].id));
        std::size_t size_name = all_monsters[i].name.size();
        file.write((char*)&size_name, sizeof(size_name));
        const char* buffer_name = all_monsters[i].name.c_str();
        file.write(buffer_name, size_name);
        file.write((char*)&(all_monsters[i].hp), sizeof(all_monsters[i].hp));
        file.write((char*)&(all_monsters[i].damage), sizeof(all_monsters[i].damage));
        file.write((char*)&(all_monsters[i].chance), sizeof(all_monsters[i].chance));
        file.write((char*)&(all_monsters[i].type_of_attack), sizeof(all_monsters[i].type_of_attack));
        file.write((char*)&(all_monsters[i].time_info.tm_hour), sizeof(all_monsters[i].time_info.tm_hour));
        file.write((char*)&(all_monsters[i].time_info.tm_min), sizeof(all_monsters[i].time_info.tm_min));
        file.write((char*)&(all_monsters[i].time_info.tm_sec), sizeof(all_monsters[i].time_info.tm_sec));
        file.write((char*)&(all_monsters[i].time_info.tm_mday), sizeof(all_monsters[i].time_info.tm_mday));
        file.write((char*)&(all_monsters[i].time_info.tm_mon), sizeof(all_monsters[i].time_info.tm_mon));
        file.write((char*)&(all_monsters[i].time_info.tm_year), sizeof(all_monsters[i].time_info.tm_year));
    }
    file.close();
    return true;
}
bool add_in_binary_file(info_monster monster, string path)//додає інформацію в кінець текстового файлу
{
    std::ofstream file(path, std::ios_base::binary | std::ios_base::app);
    if (!file.is_open()) return false;
    file.write((char*)&(monster.id), sizeof(monster.id));
    std::size_t size_name = monster.name.size();
    file.write((char*)&size_name, sizeof(size_name));
    const char* buffer_name = monster.name.c_str();
    file.write(buffer_name, size_name);
    file.write((char*)&(monster.hp), sizeof(monster.hp));
    file.write((char*)&(monster.damage), sizeof(monster.damage));
    file.write((char*)&(monster.chance), sizeof(monster.chance));
    file.write((char*)&(monster.type_of_attack), sizeof(monster.type_of_attack));
    file.write((char*)&(monster.time_info.tm_hour), sizeof(monster.time_info.tm_hour));
    file.write((char*)&(monster.time_info.tm_min), sizeof(monster.time_info.tm_min));
    file.write((char*)&(monster.time_info.tm_sec), sizeof(monster.time_info.tm_sec));
    file.write((char*)&(monster.time_info.tm_mday), sizeof(monster.time_info.tm_mday));
    file.write((char*)&(monster.time_info.tm_mon), sizeof(monster.time_info.tm_mon));
    file.write((char*)&(monster.time_info.tm_year), sizeof(monster.time_info.tm_year));
    file.close();
    return true;
}
int string_to_int(char* char_months)//переводить місяць з char[] в int
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
string read_name(string sentence)
{
    string name;
    cout << sentence;
    getline(cin, name);
    while (name.size() == 0) getline(cin, name);
    return name;
}
unsigned read_hp(string sentence)
{
    while (true)
    {
        cout << sentence;
        unsigned hp;
        cin >> hp;
        if ((hp < 1) || (hp > 50000)) cout << "\nData entered incorrectly!\n";
        else return hp;
    }
}
unsigned read_damage(string sentence)
{
    while (true)
    {
        cout << sentence;
        unsigned damage ;
        cin >> damage;
        if ((damage < 1) || (damage > 1000)) cout << "\nData entered incorrectly!\n";
        else return damage;
    }
}
double read_chance(string sentence)
{
    while (true)
    {
        cout << sentence;
        string chance_string;
        getline(cin, chance_string);
        while (chance_string.size() == 0) getline(cin, chance_string);
        if ((chance_string.size() != 1) && (chance_string[1] != '.') && (chance_string[1] != ',')) cout << "\nData entered incorrectly!" << endl;
        else
        {
            double chance = 0, coefficient = 1;
            for (unsigned i = 0; i < chance_string.size(); i++)
            {
                if (i == 1) i++;
                chance += coefficient * (int(chance_string[i]) - 48);
                coefficient /= 10;
            }
            if ((chance < 0) || (chance > 1)) cout << "\nData entered incorrectly!"<<endl;
            else return chance;
        }       
    }
}
types_of_attack read_type(string sentence)
{
    while (true)
    {
        cout << sentence;
        switch (_getch())
        {
        case '1': return INCREASE;
        case '2': return REPEAT;
        case '3': return CURE;
        case '4': return PARALYZE;
        default: cout << "\nPress the correct key!" << endl;
        }
    }
}
void write_time(struct std::tm time_info)
{
    char buffer[80];
    strftime(buffer, 80, "Creation time and date: %X  %d.%m.%Y\n", &time_info);
    cout << buffer;
}
void add_new_monster()//створює нового монстра
{
    cout << "\nCreate your own monster!" << endl;
    string name = read_name("\nEnter a monster name: ");
    unsigned hp = read_hp("\nEnter the number of monster health units (1-50000): ");
    unsigned damage = read_damage("\nEnter the number of monster attack units (1-1000): ");
    double chance = read_chance("\nEnter the monster's chance to launch a special attack (0.00 - 1.00): ");
    types_of_attack type_of_attack = read_type("\nChoose one of the possible types of special monster attack:\n1)Increase damage.\n2)Repeat the attack.\n3)Cure yourself.\n4)Paralyze the enemy.\n");
    info_monster new_monster(name, hp, damage, chance, type_of_attack);
    cout << "\nNew monster created!\nHis personal ID: " << new_monster.id << endl;
    write_time(new_monster.time_info);
    all_monsters.push_back(new_monster);
    if (!add_in_text_file(new_monster, txt_file) || !add_in_binary_file(new_monster, bin_file)) cout << "\nError saving file!..." << endl;
}
void write_monster(int number)//виводить дані монстра на еран
{
    cout << "ID: " << all_monsters[number].id << ".\n";
    cout << "Name: " << all_monsters[number].name << ".\n";
    cout << "XP: " << all_monsters[number].hp << ".\n";
    cout << "Damage: " << all_monsters[number].damage << ".\n";
    cout << "Chance to launch a special attack: " << all_monsters[number].chance << ".\n";
    cout << "Type of special monster attack: ";
    switch (all_monsters[number].type_of_attack) 
    {
    case INCREASE: cout << "Increase damage.\n";
        break;
    case REPEAT: cout << "Repeat the attack.\n";
        break;
    case CURE: cout << "Cure yourself.\n";
        break;
    case PARALYZE: cout << "Paralyze the enemy.\n";
    }
    write_time(all_monsters[number].time_info);
}
void write_monsters_menu(vector<int> numbers)
{
    if (numbers.size() == 0) cout << "\nMonster(s) don`t found!" << endl;
    else
    {
        cout << "\nMonster(s) found:" << endl;
        int n = 0;
        for (unsigned i = 0; i < numbers.size(); i++)
        {
            cout << "\n<" << ++n << ">" << endl;
            write_monster(numbers[i]);
        }
    }   
}
unsigned set_id()//створює унікальний id
{
    unsigned new_id = 1000;
    int size = all_monsters.size();
    if (size == 0) return new_id;
    else
    {
        new_id = all_monsters[size - 1].id + 1;
        return new_id;
    }
}
int find_id(unsigned monster_id)
{
    int number_monster_death = -1;
    for (unsigned i = 0; i < all_monsters.size(); i++)
    {
        if (monster_id == all_monsters[i].id)
        {
            number_monster_death = i;
            break;
        }
    }
    if (number_monster_death != -1) return number_monster_death;

    return -1;
}
void edit_monster()
{
    cout << "Enter id of monster: ";
    unsigned monster_id;
    cin >> monster_id;
    int number = find_id(monster_id);
    if (number != -1)
    {      
        while (true)
        {
            write_monster(number);
            cout << "\nSelect the option you want to edit:\n"
                << "1)Name.\n2)XP.\n3)Damage.\n4)Chance to launch a special attack.\n"
                << "5)Type of special monster attack.\n0)Exit." << endl;
            switch (_getch())
            {
            case '1':
                {
                    all_monsters[number].name = read_name("\nEnter a new Name of monster: ");
                    continue;
                }
                break;
            case '2':
                {
                    all_monsters[number].hp = read_hp("\nEnter a new HP of monster: ");
                    continue;
                }
                break;
            case '3':
                {
                    all_monsters[number].damage = read_damage("\nEnter a new Damage of monster: ");
                    continue;
                }
                break;
            case '4':
                {
                    all_monsters[number].chance = read_chance("\nEnter a new Chance of monster: ");
                    continue;
                }
                break;
            case '5':
                {             
                    all_monsters[number].type_of_attack = read_type("\nChoose one of the possible types of special monster attack:\n1)Increase damage.\n2)Repeat the attack.\n3)Cure yourself.\n4)Paralyze the enemy.\n");
                    continue;
                }
                break;
            case '0':
                break;
            default: 
                {
                    cout << "Press the correct key!\n";
                    continue;
                }
            }
        }
        if (!save_text_file(txt_file) || !save_binary_file(bin_file)) cout << "\nError saving file!..." << endl;
    }
    else cout << "\nMonster not found!" << endl;
}
void delete_monster()//видаляє монстра з вказаним ід
{
    cout << "\nEnter id of monster: ";
    unsigned monster_id;
    cin >> monster_id;
    int number = find_id(monster_id);
    if (number != -1)
    {
        all_monsters.erase(all_monsters.begin() + number);
        cout << "The monster - removed!\n";
        if (!save_text_file(txt_file) || !save_binary_file(bin_file)) cout << "\nError saving file!..." << endl;
    }
    else cout << "\nMonster not found!" << endl;
}
void write_all_monsters()//видає на екран дані всіх монстрів
{
    cout << "All monsters:" <<endl;
    for (unsigned i = 0; i < all_monsters.size(); i++)
    {
        cout << "\n<" << i + 1 << ">\n";
        write_monster(i);
    }
}
void find_types_time_menu()
{   
    types_of_attack one_types_attack = read_type("\nEnter one of the possible types of special monster attack:\n1)Increase damage.\n2)Repeat the attack.\n3)Cure yourself.\n4)Paralyze the enemy.\n");
    cout << "Enter the maximum date and time the monster was created.\n";
    int* find_time = new int[6];
    cout << "Enter year(1970-....): ";
    cin >> find_time[0];
    cout << "Enter month(1-12): ";
    cin >> find_time[1];
    cout << "Enter day(1-31): ";
    cin >> find_time[2];
    cout << "Enter hour(0-23): ";
    cin >> find_time[3];
    cout << "Enter minute(0-59): ";
    cin >> find_time[4];
    cout << "Enter second(0-59): ";
    cin >> find_time[5];
    write_monsters_menu(find_types_time(one_types_attack, find_time));
}
bool is_time(const int *find_time,const int* monster_time, int number = 0)
{

    if (monster_time[number] > find_time[number]) return false;
    else
    {
        if (number == 5) return true;
        if (monster_time[number] < find_time[number]) return true;
        return is_time(find_time, monster_time, number++);
    }
}
vector <int> find_types_time(types_of_attack one_types_attack, const int* find_time)//пошук монстра по типу атки та часу створення
{
    std::vector <int> numbers_monsters;
    for (unsigned i = 0; i < all_monsters.size(); i++)
    {
        if (one_types_attack == all_monsters[i].type_of_attack)
        {
            int* monster_time = new int[6];
            monster_time[0] = all_monsters[i].time_info.tm_year + 1900;
            monster_time[1] = all_monsters[i].time_info.tm_mon + 1;
            monster_time[2] = all_monsters[i].time_info.tm_mday;
            monster_time[3] = all_monsters[i].time_info.tm_hour;
            monster_time[4] = all_monsters[i].time_info.tm_min;
            monster_time[5] = all_monsters[i].time_info.tm_sec;
            for (int k = 0; k < 6; k++) cout << "t = " << monster_time[k] << endl;
            if (is_time(find_time, monster_time)) numbers_monsters.push_back(i);
            delete[]monster_time;
        }
    }

    return numbers_monsters;
}
void find_xp_damage_menu()
{
    cout << "Enter minimum health level of monster(1-50000): ";
    unsigned min_hp = 1;
    int max_damage = 1000;
    cin >> min_hp;
    cout << "Enter the maximum attack level of monster(1-1000): ";
    cin >> max_damage;
    write_monsters_menu(find_xp_damage(min_hp, max_damage));  
}
vector <int> find_xp_damage(unsigned min_hp, unsigned max_damage)//пошук монстар по рівню життя і атаки
{
    std::vector <int> numbers_monsters;
    for (unsigned i = 0; i < all_monsters.size(); i++)
    {
        if ((min_hp <= all_monsters[i].hp) && (max_damage >= all_monsters[i].damage)) numbers_monsters.push_back(i);
    }
    return numbers_monsters;
}
void find_name_menu()
{
    cout << "Enter the full name or snippet of the monster name:\n";
    string fragment_name;
    getline(cin, fragment_name);
    while(fragment_name.size() == 0) getline(cin, fragment_name);
    write_monsters_menu(find_name(fragment_name));
}
vector <int> find_name(string fragment_name)//пошук монстра по імені
{
    vector <int> numbers_monsters;
    int fragment_size = fragment_name.size();
    for (unsigned i = 0; i < all_monsters.size(); i++)
    {
        string name = all_monsters[i].name;
        int name_size = name.size();
        if (fragment_size <= name_size) 
        {
            for(unsigned j = 0; (j + fragment_size) <= name_size; j++)
            {
                if (name.substr(j, fragment_size) == fragment_name)
                {
                    numbers_monsters.push_back(i);
                    break;
                }
            }
        }
    }
    return numbers_monsters;
}
void monster_search()
{
    while (true)
    {
        cout << "Select Monster Search Mode:\n1)Search by Name.\n2)Search by xp and damage.\n"
            << "3)Search by type of special monster attack and date." << endl;
        switch (_getch())
        {
        case '1': find_name_menu();
            break;
        case '2': find_xp_damage_menu();
            break;
        case '3': find_types_time_menu();
            break;
        default:
            {
                cout << "Press the correct key!\n";
                continue;
            }
        }
        break;
    }
}
void interactive_dialog_mode()
{      
    while (true)
    {       
        cout << "\nSelect the opening mode:\n1)Text mode.\n2)Binary mode." << endl;
        switch (_getch())
        {
        case '1': open_text_file(txt_file);
            break;
        case '2': open_binary_file(bin_file);
            break;
        default:
            {
                cout << "\nPress the correct key!" <<endl;
                continue;
            }
        }
        break;
    }
    if (!save_text_file("copy_text.txt") || !save_binary_file("copy_binary.bin")) cout << "\nError saving copy file!..." << endl;
    while (true)
    {
        cout << "\nMenu:\n1)Add a new monster.\n2)Show all the monsters.\n3)Find an existing monster.\n"
             <<"4)Edit a monster.\n5)Delete a monster.\n0)Back." << endl;
        switch (_getch())
        {
        case '1': 
        {
            add_new_monster();
            continue;
        }
            break;
        case'2': 
        {
            write_all_monsters();
            continue;
        }
            break;
        case '3':
        {        
            monster_search();
            continue;
        }
            break;
        case '4': 
        {
            edit_monster();
            continue;
        }
            break;
        case '5': 
        {
            delete_monster();
            continue;
        }
            break;
        case '0':
            {
                if (!save_text_file(txt_file) || !save_binary_file(bin_file)) cout << "\nError saving file!..."<<endl;
                if (all_monsters.size() == 0)
                {
                    std::remove("text.txt");
                    std::remove("binary.bin");
                    std::remove("copy_text.txt");
                    std::remove("copy_binary.bin");
                }
                all_monsters.clear();
            }
            break;
        default:
            {
                cout << "\nPress the correct key!"<<endl;
                continue;
            }
        }
        break;
    }
}
bool demo_cls(int n)//очищення екрану та затримка для демонстраційного режиму
{
    Sleep(n);
    cout << "Demo mode (press any key to exit).\n\n";
    if (_kbhit()) return true;
    return false;
}
/*void demo_mode()//демонстраційний режим
{
    for (int j = 0; j < 1; j++)
    {
        int delay = 1800;
        srand(time(0));
        int id = set_id();
        unsigned int demo_xp = (rand() % 50000 + 1);
        int demo_damage = (rand() % 1000 + 1);
        double demo_chance = 0.01 * (rand() % 100 + 1);
        string demo_type = "Increase damage";
        //my_cls();
        cout << "Enter the playback delay in milliseconds(normal = 1800ms): ";
        cin >> delay;
        if (demo_cls(0)) continue;
        cout << "Select the application mode:\n1)Interactive dialog mode.\n2)Demo mode.\n3)Automatic benchmark mode.\n0)Exit.\n";
        if (demo_cls(delay)) continue;
        cout << "Select the application mode:\n1)Interactive dialog mode. <- press\n2)Demo mode.\n3)Automatic benchmark mode.\n0)Exit.\n";
        //file mode
        if (demo_cls(delay)) continue;
        cout << "Select the opening mode:\n1)Text mode.\n2)Binary mode.\n";
        if (demo_cls(delay)) continue;
        cout << "Select the opening mode:\n1)Text mode. <- press\n2)Binary mode.\n";
        //add monster
        if (demo_cls(delay)) continue;
        cout << "Menu:\n1)Add a new monster.\n2)Find an existing monster.\n3)Edit a monster.\n4)Delete a monster.\n0)Back.\n";
        if (demo_cls(delay)) continue;
        cout << "Menu:\n1)Add a new monster. <- press\n2)Find an existing monster.\n3)Edit a monster.\n4)Delete a monster.\n0)Back.\n";
        if (demo_cls(delay)) continue;
        cout << "Create your own monster!\nEnter a monster name: \n";
        if (demo_cls(delay)) continue;
        cout << "Create your own monster!\nEnter a monster name: <- write a name and press <Enter>\n";
        if (demo_cls(delay)) continue;
        cout << "Create your own monster!\nEnter a monster name: Name1\n";
        cout << "Enter the number of monster health units (1-50000): \n";
        if (demo_cls(delay)) continue;
        cout << "Create your own monster!\nEnter a monster name: Name1\n";
        cout << "Enter the number of monster health units (1-50000): <- write a xp and press <Enter>\n";
        if (demo_cls(delay)) continue;
        cout << "Create your own monster!\nEnter a monster name: Name1\n";
        cout << "Enter the number of monster health units (1-50000): " << demo_xp << endl;
        cout << "Enter the number of monster attack units (1-1000): \n";
        if (demo_cls(delay)) continue;
        cout << "Create your own monster!\nEnter a monster name: Name1\n";
        cout << "Enter the number of monster health units (1-50000): " << demo_xp << endl;
        cout << "Enter the number of monster attack units (1-1000): <- write a damage and press <Enter>\n";
        if (demo_cls(delay)) continue;
        cout << "Create your own monster!\nEnter a monster name: Name1\n";
        cout << "Enter the number of monster health units (1-50000): " << demo_xp << endl;
        cout << "Enter the number of monster attack units (1-1000): " << demo_damage << endl;
        cout << "Enter the monster's chance to launch a special attack (0.00 - 1.00): \n";
        if (demo_cls(delay)) continue;
        cout << "Create your own monster!\nEnter a monster name: Name1\n";
        cout << "Enter the number of monster health units (1-50000): " << demo_xp << endl;
        cout << "Enter the number of monster attack units (1-1000): " << demo_damage << endl;
        cout << "Enter the monster's chance to launch a special attack (0.00 - 1.00): <- write a chance and press <Enter>\n";
        if (demo_cls(delay)) continue;
        cout << "Create your own monster!\nEnter a monster name: Name1\n";
        cout << "Enter the number of monster health units (1-50000): " << demo_xp << endl;
        cout << "Enter the number of monster attack units (1-1000): " << demo_damage << endl;
        cout << "Enter the monster's chance to launch a special attack (0.00 - 1.00): " << demo_chance << endl;
        cout << "Choose one of the possible types of special monster attack:\n1)Increase damage.\n2)Repeat the attack.\n"
            << "3)Cure yourself.\n4)Paralyze the enemy.\n";
        if (demo_cls(delay)) continue;
        cout << "Create your own monster!\nEnter a monster name: Name1\n";
        cout << "Enter the number of monster health units (1-50000): " << demo_xp << endl;
        cout << "Enter the number of monster attack units (1-1000): " << demo_damage << endl;
        cout << "Enter the monster's chance to launch a special attack (0.00 - 1.00): " << demo_chance << endl;
        cout << "Choose one of the possible types of special monster attack:\n1)Increase damage. <- press\n2)Repeat the attack.\n"
            << "3)Cure yourself.\n4)Paralyze the enemy.\n";
        if (demo_cls(delay)) continue;
        cout << "New monster created!\nHis personal ID: " << id << endl;
        time_t seconds = time(NULL);
        char c[26];
        ctime_s(c, 26, &seconds);
        my_time t = set_time(c);
        info_monster monster = info_monster("Name1", demo_xp, demo_damage, demo_chance, "Increase damage", t, id);
        all_monsters.push_back(monster);
        vector <int>number(1, 0);
        write_time(t);
        cout << "\nPress '0' to continue.\n";
        if (demo_cls(delay)) continue;
        cout << "New monster created!\nHis personal ID: " << id << endl;
        write_time(t);
        cout << "\nPress '0' to continue. <- press\n";
        //find monster by name
        if (demo_cls(2 * delay)) continue;
        cout << "Menu:\n1)Add a new monster.\n2)Find an existing monster.\n3)Edit a monster.\n4)Delete a monster.\n0)Back.\n";
        if (demo_cls(delay)) continue;
        cout << "Menu:\n1)Add a new monster.\n2)Find an existing monster. <- press\n3)Edit a monster.\n4)Delete a monster.\n0)Back.\n";
        if (demo_cls(delay)) continue;
        cout << "Select Monster Search Mode:\n1)Search by Name.\n2)Search by xp and damage.\n"
            << "3)Search by type of special monster attack and date.\n4)Show all the monsters.\n";
        if (demo_cls(delay)) continue;
        cout << "Select Monster Search Mode:\n1)Search by Name. <- press\n2)Search by xp and damage.\n"
            << "3)Search by type of special monster attack and date.\n4)Show all the monsters.\n";
        if (demo_cls(delay)) continue;
        cout << "Enter the full name or snippet of the monster name:\n";
        if (demo_cls(delay)) continue;
        cout << "Enter the full name or snippet of the monster name:\n   <- write a snippet and press <Enter>";
        if (demo_cls(delay)) continue;
        cout << "Enter the full name or snippet of the monster name:\name";
        if (demo_cls(delay)) continue;
        write_monsters(number);
        cout << "\nPress '0' to continue.\n";
        if (demo_cls(delay)) continue;
        write_monsters(number);
        cout << "\nPress '0' to continue. <- press\n";
        if (demo_cls(2 * delay)) continue;
        //find monster by xp and damage
        cout << "Menu:\n1)Add a new monster.\n2)Find an existing monster.\n3)Edit a monster.\n4)Delete a monster.\n0)Back.\n";
        if (demo_cls(delay)) continue;
        cout << "Menu:\n1)Add a new monster.\n2)Find an existing monster. <- press\n3)Edit a monster.\n4)Delete a monster.\n0)Back.\n";
        if (demo_cls(delay)) continue;
        cout << "Select Monster Search Mode:\n1)Search by Name.\n2)Search by xp and damage.\n"
            << "3)Search by type of special monster attack and date.\n4)Show all the monsters.\n";
        if (demo_cls(delay)) continue;
        cout << "Select Monster Search Mode:\n1)Search by Name.\n2)Search by xp and damage. <- press\n"
            << "3)Search by type of special monster attack and date.\n4)Show all the monsters.\n";
        if (demo_cls(delay)) continue;
        cout << "Enter minimum health level of monster(1-50000): \n";
        if (demo_cls(delay)) continue;
        cout << "Enter minimum health level of monster(1-50000): <- write a min xp and press <Enter>\n";
        if (demo_cls(delay)) continue;
        cout << "Enter minimum health level of monster(1-50000): " << demo_xp << endl;
        cout << "Enter the maximum attack level of monster(1-1000): \n";
        if (demo_cls(delay)) continue;
        cout << "Enter minimum health level of monster(1-50000): " << demo_xp << endl;
        cout << "Enter the maximum attack level of monster(1-1000): <- write a max damage and press <Enter>\n";
        if (demo_cls(delay)) continue;
        cout << "Enter minimum health level of monster(1-50000): " << demo_xp << endl;
        cout << "Enter the maximum attack level of monster(1-1000): " << demo_damage << endl;
        if (demo_cls(delay)) continue;
        write_monsters(number);
        cout << "\nPress '0' to continue.\n";
        if (demo_cls(delay)) continue;
        write_monsters(number);
        cout << "\nPress '0' to continue. <- press\n";
        if (demo_cls(2 * delay)) continue;
        //find monster by type of special monster attack
        cout << "Menu:\n1)Add a new monster.\n2)Find an existing monster.\n3)Edit a monster.\n4)Delete a monster.\n0)Back.\n";
        if (demo_cls(delay)) continue;
        cout << "Menu:\n1)Add a new monster.\n2)Find an existing monster. <- press\n3)Edit a monster.\n4)Delete a monster.\n0)Back.\n";
        if (demo_cls(delay)) continue;
        cout << "Select Monster Search Mode:\n1)Search by Name.\n2)Search by xp and damage.\n"
            << "3)Search by type of special monster attack and date.\n4)Show all the monsters.\n";
        if (demo_cls(delay)) continue;
        cout << "Select Monster Search Mode:\n1)Search by Name.\n2)Search by xp and damage.\n"
            << "3)Search by type of special monster attack and date. <- press\n4)Show all the monsters.\n";
        if (demo_cls(delay)) continue;
        cout << "Enter one of the possible types of special monster attack:\n1)Increase damage.\n2)Repeat the attack.\n"
            << "3)Cure yourself.\n4)Paralyze the enemy.\n";
        if (demo_cls(delay)) continue;
        cout << "Enter one of the possible types of special monster attack:\n1)Increase damage. <- press\n2)Repeat the attack.\n"
            << "3)Cure yourself.\n4)Paralyze the enemy.\n";
        if (demo_cls(delay)) continue;
        cout << "Enter one of the possible types of special monster attack:\n1)Increase damage.\n2)Repeat the attack.\n"
            << "3)Cure yourself.\n4)Paralyze the enemy.\n";
        cout << "Enter the maximum date and time the monster was created.\n";
        cout << "Enter year(1970-....): \n";
        if (demo_cls(delay)) continue;
        cout << "Enter one of the possible types of special monster attack:\n1)Increase damage.\n2)Repeat the attack.\n"
            << "3)Cure yourself.\n4)Paralyze the enemy.\n";
        cout << "Enter the maximum date and time the monster was created.\n";
        cout << "Enter year(1970-....): <- write max year and press <Enter>\n";
        if (demo_cls(delay)) continue;
        cout << "Enter one of the possible types of special monster attack:\n1)Increase damage.\n2)Repeat the attack.\n"
            << "3)Cure yourself.\n4)Paralyze the enemy.\n";
        cout << "Enter the maximum date and time the monster was created.\n";
        cout << "Enter year(1970-....): 2030\n";
        cout << "Enter month(1-12): \n";
        if (demo_cls(delay)) continue;
        cout << "Enter one of the possible types of special monster attack:\n1)Increase damage.\n2)Repeat the attack.\n"
            << "3)Cure yourself.\n4)Paralyze the enemy.\n";
        cout << "Enter the maximum date and time the monster was created.\n";
        cout << "Enter year(1970-....): 2030\n";
        cout << "Enter month(1-12): <- write max month and press <Enter>\n";
        if (demo_cls(delay)) continue;
        cout << "Enter one of the possible types of special monster attack:\n1)Increase damage.\n2)Repeat the attack.\n"
            << "3)Cure yourself.\n4)Paralyze the enemy.\n";
        cout << "Enter the maximum date and time the monster was created.\n";
        cout << "Enter year(1970-....): 2030\n";
        cout << "Enter month(1-12): 12\n";
        cout << "Enter day(1-31): \n";
        if (demo_cls(delay)) continue;
        cout << "Enter one of the possible types of special monster attack:\n1)Increase damage.\n2)Repeat the attack.\n"
            << "3)Cure yourself.\n4)Paralyze the enemy.\n";
        cout << "Enter the maximum date and time the monster was created.\n";
        cout << "Enter year(1970-....): 2030\n";
        cout << "Enter month(1-12): 12\n";
        cout << "Enter day(1-31): <- write max day and press <Enter>\n";
        if (demo_cls(delay)) continue;
        cout << "Enter one of the possible types of special monster attack:\n1)Increase damage.\n2)Repeat the attack.\n"
            << "3)Cure yourself.\n4)Paralyze the enemy.\n";
        cout << "Enter the maximum date and time the monster was created.\n";
        cout << "Enter year(1970-....): 2030\n";
        cout << "Enter month(1-12): 12\n";
        cout << "Enter day(1-31): 31\n";
        cout << "Enter hour(0-23): \n";
        if (demo_cls(delay)) continue;
        cout << "Enter one of the possible types of special monster attack:\n1)Increase damage.\n2)Repeat the attack.\n"
            << "3)Cure yourself.\n4)Paralyze the enemy.\n";
        cout << "Enter the maximum date and time the monster was created.\n";
        cout << "Enter year(1970-....): 2030\n";
        cout << "Enter month(1-12): 12\n";
        cout << "Enter day(1-31): 31\n";
        cout << "Enter hour(0-23): <- write max hour and press <Enter>\n";
        if (demo_cls(delay)) continue;
        cout << "Enter one of the possible types of special monster attack:\n1)Increase damage.\n2)Repeat the attack.\n"
            << "3)Cure yourself.\n4)Paralyze the enemy.\n";
        cout << "Enter the maximum date and time the monster was created.\n";
        cout << "Enter year(1970-....): 2030\n";
        cout << "Enter month(1-12): 12\n";
        cout << "Enter day(1-31): 31\n";
        cout << "Enter hour(0-23): 23\n";
        cout << "Enter minute(0-59): \n";
        if (demo_cls(delay)) continue;
        cout << "Enter one of the possible types of special monster attack:\n1)Increase damage.\n2)Repeat the attack.\n"
            << "3)Cure yourself.\n4)Paralyze the enemy.\n";
        cout << "Enter the maximum date and time the monster was created.\n";
        cout << "Enter year(1970-....): 2030\n";
        cout << "Enter month(1-12): 12\n";
        cout << "Enter day(1-31): 31\n";
        cout << "Enter hour(0-23): 23\n";
        cout << "Enter minute(0-59): <- write max min and press <Enter>\n";
        if (demo_cls(delay)) continue;
        cout << "Enter one of the possible types of special monster attack:\n1)Increase damage.\n2)Repeat the attack.\n"
            << "3)Cure yourself.\n4)Paralyze the enemy.\n";
        cout << "Enter the maximum date and time the monster was created.\n";
        cout << "Enter year(1970-....): 2030\n";
        cout << "Enter month(1-12): 12\n";
        cout << "Enter day(1-31): 31\n";
        cout << "Enter hour(0-23): 23\n";
        cout << "Enter minute(0-59): 59\n";
        cout << "Enter second(0-59): \n";
        if (demo_cls(delay)) continue;
        cout << "Enter one of the possible types of special monster attack:\n1)Increase damage.\n2)Repeat the attack.\n"
            << "3)Cure yourself.\n4)Paralyze the enemy.\n";
        cout << "Enter the maximum date and time the monster was created.\n";
        cout << "Enter year(1970-....): 2030\n";
        cout << "Enter month(1-12): 12\n";
        cout << "Enter day(1-31): 31\n";
        cout << "Enter hour(0-23): 23\n";
        cout << "Enter minute(0-59): 59\n";
        cout << "Enter second(0-59): <- write max sec and press <Enter>\n";
        if (demo_cls(delay)) continue;
        cout << "Enter one of the possible types of special monster attack:\n1)Increase damage.\n2)Repeat the attack.\n"
            << "3)Cure yourself.\n4)Paralyze the enemy.\n";
        cout << "Enter the maximum date and time the monster was created.\n";
        cout << "Enter year(1970-....): 2030\n";
        cout << "Enter month(1-12): 12\n";
        cout << "Enter day(1-31): 31\n";
        cout << "Enter hour(0-23): 23\n";
        cout << "Enter minute(0-59): 59\n";
        cout << "Enter second(0-59): 59\n";
        if (demo_cls(delay)) continue;
        write_monsters(number);
        cout << "\nPress '0' to continue.\n";
        if (demo_cls(delay)) continue;
        write_monsters(number);
        cout << "\nPress '0' to continue. <- press\n";
        if (demo_cls(2 * delay)) continue;
        //Show all the monsters
        cout << "Menu:\n1)Add a new monster.\n2)Find an existing monster.\n3)Edit a monster.\n4)Delete a monster.\n0)Back.\n";
        if (demo_cls(delay)) continue;
        cout << "Menu:\n1)Add a new monster.\n2)Find an existing monster. <- press\n3)Edit a monster.\n4)Delete a monster.\n0)Back.\n";
        if (demo_cls(delay)) continue;
        cout << "Select Monster Search Mode:\n1)Search by Name.\n2)Search by xp and damage.\n"
            << "3)Search by type of special monster attack and date.\n4)Show all the monsters.\n";
        if (demo_cls(delay)) continue;
        cout << "Select Monster Search Mode:\n1)Search by Name.\n2)Search by xp and damage.\n"
            << "3)Search by type of special monster attack and date.\n4)Show all the monsters. <- press\n";
        if (demo_cls(delay)) continue;
        write_monsters(number);
        cout << "\nPress '0' to continue.\n";
        if (demo_cls(delay)) continue;
        write_monsters(number);
        cout << "\nPress '0' to continue. <- press\n";
        if (demo_cls(2 * delay)) continue;
        //edit monster
        cout << "Menu:\n1)Add a new monster.\n2)Find an existing monster.\n3)Edit a monster.\n4)Delete a monster.\n0)Back.\n";
        if (demo_cls(delay)) continue;
        cout << "Menu:\n1)Add a new monster.\n2)Find an existing monster.\n3)Edit a monster. <- press\n4)Delete a monster.\n0)Back.\n";
        if (demo_cls(delay)) continue;
        cout << "Enter id of monster: ";
        if (demo_cls(delay)) continue;
        cout << "Enter id of monster: <- write the id and press <Enter>";
        if (demo_cls(delay)) continue;
        cout << "Enter id of monster: " << id;
        if (demo_cls(delay)) continue;
        write_monster(0);
        cout << "\nSelect the option you want to edit:\n";
        cout << "1)Name.\n2)XP.\n3)Damage.\n4)Chance to launch a special attack.\n5)Type of special monster attack.\n0)Exit." << endl;
        if (demo_cls(delay)) continue;
        write_monster(0);
        cout << "\nSelect the option you want to edit:\n";
        cout << "1)Name <- press.\n2)XP.\n3)Damage.\n4)Chance to launch a special attack.\n5)Type of special monster attack.\n0)Exit." << endl;
        if (demo_cls(delay)) continue;
        write_monster(0);
        cout << "\nEnter a new Name of monster: ";
        if (demo_cls(delay)) continue;
        write_monster(0);
        cout << "\nEnter a new Name of monster: <- write a new Name and press <Enter>";
        if (demo_cls(delay)) continue;
        write_monster(0);
        cout << "\nEnter a new Name of monster: Name2";
        all_monsters[0].name = "Name2";
        if (demo_cls(delay)) continue;
        write_monster(0);
        cout << "\nSelect the option you want to edit:\n";
        cout << "1)Name.\n2)XP. <- press\n3)Damage.\n4)Chance to launch a special attack.\n5)Type of special monster attack.\n0)Exit." << endl;
        if (demo_cls(delay)) continue;
        write_monster(0);
        cout << "\nEnter a new XP of monster: ";
        if (demo_cls(delay)) continue;
        write_monster(0);
        cout << "\nEnter a new XP of monster: <- write a new XP and press <Enter>";
        if (demo_cls(delay)) continue;
        write_monster(0);
        cout << "\nEnter a new XP of monster: 20000";
        all_monsters[0].hp = 20000;
        if (demo_cls(delay)) continue;
        write_monster(0);
        cout << "\nSelect the option you want to edit:\n";
        cout << "1)Name.\n2)XP.\n3)Damage. <- press\n4)Chance to launch a special attack.\n5)Type of special monster attack.\n0)Exit." << endl;
        if (demo_cls(delay)) continue;
        write_monster(0);
        cout << "\nEnter a new Damage of monster: ";
        if (demo_cls(delay)) continue;
        write_monster(0);
        cout << "\nEnter a new Damage of monster: <- write a new Damage and press <Enter>";
        if (demo_cls(delay)) continue;
        write_monster(0);
        cout << "\nEnter a new Damage of monster: 100";
        all_monsters[0].damage = 100;
        if (demo_cls(delay)) continue;
        write_monster(0);
        cout << "\nSelect the option you want to edit:\n";
        cout << "1)Name.\n2)XP.\n3)Damage.\n4)Chance to launch a special attack. <- press\n5)Type of special monster attack.\n0)Exit." << endl;
        if (demo_cls(delay)) continue;
        write_monster(0);
        cout << "\nEnter a new Chance of monster: ";
        if (demo_cls(delay)) continue;
        write_monster(0);
        cout << "\nEnter a new Chance of monster: <- write a new Chence and press <Enter>";
        if (demo_cls(delay)) continue;
        write_monster(0);
        cout << "\nEnter a new Chance of monster: 0.11";
        all_monsters[0].chance = 0.11;
        if (demo_cls(delay)) continue;
        write_monster(0);
        cout << "\nSelect the option you want to edit:\n";
        cout << "1)Name.\n2)XP.\n3)Damage.\n4)Chance to launch a special attack.\n5)Type of special monster attack. <- press\n0)Exit." << endl;
        if (demo_cls(delay)) continue;
        write_monster(0);
        cout << "Enter one of the possible types of special monster attack:\n1)Increase damage.\n2)Repeat the attack.\n"
            << "3)Cure yourself.\n4)Paralyze the enemy.\n";
        if (demo_cls(delay)) continue;
        write_monster(0);
        cout << "Enter one of the possible types of special monster attack:\n1)Increase damage.\n2)Repeat the attack. <- press\n"
            << "3)Cure yourself.\n4)Paralyze the enemy.\n";
        all_monsters[0].type_of_attack = "Repeat the attack";
        if (demo_cls(delay)) continue;
        write_monster(0);
        cout << "\nSelect the option you want to edit:\n";
        cout << "1)Name.\n2)XP.\n3)Damage.\n4)Chance to launch a special attack.\n5)Type of special monster attack.\n0)Exit." << endl;
        if (demo_cls(delay)) continue;
        write_monster(0);
        cout << "\nSelect the option you want to edit:\n";
        cout << "1)Name.\n2)XP.\n3)Damage.\n4)Chance to launch a special attack.\n5)Type of special monster attack.\n0)Exit. <- press" << endl;
        if (demo_cls(2 * delay)) continue;
        //delete monster
        cout << "Menu:\n1)Add a new monster.\n2)Find an existing monster.\n3)Edit a monster.\n4)Delete a monster.\n0)Back.\n";
        if (demo_cls(delay)) continue;
        cout << "Menu:\n1)Add a new monster.\n2)Find an existing monster.\n3)Edit a monster.\n4)Delete a monster. <- press\n0)Back.\n";
        if (demo_cls(delay)) continue;
        cout << "Enter id of monster: ";
        if (demo_cls(delay)) continue;
        cout << "Enter id of monster: <- write the id and press <Enter>";
        if (demo_cls(delay)) continue;
        cout << "Enter id of monster: " << id;
        all_monsters.erase(all_monsters.begin());
        if (demo_cls(delay)) continue;
        cout << "The monster - removed!\n";
        cout << "\nPress '0' to continue.\n";
        if (demo_cls(delay)) continue;
        cout << "The monster - removed!\n";
        cout << "\nPress '0' to continue. <- press\n";
        if (demo_cls(delay)) continue;
        //exit
        cout << "Menu:\n1)Add a new monster.\n2)Find an existing monster.\n3)Edit a monster.\n4)Delete a monster.\n0)Back.\n";
        if (demo_cls(delay)) continue;
        cout << "Menu:\n1)Add a new monster.\n2)Find an existing monster.\n3)Edit a monster.\n4)Delete a monster.\n0)Back. <- press\n";
        if (demo_cls(delay)) continue;
        cout << "Select the application mode:\n1)Interactive dialog mode.\n2)Demo mode.\n3)Automatic benchmark mode.\n0)Exit.\n";
        if (demo_cls(delay)) continue;
        cout << "Select the application mode:\n1)Interactive dialog mode.\n2)Demo mode.\n3)Automatic benchmark mode.\n0)Exit. <- press\n";
    }
    //my_cls();
    cout << "Demo mode is over!" << endl;
    Sleep(1500);
}
*/
/*info_monster monster_generator()//створює монстра з рандомними параметрами
{
    srand(time(0));
    int id = set_id();
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

    return info_monster(name, xp, damage, chance, type, my_time(rand() % 24, rand() % 60, rand() % 60, rand() % 28 + 1, rand() % 12 + 1, rand() % 10 + 2020), id);
}
int size_file(string path)//визначає розмір файла у байтах
{
    std::ifstream file(path);
    file.seekg(0, std::ios::end);
    int sizef = file.tellg();
    file.seekg(0, std::ios::beg);
    file.close();
    return sizef;
}
void add_program_test(string path, result date)
{
    bool is_file = create_text_file(path);
    if (is_file)
    {
        std::ofstream file(path, std::ios_base::app);
        file << "N: " << date.number_n << endl;
        file << "Time: " << date.time << endl;
        if (date.size != -1) file << "Size file:" << date.size << endl << endl;
        file.close();
    }
}
void benchmark_mode()// режим benchmark
{
    //my_cls();
    int n;
    result name_find, xp_damage_find, time_type_find, open_bin, open_txt, save_bin, save_txt;
    name_find.size = -1;
    xp_damage_find.size = -1;
    time_type_find.size = -1;
    open_bin.size = -1;
    open_txt.size = -1;
    std::remove("result_save_txt_file.txt");
    std::remove("result_open_txt_file.txt");
    std::remove("result_save_binary_file.txt");
    std::remove("result_open_binary_file.txt");
    std::remove("result_name_find.txt");
    std::remove("result_xp_damage_find.txt");
    std::remove("result_time_type_find.txt");
    cout << "Enter N(1-...): ";
    cin >> n;
    auto the_start = std::chrono::high_resolution_clock::now();
    auto the_end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> duration;
    for (int i = 0; i < n; i++) all_monsters.push_back(monster_generator());
    while (true)
    {
        int k = all_monsters.size();
        cout << "\n\n        <N = " << k << ">\n";
        the_start = std::chrono::high_resolution_clock::now();
        save_text_file("benchmark_text.txt");
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
        vector <int> number;
        info_monster find_monster = monster_generator();
        the_start = std::chrono::high_resolution_clock::now();
        number = find_name(find_monster.name);
        the_end = std::chrono::high_resolution_clock::now();
        duration = the_end - the_start;
        name_find.number_n = k;
        name_find.time = duration.count();
        add_program_test("result_name_find.txt", name_find);
        cout << "Time of find by name = " << name_find.time << endl;
        //
        the_start = std::chrono::high_resolution_clock::now();
        number = find_xp_damage(find_monster.hp, find_monster.damage);
        the_end = std::chrono::high_resolution_clock::now();
        duration = the_end - the_start;
        xp_damage_find.number_n = k;
        xp_damage_find.time = duration.count();
        add_program_test("result_xp_damage_find.txt", xp_damage_find);
        cout << "Time of find by xp and damage = " << xp_damage_find.time << endl;
        //
        the_start = std::chrono::high_resolution_clock::now();
        number = find_types_time(find_monster.type_of_attack, find_monster.time_info);
        the_end = std::chrono::high_resolution_clock::now();
        duration = the_end - the_start;
        time_type_find.number_n = k;
        time_type_find.time = duration.count();
        add_program_test("result_time_type_find.txt", time_type_find);
        cout << "Time of find by types of attack and time = " << time_type_find.time << endl;
        //
        the_start = std::chrono::high_resolution_clock::now();
        open_text_file("benchmark_text.txt");
        the_end = std::chrono::high_resolution_clock::now();
        duration = the_end - the_start;
        open_txt.number_n = k;
        open_txt.time = duration.count();
        add_program_test("result_open_txt_file.txt", open_txt);
        cout << "Time of open txt = " << open_txt.time << endl;
    }
    all_monsters.clear();
    for (int i = 0; i < n; i++) all_monsters.push_back(monster_generator());
    while (true)
    {
        int m = all_monsters.size();
        cout << "\n\n        <N = " << m << ">\n";
        the_start = std::chrono::high_resolution_clock::now();
        save_binary_file("benchmark_binary.bin");
        the_end = std::chrono::high_resolution_clock::now();
        duration = the_end - the_start;
        save_bin.number_n = m;
        save_bin.time = duration.count();
        save_bin.size = size_file("benchmark_binary.bin");
        add_program_test("result_save_binary_file.txt", save_bin);
        cout << "Time save binary = " << save_bin.time << endl;
        cout << "Size save binary = " << save_bin.size << endl;
        if (save_bin.time >= 10) break;
        the_start = std::chrono::high_resolution_clock::now();
        open_binary_file("benchmark_binary.bin");
        the_end = std::chrono::high_resolution_clock::now();
        duration = the_end - the_start;
        open_bin.number_n = m;
        open_bin.time = duration.count();
        add_program_test("result_open_binary_file.txt", open_bin);
        cout << "Time open binary = " << open_bin.time << endl;
    }
    all_monsters.clear();
    cout << "\nResults of measurements of program in the following files:"
        << "\nresult_save_txt_file.txt\nresult_open_txt_file.txt\nresult_save_binary_file.txt\nresult_open_binary_file.txt"
        << "\nresult_name_find.txt\nresult_xp_damage_find.txt\nresult_time_type_find.txt" << endl;
    std::remove("benchmark_text.txt");
    std::remove("benchmark_binary.bin");
}*/
int main()
{  
    cout << "<The Forest of Monsters>" << endl;
    while (true)
    {
        cout << "\nSelect the application mode:\n1)Interactive dialog mode.\n2)Demo mode.\n3)Automatic benchmark mode.\n0)Exit.\n";
        switch (_getch())
        {
        case '1': interactive_dialog_mode();
            break;
        case '2': //demo_mode();
            break;
        case '3': //benchmark_mode();
            break;
        case'0': 
            {
                cout << "\nExit...";
                return 0;
            }
            break;
        default: cout << "\nPress the correct key!" << endl;
        }
    }
    return 0;
}