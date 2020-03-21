#include "my_sorts.h"
#include <iostream>
#include <algorithm>
namespace sorting
{  
    void swap(int& a, int& b)
    {
        int temp;
        temp = a;
        a = b;
        b = temp;
    }
    void bubble_sort(int* array, long size)
    {
        std::cout << "\nbuble\n";
        for (long i = 0; i < size; i++)
        {
            for (long j = 0; j < size - i - 1; j++)
            {
                if (array[j] > array[j + 1]) 
                {
                    swap(array[j], array[j + 1]);
                }
            }
        }
    }
    long partition(int* array, long low, long high)
    {
        int pivot = array[high];
        long i = (low - 1);
        for (long j = low; j < high; j++)
        {
            if (array[j] <= pivot)
            {
                i++;
                swap(array[i], array[j]);
            }
        }
        swap(array[i + 1], array[high]);
        return (i + 1);
    }
    void current_quick_sort(int* array, long low, long high)
    {       
        if (low < high)
        {
            long index = partition(array, low, high);
            current_quick_sort(array, low, index - 1);
            current_quick_sort(array, index + 1, high);
        }
    }
    void quick_sort(int* array, long size)
    {
        current_quick_sort(array, 0, size - 1);
    }
    void combined_quick_sort(int* array, long low, long high)
    {
        if (high - low < 11)
        {
            int* temp_array = &array[low];
            bubble_sort(temp_array, high);
            return;
        }
        if (low < high)
        {
            std::cout << "\nquick\n";
            long index = partition(array, low, high);
            combined_quick_sort(array, low, index - 1);
            combined_quick_sort(array, index + 1, high);
        }
    }
    void merge(int* source, int* destination, long begin, long middle, long end) 
    {
        long first = begin, second = middle;
        for (long i = begin; i < end; i++) 
        {
            if ((first < middle) && (second >= end || source[first] <= source[second])) 
            {
                destination[i] = source[first];
                first++;
            }
            else 
            {
                destination[i] = source[second];
                second++;
            }
        }
    }
    void merge_sort_twoarrays(int* source, int* destination, long begin, long end) 
    {
        if (end - begin < 2) return;     
        long middle = (end + begin) / 2;
        merge_sort_twoarrays(destination, source, begin, middle);
        merge_sort_twoarrays(destination, source, middle, end);
        merge(source, destination, begin, middle, end);
    }
    void merge_sort_topdown(int* array, long size) 
    {
        int* destination = new int[size];
        std::copy(array, array + size, destination);
        merge_sort_twoarrays(destination, array, 0, size);
        delete[] destination;
    }
    void library_sort(int* array, long size)
    {
        std::sort(array, array + size);
    }
    void combined_sort(int* array, long size)
    {
        combined_quick_sort(array, 0, size);
    }
}