#include "lab2b_task_number_twenty_six.h"
#include "my_correct_read.h"
#include <iostream>
using std::cout;
using std::cin;
using std::endl;
namespace twenty_six
{
    struct Point
    {
        double x;
        double y;
        double z;
        Point()
        {
            x = 0;
            y = 0;
            z = 0;
        }
        Point(double x, double y, double z)
        {
            this->x = x;
            this->y = y;
            this->z = z;
        }
        bool is_zero()
        {
            if ((x * x + y * y + z * z) == 0) return true;
            return false;
        }
        void read_point()
        {
            cout << "\nEnter a point!" << endl;
            this->x = correct::read_double("the first coordinate");
            this->y = correct::read_double("the second coordinate");
            this->z = correct::read_double("the third coordinate");
        }
        void write_point()
        {
            cout << "x = " << x << "; y = " << y
                << "; z = " << z << ";" << endl;
        }
    };
    struct ListNode
    {
        ListNode* prev;
        ListNode* next;
        std::size_t arr_size;
        std::size_t max_size;
        Point* points;
        ListNode()
        {
            max_size = 6;
            arr_size = 0;
            prev = nullptr;
            next = nullptr;
            points = nullptr;
        }
        ListNode(ListNode* prev, ListNode* next, Point point)
        {
            max_size = 6;
            arr_size = 1;
            this->prev = prev;
            this->next = next;
            points = new Point[max_size];
            points[0] = point;
        }
    };
    struct List
    {
        ListNode* head;
        ListNode* tail;
        std::size_t size;
        bool is_index(std::size_t index)
        {
            if ((index + 1) > size)
            {
                cout << "\nThere isn`t points wiht the index!" << endl;
                return false;
            }
            return true;
        }
        List() : head(nullptr), tail(nullptr), size(0){}
        void append(Point point)
        {
            size++;
            if (tail)
            {
                if (tail->arr_size < (tail->max_size / 2))
                {
                    tail->points[tail->arr_size++] = point;
                    return;
                }
                ListNode* new_node = new ListNode(tail, nullptr, point);
                tail->next = new_node;
                tail = new_node;
                return;
            }
            ListNode* new_node = new ListNode(nullptr, nullptr, point);
            tail = new_node;
            head = new_node;
        }
        void add_to_head(Point point)
        {
            ListNode* current = head;
            head = current;
            size++;
            if (current->arr_size < current->max_size)
            {                
                for (std::size_t i = current->arr_size; i > 0; i--)
                {
                    current->points[i] = current->points[i - 1];
                }
                current->points[0] = point;
                current->arr_size++;
            }
            else
            {
                std::size_t j = current->max_size / 2;
                ListNode* new_node = new ListNode(current, current->next, current->points[j++]);
                current->next->prev = new_node;
                current->next = new_node;
                new_node->arr_size = current->max_size / 2;
                for (std::size_t k = 1; j < current->max_size; j++, k++)
                {
                    new_node->points[k] = current->points[j];
                }              
                for (std::size_t i = current->max_size / 2; i > 0; i--)
                {
                    current->points[i] = current->points[i - 1];
                }
                current->points[0] = point;
                current->arr_size = current->max_size / 2 + 1;                
            }
        }
        void add_to_middle(Point point, std::size_t index)
        {
            size++;
            std::size_t current_size = 0;
            for (ListNode* current = head; current; current = current->next)
            {
                
                if (index < current_size)
                {
                    std::size_t new_index = index - current_size;
                    if (current->arr_size < current->max_size)
                    {                       
                        for (std::size_t i = current->arr_size; i > new_index; i--)
                        {
                            current->points[i] = current->points[i - 1];
                        }
                        current->points[new_index] = point;
                        current->arr_size++;
                        return;
                    }
                    else
                    {
                        std::size_t j = current->max_size / 2;
                        if (new_index < j)
                        {
                            current->arr_size = j;
                            for (std::size_t i = j; i > new_index; i--)
                            {
                                current->points[i] = current->points[i - 1];
                            }
                            current->points[new_index] = point;
                            current->arr_size++;
                            ListNode* new_node = new ListNode(current, current->next, current->points[j++]);
                            current->next->prev = new_node;
                            current->next = new_node;
                            new_node->arr_size = current->max_size / 2;
                            for (std::size_t k = 1; j < current->max_size; j++, k++)
                            {
                                new_node->points[k] = current->points[j];
                            }  
                            return;
                        }
                        else
                        {
                            current->arr_size = j;
                            ListNode* new_node = new ListNode(current, current->next, Point());
                            current->next->prev = new_node;
                            current->next = new_node;
                            new_node->arr_size = j + 1;
                            std::size_t k = 0;
                            for (; j < new_index; j++, k++)
                            {
                                new_node->points[k] = current->points[j];
                            }
                            new_node->points[k++] = point;
                            for (; j < new_node->max_size; j++, k++)
                            {
                                new_node->points[k] = current->points[j];
                            }
                            return;
                        }
                    }
                }
                current_size += current->arr_size;
            }
        }
        bool insert(Point point, std::size_t index)
        {
            if (!is_index(index)) return false;
            if ((index + 1) == size)
            {
                append(point);
                return true;
            }
            if (index == 0)
            {
                add_to_head(point);
                return true;
            }
            add_to_middle(point, index);
            return true;            
        }
        void write_list()
        {
            cout << "\nSize: " << size;
            std::size_t j = 0;
            for (ListNode* current = head; current; current = current->next)
            {      
                for (std::size_t i = 0; i < current->arr_size; i++)
                {
                    cout << "\nPoint[" << j++ << "]: ";
                    current->points[i].write_point();
                }
            }
        }
    };
    void write()
	{
        List list;
        int i = 0;        
        list.append(Point(1, 1, 1));   
        list.append(Point(2, 2, 2));
        list.append(Point(3, 3, 3));
        list.write_list();
        list.insert(Point(7, 7, 7), 3);
        list.insert(Point(7, 7, 7), 0);
        list.insert(Point(7, 7, 7), 2);
        list.write_list();
	}
}