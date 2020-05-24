#include <iostream>
#include "my_linked_list.h"
#include "my_array_list.h"
#include "my_binary_tree.h"
#include "my_avl_tree.h"
#include "my_two_three_tree.h"
#include "my_correct_read.h"
#include <conio.h>
#include <Windows.h>
#include <chrono>
#include <vector>
#include <fstream>

struct measurement_result
{
	std::size_t number_of_items;
	std::size_t number_of_operations;
	float time;
	std::size_t size;
	measurement_result()
	{
		number_of_items = 0;
		number_of_operations = 0;
		time = 0;
		size = 0;
	}
	measurement_result(std::size_t number_of_items, std::size_t number_of_operations, float time, std::size_t size)
	{
		this->number_of_items = number_of_items;
		this->number_of_operations = number_of_operations;
		this->time = time;
		this->size = size;
	}
};
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
		default: std::cout << "\nPress the correct key!" << std::endl;
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
		default: std::cout << "\nPress the correct key!" << std::endl;
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
void find_distance(T& list)
{
	std::size_t first_index, second_index;
	first_index = correct::read_size_t("index of first point");
	second_index = correct::read_size_t("index of second point");
	double distance = list.find_distance_between_two_points(first_index, second_index);
	if (distance == -1)
	{
		std::cout << "\nThere aren't points entered!" << std::endl;
		return;
	}
	std::cout << "\nDistance: "<< distance << std::endl;
}
template<class T>
void read_point_from_file(T& list)
{
	std::cout << "\nEnter the path to file: ";
	std::string path = "text.txt";
	getline(std::cin, path);
	std::size_t index = correct::read_size_t("the index of point in file");
	std::cout << "\nThe point: " << list.read_file(index, path) << " was added to list" << std::endl;
}
template<class T>
void add_point_to_file(T& list)
{
	std::cout << "\nEnter the path to file: ";
	std::string path = "text.txt";
	getline(std::cin, path);
	std::size_t index = correct::read_size_t("the index of point");
	if (list.append_file(index, path))
	{
		std::cout << "\nThe point was added to file!" << std::endl;
	}
	else
	{
		std::cout << "\nThere isn't point with index: " << index << "." << std::endl;
	}
}
template<class T>
void find_circle(T& list)
{
	std::size_t index_of_centre = correct::read_size_t("the index of point of centre of circle");
	std::size_t index = correct::read_size_t("the index of point of circle");
	if (!list.find_length_and_area_of_circle(index_of_centre, index))
	{
		std::cout << "\nThere isn't point with indexes entered!"<< std::endl;
	}
}
template<class T>
void perform_actions(T& list)
{
	while (true)
	{
		std::cout << "\nChoose:\n1)Find distance between two points in list.\n"
			<< "2)Find distance between adjacent points in list.\n"
			<< "3)Read point from file and add to list.\n"
			<< "4)Add point to file from list.\n"
			<< "5)Find length and area of circle by points in list.\n"
			<< "0)Back." << std::endl;
		switch (_getch())
		{
		case '1': find_distance(list);
			break;
		case '2': list.find_distance_between_adjacent_points();
			break;
		case '3': read_point_from_file(list);
			break;
		case '4': add_point_to_file(list);
			break;
		case '5': find_circle(list);
			break;
		case'0': return;
		default: std::cout << "\nPress the correct key!" << std::endl;
		}
	}
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
		case '5': perform_actions(list);
			break;
		case '6': generate_random_items(list);
			break;
		case'0':
		{
			list.clear();
			return;
		}
		break;
		default: std::cout << "\nPress the correct key!" << std::endl;
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
		default: std::cout << "\nPress the correct key!" << std::endl;
		}
	}
}
void demo_mode()
{

}
std::size_t set_number(bool is_one_second, std::size_t& copy_size, std::size_t& coefficient)//resizes depending on condition
{
	if (is_one_second)
	{
		return coefficient++ * copy_size;
	}
	else
	{
		return copy_size *= 2;
	}
}
void clear_result_files(std::string paths[], int number_of_files, std::string name_of_struct)
{
	for (int i = 0; i < number_of_files; i++)
	{
		std::ofstream file(name_of_struct + paths[i] + ".txt");
		file.close();
	}
}
void add_result_to_file(measurement_result result, const std::string& name_of_files)
{
	std::ofstream file(name_of_files + ".txt", std::ios_base::app);
	file << "Number of items = " << result.number_of_items << "." << std::endl;
	file << "Number of operations = " << result.number_of_operations << "." << std::endl;
	file << "Time = " << result.time << "." << std::endl;
	file << "Size of memory = " << result.size << "." << std::endl;
	file.close();
}
template<class T>
void measurement_add_item(T& list, std::size_t number_of_items)
{
	list.add_item(Point(number_of_items));
}
template<class T>
void measurement_remove_item_by_index(T& list, std::size_t number_of_items)
{
	list.remove_item(rand() % list.get_size());
}
template<class T>
void measurement_remove_item_by_value(T& list, std::size_t number_of_items)
{
	list.remove_item(Point(number_of_items));
}
template<class T>
void measurement_find_item_by_one_value(T& list, std::size_t number_of_items)
{
	std::vector<tdp::Item> items = list.find_items(Point(number_of_items));
}
template<class T>
void measurement_find_item_by_two_values(T& list, std::size_t number_of_items)
{
	std::vector<tdp::Item> items = list.find_items(Point(number_of_items/2), Point(number_of_items));
}
template<class T>
void measurement_random_generator(T& list, std::size_t number_of_items)
{
	list.random_generator(number_of_items, number_of_items);
}
template<class T>
void measurement_clear(T& list, std::size_t number_of_items)
{
	list.clear();
}
template<class T>
float measurement(T& list, std::size_t index, std::size_t number_of_items, std::size_t number_of_operations, const std::string& name_of_functions, const std::string& name_of_struct)//measures the sort time of an array
{
	srand(unsigned(time(0)));
	const int number_of_functions = 12;
	void(*all_functions[number_of_functions])(T&, std::size_t) = {
		measurement_add_item, measurement_remove_item_by_index,
		measurement_remove_item_by_value,
		measurement_find_item_by_one_value, measurement_find_item_by_two_values,
		measurement_random_generator, measurement_clear };
	T new_list(list);
	auto the_start = std::chrono::high_resolution_clock::now();
	auto the_end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<float> duration;
	the_start = std::chrono::high_resolution_clock::now();
	all_functions[index](new_list, number_of_items);
	if ((index != 5)&&(index != 6))
	{
		for (std::size_t i = 0; i < number_of_operations - 1; i++)
		{
			all_functions[index](new_list, number_of_items);
		}	
	}
	the_end = std::chrono::high_resolution_clock::now();
	duration = the_end - the_start;
	measurement_result result = measurement_result(number_of_items, number_of_operations, duration.count(), list.count_size_of_memory());
	add_result_to_file(result, name_of_struct + name_of_functions);
	std::cout << "\nTime of " << name_of_functions << " = " << result.time << std::endl;
	std::cout << "Size of memory = " << result.size << std::endl;

	return result.time;
}
template<class T>
void benchmark_mode_menu(T& list, const std::string& name_of_struct)
{
	const int number_of_functions = 7;
	std::string name_of_functions[number_of_functions] = { "Add item", "Remove item by index",
	"Remove item by value", "Find items by one value", "Find points by two values",
	"Random generator", "Clear list" };
	clear_result_files(name_of_functions, number_of_functions, name_of_struct);
	bool is_one_second, are_ten_seconds = false;
	std::size_t number_of_items, number_of_operations, number = 1000;
	std::size_t copy_number_of_items = number, coefficient_of_items = 3;
	std::size_t copy_number_of_operations, coefficient_of_operations;
	std::size_t max_number = 60000;
	for (number_of_items = number; number_of_items < max_number;)
	{
		list.random_generator(number_of_items, number_of_items);
		copy_number_of_operations = number_of_items / 10;
		coefficient_of_operations = 3;
		is_one_second = false;
		for (number_of_operations = copy_number_of_operations; number_of_operations < number_of_items;)
		{
			std::cout << "\nNumber of items = " << number_of_items << std::endl;
			std::cout << "Number of operations = " << number_of_operations << std::endl;
			float time;
			for (std::size_t i = 0; i < number_of_functions; i++)
			{
				time = measurement(list, i, number_of_items, number_of_operations, name_of_functions[i], name_of_struct);
				if (time > 1) is_one_second = true;
				if (time > 10) are_ten_seconds = true;
			}
			if (are_ten_seconds) break;			
			number_of_operations = set_number(is_one_second, copy_number_of_operations, coefficient_of_operations);			
		}
		list.clear();
		if (are_ten_seconds) break;
		number_of_items = set_number(is_one_second, copy_number_of_items, coefficient_of_items);
	}
	std::cout << "\nResults of measurements of program in the following files:\n"
		<< name_of_struct + name_of_functions[0] + ".txt\n" << name_of_struct + name_of_functions[1] + ".txt\n"
		<< name_of_struct + name_of_functions[2] + ".txt\n" << name_of_struct + name_of_functions[3] + ".txt\n"
		<< name_of_struct + name_of_functions[4] + ".txt\n" << name_of_struct + name_of_functions[5] + ".txt\n"
		<< name_of_struct + name_of_functions[6] + ".txt\n" << std::endl;
}
void benchmark_mode()
{
	list::Linked_list linked_list;
	std::cout << "\nLinked list:" << std::endl;
	benchmark_mode_menu(linked_list, "Linked list ");
	array::Array_list array_list;
	std::cout << "\nArray list:" << std::endl;
	benchmark_mode_menu(array_list, "Array list ");
	binary::Binary_tree binary_tree;
	std::cout << "\nBinary tree:" << std::endl;
	benchmark_mode_menu(binary_tree, "Binary tree ");
	avl::Avl_tree avl_tree;
	std::cout << "\nAvl tree:" << std::endl;
	benchmark_mode_menu(avl_tree, "Avl tree ");
}
int main()
{
	/*while (true)
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
	}*/
	ttt::Two_three_tree list;
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
	/*for (std::size_t j = 0; j < 3; j++)
	{
		list.random_generator(40, 100);
		list.write();
	}*/
	list.remove_item(2);
	list.write();
	std::cout << "\n------1\n";
	list.remove_item(3);
	std::cout << "\n-1---------------\n";
	list.remove_item(0);
	list.write();
	list.add_item(Point(1, 2, 3));
	list.add_item(Point(7, 2, 3));
	list.add_item(Point(0, 2, 3));
	list.add_item(Point(1, 2, 3));
	list.write();
	/*std::vector<Item> items = list.find_items(Point(3, 2, 3), Point(10,2,1));
	write_items(items);*/
	std::cout << "\nThe end\n";
	return 0;
}
