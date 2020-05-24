#include "my_avl_tree.h"
#include <iostream>
#include <vector>
#include <ctime>
#include "my_point.h"

using namespace tdp;

namespace avl
{	
	Avl_node::Avl_node()
	{
		point = Point();
		height = 0;
		left = nullptr;
		right = nullptr;
	}
	Avl_node::Avl_node(Point point)
	{
		this->point = point;
		height = 1;
		left = nullptr;
		right = nullptr;
	}	
	Avl_tree::Avl_tree()
	{
		root = nullptr;
		size = 0;
	}
	int Avl_tree::set_height(Avl_node* node)
	{
		if (!node) return 0;
		int left_height = set_height(node->left);
		int right_height = set_height(node->right);
		node->height = (left_height > right_height) ? left_height : right_height;
		node->height++;

		return node->height;
	}
	int Avl_tree::get_height(Avl_node* node)
	{
		if (!node) return 0;

		return node->height;
	}
	Avl_node* Avl_tree::rotate_right(Avl_node* node)
	{
		Avl_node* new_node = node->left;
		node->left = new_node->right;
		new_node->right = node;

		return new_node;
	}
	Avl_node* Avl_tree::rotate_left(Avl_node* node)
	{
		Avl_node* new_node = node->right;
		node->right = new_node->left;
		new_node->left = node;

		return new_node;
	}
	int Avl_tree::balance_factor(Avl_node* node)
	{
		if (!node) return 0;

		return get_height(node->right) - get_height(node->left);
	}
	Avl_node* Avl_tree::balance(Avl_node* node)
	{
		int temp = set_height(node);
		int factor = balance_factor(node);

		if (factor >= 2)
		{
			if (balance_factor(node->right) < 0)
			{
				node->right = rotate_right(node->right);
			}
				
			return rotate_left(node);
		}
		if (factor <= -2)
		{
			if (balance_factor(node->left) > 0)
			{
				node->left = rotate_left(node->left);
			}
				
			return rotate_right(node);
		}

		return node;
	}
	void Avl_tree::balance()
	{
		int temp = set_height(root);
		root = balance(root);
		temp = set_height(root);
	}
	Avl_node* Avl_tree::add_item_current(Avl_node* node, Point point)
	{
		if (!node) return new Avl_node(point);
		if (point < node->point)
		{
			node->left = add_item_current(node->left, point);
		}			
		else
		{
			node->right = add_item_current(node->right, point);
		}
			
		return balance(node);		
	}
	void Avl_tree::add_item(Point point)
	{
		size++;
		if (!root)
		{
			root = new Avl_node(point);
			return;
		}
		root = add_item_current(root, point);
		balance();
	}
	void Avl_tree::write_current(Avl_node* node, std::size_t& index)
	{
		if (!node) return;
		write_current(node->left, index);
		std::cout << index << "." << node->point << std::endl;
		index++;
		write_current(node->right, index);
	}
	void Avl_tree::write() 
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
	void Avl_tree::remove_children(Avl_node* node)
	{
		if (!node) return;
		if (node->left)
		{
			remove_children(node->left);
			delete node->left;
			node->left = nullptr;
		}
		if (node->right)
		{
			remove_children(node->right);
			delete node->right;
			node->right = nullptr;
		}
	}
	Avl_node* Avl_tree::find_min_node(Avl_node* node)
	{
		if (node->left)
		{
			return find_min_node(node->left);
		}
		return node;
	}
	Avl_node* Avl_tree::remove_min_node(Avl_node* node)
	{
		if (!node->left)
		{
			return node->right;
		}			
		node->left = remove_min_node(node->left);

		return balance(node);
	}
	Avl_node* Avl_tree::edit_tree(Avl_node* node)
	{
		size--;
		Avl_node* left_node = node->left;
		Avl_node* right_node = node->right;
		delete node;
		if (!right_node) return left_node;
		Avl_node* min_node = find_min_node(right_node);
		min_node->right = remove_min_node(right_node);
		min_node->left = left_node;

		return balance(min_node);
	}
	Avl_node* Avl_tree::remove_item_current(Avl_node* node, Point point, bool& removed)
	{
		if (!node) return nullptr;
		node->left = remove_item_current(node->left, point, removed);
		if(removed) return node;
		if (node->point == point)
		{		
			removed = true;
			return edit_tree(node);
		}
		if (node->point > point) return node;
		node->right = remove_item_current(node->right, point, removed);

		return node;
	}
	bool Avl_tree::remove_item(Point point)
	{
		bool removed = false;
		root = remove_item_current(root, point, removed);
		balance();

		return removed;
	}
	Avl_node* Avl_tree::remove_item_current(Avl_node* node, std::size_t& current, std::size_t index)
	{
		if (!node) return nullptr;
		node->left = remove_item_current(node->left, current, index);
		if (current == index)
		{
			current++;
			return edit_tree(node);
		}
		if (current > index) return node;
		current++;
		node->right = remove_item_current(node->right, current, index);

		return node;
	}
	bool Avl_tree::remove_item(std::size_t index)
	{
		if (index >= size) return false;
		std::size_t current = 0;
		root = remove_item_current(root, current, index);
		balance();

		return (current < size);
	}
	void Avl_tree::find_items_current(Avl_node* node, Point point, std::vector<Item>& items, std::size_t& index)
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
	std::vector<Item> Avl_tree::find_items(Point point)
	{
		std::vector<Item> items;
		std::size_t index = 0;
		find_items_current(root, point, items, index);
		return items;
	}
	void Avl_tree::find_items_current(Avl_node* node, Point begin_point, Point end_point, std::vector<Item>& items, std::size_t& index)
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
	std::vector<Item> Avl_tree::find_items(Point begin_point, Point end_point)
	{
		std::vector<Item> items;
		std::size_t index = 0;
		find_items_current(root, begin_point, end_point, items, index);
		return items;
	}
	void Avl_tree::random_generator(std::size_t number_of_items, double max_value)
	{
		clear();
		srand(unsigned(time(0)));
		for (std::size_t i = 0; i < number_of_items; i++)
		{			
			add_item(Point(max_value));
		}
	}
	bool Avl_tree::find_point(Avl_node* node, std::size_t index, Point& point, std::size_t& current)
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
	double Avl_tree::find_distance_between_two_points(std::size_t first_index, std::size_t second_index)
	{
		if ((first_index >= size) || (second_index >= size)) return -1;
		std::size_t first_current = 0, second_current = 0;
		Point first_point, second_point;
		if (!find_point(root, first_index, first_point, first_current) || !find_point(root, second_index, second_point, second_current)) return -1;
		return find_distance(first_point, second_point);
	}
	void Avl_tree::find_distance_between_adjacent_points()
	{
		std::cout << "\nDistance between adjacent points:" << std::endl;
		for (std::size_t i = 0; i < size - 1; i++)
		{
			std::cout << i << " -> " << i + 1 << " = " << find_distance_between_two_points(i, i + 1) << std::endl;
		}
	}
	Point Avl_tree::read_file(std::size_t index, const std::string& path)
	{
		Point point;
		point.read_from_file(path, index);
		add_item(point);

		return point;
	}
	bool Avl_tree::append_file_current(Avl_node* node, std::size_t index, std::size_t& current, const std::string& path)
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
	bool Avl_tree::append_file(std::size_t index, const std::string& path)
	{
		if (index >= size) return false;
		std::size_t current = 0;
		return append_file_current(root, index, current, path);
	}
	bool Avl_tree::find_length_and_area_of_circle(std::size_t index_of_centre, std::size_t index_of_anypoint)
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
	void Avl_tree::clear()
	{
		if (!root) return;
		remove_children(root);
		delete root;
		root = nullptr;
		size = 0;
	}
	void Avl_tree::copy_tree_current(Avl_node* node)
	{
		if (!node) return;
		add_item(node->point);
		copy_tree_current(node->left);
		copy_tree_current(node->right);
	}
	Avl_tree::Avl_tree(Avl_tree& copy_tree)
	{
		root = nullptr;
		size = 0;
		copy_tree_current(copy_tree.root);
	}
	std::size_t Avl_tree::count_size_of_memory()
	{
		std::size_t memory_size = 0;
		memory_size += size * sizeof(Avl_node*);

		return memory_size;
	}
	std::size_t Avl_tree::get_size()
	{
		return size;
	}
}