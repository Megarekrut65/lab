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
		SparseList(std::size_t size) : size(size), head(nullptr) {}
        void write_list()
        {
            for (SparseListNode* current = head; current; current = current->next)
            {
                cout << "\nindex: " << current->index << endl;
                current->point.write_point();           
            }
        }
        void insert(Point point, std::size_t index)
        {
            if (!is_index(index)||(point.is_zero())) return;
            SparseListNode* current = head;
            SparseListNode* new_node;
            if (!current)
            {
                new_node = new SparseListNode(point, index, nullptr);
                head = new_node;
                return;
            }
            if (index == current->index)
            {
                current->point = point;
                return;
            }
            if (index < current->index)
            {
                new_node = new SparseListNode(point, index, current);
                head = new_node;
                return;
            }           
            for (; current; current = current->next)
            {
                if (!current->next)
                {
                    new_node = new SparseListNode(point, index, nullptr);
                    current->next = new_node;
                    return;
                }
                if (index == current->next->index)
                {
                    current->next->point = point;
                    return;
                }
                if (index < current->next->index)
                {
                    new_node = new SparseListNode(point, index, current->next);
                    current->next = new_node;
                    return;
                }
            }
        }
	};
	void menu()
	{
        SparseList list(100);

        list.insert(Point(3, 2, 1), 3);
        list.insert(Point(5, 2, 22), 2);
        list.insert(Point(55, 11, 82), 1);
        list.insert(Point(55, 11, 82), 6);
        list.insert(Point(55, 11, 82), 5);
        list.insert(Point(55, 11, 82), 4);
       
        list.write_list();
        cout << "\nreturn 0" << endl;
  
	}
}
