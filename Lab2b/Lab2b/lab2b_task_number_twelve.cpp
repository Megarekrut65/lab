#include "lab2b_task_number_twelve.h"
#include "my_correct_read.h"
#include <iostream>
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
            this->x = correct::read("the first coordinate");
            this->y = correct::read("the second coordinate");
            this->z = correct::read("the third coordinate");
        }
        void write_point()
        {
            cout << "x = " << x << " y = " << y
                << " z = " << z << endl;
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
                cout << "\nThere isn`t item with the index!" << endl;
                return false;
            }
            return true;
        }
    public:
		SparseList() : size(0), head(nullptr) {}
        void write_list()
        {
            cout << "\nSize:" << size;
            for (SparseListNode* current = head; current; current = current->next)
            {
                cout << "\nIndex: " << current->index << endl;
                cout << "Point: ";
                current->point.write_point();           
            }
        }
        void insert(Point point, std::size_t index)
        {           
            SparseListNode* current = head;
            SparseListNode* new_node;
            if (!current)
            {
                if (!point.is_zero())
                {
                    new_node = new SparseListNode(point, index, nullptr);
                    head = new_node;
                }               
                size = index + 1;
                return;
            }           
            if (index < current->index)
            {
                if (!point.is_zero())
                {
                    new_node = new SparseListNode(point, index, current);
                    head = new_node;
                }              
                return;
            }           
            for (; current; current = current->next)
            {
                if (index == current->index)
                {
                    cout << "The Point with the index has already created!" << endl;
                    return;
                }
                if (!current->next)
                {
                    if (!point.is_zero())
                    {
                        new_node = new SparseListNode(point, index, nullptr);
                        current->next = new_node;
                    }                  
                    size = index + 1;
                    return;
                }
                if (index < current->next->index)
                {
                    if (!point.is_zero())
                    {
                        new_node = new SparseListNode(point, index, current->next);
                        current->next = new_node;
                    }
                    return;
                }
            }
        }
	};
	void menu()
	{
        SparseList list;

        list.insert(Point(3, 2, 1), 7);
        list.write_list();
        cout << "\n###########################################\n";
        list.insert(Point(5, 2, 22), 5);
        list.write_list();
        cout << "\n###########################################\n";
        list.insert(Point(55, 11, 82), 10);
        list.write_list();
        cout << "\n###########################################\n";
        list.insert(Point(55, 11, 82), 5);
        list.write_list();
        cout << "\n###########################################\n";
        list.insert(Point(0, 0, 0), 5);
        list.write_list();
        cout << "\n###########################################\n";
        list.insert(Point(0, 0, 0), 7);
        list.write_list();
        cout << "\n###########################################\n";
        list.insert(Point(0, 0, 0), 4);       
        list.write_list();
        cout << "\n###########################################\n";
        list.insert(Point(0, 0, 0), 20);
        list.write_list();
        cout << "\nreturn 0" << endl;
  
	}
}
