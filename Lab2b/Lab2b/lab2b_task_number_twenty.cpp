#include "lab2b_task_number_twenty.h"
#include "my_correct_read.h"
#include <iostream>
using std::cout;
using std::cin;
using std::endl;
namespace twenty
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
        Point point;
        ListNode* next;
        ListNode(): point(Point(0,0,0)), next(nullptr){}
        ListNode(Point point, ListNode* next) : point(point), next(next) {}
    };
    struct List
    {
    private:
        ListNode* head;
        ListNode* tail;
        std::size_t size;
        bool is_index(std::size_t index)
        {
            if (index + 1 > size)
            {
                cout << "\nThere isn`t a point with the index!" << endl;
                return false;
            }
            return true;
        }
        void add_to_head(Point point)
        {
            ListNode* new_node = new ListNode(point, head);
            head = new_node;
        }
        void add_to_middle(Point point, std::size_t index)
        {
            ListNode* current = head;
            for (std::size_t i = 0; i < size;i++)
            {
                if (index == (i + 1))
                {
                    ListNode* new_node = new ListNode(point, current->next);
                    current->next = new_node;
                    return;
                }
                current = current->next;
            }
        }
        void delete_head()
        {
            if (head->next)
            {
                ListNode* current = head;
                head = current->next;
                delete current;
                return;
            }
            if (head)
            {
                tail = nullptr;
                delete head;
                head = nullptr;
            }           
        }
        void delete_middle(std::size_t index)
        {
            std::size_t i = 0;
            for (ListNode* current = head; current; current = current->next)
            {
                if (index == (i + 1))
                {
                    ListNode* temp_node = current->next;
                    current->next = current->next->next;
                    delete temp_node;
                    return;
                }
                i++;
            }
        }
        void delete_tail()
        {
            for (ListNode* current = head; current; current = current->next)
            {
                if (!current->next->next)
                {
                    tail = current;
                    delete current->next;
                    return;
                }
            }
        }
    public:
        List(): head(nullptr), tail(nullptr), size(0) {}
        void append(Point point)
        {
            ListNode* new_node = new ListNode(point, nullptr);
            size++;
            if (tail)
            {              
                tail->next = new_node;
                tail = new_node;
                return;
            }
            tail = new_node;
            head = new_node;
            return;
        }
        bool insert(Point point, std::size_t index)
        {
            if (!is_index(index)) return false;
            size++;
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
            cout << "\nSize: " << size << endl;
            std::size_t i = 0;
            for (ListNode* current = head; current; current = current->next)
            {
                cout << "Point[" << i++ << "]: ";
                current->point.write_point();
            }
        }
        bool get(Point& point, std::size_t index)
        {
            if (!is_index(index)) return false;
            std::size_t i = 0;
            for (ListNode* current = head; current; current = current->next)
            {
                if (index == i)
                {
                    point = current->point;
                    return true;
                }
                i++;
            }
            return false;
        }
        bool set(Point point, std::size_t index)
        {
            if (!is_index(index)) return false;
            std::size_t i = 0;
            for (ListNode* current = head; current; current = current->next)
            {
                if (index == i)
                {
                    current->point = point;
                    return true;
                }
                i++;
            }
            return false;
        }
        bool remove(std::size_t index)
        {
            if (!is_index(index)) return false;
            size--;
            if (index == 0)
            {
                delete_head();
                return true;
            }
            if ((index + 1) == size)
            {
                delete_tail();
                return true;
            }
            delete_middle(index);
            return true;
        }
    };
    void menu()
	{
        List list;
        list.append(Point(0, 3, 1));
        list.append(Point(1, 3, 1));
        list.append(Point(2, 3, 1));
        list.insert(Point(3, 3, 1),0);
        list.insert(Point(4, 3, 1),3);
        list.write_list();
        list.remove(4);
        list.remove(3);
        list.remove(1);
        list.write_list();
	}
}