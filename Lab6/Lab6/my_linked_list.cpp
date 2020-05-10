#include "my_linked_list.h"
#include <iostream>
#include <vector>
#include <ctime>
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
		if (!head)
		{
			std::cout << "\nList is empty!" << std::endl;
			return;
		}
		std::size_t i = 0;
		std::cout << "\nList:\n";
		for (List_node* current = head; current; current = current->next, i++)
		{
			std::cout << i << ".";
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
	std::vector<Item> Linked_list::find_items(Point point)
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
	std::vector<Item> Linked_list::find_items(Point begin_point, Point end_point)
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
	void Linked_list::random_generator(std::size_t number_of_items, std::size_t max_point)
	{
		clear();
		srand(unsigned(time(0)));
		for (std::size_t i = 0; i < number_of_items; i++)
		{
			add_item(Point(rand()% max_point, rand() % max_point, rand() % max_point));
		}
	}
	double Linked_list::find_distance_between_two_points(std::size_t first_index, std::size_t second_index)
	{
		if ((first_index >= size)||(second_index >= size)) return -1;
		std::size_t i = 0;
		Point first_point, second_point;
		bool is_find = false;
		for (List_node* current = head; current; current = current->next, i++)
		{
			if (i == first_index)
			{
				first_point = current->point;
				if (is_find) break;
				is_find = true;
			}
			if (i == second_index)
			{
				second_point = current->point;
				if(is_find) break;
				is_find = true;
			}
		}
		return find_distance(first_point, second_point);		
	}
	void Linked_list::find_distance_between_adjacent_points()
	{
		std::cout << "\nDistance between adjacent points:" << std::endl;
		std::size_t i = 0;
		for (List_node* current = head; current->next; current = current->next, i++)
		{
			std::cout << i << " -> " << i + 1 << " = " << find_distance(current->point, current->next->point) << std::endl;
		}
	}
	void Linked_list::read_file(std::size_t index)
	{
		std::string path = "date.txt";
		Point point;
		point.read_from_file(path, index);			
		std::cout << point;
		add_item(point);
	}
	bool Linked_list::append_file(std::size_t index)
	{
		if (index >= size) return false;
		std::string path = "date.txt";
		std::size_t i = 0;
		for (List_node* current = head; current; current = current->next, i++)
		{
			if (i == index)
			{
				current->point.append_to_file(path);
				return true;
			}
		}
		return false;
	}
	bool Linked_list::find_length_and_area_of_circle(std::size_t index_of_centre, std::size_t index_of_anypoint)
	{
		if ((index_of_centre >= size) || (index_of_anypoint >= size)) return false;
		std::size_t i = 0;
		Point centre, anypoint;
		bool is_find = false;
		for (List_node* current = head; current; current = current->next, i++)
		{
			if (i == index_of_centre)
			{
				centre = current->point;
				if (is_find) break;
				else is_find = true;
			}
			if (i == index_of_anypoint)
			{
				anypoint = current->point;
				if (is_find) break;
				else is_find = true;
			}
		}
		double length = find_length_of_circle(centre, anypoint);
		double area = find_area_of_circle(centre, anypoint);
		double radius = find_distance(centre, anypoint);
		std::cout << "\nCircle.\n";
		std::cout << "Centre: ";
		centre.write();
		std::cout << "Radius: " << radius << std::endl;
		std::cout << "Length: " << length << std::endl;
		std::cout << "Area: " << area << std::endl;
		return true;
	}
	void Linked_list::clear()
	{
		List_node* current = head;
		head = nullptr;
		while (current)
		{
			List_node* temp = current;
			current = current->next;
			delete temp;
			temp = nullptr;
		}
		size = 0;
	}
}
