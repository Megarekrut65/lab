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
	struct Tree_node
	{
		Tree_node* parent;
		Tree_node* left;
		Tree_node* right;
		Point point;
		Tree_node();
		Tree_node(Tree_node*, Tree_node*, Tree_node*, Point);
	};
	struct Binary_tree
	{
	private:
		void add_item_current(Tree_node*, Point);
		void write_current(Tree_node*, std::size_t&);
		void remove_children(Tree_node*, Side);
		bool remove_item_current(Tree_node*, Point, Side);
		bool remove_item_current(Tree_node*, std::size_t&, std::size_t, Side);
		void find_items_current(Tree_node*, Point, std::vector<Item>&, std::size_t&);
		void find_items_current(Tree_node*, Point, Point, std::vector<Item>&, std::size_t&);
		bool find_point(Tree_node*, std::size_t, Point&, std::size_t&);
		bool append_file_current(Tree_node*, std::size_t, std::size_t&, const std::string&);
		void edit_tree(Tree_node* node, Side side);
	public:
		Tree_node* root;
		std::size_t size;
		Binary_tree();
		void add_item(Point);
		void write();
		bool remove_item(Point);
		bool remove_item(std::size_t);
		std::vector<Item> find_items(Point);
		std::vector<Item> find_items(Point, Point);
		void random_generator(std::size_t, std::size_t);
		double find_distance_between_two_points(std::size_t, std::size_t);
		void find_distance_between_adjacent_points();
		void read_file(std::size_t);
		bool append_file(std::size_t);
		bool find_length_and_area_of_circle(std::size_t, std::size_t);
		void clear();
	};
}