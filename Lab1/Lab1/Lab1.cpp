﻿#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <ctime>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <algorithm>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;

enum class types_of_attack: int
{
    INCREASE = 1,
    REPEAT,
    CURE,
    PARALYZE
};
struct info_monster;
struct measurement_result;
bool create_text_file(const string&);
vector <info_monster> open_text_file(const string&);
bool save_text_file(const string&, const vector<info_monster>&);
bool add_in_text_file(info_monster, const string&);
bool create_binary_file(const string&);
vector <info_monster> open_binary_file(const string&);
bool save_binary_file(const string&, const vector<info_monster>&);
bool add_in_binary_file(info_monster, const string&);
string read_name(const string&);
unsigned read_hp(const string&);
unsigned read_damage(const string&);
double line_is_number(string);
double read_chance(const string&);
types_of_attack read_type();
void line_read(std::ifstream&, string&);
void write_time(struct std::tm);
void add_new_monster(vector<info_monster>&);
unsigned set_id(const vector<info_monster>&);
int find_id(unsigned, const vector<info_monster>&);
void edit_monster(vector<info_monster>&);
void delete_monster(vector<info_monster>&);
void write_monsters_menu(vector<int>, const vector<info_monster>&);
void write_all_monsters(const vector<info_monster>&);
void find_types_time_menu(const vector<info_monster>&);
bool is_time(const int*, const int*, int);
vector <int> find_types_time(types_of_attack, const int*, const vector<info_monster>&);
void find_hp_damage_menu(const vector<info_monster>&);
vector <int> find_hp_damage(unsigned, unsigned, const vector<info_monster>&);
void find_name_menu(const vector<info_monster>&);
vector <int> find_name(string, const vector<info_monster>&);
void monster_search(const vector<info_monster>&);
void interactive_dialog_mode();
void demo_menu(int&);
void demo_read_name(int&, const string&, const string&);
void demo_read_hp(int&, const string&, const unsigned&);
void demo_read_damage(int&, const string&, const unsigned&);
void demo_read_chance(int&, const string&, const double&);
void demo_read_type(int&, const short&);
void demo_add_monster(int&, vector <info_monster>&);
void demo_show_all_monsters(int&, const vector <info_monster>&);
void demo_find_monsters(int&);
void demo_find_name(int&, const vector<info_monster>&);
void demo_find_hp_damage(int&, const vector<info_monster>&);
void demo_find_types_time(int&, const vector<info_monster>&);
void demo_read_id(int&, const vector<info_monster>&);
void demo_edit_monsters_menu(int&, vector<info_monster>&);
void demo_edit_monster(int&, vector<info_monster>&);
void demo_delete_monster(int&, vector<info_monster>&);
void demo_exit(int&);
void demo_mode();
void monster_generator(vector<info_monster>&);
std::size_t size_file(const string&);
void add_program_test(const string&, const measurement_result&, bool);
float measurement_open_txt(vector<info_monster>&);
float measurement_open_bin(vector<info_monster>&);
float measurement_save_txt(vector<info_monster>&);
float measurement_save_bin(vector<info_monster>&);
float measurement_name_find(vector<info_monster>&);
float measurement_hp_damage_find(vector<info_monster>&);
float measurement_time_type_find(vector<info_monster>&);
void clear_result_files();
void benchmark_mode();
void file_replacement(const string&, const string&);
vector<info_monster> opening_mode(const string&, const string&);
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
    info_monster(string name, unsigned hp, unsigned damage, double chance, types_of_attack type_of_attack,const vector<info_monster>& all_monsters)
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
        this->id = set_id(all_monsters);
    }
};
struct measurement_result
{
    int number_of_monsters;
    float time;
    std::size_t size;
};
namespace impl
{
    void write_monster(int number, const vector<info_monster>& all_monsters)
    {
        cout << "ID: " << all_monsters[number].id << ".\n";
        cout << "Name: " << all_monsters[number].name << ".\n";
        cout << "HP: " << all_monsters[number].hp << ".\n";
        cout << "Damage: " << all_monsters[number].damage << ".\n";
        cout << "Chance to launch a special attack: " << all_monsters[number].chance << "." << endl;
        cout << "Type of special monster attack: ";
        switch (all_monsters[number].type_of_attack)
        {
        case types_of_attack::INCREASE: cout << "Increase damage." << endl;
            break;
        case types_of_attack::REPEAT: cout << "Repeat the attack." << endl;
            break;
        case types_of_attack::CURE: cout << "Cure yourself." << endl;
            break;
        case types_of_attack::PARALYZE: cout << "Paralyze the enemy." << endl;
        }
        write_time(all_monsters[number].time_info);
    }
    void add_monster_in_files(std::ifstream& file, unsigned id, const string& txt, const string& bin)//The function adds monsters with another id to the end of the files
    {
        string line;
        string name;
        types_of_attack type_of_attack = types_of_attack::INCREASE;
        unsigned hp, damage, type;
        double chance;
        struct std::tm time_info;
        line_read(file, line);
        name = line.substr(5);
        line_read(file, line);
        hp = stoi(line.substr(3));
        line_read(file, line);
        damage = stoi(line.substr(7));
        line_read(file, line);
        chance = stod(line.substr(7));
        line_read(file, line);
        type = stoi(line.substr(5));
        switch (type)
        {
        case 1: type_of_attack = types_of_attack::INCREASE;
            break;
        case 2: type_of_attack = types_of_attack::REPEAT;
            break;
        case 3: type_of_attack = types_of_attack::CURE;
            break;
        case 4: type_of_attack = types_of_attack::PARALYZE;
        }
        file >> time_info.tm_hour >> time_info.tm_min >> time_info.tm_sec
            >> time_info.tm_mday >> time_info.tm_mon >> time_info.tm_year;
        add_in_text_file(info_monster(name, hp, damage, chance, type_of_attack, time_info, id), txt);
        add_in_binary_file(info_monster(name, hp, damage, chance, type_of_attack, time_info, id), bin);
    }
    void save_edit_monster(const string& txt, const string& bin, info_monster monster)//the function saves the files of the editable monster
    {
        std::ifstream old_file(txt);
        bool monster_found = false;
        while (!old_file.eof())
        {
            string line;
            line_read(old_file, line);
            if (line.size() == 0) break;
            if (line.substr(0, 2) == "id")
            {
                unsigned id = stoi(line.substr(3));
                if ((!monster_found) && (id == monster.id))
                {
                    monster_found = true;
                    add_in_text_file(monster, "new_" + txt);
                    add_in_binary_file(monster, "new_" + bin);
                }
                else
                {
                    add_monster_in_files(old_file, id, "new_" + txt, "new_" + bin);
                }
            }
        }
        old_file.close();
        file_replacement(txt, "new_" + txt);
        file_replacement(bin, "new_" + bin);
    }
    void delete_monster_from_files(unsigned monster_id, const string& txt, const string& bin)//function removes monster from files
    {
        std::ifstream old_file(txt);
        std::ofstream txt_file("new_" + txt);
        txt_file.close();
        std::ofstream bin_file("new_" + bin, std::ios_base::binary);
        bin_file.close();
        bool monster_found = false, the_end = false;
        while (!old_file.eof())
        {
            string line;
            line_read(old_file, line);
            if (line.size() == 0) break;
            if (line.substr(0, 2) == "id")
            {
                unsigned id = stoi(line.substr(3));
                if ((!monster_found) && (id == monster_id))
                {
                    monster_found = true;
                    while (true)
                    {
                        line_read(old_file, line);
                        if (line.size() == 0)
                        {
                            the_end = true;
                            break;
                        }
                        if (line.substr(0, 2) == "id")
                        {
                            id = stoi(line.substr(3));
                            break;
                        }
                    }
                    if (the_end) break;
                }
                add_monster_in_files(old_file, id, "new_" + txt, "new_" + bin);
            }
        }
        old_file.close();
        file_replacement(txt, "new_" + txt);
        file_replacement(bin, "new_" + bin);
    }
}

