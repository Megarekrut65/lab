// №1, №2, №5, №11, №14, №17, №19, №21
#include <iostream>
#include <vector>
#include <ctime>
#include <conio.h>
#include <Windows.h>
#include <fstream>
#include <chrono>
#include "my_correct_read.h"

struct measurement_result;
struct Edge;
struct Graph_matrix;
struct Vertex_node;
struct Graph_structure;
template<class T1, class T2>
void graph_menu(T1&, T2&);
Graph_structure graph_transformation(Graph_matrix&);
Graph_matrix graph_transformation(Graph_structure&);
template<class T>
void add_edge(T&);
template<class T>
void create_random_graph(T&);
template<class T>
void depth_first_search(T&);
template<class T>
void find_paths_between_two_vertices(T&);
template<class T>
void find_path_from_the_vertex_to_everyone_else(T&);
template<class T>
void create_spanning_tree(T&);
template<class T>
void find_path_menu(T&);
template<class T>
void create_spanning_tree_menu(T&);
template<class T1, class T2>
bool edit_menu(T1&, T2&);
template<class T1, class T2>
void graph_menu(T1&, T2&);
void graph_matrix_menu();
void graph_structure_menu();
void interactive_dialog_mode();

struct measurement_result
{
    std::size_t number_of_vertices;
    std::size_t number_of_edges;
    float time;
    std::size_t size;
    bool orientation;
};
struct Edge
{
    bool contiguity;
    int weight_coefficient;

