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

struct measurement_result
{
    long size;
    float time;
};
int* array_generator(long size)
{
    int max_value = 30000;
    int* array = new int[size];
    srand(time(0));
    for (long i = 0; i < size; i++)
    {
        array[i] = rand() % max_value;
    }
    return array;
}
int* array_set(long size)
{
    int* array = new int[size];
    for (long i = 0; i < size; i++)
    {
        array[i] = size - i;
    }
    return array;
}
void write_array(int* array, long size)
{
    for (long i = 0; i < size; i++)
    {
        cout << "Array[" << i << "] = " << array[i] << endl;
    }
}
void test()
{
    long size;
    cout << "Enter size:";
    cin >> size;
    int* array = array_generator(size);
    array[size / 2] = 31000;
    write_array(array, size);
    //sorting::combined_sort(array, size);
    //sorting::quick_sort(array, size);
    //sorting::merge_sort_topdown(array, size);
    //sorting::library_sort(array, size);
    //sorting::bubble_sort(array, size);
    cout << "Sort:" << endl;
    write_array(array, size);
    delete[] array;
}
void demo_mode()
{
   
}
template<class T>
void add_to_end_of_file(T& value, const std::string& name_of_value,const std::string& path)
{
    std::ofstream file(path + ".txt", std::ios_base::app);
    file << name_of_value << " = " << value << "." << endl;
    file.close();
}
void add_result_to_file()
{

}
float measurement_sort(void sort(int*, long), int* array, long size, const std::string& name_of_sort)
{
    int* copy_array = new int[size];
    std::copy(array, array + size, copy_array);
    auto the_start = std::chrono::high_resolution_clock::now();
    auto the_end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> duration;
    the_start = std::chrono::high_resolution_clock::now();
    sort(copy_array, size);
    the_end = std::chrono::high_resolution_clock::now();
    duration = the_end - the_start;
    cout << "Time of " << name_of_sort << " = " << duration.count() << endl;
    delete[] copy_array;
    return duration.count();
}
float measurement_combined(int* array, long size, const int threshold)
{
    int* copy_array = new int[size];
    std::copy(array, array + size, copy_array);
    auto the_start = std::chrono::high_resolution_clock::now();
    auto the_end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> duration;
    the_start = std::chrono::high_resolution_clock::now();
    sorting::combined_sort(copy_array, size, threshold);
    the_end = std::chrono::high_resolution_clock::now();
    duration = the_end - the_start;
    cout << "Time of Combined sort = " << duration.count() << endl;
    cout << "Threshold of Combined sort = " << threshold << endl;
    delete[] copy_array;
    return duration.count(); 
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
void benchmark_mode()
{
    const int number_of_sorts = 4;
    void(*all_sorts[number_of_sorts])(int*, long) = { sorting::bubble_sort, sorting::quick_sort,
    sorting::merge_sort_topdown, sorting::library_sort };
    std::string name_of_sorts[number_of_sorts] = { "Bubble sort", "Quick sort", "Merge sort topdown", "Library sort" };
    bool is_one_second = false, are_ten_seconds = false;
    long size = 1000;
    long copy_size = size, coefficient = 2;
    int threshold = 0;
    while (true)
    {     
        int* array = array_generator(size);
        float time;
        cout << "\nSize of array = " << size << endl;
        for (int i = 0; i < number_of_sorts; i++)
        {
            time = measurement_sort(all_sorts[i], array, size, name_of_sorts[i]);           
            if (time > 1) is_one_second = true;
            if (time > 100) are_ten_seconds = true;
        }
        time = measurement_combined(array, size, threshold++);
        if (time > 1) is_one_second = true;
        if (time > 100) are_ten_seconds = true;
        if (are_ten_seconds) break;
        size = set_size(is_one_second, copy_size, coefficient);
        delete[] array;
        array = nullptr;
    } 
}
int main()
{
    while (true)
    {
        cout << "Select the application mode:\n1)Demo mode.\n2)Automatic benchmark mode.\n0)Exit.\n";
        switch (_getch())
        {
        case '1':  test();//demo_mode();
            break;
        case '2': benchmark_mode();
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
