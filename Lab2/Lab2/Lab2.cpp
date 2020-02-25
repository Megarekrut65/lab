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
    List_Node()
    {
        next = nullptr;
        prev = nullptr;
    }
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
        if (is_list)
        {
            delete[] points;
            Fixed_list();
        }
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
    void insert(unsigned index, Point point)
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
    bool get(unsigned index, Point& point)//print point
    {
        if (!is_index(index)) return false;
        point = points[index];
        return true;
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
        if (!is_index(index)) return;
        std::size_t size = points.size();
        points.push_back(Point());
        for (std::size_t i = size; i > index; i--)
        {
            points[i] = points[i - 1];
        }
        points[index] = point;
    }
    void remove(unsigned index)
    {
        if (!is_index(index)) return;
        std::size_t size = points.size();
        points.erase(points.begin() + index);
    }
    bool get(unsigned index, Point& point)
    {
        if (!is_index(index)) return false;
        point = points[index];
        return true;
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
    void append(Point point)
    {
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
    }
private:
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
        head = head->next;
        delete head->prev;
        head->prev = nullptr;
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
    void insert(unsigned index, Point point)
    {
        if (!is_index(index)) return;
        if (index == 0) add_head(point);
        else add_middle(index, point);
        size++;
    }
    void remove(unsigned index)
    {
        if (!is_index(index)) return;
        if (index == 0)
        {
            delete_head();
            return;
        }
        if (index == (size - 1))
        {
            delete_tail();
            return;
        }
        delete_middle(index);     
    }
    bool get(unsigned index, Point& point)
    {
        if (!is_index(index)) return false;
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
    void set(unsigned index, Point point)
    {
        if (!is_index(index)) return;
        List_Node* current_node = head;
        for (std::size_t i = 0; i < size; i++, current_node = current_node->next)
        {
            if (i == index)
            {
                current_node->point = point;
                break;
            }
        }
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
    Fixed_list fixed;
    Dynamic_list dynamic;
    Linked_list linked;
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
void write_test(const Fixed_list& list)
{
    cout << n++ << endl;
    for (std::size_t i = 0; i < list.size; i++)
    {
        list.points[i].write_point();
    }
    cout << endl << endl;
}
void write_test(const Linked_list& list)
{
    cout << n++ << endl;
    for (List_Node* node = list.head; node; node = node->next) node->point.write_point();
    cout << endl << endl;
};
void write_test(Dynamic_list list)
{
    cout << n++ << endl;
    std::size_t size = list.points.size();
    for (std::size_t i = 0; i < size; i++)
    {
        list.points[i].write_point();
    }
    cout << endl << endl;
}
void test()
{
    Dynamic_list list;
    list.create();
    list.append(Point(0, 0, 0));
    write_test(list);//0
    list.append(Point(1, 1, 1));
    list.append(Point(2, 2, 2));
    write_test(list);//1
    list.insert(2,Point(-3, -3, -3));   
    write_test(list);//2
    list.remove(0);
    write_test(list);//3
    list.remove(2);
    write_test(list);//4
    list.remove(6);
    write_test(list);//5
    list.append(Point(4, 4, 4));
    write_test(list);//6
    list.set(2, Point(11, 11, 11));
    write_test(list);//7
    list.insert(5,Point(-5, -5, -5));
    write_test(list);//8
    list.insert(0,Point(-6, -6, -6));
    write_test(list);//9
    list.append(Point(7, 7, 7));
    write_test(list);//10
    double x = 0, y = 1, z = 2;
    std::size_t size = list.points.size();
    for (std::size_t i = 0; i < size; i++) list.set(i,Point(x++,y++,z++));
    for (std::size_t i = 0; i < 10; i++)
    {
        Point p;
        if(list.get(i,p)) p.write_point();      
    }

}
int main()
{
    while (true)
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
    }

    //test();
    return 0;
}