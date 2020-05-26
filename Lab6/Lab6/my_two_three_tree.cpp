#include "my_two_three_tree.h"
#include <iostream>
#include <vector>
#include <ctime>
#include "my_point.h"

using namespace tdp;

namespace ttt//two-three tree
{
	Tree_node::Tree_node()
	{
		parent = nullptr;
		left = nullptr;
		centre = nullptr;
		right = nullptr;		
		length = 0;
		points = new Point[2];
		for (std::size_t i = 0; i < 2; i++) points[i] = Point();
	}
	Tree_node::Tree_node(Tree_node* parent, Point point)
	{		
		this->parent = parent;
		if(parent) parent->length++;
		left = nullptr;
		centre = nullptr;
		right = nullptr;
		length = 0;
		points = new Point[2];
		points[0] = point;
		points[1] = Point();
	}	
	Two_three_tree::Two_three_tree()
	{
		root = nullptr;
		size = 0;
	}			
	void Two_three_tree::add_item_current(Tree_node* node, Point point)
	{
		if (!node) return;
		switch (node->length)
		{
		case 0:
		{
			if (node->points[0] > point) node->left = new Tree_node(node, point);
			else node->right = new Tree_node(node, point);
		}
			break;
		case 1:
		{
			if (node->points[0] > point)
			{
				if (!node->left) node->left = new Tree_node(node, point);
				else add_item_current(node->left, point);
				return;				
			}
			if (!node->right) node->right = new Tree_node(node, point);
			else add_item_current(node->right, point);
		}
			break;
		case 2:
		{
			if (node->points[0] > point)
			{
				add_item_current(node->left, point);
				return;
			}
			if (node->right->points[0] > point)
			{
				node->centre = new Tree_node(node, point);
				node->points[1] = point;
			}
			else
			{
				node->centre = node->right;
				node->points[1] = node->right->points[0];
				node->right = new Tree_node(node, point);
			}
		}
			break;
		default:
		{
			if (node->points[1] < point) add_item_current(node->right, point);
			else if (node->points[0] < point) add_item_current(node->centre, point);
			else add_item_current(node->left, point);
		}
			break;
		}			
	}
	void Two_three_tree::add_item(Point point)
	{
		size++;
		if (!root)
		{
			root = new Tree_node(nullptr, point);
			return;
		}
		add_item_current(root, point);
	}
	void Two_three_tree::write_current(Tree_node* node, std::size_t& index)
	{
		if (!node) return;
		write_current(node->left, index);
		std::cout << index << "." << node->points[0] << std::endl;
		index++;
		write_current(node->centre, index);
		write_current(node->right, index);
	}
	void Two_three_tree::write()
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
	void Two_three_tree::remove_children(Tree_node* node)
	{
		if (!node) return;
		if (node->left)
		{
			remove_children(node->left);
			delete[] node->left->points;
			delete node->left;
			node->left = nullptr;
		}
		if (node->centre)
		{
			remove_children(node->centre);
			delete[] node->centre->points;
			delete node->centre;
			node->centre = nullptr;
		}
		if (node->right)
		{
			remove_children(node->right);
			delete[] node->right->points;
			delete node->right;
			node->right = nullptr;
		}
	}
	Tree_node* Two_three_tree::find_left(Tree_node* node)
	{
		if (!node) return nullptr;
		if (node->left)
		{
			return find_left(node->left);
		}

		return node;
	}
	Tree_node* Two_three_tree::find_right(Tree_node* node)
	{
		if (!node) return nullptr;
		if (node->right)
		{
			return find_right(node->right);
		}

		return node;
	}
	Point Two_three_tree::max_point(Tree_node* node)
	{
		if (!node) return Point();
		if (node->right) return max_point(node->right);
		if (node->centre) return node->points[1];
		
		return node->points[0];
	}
	void Two_three_tree::update_centre_node(Tree_node* node)
	{
		if (!node || node->length == 0) return;
		update_centre_node(node->left);
		if (node->centre)
		{
			update_centre_node(node->centre);
			node->points[1] = max_point(node->centre);			
		}
		update_centre_node(node->right);
	}
	void Two_three_tree::edit_parent(Tree_node* node)
	{
		if (!node->parent) return;
		set_length(node->parent);
		node->parent->length--;
		if (node->parent->length == 2)
		{
			if (node->parent->centre == node) return;
			if (node->parent->right == node)
			{
				node->parent->right = node->parent->centre;
				return;
			}
			add_item_current(node->parent->centre, node->parent->points[0]);
			node->parent->points[0] = node->parent->centre->points[0];
			node->parent->left = node->parent->centre;
			node->parent->centre = nullptr;
		}
	}
	void Two_three_tree::set_length(Tree_node* node)
	{
		if (node->left && node->centre && node->right) node->length = 3;
		if (!node->left && node->centre && node->right) node->length = 2;
		if (node->left && !node->centre && node->right) node->length = 2;
		if (node->left && node->centre && !node->right) node->length = 2;
		if (!node->left && !node->centre && node->right) node->length = 1;
		if (!node->left && node->centre && !node->right) node->length = 1;
		if (node->left && !node->centre && !node->right) node->length = 1;
		if (!node->left && !node->centre && !node->right) node->length = 0;
	}
	Tree_node* Two_three_tree::delete_item(Tree_node* node)
	{
		if (!node) return nullptr;
		size--;
		Tree_node* new_node = nullptr;
		set_length(node);
		switch (node->length)
		{
		case 0:;
		break;
		case 1:
		{
			if (node->left) new_node = node->left;
			else if (node->right) new_node = node->right;
			else if (node->centre) new_node = node->centre;
		}
		break;
		case 2:
		{
			if (node->left && node->right)
			{
				Tree_node* new_parent = find_left(node->right);
				new_node = node->right;
				new_parent->left = node->left;
				new_parent->length++;
				node->left->parent = new_parent;
			}
			else if (node->left && node->centre)
			{
				Tree_node* new_parent = find_left(node->centre);
				new_node = node->centre;
				new_parent->left = node->left;
				new_parent->length++;
				node->left->parent = new_parent;
			}
			else if (node->centre && node->right)
			{
				Tree_node* new_parent = find_left(node->right);
				new_node = node->right;
				new_parent->left = node->centre;
				new_parent->length++;
				node->centre->parent = new_parent;
			}		
		}
		break;
		case 3:
		{
			if (node->left && node->right && node->centre)
			{
				Tree_node* left_node = find_left(node->centre);
				Tree_node* right_node = find_right(node->centre);
				new_node = node->centre;
				left_node->left = node->left;
				left_node->left->parent = left_node;
				left_node->length++;
				right_node->right = node->right;
				right_node->right->parent = right_node;
				right_node->length++;
			}		
		}
		break;
		default:
		{
			return node;
		}
		break;
		}
		node->left = nullptr;
		node->right = nullptr;
		node->centre = nullptr;
		if (new_node) new_node->parent = node->parent;
		else if(node->parent) edit_parent(node);
		delete[] node->points;
		delete node;

		return new_node;
	}
	Tree_node* Two_three_tree::remove_item_current(Tree_node* node, Point point)
	{
		if (!node) return nullptr;
		node->left = remove_item_current(node->left, point);
		if (node->points[0] == point)
		{
			return delete_item(node);
		}
		if(node->points[0] > point) return node;
		node->centre =remove_item_current(node->centre, point);
		node->right = remove_item_current(node->right, point);

		return node;
	}
	bool Two_three_tree::remove_item(Point point)
	{
		std::size_t size = this->size;
		root = remove_item_current(root, point);
		if (this->size < size)
		{
			update_centre_node(root);
			return true;
		}

		return false;
	}
	Tree_node* Two_three_tree::remove_item_current(Tree_node* node, std::size_t& current, std::size_t index)
	{
		if (!node) return nullptr;
		node->left = remove_item_current(node->left, current, index);
		if (current == index)
		{
			current++;
			return delete_item(node);
		}
		current++;
		if (current > index) return node;
		node->centre = remove_item_current(node->centre, current, index);
		node->right = remove_item_current(node->right, current, index);

		return node;
	}
	bool Two_three_tree::remove_item(std::size_t index)
	{
		if (index >= size) return false;
		std::size_t size = this->size;
		std::size_t current = 0;
		root = remove_item_current(root, current, index);
		if (this->size < size)
		{
			update_centre_node(root);
			return true;
		}

		return false;
	}
	void Two_three_tree::find_items_current(Tree_node* node, Point point, std::vector<Item>& items, std::size_t& index)
	{
		if (!node) return;			
		find_items_current(node->left, point, items, index);
		if (point < node->points[0]) return;
		if (point == node->points[0]) items.push_back(Item(point, index++));
		find_items_current(node->centre, point, items, index);
		find_items_current(node->right, point, items, index);
	}
	std::vector<Item> Two_three_tree::find_items(Point point)
	{
		std::vector<Item> items;
		std::size_t index = 0;
		find_items_current(root, point, items, index);
		return items;
	}
	void Two_three_tree::find_items_current(Tree_node* node, Point begin_point, Point end_point, std::vector<Item>& items, std::size_t& index)
	{
		if (!node) return;
		find_items_current(node->left, begin_point, end_point, items, index);
		if (end_point < node->points[0]) return;
		if (begin_point <= node->points[0] && end_point >= node->points[0]) items.push_back(Item(node->points[0], index++));
		find_items_current(node->centre, begin_point, end_point, items, index);
		find_items_current(node->right, begin_point, end_point, items, index);
	}
	std::vector<Item>Two_three_tree::find_items(Point begin_point, Point end_point)
	{
		std::vector<Item> items;
		std::size_t index = 0;
		find_items_current(root, begin_point, end_point, items, index);
		return items;
	}
	void Two_three_tree::random_generator(std::size_t number_of_items, double max_value)
	{
		clear();
		srand(unsigned(time(0)));
		for (std::size_t i = 0; i < number_of_items; i++)
		{
			add_item(Point(max_value));
		}
	}
	bool Two_three_tree::find_point(Tree_node* node, std::size_t index, Point& point, std::size_t& current)
	{
		if (!node) return false;
		if (find_point(node->left, index, point, current)) return true;
		if (index == current)
		{
			point = node->points[0];
			return true;
		}
		current++;
		if (current > index) return false;
		if (find_point(node->centre, index, point, current)) return true;
		if (find_point(node->right, index, point, current)) return true;
		return false;
	}
	double Two_three_tree::find_distance_between_two_points(std::size_t first_index, std::size_t second_index)
	{
		if ((first_index >= size) || (second_index >= size)) return -1;
		std::size_t first_current = 0, second_current = 0;
		Point first_point, second_point;
		if (!find_point(root, first_index, first_point, first_current) || !find_point(root, second_index, second_point, second_current)) return -1;
		return find_distance(first_point, second_point);
	}
	void Two_three_tree::find_distance_between_adjacent_points()
	{
		if (size < 2)
		{
			std::cout << "\nThere are not enough points!" << std::endl;
			return;
		}
		std::cout << "\nDistance between adjacent points:" << std::endl;
		for (std::size_t i = 0; i < size - 1; i++)
		{
			std::cout << i << " -> " << i + 1 << " = " << find_distance_between_two_points(i, i + 1) << std::endl;
		}
	}
	Point Two_three_tree::read_file(std::size_t index, const std::string& path)
	{
		Point point;
		point.read_from_file(path, index);
		add_item(point);
		return point;
	}
	bool Two_three_tree::append_file_current(Tree_node* node, std::size_t index, std::size_t& current, const std::string& path)
	{
		if (!node) return false;
		if (append_file_current(node->left, index, current, path)) return true;
		if (index == current)
		{
			node->points[0].append_to_file(path);
			return true;
		}
		current++;
		if (current > index) return false;
		if (append_file_current(node->centre, index, current, path)) return true;
		if (append_file_current(node->right, index, current, path)) return true;
		return false;
	}
	bool Two_three_tree::append_file(std::size_t index, const std::string& path)
	{
		if (index >= size) return false;
		std::size_t current = 0;
		return append_file_current(root, index, current, path);
	}
	bool Two_three_tree::find_length_and_area_of_circle(std::size_t index_of_centre, std::size_t index_of_anypoint)
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
	void Two_three_tree::clear()
	{
		if (!root) return;
		remove_children(root);
		delete[] root->points;
		delete root;
		root = nullptr;
		size = 0;
	}
	std::size_t Two_three_tree::count_size_of_memory()
	{
		std::size_t memory_size = 0;
		memory_size += size * sizeof(Tree_node*) + sizeof(size);

		return memory_size;
	}
	std::size_t Two_three_tree::get_size()
	{
		return size;
	}
	Two_three_tree::Two_three_tree(std::vector<Point>& array)
	{
		root = nullptr;
		size = 0;
		for (std::size_t i = 0; i < array.size(); i++)
		{
			add_item(array[i]);
		}
	}
}