#include <iostream>
#include "my_linked_list.h"
#include <vector>
#include <fstream>

using namespace tdp;
using namespace list;

int main()
{
	Linked_list list;
	list.random_generator(10, 100);
	list.write();
	list.find_length_and_area_of_circle(0, 4);
	return 0;
}
