#include <iostream>
#include <conio.h>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
struct List_Node;
enum class implementation_approach{ FIXED, DYNAMIC, LINKED};

struct Point
{
    double x;
    double y;
    double z;
    Point()
    {
        this->x = 0;
        this->y = 0;
        this->z = 0;
    }
    Point(double x, double y, double z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }
    void read_point()
    {
        cout << "\nEnter point!" << endl;
        cout <<"\nEnter the first coordinate : ";
        double x;
        cin >> x;
        this->x = x;
        cout << "\nEnter the second coordinate : ";
        double y;
        cin >> y;
        this->y = y;
        cout << "\nEnter the third coordinate : ";
        double z;
        cin >> z;
        this->z = z;
    }
    void write_point()
    {
        cout << "x= " << this->x << " y= " << this->y
             << " z= " << this->z << endl;
    }
};
struct List_Node
{
    Point point;
    List_Node* next;
    List_Node* prev;
};
struct Fixed_list
{
    Point* points;
    std::size_t size;
    std::size_t max_size;
    bool is_list;
    Fixed_list()
    {
        points = nullptr;
        size = 0;
        max_size = 0;
        is_list = false;
    }
    bool is_index(unsigned index)
    {
        if (index > (size - 1))
        {
            cout << "\nThere isn`t item with the index!" << endl;
            return false;
        }
        return true;
    }
    void create(std::size_t max_size)
    {
        points = new Point[max_size];
        size = 0;
        this->max_size = max_size;
        is_list = true;
    }
    void clear()
    {
        if (is_list) delete[] points;
    }
    void append(Point point)
    {
        if (size == max_size)
        {
            cout << "\nThe list is overflowing!";
            return;
        }
        points[size] = point;
        size++;
    }
    void insert(Point point, unsigned index)
    {
        if (!is_index(index)) return;
        for (std::size_t i = size; i > index; i--)
        {
            points[i] = points[i - 1];
        }
        points[index] = point;
        size++;
    }
    void remove(unsigned index)
    {
        if (!is_index(index)) return;
        for (std::size_t i = index; i < (size + 1); i++)
        {
            points[i] = points[i + 1];
        }
        size--;
    }
    void get(unsigned index)//print point
    {
        if (!is_index(index)) return;
        cout << "\nThe point:" << endl;
        points[index].write_point();
    }
    void set(unsigned index, Point point)//edit point
    {
        if (!is_index(index)) return;
        points[index] = point;
    }
};
struct Dynamic_list
{
    std::vector <Point> points;
    bool is_list;
    Dynamic_list()
    {
        is_list = false;
    }
    bool is_index(unsigned index)
    {
        std::size_t size = points.size();
        if (index > (size - 1))
        {
            cout << "\nThere isn`t item with the index!" << endl;
            return false;
        }
        return true;
    }
    void create()
    {
        is_list = true;
    }
    void clear()
    {
        if (is_list) points.clear();
    }
    void append(Point point)
    {
        points.push_back(point);
    }
    void insert(unsigned index, Point point)
    {
        std::size_t size = points.size();
        points.push_back(Point());
        if (!is_index(index)) return;
        for (std::size_t i = size; i > index; i--)
        {
            points[i] = points[i - 1];
        }
        points[index] = point;
    }
    void remove(unsigned index)
    {
        std::size_t size = points.size();
        if ((index > (size - 1)) || (index < 0))
        {
            cout << "\nThere isn`t item with the index!" << endl;
            return;
        }
        points.erase(points.begin() + index);
    }
    void get(unsigned index)
    {
        if (!is_index(index)) return;
        cout << "\nThe point:" << endl;
        points[index].write_point();
    }
    void set(unsigned index, Point point)
    {
        if (!is_index(index)) return;
        points[index] = point;
    }
};
struct Linked_list
{
    std::size_t size;
    List_Node* head;
    List_Node* tail;
    bool is_list;
    Linked_list()
    {
        size = 0;
        head = nullptr;
        tail = nullptr;
        is_list = false;
    }
    bool is_index(unsigned index)
    {
        if (index > (size - 1))
        {
            cout << "\nThere isn`t item with the index!" << endl;
            return false;
        }
        return true;
    }
    void create()
    {
        is_list = true;
    }
    void clear()
    {
        if (!is_list) return;
        List_Node* current_node = head->next;
        for (; current_node; current_node = current_node->next)
        {
            current_node->prev->next = nullptr;
            current_node->prev = nullptr;
        }
        Linked_list();
    }
    void append(Point point)
    {
        List_Node* node = new List_Node;
        node->point = point;
        node->prev = tail;
        node->next = nullptr;
        if (tail)
        {
            tail->next = node;
            tail = node;
        }
        else
        {
            tail = node;
            head = node;
        }
        size++;
    }
private:
    void add_head()
    {

    }
    void add_middle()
    {

    }
    void add_tail()
    {

    }
public:
    void insert(unsigned index, Point point)
    {
       
    }
    void remove(unsigned index)
    {
        
    }
    void get(unsigned index)
    {
        
    }
    void set(unsigned index, Point point)
    {
       
    }
};
implementation_approach choice_of_approach()
{
    while (true)
    {
        cout << "\nChoose the approach to implement the data structure \"List\"" << endl
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
}
Fixed_list create_empty_list()
{
    Fixed_list list;
    cout << "\nEnter the maximum size of list: ";
    std::size_t max_size;
    cin >> max_size;
    list.create(max_size);
    return list;
}
void interactive_dialog_mode()
{
    while (true)
    {
        cout << "\nMenu:\n1)Create a blank list.\n2)Adding an item to the end of the list.\n"
             << "3)Inserting an element before an element with an index.\n"
             << "4)Delete an item by index.\n5)Access the item by index.\n"
             << "6)Show list length.\n0)Back." << endl;
        switch (_getch())
        {
        case '1':
        {
            
            continue;
        }
        break;
        case'2':
        {
            
            continue;
        }
        break;
        case '3':
        {
            
            continue;
        }
        break;
        case '4':
        {
          
            continue;
        }
        break;
        case '5':
        {
           
            continue;
        }
        break;
        case '6':
        {

            continue;
        }
        break;
        case '0':
        {
            
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
void demo_mode()
{

}
void  benchmark_mode()
{

}
int n = 0;
void wrtite_test(Fixed_list& list)
{
    cout << n++ << endl;
    for (std::size_t i = 0; i < list.size; i++)
    {
        cout << i << ". ";
        list.points[i].write_point();
    }
    cout << endl << endl;
}
void test()
{
    Fixed_list list;
    list.create(10);
    list.append(Point(0, 0, 0));
    list.append(Point(1, 1, 1));
    list.append(Point(2, 2, 2));
    wrtite_test(list);
    list.insert(Point(-3, -3, -3), 1);   
    wrtite_test(list);
    list.remove(0);
    wrtite_test(list);
    list.remove(2);
    wrtite_test(list);
    list.remove(6);
    wrtite_test(list);
    list.append(Point(4, 4, 4));
    wrtite_test(list);
    list.insert(Point(-5, -5, -5), 5);
    wrtite_test(list);
    list.insert(Point(-6, -6, -6), 0);
    wrtite_test(list);
    list.append(Point(7, 7, 7));
    wrtite_test(list);
}
int main()
{
    /*while (true)
    {
        cout << "\nSelect the application mode:\n1)Interactive dialog mode.\n"
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
    }*/

    test();
    return 0;
}