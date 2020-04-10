#include <iostream>
#include <vector>
#include <conio.h>
#include <Windows.h>
#include <string>
#include "my_correct_read.h"
//�1 �2 �3 �11 �13 �18 �21 �22
struct Tree_node;
struct Tree;
void tree_menu(Tree&);
struct Tree_node
{
private:
	Tree_node* parent;
	std::vector<Tree_node*> children;
	int value;
	std::vector<std::size_t> path;
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
	void write_path(bool show_value = true)
	{
		std::string end;
		if (show_value) end = ": ";
		else end = ".\n";
		std::size_t size = path.size();
		if (size == 0) std::cout << "Root" + end;
		else
		{
			std::cout << "Root->";
			for (std::size_t i = 0; i < size - 1; i++)
			{
				std::cout << path[i] << "->";
			}
			std::cout << path[size - 1] << end;
		}
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
	void delete_all_children()
	{
		for (std::size_t i = 0; i < children.size(); i++)
		{
			if (children[i]->children.size() != 0) children[i]->delete_all_children();
			children[i]->parent = nullptr;
			delete children[i];
			children.erase(children.begin() + i);
		}		
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
	bool is_empty()
	{
		if (!root)
		{
			std::cout << "\nThe tree is empty!" << std::endl;
			return true;
		}
		return false;
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
		if (is_empty()) return;
		std::cout << std::endl;
		write_tree_current(root);
	}
	std::vector<Tree_node*> find_pointers(int value)
	{
		std::vector<Tree_node*> pointers;
		if (!is_empty()) find_pointers_current(root, value, pointers);	
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
			pointers[i]->write_path(false);
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
		if (!root) return Tree();
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
	void clear_tree()
	{
		if (!root) return;
		root->delete_all_children();
		delete root;
		root = nullptr;
	}
};
enum class Side{LEFT, RIGHT};
struct Binary_node
{
private:
	Binary_node* parent;
	Binary_node* left;
	Binary_node* right;
	std::vector<Side> path;
	int value;
	std::vector<Side> create_path(std::vector<Side>& path, Side side)
	{
		std::vector<Side> array;
		for (std::size_t i = 0; i < path.size(); i++)
		{
			array.push_back(path[i]);
		}
		array.push_back(side);
		return array;
	}
public:
	Binary_node()
	{
		parent = nullptr;
		left = nullptr;
		right = nullptr;
		value = 0;
	}
	Binary_node(Binary_node* parent, Binary_node* left, Binary_node* right, std::vector<Side> path, Side side,  int value)
	{
		this->parent = parent;
		this->left = left;
		this->right = right;
		if (parent) this->path = create_path(path, side);
		else this->path = path;
		this->value = value;
	}	
	Binary_node* get_parent()
	{
		return parent;
	}
	Binary_node* get_left()
	{
		return left;
	}
	Binary_node* get_right()
	{
		return right;
	}
	std::vector<Side> get_path()
	{
		return path;
	}
	int get_value()
	{
		return value;
	}
	void add_to_tree_current(Binary_node* node, int value)
	{
		if (value < node->value)
		{			
			if (!node->left)
			{
				Binary_node* new_node = new Binary_node(node, nullptr, nullptr, node->get_path(), Side::LEFT, value);
				node->left = new_node;
				return;
			}
			add_to_tree_current(node->left, value);
		}
		else
		{
			if (!node->right)
			{
				Binary_node* new_node = new Binary_node(node, nullptr, nullptr, node->get_path(), Side::RIGHT, value);
				node->right = new_node;
				return;
			}
			add_to_tree_current(node->right, value);
		}
	}
	void write_path()
	{
		if (path.size() == 0)
		{
			std::cout << "Root: ";
			return;
		}
		else std::cout << "Root->";
		for (std::size_t i = 0; i < path.size() - 1; i++)
		{
			switch (path[i])
			{
			case Side::LEFT: std::cout << "left-->";
				break;
			case Side::RIGHT: std::cout << "right->";
				break;
			}
		}
		switch (path[path.size() - 1])
		{
		case Side::LEFT: std::cout << "left: ";
			break;
		case Side::RIGHT: std::cout << "right: ";
			break;
		}
	}
	void write_tree_current()
	{
		write_path();
		std::cout << "value = " << value << std::endl;
		if(left) left->write_tree_current();
		if(right) right->write_tree_current();
	}
	void delete_all_children()
	{		
		if (left)
		{
			left->delete_all_children();
			delete left;
			left = nullptr;
		}
		if (right)
		{
			right->delete_all_children();
			delete right;
			right = nullptr;
		}
		parent = nullptr;
	}
};
struct Binary_tree
{
private:
	Binary_node* root;
	bool is_empty()
	{
		if (!root)
		{
			std::cout << "\nThe tree is empty!" << std::endl;
			return true;
		}
		return false;
	}
public:
	Binary_tree()
	{
		root = nullptr;
	}
	Binary_node* get_root()
	{
		return root;
	}
	void add_to_tree(int value)
	{
		if (!root)
		{
			std::vector<Side> path;
			Binary_node* new_node = new Binary_node(nullptr, nullptr, nullptr, path, Side::LEFT, value);
			root = new_node;
			return;
		}
		root->add_to_tree_current(root, value);
	}
	void write_tree()
	{
		if (is_empty()) return;
		std::cout << std::endl;
		root->write_tree_current();
	}
	void clear_tree()
	{
		if (!root) return;
		root->delete_all_children();
		root = nullptr;
	}
};
struct Consistent_presentation
{
	int value;
	bool is_left;
	bool is_right;
	std::size_t index_of_right;
	Consistent_presentation()
	{
		value = 0;
		is_left = false;
		is_right = false;
		index_of_right = 0;
	}
	Consistent_presentation(int value, bool is_left, bool is_right, std::size_t index_of_right)
	{
		this->value = value;
		this->is_left = is_left;
		this->is_right = is_right;
		this->index_of_right = index_of_right;
	}
};
enum class Arithmetic_type { CONSTANT, VARIABLE, OPERATION, INCORRECT };
struct Characteristics
{
	int priority;
	Arithmetic_type type;
	std::string value;
	std::string parentheses;
	bool is_open;
	bool is_close;	
	Characteristics()
	{
		priority = 0;
		type = Arithmetic_type::INCORRECT;
		value = "";
		parentheses = "";
		is_open = false;
		is_close = false;		
	}
	Characteristics(int priority, Arithmetic_type type, std::string value, std::string parentheses)
	{
		this->priority = priority;
		this->type = type;
		this->value = value;
		this->parentheses = parentheses;
		if (parentheses[0] == '(') is_open = true;
		else is_open = false;
		if (parentheses[0] == ')') is_close = true;
		else is_close = false;
	}
};
struct Expression_node
{
	Expression_node* parent;
	Expression_node* left;
	Expression_node* right;
	Characteristics item;
	Expression_node()
	{
		parent = nullptr;
		left = nullptr;
		right = nullptr;
		item = Characteristics(-1, Arithmetic_type::INCORRECT, "", "");
	}
	Expression_node(Expression_node* parent, Expression_node* left, Expression_node* right, Characteristics item)
	{
		this->parent = parent;
		this->left = left;
		this->right = right;
		this->item = item;	
	}	
};
struct Expression_tree
{
	Expression_node* root;

	Expression_tree()
	{
		root = nullptr;
	}
	int get_priority(std::string value)
	{
		if ((value == "+") || (value == "-")) return 0;
		if ((value == "*") || (value == "/")) return 1;
		if (value == "^") return 2;
		return -1;
	}
	Arithmetic_type find_type(std::string value)
	{
		std::size_t size = value.size();
		if (size < 1) return Arithmetic_type::INCORRECT;
		if (size == 1)
		{
			if ((value == "+") || (value == "-")
				|| (value == "*") || (value == "/")
				|| (value == "^")) return Arithmetic_type::OPERATION;
			if ((value[0] >= 'a') && (value[0] <= 'z')) return Arithmetic_type::VARIABLE;
			if ((value[0] >= '0') && (value[0] <= '9')) return Arithmetic_type::CONSTANT;
			return Arithmetic_type::INCORRECT;
		}
		std::size_t i = 0;
		if (value[i] == '-') i++;
		for (; i < size; i++)
		{
			if ((value[i] < '0') || (value[i] > '9')) return Arithmetic_type::INCORRECT;
		}
		return Arithmetic_type::CONSTANT;
	}
	bool regulation_parentheses(char symbol, int& priority, std::string& parentheses)
	{
		if (symbol == '(')
		{
			priority += 10;
			parentheses += "( ";
			return true;
		}
		if (symbol == ')')
		{
			priority -= 10;
			parentheses += ") ";
			return true;
		}
		return false;
	}
	bool add_to_characteristics(std::vector<Characteristics>& characteristics, int priority, std::string value, std::string& parentheses)
	{
		std::string parentheses_of_item = "";
		if (parentheses.size() != 0)
		{
			if (parentheses[0] == '(')
			{
				parentheses_of_item = parentheses;
				parentheses = "";
			} 
		}
		Arithmetic_type type = find_type(value);
		switch (type)
		{
		case Arithmetic_type::CONSTANT: characteristics.push_back(Characteristics(-1, type, value, parentheses_of_item));
			break;
		case Arithmetic_type::VARIABLE: characteristics.push_back(Characteristics(-1, type, value, parentheses_of_item));
			break;
		case Arithmetic_type::OPERATION: characteristics.push_back(Characteristics(priority + get_priority(value), type, value, parentheses_of_item));
			break;
		case Arithmetic_type::INCORRECT:
		{
			std::cout << "\nExpression entered incorrect!" << std::endl;
			return false;
		}
		break;
		}
		return true;
	}
	void write_array(std::vector<Characteristics> characteristics)
	{
		for (std::size_t i = 0; i < characteristics.size(); i++)
		{
			std::cout << "priority: " << characteristics[i].priority << " type: ";
			switch (characteristics[i].type)
			{
			case Arithmetic_type::CONSTANT: std::cout << "constant";
				break;
			case Arithmetic_type::VARIABLE: std::cout << "variable";
				break;
			case Arithmetic_type::OPERATION: std::cout << "operation";
				break;
			}
			std::cout << " value: " << characteristics[i].value << std::endl;
		}
	}
	bool check_input(std::vector<Characteristics> characteristics)
	{
		std::size_t size = characteristics.size();
		if ((characteristics[0].type == Arithmetic_type::OPERATION)
			|| (characteristics[size - 1].type == Arithmetic_type::OPERATION)) return false;
		bool is_operation = false;
		for (std::size_t i = 1; i < size - 1; i++)
		{
			if (((characteristics[i].type == Arithmetic_type::OPERATION) && !is_operation)
				|| ((characteristics[i].type == Arithmetic_type::CONSTANT) && is_operation)
				|| ((characteristics[i].type == Arithmetic_type::VARIABLE) && is_operation)) is_operation = !is_operation;
			else return false;
		}
		return true;
	}
	bool find_simple_mistakes(int priority, std::vector<Characteristics>& characteristics)
	{
		if (priority != 0)
		{
			std::cout << "\nParentheses entered incorrect!" << std::endl;
			return false;
		}
		if (characteristics.size() == 0)
		{
			std::cout << "\nArithmetic expression is not entered!" << std::endl;
			return false;
		}
		if (!check_input(characteristics))
		{
			std::cout << "\nWrong order of operations, constants, or variables!" << std::endl;
			return false;
		}
		return true;
	}
	bool add_expression_to_array(std::string expression, std::vector<Characteristics>& characteristics)
	{
		std::size_t size = expression.size();
		int priority = 0;
		std::string parentheses = "";
		for (std::size_t i = 0; i < size; i++)
		{
			if (regulation_parentheses(expression[i], priority, parentheses))
			{
				i++;
				continue;
			}
			if (priority < 0)
			{
				std::cout << "\nParentheses entered incorrect!" << std::endl;
				return false;
			}
			std::string value = "";
			while ((expression[i] != ' ') && (i < size))
			{
				value += expression[i++];
			}
			if (parentheses[0] == ')')
			{
				characteristics[characteristics.size() - 1].parentheses = parentheses;
				characteristics[characteristics.size() - 1].is_close = true;
				parentheses = "";
			}
			if (!add_to_characteristics(characteristics, priority, value, parentheses)) return false;
		}		
		//write_array(characteristics);
		return find_simple_mistakes(priority, characteristics);
	}
	void add_to_tree_current(Expression_node* node, Characteristics item, bool& is_added)
	{
		if (node->item.type != Arithmetic_type::OPERATION) return;	
		if (!node->left)
		{
			Expression_node* new_node = new Expression_node(node, nullptr, nullptr, item);
			node->left = new_node;
			is_added = true;
			return;
		}
		else
		{
			bool this_is_added = false;
			add_to_tree_current(node->left, item, this_is_added);
			is_added = this_is_added;
			if (this_is_added) return;
		}
		if (!node->right)
		{
			Expression_node* new_node = new Expression_node(node, nullptr, nullptr, item);
			node->right = new_node;
			is_added = true;
			return;
		}
		else
		{
			bool this_is_added = false;
			add_to_tree_current(node->right, item, this_is_added);
			is_added = this_is_added;
			if (this_is_added) return;
		}
	}
	void add_to_tree(Characteristics item)
	{
		if (!root)
		{
			Expression_node* node = new Expression_node(nullptr, nullptr, nullptr, item);
			root = node;
			return;
		}
		bool is_added = false;
		add_to_tree_current(root, item, is_added);
		if (!is_added)
		{
			std::cout << "\nError" << std::endl;
		}
	}
	std::size_t index_of_min_priority(Characteristics* array, std::size_t size)
	{
		std::size_t min_priority = array[1].priority;
		std::size_t index = 1;
		for (std::size_t i = 3; i < size; i+=2)
		{
			if (array[i].priority < min_priority)
			{
				min_priority = array[i].priority;
				index = i;
			}
		}
		return index;
	}
	void separation_of_expression(Characteristics* array, std::size_t size)
	{
		std::size_t index = index_of_min_priority(array, size);
		add_to_tree(array[index]);
		if (index > 2)
		{
			Characteristics* new_array = new Characteristics[index];
			new_array = &array[0];
			separation_of_expression(new_array, index);
		}
		else
		{
			add_to_tree(array[index - 1]);
		}
		if (index + 2 < size)
		{
			Characteristics* new_array = new Characteristics[size - index - 1];
			new_array = &array[index + 1];
			separation_of_expression(new_array, size - index - 1);
		}
		else
		{
			add_to_tree(array[index + 1]);
		}
	}
	void expression_analysis(std::string expression)
	{
		std::vector<Characteristics> characteristics;
		if (!add_expression_to_array(expression, characteristics)) return;
		std::size_t size = characteristics.size();
		Characteristics* array = new Characteristics[size];
		array = &characteristics[0];
		separation_of_expression(array, size);
	}
	void write_expression_current(Expression_node* node, std::string& parentheses, int& number_of_parentheses)
	{
		if (!node) return;
		if (node->left) write_expression_current(node->left, parentheses, number_of_parentheses);
		if (node->item.is_open) std::cout << node->item.parentheses;
		std::cout << node->item.value << " ";
		if (node->item.is_close) std::cout << node->item.parentheses;
		if (node->right) write_expression_current(node->right, parentheses, number_of_parentheses);
	}
	void write_expression()
	{
		if (!root) return;
		std::cout << "\nExpression: ";
		std::string parentheses = "";
		int number_of_parentheses = 0;
		write_expression_current(root, parentheses, number_of_parentheses);
		std::cout << std::endl;
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
		case '2': 
		{
			if (pointers.size() != 0) return choose_path(tree, pointers);
			else std::cout << "\nThe pointer(s) don't found!" << std::endl;;
		}
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
		case '1': tree_menu(new_tree);			
			break;
		case '0': return;
			break;
		default: std::cout << "\nPress the correct key!" << std::endl;
		}
	}
}
void remove_sub_tree_by_path(Tree& tree, std::vector<Tree_node*>& pointers)
{
	bool is_remove = false;
	std::vector<std::size_t> path = select_path(tree, pointers);
	Tree new_tree = tree.remove_sub_tree(path, is_remove);
	if (is_remove)
	{
		std::cout << "\nItem removed and pointers to all items cleared!"<< std::endl;
		pointers.clear();
		actions_new_tree(new_tree);
		new_tree.clear_tree();
		std::cout << "\nOld Tree:" << std::endl;
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
			      << "5)Write all tree.\n6)Remove sub-tree by path.\n0)Back."<< std::endl;
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
		case'0': return;		
		break;
		default: std::cout << "\nPress the correct key!" << std::endl;
		}
	}
}
void create_consistent_presentation_current(Binary_node* node, std::vector<Consistent_presentation>& new_tree, bool will_right, std::size_t index_of_parent)
{
	if (!node) return;
	if (will_right) new_tree[index_of_parent].index_of_right = new_tree.size();
	bool is_left;
	bool is_right;
	if (node->get_left()) is_left = true;
	else is_left = false;
	if (node->get_right()) is_right = true;
	else is_right = false;
	std::size_t index = new_tree.size();
	new_tree.push_back(Consistent_presentation(node->get_value(), is_left, is_right, 0));
	if (is_left)
	{
		std::cout << "left: true" << std::endl;
		std::cout << "value: " << node->get_value() << std::endl;
		create_consistent_presentation_current(node->get_left(), new_tree, false, 0);
	}
	if (is_right)
	{
		std::cout << "right: true" << std::endl;
		std::cout << "value: " << node->get_value() << std::endl;
		create_consistent_presentation_current(node->get_right(), new_tree, true, index);
	}
}
void write_consistent_presentation(std::vector<Consistent_presentation>& new_tree)
{
	if (new_tree.size() == 0)
	{
		std::cout << "\nTree is empty!" << std::endl;
		return;
	}
	std::cout << "\nConsistent presentation of tree:" << std::endl;
	for (std::size_t i = 0; i < new_tree.size(); i++)
	{
		std::cout << i << ")value: " << new_tree[i].value << ". index of right: ";
		if (new_tree[i].is_right) std::cout << new_tree[i].index_of_right;
		else std::cout << "-1";
		std::cout << ". left: ";
		if (new_tree[i].is_left) std::cout << "true.";
		else std::cout << "false.";
		std::cout << std::endl;
	}
	std::cout << std::endl;
}
std::vector<Consistent_presentation> create_consistent_presentation(Binary_tree& tree)
{
	std::vector<Consistent_presentation> new_tree;
	std::size_t index_of_parent = 0;
	create_consistent_presentation_current(tree.get_root(), new_tree, false, index_of_parent);

	return new_tree;
}
void binary_add_new_item(Binary_tree& tree)
{
	int value = correct::read_int("the value");
	tree.add_to_tree(value);
	std::cout << "\nItem added to tree!" << std::endl;
}
void binary_tree_menu(Binary_tree& tree)
{
	while (true)
	{
		std::cout << "\nBinary tree:\n1)Add new item to tree.\n2)Write all tree.\n"
				  <<"3)Create consistent presentation of the tree and write it.\n0)Back." << std::endl;
		switch (_getch())
		{
		case '1': binary_add_new_item(tree);
			break;
		case '2': tree.write_tree();
			break;	
		case '3': 
		{
			std::vector<Consistent_presentation> new_tree = create_consistent_presentation(tree);
			write_consistent_presentation(new_tree);
			new_tree.clear();
		}
			break;
		case'0': return;
		break;
		default: std::cout << "\nPress the correct key!" << std::endl;
		}
	}
}
void use_of_trees_menu()
{
	Expression_tree tree;
	std::string c;
	std::cout << "enter c: ";
	std::getline(std::cin, c);
	tree.expression_analysis(c);
	tree.write_expression();
}
void interactive_dialog_mode()
{
	while (true)
	{
		std::cout << "\nMenu:\n1)General tree.\n2)Binary tree.\n"
			<< "3)Use of trees.\n0)Back."<< std::endl;
		switch (_getch())
		{
		case '1':
		{
			Tree tree;
			tree_menu(tree);
			tree.clear_tree();
		}
			break;
		case '2':
		{
			Binary_tree tree;
			binary_tree_menu(tree);
			tree.clear_tree();
		}
			break;
		case '3': use_of_trees_menu();
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
namespace all_demo_mode
{
	void demo_main(unsigned delay)
	{
		std::cout << "\nSelect the application mode:\n1)Interactive dialog mode.\n"
			<< "2)Demo mode.\n0)Exit." << std::endl;
		Sleep(delay);
		std::cout << "\nSelect the application mode:\n1)Interactive dialog mode. <-press\n"
			<< "2)Demo mode.\n0)Exit." << std::endl;
		Sleep(delay);
	}
	void demo_create_path(unsigned delay, Tree& tree, std::vector<std::size_t> path)
	{
		std::cout << "\n1)Create new path. <-press\n2)Choose the path found." << std::endl;
		Sleep(delay);
		std::cout << "\nEnter size of path(path to root - enter 0): <-write the size and press <Enter>" << std::endl;
		Sleep(delay);
		std::cout << "Enter size of path(path to root - enter 0): " << path.size() << std::endl;
		Sleep(delay);
		if (path.size() != 0)
		{
			std::cout << "\nEnter the path\n________\nExample:\n\nEnter:0\n\nEnter:1\n...\n________" << std::endl;
			for (std::size_t i = 0; i < path.size(); i++)
			{
				std::cout << "\nEnter: <-write the size and press <Enter>" << std::endl;
				Sleep(delay);
				std::cout << "Enter: " << path[i] << std::endl;
				Sleep(delay);
			}
		}
	}
	void demo_choose_path(unsigned delay, Tree& tree, std::vector<Tree_node*>& pointers, std::size_t number)
	{
		std::cout << "\n1)Create new path.\n2)Choose the path found. <-press" << std::endl;
		Sleep(delay);
		tree.write_paths(pointers);
		std::cout << "\nEnter number of the path: <-write the number and press <Enter>" << std::endl;
		Sleep(delay);
		std::cout << "Enter number of the path: " << number << std::endl;
		Sleep(delay);
	}
	void demo_tree_menu(unsigned delay)
	{
		std::cout << "\nMenu:\n1)General tree. <-press\n2)Binary tree.\n"
			<< "3)Use of trees.\n0)Back." << std::endl;
		Sleep(delay);
	}
	void demo_add_new_item_to_tree(unsigned delay, Tree& tree, int value, std::vector<std::size_t> path, std::vector<Tree_node*>& pointers, std::size_t number, bool create = true, bool is_root = true)
	{
		std::cout << "\nGeneral tree:\n1)Add new item to tree. <-press\n2)Get the pointers to item.\n"
			<< "3)Get the path of item by pointer.\n4)Get the item by path.\n"
			<< "5)Write all tree.\n6)Remove sub-tree by path.\n0)Back." << std::endl;
		Sleep(delay);
		std::cout << "\nEnter the value: <-write the value and press <Enter>" << std::endl;
		Sleep(delay);
		std::cout << "Enter the value: " << value << std::endl;
		Sleep(delay);
		if (!is_root)
		{
			tree.add_root(value);
			std::cout << "\nThe root added to tree!" << std::endl;
			Sleep(delay);
			return;
		}
		if (create)
		{
			demo_create_path(delay, tree, path);
		}
		else
		{
			demo_choose_path(delay, tree, pointers, number);
		}
		if (!tree.add_value(value, path))
		{
			std::cout << "\nPath entered incorrect or don't found!" << std::endl;
			return;
		}
		std::cout << "\nThe item added to tree!" << std::endl;
		Sleep(delay);
	}
	void demo_get_pointer_to_item(unsigned delay, Tree& tree, int value, std::vector<Tree_node*>& pointers, std::size_t& number)
	{
		std::cout << "\nGeneral tree:\n1)Add new item to tree.\n2)Get the pointers to item. <-press\n"
			<< "3)Get the path of item by pointer.\n4)Get the item by path.\n"
			<< "5)Write all tree.\n6)Remove sub-tree by path.\n0)Back." << std::endl;
		Sleep(delay);
		std::cout << "\nEnter a value: <-write the value and press <Enter>" << std::endl;
		Sleep(delay);
		std::cout << "Enter a value: " << value << std::endl;
		Sleep(delay);
		pointers = tree.find_pointers(value);
		number = pointers.size();
		std::cout << "\nFound " << number << " pointer(s)." << std::endl;
		Sleep(delay);
	}
	void demo_get_item_by_path(unsigned delay, Tree& tree, std::vector<std::size_t> path, std::vector<Tree_node*>& pointers, std::size_t number, bool create = true)
	{
		std::cout << "\nGeneral tree:\n1)Add new item to tree.\n2)Get the pointers to item.\n"
			<< "3)Get the path of item by pointer.\n4)Get the item by path. <-press\n"
			<< "5)Write all tree.\n6)Remove sub-tree by path.\n0)Back." << std::endl;
		Sleep(delay);
		if (create)
		{
			demo_create_path(delay, tree, path);
		}
		else
		{
			demo_choose_path(delay, tree, pointers, number);
		}
		bool is_found;
		int value = tree.get_value_by_path(path, is_found);
		if (is_found)
		{
			std::cout << "\nItem found!\nValue = " << value << std::endl;
		}
		else
		{
			std::cout << "\nItem don't found!" << std::endl;
		}
		Sleep(delay);
	}
	void demo_write_all_tree(unsigned delay, Tree& tree)
	{
		std::cout << "\nGeneral tree:\n1)Add new item to tree.\n2)Get the pointers to item.\n"
			<< "3)Get the path of item by pointer.\n4)Get the item by path.\n"
			<< "5)Write all tree. <-press\n6)Remove sub-tree by path.\n0)Back." << std::endl;
		Sleep(delay);
		tree.write_tree();
		Sleep(delay);
	}
	void demo_back(unsigned delay)
	{
		std::cout << "\nGeneral tree:\n1)Add new item to tree.\n2)Get the pointers to item.\n"
			<< "3)Get the path of item by pointer.\n4)Get the item by path.\n"
			<< "5)Write all tree.\n6)Remove sub-tree by path.\n0)Back. <-press\n" << std::endl;
		Sleep(delay);
	}
	void actions_new_tree(unsigned delay, bool is_edit = true)
	{
		if (is_edit)
		{
			std::cout << "\nReceived a new tree!\n1)Edit new tree. <-press\n"
				<< "0)Back to old tree and delete new tree." << std::endl;
		}
		else
		{
			std::cout << "\nReceived a new tree!\n1)Edit new tree.\n"
				<< "0)Back to old tree and delete new tree. <-press" << std::endl;
		}
		Sleep(delay);
	}
	void demo_remove_sub_tree_by_path(unsigned delay, Tree& tree, std::vector<std::size_t> path, std::vector<Tree_node*>& pointers, std::size_t number, bool create = true)
	{
		std::cout << "\nGeneral tree:\n1)Add new item to tree.\n2)Get the pointers to item.\n"
			<< "3)Get the path of item by pointer.\n4)Get the item by path.\n"
			<< "5)Write all tree.\n6)Remove sub-tree by path. <-press\n0)Back." << std::endl;
		Sleep(delay);
		if (create)
		{
			demo_create_path(delay, tree, path);
		}
		else
		{
			demo_choose_path(delay, tree, pointers, number);
		}
		bool is_remove = false;
		Tree new_tree = tree.remove_sub_tree(path, is_remove);
		if (is_remove)
		{
			std::cout << "\nItem removed and pointers to all items cleared!" << std::endl;
			pointers.clear();
			actions_new_tree(delay);
			demo_write_all_tree(delay, new_tree);
			demo_back(delay);
			actions_new_tree(delay, false);
			new_tree.clear_tree();
			std::cout << "\nOld Tree:" << std::endl;
			demo_write_all_tree(delay, tree);
		}
		else
		{
			std::cout << "\nItem don't found!" << std::endl;
		}
	}	
	void demo_binary_add_new_item(unsigned delay, Binary_tree& tree, int value)
	{
		std::cout << "\nBinary tree:\n1)Add new item to tree. <-press\n2)Write all tree.\n"
			<< "3)Create consistent presentation of the tree and write it.\n0)Back." << std::endl;
		Sleep(delay);
		std::cout << "\nEnter the value: <-write the value and press <Enter>" << std::endl;
		Sleep(delay);
		std::cout << "Enter the value: " << value << std::endl;
		tree.add_to_tree(value);
		std::cout << "\nItem added to tree!" << std::endl;
		Sleep(delay);
	}
	void demo_binary_write_tree(unsigned delay, Binary_tree& tree)
	{
		std::cout << "\nBinary tree:\n1)Add new item to tree.\n2)Write all tree. <-press\n"
			<< "3)Create consistent presentation of the tree and write it.\n0)Back." << std::endl;
		Sleep(delay);
		tree.write_tree();
		Sleep(delay);
	}
	void demo_create_consistent_presentation(unsigned delay, Binary_tree& tree)
	{
		std::cout << "\nBinary tree:\n1)Add new item to tree.\n2)Write all tree.\n"
			<< "3)Create consistent presentation of the tree and write it. <-press\n0)Back." << std::endl;
		Sleep(delay);
		std::vector<Consistent_presentation> new_tree = create_consistent_presentation(tree);
		write_consistent_presentation(new_tree);
		new_tree.clear();
		Sleep(delay);
	}
	void demo_binary_tree_menu(unsigned delay)
	{
		std::cout << "\nMenu:\n1)General tree.\n2)Binary tree. <-press\n"
			<< "3)Use of trees.\n0)Back." << std::endl;
		Sleep(delay);
	}
	void binary_demo_mode(unsigned delay)
	{
		Binary_tree tree;
		demo_binary_tree_menu(delay);
		demo_binary_add_new_item(delay, tree, 3);
		demo_binary_add_new_item(delay, tree, 4);
		demo_binary_add_new_item(delay, tree, 5);
		demo_binary_add_new_item(delay, tree, 2);
		demo_binary_add_new_item(delay, tree, 1);
		demo_binary_add_new_item(delay, tree, 3);
		demo_binary_write_tree(delay, tree);
		demo_binary_add_new_item(delay, tree, 6);
		demo_binary_add_new_item(delay, tree, 7);
		demo_binary_add_new_item(delay, tree, 10);
		demo_binary_add_new_item(delay, tree, 8);
		demo_binary_write_tree(delay, tree);
		demo_create_consistent_presentation(delay, tree);
		demo_back(delay);
	}
	void tree_demo_mode(unsigned delay)
	{
		Tree tree;
		std::vector<std::size_t> path;
		std::vector<Tree_node*> pointers;
		std::size_t number = 0;
		demo_main(delay);
		demo_tree_menu(delay);
		demo_add_new_item_to_tree(delay, tree, 10, path, pointers, number, true, false);
		demo_add_new_item_to_tree(delay, tree, 4, path, pointers, number, true);
		demo_add_new_item_to_tree(delay, tree, 5, path, pointers, number, true);
		path.push_back(1);
		demo_add_new_item_to_tree(delay, tree, 25, path, pointers, number, true);
		demo_write_all_tree(delay, tree);
		demo_add_new_item_to_tree(delay, tree, 26, path, pointers, number, true);
		path.push_back(0);
		demo_add_new_item_to_tree(delay, tree, 125, path, pointers, number, true);
		demo_add_new_item_to_tree(delay, tree, 5, path, pointers, number, true);
		demo_get_pointer_to_item(delay, tree, 5, pointers, number);
		demo_get_item_by_path(delay, tree, pointers[number - 1]->get_path(), pointers, number, false);
		demo_remove_sub_tree_by_path(delay, tree, pointers[number - 2]->get_path(), pointers, number - 1, false);
		path.clear();
		path.push_back(0);
		demo_add_new_item_to_tree(delay, tree, 100, path, pointers, number, true);
		demo_write_all_tree(delay, tree);
		demo_back(delay);
	}
}
void demo_mode()
{
	unsigned delay = correct::read_unsigned("a delay to display data(in milliseconds; normal = 1900)");
	all_demo_mode::tree_demo_mode(delay);
	all_demo_mode::binary_demo_mode(delay);
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