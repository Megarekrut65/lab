#include <iostream>
#include <vector>
#include <ctime>
#include <conio.h>

namespace monster
{
    struct info_monster;
    unsigned long set_id(const std::vector<info_monster>&);
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
        std::string name;
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
            this->time_info = tm();
            this->id = -1;
        }
        info_monster(std::string name, unsigned hp, unsigned damage, double chance, types_of_attack type_of_attack, const std::vector<info_monster>& all_monsters)
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
    unsigned long set_id(const std::vector<info_monster>& all_monsters)
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
        std::cout << buffer << std::endl;
    }
    void write_type(types_of_attack type)
    {
        std::cout << "Type of special monster attack: ";
        switch (type)
        {
        case types_of_attack::INCREASE: std::cout << "Increase damage." << std::endl;
            break;
        case types_of_attack::REPEAT: std::cout << "Repeat the attack." << std::endl;
            break;
        case types_of_attack::CURE: std::cout << "Cure yourself." << std::endl;
            break;
        case types_of_attack::PARALYZE: std::cout << "Paralyze the enemy." << std::endl;
        }
    }
    void write_parameter(const info_monster& monster, const int number)
    {
        switch (number)
        {
        case 0: std::cout << "ID: " << monster.id << "." << std::endl;
            break;
        case 1: std::cout << "Name: " << monster.name << "." << std::endl;
            break;
        case 2: std::cout << "HP: " << monster.hp << "." << std::endl;
            break;
        case 3: std::cout << "Damage: " << monster.damage << "." << std::endl;
            break;
        case 4: std::cout << "Chance to launch a special attack: " << monster.chance << "." << std::endl;
            break;
        case 5: write_type(monster.type_of_attack);
            break;
        case 6: write_time(monster.time_info);
            break;
        }
    }
    void write_monsters(const std::vector<info_monster>& all_monsters)
    {
        for (long i = 0; i < all_monsters.size(); i++)
        {
            std::cout << i + 1 << ".\n";
            for (int j = 0; j < 7; j++)
            {
                write_parameter(all_monsters[i], j);
            }
        }
    }
    std::string random_name()
    {        
        int size = rand() % 30;
        std::string name = "";
        for (int i = 0; i < size; i++)
        {
            int word = rand() % 26;
            name += 'a' + word;
        }
        return name;
    }
    unsigned random_hp()
    {
        return unsigned(rand() % 50000);
    }
    unsigned random_damage()
    {
        return unsigned(rand() % 1000);
    }
    double random_chance()
    {
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
        return types_of_attack::INCREASE;
    }
    std::vector<info_monster> monsters_generator(long number_of_monsters)
    {
        std::vector<info_monster> all_monsters;
        srand(unsigned(time(0)));
        for (long i = 0; i < number_of_monsters; i++)
        {
            all_monsters.push_back(info_monster(random_name(), random_hp(), random_damage(), random_chance(), random_type(), all_monsters));
        }
        return all_monsters;
    }
}
namespace key_sorting
{
    struct Keys
    {
    private:
        const int number_of_keys = 7;
        int* priorities;
        int priority;
    public:
        Keys()
        {
            priorities = new int[number_of_keys];
            priority = 6;
            for (int i = 0; i < number_of_keys; i++)
            {
                priorities[i] = -1;
            }
        }
        void edit_key(bool key, int index)
        {
            if ((index >= number_of_keys)) return;
            if (key) priorities[index] = priority--;
            else priorities[index] = -1;
        }
        bool is_key(int index)
        {
            if ((index >= number_of_keys)) return false;
            if (priorities[index] != -1) return true;
            return false;
        }
        int give_index(int priority)
        {
            if (priority >= number_of_keys) return 0;
            for (int i = 0; i < number_of_keys; i++)
            {
                if (priority == priorities[i]) return i;
            }
            return 0;
        }
        int give_min_priority()
        {
            return priority + 1;
        }
        void clear()
        {
            delete[] priorities;
        }
    };
    void write_array(const std::vector<monster::info_monster>& array, Keys keys)
    {
        std::cout << "\nArray:" << std::endl;
        for (long i = 0; i < array.size(); i++)
        {
            std::cout << i + 1 << ".\n";
            monster::write_parameter(array[i], 0);
            for (int j = 1; j < 7; j++)
            {
                if (keys.is_key(j)) monster::write_parameter(array[i], j);
            }
        }
        std::cout << std::endl;
    }
    void audit_step(const std::vector<monster::info_monster>& array, Keys keys, long frequency, long& step)//checks whether an array is to be output
    {
        step++;
        if ((frequency == 0) || (frequency == -1) || (step % frequency != 0)) return;
        step = 0;
        write_array(array, keys);
    }
    void swap(monster::info_monster& a, monster::info_monster& b)
    {
        monster::info_monster temp;
        temp = a;
        a = b;
        b = temp;
    }
    bool is_time(const int* time_a, const int* time_b, int number = 0)//recursion to check that the monster is created no later than the specified time
    {
        if (number == 6) return false;
        if (time_a[number] > time_b[number]) return false;
        else
        {
            if (number == 5) return true;
            if (time_a[number] < time_b[number]) return true;
            return is_time(time_a, time_b, ++number);
        }
    }
    bool comparison_time(struct tm a, struct tm b)
    {
        int* time_a = new int[6];
        int* time_b = new int[6];
        time_a[0] = a.tm_year;
        time_a[1] = a.tm_mon;
        time_a[2] = a.tm_mday;
        time_a[3] = a.tm_hour;
        time_a[4] = a.tm_min;
        time_a[5] = a.tm_sec;
        time_b[0] = b.tm_year;
        time_b[1] = b.tm_mon;
        time_b[2] = b.tm_mday;
        time_b[3] = b.tm_hour;
        time_b[4] = b.tm_min;
        time_b[5] = b.tm_sec;
        return is_time(time_a, time_b);
    }
    bool comparison(const monster::info_monster& a, const monster::info_monster& b, int number)
    {
        monster::write_parameter(a, number);
        std::cout << std::endl;
        monster::write_parameter(b, number);
        switch (number)
        {
        case 0: return (a.id <= b.id);
        case 1: return (a.name <= b.name);
        case 2: return (a.hp <= b.hp);
        case 3: return (a.damage <= b.damage);
        case 4: return (a.chance <= b.chance);
        case 5: return (a.type_of_attack <= b.type_of_attack);
        case 6: return comparison_time(a.time_info, b.time_info);
        }
        return false;
    }
    bool equal_comparison_time(struct tm a, struct tm b)
    {
        if (a.tm_year != b.tm_year) return false;
        if (a.tm_mon != b.tm_mon) return false;
        if (a.tm_mday != b.tm_mday) return false;
        if (a.tm_hour != b.tm_hour) return false;
        if (a.tm_min != b.tm_min) return false;
        if (a.tm_sec != b.tm_sec) return false;
        return true;
    }
    bool equal_comparison(const monster::info_monster& a, const monster::info_monster& b, int number)
    {
        switch (number)
        {
        case 0: return a.id == b.id;
        case 1: return a.name == b.name;
        case 2: return a.hp == b.hp;
        case 3: return a.damage == b.damage;
        case 4: return a.chance == b.chance;
        case 5: return a.type_of_attack == b.type_of_attack;
        case 6: return equal_comparison_time(a.time_info, b.time_info);
        }
        return false;
    }
    bool comparison_monsters(monster::info_monster& a, monster::info_monster& b, Keys keys)
    {
        int priority = keys.give_min_priority();
        std::cout << "min pri: " << priority << std::endl;
        bool end = false;
        for (int i = 6; i >= priority; i--)
        {
            if (comparison(a, b, keys.give_index(i)))
            {
                end = true;
                if (equal_comparison(a, b, keys.give_index(i)))
                {
                    continue;
                }
            }
            else if (end) swap(a, b);
            return end;
        }
        return end;
    }
    long partition(std::vector<monster::info_monster> array, Keys keys, long low, long high, long frequency, long& step)
    {
        monster::info_monster pivot = array[high];
        long i = low - 1;
        for (long j = low; j < high; j++)
        {
            if (comparison_monsters(array[j], pivot, keys))
            {
                std::cout << "true\n";
                i++;
                swap(array[j], array[i]);
                audit_step(array, keys, frequency, step);
            }
        }
        swap(array[i + 1], array[high]);
        audit_step(array, keys, frequency, step);
        return (i + 1);
    }
    void current_quick_sort(std::vector<monster::info_monster> array, Keys keys, long low, long high, long frequency, long& step)
    {
        if (low < high)
        {
            long index = partition(array, keys, low, high, frequency, step);
            current_quick_sort(array, keys, low, index - 1, frequency, step);
            current_quick_sort(array, keys, index + 1, high, frequency, step);
        }
    }
    void quick_sort(std::vector<monster::info_monster> array, Keys keys, long frequency)
    {
        long step = 0;
        long size = array.size();
        current_quick_sort(array, keys, 0, size - 1, frequency, step);
        if (frequency != 0)
        {
            write_array(array, keys);
        }
    }
}

int main()
{
	std::vector<monster::info_monster> array;
    for (unsigned i = 0; i < 7; i++)
    {
        array.push_back(monster::info_monster("name", 7 - i, 7 - i, 0.1, monster::types_of_attack::CURE, array));
    }
    array.push_back(monster::info_monster("name", 10, 1, 0.1, monster::types_of_attack::CURE, array));
    key_sorting::Keys keys;
    keys.edit_key(true, 2);
    key_sorting::write_array(array, keys);
    //key_sorting::write_array(all_monsters, keys);
    key_sorting::quick_sort(array, keys, 1);
    keys.clear();
	return 0;
}

