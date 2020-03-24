#include "my_sorts.h"
#include <iostream>
#include <algorithm>
namespace sorting
{    
    void write_array(int* array, long size)
    {
        std::cout << "Array: ";
        for (long i = 0; i < size; i++)
        {
            std::cout << array[i] << " ";
        }
        std::cout << std::endl;
    }
    void audit_step(int* array, long size, long frequency, long& step)
    {
        step++;      
        if ((frequency == 0) || (frequency == -1) || (step % frequency != 0)) return;
        step = 0;  
        write_array(array, size);
    }
    void swap(int& a, int& b)
    {
        int temp;
        temp = a;
        a = b;
        b = temp;
    }
    void current_bubble_sort(int* array, long end, long size, long frequency, long& step)
    {
        for (long i = 0; i < end; i++)
        {
            for (long j = 0; j < end - i - 1; j++)
            {
                if (array[j] > array[j + 1])
                {
                    swap(array[j], array[j + 1]);
                    audit_step(array, size, frequency, step);
                }
            }
        }
    }
    void bubble_sort(int* array, long size, long frequency)
    {
        long step = 0;
        current_bubble_sort(array, size, size, frequency, step);
        if (frequency != 0)
        {
            write_array(array, size);
        }
    }   
    long partition(int* array, long low, long high, long size, int frequency, long& step)
    {
        int pivot = array[high];
        long i = low - 1;
        for (long j = low; j < high; j++)
        {
            if (array[j] <= pivot)
            {
                i++;
                swap(array[i], array[j]);
                audit_step(array, size, frequency, step);
            }
        }
        swap(array[i + 1], array[high]);
        audit_step(array, size, frequency, step);
        return (i + 1);
    }
    void current_quick_sort(int* array, long low, long high, long size, long frequency, long& step)
    {
        if (low < high)
        {
            long index = partition(array, low, high, size, frequency, step);
            current_quick_sort(array, low, index - 1, size, frequency, step);
            current_quick_sort(array, index + 1, high, size, frequency, step);
        }
    }
    void quick_sort(int* array, long size, long frequency)
    {
        long step = 0;
        current_quick_sort(array, 0, size - 1, size, frequency, step);
        if (frequency != 0)
        {
            write_array(array, size);
        }
    }
    void merge_sort(int* source, int* destination, long begin, long middle, long end, long size, long frequency, long& step)
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
            audit_step(destination, size, frequency,step);
        }
    }
    void merge_sort_twoarrays(int* source, int* destination, long begin, long end, long size, long frequency, long& step)
    {
        if (end - begin < 2) return;
        long middle = (end + begin) / 2;
        merge_sort_twoarrays(destination, source, begin, middle, size, frequency, step);
        merge_sort_twoarrays(destination, source, middle, end, size, frequency, step);
        merge_sort(source, destination, begin, middle, end, size, frequency, step);
    }
    void merge_sort_topdown(int* array, long size, long frequency)
    {
        long step = 0;
        int* destination = new int[size];
        std::copy(array, array + size, destination);
        merge_sort_twoarrays(destination, array, 0, size, size, frequency, step);
        delete[] destination;
        if (frequency != 0)
        {
            write_array(array,size);
        }
    }
    void library_sort(int* array, long size, long frequency)
    {
        std::sort(array, array + size);
        if (frequency != 0)
        {
            write_array(array,size);
        }
    }
    void combined_quick_bubble_sort(int* array, long low, long high, int threshold, long size, long frequency, long& step)
    {
        if (low < high)
        {
            if (high - low < threshold)
            {
                int* temp_array = &array[low];
                current_bubble_sort(temp_array, high - low + 1,size, frequency, step);
                temp_array = nullptr;
                return;
            }
            long index = partition(array, low, high, size, frequency, step);
            combined_quick_bubble_sort(array, low, index - 1, threshold, size, frequency, step);
            combined_quick_bubble_sort(array, index + 1, high, threshold, size, frequency, step);
        }
    }
    void combined_sort(int* array, long size, int threshold, long frequency)
    {
        long step = 0;
        combined_quick_bubble_sort(array, 0, size - 1, threshold, size, frequency, step);
        if (frequency != 0)
        {
            write_array(array, size);
        }
    }
   
}