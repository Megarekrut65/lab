#include <iostream>
#include "my_linked_list.h"
#include <vector>

using namespace tdp;
using namespace list;

int main()
{
	Linked_list list;
	list.add_item(Point(10, 3, 2));
	list.add_item(Point(2, 3, 2));
	list.add_item(Point(11, 3, 2));
	list.add_item(Point(10, 3, 2));
	list.add_item(Point(10, 3, 3));
	list.add_item(Point(10, 3, 1));
	list.add_item(Point(0, 3, 1));
	list.add_item(Point(0, 2, 11));
	list.write();
	std::vector<Item> items = list.find_item(Point(0, 2, 2), Point(10, 3, 2));
	write_items(items);
	return 0;
}
