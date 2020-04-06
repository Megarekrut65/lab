#include <iostream>
#include <vector>
#include <conio.h>
#include <Windows.h>
#include "my_correct_read.h"
//¹0 ¹2 ¹3 ¹11 ¹13
struct Tree_node
{
private:
	Tree_node* parent;
	std::vector<Tree_node*> children;
	int value;
	std::vector<std::size_t> path;
	void write_path()
	{
		std::size_t size = path.size();
		if (size == 0) std::cout << "Root: ";
		else
		{
			std::cout << "Root->";
			for (std::size_t i = 0; i < size - 1; i++)
			{
				std::cout << path[i] << "->";
			}
			std::cout << path[size - 1] << ": ";
		}
	}
	std::vector<std::size_t> create_path(std::vector<std::size_t>& path, std::size_t index)
	{
		std::vector<std::size_t> array;
		for (std::size_t i = 0; i < path.size(); i++)
		{
			array.push_back(path[i]);
		}
		array.push_back(index);
		return array;
	}
	void refresh_old_path_current(std::size_t size_of_remove_path)
	{
		path[size_of_remove_path - 1]--;
		for (std::size_t i = 0; i < children.size(); i++)
		{
			children[i]->refresh_old_path_current(size_of_remove_path);
		}
	}
	void children_refresh_path(std::size_t old_size_of_path)
	{
		if (path.size() > 0)
		{
			for (std::size_t i = 0; i < old_size_of_path; i++)
			{
				path.erase(path.begin());
			}
			for (std::size_t j = 0; j < children.size(); j++)
			{
				children[j]->children_refresh_path(old_size_of_path);
			}
		}
	}
public:
	Tree_node()
	{
		parent = nullptr;
		value = 0;
	}
	Tree_node(Tree_node* parent, int value, std::vector<std::size_t>& path, std::size_t index, bool is_root = true)
	{
		this->parent = parent;
		this->value = value;
		if (is_root) this->path = create_path(path, index);
		else this->path = path;
		
	}
	void add_child(Tree_node* child)
	{
		children.push_back(child);
	}
	Tree_node* get_child(std::size_t index)
	{
		return children[index];
	}
	Tree_node* get_parent()
	{
		return parent;
	}
	std::size_t get_size()
	{
		return children.size();
	}
	int get_value()
	{
		return value;
	}
	std::vector<std::size_t> get_path()
	{
		return path;
	}
	void refresh_new_path(std::size_t old_size_of_path)
	{
		children_refresh_path(old_size_of_path);
		path.clear();		
	}
	void set_parent(Tree_node* new_parent)
	{
		parent = new_parent;
	}	
	void write_value()
	{
		write_path();
		std::cout << "value = " << value << std::endl;
	}
	void refresh_old_path(std::size_t index, std::size_t size_of_remove_path)
	{
		for (std::size_t i = index + 1; i < children.size(); i++)
		{
			children[i]->refresh_old_path_current(size_of_remove_path);
		}
	}
	Tree_node* remove_child(std::size_t index)
	{
		if (index >= children.size()) return nullptr;
		Tree_node* child = children[index];
		children[index] = nullptr;
		children.erase(children.begin() + index);
		return child;
	}
};
struct Tree
{
private:
	Tree_node* root;	
	bool add_value_current(Tree_node* node, int value, std::vector<std::size_t>& path, std::size_t index = 0)
	{
		if (node == nullptr) return false;
		if (index == path.size())
		{
			Tree_node* new_node = new Tree_node(node, value, path, node->get_size());
			node->add_child(new_node);
			return true;
		}
		if (path[index] < node->get_size())
		{
			index++;
			return add_value_current(node->get_child(path[index - 1]), value, path, index);
		}
		else
		{
			return false;
		}
	}
	void write_tree_current(Tree_node* node)
	{
		node->write_value();
		for (std::size_t i = 0; i < node->get_size(); i++)
		{
			write_tree_current(node->get_child(i));
		}
	}
	void find_pointers_current(Tree_node* node, int value, std::vector<Tree_node*>& pointers)
	{
		if (node->get_value() == value) pointers.push_back(node);
		for (std::size_t i = 0; i < node->get_size(); i++)
		{
			find_pointers_current(node->get_child(i), value, pointers);
		}
	}
	Tree_node* find_by_path(std::vector<std::size_t>& path)
	{
		Tree_node* current = root;
		for (std::size_t i = 0; i < path.size(); i++)
		{
			if (path[i] < current->get_size()) current = current->get_child(path[i]);
			else return nullptr;			
		}
		return current;
	}
	Tree(Tree_node* new_root, std::size_t old_size_of_path)
	{
		root = new_root;
		root->set_parent(nullptr);
		root->refresh_new_path(old_size_of_path);
	}
public:
	Tree()
	{
		root = nullptr;
	}
	bool is_root()
	{
		if (root) return true;
		return false;
	}
	void add_root(int value)
	{
		if (root) return;
		std::vector<std::size_t> path;
		Tree_node* node = new Tree_node(nullptr, value, path, 0, false);
		root = node;
	}
	bool add_value(int value, std::vector<std::size_t>& path)
	{
		if (root == nullptr) return false;
		return add_value_current(root, value, path);		
	}
	void write_tree()
	{
		write_tree_current(root);
	}
	std::vector<Tree_node*> find_pointers(int value)
	{
		std::vector<Tree_node*> pointers;
		find_pointers_current(root, value, pointers);
		return pointers;
	}
	void write_paths(std::vector<Tree_node*> pointers)
	{
		if (pointers.size() == 0)
		{
			std::cout << "\nPointer(s) don't found!" << std::endl;
			return;
		}
		std::cout << "\nPath(s):" << std::endl;
		for (std::size_t i = 0; i < pointers.size(); i++)
		{
			std::cout << i + 1 << ")";
			pointers[i]->write_value();
		}
	}
	int get_value_by_path(std::vector<std::size_t>& path, bool& is_found)
	{
		is_found = true;
		Tree_node* current = find_by_path(path);
		if(current) return current->get_value();
		is_found = false;
		return -1;
	}
	Tree remove_sub_tree(std::vector<std::size_t>& path, bool& is_remove)
	{		
		is_remove = true;
		std::size_t size_of_path = path.size();
		if (size_of_path == 0)
		{
			Tree_node* new_root = root;
			root = nullptr;
			return Tree(new_root, 0);
		}
		Tree_node* current = find_by_path(path);
		if (!current)
		{
			is_remove = false;
			return Tree();
		}
		std::size_t index = path[size_of_path - 1];		
		current->get_parent()->refresh_old_path(index, size_of_path);
		Tree_node* child = current->get_parent()->remove_child(index);		
		return Tree(child, size_of_path);
	}
};
std::vector<std::size_t> choose_path(Tree& tree, std::vector<Tree_node*>& pointers)
{
	while (true)
	{
		tree.write_paths(pointers);
		std::size_t number = correct::read_size_t("number of the path");
		if (number - 1 < pointers.size())
		{
			return pointers[number - 1]->get_path();
		}
		else
		{
			std::cout << "\nNumber entered incorrect!" << std::endl;
		}
	}
}
std::vector<std::size_t> create_path()
{
	std::size_t size = correct::read_size_t("size of path(path to root - enter 0)");
	std::vector<std::size_t> path(size);
	if(size == 0) return path;
	std::cout << "\nEnter the path\n________\nExample:\n\nEnter:0\n\nEnter:1\n...\n________" << std::endl;
	for (std::size_t i = 0; i < size; i++)
	{
		path[i] = correct::read_size_t("");
	}
	return path;
}
std::vector<std::size_t> select_path(Tree& tree, std::vector<Tree_node*>& pointers)
{
	while (true)
	{
		std::cout << "\n1)Create new path.\n2)Choose the path found."<< std::endl;
		switch (_getch())
		{
		case '1':  return create_path();
			break;
		case '2': return choose_path(tree, pointers);
			break;
		default: std::cout << "\nPress the correct key!" << std::endl;
		}
	}
}
void add_new_item_to_tree(Tree& tree, std::vector<Tree_node*>& pointers)
{
	int value = correct::read_int("the value");
	if (!tree.is_root())
	{
		tree.add_root(value);
		std::cout << "\nThe root added to tree!" << std::endl;
		return;
	}
	std::vector<std::size_t> path = select_path(tree, pointers);
	std::size_t size = path.size();
	if (!tree.add_value(value, path))
	{
		std::cout << "\nPath entered incorrect or don't found!" << std::endl;
		return;
	}
	std::cout << "\nThe item added to tree!" << std::endl;
}
std::vector<Tree_node*> get_pointer_to_item(Tree& tree)
{
	int value = correct::read_int("the value");
	std::vector<Tree_node*> pointers = tree.find_pointers(value);
	std::cout << "\nFound " << pointers.size() << " pointer(s)." << std::endl;

	return pointers;
}
void get_item_by_path(Tree& tree, std::vector<Tree_node*>& pointers)
{
	bool is_found;
	std::vector<std::size_t> path = select_path(tree, pointers);
	int value = tree.get_value_by_path(path, is_found);
	if (is_found)
	{
		std::cout << "\nItem found!\nValue = " << value << std::endl;
	}
	else
	{
		std::cout << "\nItem don't found!" << std::endl;
	}
}
void actions_new_tree(Tree& new_tree)
{
	while (true)
	{
		std::cout << "\nReceived a new tree!\n1)Edit new tree.\n"
			      << "0)Back to old tree and delete new tree." << std::endl;
		switch (_getch())
		{
		case '1': 
		{
			return;
		}
			break;
		case '2': 
		{
			return;
		}
			break;
		default: std::cout << "\nPress the correct key!" << std::endl;
		}
	}
	
}
void remove_sub_tree_by_path(Tree& tree, std::vector<Tree_node*>& pointers)
{
	bool is_remove;
	std::vector<std::size_t> path = select_path(tree, pointers);
	Tree new_tree = tree.remove_sub_tree(path, is_remove);
	if (is_remove)
	{
		std::cout << "\nItem removed!"<< std::endl;
		actions_new_tree(new_tree);
	}
	else
	{
		std::cout << "\nItem don't found!" << std::endl;
	}
}
void tree_menu(Tree& tree)
{
	std::vector<Tree_node*> pointers;
	while (true)
	{
		std::cout << "\nGeneral tree:\n1)Add new item to tree.\n2)Get the pointers to item.\n"
			      << "3)Get the path of item by pointer.\n4)Get the item by path.\n"
			      << "5)Write all tree\n6)Remove sub-tree by path.\n0)Back."<< std::endl;
		switch (_getch())
		{
		case '1':  add_new_item_to_tree(tree, pointers);
			break;
		case '2': pointers = get_pointer_to_item(tree);
			break;
		case '3': tree.write_paths(pointers);
			break;
		case '4': get_item_by_path(tree, pointers);
			break;
		case '5': tree.write_tree();
			break;
		case '6': remove_sub_tree_by_path(tree, pointers);
			break;
		case'0':
		{
			return;
		}
		break;
		default: std::cout << "\nPress the correct key!" << std::endl;
		}
	}
}
void binary_tree_menu()
{

}
void use_of_trees_menu()
{

}
void interactive_dialog_mode()
{
	while (true)
	{
		std::cout << "\nMenu:\n1)General tree.\n2)Binary tree.\n"
			<< "3)Use of trees.\n0)Back."
			<< "" << std::endl;
		switch (_getch())
		{
		case '1':
		{
			Tree tree = Tree();
			tree_menu(tree);
			//delete tree
		}
			break;
		case '2':
			break;
		case '3':
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
int main()
{
	while (true)
	{
		std::cout << "Select the application mode:\n1)Interactive dialog mode.\n"
			<< "2)Demo mode.\n0)Exit." << std::endl;
		switch (_getch())
		{
		case '1':  interactive_dialog_mode();
			break;
		case '2': demo_mode();
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
	return 0;
}