#include "lab2b_task_number_twenty_six.h"
#include "my_correct_read.h"
#include <iostream>
#include <conio.h>
#include <Windows.h>
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
    private:
        ListNode* head;
        ListNode* tail;
        std::size_t size;
        bool is_index(std::size_t index)
        {
            if ((index + 1) > size)
            {
                cout << "\nThere isn`t points with the index!" << endl;
                return false;
            }
            return true;
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
                std::size_t new_index = index - current_size;
                current_size += current->arr_size;
                if (index < current_size)
                {
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
                            ListNode* new_node = new ListNode(current, current->next, current->points[j++]);
                            current->next->prev = new_node;
                            current->next = new_node;
                            new_node->arr_size = current->max_size / 2;
                            for (std::size_t k = 1; j < current->max_size; j++, k++)
                            {
                                new_node->points[k] = current->points[j];
                            }                          
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

            }
        }
        void delete_head()
        {
            size--;
            ListNode* current = head;
            if (size == 0)
            {
                delete[] current->points;
                head = nullptr;
                tail = nullptr;
                delete current;
                return;
            }
            if (current->arr_size == 1)
            {
                delete[] current->points;
                head = current->next;
                current->next->prev = nullptr;
                delete current;              
                return;
            }
            current->arr_size--;
            for (std::size_t i = 0; i < current->arr_size; i++)
            {
                current->points[i] = current->points[i + 1];
            }
        }
        void delete_middle(std::size_t index)
        {
            size--;
            std::size_t current_size = 0;
            for (ListNode* current = head; current; current = current->next)
            {
                std::size_t new_index = index - current_size;
                current_size += current->arr_size;
                if (index < current_size)
                {
                    if (current->arr_size == 1)
                    {
                        delete[] current->points;
                        current->prev->next = current->next;
                        current->next->prev = current->prev;
                        delete current;
                       
                        return;
                    }
                    current->arr_size--;
                    for (std::size_t i = new_index; i < current->arr_size; i++)
                    {
                        current->points[i] = current->points[i + 1];
                    }
                    return;
                }
            }
        }
        void delete_tail()
        {
            size--;
            ListNode* current = tail;
            if (current->arr_size == 1)
            {
                delete[] current->points;
                tail = current->prev;
                current->prev->next = nullptr;
                delete current;
                return;
            }
            current->arr_size--;
        }
    public:
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
        bool insert(Point point, std::size_t index)
        {
            if (!is_index(index)) return false;
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
        bool get(Point& point, std::size_t index)
        {
            if (!is_index(index)) return false;
            std::size_t current_size = 0;
            for (ListNode* current = head; current; current = current->next)
            {
                std::size_t new_index = index - current_size;
                current_size += current->arr_size;
                if (index < current_size)
                {
                    point = current->points[new_index];
                    return true;
                }
            }
            return false;
        }
        bool set(Point point, std::size_t index)
        {
            if (!is_index(index)) return false;
            std::size_t current_size = 0;
            for (ListNode* current = head; current; current = current->next)
            {
                std::size_t new_index = index - current_size;
                current_size += current->arr_size;
                if (index < current_size)
                {
                    current->points[new_index] = point;
                    return true;
                }
            }
            return false;
        }
        bool remove(std::size_t index)
        {
            if (!is_index(index)) return false;
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
        void clear()
        {
            size = 0;
            if (!head)
            {
                return;
            }
            if (head->next)
            {
                ListNode* current = head->next;
                head = nullptr;
                for (; current; current = current->next)
                {
                    delete[] current->prev->points;
                    current->prev->next = nullptr;
                    delete current->prev;
                }
                delete tail;
                tail = nullptr;
                return;
            }
            ListNode* current = head;
            head = nullptr;
            tail = nullptr;
            if (current) delete current;           
        }
    };
    void add_to_end_of_list(List& list)
    {
        Point point;
        point.read_point();
        list.append(point);
        cout << "\nThe point added to list!" << endl;
    }
    void add_to_list_by_index(List& list)
    {
        std::size_t index = correct::read_size_t("the index");
        Point point;
        point.read_point();
        if (list.insert(point, index))
        {
            cout << "\nThe point added to list!" << endl;
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
    void edit_point_by_index(List& list)
    {
        std::size_t index = correct::read_size_t("the index");
        Point point;
        point.read_point();
        if (list.set(point, index))
        {
            cout << "\nThe point edited!" << endl;
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
    void interactive_dialog_mode()
    {
        List list;
        while (true)
        {
            cout << "\nMenu:\n1)Adding a point to the end of the list.\n"
                << "2)Inserting a point before a point with the index.\n"
                << "3)Delete a point by index.\n4)Show a point by index.\n"
                << "5)Edit a point by index.\n6)Show all list\n0)Back." << endl;
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
            case '5': edit_point_by_index(list);
                break;
            case '6': list.write_list();
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
    void demo_add_to_end(unsigned delay, List& list, Point point)
    {
        cout << "\nMenu:\n1)Adding a point to the end of the list. <- press\n"
            << "2)Inserting a point before a point with the index.\n"
            << "3)Delete a point by index.\n4)Show a point by index.\n"
            << "5)Edit a point by index.\n6)Show all list.\n0)Back." << endl;
        Sleep(delay);
        demo_write_coordinate(delay, point);
        list.append(point);
        cout << "\nThe point added to list!" << endl;
        Sleep(delay);
    }
    void demo_add_to_list_by_index(unsigned delay, List& list, Point point, std::size_t index)
    {
        cout << "\nMenu:\n1)Adding a point to the end of the list.\n"
            << "2)Inserting a point before a point with the index. <- press\n"
            << "3)Delete a point by index.\n4)Show a point by index.\n"
            << "5)Edit a point by index.\n6)Show all list.\n0)Back." << endl;
        Sleep(delay);
        demo_write_index(delay, index);
        demo_write_coordinate(delay, point);
        if (list.insert(point, index)) cout << "\nThe point added to list!" << endl;
        Sleep(delay);
    }
    void demo_show_point_by_index(unsigned delay, List& list, std::size_t index)
    {
        cout << "\nMenu:\n1)Adding a point to the end of the list.\n"
            << "2)Inserting a point before a point with the index.\n"
            << "3)Delete a point by index.\n4)Show a point by index. <- press\n"
            << "5)Edit a point by index.\n6)Show all list.\n0)Back." << endl;
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
    void demo_edit_point_by_index(unsigned delay, List& list, Point point, std::size_t index)
    {
        cout << "\nMenu:\n1)Adding a point to the end of the list.\n"
            << "2)Inserting a point before a point with the index.\n"
            << "3)Delete a point by index.\n4)Show a point by index.\n"
            << "5)Edit a point by index. <- press\n6)Show all list.\n0)Back." << endl;
        Sleep(delay);
        demo_write_index(delay, index);
        demo_write_coordinate(delay, point);
        if (list.set(point, index))  cout << "\nThe point edited!" << endl;
        Sleep(delay);
    }
    void demo_delete_point_by_index(unsigned delay, List& list, std::size_t index)
    {
        cout << "\nMenu:\n1)Adding a point to the end of the list.\n"
            << "2)Inserting a point before a point with the index.\n"
            << "3)Delete a point by index. <- press\n4)Show a point by index.\n"
            << "5)Edit a point by index.\n6)Show all list.\n0)Back." << endl;
        Sleep(delay);
        demo_write_index(delay, index);
        if (list.remove(index))  cout << "\nThe point removed!" << endl;
        Sleep(delay);
    }
    void demo_write_list(unsigned delay, List& list)
    {
        cout << "\nMenu:\n1)Adding a point to the end of the list.\n"
            << "2)Inserting a point before a point with the index.\n"
            << "3)Delete a point by index.\n4)Show a point by index.\n"
            << "5)Edit a point by index.\n6)Show all list. <- press\n0)Back." << endl;
        Sleep(delay);
        list.write_list();
        Sleep(delay);
    }
    void demo_back(unsigned delay, List& list)
    {
        cout << "\nMenu:\n1)Adding a point to the end of the list.\n"
            << "2)Inserting a point before a point with the index.\n"
            << "3)Delete a point by index.\n4)Show a point by index.\n"
            << "5)Edit a point by index.\n6)Show all list.\n0)Back. <- press" << endl;
        list.clear();
        Sleep(delay);
    }
    void demo_mode()
    {
        unsigned delay = 1900;
        delay = correct::read_unsigned("a delay to display data(in milliseconds; normal = 1900)");
        List list;
        cout << "\nThe start of the demo mode(press <Ctrl + C> to exit)" << endl;
        Sleep(delay);
        demo_begin(delay);
        demo_add_to_end(delay, list, Point(5, 7, 4));
        demo_add_to_end(delay, list, Point(12, 8, 14));
        demo_add_to_list_by_index(delay, list, Point(1, 2, 3), 0);
        demo_write_list(delay, list);
        demo_edit_point_by_index(delay, list, Point(11, 12, 13), 2);
        demo_show_point_by_index(delay, list, 2);
        demo_edit_point_by_index(delay, list, Point(2, 7, 14), 0);
        demo_add_to_end(delay, list, Point(15, 3, 1));
        demo_add_to_list_by_index(delay, list, Point(3, 2, 6), 3);
        demo_write_list(delay, list);
        demo_delete_point_by_index(delay, list, 0);
        demo_delete_point_by_index(delay, list, 2);
        demo_write_list(delay, list);
        demo_back(delay, list);
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