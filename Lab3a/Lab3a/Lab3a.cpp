#include <iostream>
#include <conio.h>
#include <ctime>
#include <chrono>
#include <string>
#include <fstream>
#include "my_correct_read.h"
#include "my_sorts.h"

using std::cout;
using std::cin;
using std::endl;
enum class array_set {RANDOM, SORTED, NOTSORTED};
struct measurement_result
{
    long size;
    float time;
};
void array_random(int* array, long size)
{
    int max_value = 30000;
    srand(time(0));
    for (long i = 0; i < size; i++)
    {
        array[i] = rand() % max_value;
    }
}
void array_sorted(int* array, long sorted, long not_sorted)
{
    int max_value = 30000;
    long size = sorted > not_sorted ? sorted : not_sorted;
    cout << "size: " << size << endl;
    long limit_size = size / 10;
    cout << "limit: " << limit_size << endl;
    for (long i = 0; i < (size - limit_size); i++)
    {
        array[i] = abs(not_sorted - i) % max_value;
    }
    for (long i = (size - limit_size); i < size; i++)
    {
        array[i] = abs(sorted - i) % max_value;
    } 
}
int* array_generator(long size, array_set set)
{
    if (size == 0) return nullptr;
    int* array = new int[size];
    switch (set)
    {
    case array_set::RANDOM: array_random(array, size);
        break;
    case array_set::SORTED: array_sorted(array, size, 0);
        break;
    case array_set::NOTSORTED: array_sorted(array, 0, size);
        break;
    }
    return array;
}
void write_array(int* array, long size)
{
    std::cout << "Array: ";
    for (long i = 0; i < size; i++)
    {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
}
void test()
{
    int* array = array_generator(60000, array_set::SORTED);
   // write_array(array, 6000000);
    sorting::library_sort(array, 60000, 0);
    delete[] array;
    array = nullptr;
}
void demo_mode()
{
    long size, frequency;
    cout << "Enter size:";
    cin >> size;
    cout << "Enter the frequency of the array to display\n"
        << "(where '-1' is to show only the last step,\n"
        << "'0' is not to show sorting steps,\n"
        << "'1 - ...' is the number of steps through which the array will be displayed)";
    cin >> frequency;
}
template<class T>
void add_to_end_of_file(T& value, const std::string& name_of_value,const std::string& path)
{
    std::ofstream file(path + ".txt", std::ios_base::app);
    file << name_of_value << " = " << value << "." << endl;
    file.close();
}
void add_result_to_file(measurement_result result, const std::string& name_of_sort)
{
    add_to_end_of_file(result.size, "Size", name_of_sort);
    add_to_end_of_file(result.time, "Time", name_of_sort);
}
void clear_result_files(const std::string& name_of_set)
{
    const int number_of_sorts = 5;
    std::string paths[number_of_sorts] = { "Bubble sort", "Quick sort", 
        "Merge sort topdown", "Library sort", "Combined sort" };
    for (int i = 0; i < number_of_sorts; i++)
    {
        std::ofstream file(name_of_set+paths[i]+".txt");
        file.close();
;   }
}
float measurement_sort(void sort(int*, long, int), int* array, long size, const std::string& name_of_sort, const std::string& name_of_set)
{
    int* copy_array = new int[size];
    std::copy(array, array + size, copy_array);
    auto the_start = std::chrono::high_resolution_clock::now();
    auto the_end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> duration;
    the_start = std::chrono::high_resolution_clock::now();
    sort(copy_array, size, 0);
    the_end = std::chrono::high_resolution_clock::now();
    duration = the_end - the_start;
    measurement_result result;
    result.size = size;
    result.time = duration.count();
    add_result_to_file(result, name_of_set+name_of_sort);
    cout << "Time of " << name_of_sort << " = " << result.time << endl;
    delete[] copy_array;
    return result.time;
}
float measurement_combined(int* array, long size, const int threshold, const std::string& name_of_set)
{
    int* copy_array = new int[size];
    std::copy(array, array + size, copy_array);
    auto the_start = std::chrono::high_resolution_clock::now();
    auto the_end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> duration;
    the_start = std::chrono::high_resolution_clock::now();
    sorting::combined_sort(copy_array, size, threshold, 0);
    the_end = std::chrono::high_resolution_clock::now();
    duration = the_end - the_start;
    measurement_result result;
    result.size = size;
    result.time = duration.count();
    add_result_to_file(result, name_of_set+"Combined sort");
    add_to_end_of_file(threshold, "Threshold", name_of_set+"Combined sort");
    cout << "Threshold of Combined sort = " << threshold << endl;
    cout << "Time of Combined sort = " << result.time << endl;  
    delete[] copy_array;
    return result.time;
}
long set_size(bool is_one_second, long& copy_size, long& coefficient)
{
    if (is_one_second)
    {
        return coefficient++ * copy_size;
    }
    else
    {
        return copy_size *= 2;
    }
}
void benchmark_mode(array_set set, const std::string& name_of_set)
{
    clear_result_files(name_of_set);
    const int number_of_sorts = 4;
    void(*all_sorts[number_of_sorts])(int*, long, int) = { sorting::bubble_sort, sorting::quick_sort,
    sorting::merge_sort_topdown, sorting::library_sort };
    std::string name_of_sorts[number_of_sorts] = { "Bubble sort", "Quick sort", "Merge sort topdown", "Library sort" };
    bool is_one_second = false, are_ten_seconds = false, long_bubble = false, once = true;
    long size = 1000;
    long copy_size = size, coefficient = 2;
    int max_threshold = 15;
    while (true)
    {     
        int* array = array_generator(size, set);
        float time;
        cout << "\nSize of array = " << size << endl << endl;
        for (int i = 0; i < number_of_sorts; i++)
        {
            if (long_bubble && (i == 0)) continue;
            time = measurement_sort(all_sorts[i], array, size, name_of_sorts[i], name_of_set);
            if (time > 1) is_one_second = true;
            if ((time > 10)&&(i!=0)) are_ten_seconds = true;
            if (time > 10) long_bubble = true;
        }     
        cout << endl;
        for (int j = 5; j < max_threshold; j++)
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
        << name_of_set+name_of_sorts[0] + ".txt\n" << name_of_set+name_of_sorts[1] + ".txt\n"
        << name_of_set+name_of_sorts[2] + ".txt\n" << name_of_set+name_of_sorts[3] + ".txt\n"
        << name_of_set+"Combined sort.txt" << endl;
}
void benchmark_mode_menu()
{
    /*cout << "\nRandom items:" << endl << endl;
    benchmark_mode(array_set::RANDOM, "Random ");*/
    cout << "\nAlmost sorted items in the correct order:" << endl << endl;
    benchmark_mode(array_set::SORTED, "Sorted ");
    cout << "\nAlmost sorted items in the wrong order:" << endl << endl;
    benchmark_mode(array_set::NOTSORTED,"Not sorted ");
}
int main()
{
    while (true)
    {
        cout << "Select the application mode:\n1)Demo mode.\n2)Automatic benchmark mode.\n0)Exit.\n";
        switch (_getch())
        {
        case '1':  test();// demo_mode();
            break;
        case '2': benchmark_mode_menu();
            break;
        case'0':
        {
            cout << "\nExit..." << endl;
            return 0;
        }
        break;
        default: cout << "\nPress the correct key!\n" << endl;
        }
    }
    return 0;
}
