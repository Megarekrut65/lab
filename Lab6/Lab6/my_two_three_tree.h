#pragma once
#include "my_two_three_tree.h"
#include <iostream>
#include <vector>
#include <ctime>
#include "my_point.h"

using namespace tdp;

namespace ttt//two-three tree
{
	struct Tree_node
	{
		const std::size_t max_size = 4;
		Tree_node* parent;
		Tree_node* left;
		Tree_node* centre;
		Tree_node* right;
		std::size_t length;
		Point* points;
		Tree_node();
		Tree_node(Tree_node*, Point);
	};
	struct Two_three_tree
	{
	private:
		void add_item_current(Tree_node*, Point);
		void write_current(Tree_node*, std::size_t&);
		void remove_children(Tree_node*);
		Tree_node* delete_item(Tree_node*);
		void update_centre_node(Tree_node*);
		Point max_point(Tree_node*);
		bool remove_item_current(Tree_node*, Point);
		bool remove_item_current(Tree_node*, std::size_t&, std::size_t);
		//void find_items_current(Tree_node*, Point, std::vector<Item>&, std::size_t&);
		//void find_items_current(Tree_node*, Point, Point, std::vector<Item>&, std::size_t&);
		//bool find_point(Tree_node*, std::size_t, Point&, std::size_t&);
		//bool append_file_current(Tree_node*, std::size_t, std::size_t&, const std::string&);
		Tree_node* find_left(Tree_node*);
		Tree_node* find_right(Tree_node*);
		//Tree_node* remove_min_node(Tree_node*);
		//Tree_node* edit_tree(Tree_node*);
		//int set_height(Tree_node*);
		//int get_height(Tree_node*);
		//Tree_node* rotate_right(Tree_node*);
		//Tree_node* rotate_left(Tree_node*);
		//Tree_node* balance(Tree_node*);
		//int balance_factor(Tree_node*);
		//void balance();
	public:
		Tree_node* root;
		std::size_t size;

		Two_three_tree();
		void add_item(Point);
		void write();
		bool remove_item(Point);
		bool remove_item(std::size_t);
		//std::vector<Item> find_items(Point);
		//std::vector<Item> find_items(Point, Point);
		void random_generator(std::size_t, double);
		//double find_distance_between_two_points(std::size_t, std::size_t);
		//void find_distance_between_adjacent_points();
		//void read_file(std::size_t);
		//bool append_file(std::size_t);
		//bool find_length_and_area_of_circle(std::size_t, std::size_t);
		void clear();
	};
}
