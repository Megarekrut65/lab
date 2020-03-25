#include "my_key_sort.h"
#include "my_monsters.h"
#include <iostream>
#include <vector>
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
            if (priority >= number_of_keys) return -1;
            for (int i = 0; i < number_of_keys; i++)
            {
                if (priority == priorities[i]) return i;
            }
            return -1;
        }
        int give_min_priority()
        {
            return priority + 1;
        }
        ~Keys()
        {
            priority = 0;
            delete[] priorities;
        }
    };
    void write_array(std::vector<monster::info_monster> array, Keys keys)
    {
        std::cout << "\nArray: ";
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
    void audit_step(std::vector<monster::info_monster> array, Keys keys, long frequency, long& step)//checks whether an array is to be output
    {
        step++;
        if ((frequency == 0) || (frequency == -1) || (step % frequency != 0)) return;
        step = 0;
        write_array(array, keys);
    }
    template<class T>
    void swap(T& a, T& b)
    {
        T temp;
        temp = a;
        a = b;
        b = temp;
    }
    template<class T>
    bool comparison()
    {

    }
    bool comparison_monsters(const monster::info_monster& a, const monster::info_monster& b, Keys keys)
    {
        int priority = keys.give_min_priority();
        for (int i = 6; i >= priority; i--)
        {

        }
    }
    long partition(std::vector<monster::info_monster> array, Keys keys, long low, long high, long frequency, long& step)
    {
        monster::info_monster pivot = array[high];
        long i = low - 1;
        for (long j = low; j < high; j++)
        {
            if (array[j] <= pivot)
            {
                i++;
                swap(array[i], array[j]);
                audit_step(array, keys, frequency, step);                
            }
        }
        swap(array[i + 1], array[high]);
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
    }
}
