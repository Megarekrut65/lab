#include "my_monsters.h"
#include <string>
#include <ctime>
#include <vector>
#include <iostream>

using std::string;
using std::vector;
using std::cout;
using std::endl;
namespace monster
{
    unsigned long set_id(const vector<info_monster>&);
    enum class types_of_attack : int
    {
        INCREASE = 1,
        REPEAT,
        CURE,
        PARALYZE
    };
    struct info_monster
    {
        unsigned long id;
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
        info_monster(string name, unsigned hp, unsigned damage, double chance, types_of_attack type_of_attack, const vector<info_monster>& all_monsters)
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
    unsigned long set_id(const vector<info_monster>& all_monsters)
    {
        unsigned long new_id = 1000;
        long size = all_monsters.size();
        if (size == 0) return new_id;
        else return all_monsters[size - 1].id + 1;
    }
    void write_time(struct std::tm time_info)
    {
        char buffer[80];
        strftime(buffer, 80, "Creation time and date: %X  %d.%m.%Y", &time_info);
        cout << buffer << endl;
    }
    void write_type(types_of_attack type)
    {
        switch (type)
        {
        case types_of_attack::INCREASE: cout << "Increase damage." << endl;
            break;
        case types_of_attack::REPEAT: cout << "Repeat the attack." << endl;
            break;
        case types_of_attack::CURE: cout << "Cure yourself." << endl;
            break;
        case types_of_attack::PARALYZE: cout << "Paralyze the enemy." << endl;
        }
    }
    void write_parameter(const info_monster& monster, const int number)
    {
        switch (number)
        {
        case 0: cout << "ID: " << monster.id << "." << endl;
            break;
        case 1: cout << "Name: " << monster.name << "." << endl;
            break;
        case 2: cout << "HP: " << monster.hp << "." << endl;
            break;
        case 3: cout << "Damage: " << monster.damage << "." << endl;
            break;
        case 4: cout << "Chance to launch a special attack: " << monster.chance << "." << endl;
            break;
        case 5: write_type(monster.type_of_attack);
            break;
        case 6: write_time(monster.time_info);
            break;
        }
    }
    void write_monsters(const vector<info_monster>& all_monsters)
    {
        for (long i = 0; i < all_monsters.size(); i++)
        {
            cout << i + 1 << ".\n";
            for (int j = 0; j < 7; j++)
            {
                write_parameter(all_monsters[i], j);
            }           
        }   
    }  
    vector<info_monster> monsters_generator(long number_of_monsters)
    {
        vector<info_monster> all_monsters;      
        for (long i = 0; i < number_of_monsters; i++)
        {
            all_monsters.push_back(info_monster(random_name(), random_hp(), random_damage(), random_chance(), random_type(), all_monsters));
        }
        return all_monsters;
    }
    string random_name()
    {
        srand(time(0));
        int size = rand() % 1000;
        string name = "";
        for (int i = 0; i < size; i++)
        {
            int word = rand() % 26;
            name += 'a' + word;
        }
        return name;
    }
    unsigned random_hp()
    {
        srand(time(0));
        return unsigned(rand() % 50000);
    }
    unsigned random_damage()
    {
        srand(time(0));
        return unsigned(rand() % 1000);
    }
    double random_chance()
    {
        srand(time(0));
        int integer = rand() % 101;
        return double(0.01 * integer);
    }
    types_of_attack random_type()
    {
        int type = rand() % 4 + 1;
        switch (type)
        {
        case 1: return types_of_attack::INCREASE;
        case 2: return types_of_attack::REPEAT;
        case 3: return types_of_attack::CURE;
        case 4: return types_of_attack::PARALYZE;
        }
    }   
}
