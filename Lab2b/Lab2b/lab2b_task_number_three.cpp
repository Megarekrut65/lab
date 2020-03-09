#include "lab2b_task_number_three.h"
#include "my_correct_read.h"
#include <iostream>
#include <string>
using std::cout;
using std::cin;
using std::endl;
namespace three
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
        void read_point()
        {
            cout << "\nEnter a point!" << endl;
            this->x = correct::read_double("the first coordinate");
            this->y = correct::read_double("the second coordinate");
            this->z = correct::read_double("the third coordinate");
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
    struct List
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
        List()
        {
            size = 0;
            head = nullptr;
            tail = nullptr;
            created_list = false;
        }
        bool create()
        {
            if (created_list) return false;
            created_list = true;
            return true;
        }
        void clear()
        {
            if ((!created_list) || (!head)) return;
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
        bool splice(int begin_index, int end_index, List* new_head)
        {
            if ((!is_list()) || (!is_index(abs(begin_index)))|| (!is_index(abs(end_index)))) return false;

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
	void menu()
	{
        List list;
        list.create();
        list.append(Point(0, 1, 3));
        Point point;
        point.read_point();
        list.append(point);
        point.write_point();
        list.clear();
		std::cout << "\nThe end!" << std::endl;
	}
}
