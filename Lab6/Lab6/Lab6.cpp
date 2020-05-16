#include <iostream>
#include "my_linked_list.h"
#include "my_array_list.h"
#include "my_binary_tree.h"
#include "my_avl_tree.h"
#include <vector>
#include <fstream>

using namespace tdp;
using namespace avl;

int main()
{
	Avl_tree list;
	list.add_item(Point(100, 1, 1));
	list.add_item(Point(2, 1, 1));
	list.add_item(Point(7, 2, 5));
	list.add_item(Point(6, 2, 3));
	list.add_item(Point(3, 2, 3));
	list.add_item(Point(9, 1, 1));
	list.add_item(Point(4, 1, 1));
	list.write();
	//list.find_length_and_area_of_circle(0, 3);
	//list.append_file(3);
	//std::cout << list.find_distance_between_two_points(1, 6);
	//list.find_distance_between_adjacent_points();
	/*for (std::size_t j = 0; j < 15; j++)
	{
		list.clear();
		list.random_generator(30, 100);
		list.write();
		for (std::size_t i = 0; i < 15; i++) list.remove_item(0);
		list.write();
	}	*/
	/*list.remove_item(2);
	list.remove_item(3);
	list.remove_item(0);
	list.write();
	list.add_item(Point(1, 2, 3));
	list.add_item(Point(7, 2, 3));
	list.add_item(Point(0, 2, 3));
	list.add_item(Point(1, 2, 3));
	list.write();*/
	/*std::vector<Item> items = list.find_items(Point(3, 2, 3), Point(10,2,1));
	write_items(items);*/
	return 0;
}
