#include <iostream>
#include "my_linked_list.h"
#include "my_array_list.h"
#include <vector>
#include <fstream>

using namespace tdp;
using namespace list;
using namespace array;

int main()
{
	Array_list list;
	list.random_generator(14, 20);
	list.write();
	list.find_distance_between_adjacent_points();
	return 0;
}
