#pragma once
#include "my_point.h"
#include <vector>
#include <string>
#include <fstream>

namespace tdp
{
	struct Point
	{
		double x;
		double y;
		double z;
		Point();
		Point(double, double, double);	
		void write();
		void append_to_file(const std::string&);
		void read_from_file(const std::string&);
	};
	struct Item
	{
		Point point;
		std::size_t index;
		Item();
		Item(Point, std::size_t);
	};
	void write_items(std::vector<Item>&);
	double find_distance(Point, Point);
	double find_length_of_circle(Point, Point);
	double find_area_of_circle(Point, Point);
	bool operator < (Point, Point);
	bool operator > (Point, Point);
	bool operator <= (Point, Point);
	bool operator >= (Point, Point);
	bool operator == (Point, Point);
	bool operator != (Point, Point);
	Point operator + (Point, Point);
	Point operator - (Point, Point);
	Point operator * (Point, Point);
	Point operator / (Point, Point);
	std::ostream& operator << (std::ostream&, const Point&);
	std::istream& operator >> (std::istream&, Point&);
}