    Edge()
    {
        contiguity = false;
        weight_coefficient = 0;
    }
    Edge(bool contiguity, int weight_coefficient)
    {
        this->contiguity = contiguity;
        this->weight_coefficient = weight_coefficient;
    }
};
struct Graph_matrix
{
    std::vector<std::vector<Edge>> matrix;
    std::size_t number_of_vertices;
    std::size_t number_of_edges;
    bool orientation;
    int total_weight;
private:
    bool is_index(std::size_t index)
    {
        if (index >= number_of_vertices)
        {
            std::cout << "\nVertex with index: " << index << " isn't in Graph!" << std::endl;
            return false;
        }
        return true;
    }
    bool do_add_index(std::vector<std::size_t>& indexes, std::size_t index)
    {
        for (std::size_t i = 0; i < indexes.size(); i++)
        {
            if (indexes[i] == index) return false;
        }
        indexes.push_back(index);

        return true;
    }
    template<class T>
    void swap(T& a, T& b)
    {
        T temp = a;
        a = b;
        b = temp;
    }
    std::vector<std::size_t> create_numbers(std::size_t index, bool mode)
    {
        std::vector<std::size_t> numbers;
        std::vector<Edge> line = matrix[index];
        for (std::size_t i = 0; i < number_of_vertices; i++) numbers.push_back(i);
        if(!mode) return numbers;
        for (std::size_t i = 0; i < number_of_vertices; i++)
        {
            for (std::size_t j = 0; j < (number_of_vertices - 1 - i); j++)
            {
                if (line[j].weight_coefficient > line[j + 1].weight_coefficient)
                {
                    swap(line[j].weight_coefficient, line[j + 1].weight_coefficient);
                    swap(numbers[j], numbers[j + 1]);
                }
            }
        }
        return numbers;
    }
    void is_connected_current(std::vector<std::size_t>& indexes, std::size_t index, bool mode)
    {
        std::vector<std::size_t> numbers = create_numbers(index, mode);
        for (std::size_t j = 0; j < number_of_vertices; j++)
        {            
            if (matrix[index][numbers[j]].contiguity)
            {
                do_add_index(indexes, index);
                if (index == numbers[j]) continue;
                if (do_add_index(indexes, numbers[j]))
                {
                    is_connected_current(indexes, numbers[j], mode);
                }
            }
        }
    }
    bool is_connected(std::vector<std::size_t>& indexes, bool mode)
    {
        for (std::size_t i = 0; i < number_of_vertices; i++)
        {
            is_connected_current(indexes, i, mode);
            if (indexes.size() == number_of_vertices)
            {
                return true;
            }
            indexes.clear();
        }
        
        return false;
    }  
    std::size_t min_distance(int* distance, bool* is_set)
    {
        int min = INT_MAX;
        std::size_t index = 0;
        for (std::size_t i = 0; i < number_of_vertices; i++)
        {
            if (!is_set[i] && distance[i] <= min)
            {
                min = distance[i];
                index = i;
            }
        }

        return index;
    }
    int* dijkstra(std::size_t begin_index)
    {
        int* distance = new int[number_of_vertices];
        bool* is_set = new bool[number_of_vertices];
        for (std::size_t i = 0; i < number_of_vertices; i++)
        {
            distance[i] = INT_MAX;
            is_set[i] = false;
        }
        distance[begin_index] = 0;
        for (std::size_t i = 0; i < number_of_vertices; i++)
        {
            std::size_t index = min_distance(distance, is_set);
            is_set[index] = true;
            for (std::size_t j = 0; j < number_of_vertices; j++)
            {
                if (!is_set[j] && matrix[index][j].contiguity
                    && distance[index] != INT_MAX
                    && distance[index] + matrix[index][j].weight_coefficient < distance[j])
                    distance[j] = distance[index] + matrix[index][j].weight_coefficient;
            }
        }
        delete[]is_set;
        return distance;
    }
    bool connected_graph(bool show)
    {
        std::vector<std::size_t> indexes;
        if (!is_connected(indexes, false))
        {
            if(show) std::cout << "\nThe graph isn't connected!" << std::endl;
            return false;
        }
        return true;
    }
    std::vector<std::vector<std::size_t>> create_set()
    {
        std::vector<std::vector<std::size_t>> set(number_of_vertices);
        for (std::size_t i = 0; i < number_of_vertices; i++)
        {
            for (std::size_t j = 0; j < number_of_vertices; j++)
            {
                if (matrix[i][j].contiguity) set[j].push_back(i);
            }
        }
        return set;
    }
    void edit_set(std::vector<std::vector<std::size_t>>& set, std::size_t index)
    {
        for (std::size_t i = 0; i < number_of_vertices; i++)
        {
            for (std::size_t j = 0; j < set[i].size(); j++)
            {
                if (set[i][j] == index)
                {
                    set[i].erase(set[i].begin() + j);
                    j--;
                }
            }
        }
    }
    bool is_in_indexes(std::vector<std::size_t> indexes, std::size_t index)
    {
        for (std::size_t i = 0; i < indexes.size(); i++)
        {
            if (indexes[i] == index) return true;
        }
        return false;
    }
    void create_spanning_tree_current(Graph_matrix& spanning_tree, std::vector<std::size_t>& indexes, std::size_t index, bool mode, int& total_weight)
    {
        std::vector<std::size_t> numbers = create_numbers(index, mode);
        for (std::size_t j = 0; j < number_of_vertices; j++)
        {
            if (matrix[index][numbers[j]].contiguity)
            {
                do_add_index(indexes, index);
                if (index == numbers[j]) continue;
                if (do_add_index(indexes, numbers[j]))
                {
                    spanning_tree.add_edge(index, numbers[j], matrix[index][numbers[j]].weight_coefficient, false);
                    total_weight += matrix[index][numbers[j]].weight_coefficient;
                    create_spanning_tree_current(spanning_tree, indexes, numbers[j], mode, total_weight);
                }
            }
        }
    }
    Graph_matrix kruskal()
    {
        Graph_matrix spanning_tree(number_of_vertices, false);
        std::vector<std::size_t> belongs(number_of_vertices);
        for (std::size_t i = 0; i < number_of_vertices; i++)
        {
            belongs[i] = i;
        }
        std::size_t first_index;
        std::size_t second_index;
        for (std::size_t vertices = 1; vertices < number_of_vertices; vertices++)
        {
            int min = INT_MAX;
            for (std::size_t i = 0; i < number_of_vertices; i++)
            {
                for (std::size_t j = 0; j < number_of_vertices; j++)
                {
                    if (matrix[i][j].contiguity && (min > matrix[i][j].weight_coefficient)
                        && (belongs[i] != belongs[j]))
                    {
                        min = matrix[i][j].weight_coefficient;
                        first_index = i;
                        second_index = j;
                    }
                }
            }
            if (belongs[first_index] != belongs[second_index])
            {
                spanning_tree.add_edge(first_index, second_index, min, false);
                std::size_t temp = belongs[second_index];
                belongs[second_index] = belongs[first_index];
                for (std::size_t i = 0; i < number_of_vertices; i++)
                {
                    if (belongs[i] == temp)
                    {
                        belongs[i] = belongs[first_index];
                    }
                }
            }
        }
        return spanning_tree;
    }
    void create_graph(std::size_t number_of_vertices, bool orientation)
    {
        this->number_of_vertices = number_of_vertices;
        number_of_edges = 0;
        this->orientation = orientation;
        std::vector<Edge> new_line(number_of_vertices, Edge());
        for (std::size_t i = 0; i < number_of_vertices; i++)
        {
            matrix.push_back(new_line);
        }
        total_weight = 0;
    }
    bool create_random(std::size_t number_of_vertices, std::size_t number_of_edges, bool orientation, int max_weight)
    {
        clear();
        create_graph(number_of_vertices, orientation);
        srand(unsigned(time(0)));
        for (std::size_t i = 0; i < number_of_vertices; i++)
        {
            for (std::size_t j = 0; j < number_of_vertices; j++)
            {
                if (this->number_of_edges >= number_of_edges) return true;
                if ((i != j) && !matrix[i][j].contiguity)
                {
                    add_edge(i, j, rand() % max_weight, false);
                }
            }
        }
        if (this->number_of_edges < number_of_edges)
        {
            for (std::size_t i = 0; i < number_of_vertices; i++)
            {
                if (this->number_of_edges >= number_of_edges) return true;
                if (!matrix[i][i].contiguity)
                {
                    add_edge(i, i, rand() % max_weight, false);
                }
            }
        }
        if (this->number_of_edges < number_of_edges)
        {
            std::cout << "\nThere are too many edges!" << std::endl;
            clear();
            return false;
        }

        return false;
    }
public:
    Graph_matrix(bool orientation)
    {
        number_of_vertices = 0;
        number_of_edges = 0;
        this->orientation = orientation;
        total_weight = 0;
    }
    Graph_matrix(std::size_t number_of_vertices, bool orientation)
    {
        create_graph(number_of_vertices, orientation);
    }       
    void add_vertex(bool show = true)
    {
        for (std::size_t i = 0; i < number_of_vertices; i++)
        {
            matrix[i].push_back(Edge());
        }
        number_of_vertices++;
        std::vector<Edge> new_line(number_of_vertices, Edge());
        matrix.push_back(new_line);
        if (show) std::cout << "\nThe vertex is added!" << std::endl;
    }
    void add_edge(std::size_t begin_index, std::size_t end_index, int weight_coefficient, bool show = true)
    {
        if (!is_index(begin_index) || !is_index(end_index)) return;
        if (matrix[begin_index][end_index].contiguity)
        {
            if (show) std::cout << "\nThe edge already exists between the vertices!" << std::endl;
            return;
        }
        Edge node = Edge(true, weight_coefficient);
        matrix[begin_index][end_index] = node;
        if(!orientation) matrix[end_index][begin_index] = node;
        number_of_edges++;
        total_weight += weight_coefficient;
        if(show) std::cout <<"\nThe edge added!" << std::endl;
    }
    void write_graph()
    {
        if (number_of_vertices == 0)
        {
            std::cout << "\nThe graph is empty!" << std::endl;
            return;
        }
        std::cout << "\nGraph:\n" << std::endl;
        for (std::size_t i = 0; i < number_of_vertices; i++)
        {
            std::cout << "| ";
            for (std::size_t j = 0; j < number_of_vertices; j++)
            {
                if (matrix[i][j].contiguity) std::cout << "1 ";
                else std::cout << "0 ";
            }
            std::cout << "|" << std::endl;
        }
        std::cout << "\nVertices: " << number_of_vertices << std::endl;
        std::cout << "Edges: " << number_of_edges << std::endl;
        std::cout << "Total weight: " << total_weight << std::endl;
    }    
    void create_random_graph(std::size_t number_of_vertices, std::size_t number_of_edges, bool orientation, int max_weight, bool show = true)
    {
        if (create_random(number_of_vertices, number_of_edges, orientation, max_weight))
        {
            if (!show) return;
            std::cout << "\nThe graph is created!" << std::endl;
            write_graph();
        }        
    }
    void checking_the_connectivity_of_graph(bool show = true)
    {
        if (connected_graph(show))
        {
            if(show) std::cout << "\nThe graph is connected!" << std::endl;
        }
    }
    void depth_first_search(bool mode, bool show = true)
    {
        std::vector<std::size_t> indexes;
        if (is_connected(indexes, mode))
        {
            if (!show) return;
            std::cout << "\nSearch is finished!\nVertex: " << std::endl;
            for (std::size_t i = 0; i < number_of_vertices; i++)
            {
                std::cout << indexes[i] << " ";
            }
            std::cout << std::endl;
        }
        else
        {
            if (show) std::cout << "\nThe graph isn't connected!" << std::endl;
        }      
    }
    void find_paths_between_two_vertices(std::size_t begin_index, std::size_t end_index, bool show = true)
    {
        if (!connected_graph(show)) return;
        int* distance = dijkstra(begin_index);       
        if (distance[end_index] == INT_MAX)
        {
            if(show) std::cout << "\nThe graph is poorly oriented so it cannot be reached from " << begin_index
                << " to " << end_index << "." << std::endl;
        }
        else
        {
            if (show) std::cout << "\nThe smallest distance from " << begin_index
                << " to " << end_index << " = " << distance[end_index] << "." << std::endl;
        }
        delete[]distance;
    }   
    void find_path_from_the_vertex_to_everyone_else(std::size_t begin_index, bool show = true)
    {
        if (!connected_graph(show)) return;
        int* distance = dijkstra(begin_index);
        for (std::size_t i = 0; i < number_of_vertices; i++)
        {
            if (distance[i] == INT_MAX)
            {
                if(show) std::cout << "\nThe graph is poorly oriented so it cannot be reached from " << begin_index
                    << " to " << i << "." << std::endl;
            }
            else
            {
                if (show) std::cout << "\nThe smallest distance from " << begin_index
                    << " to " << i << " = " << distance[i] << "." << std::endl;
            }
        }       
        delete[]distance;
    }
    void find_paths_between_all_vertices(bool show = true)
    {
        if (!connected_graph(show)) return;
        for (std::size_t i = 0; i < number_of_vertices; i++)
        {
            if(show) std::cout << "\nVertex: " << i << "." << std::endl;
            find_path_from_the_vertex_to_everyone_else(i, show);
        }
    }
    void topological_sorting(bool show = true)
    {
        if (!orientation)
        {
            if(show) std::cout << "\nTopological sorting for directed graph only" << std::endl;
            return;
        }
        if (!connected_graph(show)) return;
        std::vector<std::size_t> indexes;
        std::vector<std::vector<std::size_t>> set = create_set(); 
        for (std::size_t i = 0; i < number_of_vertices; i++)
        {           
            if ((set[i].size() == 0 ) && (!is_in_indexes(indexes, i)))
            {
                indexes.push_back(i);
                edit_set(set, i);
                i = -1;
            }
        }
        if (indexes.size() != number_of_vertices)
        {
            if (show) std::cout << "\nThe graph has a cycle!" << std::endl;
            return;
        }
        if (!show) return;
        std::cout << "\nResult: ";
        for (std::size_t i = 0; i < number_of_vertices; i++)
        {
            std::cout << indexes[i] << " ";
        }
        std::cout << std::endl;
    }
    void create_spanning_tree(bool mode, bool show = true)
    {
        if (orientation)
        {
            if(show) std::cout << "\nSpanning tree for undirected graph only" << std::endl;
            return;
        }
        Graph_matrix spanning_tree(number_of_vertices, false);
        std::vector<std::size_t> indexes;        
        int total_weight = 0;
        create_spanning_tree_current(spanning_tree, indexes, 0, mode, total_weight);
        if (indexes.size() != number_of_vertices)
        {
            if (show) std::cout << "\nThe graph isn't connected!" << std::endl;
            return;
        }
        if (show) std::cout << "\nThe spanning tree is created!" << std::endl;
        if (show) spanning_tree.write_graph();
        spanning_tree.clear();
    }
    void create_the_smallest_spanning_tree(bool show = true)
    {
        if (orientation)
        {
            if (show) std::cout << "\nSpanning tree for undirected graph only" << std::endl;
            return;
        }
        if (!connected_graph(show)) return;
        Graph_matrix spanning_tree = kruskal();
        if (show) std::cout << "\nThe spanning tree is created!" << std::endl;
        if (show) spanning_tree.write_graph();
        spanning_tree.clear();
    }  
    std::size_t get_size()
    {
        std::size_t size = 0;
        size += number_of_vertices * number_of_vertices * sizeof(Edge)
            + sizeof(number_of_vertices) + sizeof(number_of_edges) 
            + sizeof(orientation) + sizeof(total_weight);

        return size;
    }
    void clear()
    {
        for (std::size_t i = 0; i < number_of_vertices; i++)
        {
            matrix[i].clear();
        }
        matrix.clear();
        number_of_vertices = 0;
        number_of_edges = 0;
        orientation = false;
        total_weight = 0;
    }
};
struct Vertex_node
{
    std::size_t index;
    Vertex_node* next;
    int weight_coefficient;

