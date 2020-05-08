#include "my_array_list.h"
#include <iostream>
#include <vector>
#include <ctime>
#include "my_point.h"

using namespace tdp;

namespace array
{
	Array_list::Array_list()
	{

	}
	void Array_list::edit_points(std::size_t index, Point point)
	{
		points.push_back(Point());
		for (std::size_t i = points.size() - 1; i > index; i--)
		{
			points[i] = points[i - 1];
		}
		points[index] = point;
	}
	void Array_list::add_item(Point point)
	{
		for (std::size_t i = 0; i < points.size(); i++)
		{
			if (points[i] > point)
			{
				edit_points(i, point);
				return;
			}
		}
		points.push_back(point);
	}
	void Array_list::write()
	{
		if (points.size() == 0)
		{
			std::cout << "\nList is empty!" << std::endl;
		}
		std::cout << "\nList:\n";
		for (std::size_t i = 0; i < points.size(); i++)
		{
			std::cout << i << ".";
			points[i].write();
		}
	}
	bool Array_list::remove_item(std::size_t index)
	{
		if (index >= points.size()) return false;
		points.erase(points.begin() + index);
		return true;
	}
	bool Array_list::remove_item(Point point)
	{
		for (std::size_t i = 0; i < points.size(); i++)
		{
			if(points[i] > point) return false;
			if (points[i] == point)
			{
				points.erase(points.begin() + i);
				return true;
			}
		}
		return false;
	}
	std::vector<Item> Array_list::find_items(Point point)
	{
		std::vector<Item> items;		
		for (std::size_t i = 0; i < points.size(); i++)
		{
			if (points[i] > point) return items;
			if (points[i] == point)
			{
				items.push_back(Item(point, i));
			}
		}
		return items;
	}
	std::vector<Item> Array_list::find_items(Point begin_point, Point end_point)
	{
		std::vector<Item> items;		
		for (std::size_t i = 0; i < points.size(); i++)
		{
			if (points[i] > end_point) return items;
			if (points[i] >= begin_point && points[i] <= end_point)
			{
				items.push_back(Item(points[i], i));
			}
		}
		return items;
	}
	void Array_list::random_generator(std::size_t number_of_items, std::size_t max_point)
	{
		srand(unsigned(time(0)));
		for (std::size_t i = 0; i < number_of_items; i++)
		{
			add_item(Point(rand() % max_point, rand() % max_point, rand() % max_point));
		}
	}
	double Array_list::find_distance_between_two_points(std::size_t first_index, std::size_t second_index)
	{
		std::size_t size = points.size();
		if ((first_index >= size) || (second_index >= size)) return -1;
		return find_distance(points[first_index], points[second_index]);
	}
	void Array_list::find_distance_between_adjacent_points()
	{
		std::cout << "\nDistance between adjacent points:" << std::endl;		
		for (std::size_t i = 0; i < points.size() - 1; i++)
		{
			std::cout << i << " -> " << i + 1 << " = " << find_distance(points[i], points[i + 1]) << std::endl;
		}
	}
	void Array_list::read_file(std::size_t index)
	{
		std::string path = "date.txt";
		Point point;
		point.read_from_file(path, index);
		std::cout << point;
	}
	bool Array_list::append_file(std::size_t index)
	{
		if (index >= points.size()) return false;
		std::string path = "date.txt";
		points[index].append_to_file(path);
		return true;
	}
	bool Array_list::find_length_and_area_of_circle(std::size_t index_of_centre, std::size_t index_of_anypoint)
	{
		std::size_t size = points.size();
		if ((index_of_centre >= size) || (index_of_anypoint >= size)) return false;
		std::size_t i = 0;
		Point centre = points[index_of_centre], anypoint = points[index_of_anypoint];
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
	void Array_list::clear()
	{
		points.clear();
	}
}
