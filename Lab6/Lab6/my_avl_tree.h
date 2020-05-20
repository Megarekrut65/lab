#pragma once
#include "my_avl_tree.h"
#include <iostream>
#include <vector>
#include <ctime>
#include "my_point.h"

using namespace tdp;

namespace avl
{
	struct Avl_node
	{
		Point point;
		int height;
		Avl_node* left;
		Avl_node* right;

		Avl_node();
		Avl_node(Point);
	};
	struct Avl_tree
	{
	private:
		Avl_node* add_item_current(Avl_node*, Point);
		void write_current(Avl_node*, std::size_t&);
		void remove_children(Avl_node*);
		Avl_node* remove_item_current(Avl_node*, Point, bool&);
		Avl_node* remove_item_current(Avl_node*, std::size_t&, std::size_t);
		void find_items_current(Avl_node*, Point, std::vector<Item>&, std::size_t&);
		void find_items_current(Avl_node*, Point, Point, std::vector<Item>&, std::size_t&);
		bool find_point(Avl_node*, std::size_t, Point&, std::size_t&);
		bool append_file_current(Avl_node*, std::size_t, std::size_t&, const std::string&);
		Avl_node* find_min_node(Avl_node*);
		Avl_node* remove_min_node(Avl_node*);
		Avl_node* edit_tree(Avl_node*);
		int set_height(Avl_node*);
		int get_height(Avl_node*);
		Avl_node* rotate_right(Avl_node*);
		Avl_node* rotate_left(Avl_node*);
		Avl_node* balance(Avl_node*);
		int balance_factor(Avl_node*);
		void balance();
	public:
		Avl_node* root;
		std::size_t size;

		Avl_tree();
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