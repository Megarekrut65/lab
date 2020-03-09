#include "lab2b_task_number_three.h"
#include "my_correct_read.h"
#include <iostream>
#include <string>
using std::cout;
using std::cin;
using std::endl;
namespace three
{
    struct ListNode
    {
        int value;
        ListNode* prev;
        ListNode* next;
        ListNode() : value(0), prev(nullptr), next(nullptr){}
        ListNode(int value, ListNode* next, ListNode* prev) : value(value), prev(prev), next(next){}
    };
    struct List
    {
        int size;
        ListNode* head;
        ListNode* tail;       
        List() : size(0), head(nullptr), tail(nullptr){}
        void append(int value)
        {
            if (tail)
            {
                ListNode* new_node = new ListNode(value, tail, nullptr);
                tail->next = new_node;
                tail = new_node;
                size++;
                return;
            }
            ListNode* new_node = new ListNode(value, nullptr, nullptr);
            head = new_node;
            tail = new_node;
            size++;   
        }
        void splice(ListNode* new_head, int begin, int end)
        {
            if (end < 0)
            {
                //perevirka na index
                int i = size - 1;
                for (ListNode* current = tail; current; current = current->prev)
                {
                    if (i == -1) current = tail;
                    if (begin <= i)
                    {

                    }
                    i--;
                }
            }
        }
    };
	void menu()
	{
       
		std::cout << "\nThe end!" << std::endl;
	}
}
