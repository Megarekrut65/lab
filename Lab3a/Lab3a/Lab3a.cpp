#include <iostream>
#include <conio.h>
#include <ctime>
#include <chrono>
#include "my_sorts.h"

using std::cout;
using std::cin;
using std::endl;

int* array_generator(long size)
{
    int max_value = 100;
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
    write_array(array, size);
    sorting::combined_sort(array, size);
    cout << "Sort:" << endl;
    write_array(array, size);
    delete[] array;
}
void demo_mode()
{

}
void benchmark_mode()
{
    auto the_start = std::chrono::high_resolution_clock::now();
    auto the_end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> duration;
    long size = 40000000;
    cout << "here : " << size << endl;
    int* array = array_generator(size);
    the_start = std::chrono::high_resolution_clock::now();
    sorting::library_sort(array, size);
    the_end = std::chrono::high_resolution_clock::now();
    duration = the_end - the_start;
    cout << "time: " << duration.count() << endl;
    delete[] array;
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
