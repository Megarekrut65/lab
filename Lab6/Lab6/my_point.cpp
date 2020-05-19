#include "my_point.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>
#include "my_correct_read.h"

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
		if (items.size() == 0)
		{
			std::cout << "\nArray is empty!" << std::endl;
			return;
		}
		std::cout << "\nItem:" << std::endl;
		for (std::size_t i = 0; i < items.size(); i++)
		{
			std::cout << items[i].index << ".";
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
	double Point::fractional_part(double max_value)
	{
		double value = rand() % long(trunc(max_value));
		return value;
	}
	double Point::whole_part(double max_value)
	{
		double value = rand() % 1000;
		return value / 1000;
	}	
	int Point::sign()
	{
		int value = rand() % 2;
		if (value == 0) return 1;
		return -1;
	}
	Point::Point(double max_value)
	{
		x = sign() * (whole_part(max_value) - fractional_part(max_value));
		y = sign() * (whole_part(max_value) - fractional_part(max_value));
		z = sign() * (whole_part(max_value) - fractional_part(max_value));
	}
	void Point::write()
	{
		std::cout << "(" << this->x << ", " << this->y << ", " << this->z << ")." << std::endl;
	}
	void Point::read(const std::string& name)
	{
		std::cout << "\n" + name << std::endl;
		x = correct::read_double("the first coordinate");
		y = correct::read_double("the second coordinate");
		z = correct::read_double("the third coordinate");
	}
	void Point::append_to_file(const std::string& path)
	{
		std::ofstream fout(path, std::ios_base::app);
		fout << *this;
		fout.close();
	}
	void Point::read_from_file(const std::string& path, std::size_t index)
	{
		std::ifstream fin(path);
		for (std::size_t i = 0; i <= index; i++)
		{
			fin >> *this;
		}
		fin.close();
	}
	double find_distance(Point A, Point B)
	{
		return (sqrt(pow(A.x - B.x, 2) + pow(A.y - B.y, 2) + pow(A.z - B.z, 2)));
	}
	double find_length_of_circle(Point centre, Point anypoint)
	{
		double radius = find_distance(centre, anypoint);
		return atan(1) * 8 * radius;
	}
	double find_area_of_circle(Point centre, Point anypoint)
	{
		double radius = find_distance(centre, anypoint);
		return atan(1) * 4 * radius * radius;
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
	std::ostream& operator << (std::ostream& out, const Point& point)
	{
		return out << "(" << point.x << ", " << point.y << ", " << point.z << ")" << std::endl;
	}
	std::istream& operator >> (std::istream& in, Point& point)
	{
		char waste[4];
		in >> waste[0] >> point.x >> waste[1] >> point.y >> waste[2] >> point.z >> waste[3];
		if (!in) point = Point();
		return in;
	}
}