    Vertex_node()
    {
        index = 0;
        next = nullptr;
        weight_coefficient = 0;
    }
    Vertex_node(std::size_t index, Vertex_node* next)
    {
        this->index = index;
        this->next = next;
        weight_coefficient = 0;
    }
    Vertex_node(std::size_t index, Vertex_node* next, int weight_coefficient)
    {
        this->index = index;
        this->next = next;
        this->weight_coefficient = weight_coefficient;
    }
};
struct Graph_structure
{
    std::vector<Vertex_node*> list;
    std::size_t number_of_vertices;
    std::size_t number_of_edges;
    bool orientation;
    int total_weight;
private:
    bool is_index(std::size_t index)
    {
        if (index >= number_of_vertices)
        {
            std::cout << "\nVertex with index: " << index << " isn't in Graph!" << std::endl;
            return false;
        }
        return true;
    }
    bool do_add_index(std::vector<std::size_t>& indexes, std::size_t index)
    {
        for (std::size_t i = 0; i < indexes.size(); i++)
        {
            if (indexes[i] == index) return false;
        }
        indexes.push_back(index);

        return true;
    }
    bool add_node(std::size_t begin_index, std::size_t end_index, int weight_coefficient)
    {
        if (is_edge(begin_index, end_index)) return false;
        Vertex_node* current = list[begin_index]->next;
        if (!current)
        {
            list[begin_index]->next = new Vertex_node(end_index, nullptr, weight_coefficient);
            return true;
        }
        Vertex_node* temp_node = list[begin_index];
        for (; current; current = current->next)
        {
            if (current->index > end_index)
            {
                temp_node->next = new Vertex_node(end_index, current, weight_coefficient);
                return true;
            }
            temp_node = current;
        }
        temp_node->next = new Vertex_node(end_index, nullptr, weight_coefficient);
        
        return true;
    }   
    template<class T>
    void swap(T& a, T& b)
    {
        T temp = a;
        a = b;
        b = temp;
    }
    std::vector<std::size_t> create_numbers(std::size_t index, bool mode)
    {
        std::vector<std::size_t> numbers;
        std::vector<int> line;
        for (Vertex_node* current = list[index]->next; current; current = current->next)
        {
            line.push_back(current->weight_coefficient);
            numbers.push_back(current->index);
        }
        if (!mode) return numbers;       
        for (std::size_t i = 0; i < line.size(); i++)
        {
            for (std::size_t j = 0; j < (line.size() - 1 - i); j++)
            {
                if (line[j] > line[j + 1])
                {
                    swap(line[j], line[j + 1]);
                    swap(numbers[j], numbers[j + 1]);
                }
            }
        }
        return numbers;
    }
    void is_connected_current(std::vector<std::size_t>& indexes, std::size_t index, bool mode)
    {
        std::vector<std::size_t> numbers = create_numbers(index, mode);
        for (std::size_t j = 0; j < numbers.size(); j++)
        {
            if (is_edge(index, numbers[j]))
            {
                do_add_index(indexes, index);
                if (index == numbers[j]) continue;
                if (do_add_index(indexes, numbers[j]))
                {
                    is_connected_current(indexes, numbers[j], mode);
                }
            }
        }
    }
    bool is_connected(std::vector<std::size_t>& indexes, bool mode)
    {
        for (std::size_t i = 0; i < number_of_vertices; i++)
        {
            is_connected_current(indexes, i, mode);
            if (indexes.size() == number_of_vertices)
            {
                return true;
            }
            indexes.clear();
        }

        return false;
    }
    bool connected_graph(bool show)
    {
        std::vector<std::size_t> indexes;
        if (!is_connected(indexes, false))
        {
            if(show) std::cout << "\nThe graph isn't connected!" << std::endl;
            return false;
        }
        return true;
    }   
    std::size_t min_distance(int* distance, bool* is_set)
    {
        int min = INT_MAX;
        std::size_t index = 0;
        for (std::size_t i = 0; i < number_of_vertices; i++)
        {
            if (!is_set[i] && distance[i] <= min)
            {
                min = distance[i];
                index = i;
            }
        }

        return index;
    }
    int* dijkstra(std::size_t begin_index)
    {
        int* distance = new int[number_of_vertices];
        bool* is_set = new bool[number_of_vertices];
        for (std::size_t i = 0; i < number_of_vertices; i++)
        {
            distance[i] = INT_MAX;
            is_set[i] = false;
        }
        distance[begin_index] = 0;
        for (std::size_t i = 0; i < number_of_vertices; i++)
        {
            std::size_t index = min_distance(distance, is_set);
            is_set[index] = true;
            for (std::size_t j = 0; j < number_of_vertices; j++)
            {
                int weight_coefficient = give_weight(index, j);
                if (!is_set[j] && is_edge(index, j)
                    && distance[index] != INT_MAX
                    && distance[index] + weight_coefficient < distance[j])
                    distance[j] = distance[index] + weight_coefficient;
            }
        }
        delete[]is_set;
        return distance;
    }
    std::vector<std::vector<std::size_t>> create_set()
    {
        std::vector<std::vector<std::size_t>> set(number_of_vertices);
        for (std::size_t i = 0; i < number_of_vertices; i++)
        {
            for (std::size_t j = 0; j < number_of_vertices; j++)
            {
                if (is_edge(i, j)) set[j].push_back(i);
            }
        }
        return set;
    }
    void edit_set(std::vector<std::vector<std::size_t>>& set, std::size_t index)
    {
        for (std::size_t i = 0; i < number_of_vertices; i++)
        {
            for (std::size_t j = 0; j < set[i].size(); j++)
            {
                if (set[i][j] == index)
                {
                    set[i].erase(set[i].begin() + j);
                    j--;
                }
            }
        }
    }
    bool is_in_indexes(std::vector<std::size_t> indexes, std::size_t index)
    {
        for (std::size_t i = 0; i < indexes.size(); i++)
        {
            if (indexes[i] == index) return true;
        }
        return false;
    }
    void create_spanning_tree_current(Graph_structure& spanning_tree, std::vector<std::size_t>& indexes, std::size_t index, bool mode, int& total_weight)
    {
        std::vector<std::size_t> numbers = create_numbers(index, mode);
        for (std::size_t j = 0; j < numbers.size(); j++)
        {
            if (is_edge(index, numbers[j]))
            {
                do_add_index(indexes, index);
                if (index == numbers[j]) continue;
                if (do_add_index(indexes, numbers[j]))
                {
                    int weight_coefficient = give_weight(index, numbers[j]);
                    spanning_tree.add_edge(index, numbers[j], weight_coefficient, false);
                    total_weight += weight_coefficient;
                    create_spanning_tree_current(spanning_tree, indexes, numbers[j], mode, total_weight);
                }
            }
        }
    }
    void clear_node(std::size_t index)
    {
        Vertex_node* current = list[index];
        list[index] = nullptr;
        while (current)
        {
            Vertex_node* temp_node = current;
            current = current->next;
            delete temp_node;
            temp_node = nullptr;
        }
    }
    Graph_structure kruskal()
    {
        Graph_structure spanning_tree(number_of_vertices, false);
        std::vector<std::size_t> belongs(number_of_vertices);
        for (std::size_t i = 0; i < number_of_vertices; i++)
        {
            belongs[i] = i;
        }
        std::size_t first_index;
        std::size_t second_index;
        for (std::size_t vertices = 1; vertices < number_of_vertices; vertices++)
        {
            int min = INT_MAX;
            for (std::size_t i = 0; i < number_of_vertices; i++)
            {
                for (std::size_t j = 0; j < number_of_vertices; j++)
                {
                    int weight_coefficient = give_weight(i, j);
                    if (is_edge(i, j) && (min > weight_coefficient)
                        && (belongs[i] != belongs[j]))
                    {
                        min = weight_coefficient;
                        first_index = i;
                        second_index = j;
                    }
                }
            }
            if (belongs[first_index] != belongs[second_index])
            {
                spanning_tree.add_edge(first_index, second_index, min, false);
                std::size_t temp = belongs[second_index];
                belongs[second_index] = belongs[first_index];
                for (std::size_t i = 0; i < number_of_vertices; i++)
                {
                    if (belongs[i] == temp)
                    {
                        belongs[i] = belongs[first_index];
                    }
                }
            }
        }
        return spanning_tree;
    }
    void create_graph(std::size_t number_of_vertices, bool orientation)
    {
        number_of_edges = 0;
        this->number_of_vertices = 0;
        this->orientation = orientation;
        total_weight = 0;
        for (std::size_t i = 0; i < number_of_vertices; i++)
        {
            add_vertex(false);
        }
    }
    bool create_random(std::size_t number_of_vertices, std::size_t number_of_edges, bool orientation, int max_weight)
    {
        clear();
        create_graph(number_of_vertices, orientation);
        srand(unsigned(time(0)));
        for (std::size_t i = 0; i < number_of_vertices; i++)
        {
            for (std::size_t j = 0; j < number_of_vertices; j++)
            {
                if (this->number_of_edges >= number_of_edges) return true;
                if ((i != j) && !is_edge(i, j))
                {
                    add_edge(i, j, rand() % max_weight, false);
                }
            }
        }
        if (this->number_of_edges < number_of_edges)
        {
            for (std::size_t i = 0; i < number_of_vertices; i++)
            {
                if (this->number_of_edges >= number_of_edges) return true;
                if (!is_edge(i, i))
                {
                    add_edge(i, i, rand() % max_weight, false);
                }
            }
        }
        if (this->number_of_edges < number_of_edges)
        {
            std::cout << "\nThere are too many edges!" << std::endl;
            clear();
            return false;
        }

        return false;
    }
public:
    Graph_structure(bool orientation)
    {
        number_of_vertices = 0;
        number_of_edges = 0;
        this->orientation = orientation;
        total_weight = 0;
    }
    Graph_structure(std::size_t number_of_vertices, bool orientation)
    {        
        create_graph(number_of_vertices, orientation);
    }
    void add_vertex(bool show = true)
    {
        list.push_back(new Vertex_node(number_of_vertices, nullptr));
        number_of_vertices++;
        if (show) std::cout << "\nThe vertex is added!" << std::endl;
    }   
    void add_edge(std::size_t begin_index, std::size_t end_index, int weight_coefficient, bool show = true)
    {
        if (!is_index(begin_index) || !is_index(end_index)) return;
        if (!add_node(begin_index, end_index, weight_coefficient))
        {
            if (show) std::cout << "\nThe edge already exists between the vertices!" << std::endl;
            return;
        }
        if (!orientation && (begin_index != end_index))
        {
            if (!add_node(end_index, begin_index, weight_coefficient))
            {
                if (show) std::cout << "\nThe edge already exists between the vertices!" << std::endl;
                return;
            }
        }
        total_weight += weight_coefficient;
        if (show) std::cout << "\nThe edge added!" << std::endl;
        number_of_edges++;
    }
    void write_graph()
    {
        if (number_of_vertices == 0)
        {
            std::cout << "\nThe graph is empty!" << std::endl;
            return;
        }
        std::cout << "\nGraph:\n" << std::endl;
        for (std::size_t i = 0; i < number_of_vertices; i++)
        {            
            std::cout << "Vertex: [" << list[i]->index << "]-> { ";
            for (Vertex_node* current = list[i]->next; current; current = current->next)
            {
                std::cout << current->index << "-> ";
            }
            std::cout << "# }" << std::endl;
        }
        std::cout << "\nVertices: " << number_of_vertices << std::endl;
        std::cout << "Edges: " << number_of_edges << std::endl;
        std::cout << "Total weight: " << total_weight << std::endl;
    }
    void create_random_graph(std::size_t number_of_vertices, std::size_t number_of_edges, bool orientation, int max_weight, bool show = true)
    {
        if (create_random(number_of_vertices, number_of_edges, orientation, max_weight))
        {
            if (!show) return;
            std::cout << "\nThe graph is created!" << std::endl;
            write_graph();
        }
    }
    void checking_the_connectivity_of_graph(bool show = true)
    {
        if (connected_graph(show))
        {
            if(show) std::cout << "\nThe graph is connected!" << std::endl;
        }
    }
    void depth_first_search(bool mode, bool show = true)
    {
        std::vector<std::size_t> indexes;
        if (is_connected(indexes, mode))
        {
            if (!show) return;
            std::cout << "\nSearch is finished!\nVertex: " << std::endl;
            for (std::size_t i = 0; i < number_of_vertices; i++)
            {
                std::cout << indexes[i] << " ";
            }
            std::cout << std::endl;
        }
        else
        {
            if(show) std::cout << "\nThe graph isn't connected!" << std::endl;
        }
    }
    void find_paths_between_two_vertices(std::size_t begin_index, std::size_t end_index, bool show = true)
    {
        if (!connected_graph(show)) return;
        int* distance = dijkstra(begin_index);
        if (distance[end_index] == INT_MAX)
        {
            if(show) std::cout << "\nThe graph is poorly oriented so it cannot be reached from " << begin_index
                << " to " << end_index << "." << std::endl;
        }
        else
        {
            if(show) std::cout << "\nThe smallest distance from " << begin_index
                << " to " << end_index << " = " << distance[end_index] << "." << std::endl;
        }
        delete[]distance;
    }
    void find_path_from_the_vertex_to_everyone_else(std::size_t begin_index, bool show = true)
    {
        if (!connected_graph(show)) return;
        int* distance = dijkstra(begin_index);
        for (std::size_t i = 0; i < number_of_vertices; i++)
        {
            if (distance[i] == INT_MAX)
            {
                if(show) std::cout << "\nThe graph is poorly oriented so it cannot be reached from " << begin_index
                    << " to " << i << "." << std::endl;
            }
            else
            {
                if (show) std::cout << "\nThe smallest distance from " << begin_index
                    << " to " << i << " = " << distance[i] << "." << std::endl;
            }
        }
        delete[]distance;
    }
    void find_paths_between_all_vertices(bool show = true)
    {
        if (!connected_graph(show)) return;
        for (std::size_t i = 0; i < number_of_vertices; i++)
        {
            if(show) std::cout << "\nVertex: " << i << "." << std::endl;
            find_path_from_the_vertex_to_everyone_else(i, show);
        }
    }
    void topological_sorting(bool show = true)
    {
        if (!orientation)
        {
            if(show) std::cout << "\nTopological sorting for directed graph only" << std::endl;
            return;
        }
        if (!connected_graph(show)) return;
        std::vector<std::size_t> indexes;
        std::vector<std::vector<std::size_t>> set = create_set();
        for (std::size_t i = 0; i < number_of_vertices; i++)
        {
            if ((set[i].size() == 0) && (!is_in_indexes(indexes, i)))
            {
                indexes.push_back(i);
                edit_set(set, i);
                i = -1;
            }
        }
        if (indexes.size() != number_of_vertices)
        {
            if (show) std::cout << "\nThe graph has a cycle!" << std::endl;
            return;
        }
        if (!show) return;
        std::cout << "\nResult: ";
        for (std::size_t i = 0; i < number_of_vertices; i++)
        {
            std::cout << indexes[i] << " ";
        }
        std::cout << std::endl;
    }
    void create_spanning_tree(bool mode, bool show = true)
    {
        if (orientation)
        {
            if(show) std::cout << "\nSpanning tree for undirected graph only" << std::endl;
            return;
        }
        Graph_structure spanning_tree(number_of_vertices, false);
        std::vector<std::size_t> indexes;
        int total_weight = 0;
        create_spanning_tree_current(spanning_tree, indexes, 0, mode, total_weight);
        if (indexes.size() != number_of_vertices)
        {
            if (show) std::cout << "\nThe graph isn't connected!" << std::endl;
            return;
        }
        if (show) std::cout << "\nThe spanning tree is created!" << std::endl;
        if (show) spanning_tree.write_graph();
        spanning_tree.clear();
    }
    void create_the_smallest_spanning_tree(bool show = true)
    {
        if (orientation)
        {
            if(show) std::cout << "\nSpanning tree for undirected graph only" << std::endl;
            return;
        }
        if (!connected_graph(show)) return;
        Graph_structure spanning_tree = kruskal();
        if (show) std::cout << "\nThe spanning tree is created!" << std::endl;
        if (show) spanning_tree.write_graph();
        spanning_tree.clear();
    }
    bool is_edge(std::size_t begin_index, std::size_t end_index)
    {
        for (Vertex_node* current = list[begin_index]->next; current; current = current->next)
        {
            if (current->index == end_index) return true;
        }
        return false;
    }
    int give_weight(std::size_t index_i, std::size_t index_j)
    {
        for (Vertex_node* current = list[index_i]->next; current; current = current->next)
        {
            if (current->index == index_j) return current->weight_coefficient;
        }

        return INT_MAX;
    }
    std::size_t get_size()
    {
        std::size_t size = 0;
        std::size_t number_of_node = 0;
        for (std::size_t i = 0; i < number_of_vertices; i++)
        {
            for (Vertex_node* current = list[i]; current; current = current->next)
            {
                number_of_node++;
            }
        }
        size += number_of_node*sizeof(Vertex_node*) + sizeof(number_of_vertices)
            + sizeof(number_of_edges) + sizeof(orientation) + sizeof(total_weight);

        return size;
    }
    void clear()
    {
        for (std::size_t i = 0; i < number_of_vertices; i++)
        {
            clear_node(i);
        }
        list.clear();
        number_of_vertices = 0;
        number_of_edges = 0;
        orientation = false;
        total_weight = 0;
    }
};

