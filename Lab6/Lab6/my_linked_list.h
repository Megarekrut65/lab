#pragma once
#include "my_linked_list.h"
#include <iostream>
#include <vector>
#include "my_point.h"

using namespace tdp;

namespace list
{
	struct List_node
	{
		List_node* next;
		Point point;
		List_node();
		List_node(List_node*, Point);
	};
	struct Linked_list
	{
		List_node* head;
		std::size_t size;
		Linked_list();
		void add_item(Point);
		void write();
		bool remove_item(Point);
		bool remove_item(std::size_t);
		std::vector<Item>  find_item(Point);
		std::vector<Item>  find_item(Point, Point);
	};
}
