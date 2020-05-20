#pragma once
#include "my_array_list.h"
#include <iostream>
#include <vector>
#include <ctime>
#include "my_point.h"

using namespace tdp;

namespace array
{
	struct Array_list
	{
	private:
		void edit_points(std::size_t, Point);
	public:
		std::vector<Point> points;
		Array_list();
		void add_item(Point);
		void write();
		bool remove_item(std::size_t);
		bool remove_item(Point);
		std::vector<Item> find_items(Point);
		std::vector<Item> find_items(Point, Point);
		void random_generator(std::size_t, double);
		double find_distance_between_two_points(std::size_t, std::size_t);
		void find_distance_between_adjacent_points();
		Point read_file(std::size_t, const std::string&);
		bool append_file(std::size_t, const std::string&);
		bool find_length_and_area_of_circle(std::size_t, std::size_t);
		void clear();
	};
}