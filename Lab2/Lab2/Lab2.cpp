﻿#include <iostream>
#include <conio.h>
#include <vector>
#include <string>
#include <Windows.h>
using std::cin;
using std::cout;
using std::endl;
struct List_Node;
enum class implementation_approach;
void interactive_dialog_mode();
implementation_approach choice_of_approach();
double correct_read_double(const std::string&);
unsigned correct_read_unsigned(const std::string&);
enum class implementation_approach{ FIXED, DYNAMIC, LINKED};
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
        double x = correct_read_double("the first coordinate");
        double y = correct_read_double("the second coordinate");
        double z = correct_read_double("the third coordinate");
        this->x = x;
        this->y = y;
        this->z = z;
    }
    void write_point()
    {
        cout << "x = " << x << " y = " << y
             << " z = " << z << endl;
    }
};
struct List_Node
{
    Point point;
    List_Node* next;
    List_Node* prev;
    List_Node()
    {
        next = nullptr;
        prev = nullptr;
    }
};
struct Fixed_list
{
private:
    Point* points;
    std::size_t size;
    std::size_t max_size;
    bool created_list;   
public:
    Fixed_list()
    {
        points = nullptr;
        size = 0;
        max_size = 1;
        created_list = false;
    }
    void add_max_size(std::size_t max_size)
    {
        if (created_list) return;
        this->max_size = max_size;
    }
    bool is_index(unsigned index)
    {
        if ((index + 1) > size)
        {
            cout << "\nThere isn`t item with the index!" << endl;
            return false;
        }
        return true;
    }
    bool is_list()
    {
        if (!created_list)
        {
            cout << "\nThe list not created!" << endl;
            return false;
        }
        return true;
    }  
    bool is_space()
    {
        if (size == max_size)
        {          
            cout << "\nThe list is overflowing!" << endl;
            return false;
        }
        return true;
    }
    bool create()
    {
        if (created_list) return false;
        points = new Point[max_size];
        size = 0;
        created_list = true;
        return true;
    }
    void clear()
    {
        if (created_list)
        {
            delete[] points;
            Fixed_list();
        }
    }
    bool append(Point point)
    {
        if((!is_list()) || (!is_space())) return false;        
        points[size] = point;
        size++;
        return true;
    }
    bool insert(unsigned index, Point point)
    {
        if ((!is_list()) || (!is_space()) || (!is_index(index))) return false;
        for (std::size_t i = size; i > index; i--)
        {
            points[i] = points[i - 1];
        }
        points[index] = point;
        size++;
        return true;
    }
    bool remove(unsigned index)
    {
        if ((!is_list()) || (!is_index(index))) return false;
        for (std::size_t i = index; i < (size - 1); i++)
        {
            points[i] = points[i + 1];
        }                  
        size--;
        return true;
    }
    bool get(unsigned index, Point& point)
    {
        if ((!is_list()) || (!is_index(index))) return false;
        point = points[index];
        return true;
    }
    bool set(unsigned index, Point point)
    {
        if ((!is_list()) || (!is_index(index))) return false;
        points[index] = point;
        return true;
    }
    bool lenght(std::size_t& size)
    {
        if (!is_list()) return false;
        size = this->size;
        return true;
    }
};
struct Dynamic_list
{
private:
    std::vector <Point> points;
    bool created_list;
public:
    Dynamic_list()
    {
        created_list = false;
    }
    bool is_index(unsigned index)
    {
        std::size_t size = points.size();
        if ((index + 1) > size)
        {
            cout << "\nThere isn`t item with the index!" << endl;
            return false;
        }
        return true;
    }
    bool is_list()
    {
        if (!created_list)
        {
            cout << "\nThe list not created!" << endl;
            return false;
        }
        return true;
    }
    bool create()
    {
        if (created_list) return false;
        created_list = true;
        return true;
    }
    void clear()
    {
        if (created_list)
        {
            points.clear();
            Dynamic_list();
        }
    }
    bool append(Point point)
    {
        if (!is_list()) return false;
        points.push_back(point);
        return true;
    }
    bool insert(unsigned index, Point point)
    {
        if ((!is_list()) || (!is_index(index))) return false;
        std::size_t size = points.size();
        points.push_back(Point());
        for (std::size_t i = size; i > index; i--)
        {
            points[i] = points[i - 1];
        }
        points[index] = point;
        return true;
    }
    bool remove(unsigned index)
    {
        if ((!is_list()) || (!is_index(index))) return false;
        points.erase(points.begin() + index);
        return true;
    }
    bool get(unsigned index, Point& point)
    {
        if ((!is_list()) || (!is_index(index))) return false;
        point = points[index];
        return true;
    }
    bool set(unsigned index, Point point)
    {
        if ((!is_list()) || (!is_index(index))) return false;
        points[index] = point;
        return true;
    }
     bool lenght(std::size_t& size)
    {
         if (!is_list()) return false;
         size = points.size();
         return true;
    }
};
struct Linked_list
{
private:
    std::size_t size;
    List_Node* head;
    List_Node* tail;
    bool created_list;
    void add_head(Point point)
    {
        List_Node* new_node = new List_Node;
        new_node->point = point;
        new_node->prev = nullptr;
        new_node->next = head;
        head->prev = new_node;
        head = new_node;
    }
    void add_middle(unsigned index, Point point)
    {
        List_Node* new_node = new List_Node;
        List_Node* current_node = head->next;
        new_node->point = point;
        for (std::size_t i = 1; i < size; i++, current_node = current_node->next)
        {
            if (i == index)
            {
                new_node->next = current_node;
                new_node->prev = current_node->prev;
                current_node->prev->next = new_node;
                current_node->prev = new_node;
                break;
            }
        }
    }
    void delete_head()
    {
        if (head->next)
        {
            head = head->next;
            delete head->prev;
            head->prev = nullptr;
        }
        else
        {
            tail = nullptr;
            delete head;
            head = nullptr;
        }
        size--;
    }
    void delete_middle(unsigned index)
    {
        List_Node* current_node = head->next;
        for (std::size_t i = 1; i < size; i++, current_node = current_node->next)
        {
            if (i == index)
            {
                current_node->prev->next = current_node->next;
                current_node->next->prev = current_node->prev;
                delete current_node;
                current_node = nullptr;
                break;
            }
        }
        size--;
    }
    void delete_tail()
    {
        tail = tail->prev;
        delete tail->next;
        tail->next = nullptr;
        size--;
    }
public:
    Linked_list()
    {
        size = 0;
        head = nullptr;
        tail = nullptr;
        created_list = false;
    }
    bool is_index(unsigned index)
    {
        if ((index + 1) > size)
        {
            cout << "\nThere isn`t item with the index!" << endl;
            return false;
        }
        return true;
    }
    bool is_list()
    {
        if (!created_list)
        {
            cout << "\nThe list not created!" << endl;
            return false;
        }
        return true;
    }
    bool create()
    {
        if (created_list) return false;
        created_list = true;
        return true;
    }
    void clear()
    {
        if ((!created_list)||(size == 0)) return;
        List_Node* current_node = head->next;
        head = nullptr;
        for (; current_node; current_node = current_node->next)
        {
            current_node->prev->next = nullptr;
            delete current_node->prev;
            current_node->prev = nullptr;
        }
        delete tail;
        tail = nullptr;
        Linked_list();
    }
    bool append(Point point)
    {
        if (!is_list()) return false;
        List_Node* new_node = new List_Node;
        new_node->point = point;
        new_node->prev = tail;
        new_node->next = nullptr;
        if (tail)
        {
            tail->next = new_node;
            tail = new_node;
        }
        else
        {
            tail = new_node;
            head = new_node;
        }
        size++;
        return true;
    }
    bool insert(unsigned index, Point point)
    {
        if ((!is_list()) || (!is_index(index))) return false;
        if (index == 0) add_head(point);
        else add_middle(index, point);
        size++;
        return true;
    }
    bool remove(unsigned index)
    {
        if ((!is_list()) || (!is_index(index))) return false;
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
    bool get(unsigned index, Point& point)
    {
        if ((!is_list()) || (!is_index(index))) return false;
        List_Node* current_node = head;
        for (std::size_t i = 0; i < size; i++, current_node = current_node->next)
        {
            if (i == index)
            {
                point = current_node->point;
                return true;
            }
        } 
        return false;
    }
    bool set(unsigned index, Point point)
    {
        if ((!is_list()) || (!is_index(index))) return false;
        List_Node* current_node = head;
        for (std::size_t i = 0; i < size; i++, current_node = current_node->next)
        {
            if (i == index)
            {
                current_node->point = point;
                return true;
            }
        }
        return false;
    }
    bool lenght(std::size_t& size)
    {
        if (!is_list()) return false;
        size = this->size;
        return true;
    }
};
template<class T>
void create_empty_list(T& list)
{
    if (list.create())
    {      
        cout << "\nNew list created!" << endl;
    }
    else
    {
        cout << "\nThe list has already been created!" << endl;
    }
}
template<class T>
void add_to_end_of_list(T& list)
{
    Point point;
    point.read_point();
    if (list.append(point))
    {
        cout << "\nThe point added to the list!" << endl;
    }   
}
template<class T>
void add_to_list_by_index(T& list)
{
    unsigned index = correct_read_unsigned("the index");
    Point point;
    point.read_point();
    if (list.insert(index, point))
    {
        cout << "\nThe point added to the list!" << endl;
    }
}
template<class T>
void delete_point_by_index(T& list)
{
    unsigned index = correct_read_unsigned("the index");
    if (list.remove(index))
    {
        cout << "\nThe point removed!" << endl;
    }
}
template<class T>
void show_point_by_index(T& list)
{
    unsigned index = correct_read_unsigned("the index");
    Point point;
    if (list.get(index, point))
    {
        point.write_point();
    }
}
template<class T>
void edit_point_by_index(T& list)
{
    unsigned index = correct_read_unsigned("the index");   
    Point point;
    point.read_point();
    if (list.set(index, point))
    {
        cout << "\nThe point edited!" << endl;
    }
}
template<class T>
void show_list_length(T& list)
{
    std::size_t size;
    if (list.lenght(size))
    {
        cout << "\nThe lenght of list: " << size << endl;
    }
}
template<class T>
void clear_list(T& list)
{
    list.clear();
}
double correct_read_double(const std::string& sentence)
{   
    while (true)
    {
        cout << "\nEnter " << sentence << ": ";
        std::string line;
        getline(cin, line);
        while (line.size() == 0) getline(cin, line);
        char* p;
        double number;
        if (line.find(",") != std::string::npos)
        {
            line.replace(line.find(","), 1, ".");
        }
        number = strtod(line.c_str(), &p);
        if (*p == 0) return number;
        else cout << "\nThe data entered incorrectly!" << endl;
    }
}
unsigned correct_read_unsigned(const std::string& sentence)
{
    while (true)
    {
        cout <<"\nEnter " << sentence << ": ";
        int number;
        cin >> number;
        if ((!cin.good()) || (number < 0))
        {        
            cin.clear();
            cin.ignore(200, '\n');
            cout << "\nThe data entered incorrectly!" << endl;
        }
        else
        {
            cin.clear();
            cin.ignore(200, '\n');
            return unsigned(number);
        }
    }
}
implementation_approach choice_of_approach()
{
    while (true)
    {
        cout << "\nChoose the approach to implement the data structure \"List\":" << endl
             << "1)Based on a fixed size array.\n2)Based on a dynamic array.\n3)Based on a linked list." << endl;
        switch (_getch())
        {
        case '1': return implementation_approach::FIXED;
            break;
        case '2': return implementation_approach::DYNAMIC;
            break;
        case '3': return implementation_approach::LINKED;
            break;
        default: cout << "\nPress the correct key!" << endl;
        }
    }
    return implementation_approach::FIXED;
}
void interactive_dialog_mode()
{
    implementation_approach approach = choice_of_approach();
    Fixed_list fixed;
    Dynamic_list dynamic;
    Linked_list linked;
    while (true)
    {
        cout << "\nMenu:\n1)Create a blank list.\n2)Adding a point to the end of the list.\n"
             << "3)Inserting a point before a point with the index.\n"
             << "4)Delete a point by index.\n5)Show a point by index.\n"
             << "6)Edit a point by index.\n7)Show list length.\n0)Back." << endl;
        switch (_getch())
        {
        case '1':
        {
            switch (approach)
            {
            case implementation_approach::FIXED: 
            {
                cout << "\nEnter the maximum size of list: ";
                std::size_t max_size;
                cin >> max_size;
                fixed.add_max_size(max_size);
                create_empty_list(fixed);
            }
                break;
            case implementation_approach::DYNAMIC: create_empty_list(dynamic);
                break;
            case implementation_approach::LINKED: create_empty_list(linked);
            }
            continue;
        }
        break;
        case'2':
        {
            switch (approach)
            {
            case implementation_approach::FIXED: add_to_end_of_list(fixed);
                break;
            case implementation_approach::DYNAMIC: add_to_end_of_list(dynamic);
                break;
            case implementation_approach::LINKED: add_to_end_of_list(linked);
            }                
            continue;
        }
        break;
        case '3':
        {
            switch (approach)
            {
            case implementation_approach::FIXED: add_to_list_by_index(fixed);
                break;
            case implementation_approach::DYNAMIC: add_to_list_by_index(dynamic);
                break;
            case implementation_approach::LINKED: add_to_list_by_index(linked);
            }
            continue;
        }
        break;
        case '4':
        {
            switch (approach)
            {
            case implementation_approach::FIXED: delete_point_by_index(fixed);
                break;
            case implementation_approach::DYNAMIC: delete_point_by_index(dynamic);
                break;
            case implementation_approach::LINKED: delete_point_by_index(linked);
            }
            continue;
        }
        break;
        case '5':
        {
            switch (approach)
            {
            case implementation_approach::FIXED: show_point_by_index(fixed);
                break;
            case implementation_approach::DYNAMIC: show_point_by_index(dynamic);
                break;
            case implementation_approach::LINKED: show_point_by_index(linked);
            }
            continue;
        }
        break;
        case '6':
        {
            switch (approach)
            {
            case implementation_approach::FIXED: edit_point_by_index(fixed);
                break;
            case implementation_approach::DYNAMIC: edit_point_by_index(dynamic);
                break;
            case implementation_approach::LINKED: edit_point_by_index(linked);
            }
            continue;
        }
        break;
        case '7':
        {
            switch (approach)
            {
            case implementation_approach::FIXED: show_list_length(fixed);
                break;
            case implementation_approach::DYNAMIC: show_list_length(dynamic);
                break;
            case implementation_approach::LINKED: show_list_length(linked);
            }
            continue;
        }
        break;
        case '0':
        {
            switch (approach)
            {
            case implementation_approach::FIXED: clear_list(fixed);
            break;
            case implementation_approach::DYNAMIC: clear_list(dynamic);
                break;
            case implementation_approach::LINKED: clear_list(linked);
            }
            cout << endl;
        }
        break;
        default:
        {
            cout << "\nPress the correct key!" << endl;
            continue;
        }
        }
        break;
    }
}
void demo_begin(unsigned delay)
{
    cout << "\nSelect the application mode:\n1)Interactive dialog mode.\n"
        << "2)Demo mode.\n3)Automatic benchmark mode.\n0)Exit.\n";
    Sleep(delay);
    cout << "\nSelect the application mode:\n1)Interactive dialog mode. <- press\n"
        << "2)Demo mode.\n3)Automatic benchmark mode.\n0)Exit.\n";
    Sleep(delay);
}
void demo_choice_of_approach(unsigned delay)
{
    cout << "\nChoose the approach to implement the data structure \"List\":" << endl
        << "1)Based on a fixed size array. <- press\n2)Based on a dynamic array.\n3)Based on a linked list." << endl;
    Sleep(delay);
}
void demo_create_empty_list(unsigned delay, Fixed_list& list, std::size_t max_size)
{
    cout << "\nMenu:\n1)Create a blank list. <- press\n2)Adding a point to the end of the list.\n"
        << "3)Inserting a point before a point with the index.\n"
        << "4)Delete a point by index.\n5)Show a point by index.\n"
        << "6)Edit a point by index.\n7)Show list length.\n0)Back." << endl;
    Sleep(delay);
    cout << "\nEnter the maximum size of list: <- write the size and press <Enter>" << endl;
    Sleep(delay);
    cout << "\nEnter the maximum size of list: " << max_size << endl;
    Sleep(delay);
    cout << "\nThe list not created!" << endl;
    list.add_max_size(max_size);
    list.create();
    cout << "\nNew list created!" << endl;
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
void demo_write_index(unsigned delay, unsigned index)
{
    cout << "\nEnter the index: <- write the index and press <Enter>" << endl;
    Sleep(delay);
    cout << "Enter the index: " << index << endl;
    Sleep(delay);
}
void demo_add_to_end_of_list(unsigned delay, Fixed_list& list, Point point)
{
    cout << "\nMenu:\n1)Create a blank list.\n2)Adding a point to the end of the list. <- press\n"
        << "3)Inserting a point before a point with the index.\n"
        << "4)Delete a point by index.\n5)Show a point by index.\n"
        << "6)Edit a point by index.\n7)Show list length.\n0)Back." << endl;
    Sleep(delay);
    demo_write_coordinate(delay, point);
    if(list.append(point)) cout << "\nThe point added to the list!" << endl;
    Sleep(delay);
}
void demo_add_to_list_by_index(unsigned delay, Fixed_list& list, unsigned index, Point point)
{
    cout << "\nMenu:\n1)Create a blank list.\n2)Adding a point to the end of the list.\n"
        << "3)Inserting a point before a point with the index. <- press\n"
        << "4)Delete a point by index.\n5)Show a point by index.\n"
        << "6)Edit a point by index.\n7)Show list length.\n0)Back." << endl;
    Sleep(delay);
    demo_write_index(delay, index);
    demo_write_coordinate(delay, point);
    if(list.insert(index, point))  cout << "\nThe point added to the list!" << endl;
    Sleep(delay);
}
void demo_delete_point_by_index(unsigned delay, Fixed_list& list, unsigned index)
{

    cout << "\nMenu:\n1)Create a blank list.\n2)Adding a point to the end of the list.\n"
        << "3)Inserting a point before a point with the index.\n"
        << "4)Delete a point by index. <- press\n5)Show a point by index.\n"
        << "6)Edit a point by index.\n7)Show list length.\n0)Back." << endl;
    Sleep(delay);
    demo_write_index(delay, index);
    list.remove(index);
    Sleep(delay);
}
void demo_show_point_by_index(unsigned delay, Fixed_list& list, unsigned index)
{
    cout << "\nMenu:\n1)Create a blank list.\n2)Adding a point to the end of the list.\n"
        << "3)Inserting a point before a point with the index.\n"
        << "4)Delete a point by index.\n5)Show a point by index. <- press\n"
        << "6)Edit a point by index.\n7)Show list length.\n0)Back." << endl;
    Sleep(delay);
    demo_write_index(delay, index);
    Point point;
    bool temp = list.get(index, point);
    point.write_point();
    Sleep(delay);
}
void demo_edit_point_by_index(unsigned delay, Fixed_list& list, unsigned index, Point point)
{
    cout << "\nMenu:\n1)Create a blank list.\n2)Adding a point to the end of the list.\n"
        << "3)Inserting a point before a point with the index.\n"
        << "4)Delete a point by index.\n5)Show a point by index.\n"
        << "6)Edit a point by index. <- press\n7)Show list length.\n0)Back." << endl;
    Sleep(delay);
    demo_write_index(delay, index);
    demo_write_coordinate(delay, point);
    list.set(index, point);
    Sleep(delay);
}
void demo_show_list_length(unsigned delay, Fixed_list& list)
{
    cout << "\nMenu:\n1)Create a blank list.\n2)Adding a point to the end of the list.\n"
        << "3)Inserting a point before a point with the index.\n"
        << "4)Delete a point by index.\n5)Show a point by index.\n"
        << "6)Edit a point by index.\n7)Show list length. <- press\n0)Back." << endl;
    Sleep(delay);
    std::size_t size;
    if(list.lenght(size)) cout << "\nThe lenght of list: " << size << endl; 
    Sleep(delay);
}
void demo_exit(unsigned delay)
{
    cout << "\nMenu:\n1)Create a blank list.\n2)Adding a point to the end of the list.\n"
        << "3)Inserting a point before a point with the index.\n"
        << "4)Delete a point by index.\n5)Show a point by index.\n"
        << "6)Edit a point by index.\n7)Show list length.\n0)Back.  <- press" << endl;
    Sleep(delay);
}
void demo_mode()
{
    unsigned delay = 1900;
    delay = correct_read_unsigned("a delay to display data(in milliseconds; normal = 1900)");
    Fixed_list list;
    cout << "\nThe start of the demo mode(press <Ctrl + C> to exit)" << endl;
    demo_begin(delay);
    demo_choice_of_approach(delay);
    demo_create_empty_list(delay, list, 5);  
    demo_add_to_end_of_list(delay, list, Point(3.7, 6, 10.24));
    demo_add_to_end_of_list(delay, list, Point(11, 0.34, 0));
    demo_add_to_list_by_index(delay, list, 1, Point(1.1, 2.2, 3.3));
    demo_show_point_by_index(delay, list, 0);
    demo_show_point_by_index(delay, list, 1);
    demo_show_point_by_index(delay, list, 2);
    demo_delete_point_by_index(delay, list, 0);
    demo_edit_point_by_index(delay, list, 1, Point(10, 10, 10));
    demo_show_list_length(delay, list);
    demo_show_point_by_index(delay, list, 0);
    demo_show_point_by_index(delay, list, 1);
    demo_exit(delay);
    list.clear();
    cout << "\nThe end of the demo mode\n" << endl;
    Sleep(delay);
}
void  benchmark_mode()
{

}
int main()
{
    while (true)
    {
        cout << "Select the application mode:\n1)Interactive dialog mode.\n"
            << "2)Demo mode.\n3)Automatic benchmark mode.\n0)Exit.\n";
        switch (_getch())
        {
        case '1': interactive_dialog_mode();
            break;
        case '2': demo_mode();
            break;
        case '3': benchmark_mode();
            break;
        case'0':
        {
            cout << "\nExit..." << endl;
            return 0;
        }
        break;
        default: cout << "\nPress the correct key!" << endl;
        }
    }
    //test();
    return 0;
}