bool create_text_file(const string& path)//the function creates a text file if it does not exist
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
vector <info_monster> open_text_file(const string& path)//the function copies information from a text file to an array
{
    vector <info_monster> all_monsters;
    if (!create_text_file(path))
    {
        cout << "\nFile not found!..." <<endl;
        cout << "\nNew file created!" << endl;
    }
    else
    {
        std::ifstream file(path);
        while (!file.eof())
        {
            string line;           
            line_read(file, line);
            if (line.size() == 0) break;
            unsigned id;
            id = stoi(line.substr(3));
            string name;
            types_of_attack type_of_attack = types_of_attack::INCREASE;
            unsigned hp, damage, type;
            double chance;
            struct std::tm time_info;
            line_read(file, line);
            name = line.substr(5);
            line_read(file, line);
            hp = stoi(line.substr(3));
            line_read(file, line);
            damage = stoi(line.substr(7));
            line_read(file, line);
            chance = stod(line.substr(7));
            line_read(file, line);
            type = stoi(line.substr(5));
            switch (type)
            {
                case 1: type_of_attack = types_of_attack::INCREASE;
                break;
                case 2: type_of_attack = types_of_attack::REPEAT;
                break;
                case 3: type_of_attack = types_of_attack::CURE;
                break;
                case 4: type_of_attack = types_of_attack::PARALYZE;
            }
            file >> time_info.tm_hour >> time_info.tm_min >> time_info.tm_sec 
                 >> time_info.tm_mday >> time_info.tm_mon >> time_info.tm_year;
            all_monsters.push_back(info_monster(name, hp, damage, chance, type_of_attack, time_info, id));
        }
        file.close();
    }
    return all_monsters;
}
bool save_text_file(const string& path,const vector<info_monster>& all_monsters)//The function copies information from an array into a text file
{
    std::ofstream file(path);
    if (!file.is_open()) return false;
    for (unsigned i = 0; i < all_monsters.size(); i++)
    {
        file << "id:" << all_monsters[i].id << endl;
        file << "name:" << all_monsters[i].name << endl;
        file << "hp:" << all_monsters[i].hp << endl;
        file << "damage:" << all_monsters[i].damage << endl;
        file << "chance:" << all_monsters[i].chance << endl;
        switch (all_monsters[i].type_of_attack)
        {
        case types_of_attack::INCREASE: file <<"type:" << 1 << endl;
            break;
        case types_of_attack::REPEAT: file << "type:" << 2 << endl;
            break;
        case types_of_attack::CURE: file << "type:" << 3 << endl;
            break;
        case types_of_attack::PARALYZE: file << "type:" << 4 << endl;
        }
        file << all_monsters[i].time_info.tm_hour << " " 
             << all_monsters[i].time_info.tm_min << " " << all_monsters[i].time_info.tm_sec << " "
             << all_monsters[i].time_info.tm_mday << " " << all_monsters[i].time_info.tm_mon << " " 
             << all_monsters[i].time_info.tm_year << endl;
    }
    file.close();
    return true;
}
bool add_in_text_file(info_monster monster, const string& path)//the function writes information to the end of a text file
{
    std::ofstream file(path, std::ios_base::app);
    if (!file.is_open()) return false;
    file << "id:" << monster.id << endl;
    file << "name:" << monster.name << endl;
    file << "hp:" << monster.hp << endl;
    file << "damage:" << monster.damage << endl;
    file << "chance:" << monster.chance << endl;
    switch (monster.type_of_attack)
    {
    case types_of_attack::INCREASE: file << "type:" << 1 << endl;
        break;
    case types_of_attack::REPEAT: file << "type:" << 2 << endl;
        break;
    case types_of_attack::CURE: file << "type:" << 3 << endl;
        break;
    case types_of_attack::PARALYZE: file << "type:" << 4 << endl;
    }
    file << monster.time_info.tm_hour << " " << monster.time_info.tm_min << " " 
        << monster.time_info.tm_sec << " " << monster.time_info.tm_mday << " " 
        << monster.time_info.tm_mon << " " << monster.time_info.tm_year << endl;
    file.close();
    return true;
}
bool create_binary_file(const string& path)//the function creates a binary file if it does not exist
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
vector <info_monster> open_binary_file(const string& path)//the function copies information from a binary file to an array
{
    vector <info_monster> all_monsters;
    if (!create_binary_file(path))
    {
        cout << "\nFile not found!..." << endl;
        cout << "\nNew file created!" << endl;
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
            file.read((char*)&(monster.time_info), sizeof(monster.time_info));
            all_monsters.push_back(monster);
            delete[] buffer_name;
        }
        file.close();
    }
    return all_monsters;
}
bool save_binary_file(const string& path, const vector<info_monster>& all_monsters)//The function copies information from an array into a binary file
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
        file.write((char*)&(all_monsters[i].time_info), sizeof(all_monsters[i].time_info));       
    }
    file.close();
    return true;
}
bool add_in_binary_file(info_monster monster, const string& path)//the function writes information to the end of a binary file
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
    file.write((char*)&(monster.time_info), sizeof(monster.time_info));
    file.close();
    return true;
}
string read_name(const string& sentence)
{
    string name;
    cout << "\nEnter " << sentence << " name of monster: ";
    getline(cin, name);
    while (name.size() == 0) getline(cin, name);
    return name;
}
unsigned read_hp(const string& sentence)
{
    while (true)
    {
        cout << "\nEnter " << sentence 
             << " number of monster health units (1-50000): ";
        unsigned hp;
        cin >> hp;
        if ((hp < 1)||(hp > 50000)||(!cin.good()))
        {
            cin.clear();
            cin.ignore(200, '\n');
            cout << "\nData entered incorrectly!" << endl;
        }
        else return hp;
    }
}
unsigned read_damage(const string& sentence)
{
    while (true)
    {
        cout << "\nEnter " << sentence
            << " number of monster attack units (1-1000): ";
        unsigned damage;
        cin >> damage;
        if ((damage < 1) || (damage > 1000)||(!cin.good()))
        {
            cin.clear();
            cin.ignore(200, '\n');
            cout << "\nData entered incorrectly!" << endl;
        }
        else return damage;
    }
}
double line_is_number(string line)//checks that the fractional number is entered correctly
{
    char* p;
    double number;
    if (line.size() > 1) if (line[1] == ',') line.replace(1, 1, ".");
    number = strtod(line.c_str(), &p);          
    if (*p == 0) return number;
    return -1;
}
double read_chance(const string& sentence)
{
    while (true)
    {
        cout << "\nEnter " << sentence
            << " chance to launch a special attack of monster (0.00 - 1.00): ";
        string chance_string;
        getline(cin, chance_string);
        while (chance_string.size() == 0) getline(cin, chance_string);
        double chance = line_is_number(chance_string);        
        if ((chance >= 0) && (chance <= 1)) return chance;
        cout << "\nData entered incorrectly!" << endl;             
    }
    return -1;
}
types_of_attack read_type()
{
    while (true)
    {
        cout << "\nChoose one of the possible types of special monster attack:\n1)Increase damage.\n"
             << "2)Repeat the attack.\n3)Cure yourself.\n4)Paralyze the enemy." << endl;
        switch (_getch())
        {
        case '1': return types_of_attack::INCREASE;
        case '2': return types_of_attack::REPEAT;
        case '3': return types_of_attack::CURE;
        case '4': return types_of_attack::PARALYZE;
        default: cout << "\nPress the correct key!" << endl;
        }
    }
}
void line_read(std::ifstream& file, string& line)
{
    getline(file, line);
    while (line.size() == 0)
    {
        if (file.eof()) break;
        getline(file, line);
    }
}
void write_time(struct std::tm time_info)
{
    char buffer[80];
    strftime(buffer, 80, "Creation time and date: %X  %d.%m.%Y", &time_info);
    cout << buffer << endl;
}
void add_new_monster(vector<info_monster>& all_monsters)//function to create a new monster
{
    cout << "\nCreate your own monster!" << endl;
    string name = read_name("a");
    unsigned hp = read_hp("a");
    unsigned damage = read_damage("a");
    double chance = read_chance("a");
    types_of_attack type_of_attack = read_type();
    info_monster new_monster(name, hp, damage, chance, type_of_attack, all_monsters);
    cout << "\nNew monster created!\nHis personal ID: " << new_monster.id << endl;
    write_time(new_monster.time_info);
    all_monsters.push_back(new_monster);
    if (!add_in_text_file(new_monster, "text.txt") || !add_in_binary_file(new_monster, "binary.bin"))
    {
        cout << "\nError saving file!..." << endl;
    }
}
unsigned set_id(const vector<info_monster>& all_monsters)//creates a unique id
{
    unsigned new_id = 1000;
    int size = all_monsters.size();
    if (size == 0) return new_id;
    else return all_monsters[size - 1].id + 1;
}
int find_id(unsigned monster_id, const vector<info_monster>& all_monsters)
{
    int number_monster = -1;
    for (unsigned i = 0; i < all_monsters.size(); i++)
    {
        if (monster_id == all_monsters[i].id)
        {
            number_monster = i;
            break;
        }
    }
    return number_monster;
}
void file_replacement(const string& first_file, const string& second_file)//deletes the first file and renames the second file to the first
{
    const char* f_file = first_file.c_str();
    const char* s_file = second_file.c_str();
    remove(f_file);
    if (rename(s_file, f_file) != 0)
    {
        cout << "\nError file replacement!" << endl;
    }
}
void edit_monster(vector<info_monster>& all_monsters)
{   
    cout << "\nEnter id of monster: ";
    unsigned monster_id;
    cin >> monster_id;
    int number = find_id(monster_id,all_monsters);
    if (number != -1)
    {      
        while (true)
        {
            cout << "\nMonster:\n" << endl;
            impl::write_monster(number, all_monsters);
            cout << "\nSelect the option you want to edit:\n"
                << "1)Name.\n2)HP.\n3)Damage.\n4)Chance to launch a special attack.\n"
                << "5)Type of special monster attack.\n0)Exit." << endl;
            switch (_getch())
            {
            case '1':
                {
                    all_monsters[number].name = read_name("a new");
                    continue;
                }
                break;
            case '2':
                {
                    all_monsters[number].hp = read_hp("a new");
                    continue;
                }
                break;
            case '3':
                {
                    all_monsters[number].damage = read_damage("a new");
                    continue;
                }
                break;
            case '4':
                {
                    all_monsters[number].chance = read_chance("a new");
                    continue;
                }
                break;
            case '5':
                {             
                    all_monsters[number].type_of_attack = read_type();
                    continue;
                }
                break;
            case '0':
                break;
            default: 
                {
                    cout << "\nPress the correct key!" << endl;
                    continue;
                }
            }
            break;
        }
        impl::save_edit_monster("text.txt", "binary.bin", all_monsters[number]);
    }
    else cout << "\nMonster not found!" << endl;
}
void delete_monster(vector <info_monster>& all_monsters)
{
    cout << "\nEnter id of monster: ";
    unsigned monster_id;
    cin >> monster_id;
    int number = find_id(monster_id,all_monsters);
    if(number == -1) cout << "\nMonster not found!" << endl;
    else
    {      
        all_monsters.erase(all_monsters.begin() + number);
        impl::delete_monster_from_files(monster_id, "text.txt", "binary.bin");
        cout << "\nThe monster - removed!" << endl;
    }
}
void write_monsters_menu(vector<int> numbers, const vector<info_monster>& all_monsters)
{
    if (numbers.size() == 0) cout << "\nMonster(s) don`t found!" << endl;
    else
    {
        cout << "\nMonster(s) found:" << endl;
        int n = 0;
        for (unsigned i = 0; i < numbers.size(); i++)
        {
            cout << "\n<" << ++n << ">" << endl;
            impl::write_monster(numbers[i],all_monsters);
        }
    }
}
void write_all_monsters(const vector<info_monster>& all_monsters)
{
    if (all_monsters.size() == 0)
    {
        cout << "\nNo monsters saved!" << endl;
    }
    else cout << "\nAll monsters:" <<endl;
    for (unsigned i = 0; i < all_monsters.size(); i++)
    {
        cout << "\n<" << i + 1 << ">\n";
        impl::write_monster(i,all_monsters);
    }
}
void find_types_time_menu(const vector<info_monster>& all_monsters)
{   
    types_of_attack one_types_attack = read_type();
    cout << "\nEnter the maximum date and time the monster was created:" << endl;
    int* find_time = new int[6];
    cout << "\nEnter year(2020-....): ";
    cin >> find_time[0];
    cout << "\nEnter month(1-12): ";
    cin >> find_time[1];
    cout << "\nEnter day(1-31): ";
    cin >> find_time[2];
    cout << "\nEnter hour(0-23): ";
    cin >> find_time[3];
    cout << "\nEnter minute(0-59): ";
    cin >> find_time[4];
    cout << "\nEnter second(0-59): ";
    cin >> find_time[5];
    write_monsters_menu(find_types_time(one_types_attack, find_time,all_monsters),all_monsters);
    delete[] find_time;
}
bool is_time(const int* find_time,const int* monster_time, int number = 0)//recursion to check that the monster is created no later than the specified time
{
    if (number == 6) return false;
    if (monster_time[number] > find_time[number]) return false;
    else
    {
        if (number == 5) return true;
        if (monster_time[number] < find_time[number]) return true;
        return is_time(find_time, monster_time, ++number);
    }
}
vector <int> find_types_time(types_of_attack one_types_attack, const int* find_time, const vector<info_monster>& all_monsters)
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
            if (is_time(find_time, monster_time)) numbers_monsters.push_back(i);
            delete[]monster_time;
        }
    }

    return numbers_monsters;
}
void find_hp_damage_menu(const vector<info_monster>& all_monsters)
{
    unsigned min_hp = read_hp("the minimum");
    unsigned max_damage = read_damage("the maximum");
    write_monsters_menu(find_hp_damage(min_hp, max_damage,all_monsters),all_monsters);
}
vector <int> find_hp_damage(unsigned min_hp, unsigned max_damage, const vector<info_monster>& all_monsters)
{
    std::vector <int> numbers_monsters;
    for (unsigned i = 0; i < all_monsters.size(); i++)
    {
        if ((min_hp <= all_monsters[i].hp) && (max_damage >= all_monsters[i].damage)) numbers_monsters.push_back(i);
    }
    return numbers_monsters;
}
void find_name_menu(const vector<info_monster>& all_monsters)
{
    string fragment_name = read_name("the full name or snippet of");
    write_monsters_menu(find_name(fragment_name,all_monsters), all_monsters);
}
vector <int> find_name(string fragment_name, const vector<info_monster>& all_monsters)
{
    vector <int> numbers_monsters;
    int fragment_size = fragment_name.size();
    for (unsigned i = 0; i < all_monsters.size(); i++)
    {
        string name = all_monsters[i].name;
        int name_size = name.size();
        if (fragment_size <= name_size) 
        {
            transform(name.begin(), name.end(), name.begin(), ::tolower);
            transform(fragment_name.begin(), fragment_name.end(), fragment_name.begin(), ::tolower);
            for(int j = 0; (j + fragment_size) <= name_size; j++)
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
void monster_search(const vector<info_monster>& all_monsters)
{
    while (true)
    {
        cout << "\nSelect Monster Search Mode:\n1)Search by Name.\n2)Search by hp and damage.\n"
            << "3)Search by type of special monster attack and date." << endl;
        switch (_getch())
        {
        case '1': find_name_menu(all_monsters);
            break;
        case '2': find_hp_damage_menu(all_monsters);
            break;
        case '3': find_types_time_menu(all_monsters);
            break;
        default:
            {
                cout << "\nPress the correct key!" << endl;
                continue;
            }
        }
        break;
    }
}
void demo_menu(int& delay)
{
    cout << "\nSelect the application mode:\n1)Interactive dialog mode. <- press\n"
        << "2)Demo mode.\n3)Automatic benchmark mode.\n0)Exit.\n";
    Sleep(delay);
    cout << "\nSelect the opening mode:\n1)Text mode. <- press\n2)Binary mode." << endl;
    Sleep(delay);
}
void demo_read_name(int& delay,const string& sentence, const string& name)
{
    cout << "\nEnter " << sentence << " name of monster: <- write " 
         << sentence << " name and press <Enter>\n";
    Sleep(delay);
    cout << "Enter " << sentence << " name of monster: " << name << endl;
    Sleep(delay);
}
void demo_read_hp(int& delay, const string& sentence, const unsigned& hp)
{
    cout << "\nEnter " << sentence << " number of monster health units (1-50000): <- write "
         << sentence << " hp and press <Enter>\n";
    Sleep(delay);
    cout << "Enter " << sentence << " number of monster health units (1-50000): " << hp << endl;
    Sleep(delay);
}
void demo_read_damage(int& delay, const string& sentence, const unsigned& damage)
{
    cout << "\nEnter " << sentence
        << " number of monster attack units (1-1000): <- write "
        << sentence << " damage and press <Enter>\n";
    Sleep(delay);
    cout << "Enter " << sentence
        << " number of monster attack units (1-1000): " << damage << endl;
    Sleep(delay);
}
void demo_read_chance(int& delay, const string& sentence, const double& chance)
{
    cout << "\nEnter " << sentence
        << " chance to launch a special attack of monster (0.00 - 1.00): <- write "
        << sentence << " chance and press <Enter>\n";
    Sleep(delay);
    cout << "Enter " << sentence
        << " chance to launch a special attack of monster (0.00 - 1.00): " << chance << endl;
    Sleep(delay);
}
void demo_read_type(int& delay, const short& type_of_attack)
{
    cout << "\nChoose one of the possible types of special monster attack:";
    switch (type_of_attack)
    {
    case 1: cout << "\n1)Increase damage. <- press\n"
                 << "2)Repeat the attack.\n3)Cure yourself.\n4)Paralyze the enemy." << endl;
        break;
    case 2: cout << "\n1)Increase damage.\n"
                 << "2)Repeat the attack. <- press\n3)Cure yourself.\n4)Paralyze the enemy." << endl;
    }
    Sleep(delay+1000);
}
void demo_add_monster(int& delay, vector <info_monster>& demo_monsters)
{
    cout << "\nMenu:\n1)Add a new monster. <- press\n2)Show all the monsters.\n3)Find an existing monster.\n"
        << "4)Edit a monster.\n5)Delete a monster.\n0)Back." << endl;
    Sleep(delay);
    cout << "\nCreate your own monster!" << endl;
    demo_read_name(delay, "a", "Name1");
    demo_read_hp(delay, "a", 8421);
    demo_read_damage(delay, "a", 911);
    demo_read_chance(delay, "a", 0.32);
    demo_read_type(delay, 1);
    demo_monsters.push_back(info_monster("Name1", 8421, 911, 0.32, types_of_attack::INCREASE, demo_monsters));
    cout << "\nNew monster created!\nHis personal ID: " << demo_monsters[0].id << endl;
    write_time(demo_monsters[0].time_info);
    Sleep(delay);
}
void demo_show_all_monsters(int& delay, const vector <info_monster>& demo_monsters)
{
    cout << "\nMenu:\n1)Add a new monster.\n2)Show all the monsters. <- press\n3)Find an existing monster.\n"
        << "4)Edit a monster.\n5)Delete a monster.\n0)Back." << endl;
    Sleep(delay+1000);
    write_all_monsters(demo_monsters);
    Sleep(delay+1000);
}
void demo_find_monsters(int& delay)
{
    cout << "\nMenu:\n1)Add a new monster.\n2)Show all the monsters.\n3)Find an existing monster. <- press\n"
        << "4)Edit a monster.\n5)Delete a monster.\n0)Back." << endl;
    Sleep(delay);
}
void demo_find_name(int& delay, const vector<info_monster>& demo_monsters)
{
    demo_find_monsters(delay);
    cout << "\nSelect Monster Search Mode:\n1)Search by Name. <- press\n2)Search by hp and damage.\n"
        << "3)Search by type of special monster attack and date." << endl;
    Sleep(delay);
    demo_read_name(delay, "the full name or snippet of", "Me1");
    write_monsters_menu(find_name("Me1", demo_monsters), demo_monsters);
    Sleep(delay+1000);
}
void demo_find_hp_damage(int& delay, const vector<info_monster>& demo_monsters)
{
    demo_find_monsters(delay);
    cout << "\nSelect Monster Search Mode:\n1)Search by Name.\n2)Search by hp and damage. <- press\n"
        << "3)Search by type of special monster attack and date." << endl;
    Sleep(delay);
    unsigned min_hp = demo_monsters[0].hp - 100;
    unsigned max_damage = demo_monsters[0].damage + 20;
    demo_read_hp(delay,"the minimum", min_hp);
    demo_read_damage(delay,"the maximum", max_damage);
    write_monsters_menu(find_hp_damage(min_hp, max_damage, demo_monsters), demo_monsters);
    Sleep(delay+1000);
}
void demo_find_types_time(int& delay, const vector<info_monster>& demo_monsters)
{
    demo_find_monsters(delay);
    cout << "\nSelect Monster Search Mode:\n1)Search by Name.\n2)Search by hp and damage.\n"
        << "3)Search by type of special monster attack and date. <- press" << endl;
    Sleep(delay);
    types_of_attack type = demo_monsters[0].type_of_attack;
    demo_read_type(delay, 1);
    cout << "\nEnter the maximum date and time the monster was created:" << endl;
    int* find_time = new int[6];
    find_time[0] = demo_monsters[0].time_info.tm_year + 1901;
    find_time[1] = demo_monsters[0].time_info.tm_mon + 1;
    find_time[2] = demo_monsters[0].time_info.tm_mday;
    find_time[3] = demo_monsters[0].time_info.tm_hour;
    find_time[4] = demo_monsters[0].time_info.tm_min;
    find_time[5] = demo_monsters[0].time_info.tm_sec;
    cout << "\nEnter year(2020-....): <- write a year and press <Enter>" << endl;
    Sleep(delay);
    cout << "Enter year(2020-....): " << find_time[0] << endl;
    cout << "\nEnter month(1-12): <- write a month and press <Enter>" << endl;
    Sleep(delay);
    cout << "Enter month(1-12): " << find_time[1] << endl;
    cout << "\nEnter day(1-31): <- write a day and press <Enter>" << endl;
    Sleep(delay);
    cout << "Enter day(1-31): " << find_time[2] << endl;
    cout << "\nEnter hour(0-23): <- write a hour and press <Enter>" << endl;
    Sleep(delay);
    cout << "Enter hour(0-23): " << find_time[3] << endl;
    cout << "\nEnter minute(0-59): <- write a minute and press <Enter>" << endl;
    Sleep(delay);
    cout << "Enter minute(0-59): " << find_time[4] << endl;
    cout << "\nEnter second(0-59): <- write a second and press <Enter>" << endl;
    Sleep(delay);
    cout << "Enter second(0-59): " << find_time[5] << endl;
    Sleep(delay+1000);
    write_monsters_menu(find_types_time(type, find_time, demo_monsters), demo_monsters);
    Sleep(delay+1000);
    delete[] find_time;
}
void demo_read_id(int& delay, const vector<info_monster>& demo_monsters)
{
    cout << "\nEnter id of monster: <- write the id and press <Enter>" << endl;
    Sleep(delay);
    cout << "Enter id of monster: " << demo_monsters[0].id << endl;
    Sleep(delay);
}
void demo_edit_monsters_menu(int& delay, vector<info_monster>& demo_monsters)
{
    Sleep(delay);
    cout << "\nMonster:\n" << endl;
    impl::write_monster(0, demo_monsters);
    Sleep(delay);
}
void demo_edit_monster(int& delay, vector<info_monster>& demo_monsters)
{
    cout << "\nMenu:\n1)Add a new monster.\n2)Show all the monsters.\n3)Find an existing monster.\n"
        << "4)Edit a monster. <- press\n5)Delete a monster.\n0)Back." << endl;
    Sleep(delay);
    demo_read_id(delay, demo_monsters);
    demo_edit_monsters_menu(delay, demo_monsters);
    cout << "\nSelect the option you want to edit:\n"
        << "1)Name. <- press\n2)HP.\n3)Damage.\n4)Chance to launch a special attack.\n"
        << "5)Type of special monster attack.\n0)Exit." << endl;
    Sleep(delay);
    demo_read_name(delay, "a new", "Name2");
    demo_monsters[0].name = "Name2";
    demo_edit_monsters_menu(delay, demo_monsters);
    cout << "\nSelect the option you want to edit:\n"
        << "1)Name.\n2)HP. <- press\n3)Damage.\n4)Chance to launch a special attack.\n"
        << "5)Type of special monster attack.\n0)Exit." << endl;
    Sleep(delay);
    demo_read_hp(delay, "a new", 10700);
    demo_monsters[0].hp = 10700;
    demo_edit_monsters_menu(delay, demo_monsters);
    cout << "\nSelect the option you want to edit:\n"
        << "1)Name.\n2)HP.\n3)Damage. <- press\n4)Chance to launch a special attack.\n"
        << "5)Type of special monster attack.\n0)Exit." << endl;
    Sleep(delay);
    demo_read_damage(delay, "a new", 800); 
    demo_monsters[0].damage = 800;
    demo_edit_monsters_menu(delay, demo_monsters);
    cout << "\nSelect the option you want to edit:\n"
        << "1)Name.\n2)HP.\n3)Damage.\n4)Chance to launch a special attack. <- press\n"
        << "5)Type of special monster attack.\n0)Exit." << endl;
    Sleep(delay);
    demo_read_chance(delay, "a new", 0.64);
    demo_monsters[0].chance = 0.64;
    demo_edit_monsters_menu(delay, demo_monsters);
    cout << "\nSelect the option you want to edit:\n"
        << "1)Name.\n2)HP.\n3)Damage.\n4)Chance to launch a special attack.\n"
        << "5)Type of special monster attack. <- press\n0)Exit." << endl;
    Sleep(delay);
    demo_read_type(delay, 2);
    demo_monsters[0].type_of_attack = types_of_attack::REPEAT;
    demo_edit_monsters_menu(delay, demo_monsters);
    cout << "\nSelect the option you want to edit:\n"
        << "1)Name.\n2)HP.\n3)Damage.\n4)Chance to launch a special attack.\n"
        << "5)Type of special monster attack.\n0)Exit. <- press" << endl;
    Sleep(delay);
}
void demo_delete_monster(int& delay, vector<info_monster>& demo_monsters)
{
    cout << "\nMenu:\n1)Add a new monster.\n2)Show all the monsters.\n3)Find an existing monster.\n"
        << "4)Edit a monster.\n5)Delete a monster. <- press\n0)Back." << endl;
    Sleep(delay);
    demo_read_id(delay, demo_monsters);
    demo_monsters.erase(demo_monsters.begin());
    cout << "\nThe monster - removed!" << endl;
    Sleep(delay);
}
void demo_exit(int& delay)
{
    cout << "\nMenu:\n1)Add a new monster.\n2)Show all the monsters.\n3)Find an existing monster.\n"
        << "4)Edit a monster.\n5)Delete a monster.\n0)Back. <- press" << endl;
    Sleep(delay);
}
void monster_generator(vector<info_monster>& all_monsters)//the function creates a monster with random parameters
{    
    srand(unsigned(time(0)));
    string name;
    int n = (rand() % 30 + 5);
    char* buff = new char[n + 1];
    for (int i = 0; i < n; i++)
    {
        buff[i] = 'a' + (rand() % 26);
    }
    buff[n] = '\0';
    name = buff;
    unsigned hp = (rand() % 50000 + 1);
    unsigned damage = (rand() % 1000 + 1);
    double chance = 0.01 * double(rand() % 101);
    types_of_attack type = types_of_attack::INCREASE;
    int k = (rand() % 4 + 1);
    switch (k)
    {
    case 1: type = types_of_attack::INCREASE;
        break;
    case 2: type = types_of_attack::REPEAT;
        break;
    case 3: type = types_of_attack::CURE;
        break;
    case 4: type = types_of_attack::PARALYZE;
        break;
    }
    all_monsters.push_back(info_monster(name, hp, damage, chance, type, all_monsters));
    delete[] buff;
}
std::size_t size_file(const string& path)
{
    std::ifstream file(path);
    file.seekg(0, std::ios_base::end);
    std::size_t sizef = size_t(file.tellg());
    file.close();

    return sizef;
}
void add_program_test(const string& path, const measurement_result& date,bool is_size = true)//the function adds the measurement result to a text file
{
    std::ofstream file(path, std::ios_base::app);
    file << "N: " << date.number_of_monsters << endl;
    file << "Time: " << date.time << endl;
    if (is_size) file << "Size file:" << date.size << endl << endl;
    file.close();
}
float measurement_open_txt(vector<info_monster>& all_monsters)//the function measures the opening time of a text file
{
    measurement_result open_txt;
    auto the_start = std::chrono::high_resolution_clock::now();
    auto the_end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> duration;
    open_txt.number_of_monsters = all_monsters.size();
    the_start = std::chrono::high_resolution_clock::now();
    all_monsters = open_text_file("benchmark_text.txt");
    the_end = std::chrono::high_resolution_clock::now();
    duration = the_end - the_start;
    open_txt.time = duration.count();
    add_program_test("result_open_txt_file.txt", open_txt,false);
    cout << "Time of open txt = " << open_txt.time << " seconds." << endl;
    all_monsters.clear();

    return open_txt.time;
}
float measurement_open_bin(vector<info_monster>& all_monsters)//the function measures the opening time of a binary file
{
    measurement_result open_bin;
    auto the_start = std::chrono::high_resolution_clock::now();
    auto the_end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> duration;
    open_bin.number_of_monsters = all_monsters.size();
    the_start = std::chrono::high_resolution_clock::now();
    all_monsters = open_binary_file("benchmark_binary.bin");
    the_end = std::chrono::high_resolution_clock::now();
    duration = the_end - the_start;
    open_bin.time = duration.count();
    add_program_test("result_open_binary_file.txt", open_bin, false);
    cout << "Time of open binary = " << open_bin.time << " seconds." << endl;

    return open_bin.time;
}
float measurement_save_txt(vector<info_monster>& all_monsters)//the function measures the storage time of a text file and its size
{
    measurement_result save_txt;
    auto the_start = std::chrono::high_resolution_clock::now();
    auto the_end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> duration;
    save_txt.number_of_monsters = all_monsters.size();
    the_start = std::chrono::high_resolution_clock::now();
    save_text_file("benchmark_text.txt",all_monsters);
    the_end = std::chrono::high_resolution_clock::now();
    duration = the_end - the_start;
    save_txt.time = duration.count();
    save_txt.size = size_file("benchmark_text.txt");
    add_program_test("result_save_txt_file.txt", save_txt);
    cout << "Time of save txt = " << save_txt.time << " seconds." << endl;
    cout << "Size of save txt = " << save_txt.size << " bytes." << endl;

    return save_txt.time;
}
float measurement_save_bin(vector<info_monster>& all_monsters)//the function measures the storage time of a binary file and its size
{
    measurement_result save_bin;
    save_bin.number_of_monsters = all_monsters.size();
    auto the_start = std::chrono::high_resolution_clock::now();
    auto the_end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> duration;
    the_start = std::chrono::high_resolution_clock::now();
    save_binary_file("benchmark_binary.bin",all_monsters);
    the_end = std::chrono::high_resolution_clock::now();
    duration = the_end - the_start;
    save_bin.time = duration.count();
    save_bin.size = size_file("benchmark_binary.bin");
    add_program_test("result_save_binary_file.txt", save_bin);
    cout << "Time of save binary = " << save_bin.time << " seconds." << endl;
    cout << "Size of save binary = " << save_bin.size << " bytes." << endl;
    all_monsters.clear();
    return save_bin.time;
}
float measurement_name_find(vector<info_monster>& all_monsters)//the function measures the search time of a monster in a file
{
    measurement_result name_find;
    auto the_start = std::chrono::high_resolution_clock::now();
    auto the_end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> duration;
    name_find.number_of_monsters = all_monsters.size();
    string name = all_monsters[name_find.number_of_monsters - 1].name;
    vector <int> number;
    the_start = std::chrono::high_resolution_clock::now();
    number = find_name(name, all_monsters);
    the_end = std::chrono::high_resolution_clock::now();
    duration = the_end - the_start;
    name_find.time = duration.count();
    add_program_test("result_name_find.txt", name_find, false);
    cout << "Time of find by name = " << name_find.time <<" seconds." << endl;

    return name_find.time;
}
float measurement_hp_damage_find(vector<info_monster>& all_monsters)//the function measures the search time of a monster in a file
{
    measurement_result xp_damage_find;
    auto the_start = std::chrono::high_resolution_clock::now();
    auto the_end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> duration;
    xp_damage_find.number_of_monsters = all_monsters.size();
    unsigned hp = all_monsters[xp_damage_find.number_of_monsters - 1].hp;
    unsigned damage = all_monsters[xp_damage_find.number_of_monsters - 1].damage;
    vector <int> number;
    the_start = std::chrono::high_resolution_clock::now();
    number = find_hp_damage(hp, damage, all_monsters);
    the_end = std::chrono::high_resolution_clock::now();
    duration = the_end - the_start;
    xp_damage_find.time = duration.count();
    add_program_test("result_xp_damage_find.txt", xp_damage_find, false);
    cout << "Time of find by xp and damage = " << xp_damage_find.time << " seconds." << endl;

    return xp_damage_find.time;
}
float measurement_time_type_find(vector<info_monster>& all_monsters)//the function measures the search time of a monster in a file
{
    measurement_result time_type_find;
    auto the_start = std::chrono::high_resolution_clock::now();
    auto the_end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> duration;
    time_type_find.number_of_monsters = all_monsters.size();
    vector <int> number;
    types_of_attack type = all_monsters[time_type_find.number_of_monsters - 1].type_of_attack;
    int time[6] = {2021,12,28,23,59,59};
    the_start = std::chrono::high_resolution_clock::now();
    number = find_types_time(type, time,all_monsters);
    the_end = std::chrono::high_resolution_clock::now();
    duration = the_end - the_start; 
    time_type_find.time = duration.count();
    add_program_test("result_time_type_find.txt", time_type_find, false);
    cout << "Time of find by types of attack and time = " << time_type_find.time << " seconds." << endl;
    all_monsters.clear();

    return time_type_find.time;
}
void clear_result_files()//function clears old result files
{
    string all_result_files[7] = { "result_save_txt_file.txt", "result_save_binary_file.txt",
        "result_open_txt_file.txt", "result_open_binary_file.txt", "result_name_find.txt", 
        "result_xp_damage_find.txt", "result_time_type_find.txt" };
    for (unsigned i = 0; i < 7; i++)
    {
        std::ofstream clear_file(all_result_files[i]);
        clear_file.close();
    }
}
vector<info_monster> opening_mode(const string& txt, const string& bin)
{
    while (true)
    {
        cout << "\nSelect the opening mode:\n1)Text mode.\n2)Binary mode." << endl;
        switch (_getch())
        {
        case '1':  return open_text_file(txt);
            break;
        case '2':  return open_binary_file(bin);
            break;
        default:
            {
                cout << "\nPress the correct key!" << endl;
                continue;
            }
        }
        break;
    }
}
void interactive_dialog_mode()
{
    vector <info_monster> all_monsters;
    string txt = "text.txt", bin = "binary.bin";
    all_monsters = opening_mode(txt, bin);
    while (true)
    {
        cout << "\nMenu:\n1)Add a new monster.\n2)Show all the monsters.\n3)Find an existing monster.\n"
            << "4)Edit a monster.\n5)Delete a monster.\n0)Back." << endl;
        switch (_getch())
        {
        case '1':
        {
            add_new_monster(all_monsters);
            continue;
        }
        break;
        case'2':
        {
            write_all_monsters(all_monsters);
            continue;
        }
        break;
        case '3':
        {
            monster_search(all_monsters);
            continue;
        }
        break;
        case '4':
        {
            edit_monster(all_monsters);
            continue;
        }
        break;
        case '5':
        {
            delete_monster(all_monsters);
            continue;
        }
        break;
        case '0':
        {
            if (!save_text_file("copy_"+txt, all_monsters) || !save_binary_file("copy_"+bin, all_monsters))
            {
                cout << "\nError saving copy file!..." << endl;
            }
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
            cout << "\nPress the correct key!" << endl;
            continue;
        }
        }
        break;
    }
}
void demo_mode()
{
    int delay = 1900;
    while (true)
    {
        cout << "\nEnter a delay to display data (in milliseconds; normal = 1900): ";
        cin >> delay;
        if ((delay < 0) || (!cin.good()))
        {
            cin.clear();
            cin.ignore(200, '\n');
            cout << "\nData entered incorrectly!" << endl;
            continue;
        }
        break;
    }
    vector <info_monster> demo_monsters;
    cout << "\nThe start of the demo mode(press <Ctrl + C> to exit)" << endl;
    demo_menu(delay);
    demo_add_monster(delay, demo_monsters);
    demo_show_all_monsters(delay, demo_monsters);
    demo_find_name(delay, demo_monsters);
    demo_find_hp_damage(delay, demo_monsters);
    demo_find_types_time(delay, demo_monsters);
    demo_edit_monster(delay, demo_monsters);
    demo_delete_monster(delay, demo_monsters);
    demo_exit(delay);
    cout << "\nThe end of the demo mode" << endl;
    Sleep(1000);
}
void benchmark_mode()
{
    clear_result_files();
    unsigned number_of_monsters, number_of_monsters_for_progression = 1;
    while (true)
    {
        cout << "\nEnter the initial number of monsters(1-...): ";
        cin >> number_of_monsters;
        if ((number_of_monsters < 1)||(!cin.good()))
        {
            cin.clear();
            cin.ignore(200, '\n');
            cout << "\nData entered incorrectly!" << endl;
            continue;
        }
        break;
    } 
    vector <info_monster> all_monsters;
    float function_time;
    const int number_of_function = 7;
    float (*arr_pointers_to_functions[number_of_function])(vector<info_monster>&) = { measurement_save_txt,
        measurement_save_bin, measurement_open_txt, measurement_open_bin ,measurement_name_find, 
        measurement_hp_damage_find, measurement_time_type_find };
    bool time_is_more_than_second = false, time_is_more_than_ten_seconds = false;
    unsigned coefficient = 2;
    while (true)
    {
        for (unsigned i = 0; i < number_of_monsters; i++)
        {
            monster_generator(all_monsters);
        }
        cout << "\n\nN = " << number_of_monsters << endl;
        for (unsigned j = 0; j < number_of_function; j++)
        {
            function_time = arr_pointers_to_functions[j](all_monsters);
            if (function_time >= 1) time_is_more_than_second = true;
            if (function_time > 10) time_is_more_than_ten_seconds = true;
        }
        if (time_is_more_than_ten_seconds) break;
        if (time_is_more_than_second) number_of_monsters = number_of_monsters_for_progression*coefficient++;
        else
        {
            number_of_monsters *= 2;
            number_of_monsters_for_progression = number_of_monsters;
        }
    }
    cout << "\nResults of measurements of program in the following files:\n"
        << "result_save_txt_file.txt\nresult_open_txt_file.txt\n"
        << "result_save_binary_file.txt\nresult_open_binary_file.txt\n"
        << "result_name_find.txt\nresult_xp_damage_find.txt\nresult_time_type_find.txt" << endl;
    std::remove("benchmark_text.txt");
    std::remove("benchmark_binary.bin");
}
int main()
{  
    cout << "<The Forest of Monsters>" << endl;
    while (true)
    {
        cout << "\nSelect the application mode:\n1)Interactive dialog mode.\n"
             <<"2)Demo mode.\n3)Automatic benchmark mode.\n0)Exit.\n";
        switch (_getch())
        {
        case '1': interactive_dialog_mode();
            break;
        case '2': demo_mode();
            break;
        case '3': benchmark_mode();
            break;
        case'0': 
            {
                cout << "\nExit..." << endl;
                return 0;
            }
            break;
        default: cout << "\nPress the correct key!" << endl;
        }
    }

    return 0;
}