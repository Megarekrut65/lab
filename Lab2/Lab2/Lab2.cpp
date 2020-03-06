#include <iostream>
#include <conio.h>
#include <vector>
#include <string>
#include <Windows.h>
#include <chrono>
#include <fstream>
using std::cin;
using std::cout;
using std::endl;
struct measurement_result;
struct Point;
struct List_Node;
struct Fixed_list;
struct Dynamic_list;
struct Linked_list;
enum class implementation_approach;

template<class T>
void create_empty_list(T&);
template<class T>
void add_to_end_of_list(T&);
template<class T>
void add_to_list_by_index(T&);
template<class T>
void delete_point_by_index(T&);
template<class T>
void show_point_by_index(T&);
template<class T>
void edit_point_by_index(T&);
template<class T>
void show_list_length(T&);
template<class T>
void clear_list(T&);
double correct_read_double(const std::string&);
unsigned correct_read_unsigned(const std::string&);
std::size_t correct_read_size(const std::string&);
implementation_approach choice_of_approach();
void interactive_create(const implementation_approach&, Fixed_list&, Dynamic_list&, Linked_list&);
void interactive_append(const implementation_approach&, Fixed_list&, Dynamic_list&, Linked_list&);
void interactive_insert(const implementation_approach&, Fixed_list&, Dynamic_list&, Linked_list&);
void interactive_get(const implementation_approach&, Fixed_list&, Dynamic_list&, Linked_list&);
void interactive_set(const implementation_approach&, Fixed_list&, Dynamic_list&, Linked_list&);
void interactive_remove(const implementation_approach&, Fixed_list&, Dynamic_list&, Linked_list&);
void interactive_length(const implementation_approach&, Fixed_list&, Dynamic_list&, Linked_list&);
void interactive_back(const implementation_approach&, Fixed_list&, Dynamic_list&, Linked_list&);
void interactive_dialog_mode();
void demo_begin(unsigned);
void demo_choice_of_approach(unsigned);
void demo_create_empty_list(unsigned, Fixed_list&, std::size_t);
void demo_write_coordinate(unsigned, Point);
void demo_write_index(unsigned, std::size_t);
void demo_add_to_end_of_list(unsigned, Fixed_list&, Point);
void demo_add_to_list_by_index(unsigned, Fixed_list&, std::size_t, Point);
void demo_delete_point_by_index(unsigned, Fixed_list&, std::size_t);
void demo_show_point_by_index(unsigned, Fixed_list&, std::size_t);
void demo_edit_point_by_index(unsigned, Fixed_list&, std::size_t, Point);
void demo_show_list_length(unsigned, Fixed_list&);
void demo_exit(unsigned);
void demo_mode();
void clear_result_files(const std::string&);
void add_result_to_file(const std::string&, measurement_result);
void write_time(float, const std::string&);
Point point_generetor();
unsigned index_generator(std::size_t);
template<class T>
float measurement_append(T&, const std::string&, std::size_t);
template<class T>
float measurement_insert(T&, const std::string&, std::size_t);
template<class T>
float measurement_remove(T&, const std::string&, std::size_t);
template<class T>
float measurement_get(T&, const std::string&, std::size_t);
template<class T>
float measurement_set(T&, const std::string&, std::size_t);
template<class T>
float measurement_clear(T&, const std::string&, std::size_t);
template<class T>
void measurement_menu(T&, const std::string&);
void  benchmark_mode();

