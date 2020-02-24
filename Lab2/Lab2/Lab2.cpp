#include <iostream>
#include <conio.h>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
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
struct Fixed_list
{
    Point* points;
    std::size_t size;
    std::size_t max_size;
    Fixed_list(std::size_t max_size)
    {
        this->points = new Point[max_size];
        this->size = 0;
        this->max_size = max_size;
    }
    void append(Point point)
    {
        if (this->size == this->max_size)
        {
            cout << "\nThe list is overflowing!";
            return;
        }
        this->points[this->size] = point;
        this->size++;
    }
    void insert(Point point, unsigned index)
    {
        if ((index > (this->size - 1))|| (index < 0))
        {
            cout << "\nThere isn`t item with the index!" << endl;
            return;
        }
        for (std::size_t i = size; i > index; i--)
        {
            this->points[i] = this->points[i - 1];
        }
        this->points[index] = point;
        this->size++;
    }
    void remove(unsigned index)
    {
        if ((index > (this->size - 1)) || (index < 0))
        {
            cout << "\nThere isn`t item with the index!" << endl;
            return;
        }
        for (std::size_t i = index; i < (size + 1); i++)
        {
            this->points[i] = this->points[i + 1];
        }
        this->size--;
    }
    void get(unsigned index)
    {

    }
    void set(unsigned index)
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
    cout << "\nEnter the maximum size of list: ";
    std::size_t max_size;
    cin >> max_size;
    return Fixed_list(max_size);
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
    Fixed_list list = Fixed_list(10);
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