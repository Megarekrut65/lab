#include <iostream>
#include <vector>
#include <ctime>
#include <conio.h>
#include <chrono>
#include "my_correct_read.h"

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
        info_monster(std::string name, unsigned hp, unsigned damage, double chance, types_of_attack type_of_attack,struct std::tm time_info, const std::vector<info_monster>& all_monsters)
        {
            this->name = name;
            this->hp = hp;
            this->damage = damage;
            this->chance = chance;
            this->type_of_attack = type_of_attack;          
            this->time_info = time_info;
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
        std::cout << "Type of special attack: ";
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
        int size = rand() % 30 + 1;
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
    struct std::tm random_time()
    {
        struct std::tm time_info;
        time_info.tm_year = rand() % 120;
        time_info.tm_mon = rand() % 12;
        time_info.tm_mday = rand() % 28 + 1;
        time_info.tm_hour = rand() % 24;
        time_info.tm_min = rand() % 60;
        time_info.tm_sec = rand() % 60;
        return time_info;
    }
    std::vector<info_monster> monsters_generator(long number_of_monsters)
    {
        std::vector<info_monster> all_monsters;
        srand(unsigned(time(0)));
        for (long i = 0; i < number_of_monsters; i++)
        {
            all_monsters.push_back(info_monster(random_name(), random_hp(), random_damage(), random_chance(), random_type(), random_time(), all_monsters));
        }
        return all_monsters;
    }
    void copy(const std::vector<info_monster>& array, std::vector<info_monster>& copy_array)
    {
        long size = array.size();
        for (long i = 0; i < size; i++)
        {
            copy_array[i] = array[i];
        }
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
            else
            {
                if (priorities[index] == -1) return;
                for (int i = 0; i < number_of_keys; i++)
                {
                    if ((priorities[i] != -1) && (priorities[i] < priorities[index])) priorities[i]++;
                }                
                priorities[index] = -1;
                priority++;
            }
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
        
        if ((frequency == 0) || (frequency == -1))
        {
            step = 0;
            return;
        }
        step++;     
        if (step % frequency != 0) return;
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
    bool is_time(const int* time_a, const int* time_b, int number = 0)
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
    long partition(std::vector<monster::info_monster>& array, Keys keys, long low, long high, long frequency, long& step)
    {
        long i = low - 1;
        for (long j = low; j < high; j++)
        {
            if (comparison_monsters(array[j], array[high], keys))
            {
                i++;
                swap(array[j], array[i]);
                audit_step(array, keys, frequency, step);
            }
        }
        swap(array[i + 1], array[high]);
        audit_step(array, keys, frequency, step);
        return (i + 1);
    }
    void current_quick_sort(std::vector<monster::info_monster>& array, Keys keys, long low, long high, long frequency, long& step)
    {
        if (low < high)
        {
            long index = partition(array, keys, low, high, frequency, step);
            current_quick_sort(array, keys, low, index - 1, frequency, step);
            current_quick_sort(array, keys, index + 1, high, frequency, step);
        }
    }
    void quick_sort(std::vector<monster::info_monster>& array, Keys keys, long frequency)
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
namespace other_sorting
{     
    void current_radix_sort(std::vector<monster::info_monster>& array, int exp, int count_size)
    {
        long size = array.size();
        std::vector<monster::info_monster> result(size);
        std::vector<unsigned> count(count_size, 0);
        for (long i = 0; i < size; i++)
        {
            count[(array[i].hp / exp) % count_size]++;
        }
        for (long i = 1; i < count_size; i++)
        {
            count[i] += count[i - 1];
        }
        for (long i = size - 1; i >= 0; i--)
        {
            result[count[(array[i].hp / exp) % count_size] - 1] = array[i];
            count[(array[i].hp / exp) % count_size]--;
        }
        for (long i = 0; i < size; i++)
        {
            array[i] = result[i];
        }
        result.clear();
        count.clear();
    }
    unsigned max_hp(std::vector<monster::info_monster>& array)
    {
        long size = array.size();
        unsigned max = array[0].hp;
        for (long i = 1; i < size; i++)
        {
            if (array[i].hp > max)
            {
                max = array[i].hp;
            }
        }
        return max;
    }
    void radix_sort(std::vector<monster::info_monster>& array)
    {
        long size = array.size();
        unsigned max = max_hp(array);
        for (unsigned exp = 1; max / exp > 0; exp *= 10)
        {
            current_radix_sort(array, exp, 10);
        }
    }
    int types_of_attack_to_int(monster::types_of_attack& type)
    {
        switch (type)
        {
        case monster::types_of_attack::INCREASE: return 0;
            break;
        case monster::types_of_attack::REPEAT: return 1;
            break;
        case monster::types_of_attack::CURE: return 2;
            break;
        case monster::types_of_attack::PARALYZE: return 3;
            break;
        }
    }
    void count_sort(std::vector<monster::info_monster>& array)
    {
        long size = array.size();
        std::vector<monster::info_monster> result(size);
        std::vector<int> count(4, 0);
        for (long i = 0; i < size; i++)
        {
            count[types_of_attack_to_int(array[i].type_of_attack)]++;
        }
        for (int i = 1; i < 4; i++)
        {
            count[i] += count[i - 1];
        }
        for (long i = size - 1; i >= 0; i--)
        {
            result[count[types_of_attack_to_int(array[i].type_of_attack)] - 1] = array[i];
            count[types_of_attack_to_int(array[i].type_of_attack)]--;
        }
        for (long i = 0; i < size; i++)
        {
            array[i] = result[i];
        }
        result.clear();
        count.clear();
    }
}
void write_keys(key_sorting::Keys keys, bool choose)
{
    const int number_of_keys = 7;
    std::string name_of_keys[number_of_keys] = { "1)ID.", "2)Name.", "3)HP.", "4)Damage.", 
        "5)Chance to launch a special attack.", "6)Type of special attack.", "7)Creation time and date." };
    if (choose)
    {
        for (int i = 0; i < number_of_keys; i++)
        {
            if (!keys.is_key(i)) std::cout << name_of_keys[i] << std::endl;
        }
    }
    else
    {
        for (int i = 0; i < number_of_keys; i++)
        {
            if (keys.is_key(i)) std::cout << name_of_keys[i] << std::endl;
        }
    } 
}
void choose_key(key_sorting::Keys& keys, int index, bool& choose, int& priority)
{
    if (choose)
    {
        if (!keys.is_key(index))
        {
            keys.edit_key(choose, index);
            priority++;
        }
        else
        {
            std::cout << "\nPress the correct key!\n" << std::endl;
        }
    }
    else
    {       
        if (keys.is_key(index))
        {
            keys.edit_key(choose, index);
            choose = true;
            priority--;
        }
        else
        {
            std::cout << "\nPress the correct key!\n" << std::endl;
        }
    }
   
}
key_sorting::Keys choose_keys_menu()
{
    int priority = 1;
    key_sorting::Keys keys;
    std::string regime = "\nChoose ";
    bool choose = true;
    while (priority != 7)
    {
        if (choose) regime = "\nChoose ";
        else regime = "\nRemove ";
        std::cout << regime;
        if (choose) std::cout << priority << "th ";
        std::cout << "sort key:\n";
        write_keys(keys, choose);
        if (choose) std::cout << "8)Remove sort key.\n";
        else std::cout << "8)Choose sort key.\n";
        std::cout << "0)Start sorting."<< std::endl;
        std::cout << std::endl;
        switch (_getch())
        {
        case '1': choose_key(keys, 0, choose, priority);
            break;
        case '2': choose_key(keys, 1, choose, priority);
            break;
        case '3': choose_key(keys, 2, choose, priority);
            break;
        case '4': choose_key(keys, 3, choose, priority);
            break;
        case '5': choose_key(keys, 4, choose, priority);
            break;
        case '6': choose_key(keys, 5, choose, priority);
            break;
        case '7': choose_key(keys, 6, choose, priority);
            break;
        case '8': choose = !choose;
            break;
        case '0': return keys;
            break;
        default: std::cout << "\nPress the correct key!\n" << std::endl;
        }
    }
    return keys;
}
void demo_key_sort(const std::vector<monster::info_monster>& array, key_sorting::Keys keys, long frequency)
{
    if (keys.give_min_priority() > 6) keys.edit_key(true, 0);
    std::cout << "\nQuick sort by the selected keys." << std::endl;
    std::vector<monster::info_monster> copy_array(array.size());
    monster::copy(array, copy_array);
    key_sorting::quick_sort(copy_array, keys, frequency);
    copy_array.clear();
}
void demo_other_sorts(const std::vector<monster::info_monster>& array, long frequency)
{
    key_sorting::Keys keys;
    keys.edit_key(true, 5);
    std::cout << "\nCount sort by type of attack." << std::endl;
    std::vector<monster::info_monster> copy_array(array.size());
    monster::copy(array, copy_array);
    other_sorting::count_sort(copy_array);
    if (frequency != 0) key_sorting::write_array(copy_array, keys);
    keys.edit_key(false, 5);
    keys.edit_key(true, 2);
    std::cout << "\nRadix sort by hp." << std::endl;
    monster::copy(array, copy_array);
    other_sorting::radix_sort(copy_array);
    if (frequency != 0) key_sorting::write_array(copy_array, keys);
    copy_array.clear();
    keys.clear();
    std::cout << std::endl;
}
void demo_mode()
{
    long size, frequency;
    size = correct::read_long("size of array");
    if (size < 0)
    {
        std::cout << "\nThe size can`t be < 0!\n" << std::endl;
        return;
    }
    frequency = correct::read_long("the frequency of the array to display:\n('-1' - to show only the last step, '0' - not to show sorting steps,\n'1 - ...' - the number of steps through which the array will be displayed)");
    if (frequency < -1)
    {
        std::cout << "\nThe frequency can`t be < -1!\n" << std::endl;
        return;
    }
    std::vector<monster::info_monster> array;
    array = monster::monsters_generator(size);
    std::cout << "\nPress '1' if you want to see the array or enter another key if you don`t want that.";
    if(_getch() == '1') monster::write_monsters(array);
    std::cout << std::endl;
    key_sorting::Keys keys = choose_keys_menu();
    demo_key_sort(array, keys, frequency);   
    demo_other_sorts(array, frequency);
    keys.clear();
    array.clear();
}
void clear_result_files(const std::string& name_of_set)
{
    const int number_of_files = 5;
    std::string paths[number_of_files] = { "Bubble sort", "Quick sort",
        "Merge sort", "Library sort", "Combined sort" };
    for (int i = 0; i < number_of_files; i++)
    {
        std::ofstream file(name_of_set + paths[i] + ".txt");
        file.close();
    }
}
void benchmark_mode()
{
    clear_result_files(name_of_set);
    const int number_of_sorts = 4;
    void(*all_sorts[number_of_sorts])(int*, long, long) = { sorting::bubble_sort, sorting::quick_sort,
    sorting::merge_sort_topdown, sorting::library_sort };
    std::string name_of_sorts[number_of_sorts] = { "Bubble sort", "Quick sort", "Merge sort", "Library sort" };
    bool is_one_second = false, are_ten_seconds = false, long_bubble = false, once = true;
    long size = 1000;
    long copy_size = size, coefficient = 2;
    int max_threshold = 15;
    int max_value = 30000;
    while (true)
    {
        int* array = array_generator(size, max_value, set);
        float time;
        cout << "\nSize of array = " << size << endl << endl;
        for (int i = 0; i < number_of_sorts; i++)
        {
            if (long_bubble && (i == 0)) continue;
            time = measurement_sort(all_sorts[i], array, size, name_of_sorts[i], name_of_set);
            if (time > 1) is_one_second = true;
            if ((time > 10) && (i != 0)) are_ten_seconds = true;
            if (time > 10) long_bubble = true;
        }
        cout << endl;
        for (long j = 5; j < max_threshold; j++)
        {
            time = measurement_combined(array, size, j, name_of_set);
            if (time > 1) is_one_second = true;
            if (time > 10) are_ten_seconds = true;
        }
        if (once && long_bubble)
        {
            is_one_second = false;
            copy_size = size;
            coefficient = 2;
            once = false;
        }
        size = set_size(is_one_second, copy_size, coefficient);
        delete[] array;
        array = nullptr;
        if (are_ten_seconds) break;
    }
    cout << "\nResults of measurements of program in the following files:\n"
        << name_of_set + name_of_sorts[0] + ".txt\n" << name_of_set + name_of_sorts[1] + ".txt\n"
        << name_of_set + name_of_sorts[2] + ".txt\n" << name_of_set + name_of_sorts[3] + ".txt\n"
        << name_of_set + "Combined sort.txt\n" << endl;
}
int main()
{
    while (true)
    {
        std::cout << "Select the application mode:\n1)Demo mode.\n2)Automatic benchmark mode.\n0)Exit." << std::endl;
        switch (_getch())
        {
        case '1':  demo_mode();
            break;
        case '2': benchmark_mode();
            break;
        case'0':
        {
            std::cout << "\nExit..." << std::endl;
            return 0;
        }
        break;
        default: std::cout << "\nPress the correct key!\n" << std::endl;
        }
    }
	return 0;
}

