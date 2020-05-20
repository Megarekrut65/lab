#include "my_binary_tree.h"
#include <iostream>
#include <vector>
#include <ctime>
#include "my_point.h"

namespace binary
{	
	Binary_node::Binary_node()
	{
		parent = nullptr;
		left = nullptr;
		right = nullptr;
		point = Point();
	}
	Binary_node::Binary_node(Binary_node* parent, Point point)
	{
		this->parent = parent;
		this->left = nullptr;
		this->right = nullptr;
		this->point = point;
	}
	Binary_tree::Binary_tree()
	{
		root = nullptr;
		size = 0;
	}
	void Binary_tree::add_item_current(Binary_node* node, Point point)
	{
		if (!node) return;
		if (point < node->point)
		{
			if (!node->left)
			{
				node->left = new Binary_node(node, point);
				return;
			}
			add_item_current(node->left, point);
		}
		else
		{
			if (!node->right)
			{
				node->right = new Binary_node(node, point);
				return;
			}
			add_item_current(node->right, point);
		}
	}
	void Binary_tree::add_item(Point point)
	{
		size++;
		if (!root)
		{
			root = new Binary_node(nullptr, point);
			return;
		}
		add_item_current(root, point);
	}
	void Binary_tree::write_current(Binary_node* node, std::size_t& index)
	{
		if (!node) return;
		write_current(node->left, index);
		std::cout << index << "." << node->point << std::endl;
		index++;
		write_current(node->right, index);
	}
	void Binary_tree::write()
	{
		if (!root)
		{
			std::cout << "\nTree is empty!" << std::endl;
			return;
		}
		std::size_t index = 0;
		std::cout << "\nTree:\n";
		write_current(root, index);
	}
	void Binary_tree::remove_children(Binary_node* node, Side side)
	{
		if (!node) return;
		if (node->left)
		{
			remove_children(node->left, Side::LEFT);
		}
		if (node->right)
		{
			remove_children(node->right, Side::RIGHT);
		}
		switch (side)
		{
		case Side::CENTRE: root = nullptr;
			break;
		case Side::LEFT: node->parent->left = nullptr;
			break;
		case Side::RIGHT: node->parent->right = nullptr;
			break;
		}	
		delete node;
		node = nullptr;
	}
	Binary_node* Binary_tree::find_parent(Binary_node* node)
	{
		if (node->left)
		{
			return find_parent(node->left);
		}
		return node;
	}
	void Binary_tree::edit_tree(Binary_node* node, Side side)
	{
		size--;
		Binary_node* new_parent = node->parent;
		Binary_node* new_node = node->left;
		if (node->left)
		{
			if (node->right)
			{
				new_node = node->right;
				new_parent = find_parent(node->right);
				new_parent->left = node->left;	
				new_node->parent = node->parent;
			}			
			node->left->parent = new_parent;
		}
		else
		{
			if (node->right)
			{
				new_node = node->right;				
				new_node->parent = new_parent;				
			}	
			else
			{
				new_node = nullptr;
				new_parent = nullptr;
			}
		}
		if (side == Side::LEFT) node->parent->left = new_node;
		if (side == Side::RIGHT) node->parent->right = new_node;
		if (root == node)
		{
			root = new_node;
		}
		node->left = nullptr;
		node->right = nullptr;
		delete node;
		node = nullptr;
	}
	bool Binary_tree::remove_item_current(Binary_node* node, Point point, Side side)
	{
		if (!node) return false;
		if (remove_item_current(node->left, point, Side::LEFT)) return true;
		if (node->point == point)
		{
			edit_tree(node, side);
			return true;
		}
		if (node->point > point) return false;
		if(remove_item_current(node->right, point, Side::RIGHT)) return true;
		return false;
	}
	bool Binary_tree::remove_item(Point point)
	{			
		return remove_item_current(root, point, Side::CENTRE);
	}
	bool Binary_tree::remove_item_current(Binary_node* node, std::size_t& current, std::size_t index, Side side)
	{
		if (!node) return false;
		if (remove_item_current(node->left, current, index, Side::LEFT)) return true;		
		if (current == index)
		{
			edit_tree(node, side);
			return true;
		}
		current++;
		if (current > index) return false;
		if (remove_item_current(node->right, current, index, Side::RIGHT)) return true;
		
		return false;
	}
	bool Binary_tree::remove_item(std::size_t index)
	{
		if (index >= size) return false;
		std::size_t current = 0;

		return remove_item_current(root, current, index, Side::CENTRE);
	}
	void Binary_tree::find_items_current(Binary_node* node, Point point, std::vector<Item>& items, std::size_t& index)
	{
		if (!node) return;
		find_items_current(node->left, point, items, index);
		if (node->point == point)
		{
			items.push_back(Item(point, index));
		}
		index++;
		if (node->point > point) return;
		find_items_current(node->right, point, items, index);
	}
	std::vector<Item> Binary_tree::find_items(Point point)
	{
		std::vector<Item> items;
		std::size_t index = 0;
		find_items_current(root, point, items, index);
		return items;
	}
	void Binary_tree::find_items_current(Binary_node* node, Point begin_point, Point end_point, std::vector<Item>& items, std::size_t& index)
	{
		if (!node) return;
		find_items_current(node->left, begin_point, end_point, items, index);
		if (node->point >= begin_point && node->point <= end_point)
		{
			items.push_back(Item(node->point, index));
		}
		index++;
		if (node->point > end_point) return;
		find_items_current(node->right, begin_point, end_point, items, index);
	}
	std::vector<Item> Binary_tree::find_items(Point begin_point, Point end_point)
	{
		std::vector<Item> items;
		std::size_t index = 0;
		find_items_current(root, begin_point, end_point, items, index);
		return items;
	}
	void Binary_tree::random_generator(std::size_t number_of_items, double max_value)
	{
		clear();
		srand(unsigned(time(0)));
		for (std::size_t i = 0; i < number_of_items; i++)
		{
			add_item(Point(max_value));
		}
	}
	bool Binary_tree::find_point(Binary_node* node, std::size_t index, Point& point, std::size_t& current)
	{
		if (!node) return false;
		if (find_point(node->left, index, point, current)) return true;
		if (index == current)
		{
			point = node->point;
			return true;
		}
		current++;
		if (current > index) return false;
		if (find_point(node->right, index, point, current)) return true;
		return false;
	}
	double Binary_tree::find_distance_between_two_points(std::size_t first_index, std::size_t second_index)
	{
		if ((first_index >= size) || (second_index >= size)) return -1;
		std::size_t first_current = 0, second_current = 0;
		Point first_point, second_point;
		if (!find_point(root, first_index, first_point, first_current) || !find_point(root, second_index, second_point, second_current)) return -1;
		return find_distance(first_point, second_point);
	}
	void Binary_tree::find_distance_between_adjacent_points()
	{
		std::cout << "\nDistance between adjacent points:" << std::endl;
		for (std::size_t i = 0; i < size - 1; i++)
		{
			std::cout << i << " -> " << i + 1 << " = " << find_distance_between_two_points(i, i + 1) << std::endl;
		}
	}
	Point Binary_tree::read_file(std::size_t index, const std::string& path)
	{
		Point point;
		point.read_from_file(path, index);
		add_item(point);

		return point;
	}
	bool Binary_tree::append_file_current(Binary_node* node, std::size_t index, std::size_t& current, const std::string& path)
	{
		if (!node) return false;
		if (append_file_current(node->left, index, current, path)) return true;
		if (index == current)
		{
			node->point.append_to_file(path);
			return true;
		}
		current++;
		if (current > index) return false;
		if (append_file_current(node->right, index, current, path)) return true;
		return false;
	}
	bool Binary_tree::append_file(std::size_t index, const std::string& path)
	{
		if (index >= size) return false;
		std::size_t current = 0;
		return append_file_current(root, index, current, path);
	}
	bool Binary_tree::find_length_and_area_of_circle(std::size_t index_of_centre, std::size_t index_of_anypoint)
	{
		if ((index_of_centre >= size) || (index_of_anypoint >= size)) return false;
		std::size_t index = 0;
		Point centre, anypoint;
		std::size_t centre_current = 0, anypoint_current = 0;
		if (!find_point(root, index_of_centre, centre, centre_current) 
			|| !find_point(root, index_of_anypoint, anypoint, anypoint_current)) return false;
		double length = find_length_of_circle(centre, anypoint);
		double area = find_area_of_circle(centre, anypoint);
		double radius = find_distance(centre, anypoint);
		std::cout << "\nCircle.\n";
		std::cout << "Centre: " << centre << std::endl;
		std::cout << "Radius: " << radius << std::endl;
		std::cout << "Length: " << length << std::endl;
		std::cout << "Area: " << area << std::endl;
		return true;
	}
	void Binary_tree::clear()
	{
		remove_children(root, Side::CENTRE);
		size = 0;
	}
}