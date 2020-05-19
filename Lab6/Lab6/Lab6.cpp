#include <iostream>
#include "my_linked_list.h"
#include "my_array_list.h"
#include "my_binary_tree.h"
#include "my_avl_tree.h"
#include "my_two_three_tree.h"
#include "my_correct_read.h"
#include <conio.h>
#include <Windows.h>
#include <vector>
#include <fstream>

template<class T>
void add_item(T& list)
{
	tdp::Point point;
	point.read("The point:");
	list.add_item(point);
	std::cout << "\nThe point was added!" << std::endl;
}
template<class T>
void remove_by_index(T& list)
{
	std::size_t index = correct::read_size_t("the index of point");
	if (list.remove_item(index))
	{
		std::cout << "\nThe point was removed!" << std::endl;
	}
	else
	{
		std::cout << "\nThere isn't point with index: " << index << "." << std::endl;
	}
}
template<class T>
void remove_by_value(T& list)
{
	tdp::Point point;
	point.read("The point:");
	if (list.remove_item(point))
	{
		std::cout << "\nThe point was removed!" << std::endl;
	}
	else
	{
		std::cout << "\nThere is no point entered." << std::endl;
	}
}
template<class T>
void remove_item_menu(T& list)
{
	while (true)
	{
		std::cout << "\nChoose:\n1)Remove by index.\n2)Remove by value."
			<< "\n0)Back." << std::endl;
		switch (_getch())
		{
		case '1': remove_by_index(list);
			break;
		case '2': remove_by_value(list);
			break;
		case'0': return;
		default: std::cout << "\nPress the correct key!\n" << std::endl;
		}
	}
}
template<class T>
void find_by_value(T& list)
{
	tdp::Point point;
	point.read("The point:");
	std::vector<tdp::Item> items = list.find_items(point);
	tdp::write_items(items);
}
template<class T>
void find_by_begin_and_end(T& list)
{
	tdp::Point begin_point, end_point;
	while (true)
	{
		begin_point.read("Begin point:");
		end_point.read("End point:");
		if (begin_point > end_point) std::cout << "\nThe begin must be smaller than end!" << std::endl;
		else break;
	}
	std::vector<tdp::Item> items = list.find_items(begin_point, end_point);
	tdp::write_items(items);
}
template<class T>
void find_menu(T& list)
{
	while (true)
	{
		std::cout << "\nChoose:\n1)Find by value of point.\n2)Find by value of begin point and value of end point."
			<< "\n0)Back." << std::endl;
		switch (_getch())
		{
		case '1': find_by_value(list);
			break;
		case '2': find_by_begin_and_end(list);
			break;
		case'0': return;
		default: std::cout << "\nPress the correct key!\n" << std::endl;
		}
	}
}
template<class T>
void generate_random_items(T& list)
{
	std::size_t size = correct::read_size_t("number of points");
	double max = correct::read_double("maximum coordinate value");
	list.random_generator(size, max);
	std::cout << "\nThe list was created!" << std::endl;
}
template<class T>
void menu(T& list)
{
	while (true)
	{
		std::cout << "\nMenu:\n1)Add item.\n2)Remove item.\n3)Find item.\n4)Write list.\n"
			<< "5)Perform actions on items.\n6)Generate random items.\n0)Back." << std::endl;
		switch (_getch())
		{
		case '1': add_item(list);
			break;
		case '2': remove_item_menu(list);
			break;
		case '3': find_menu(list);
			break;
		case '4': list.write();
			break;
		case '5':;
			break;
		case '6': generate_random_items(list);
			break;
		case'0':
		{
			list.clear();
			return;
		}
		break;
		default: std::cout << "\nPress the correct key!\n" << std::endl;
		}
	}
}
void interactive_dialog_mode()
{
	list::Linked_list list;
	array::Array_list array;
	binary::Binary_tree binary;
	avl::Avl_tree avl_tree;
	while (true)
	{
		std::cout << "\nSelect the basis for the data structure:\n1)Linked list.\n"
			<< "2)Array list.\n3)Binary tree.\n4)Avl tree.\n5)Two-Three tree.\n0)Back." << std::endl;
		switch (_getch())
		{
		case '1': menu(list);
			break;
		case '2': menu(array);
			break;
		case '3': menu(binary);
			break;
		case '4': menu(avl_tree);
			break;
		case '5':;
			break;
		case'0':
		{
			std::cout << std::endl;
			return;
		}
		break;
		default: std::cout << "\nPress the correct key!\n" << std::endl;
		}
	}
}
void demo_mode()
{

}
void benchmark_mode()
{

	
}
int main()
{
	while (true)
	{
		std::cout << "Select the application mode:\n1)Interactive dialog mode.\n"
			<< "2)Demo mode.\n3)Automatic benchmark mode.\n0)Exit." << std::endl;
		switch (_getch())
		{
		case '1': interactive_dialog_mode();
			break;
		case '2': demo_mode();
			break;
		case '3': benchmark_mode();
			break;
		case'0':
		{
			std::cout << "\nExit..." << std::endl;
			return 0;
		}
		break;
		default: std::cout << "\nPress the correct key!\n" << std::endl;
		}
	}
	/*Two_three_tree list;
	list.add_item(Point(100, 1, 1));
	std::cout << "====\n";
	list.add_item(Point(2, 1, 1));
	std::cout << "====\n";
	list.add_item(Point(7, 2, 5));
	list.add_item(Point(6, 2, 3));
	list.add_item(Point(3, 2, 3));
	list.add_item(Point(9, 1, 1));
	list.add_item(Point(4, 1, 1));
	std::cout << "====\n";
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
