#include "my_linked_list.h"
#include <iostream>
#include <vector>
#include "my_point.h"

using namespace tdp;

namespace list
{
	List_node::List_node()
	{
		next = nullptr;
		point = Point();
	}
	List_node::List_node(List_node* next, Point point)
	{
		this->next = next;
		this->point = point;
	}
	Linked_list::Linked_list()
	{
		head = nullptr;
		size = 0;
	}
	void Linked_list::add_item(Point point)
	{
		size++;
		if (!head)
		{
			head = new List_node(nullptr, point);
			return;
		}
		if (head->point >= point)
		{
			List_node* node = new List_node(head, point);
			head = node;
			return;
		}
		List_node* current = head;
		for (; current->next; current = current->next)
		{
			if (current->next->point >= point)
			{
				List_node* node = new List_node(current->next, point);
				current->next = node;
				return;
			}
		}
		List_node* node = new List_node(nullptr, point);
		current->next = node;
	}
	void Linked_list::write()
	{
		std::cout << "\nList:\n";
		for (List_node* current = head; current; current = current->next)
		{
			current->point.write();
		}
	}
	bool Linked_list::remove_item(Point point)
	{
		size--;
		if (head->point == point)
		{
			List_node* node = head->next;
			delete head;
			head = node;
			return true;
		}
		for (List_node* current = head; current->next; current = current->next)
		{
			if (current->next->point == point)
			{
				List_node* node = current->next;
				current->next = node->next;
				delete node;
				return true;
			}
		}
		size++;
		return false;
	}
	bool Linked_list::remove_item(std::size_t index)
	{
		if (index >= size) return false;
		size--;
		if (index == 0)
		{
			List_node* node = head->next;
			delete head;
			head = node;
			return true;
		}
		std::size_t i = 0;
		for (List_node* current = head; current->next; current = current->next)
		{
			if (i + 1 == index)
			{
				List_node* node = current->next;
				current->next = node->next;
				delete node;
				return true;
			}
			i++;
		}
		size++;
		return false;
	}
	std::vector<Item> Linked_list::find_item(Point point)
	{
		std::vector<Item> items;
		std::size_t i = 0;
		for (List_node* current = head; current; current = current->next, i++)
		{
			if (current->point > point) return items;
			if (current->point == point)
			{
				items.push_back(Item(point, i));
			}			
		}
		return items;
	}
	std::vector<Item> Linked_list::find_item(Point begin_point, Point end_point)
	{
		std::vector<Item> items;
		std::size_t i = 0;
		for (List_node* current = head; current; current = current->next, i++)
		{
			if (current->point > end_point) return items;
			if (current->point >= begin_point && current->point <= end_point)
			{
				items.push_back(Item(current->point, i));
			}
		}
		return items;
	}

}
