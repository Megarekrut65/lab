#pragma once
#include "my_point.h"
#include <vector>

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
	};
	struct Item
	{
		Point point;
		std::size_t index;
		Item();
		Item(Point, std::size_t);
	};
	void write_items(std::vector<Item>&);
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
}