enum class implementation_approach{ FIXED, DYNAMIC, LINKED};
struct measurement_result
{    
    std::size_t number_of_points;
    std::size_t number_of_operations;
    float time;
};
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
    bool is_index(std::size_t index)
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
public:
    Point* give_points()
    {
        return points;
    }
    void copy_points(Point* points, std::size_t size)
    {
        Point* new_points = new Point[max_size];
        for (std::size_t i = 0; i < size; i++) new_points[i] = points[i];
        if (this->points) delete[] this->points;
        this->points = new_points;
        this->size = size;
        created_list = true;
    }
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
    bool create()
    {
        if (created_list) return false;
        points = new Point[max_size];
        created_list = true;
        return true;
    }
    void clear()
    {
        if (created_list)
        {
            delete[] points;
            points = nullptr;
            size = 0;
            created_list = false;
        }
    }
    bool append(Point point)
    {
        if((!is_list()) || (!is_space())) return false;        
        points[size] = point;
        size++;
        return true;
    }
    bool insert(std::size_t index, Point point)
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
    bool remove(std::size_t index)
    {
        if ((!is_list()) || (!is_index(index))) return false;
        for (std::size_t i = index; i < (size - 1); i++)
        {
            points[i] = points[i + 1];
        }                  
        size--;
        return true;
    }
    bool get(std::size_t index, Point& point)
    {
        if ((!is_list()) || (!is_index(index))) return false;
        point = points[index];
        return true;
    }
    bool set(std::size_t index, Point point)
    {
        if ((!is_list()) || (!is_index(index))) return false;
        points[index] = point;
        return true;
    }
    bool length(std::size_t& size)
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
    bool is_index(std::size_t index)
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
public:
    Dynamic_list()
    {
        created_list = false;
    } 
    std::vector <Point> give_points()
    {
        return points;
    }
    void copy_points(const std::vector <Point>& points,std::size_t size)
    {
        if (this->points.size() > 0) this->points.clear();
        this->points = points;
        created_list = true;
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
            created_list = false;
        }
    }
    bool append(Point point)
    {
        if (!is_list()) return false;
        points.push_back(point);
        return true;
    }
    bool insert(std::size_t index, Point point)
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
    bool remove(std::size_t index)
    {
        if ((!is_list()) || (!is_index(index))) return false;
        points.erase(points.begin() + index);
        return true;
    }
    bool get(std::size_t index, Point& point)
    {
        if ((!is_list()) || (!is_index(index))) return false;
        point = points[index];
        return true;
    }
    bool set(std::size_t index, Point point)
    {
        if ((!is_list()) || (!is_index(index))) return false;
        points[index] = point;
        return true;
    }
     bool length(std::size_t& size)
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
    void add_middle(std::size_t index, Point point)
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
    void delete_middle(std::size_t index)
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
    bool is_index(std::size_t index)
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
public:
    Linked_list()
    {       
        size = 0;
        head = nullptr;
        tail = nullptr;
        created_list = false;      
    }  
    List_Node* give_points()
    {
        return head;
    }
    void copy_points(List_Node* head, std::size_t size)
    {
        if (size > 0) clear();
        created_list = true;
        if (!head) return;
        for (List_Node* current = head; current; current = current->next)
        {
            append(current->point);
        }       
    }
    bool create()
    {
        if (created_list) return false;      
        created_list = true;
        return true;
    }
    void clear()
    {
        if ((!created_list)||(!head)) return;
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
        size = 0;
        created_list = false;
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
    bool insert(std::size_t index, Point point)
    {
        if ((!is_list()) || (!is_index(index))) return false;
        if (index == 0) add_head(point);
        else add_middle(index, point);
        size++;
        return true;
    }
    bool remove(std::size_t index)
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
    bool get(std::size_t index, Point& point)
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
    bool set(std::size_t index, Point point)
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
    bool length(std::size_t& size)
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
    std::size_t index = correct_read_size("the index");
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
    std::size_t index = correct_read_size("the index");
    if (list.remove(index))
    {
        cout << "\nThe point removed!" << endl;
    }
}
template<class T>
void show_point_by_index(T& list)
{
    std::size_t index = correct_read_size("the index");
    Point point;
    if (list.get(index, point))
    {
        point.write_point();
    }
}
template<class T>
void edit_point_by_index(T& list)
{
    std::size_t index = correct_read_size("the index");
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
    if (list.length(size))
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
        long number;
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
std::size_t correct_read_size(const std::string& sentence)
{
    while (true)
    {
        cout << "\nEnter " << sentence << ": ";
        long long number;
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
            return number;
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
void interactive_create(const implementation_approach& approach, Fixed_list& fixed, Dynamic_list& dynamic, Linked_list& linked)
{
    switch (approach)
    {
    case implementation_approach::FIXED:
    {
        std::size_t max_size = correct_read_size("the maximum size of list");
        fixed.add_max_size(max_size);
        create_empty_list(fixed);
    }
    break;
    case implementation_approach::DYNAMIC: create_empty_list(dynamic);
        break;
    case implementation_approach::LINKED: create_empty_list(linked);
    }
}
void interactive_append(const implementation_approach& approach, Fixed_list& fixed, Dynamic_list& dynamic, Linked_list& linked)
{
    switch (approach)
    {
    case implementation_approach::FIXED: add_to_end_of_list(fixed);
        break;
    case implementation_approach::DYNAMIC: add_to_end_of_list(dynamic);
        break;
    case implementation_approach::LINKED: add_to_end_of_list(linked);
    }
}
void interactive_insert(const implementation_approach& approach, Fixed_list& fixed, Dynamic_list& dynamic, Linked_list& linked)
{
    switch (approach)
    {
    case implementation_approach::FIXED: add_to_list_by_index(fixed);
        break;
    case implementation_approach::DYNAMIC: add_to_list_by_index(dynamic);
        break;
    case implementation_approach::LINKED: add_to_list_by_index(linked);
    }
}
void interactive_remove(const implementation_approach& approach, Fixed_list& fixed, Dynamic_list& dynamic, Linked_list& linked)
{
    switch (approach)
    {
    case implementation_approach::FIXED: delete_point_by_index(fixed);
        break;
    case implementation_approach::DYNAMIC: delete_point_by_index(dynamic);
        break;
    case implementation_approach::LINKED: delete_point_by_index(linked);
    }
}
void interactive_get(const implementation_approach& approach, Fixed_list& fixed, Dynamic_list& dynamic, Linked_list& linked)
{
    switch (approach)
    {
    case implementation_approach::FIXED: show_point_by_index(fixed);
        break;
    case implementation_approach::DYNAMIC: show_point_by_index(dynamic);
        break;
    case implementation_approach::LINKED: show_point_by_index(linked);
    }
}
void interactive_set(const implementation_approach& approach, Fixed_list& fixed, Dynamic_list& dynamic, Linked_list& linked)
{
    switch (approach)
    {
    case implementation_approach::FIXED: edit_point_by_index(fixed);
        break;
    case implementation_approach::DYNAMIC: edit_point_by_index(dynamic);
        break;
    case implementation_approach::LINKED: edit_point_by_index(linked);
    }
}
void interactive_length(const implementation_approach& approach, Fixed_list& fixed, Dynamic_list& dynamic, Linked_list& linked)
{
    switch (approach)
    {
    case implementation_approach::FIXED: show_list_length(fixed);
        break;
    case implementation_approach::DYNAMIC: show_list_length(dynamic);
        break;
    case implementation_approach::LINKED: show_list_length(linked);
    }
}
void interactive_back(const implementation_approach& approach, Fixed_list& fixed, Dynamic_list& dynamic, Linked_list& linked)
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
            interactive_create(approach, fixed, dynamic, linked);
            continue;
        }
        break;
        case'2':
        {
            interactive_append(approach, fixed, dynamic, linked);
            continue;
        }
        break;
        case '3':
        {
            interactive_insert(approach, fixed, dynamic, linked);
            continue;
        }
        break;
        case '4':
        {
            interactive_remove(approach, fixed, dynamic, linked);
            continue;
        }
        break;
        case '5':
        {
            interactive_get(approach, fixed, dynamic, linked);
            continue;
        }
        break;
        case '6':
        {
            interactive_set(approach, fixed, dynamic, linked);
            continue;
        }
        break;
        case '7':
        {
            interactive_length(approach, fixed, dynamic, linked);
            continue;
        }
        break;
        case '0':
        {
            interactive_back(approach, fixed, dynamic, linked);
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
void demo_write_index(unsigned delay, std::size_t index)
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
void demo_add_to_list_by_index(unsigned delay, Fixed_list& list, std::size_t index, Point point)
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
void demo_delete_point_by_index(unsigned delay, Fixed_list& list, std::size_t index)
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
void demo_show_point_by_index(unsigned delay, Fixed_list& list, std::size_t index)
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
void demo_edit_point_by_index(unsigned delay, Fixed_list& list, std::size_t index, Point point)
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
    if(list.length(size)) cout << "\nThe lenght of list: " << size << endl; 
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
void clear_result_files(const std::string& approach)
{
    std::string all_result_files[6] = { "result_append_" + approach + ".txt", "result_insert_" + approach + ".txt",
        "result_remove_" + approach + ".txt", "result_get_" + approach + ".txt", "result_set_" + approach + ".txt",
        "result_clear_" + approach + ".txt"};
    for (unsigned i = 0; i < 6; i++)
    {
        std::ofstream clear_file(all_result_files[i]);
        clear_file.close();
    }
}
void add_result_to_file(const std::string& path, measurement_result result)
{
    std::ofstream file(path, std::ios_base::app);
    file << "Number of operations: " << result.number_of_operations << endl;
    file << "The initial number of points: " << result.number_of_points << endl;   
    file << "Time: " << result.time << endl;
    file.close();
}
void write_time(float time, const std::string& method)
{
    cout << "Time of " + method + " points = " << time << " seconds." 
         << endl;
}
Point point_generetor()
{
    double x, y, z;
    srand(unsigned(time(0)));
    x = double(rand() % 10000);
    y = x;
    z = x;
    return Point(x, y, z);
}
unsigned index_generator(std::size_t size)
{
    unsigned index;
    srand(unsigned(time(0)));
    index = unsigned(rand()%size);
    return index;
}
template<class T>
float measurement_append(T& list, const std::string& path, std::size_t number_of_operations)
{
    measurement_result append;
    auto the_start = std::chrono::high_resolution_clock::now();
    auto the_end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> duration; 
    std::size_t size;
    bool temp = list.length(size);
    append.number_of_operations = number_of_operations;    
    append.number_of_points = size;
    Point point = point_generetor();
    the_start = std::chrono::high_resolution_clock::now();
    for (std::size_t i = 0; i < number_of_operations; i++)
    {
        temp = list.append(point);
    }
    the_end = std::chrono::high_resolution_clock::now();  
    duration = the_end - the_start;
    append.time = duration.count();
    add_result_to_file("result_append_" + path + ".txt", append);
    write_time(append.time,"append");

    return append.time;
}
template<class T>
float measurement_insert(T& list, const std::string& path, std::size_t number_of_operations)
{
    measurement_result insert;
    auto the_start = std::chrono::high_resolution_clock::now();
    auto the_end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> duration;
    std::size_t size;
    bool temp = list.length(size);
    insert.number_of_operations = number_of_operations;  
    insert.number_of_points = size;
    Point point = point_generetor();
    std::vector<unsigned> indexs;
    for (std::size_t k = 0; k < number_of_operations; k++)
    {
        indexs.push_back(index_generator(size));
        size++;
    }   
    the_start = std::chrono::high_resolution_clock::now();  
    for (std::size_t i = 0; i < number_of_operations; i++)
    {
        temp = list.insert(indexs[i], point);
    }
    the_end = std::chrono::high_resolution_clock::now();
    duration = the_end - the_start;
    insert.time = duration.count();
    add_result_to_file("result_insert_" + path + ".txt", insert);
    write_time(insert.time,"insert");
    return insert.time;
}
template<class T>
float measurement_remove(T& list, const std::string& path, std::size_t number_of_operations)
{
    measurement_result remove;
    auto the_start = std::chrono::high_resolution_clock::now();
    auto the_end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> duration;
    std::size_t size;
    bool temp = list.length(size);
    remove.number_of_operations = number_of_operations;
    remove.number_of_points = size;
    std::vector<unsigned> indexs;
    for (std::size_t k = 0; k < number_of_operations; k++)
    {
        indexs.push_back(index_generator(size));
        size--;
        if (size <= 0) break;
    }
    the_start = std::chrono::high_resolution_clock::now();
    for (std::size_t i = 0; i < number_of_operations; i++)
    {
        temp = list.remove(indexs[i]);
    } 
    the_end = std::chrono::high_resolution_clock::now();
    duration = the_end - the_start;
    remove.time = duration.count();
    add_result_to_file("result_remove_" + path + ".txt", remove);
    write_time(remove.time,"remove");

    return remove.time;
}
template<class T>
float measurement_get(T& list, const std::string& path, std::size_t number_of_operations)
{
    measurement_result get;
    auto the_start = std::chrono::high_resolution_clock::now();
    auto the_end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> duration;
    std::size_t size;
    bool temp = list.length(size);
    get.number_of_operations = number_of_operations;
    get.number_of_points = size;
    Point point = point_generetor();
    std::vector<unsigned> indexs;
    for (std::size_t k = 0; k < number_of_operations; k++)
    {
        indexs.push_back(index_generator(size));
    }
    the_start = std::chrono::high_resolution_clock::now();
    for (std::size_t i = 0; i < number_of_operations; i++)
    {
        temp = list.get(indexs[i], point);
    }
    the_end = std::chrono::high_resolution_clock::now();
    duration = the_end - the_start;
    get.time = duration.count();
    add_result_to_file("result_get_" + path + ".txt", get);
    write_time(get.time,"get");

    return get.time;
}
template<class T>
float measurement_set(T& list, const std::string& path, std::size_t number_of_operations)
{
    measurement_result set;
    auto the_start = std::chrono::high_resolution_clock::now();
    auto the_end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> duration;
    std::size_t size;
    bool temp = list.length(size);
    set.number_of_operations = number_of_operations;   
    set.number_of_points = size;
    Point point = point_generetor();
    std::vector<unsigned> indexs;
    for (std::size_t k = 0; k < number_of_operations; k++)
    {
        indexs.push_back(index_generator(size));
    }
    the_start = std::chrono::high_resolution_clock::now();
    for (std::size_t i = 0; i < number_of_operations; i++)
    {
        temp = list.set(indexs[i], point);
    }     
    the_end = std::chrono::high_resolution_clock::now();
    duration = the_end - the_start;
    set.time = duration.count();
    add_result_to_file("result_set_" + path + ".txt", set);
    write_time(set.time,"set");

    return set.time;
}
template<class T>
float measurement_clear(T& list, const std::string& path, std::size_t number_of_operations)
{
    measurement_result clear;
    auto the_start = std::chrono::high_resolution_clock::now();
    auto the_end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> duration;
    std::size_t size;
    bool temp = list.length(size);
    clear.number_of_operations = number_of_operations;
    clear.number_of_points = size;
    the_start = std::chrono::high_resolution_clock::now();
    list.clear();
    the_end = std::chrono::high_resolution_clock::now();
    duration = the_end - the_start;
    clear.time = duration.count();
    add_result_to_file("result_clear_" + path + ".txt", clear);
    write_time(clear.time,"clear");

    return clear.time;
}
template<class T>
void measurement_menu(T& list, const std::string& approach)
{   
    clear_result_files(approach);
    const std::size_t number = 1562;
    std::size_t the_end_of_numbers = 150001;
    std::size_t number_of_points = 1, number_of_operations = number;
    std::size_t copy_number_of_operations = number, copy_number_of_points = 1, save_number_of_points = 0;
    std::size_t coefficient_of_operations = 2, coefficient_of_points = 2;
    const unsigned number_of_methods = 6;
    bool more_one_second = false;
    bool more_ten_second = false;
    float(*methods[number_of_methods])(T&, const std::string&, std::size_t) = {
        measurement_append, measurement_insert, measurement_remove, measurement_get, 
        measurement_set, measurement_clear };    
    for (number_of_operations = number; number_of_operations < the_end_of_numbers;)
    {      
        T copy_list = list;
        bool temp = copy_list.create();
        save_number_of_points = 0;
        copy_number_of_points = number_of_operations;
        coefficient_of_points = 2;
        more_one_second = false;
        for (number_of_points = number_of_operations; number_of_points < (the_end_of_numbers/2);)
        {
            for (std::size_t i = 0; i < (number_of_points - save_number_of_points); i++)
            {
                temp = copy_list.append(point_generetor());
            }
            temp = list.create();
            save_number_of_points = number_of_points;
            cout << "\nThe initial number of operations:" << number_of_operations << endl; 
            cout << "The initial number of points:" << number_of_points << endl;
            for (unsigned j = 0; j < number_of_methods; j++)
            {
                float time;
                list.copy_points(copy_list.give_points(), number_of_points);            
                time = methods[j](list, approach, number_of_operations);
                if (time > 1) more_one_second = true;
                if (time > 10) more_ten_second = true;
            }
            cout << endl;
            if (more_ten_second) break;
            if (more_one_second)
            {
                number_of_points = coefficient_of_points * copy_number_of_points;
                coefficient_of_points++;
            }
            else
            {
                number_of_points *= 2;
                copy_number_of_points = number_of_points;
            }
        }
        if (more_ten_second) break;
        if (more_one_second)
        {
            number_of_operations = coefficient_of_operations * copy_number_of_operations;
            coefficient_of_operations++;
        }
        else
        {
            number_of_operations *= 2;
            copy_number_of_operations = number_of_operations;
        }
        copy_list.clear();
    }
    
    cout << "\nResults of measurements of program in the following files:\n"
        << "result_append_"+approach+".txt\nresult_insert_" + approach + ".txt\n"
        << "result_remove_" + approach + ".txt\nresult_get_" + approach + ".txt\n"
        << "result_set_" + approach + ".txt\nresult_clear_" + approach + ".txt" << endl;
}
void  benchmark_mode()
{
    Fixed_list fixed;
    cout << "\nMeasurement result of Fixed list: " << endl;
    fixed.add_max_size(500001);
    measurement_menu(fixed, "fixed");
    Dynamic_list dynamic;
    cout << "\nMeasurement result of Dynamic list: " << endl;
    measurement_menu(dynamic, "dynamic");
    Linked_list linked;
    cout << "\nMeasurement result of Linked list: " << endl;
    measurement_menu(linked, "linked");
    cout << "\nThe end of measurements!" << endl;
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
        default: cout << "\nPress the correct key!\n" << endl;
        }
    }
    return 0;
}