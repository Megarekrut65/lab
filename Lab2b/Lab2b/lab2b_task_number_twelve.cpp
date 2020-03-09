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
                size = (index + 1) > size ? (index + 1) : size;
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
                    cout << "\nThe Point with the index has already created!" << endl;
                    return;
                }
                if (!current->next)
                {
                    if (!point.is_zero())
                    {
                        new_node = new SparseListNode(point, index, nullptr);
                        current->next = new_node;
                    }                  
                    size = (index + 1) > size ? (index + 1) : size;
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
                    }
                    return true;
                }
            }
            insert(point, index);
            return true;
        }
        bool remove(std::size_t index)
        {
            if (!is_index(index)) return false;
            SparseListNode* current = head;
            if (index == current->index)
            {
                head = current->next;
                delete current;
                size--;
                return true;
            }
            for (; current; current = current->next)
            {
                if (!current->next)
                {
                    size--;
                    return true;
                }
                if (index == current->next->index)
                {
                    SparseListNode* temp_node = current->next;
                    current->next = temp_node->next;
                    delete temp_node;
                    size--;
                    return true;
                }
            }          
        }
	};
	void menu()
	{
        SparseList list;
        
        cout << "\nreturn 0" << endl;
  
	}
}
