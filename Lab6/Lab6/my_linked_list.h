#pragma once
#include "my_linked_list.h"
#include <iostream>
#include <vector>
#include <ctime>
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
		Linked_list(std::vector<Point>&);
		void add_item(Point);
		void write();
		bool remove_item(Point);
		bool remove_item(std::size_t);
		std::vector<Item>  find_items(Point);
		std::vector<Item>  find_items(Point, Point);
		void random_generator(std::size_t, double); 
		double find_distance_between_two_points(std::size_t, std::size_t);
		void find_distance_between_adjacent_points();
		Point read_file(std::size_t, const std::string&);
		bool append_file(std::size_t, const std::string&);
		bool find_length_and_area_of_circle(std::size_t, std::size_t);
		void clear();
		std::size_t count_size_of_memory();
		std::size_t get_size();

	};
}
