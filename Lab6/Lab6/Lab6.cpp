#include <iostream>
#include "my_linked_list.h"
#include "my_array_list.h"
#include "my_binary_tree.h"
#include <vector>
#include <fstream>

using namespace tdp;
using namespace binary;

int main()
{
	Binary_tree list;
	list.add_item(Point(1, 2, 3));
	list.add_item(Point(11, 2, 3));
	list.add_item(Point(7, 2, 5));
	list.add_item(Point(1, 2, 3));
	list.add_item(Point(7, 2, 3));
	list.add_item(Point(0, 2, 3));
	list.add_item(Point(1, 2, 3));
	list.write();
	list.clear();
	list.write();
	list.add_item(Point(1, 2, 3));
	list.add_item(Point(7, 2, 3));
	list.add_item(Point(0, 2, 3));
	list.add_item(Point(1, 2, 3));
	list.write();
	return 0;
}
