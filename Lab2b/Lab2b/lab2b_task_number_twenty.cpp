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
        ListNode* prev;
        ListNode(): point(Point(0,0,0)), prev(nullptr), next(nullptr){}
        ListNode(Point point, ListNode* prev, ListNode* next) : point(point), prev(prev), next(next) {}
    };
    struct List
    {
    private:      
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
            ListNode* new_node = new ListNode(point, nullptr, head);
            head->prev = new_node;
            head = new_node;
        }
        void add_to_middle(Point point, std::size_t index)
        {
            ListNode* current = head;
            for (std::size_t i = 0; i < size;i++)
            {
                if (index == (i + 1))
                {
                    ListNode* new_node = new ListNode(point,current, current->next);
                    current->next->prev = new_node;
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
                current->next->prev = nullptr;
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
                if (index == i)
                {
                    current->prev->next = current->next;
                    current->next->prev = current->prev;
                    delete current;
                    return;
                }
                i++;
            }
        }
        void delete_tail()
        {
            ListNode* current = tail;
            tail = current->prev;
            current->prev->next = nullptr;
            delete current;
        }
    public:
        ListNode* head;
        List(): head(nullptr), tail(nullptr), size(0) {}
        void append(Point point)
        {
            if (is_point(point)) return;
            ListNode* new_node;
            size++;
            if (tail)
            {           
                new_node = new ListNode(point,tail, nullptr);
                tail->next = new_node;
                tail = new_node;
                return;
            }
            new_node = new ListNode(point, nullptr, nullptr);
            tail = new_node;
            head = new_node;
            return;
        }
        bool insert(Point point, std::size_t index)
        {          
            if (!is_index(index)) return false;
            if (is_point(point)) return true;
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
        bool remove(std::size_t index)
        {
            if (!is_index(index)) return false;           
            if (index == 0)
            {
                delete_head();
                size--;
                return true;
            }
            if ((index + 1) == size)
            {
                delete_tail();
                size--;
                return true;
            }
            delete_middle(index);
            size--;
            return true;
        }
        bool is_point(Point point)
        {
            for (ListNode* current = head; current; current = current->next)
            {
                if ((point.x == current->point.x) && (point.y == current->point.y) && (point.z == current->point.z))
                {                   
                    return true;
                }
            }
            return false;
        }
    };
    List union_lists(List& list1, List& list2) // це перетнин!!!
    {
        List new_list;
        for (ListNode* current = list1.head; current; current = current->next)
        {
            if (list2.is_point(current->point)) new_list.append(current->point);
        }
        return new_list;
    }
    List intersections(List& list1, List& list2)
    {

    }
    void menu()
	{
        List list1;
        list1.append(Point(0, 0, 0));
        list1.append(Point(-1, -1, -1));
        list1.append(Point(2, 3, 2));
        cout << "\nFirst list: " << endl;
        list1.write_list();
        List list2;
        list2.append(Point(0, 0, 0));
        list2.append(Point(1, 1, 1));
        list2.append(Point(2, 2, 2));
        cout << "\nSecond list: " << endl;
        list2.write_list();
        List new_list = union_lists(list1, list2);
        cout << "\nUnion list: " << endl;
        new_list.write_list();
	}
}