Graph_structure graph_transformation(Graph_matrix& graph)
{
    Graph_structure new_graph(graph.number_of_vertices, graph.orientation);
    for (std::size_t i = 0; i < graph.number_of_vertices; i++)
    {
        for (std::size_t j = 0; j < graph.number_of_vertices; j++)
        {
            if (graph.matrix[i][j].contiguity)
            {
                new_graph.add_edge(i, j, graph.matrix[i][j].weight_coefficient, false);
            }
        }
    }
    graph.clear();
    return new_graph;
}
Graph_matrix graph_transformation(Graph_structure& graph)
{
    Graph_matrix new_graph(graph.number_of_vertices, graph.orientation);
    for (std::size_t i = 0; i < graph.number_of_vertices; i++)
    {
        for (std::size_t j = 0; j < graph.number_of_vertices; j++)
        {
            if (graph.is_edge(i, j))
            {
                new_graph.add_edge(i, j, graph.give_weight(i, j), false);
            }
        }
    }
    graph.clear();
    return new_graph;
}
template<class T>
void add_edge(T& graph)
{
    std::size_t begin_index = correct::read_size_t("the index of begin vertex");
    std::size_t end_index = correct::read_size_t("the index of end vertex");
    int weight_coefficient = correct::read_int("weight coefficient of edge");
    graph.add_edge(begin_index, end_index, weight_coefficient);
}
template<class T>
void create_random_graph(T& graph)
{
    std::size_t number_of_vertices = correct::read_size_t("the number of vertices");
    std::size_t number_of_edges = correct::read_size_t("the number of edges");
    bool orientation = correct::read_bool("True to graph will be directed or False to it will be undirected");
    int weight_coefficient = correct::read_int("maximum weight coefficient of edge");
    graph.create_random_graph(number_of_vertices, number_of_edges, orientation, weight_coefficient);
}
template<class T>
void depth_first_search(T& graph)
{    
    bool mode = correct::read_bool("True to bypass is performed on the edges taking into account the weight coefficient\nor False to bypass is performed on the edges of any order");
    graph.depth_first_search(mode);
}
template<class T>
void find_paths_between_two_vertices(T& graph)
{
    std::size_t begin_index = correct::read_size_t("the index of begin vertex");
    std::size_t end_index = correct::read_size_t("the index of end vertex");
    graph.find_paths_between_two_vertices(begin_index, end_index);
}
template<class T>
void find_path_from_the_vertex_to_everyone_else(T& graph)
{
    std::size_t begin_index = correct::read_size_t("the index of begin vertex");
    graph.find_path_from_the_vertex_to_everyone_else(begin_index);
}
template<class T>
void create_spanning_tree(T& graph)
{
    bool mode = correct::read_bool("True to bypass is performed on the edges taking into account the weight coefficient\nor False to bypass is performed on the edges of any order");
    graph.create_spanning_tree(mode);
}
template<class T>
void find_path_menu(T& graph)
{
    while (true)
    {                     
        std::cout << "\n\n------------------------------------------------"
            << "\nFind path:\n1)Find path between two vertices.\n"
            << "2)Find paths from the vertex to everyone else.\n"
            << "3)Find paths between all vertices.\n0)Back." << std::endl
            << "------------------------------------------------\n\n";
        switch (_getch())
        {
        case '1': find_paths_between_two_vertices(graph);
            break;
        case '2': find_path_from_the_vertex_to_everyone_else(graph);
            break;
        case '3': graph.find_paths_between_all_vertices();
            break;        
        case '0': return;       
        default: std::cout << "\nPress the correct key!" << std::endl;
        }
    }
}
template<class T>
void create_spanning_tree_menu(T& graph)
{
    while (true)
    {
        std::cout << "\n\n------------------------------------------------"
            << "\nSpanning tree:\n1)Create spanning tree.\n"
            << "2)Create the smallest spanning tree.\n0)Back." << std::endl
            << "------------------------------------------------\n\n";
        switch (_getch())
        {
        case '1': create_spanning_tree(graph);
            break;
        case '2': graph.create_the_smallest_spanning_tree();
            break;
        case '0': return;        
        break;
        default: std::cout << "\nPress the correct key!" << std::endl;
        }
    }
}
template<class T1, class T2>
bool edit_menu(T1& graph, T2& new_graph)
{
    while (true)
    {
        std::cout << "\n\n------------------------------------------------"
            << "\nEdit menu:\n1)Add vertex.\n2)Add edge.\n3)Create random graph.\n"
            << "4)Transformation.\n0)Back." << std::endl
            << "------------------------------------------------\n\n";
        switch (_getch())
        {
        case '1': graph.add_vertex();
            break;
        case '2': add_edge(graph);
            break;
        case '3': create_random_graph(graph);
            break;
        case '4': 
        {
            new_graph.clear();
            new_graph = graph_transformation(graph);
            std::cout << "\nTransformation is finished!" << std::endl;
            graph_menu(new_graph, graph);
            return true;
        }
            break;       
        case'0': return false;       
        default: std::cout << "\nPress the correct key!" << std::endl;
        }
    }
}
template<class T1, class T2>
void graph_menu(T1& graph, T2& new_graph)
{
    while (true)
    {
        std::cout << "\n\n################################################" 
            << "\nMenu:\n1)Edit graph.\n2)Write graph.\n3)Checking the connectivity of graph.\n"
            << "4)Depth-first search.\n5)Find paths.\n6)Topological sorting.\n"
            << "7)Create spanning tree.\n0)Back." << std::endl
            << "################################################\n\n";
        switch (_getch())
        {
        case '1': if (edit_menu(graph, new_graph)) return;
            break;
        case '2': graph.write_graph();
            break;
        case '3': graph.checking_the_connectivity_of_graph();
            break;
        case '4': depth_first_search(graph);
            break;
        case '5': find_path_menu(graph);
            break;
        case '6': graph.topological_sorting();
            break;
        case '7': create_spanning_tree_menu(graph);
            break;
        case'0': 
        {
            graph.clear();
            return;
        }
        break;
        default: std::cout << "\nPress the correct key!" << std::endl;
        }
    }
}
void graph_matrix_menu()
{
    std::size_t number_of_vertices = correct::read_size_t("the initial number of vertices in the graph");
    bool orientation = correct::read_bool("True to graph will be directed or False to it will be undirected");
    Graph_matrix graph(number_of_vertices, orientation);
    Graph_structure new_graph(orientation);
    graph_menu(graph, new_graph);
}
void graph_structure_menu()
{
    std::size_t number_of_vertices = correct::read_size_t("the initial number of vertices in the graph");
    bool orientation = correct::read_bool("True to graph will be directed or False to it will be undirected");
    Graph_structure graph(number_of_vertices, orientation);
    Graph_matrix new_graph(orientation);
    graph_menu(graph, new_graph);
}
void interactive_dialog_mode()
{  
    while (true)
    {
        std::cout << "\nSelect one:\n1)Graph based on adjacency matrix.\n"
            << "2)Graph based on adjacency structure.\n0)Back." << std::endl;
        switch (_getch())
        {
        case '1': graph_matrix_menu();
            break;
        case '2': graph_structure_menu();
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
namespace all_benchmark_mode
{
    void clear_result_files(std::string paths[], int number_of_files, std::string name_of_type)
    {
        for (int i = 0; i < number_of_files; i++)
        {
            std::ofstream file(name_of_type + paths[i] + ".txt");
            file.close();
        }
    }
    Graph_matrix copy_graph(Graph_matrix& graph)
    {
        Graph_matrix new_graph(graph.number_of_vertices, graph.orientation);
        for (std::size_t i = 0; i < graph.number_of_vertices; i++)
        {
            for (std::size_t j = 0; j < graph.number_of_vertices; j++)
            {
                if (graph.matrix[i][j].contiguity)
                {
                    new_graph.add_edge(i, j, graph.matrix[i][j].weight_coefficient, false);
                }
            }
        }
        return new_graph;
    }
    Graph_structure copy_graph(Graph_structure& graph)
    {
        Graph_structure new_graph(graph.number_of_vertices, graph.orientation);
        for (std::size_t i = 0; i < graph.number_of_vertices; i++)
        {
            for (std::size_t j = 0; j < graph.number_of_vertices; j++)
            {
                if (graph.is_edge(i, j))
                {
                    new_graph.add_edge(i, j, graph.give_weight(i, j), false);
                }
            }
        }
        return new_graph;
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
    void add_result_to_file(measurement_result result, const std::string& name_of_files)
    {
        std::ofstream file(name_of_files + ".txt", std::ios_base::app);
        file << "Number of vertices = " << result.number_of_vertices << "." << std::endl;
        file << "Number of edges = " << result.number_of_edges << "." << std::endl;
        file << "Time = " << result.time << "." << std::endl;
        file << "Size = " << result.size << "." << std::endl;
        file << "Orientation = ";
        if (result.orientation) file << "directed";
        else file << "undirected";
        file << ".\n" << std::endl;
        file.close();
    }
    template<class T>
    void measurement_add_vertex(T& graph, std::size_t number_of_vertices, std::size_t number_of_edges)
    {
        graph.add_vertex(false);
    }
    template<class T>
    void measurement_add_edge(T& graph, std::size_t number_of_vertices, std::size_t number_of_edges)
    {
        graph.add_edge(rand() % number_of_vertices, rand() % number_of_vertices, rand() % number_of_edges, false);
    }
    template<class T>
    void measurement_create_random(T& graph, std::size_t number_of_vertices, std::size_t number_of_edges)
    {
        graph.create_random_graph(number_of_vertices, number_of_edges, false, number_of_edges, false);
    }
    template<class T>
    void measurement_checking_the_connectivity_of_graph(T& graph, std::size_t number_of_vertices, std::size_t number_of_edges)
    {
        graph.checking_the_connectivity_of_graph(false);
    }
    template<class T>
    void measurement_depth_first_search(T& graph, std::size_t number_of_vertices, std::size_t number_of_edges)
    {
        graph.depth_first_search(true, false);
    }
    template<class T>
    void measurement_find_paths_between_two_vertices(T& graph, std::size_t number_of_vertices, std::size_t number_of_edges)
    {
        graph.find_paths_between_two_vertices(rand() % number_of_vertices, rand() % number_of_vertices, false);
    }
    template<class T>
    void measurement_find_path_from_the_vertex_to_everyone_else(T& graph, std::size_t number_of_vertices, std::size_t number_of_edges)
    {
        graph.find_path_from_the_vertex_to_everyone_else(rand() % number_of_vertices, false);
    }
    template<class T>
    void measurement_find_paths_between_all_vertices(T& graph, std::size_t number_of_vertices, std::size_t number_of_edges)
    {
        graph.find_paths_between_all_vertices(false);
    }
    template<class T>
    void measurement_topological_sorting(T& graph, std::size_t number_of_vertices, std::size_t number_of_edges)
    {
        graph.topological_sorting(false);
    }
    template<class T>
    void measurement_create_spanning_tree(T& graph, std::size_t number_of_vertices, std::size_t number_of_edges)
    {
        graph.create_spanning_tree(true, false);
    }
    template<class T>
    void measurement_create_the_smallest_spanning_tree(T& graph, std::size_t number_of_vertices, std::size_t number_of_edges)
    {
        graph.create_the_smallest_spanning_tree(false);
    }
    template<class T>
    void measurement_clear(T& graph, std::size_t number_of_vertices, std::size_t number_of_edges)
    {
        graph.clear();
    }
    template<class T>
    float measurement(T& graph, std::size_t index, bool orientation, std::size_t number_of_vertices, std::size_t number_of_edges, const std::string& name_of_functions, const std::string& name_of_type)//measures the sort time of an array
    {
        srand(unsigned(time(0)));
        const int number_of_functions = 12;
        void(*all_functions[number_of_functions])(T&, std::size_t, std::size_t) = {
            measurement_add_vertex, measurement_add_edge, measurement_create_random,
            measurement_checking_the_connectivity_of_graph,
            measurement_depth_first_search, measurement_find_paths_between_two_vertices,
            measurement_find_path_from_the_vertex_to_everyone_else,
            measurement_find_paths_between_all_vertices, measurement_topological_sorting,
            measurement_create_spanning_tree, measurement_create_the_smallest_spanning_tree,
            measurement_clear };
        T new_graph = copy_graph(graph);
        auto the_start = std::chrono::high_resolution_clock::now();
        auto the_end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> duration;
        the_start = std::chrono::high_resolution_clock::now();
        all_functions[index](new_graph, number_of_vertices, number_of_edges);
        the_end = std::chrono::high_resolution_clock::now();
        duration = the_end - the_start;
        measurement_result result;
        result.number_of_vertices = number_of_vertices;
        result.number_of_edges = number_of_edges;
        result.size = graph.get_size();
        result.time = duration.count();
        result.orientation = orientation;
        add_result_to_file(result, name_of_type + name_of_functions);
        std::cout << "\nTime of " << name_of_functions << " = " << result.time << std::endl;
        std::cout << "Size = " << result.size << std::endl;

        return result.time;
    }
    template<class T>
    void benchmark_mode_menu(T& graph, const std::string& name_of_type)
    {
        const int number_of_functions = 12;
        std::string name_of_functions[number_of_functions] = { "Add vertex", "Add edge", 
        "Create random graph", "Checking the connectivity of graph", "Depth-first search",
        "Find path between two vertices", "Find paths from the vertex to everyone else",
        "Find paths between all vertices", "Topological sorting",
        "Create spanning tree", "Create the smallest spanning tree", "Clear graph" };
        clear_result_files(name_of_functions, number_of_functions, name_of_type);
        bool is_one_second = false, are_ten_seconds = false;
        std::size_t number_of_vertices = 5, number_of_edges = number_of_vertices;
        std::size_t copy_number = number_of_vertices, coefficient = 2;
        bool orientation = false;
        while (true)
        {
            float time;
            std::cout << "\nNumber of vertices = " << number_of_vertices << std::endl;
            std::cout << "Number of edges = " << number_of_edges << std::endl;
            for (int j = 0; j < 2; j++)
            {
                orientation = !orientation;
                std::cout << "\nOrientation = ";
                if (orientation) std::cout << "directed";
                else std::cout << "undirected";
                std::cout << "." << std::endl;
                graph.create_random_graph(number_of_vertices, number_of_edges, orientation, number_of_edges, false);
                for (std::size_t i = 0; i < number_of_functions; i++)
                {
                    time = measurement(graph, i, orientation, number_of_vertices, number_of_edges, name_of_functions[i], name_of_type);
                    if (time > 1) is_one_second = true;
                    if (time > 10) are_ten_seconds = true;
                }
                graph.clear();
                if (are_ten_seconds) break;
            }
            if (are_ten_seconds) break;
            number_of_vertices = set_number(is_one_second, copy_number, coefficient);
            number_of_edges = number_of_vertices;
        }
        std::cout << "\nResults of measurements of program in the following files:\n"
            << name_of_type + name_of_functions[0] + ".txt\n" << name_of_type + name_of_functions[1] + ".txt\n"
            << name_of_type + name_of_functions[2] + ".txt\n" << name_of_type + name_of_functions[3] + ".txt\n"
            << name_of_type + name_of_functions[4] + ".txt\n" << name_of_type + name_of_functions[5] + ".txt\n"
            << name_of_type + name_of_functions[6] + ".txt\n" << name_of_type + name_of_functions[7] + ".txt\n"
            << name_of_type + name_of_functions[8] + ".txt\n" << name_of_type + name_of_functions[9] + ".txt\n"
            << name_of_type + name_of_functions[10] + ".txt\n" << name_of_type + name_of_functions[11] + ".txt\n"
            << std::endl;
    }
    void benchmark_mode()
    {
        Graph_matrix matrix(false);
        std::cout << "\nAdjacency Matrix." << std::endl;
        benchmark_mode_menu(matrix, "Adjacency Matrix ");
        Graph_structure structure(false);
        std::cout << "\nAdjacency Structure." << std::endl;
        benchmark_mode_menu(structure, "Adjacency Structure ");
        std::cout << std::endl;
    }
}
namespace all_demo_mode
{
    void demo_interactive(unsigned delay)
    {
        std::cout << "\nSelect the application mode:\n1)Interactive dialog mode.\n"
            << "2)Demo mode.\n3)Automatic benchmark mode.\n0)Exit.\n";
        Sleep(delay);
        std::cout << "\nSelect the application mode:\n1)Interactive dialog mode. <-press\n"
            << "2)Demo mode.\n3)Automatic benchmark mode.\n0)Exit.\n";
        Sleep(delay);
    }
    template<class T>
    void demo_read_value(unsigned delay, T value, std::string sentence)
    {
        std::cout << "\nEnter " << sentence << ": <-write and press <Enter>" << std::endl;
        Sleep(delay);
        std::cout << "Enter " << sentence << ": " << value << std::endl;
        Sleep(delay);
    }
    void demo_select(unsigned delay, bool mode, std::string sentence)
    {
        if (mode) std::cout << "\nSelect " << sentence << ":\n1)True. <-press\n2)False." << std::endl;
        else std::cout << "\nSelect " << sentence << ":\n1)True.\n2)False. <-press" << std::endl;
        Sleep(delay);
    }
    void demo_matrix_menu(unsigned delay, Graph_matrix& graph, bool orientation, std::size_t number_of_vertices)
    {
        std::cout << "\nSelect one:\n1)Graph based on adjacency matrix. <-press\n"
            << "2)Graph based on adjacency structure.\n0)Back.\n";
        Sleep(delay);
        demo_read_value(delay, number_of_vertices, "the initial number of vertices in the graph");
        demo_select(delay, orientation, "True to graph will be directed or False to it will be undirected");
        graph = Graph_matrix(number_of_vertices, orientation);
    }
    void demo_structure_menu(unsigned delay, Graph_structure& graph, bool orientation, std::size_t number_of_vertices)
    {
        std::cout << "\nSelect one:\n1)Graph based on adjacency matrix.\n"
            << "2)Graph based on adjacency structure. <-press\n0)Back.\n";
        Sleep(delay);
        demo_read_value(delay, number_of_vertices, "the initial number of vertices in the graph");
        demo_select(delay, orientation, "True to graph will be directed or False to it will be undirected");
        graph = Graph_structure(number_of_vertices, orientation);
    }
    void demo_edit_menu(unsigned delay)
    {
        std::cout << "\n\n################################################"
            << "\nMenu:\n1)Edit graph. <-press\n2)Write graph.\n3)Checking the connectivity of graph.\n"
            << "4)Depth-first search.\n5)Find paths.\n6)Topological sorting.\n"
            << "7)Create spanning tree.\n0)Back." << std::endl
            << "################################################\n\n";
        Sleep(delay);
    }
    template<class T>
    void demo_add_vertex(unsigned delay, T& graph)
    {
        std::cout << "\n\n------------------------------------------------"
            << "\nEdit menu:\n1)Add vertex. <-press\n2)Add edge.\n3)Create random graph.\n"
            << "4)Transformation.\n0)Back." << std::endl
            << "------------------------------------------------\n\n";
        Sleep(delay);
        graph.add_vertex();
        Sleep(delay);
    }
    template<class T>
    void demo_add_edge(unsigned delay, T& graph, std::size_t begin_index, std::size_t end_index, int weight_coefficient)
    {
        std::cout << "\n\n------------------------------------------------"
            << "\nEdit menu:\n1)Add vertex.\n2)Add edge. <-press\n3)Create random graph.\n"
            << "4)Transformation.\n0)Back." << std::endl
            << "------------------------------------------------\n\n";
        Sleep(delay);
        demo_read_value(delay, begin_index, "the index of begin vertex");
        demo_read_value(delay, end_index, "the index of end vertex");
        demo_read_value(delay, weight_coefficient, "weight coefficient of edge");
        graph.add_edge(begin_index, end_index, weight_coefficient);
        Sleep(delay);
    }
    template<class T>
    void demo_create_random(unsigned delay, T& graph, bool orientation, std::size_t number_of_vertices, std::size_t number_of_edges, int max_weight_coefficient)
    {
        std::cout << "\n\n------------------------------------------------"
            << "\nEdit menu:\n1)Add vertex.\n2)Add edge.\n3)Create random graph. <-press\n"
            << "4)Transformation.\n0)Back." << std::endl
            << "------------------------------------------------\n\n";
        Sleep(delay);
        demo_read_value(delay, number_of_vertices, "the number of vertices");
        demo_read_value(delay, number_of_edges, "the number of edges");
        demo_select(delay, orientation, "True to graph will be directed or False to it will be undirected");
        demo_read_value(delay, max_weight_coefficient, "maximum weight coefficient of edge");
        graph.create_random_graph(number_of_vertices, number_of_edges, orientation, max_weight_coefficient);
        Sleep(delay);
    }
    template<class T1, class T2>
    void demo_graph_transformation(unsigned delay, T1& graph, T2& new_graph)
    {
        std::cout << "\n\n------------------------------------------------"
            << "\nEdit menu:\n1)Add vertex.\n2)Add edge.\n3)Create random graph.\n"
            << "4)Transformation. <-press\n0)Back." << std::endl
            << "------------------------------------------------\n\n";
        Sleep(delay);
        new_graph.clear();
        new_graph = graph_transformation(graph);
        std::cout << "\nTransformation is finished!" << std::endl;
        Sleep(delay);
    }
    void demo_back_from_edit_menu(unsigned delay)
    {
        std::cout << "\n\n------------------------------------------------"
            << "\nEdit menu:\n1)Add vertex.\n2)Add edge.\n3)Create random graph.\n"
            << "4)Transformation.\n0)Back. <-press" << std::endl
            << "------------------------------------------------\n\n";
        Sleep(delay);
    }
    template<class T>
    void demo_write_graph(unsigned delay, T& graph)
    {
        std::cout << "\n\n################################################"
            << "\nMenu:\n1)Edit graph.\n2)Write graph. <-press\n3)Checking the connectivity of graph.\n"
            << "4)Depth-first search.\n5)Find paths.\n6)Topological sorting.\n"
            << "7)Create spanning tree.\n0)Back." << std::endl
            << "################################################\n\n";
        Sleep(delay);
        graph.write_graph();
        Sleep(delay);
    }
    template<class T>
    void demo_checking_the_connectivity(unsigned delay, T& graph)
    {
        std::cout << "\n\n################################################"
            << "\nMenu:\n1)Edit graph.\n2)Write graph.\n3)Checking the connectivity of graph. <-press\n"
            << "4)Depth-first search.\n5)Find paths.\n6)Topological sorting.\n"
            << "7)Create spanning tree.\n0)Back." << std::endl
            << "################################################\n\n";
        Sleep(delay);
        graph.checking_the_connectivity_of_graph();
        Sleep(delay);
    }
    template<class T>
    void demo_depth_first_search(unsigned delay, T& graph, bool mode)
    {
        std::cout << "\n\n################################################"
            << "\nMenu:\n1)Edit graph.\n2)Write graph.\n3)Checking the connectivity of graph.\n"
            << "4)Depth-first search. <-press\n5)Find paths.\n6)Topological sorting.\n"
            << "7)Create spanning tree.\n0)Back." << std::endl
            << "################################################\n\n";
        Sleep(delay);
        demo_select(delay, mode, "True to bypass is performed on the edges taking into account the weight coefficient\nor False to bypass is performed on the edges of any order");      
        graph.depth_first_search(mode);
        Sleep(delay);
    }
    void demo_find_path_menu(unsigned delay)
    {
        std::cout << "\n\n################################################"
            << "\nMenu:\n1)Edit graph.\n2)Write graph.\n3)Checking the connectivity of graph.\n"
            << "4)Depth-first search.\n5)Find paths. <-press\n6)Topological sorting.\n"
            << "7)Create spanning tree.\n0)Back." << std::endl
            << "################################################\n\n";
        Sleep(delay);
    }
    template<class T>
    void demo_find_paths_between_two_vertices(unsigned delay, T& graph, std::size_t begin_index, std::size_t end_index)
    {
        std::cout << "\n\n------------------------------------------------"
            << "\nFind path:\n1)Find path between two vertices. <-press\n"
            << "2)Find paths from the vertex to everyone else.\n"
            << "3)Find paths between all vertices.\n0)Back." << std::endl
            << "------------------------------------------------\n\n";
        Sleep(delay);
        demo_read_value(delay, begin_index, "the index of begin vertex");
        demo_read_value(delay, end_index, "the index of end vertex");
        graph.find_paths_between_two_vertices(begin_index, end_index);
        Sleep(delay);
    }
    template<class T>
    void demo_find_path_from_the_vertex_to_everyone_else(unsigned delay, T& graph, std::size_t begin_index)
    {
        std::cout << "\n\n------------------------------------------------"
            << "\nFind path:\n1)Find path between two vertices.\n"
            << "2)Find paths from the vertex to everyone else. <-press\n"
            << "3)Find paths between all vertices.\n0)Back." << std::endl
            << "------------------------------------------------\n\n";
        Sleep(delay);
        demo_read_value(delay, begin_index, "the index of begin vertex");
        graph.find_path_from_the_vertex_to_everyone_else(begin_index);
        Sleep(delay);
    }
    template<class T>
    void demo_find_paths_between_all_vertices(unsigned delay, T& graph)
    {
        std::cout << "\n\n------------------------------------------------"
            << "\nFind path:\n1)Find path between two vertices.\n"
            << "2)Find paths from the vertex to everyone else.\n"
            << "3)Find paths between all vertices. <-press\n0)Back." << std::endl
            << "------------------------------------------------\n\n";
        Sleep(delay);
        graph.find_paths_between_all_vertices();
        Sleep(4*delay);
    }
    void demo_find_path_back(unsigned delay)
    {
        std::cout << "\n\n------------------------------------------------"
            << "\nFind path:\n1)Find path between two vertices.\n"
            << "2)Find paths from the vertex to everyone else.\n"
            << "3)Find paths between all vertices.\n0)Back. <-press" << std::endl
            << "------------------------------------------------\n\n";
        Sleep(delay);
    }
    template<class T>
    void demo_topological_sorting(unsigned delay, T& graph)
    {
        std::cout << "\n\n################################################"
            << "\nMenu:\n1)Edit graph.\n2)Write graph.\n3)Checking the connectivity of graph.\n"
            << "4)Depth-first search.\n5)Find paths.\n6)Topological sorting. <-press\n"
            << "7)Create spanning tree.\n0)Back." << std::endl
            << "################################################\n\n";
        Sleep(delay);
        graph.topological_sorting();
        Sleep(delay);
    }
    void demo_create_spanning_tree_menu(unsigned delay)
    {
        std::cout << "\n\n################################################"
            << "\nMenu:\n1)Edit graph.\n2)Write graph.\n3)Checking the connectivity of graph.\n"
            << "4)Depth-first search.\n5)Find paths.\n6)Topological sorting.\n"
            << "7)Create spanning tree. <-press\n0)Back." << std::endl
            << "################################################\n\n";
        Sleep(delay);
    }
    template<class T>
    void create_spanning_tree(unsigned delay, T& graph, bool mode)
    {
        std::cout << "\n\n------------------------------------------------"
            << "\nSpanning tree:\n1)Create spanning tree. <-press\n"
            << "2)Create the smallest spanning tree.\n0)Back." << std::endl
            << "------------------------------------------------\n\n";
        Sleep(delay);
        demo_select(delay, mode, "True to bypass is performed on the edges taking into account the weight coefficient\nor False to bypass is performed on the edges of any order");
        graph.create_spanning_tree(mode); 
        Sleep(2*delay);
    }
    template<class T>
    void demo_create_the_smallest_spanning_tree(unsigned delay, T& graph)
    {
        std::cout << "\n\n------------------------------------------------"
            << "\nSpanning tree:\n1)Create spanning tree.\n"
            << "2)Create the smallest spanning tree. <-press\n0)Back." << std::endl
            << "------------------------------------------------\n\n";
        Sleep(delay);
        graph.create_the_smallest_spanning_tree();
        Sleep(2 * delay);
    }
    void demo_spanning_tree_menu_back(unsigned delay)
    {
        std::cout << "\n\n------------------------------------------------"
            << "\nSpanning tree:\n1)Create spanning tree.\n"
            << "2)Create the smallest spanning tree.\n0)Back. <-press" << std::endl
            << "------------------------------------------------\n\n";
        Sleep(delay);
    }
    void demo_back(unsigned delay)
    {
        std::cout << "\n\n################################################"
            << "\nMenu:\n1)Edit graph.\n2)Write graph.\n3)Checking the connectivity of graph.\n"
            << "4)Depth-first search.\n5)Find paths.\n6)Topological sorting.\n"
            << "7)Create spanning tree.\n0)Back. <-press" << std::endl
            << "################################################\n\n";
        Sleep(delay);
        std::cout << "\nSelect one:\n1)Graph based on adjacency matrix.\n"
            << "2)Graph based on adjacency structure.\n0)Back. <-press" << std::endl;
        Sleep(delay);
    }
    void demo_mode()
    {
        unsigned delay = correct::read_unsigned("a delay to display data(in milliseconds; normal = 1900)");
        std::cout << "\nThe start of the demo mode(press <Ctrl + C> to exit)" << std::endl;
        Graph_matrix graph_matrix(false);
        Graph_structure graph_structure(false);
        demo_interactive(delay);
        demo_matrix_menu(delay, graph_matrix, false, 5);
        demo_edit_menu(delay);
        demo_add_vertex(delay, graph_matrix);
        demo_add_vertex(delay, graph_matrix);
        demo_add_edge(delay, graph_matrix, 3, 1, 10);
        demo_add_edge(delay, graph_matrix, 0, 4, 14);
        demo_add_edge(delay, graph_matrix, 4, 2, 61);
        demo_back_from_edit_menu(delay);
        demo_write_graph(delay, graph_matrix);
        demo_checking_the_connectivity(delay, graph_matrix);
        demo_edit_menu(delay);
        demo_add_edge(delay, graph_matrix, 2, 3, 13);
        demo_add_edge(delay, graph_matrix, 1, 6, 29);
        demo_add_edge(delay, graph_matrix, 0, 5, 1);
        demo_add_edge(delay, graph_matrix, 6, 5, 73);
        demo_add_edge(delay, graph_matrix, 4, 5, 47);
        demo_back_from_edit_menu(delay);
        demo_write_graph(delay, graph_matrix);
        demo_checking_the_connectivity(delay, graph_matrix);
        demo_find_path_menu(delay);
        demo_find_paths_between_two_vertices(delay, graph_matrix, 3, 5);
        demo_find_paths_between_two_vertices(delay, graph_matrix, 1, 4);
        demo_find_path_from_the_vertex_to_everyone_else(delay, graph_matrix, 0);
        demo_find_paths_between_all_vertices(delay, graph_matrix);
        demo_find_path_back(delay);
        demo_topological_sorting(delay, graph_matrix);
        demo_create_spanning_tree_menu(delay);
        create_spanning_tree(delay, graph_matrix, true);
        demo_create_the_smallest_spanning_tree(delay, graph_matrix);
        demo_spanning_tree_menu_back(delay);
        demo_edit_menu(delay);
        demo_create_random(delay, graph_matrix, true, 6, 3, 100);
        demo_back_from_edit_menu(delay);
        demo_edit_menu(delay);
        demo_add_edge(delay, graph_matrix, 2, 4, 13);
        demo_add_edge(delay, graph_matrix, 1, 5, 17);
        demo_add_edge(delay, graph_matrix, 2, 5, 11);
        demo_add_edge(delay, graph_matrix, 3, 4, 99);
        demo_add_edge(delay, graph_matrix, 4, 5, 47);
        demo_back_from_edit_menu(delay);
        demo_write_graph(delay, graph_matrix);
        demo_checking_the_connectivity(delay, graph_matrix);
        demo_topological_sorting(delay, graph_matrix);
        demo_edit_menu(delay);
        demo_graph_transformation(delay, graph_matrix, graph_structure);
        demo_write_graph(delay, graph_structure);
        demo_edit_menu(delay);
        demo_add_edge(delay, graph_structure, 5, 0, 77);
        demo_add_edge(delay, graph_structure, 3, 1, 142);
        demo_back_from_edit_menu(delay);
        demo_write_graph(delay, graph_structure);
        demo_find_path_menu(delay);
        demo_find_paths_between_all_vertices(delay, graph_structure);
        demo_find_path_back(delay);
        demo_back(delay);
        std::cout << "\nThe end of the demo mode\n" << std::endl;
        Sleep(delay);
    }
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
        case '2': all_demo_mode::demo_mode();
            break;
        case '3': all_benchmark_mode::benchmark_mode();
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