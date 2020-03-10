#include "lab2b_task_number_twenty.h"
#include "my_correct_read.h"
#include <iostream>
#include <conio.h>
#include <Windows.h>
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
        void clear()
        {
            if (!head) return;
            ListNode* current = head->next;
            head = nullptr;
            for (; current; current = current->next)
            {
                current->prev->next = nullptr;
                delete current->prev;
                current->prev = nullptr;
            }
            delete tail;
            tail = nullptr;
            size = 0;
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
    List union_lists(List& list1, List& list2)
    {
        List new_list;
        for (ListNode* current = list1.head; current; current = current->next)
        {
            new_list.append(current->point);
        }
        for (ListNode* current = list2.head; current; current = current->next)
        {
            if (!list1.is_point(current->point)) new_list.append(current->point);
        }
        return new_list;
    }
    List intersection_lists(List& list1, List& list2)
    {
        List new_list;
        for (ListNode* current = list1.head; current; current = current->next)
        {
            if (list2.is_point(current->point)) new_list.append(current->point);
        }
        return new_list;
    }
    List difference_lists(List& list1, List& list2)
    {
        List new_list;
        for (ListNode* current = list1.head; current; current = current->next)
        {
            if (!list2.is_point(current->point)) new_list.append(current->point);
        }
        return new_list;
    }
    void add_to_end_of_list(List& list)
    {
        Point point;
        point.read_point();
        list.append(point);
        cout << "\nThe point added to set!" << endl;
    }
    void add_to_list_by_index(List& list)
    {
        std::size_t index = correct::read_size_t("the index");
        Point point;
        point.read_point();
        if (list.insert(point, index))
        {
            cout << "\nThe point added to set!" << endl;
        }
    }
    void show_point_by_index(List& list)
    {
        std::size_t index = correct::read_size_t("the index");
        Point point;
        if (list.get(point, index))
        {
            cout << "\nThe point: ";
            point.write_point();
        }
    }
    void delete_point_by_index(List& list)
    {
        std::size_t index = correct::read_size_t("the index");
        if (list.remove(index))
        {
            cout << "\nThe point removed!" << endl;
        }
    }
    void edit_the_list(List& list)
    {        
        while (true)
        {
            cout << "\nSelect the operation:\n1)Adding a point to the end of the set.\n"
                << "2)Inserting a point before a point with the index.\n"
                << "3)Delete a point by index.\n4)Show a point by index.\n"
                << "5)Show all set.\n0)Back." << endl;
            switch (_getch())
            {
            case '1': add_to_end_of_list(list);
                break;
            case '2': add_to_list_by_index(list);
                break;
            case '3': delete_point_by_index(list);
                break;
            case '4': show_point_by_index(list);
                break;
            case '5': list.write_list();
                break;
            case '0':return;
                break;
            default: cout << "\nPress the correct key!" << endl;
            }
        }
    }
    void interactive_dialog_mode()
    {
        List list1, list2;
        while (true)
        {                    
            cout << "\nMenu:\n1)Edit the first set.\n2)Edit the second set.\n"
                << "3)Show the union of the first set and the second set.\n"
                <<"4)Show the intersection of the first set and the second set.\n" 
                << "5)Show the difference of the first set and the second set.\n0)Back." << endl;
            switch (_getch())
            {
            case '1': edit_the_list(list1);
                break;
            case '2': edit_the_list(list2);
                break;
            case '3': 
            {
                cout << "\nThe union:" << endl;
                union_lists(list1, list2).write_list();
            }
                break;
            case '4': 
            {
                cout << "\nThe intersection:" << endl;
                intersection_lists(list1, list2).write_list();
            }
                break;
            case '5': 
            {
                cout << "\nThe difference:" << endl;
                difference_lists(list1, list2).write_list();
            }
                break;
            case '0':
            {
                list1.clear();
                list2.clear();
                return;
            }
                break;
            default: cout << "\nPress the correct key!" << endl;
            }
        }
    }
    void demo_begin(unsigned delay)
    {
        cout << "\nSelect the application mode:\n1)Interactive dialog mode.\n"
            << "2)Demo mode.\n0)Back.\n";
        Sleep(delay);
        cout << "\nSelect the application mode:\n1)Interactive dialog mode. <- press\n"
            << "2)Demo mode.\n0)Back.\n";
        Sleep(delay);
    }
    void demo_union_lists(unsigned delay, List list1, List list2)
    {
        cout << "\nMenu:\n1)Edit the first set.\n2)Edit the second set.\n"
            << "3)Show the union of the first set and the second set. <- press\n"
            << "4)Show the intersection of the first set and the second set.\n"
            << "5)Show the difference of the first set and the second set.\n0)Back." << endl;
        Sleep(delay);
        cout << "\nThe union:" << endl;
        union_lists(list1, list2).write_list();
        Sleep(delay);
    }
    void demo_intersection_lists(unsigned delay, List& list1, List& list2)
    {
        cout << "\nMenu:\n1)Edit the first set.\n2)Edit the second set.\n"
            << "3)Show the union of the first set and the second set.\n"
            << "4)Show the intersection of the first set and the second set. <- press\n"
            << "5)Show the difference of the first set and the second set.\n0)Back." << endl;
        Sleep(delay);
        cout << "\nThe intersection:" << endl;
        intersection_lists(list1, list2).write_list();
        Sleep(delay);
    }  
    void demo_difference_lists(unsigned delay, List& list1, List& list2)
    {
        cout << "\nMenu:\n1)Edit the first set.\n2)Edit the second set.\n"
            << "3)Show the union of the first set and the second set.\n"
            << "4)Show the intersection of the first set and the second set.\n"
            << "5)Show the difference of the first set and the second set. <- press\n0)Back." << endl;
        Sleep(delay);
        cout << "\nThe difference:" << endl;
        difference_lists(list1, list2).write_list();
        Sleep(delay);
    }  
    void demo_write_coordinate(unsigned delay, Point point)
    {
        cout << "\nEnter a point!" << endl;
        cout << "\nEnter the first coordinate: <- write the coordinate and press <Enter>" << endl;
        Sleep(delay);
        cout << "Enter the first coordinate: " << point.x << endl;
        Sleep(delay);
        cout << "\nEnter the second coordinate: <- write the coordinate and press <Enter>" << endl;
        Sleep(delay);
        cout << "Enter the second coordinate: " << point.y << endl;
        Sleep(delay);
        cout << "\nEnter the third coordinate: <- write the coordinate and press <Enter>" << endl;
        Sleep(delay);
        cout << "Enter the third coordinate: " << point.z << endl;
        Sleep(delay);
    }
    void demo_write_index(unsigned delay, std::size_t index)
    {
        cout << "\nEnter the index: <- write the index and press <Enter>" << endl;
        Sleep(delay);
        cout << "Enter the index: " << index << endl;
        Sleep(delay);
    }
    void demo_add_to_end(unsigned delay, List& list, Point point)
    {
        cout << "\nSelect the operation:\n1)Adding a point to the end of the set. <- press\n"
            << "2)Inserting a point before a point with the index.\n"
            << "3)Delete a point by index.\n4)Show a point by index.\n"
            << "5)Show all set.\n0)Back." << endl;
        Sleep(delay);
        demo_write_coordinate(delay, point);
        list.append(point);
        cout << "\nThe point added to set!" << endl;
        Sleep(delay);
    }
    void demo_add_to_list_by_index(unsigned delay, List& list, Point point, std::size_t index)
    {
        cout << "\nSelect the operation:\n1)Adding a point to the end of the set.\n"
            << "2)Inserting a point before a point with the index. <- press\n"
            << "3)Delete a point by index.\n4)Show a point by index.\n"
            << "5)Show all set.\n0)Back." << endl;
        Sleep(delay);
        demo_write_index(delay, index);
        demo_write_coordinate(delay, point);
        if (list.insert(point, index)) cout << "\nThe point added to set!" << endl;
        Sleep(delay);
    }
    void demo_show_point_by_index(unsigned delay, List& list, std::size_t index)
    {
        cout << "\nSelect the operation:\n1)Adding a point to the end of the set.\n"
            << "2)Inserting a point before a point with the index.\n"
            << "3)Delete a point by index.\n4)Show a point by index. <- press\n"
            << "5)Show all set.\n0)Back." << endl;
        Sleep(delay);
        demo_write_index(delay, index);
        Point point;
        if (list.get(point, index))
        {
            cout << "The point: ";
            point.write_point();
        }
        Sleep(delay);
    }    
    void demo_delete_point_by_index(unsigned delay, List& list, std::size_t index)
    {
        cout << "\nSelect the operation:\n1)Adding a point to the end of the set.\n"
            << "2)Inserting a point before a point with the index.\n"
            << "3)Delete a point by index. <- press\n4)Show a point by index.\n"
            << "5)Show all set.\n0)Back." << endl;
        Sleep(delay);
        demo_write_index(delay, index);
        if (list.remove(index))  cout << "\nThe point removed!" << endl;
        Sleep(delay);
    }
    void demo_write_list(unsigned delay, List& list)
    {
        cout << "\nSelect the operation:\n1)Adding a point to the end of the set.\n"
            << "2)Inserting a point before a point with the index.\n"
            << "3)Delete a point by index.\n4)Show a point by index.\n"
            << "5)Show all set. <- press\n0)Back." << endl;
        Sleep(delay);
        list.write_list();
        Sleep(delay);
    }
    void demo_back(unsigned delay)
    {
        cout << "\nSelect the operation:\n1)Adding a point to the end of the set.\n"
            << "2)Inserting a point before a point with the index.\n"
            << "3)Delete a point by index.\n4)Show a point by index.\n"
            << "5)Show all set.\n0)Back. <- press" << endl;
        Sleep(delay);
    }
    void demo_menu_back(unsigned delay, List& list1, List& list2)
    {
        cout << "\nMenu:\n1)Edit the first set.\n2)Edit the second set.\n"
            << "3)Show the union of the first set and the second set.\n"
            << "4)Show the intersection of the first set and the second set.\n"
            << "5)Show the difference of the first set and the second set.\n0)Back. <- press" << endl;
        list1.clear();
        list2.clear();
        Sleep(delay);
    }  
    void demo_edit_first_list(unsigned delay, List& list)
    {
        cout << "\nMenu:\n1)Edit the first set. <- press\n2)Edit the second set.\n"
            << "3)Show the union of the first set and the second set.\n"
            << "4)Show the intersection of the first set and the second set.\n"
            << "5)Show the difference of the first set and the second set.\n0)Back." << endl;
        Sleep(delay);
        demo_add_to_end(delay, list, Point(-9.2, 3, 11));
        demo_add_to_end(delay, list, Point(0, -1.2, 4));
        demo_write_list(delay, list);
        demo_add_to_list_by_index(delay, list, Point(3, 7, 1.6), 0);
        demo_show_point_by_index(delay, list, 0);
        demo_add_to_list_by_index(delay, list, Point(-4, -5, -10), 1);
        demo_show_point_by_index(delay, list, 1);
        demo_delete_point_by_index(delay, list, 0);
        demo_add_to_end(delay, list, Point(13, 0.1, 6.4));
        demo_add_to_end(delay, list, Point(1, 4, 2));
        demo_add_to_end(delay, list, Point(-8, 11, 2.3));
        demo_write_list(delay, list);
        demo_back(delay);
    }
    void demo_edit_second_list(unsigned delay, List& list)
    {
        cout << "\nMenu:\n1)Edit the first set.\n2)Edit the second set. <- press\n"
            << "3)Show the union of the first set and the second set.\n"
            << "4)Show the intersection of the first set and the second set.\n"
            << "5)Show the difference of the first set and the second set.\n0)Back." << endl;
        Sleep(delay);
        demo_add_to_end(delay, list, Point(1, 4, 2));
        demo_add_to_end(delay, list, Point(2, -7, 11));
        demo_write_list(delay, list);
        demo_add_to_list_by_index(delay, list, Point(3.3, 17, 4.6), 0);
        demo_show_point_by_index(delay, list, 0);
        demo_add_to_list_by_index(delay, list, Point(-4, -5, -10), 1);
        demo_show_point_by_index(delay, list, 1);
        demo_delete_point_by_index(delay, list, 0);
        demo_add_to_end(delay, list, Point(0.2, 0.2, 0.2));
        demo_add_to_end(delay, list, Point(-8, 11, 2.3));
        demo_write_list(delay, list);
        demo_back(delay);
    }
    void demo_mode()
    {
        unsigned delay = 1900;
        delay = correct::read_unsigned("a delay to display data(in milliseconds; normal = 1900)");
        List list1,list2;
        cout << "\nThe start of the demo mode(press <Ctrl + C> to exit)" << endl;
        Sleep(delay);
        demo_begin(delay);
        demo_edit_first_list(delay, list1);
        demo_edit_second_list(delay, list2);
        demo_union_lists(delay, list1, list2);
        demo_intersection_lists(delay, list1, list2);
        demo_difference_lists(delay, list1, list2);
        demo_menu_back(delay, list1, list2);
        cout << "\nThe end of the demo mode" << endl;
        Sleep(delay);
    }
    void menu()
	{
        while (true)
        {
            cout << "\nSelect the application mode:\n1)Interactive dialog mode.\n"
                << "2)Demo mode.\n0)Back.\n";
            switch (_getch())
            {
            case '1': interactive_dialog_mode();
                break;
            case '2': demo_mode();
                break;
            case'0':
            {
                cout << endl;
                return;
            }
            break;
            default: cout << "\nPress the correct key!" << endl;
            }
        }
	}
}