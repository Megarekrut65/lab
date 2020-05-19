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
		children = new Tree_node* [max_size];
		for (std::size_t i = 0; i < max_size; i++) children[i] = nullptr;
		length = 0;
		points = new Point[2];
		for (std::size_t i = 0; i < 2; i++) points[i] = Point();
	}
	Tree_node::Tree_node(Tree_node* parent, Point point)
	{		
		this->parent = parent;
		children = new Tree_node * [max_size];
		for (std::size_t i = 0; i < max_size; i++) children[i] = nullptr;
		length = 0;
		points = new Point[2];
		points[0] = point;
		points[1] = Point();
	}
	void Tree_node::add_child(Tree_node* child)
	{
		std::cout << "\nL: " << length << std::endl;
		child->points[0].write();
		if (length > 3) return;
		std::size_t i = length;
		while(i != 0)
		{
			if (child < children[i - 1])
			{
				children[i] = children[i - 1];
			}
			else
			{
				break;
			}
			i--;
		}
		children[i] = child;
		length++;
		if (length > 2) points[1] = children[1]->points[0];
	}
	Two_three_tree::Two_three_tree()
	{
		root = nullptr;
		size = 0;
	}
	/*int Two_three_tree::set_height(Tree_node* node)
	{
		if (!node) return 0;
		int left_height = set_height(node->left);
		int right_height = set_height(node->right);
		node->height = (left_height > right_height) ? left_height : right_height;
		node->height++;

		return node->height;
	}*/
	/*int Two_three_tree::get_height(Tree_node* node)
	{
		if (!node) return 0;

		return node->height;
	}*/
	/*Tree_node* Two_three_tree::rotate_right(Tree_node* node)
	{
		Avl_node* new_node = node->left;
		node->left = new_node->right;
		new_node->right = node;

		return new_node;
	}*/
	/*Tree_node* Two_three_tree::rotate_left(Tree_node* node)
	{
		Avl_node* new_node = node->right;
		node->right = new_node->left;
		new_node->left = node;

		return new_node;
	}*/
	/*int Two_three_tree::balance_factor(Tree_node* node)
	{
		if (!node) return 0;

		return get_height(node->right) - get_height(node->left);
	}*/
	/*Tree_node* Two_three_tree::balance(Tree_node* node)
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
	}*/
	/*void Two_three_tree::balance()
	{
		int temp = set_height(root);
		root = balance(root);
		temp = set_height(root);
	}*/
	void Two_three_tree::add_item_current(Tree_node* node, Point point)
	{
		if (!node) return;
		if (node->length < 3)
		{
			node->add_child(new Tree_node(node, point));
			return;
		}
		if (node->points[1] < point) add_item_current(node->children[2], point);
		else if (node->points[0] < point) add_item_current(node->children[1], point);
		else add_item_current(node->children[0], point);
	}
	/*void Two_three_tree::split_parent(Tree_node* parent)
	{
		if (parent->length <= 3) return;
		Tree_node* new_node = parent->children[3];
		new_node->add_child(parent->children[2]);
		parent->children[2]->parent = new_node;
		parent->children[2] = nullptr;
		parent->children[3] = nullptr;
		parent->length = 2;
		parent->points[1] = Point();		
		if (parent->parent)
		{
			new_node->parent = parent->parent;
			parent->parent->add_child(new_node);
			split_parent(parent->parent);
			return;
		}
		new_node->parent = parent;
		parent->add_child(new_node);
		Tree_node* new_node = new Tree_node(parent->parent, parent->children[2]->points[0]);
		new_node->add_child(parent->children[2]);
		new_node->add_child(parent->children[3]);
		parent->children[2]->parent = new_node;
		parent->children[3]->parent = new_node;
		parent->length = 2;
		parent->children[2] = nullptr;
		parent->children[3] = nullptr;
		if (parent->parent)
		{
			parent->parent->add_child(new_node);
			split_parent(parent->parent);
			return;
		}
		Tree_node* node = root;
		root.sons[0] = t;
		root.sons[1] = a;
		t.parent = root;
		a.parent = root;
		root.length = 2;
	}*/
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
		write_current(node->children[0], index);
		std::cout << index << ".";
		node->points[0].write();
		index++;
		write_current(node->children[1], index);
		write_current(node->children[2], index);
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
	/*void Two_three_tree::remove_children(Tree_node* node)
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
	}*/
	/*Tree_node* Two_three_tree::find_min_node(Tree_node* node)
	{
		if (node->left)
		{
			return find_min_node(node->left);
		}
		return node;
	}*/
	/*Tree_node* Two_three_tree::remove_min_node(Tree_node* node)
	{
		if (!node->left)
		{
			return node->right;
		}
		node->left = remove_min_node(node->left);

		return balance(node);
	}*/
	/*Tree_node* Two_three_tree::edit_tree(Tree_node* node)
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
	}*/
	/*Tree_node* Two_three_tree::remove_item_current(Tree_node* node, Point point, bool& removed)
	{
		if (!node) return nullptr;
		node->left = remove_item_current(node->left, point, removed);
		if (removed) return node;
		if (node->point == point)
		{
			removed = true;
			return edit_tree(node);
		}
		if (node->point > point) return node;
		node->right = remove_item_current(node->right, point, removed);

		return node;
	}*/
	/*bool Two_three_tree::remove_item(Point point)
	{
		bool removed = false;
		root = remove_item_current(root, point, removed);
		balance();

		return removed;
	}*/
	/*Tree_node* Two_three_tree::remove_item_current(Tree_node* node, std::size_t& current, std::size_t index)
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
	}*/
	/*bool Two_three_tree::remove_item(std::size_t index)
	{
		if (index >= size) return false;
		std::size_t current = 0;
		root = remove_item_current(root, current, index);
		balance();

		return (current < size);
	}*/
	void Two_three_tree::find_items_current(Tree_node* node, Point point, std::vector<Item>& items, std::size_t& index)
	{
		if (!node) return;
		if (point < node->points[0]) return;
		if (point == node->points[0]) items.push_back(Item(point, index++));
		if (node->length <= 2)
		{			
			if (point < node->points[0])
			{
				find_items_current(node->children[0], point, items, index);
			}
			find_items_current(node->children[1], point, items, index);
			return;
		}
		if (point == node->points[1]) items.push_back(Item(point, index++));
		if (node->points[1] < point)
		{
			find_items_current(node->children[2], point, items, index);
		}
		if (node->points[0] < point)
		{
			find_items_current(node->children[1], point, items, index);
		}
		find_items_current(node->children[0], point, items, index);
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
		if (end_point < node->points[0]) return;
		if (node->length <= 2)
		{
			find_items_current(node->children[0], begin_point, end_point, items, index);
			if (begin_point <= node->points[0] && end_point >= node->points[0]) items.push_back(Item(node->points[0], index++));
			find_items_current(node->children[1], begin_point, end_point, items, index);
			return;
		}		
		find_items_current(node->children[0], begin_point, end_point, items, index);
		find_items_current(node->children[1], begin_point, end_point, items, index);
		if (begin_point <= node->points[0] && end_point >= node->points[0]) items.push_back(Item(node->points[0], index++));
		if (begin_point <= node->points[1] && end_point >= node->points[1]) items.push_back(Item(node->points[0], index++));
		find_items_current(node->children[2], begin_point, end_point, items, index);
	}
	std::vector<Item>Two_three_tree::find_items(Point begin_point, Point end_point)
	{
		std::vector<Item> items;
		std::size_t index = 0;
		find_items_current(root, begin_point, end_point, items, index);
		return items;
	}
	/*void Two_three_tree::random_generator(std::size_t number_of_items, double max_point)
	{
		clear();
		srand(unsigned(time(0)));
		for (std::size_t i = 0; i < number_of_items; i++)
		{
			double x = max_point - rand() % long(trunc(max_point));
			double y = max_point - rand() % long(trunc(max_point));
			double z = max_point - rand() % long(trunc(max_point));
			add_item(Point(x, y, z));
		}
	}*/
	/*bool Two_three_tree::find_point(Tree_node* node, std::size_t index, Point& point, std::size_t& current)
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
	}*/
	/*double Two_three_tree::find_distance_between_two_points(std::size_t first_index, std::size_t second_index)
	{
		if ((first_index >= size) || (second_index >= size)) return -1;
		std::size_t first_current = 0, second_current = 0;
		Point first_point, second_point;
		if (!find_point(root, first_index, first_point, first_current) || !find_point(root, second_index, second_point, second_current)) return -1;
		return find_distance(first_point, second_point);
	}*/
	/*void Two_three_tree::find_distance_between_adjacent_points()
	{
		std::cout << "\nDistance between adjacent points:" << std::endl;
		for (std::size_t i = 0; i < size - 1; i++)
		{
			std::cout << i << " -> " << i + 1 << " = " << find_distance_between_two_points(i, i + 1) << std::endl;
		}
	}*/
	/*void Two_three_tree::read_file(std::size_t index)
	{
		std::string path = "date.txt";
		Point point;
		point.read_from_file(path, index);
		std::cout << point;
		add_item(point);
	}*/
	/*bool Two_three_tree::append_file_current(Tree_node* node, std::size_t index, std::size_t& current, const std::string& path)
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
	}*/
	/*bool Two_three_tree::append_file(std::size_t index)
	{
		if (index >= size) return false;
		std::string path = "date.txt";
		std::size_t current = 0;
		return append_file_current(root, index, current, path);
	}*/
	/*bool Two_three_tree::find_length_and_area_of_circle(std::size_t index_of_centre, std::size_t index_of_anypoint)
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
		std::cout << "Centre: ";
		centre.write();
		std::cout << "Radius: " << radius << std::endl;
		std::cout << "Length: " << length << std::endl;
		std::cout << "Area: " << area << std::endl;
		return true;
	}*/
	/*void Two_three_tree::clear()
	{
		remove_children(root);
		delete root;
		root = nullptr;
		size = 0;
	}*/
}