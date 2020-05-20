#pragma once
#include "my_binary_tree.h"
#include <iostream>
#include <vector>
#include <ctime>
#include "my_point.h"

using namespace tdp;

namespace binary
{
	enum class Side { CENTRE, LEFT, RIGHT };
	struct Binary_node
	{
		Binary_node* parent;
		Binary_node* left;
		Binary_node* right;
		Point point;
		Binary_node();
		Binary_node(Binary_node*, Point);
	};
	struct Binary_tree
	{
	private:
		void add_item_current(Binary_node*, Point);
		void write_current(Binary_node*, std::size_t&);
		void remove_children(Binary_node*, Side);
		bool remove_item_current(Binary_node*, Point, Side);
		bool remove_item_current(Binary_node*, std::size_t&, std::size_t, Side);
		void find_items_current(Binary_node*, Point, std::vector<Item>&, std::size_t&);
		void find_items_current(Binary_node*, Point, Point, std::vector<Item>&, std::size_t&);
		bool find_point(Binary_node*, std::size_t, Point&, std::size_t&);
		bool append_file_current(Binary_node*, std::size_t, std::size_t&, const std::string&);
		Binary_node* find_parent(Binary_node*);
		void edit_tree(Binary_node* node, Side side);
	public:
		Binary_node* root;
		std::size_t size;
		Binary_tree();
		void add_item(Point);
		void write();
		bool remove_item(Point);
		bool remove_item(std::size_t);
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