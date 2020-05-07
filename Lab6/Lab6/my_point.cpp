#include "my_point.h"
#include <iostream>
#include <vector>

namespace tdp//three-dimensional points
{
	Item::Item()
	{
		point = Point();
		index = 0;
	}
	Item::Item(Point point, std::size_t index)
	{
		this->point = point;
		this->index = index;
	}
	void write_items(std::vector<Item>& items)
	{
		std::cout << "\nItem:\nIndex -> Point" << std::endl;
		for (std::size_t i = 0; i < items.size(); i++)
		{
			std::cout << items[i].index << " -> ";
			items[i].point.write();
		}
	}
	Point::Point()
	{
		x = 0;
		y = 0;
		z = 0;
	}
	Point::Point(double x, double y, double z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
	void Point::write()
	{
		std::cout << "( " << this->x << ", " << this->y << ", " << this->z << ")." << std::endl;
	}
	bool operator < (Point A, Point B)
	{
		if (A.x < B.x) return true;
		else if (A.x > B.x) return false;
		if (A.y < B.y) return true;
		else if (A.y > B.y) return false;
		if (A.z < B.z) return true;
		else if (A.z > B.z) return false;
		return false;
	}
	bool operator > (Point A, Point B)
	{
		if (A.x > B.x) return true;
		else if (A.x < B.x) return false;
		if (A.y > B.y) return true;
		else if (A.y < B.y) return false;
		if (A.z > B.z) return true;
		else if (A.z < B.z) return false;
		return false;
	}
	bool operator <= (Point A, Point B)
	{
		if (A.x < B.x) return true;
		else if (A.x > B.x) return false;
		if (A.y < B.y) return true;
		else if (A.y > B.y) return false;
		if (A.z < B.z) return true;
		else if (A.z > B.z) return false;
		return true;
	}
	bool operator >= (Point A, Point B)
	{
		if (A.x > B.x) return true;
		else if (A.x < B.x) return false;
		if (A.y > B.y) return true;
		else if (A.y < B.y) return false;
		if (A.z > B.z) return true;
		else if (A.z < B.z) return false;
		return true;
	}
	bool operator == (Point A, Point B)
	{
		return (A.x == B.x && A.y == B.y && A.z == B.z);
	}
	bool operator != (Point A, Point B)
	{
		return (A.x != B.x || A.y != B.y || A.z != B.z);
	}
	Point operator + (Point A, Point B)
	{
		return Point(A.x + B.x, A.y + B.y, A.z + B.z);
	}
	Point operator - (Point A, Point B)
	{
		return Point(A.x - B.x, A.y - B.y, A.z - B.z);
	}
	Point operator * (Point A, Point B)
	{
		return Point(A.x * B.x, A.y * B.y, A.z * B.z);
	}
	Point operator / (Point A, Point B)
	{
		return Point(A.x / B.x, A.y / B.y, A.z / B.z);
	}
}