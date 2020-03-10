#include "lab2b_task_number_twelve.h"
#include "my_correct_read.h"
#include <iostream>
#include <conio.h>
#include <Windows.h>
using std::cout;
using std::cin;
using std::endl;
namespace twelve
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
            if ((x*x + y*y + z*z) == 0) return true;
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
	struct SparseListNode
	{
        Point point;
		std::size_t index;
		SparseListNode* next;
		SparseListNode(Point point, std::size_t index, SparseListNode* next) :
			point(point), index(index), next(next) {}
	};
	struct SparseList
	{
    private:
		std::size_t size;
		SparseListNode* head;
        bool is_index(std::size_t index)
        {
            if ((index + 1) > size)
            {
                cout << "\nThere isn`t point with the index!" << endl;
                return false;
            }
            return true;
        }
        void minus_indexes(std::size_t index)
        {
            for (SparseListNode* current_node = head; current_node; current_node = current_node->next)
            {
                if (index < current_node->index) current_node->index--;
            }
        }
        void plus_indexes(std::size_t index)
        {
            for (SparseListNode* current_node = head; current_node; current_node = current_node->next)
            {
                if (index < current_node->index) current_node->index++;
            }
        }
    public:
		SparseList() : size(0), head(nullptr) {}
        void write_list()
        {
            cout << "\nOverall size:" << size << endl;
            for (SparseListNode* current = head; current; current = current->next)
            {
                cout << "Point[" << current->index << "]: ";
                current->point.write_point();           
            }
        }
        bool insert(Point point, std::size_t index)
        {           
            SparseListNode* current = head;
            SparseListNode* new_node;    
            if ((!current)||(index < current->index))
            {
                if (!point.is_zero())
                {
                    new_node = new SparseListNode(point, index, current);
                    head = new_node;
                }     
                size = (index + 1) > size ? (index + 1) : size;
                return true;
            }           
            for (; current; current = current->next)
            {
                if (index == current->index)
                {                   
                    return false;
                }
                if ((!current->next)||(index < current->next->index))
                {
                    if (!point.is_zero())
                    {
                        new_node = new SparseListNode(point, index, current->next);
                        current->next = new_node;
                    }
                    size = (index + 1) > size ? (index + 1) : size;
                    return true;
                }
            }
            return false;
        }
        bool get(Point& point, std::size_t index)
        {
            if (!is_index(index)) return false;            
            for (SparseListNode* current = head; current; current = current->next)
            {
                if (index == current->index)
                {
                    point = current->point;
                    return true;
                }
            }
            point = Point(0, 0, 0);
            return true;
        }
        bool set(Point point, std::size_t index)
        {
            if (!is_index(index)) return false;
            for (SparseListNode* current = head; current; current = current->next)
            {
                if (index == current->index)
                {
                    current->point = point;
                    if (point.is_zero())
                    {
                        bool temp = remove(index);
                        size++;
                        plus_indexes(index - 1);
                    }
                    return true;
                }
            }
            bool temp = insert(point, index);
            return true;
        }        
        bool remove(std::size_t index)
        {
            if (!is_index(index)) return false;
            size--;
            if (!head) return true;                      
            SparseListNode* current = head;
            if (index == current->index)
            {
                head = current->next;
                delete current;
                minus_indexes(index);
                return true;
            }
            for (; current; current = current->next)
            {
                if (!current->next)
                {
                    minus_indexes(index);
                    return true;
                }
                if (index == current->next->index)
                {
                    SparseListNode* temp_node = current->next;
                    current->next = temp_node->next;
                    delete temp_node;
                    minus_indexes(index);
                    return true;
                }
            } 
            return false;
        }
        void clear()
        {
            SparseListNode* current = head;
            head = nullptr;
            while(current)
            {
                SparseListNode* temp_node = current;
                current = current->next;
                delete temp_node;
                temp_node = nullptr;             
            }
            size = 0;
        }
	};
    void add_to_list_by_index(SparseList& list)
    {
        Point point;
        std::size_t index = correct::read_size_t("the index");
        point.read_point();
        if (list.insert(point, index))
        {
            cout << "\nThe point added to list!" << endl;
        }
        else
        {
            cout << "\nThe Point with the index has already created!" << endl;
        }
    }
    void show_point_by_index(SparseList& list)
    {
        Point point;
        std::size_t index = correct::read_size_t("the index");
        if (list.get(point, index))
        {
            cout << "The point: ";
            point.write_point();
        }
    }
    void edit_point_by_index(SparseList& list)
    {
        std::size_t index = correct::read_size_t("the index");
        Point point;
        point.read_point();       
        if (list.set(point, index))
        {
            cout << "\nThe point edited!" << endl;
        }
    }
    void delete_point_by_index(SparseList& list)
    {
        std::size_t index = correct::read_size_t("the index");
        if (list.remove(index))
        {
            cout << "\nThe point removed!" << endl;
        }
    }
    void interactive_dialog_mode()
    {
        SparseList list;
        while (true)
        {
            cout << "\nMenu:\n1)Inserting a point by index.\n"
                << "2)Show a point by index.\n3)Edit a point by index.\n"
                << "4)Delete a point by index.\n5)Show all non-zero points.\n0)Back." << endl;
            switch (_getch())
            {
            case '1': add_to_list_by_index(list);
                break;
            case '2': show_point_by_index(list);
                break;
            case '3': edit_point_by_index(list);
                break;
            case '4': delete_point_by_index(list);
                break;
            case '5': list.write_list();
                break;
            case '0':
            {
                list.clear();
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
    void demo_add_to_list_by_index(unsigned delay, SparseList& list, Point point, std::size_t index)
    {
        cout << "\nMenu:\n1)Inserting a point by index. <- press\n"
            << "2)Show a point by index.\n3)Edit a point by index.\n"
            << "4)Delete a point by index.\n5)Show all non-zero points.\n0)Back." << endl;
        Sleep(delay);
        demo_write_index(delay, index);
        demo_write_coordinate(delay, point);
        if(list.insert(point, index)) cout << "\nThe point added to list!" << endl;
        else cout << "\nThe Point with the index has already created!" << endl;
        Sleep(delay);
    }
    void demo_show_point_by_index(unsigned delay, SparseList& list, std::size_t index)
    {
        cout << "\nMenu:\n1)Inserting a point by index.\n"
            << "2)Show a point by index. <- press\n3)Edit a point by index.\n"
            << "4)Delete a point by index.\n5)Show all non-zero points.\n0)Back." << endl;
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
    void demo_edit_point_by_index(unsigned delay, SparseList& list, Point point, std::size_t index)
    {
        cout << "\nMenu:\n1)Inserting a point by index.\n"
            << "2)Show a point by index.\n3)Edit a point by index. <- press\n"
            << "4)Delete a point by index.\n5)Show all non-zero points.\n0)Back." << endl;
        Sleep(delay);
        demo_write_index(delay, index);
        demo_write_coordinate(delay, point);
        if (list.set(point, index))  cout << "\nThe point edited!" << endl;
        Sleep(delay);
    }
    void demo_delete_point_by_index(unsigned delay, SparseList& list, std::size_t index)
    {
        cout << "\nMenu:\n1)Inserting a point by index.\n"
            << "2)Show a point by index.\n3)Edit a point by index.\n"
            << "4)Delete a point by index. <- press\n5)Show all non-zero points.\n0)Back." << endl;
        Sleep(delay);
        demo_write_index(delay, index);
        if (list.remove(index))  cout << "\nThe point removed!" << endl;
        Sleep(delay);
    }
    void demo_write_list(unsigned delay, SparseList& list)
    {
        cout << "\nMenu:\n1)Inserting a point by index.\n"
            << "2)Show a point by index.\n3)Edit a point by index.\n"
            << "4)Delete a point by index.\n5)Show all non-zero points. <- press\n0)Back." << endl;
        Sleep(delay);
        list.write_list();
        Sleep(delay);
    }
    void demo_back(unsigned delay, SparseList& list)
    {
        cout << "\nMenu:\n1)Inserting a point by index.\n"
            << "2)Show a point by index.\n3)Edit a point by index.\n"
            << "4)Delete a point by index.\n5)Show all non-zero points.\n0)Back. <- press" << endl;
        list.clear();
        Sleep(delay);
    }
    void demo_mode()
    {
        unsigned delay = 1900;
        delay = correct::read_unsigned("a delay to display data(in milliseconds; normal = 1900)");
        SparseList list;
        cout << "\nThe start of the demo mode(press <Ctrl + C> to exit)" << endl;
        Sleep(delay);
        demo_begin(delay);
        demo_add_to_list_by_index(delay, list, Point(1.2, 4.1, 10), 10);
        demo_add_to_list_by_index(delay, list, Point(0, 0, 0), 15);
        demo_add_to_list_by_index(delay, list, Point(3, 2, 6), 5);
        demo_write_list(delay, list);
        demo_edit_point_by_index(delay, list, Point(11, 12, 13), 5);
        demo_show_point_by_index(delay, list, 5);
        demo_edit_point_by_index(delay, list, Point(2, 7, 14), 0);
        demo_edit_point_by_index(delay, list, Point(0, 0, 0), 10);
        demo_write_list(delay, list);
        demo_delete_point_by_index(delay, list, 0);
        demo_delete_point_by_index(delay, list, 9);
        demo_write_list(delay, list);
        demo_back(delay,list);
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
