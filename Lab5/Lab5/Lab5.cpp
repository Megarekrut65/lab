﻿// №1, №2, №5, №11, №14, №17, №19, №21
#include <iostream>
#include <vector>
#include <ctime>
#include <conio.h>
#include <Windows.h>
#include "my_correct_read.h"

struct Edge;
struct Graph_matrix;
struct Vertex_node;
struct Graph_structure;
template<class T1, class T2>
void graph_menu(T1&, T2&);

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
    bool connected_graph()
    {
        std::vector<std::size_t> indexes;
        if (!is_connected(indexes, false))
        {
            std::cout << "\nThe graph isn't connected!" << std::endl;
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
    void create_random_graph(std::size_t number_of_vertices, std::size_t number_of_edges, bool orientation, int max_weight)
    {
        if (create_random(number_of_vertices, number_of_edges, orientation, max_weight))
        {
            std::cout << "\nThe graph is created!" << std::endl;
            write_graph();
        }        
    }
    void checking_the_connectivity_of_graph()
    {
        if (connected_graph())
        {
            std::cout << "\nThe graph is connected!" << std::endl;
        }
    }
    void depth_first_search(bool mode)
    {
        std::vector<std::size_t> indexes;
        if (is_connected(indexes, mode))
        {
            std::cout << "\nSearch is finished!\nVertex: " << std::endl;
            for (std::size_t i = 0; i < number_of_vertices; i++)
            {
                std::cout << indexes[i] << " ";
            }
            std::cout << std::endl;
        }
        else
        {
            std::cout << "\nThe graph isn't connected!" << std::endl;
        }      
    }
    void find_paths_between_two_vertices(std::size_t begin_index, std::size_t end_index)
    {
        if (!connected_graph()) return;
        int* distance = dijkstra(begin_index);       
        if (distance[end_index] == INT_MAX)
        {
            std::cout << "\nThe graph is poorly oriented so it cannot be reached from " << begin_index
                << " to " << end_index << "." << std::endl;
        }
        else
        {
            std::cout << "\nThe smallest distance from " << begin_index
                << " to " << end_index << " = " << distance[end_index] << "." << std::endl;
        }
        delete[]distance;
    }   
    void find_path_from_the_vertex_to_everyone_else(std::size_t begin_index)
    {
        if (!connected_graph()) return;
        int* distance = dijkstra(begin_index);
        for (std::size_t i = 0; i < number_of_vertices; i++)
        {
            if (distance[i] == INT_MAX)
            {
                std::cout << "\nThe graph is poorly oriented so it cannot be reached from " << begin_index
                    << " to " << i << "." << std::endl;
            }
            else
            {
                std::cout << "\nThe smallest distance from " << begin_index
                    << " to " << i << " = " << distance[i] << "." << std::endl;
            }
        }       
        delete[]distance;
    }
    void find_paths_between_all_vertices()
    {
        if (!connected_graph()) return;
        for (std::size_t i = 0; i < number_of_vertices; i++)
        {
            std::cout << "\nVertex: " << i << "." << std::endl;
            find_path_from_the_vertex_to_everyone_else(i);
        }
    }
    void topological_sorting()
    {
        if (!orientation)
        {
            std::cout << "\nTopological sorting for directed graph only" << std::endl;
            return;
        }
        if (!connected_graph()) return;
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
            std::cout << "\nThe graph has a cycle!" << std::endl;
            return;
        }
        std::cout << "\nResult: ";
        for (std::size_t i = 0; i < number_of_vertices; i++)
        {
            std::cout << indexes[i] << " ";
        }
        std::cout << std::endl;
    }
    void create_spanning_tree(bool mode)
    {
        if (orientation)
        {
            std::cout << "\nSpanning tree for undirected graph only" << std::endl;
            return;
        }
        Graph_matrix spanning_tree(number_of_vertices, false);
        std::vector<std::size_t> indexes;        
        int total_weight = 0;
        create_spanning_tree_current(spanning_tree, indexes, 0, mode, total_weight);
        if (indexes.size() != number_of_vertices)
        {
            std::cout << "\nThe graph isn't connected!" << std::endl;
            return;
        }
        std::cout << "\nThe spanning tree is created!" << std::endl;
        spanning_tree.write_graph();    
        spanning_tree.clear();
    }
    void create_the_smallest_spanning_tree()
    {
        if (orientation)
        {
            std::cout << "\nSpanning tree for undirected graph only" << std::endl;
            return;
        }
        if (!connected_graph()) return;
        Graph_matrix spanning_tree = kruskal();
        std::cout << "\nThe spanning tree is created!" << std::endl;
        spanning_tree.write_graph();
        spanning_tree.clear();
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
    bool connected_graph()
    {
        std::vector<std::size_t> indexes;
        if (!is_connected(indexes, false))
        {
            std::cout << "\nThe graph isn't connected!" << std::endl;
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
    void create_random_graph(std::size_t number_of_vertices, std::size_t number_of_edges, bool orientation, int max_weight)
    {
        if (create_random(number_of_vertices, number_of_edges, orientation, max_weight))
        {
            std::cout << "\nThe graph is created!" << std::endl;
            write_graph();
        }
    }
    void checking_the_connectivity_of_graph()
    {
        if (connected_graph())
        {
            std::cout << "\nThe graph is connected!" << std::endl;
        }
    }
    void depth_first_search(bool mode)
    {
        std::vector<std::size_t> indexes;
        if (is_connected(indexes, mode))
        {
            std::cout << "\nSearch is finished!\nVertex: " << std::endl;
            for (std::size_t i = 0; i < number_of_vertices; i++)
            {
                std::cout << indexes[i] << " ";
            }
            std::cout << std::endl;
        }
        else
        {
            std::cout << "\nThe graph isn't connected!" << std::endl;
        }
    }
    void find_paths_between_two_vertices(std::size_t begin_index, std::size_t end_index)
    {
        if (!connected_graph()) return;
        int* distance = dijkstra(begin_index);
        if (distance[end_index] == INT_MAX)
        {
            std::cout << "\nThe graph is poorly oriented so it cannot be reached from " << begin_index
                << " to " << end_index << "." << std::endl;
        }
        else
        {
            std::cout << "\nThe smallest distance from " << begin_index
                << " to " << end_index << " = " << distance[end_index] << "." << std::endl;
        }
        delete[]distance;
    }
    void find_path_from_the_vertex_to_everyone_else(std::size_t begin_index)
    {
        if (!connected_graph()) return;
        int* distance = dijkstra(begin_index);
        for (std::size_t i = 0; i < number_of_vertices; i++)
        {
            if (distance[i] == INT_MAX)
            {
                std::cout << "\nThe graph is poorly oriented so it cannot be reached from " << begin_index
                    << " to " << i << "." << std::endl;
            }
            else
            {
                std::cout << "\nThe smallest distance from " << begin_index
                    << " to " << i << " = " << distance[i] << "." << std::endl;
            }
        }
        delete[]distance;
    }
    void find_paths_between_all_vertices()
    {
        if (!connected_graph()) return;
        for (std::size_t i = 0; i < number_of_vertices; i++)
        {
            std::cout << "\nVertex: " << i << "." << std::endl;
            find_path_from_the_vertex_to_everyone_else(i);
        }
    }
    void topological_sorting()
    {
        if (!orientation)
        {
            std::cout << "\nTopological sorting for directed graph only" << std::endl;
            return;
        }
        if (!connected_graph()) return;
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
            std::cout << "\nThe graph has a cycle!" << std::endl;
            return;
        }
        std::cout << "\nResult: ";
        for (std::size_t i = 0; i < number_of_vertices; i++)
        {
            std::cout << indexes[i] << " ";
        }
        std::cout << std::endl;
    }
    void create_spanning_tree(bool mode)
    {
        if (orientation)
        {
            std::cout << "\nSpanning tree for undirected graph only" << std::endl;
            return;
        }
        Graph_structure spanning_tree(number_of_vertices, false);
        std::vector<std::size_t> indexes;
        int total_weight = 0;
        create_spanning_tree_current(spanning_tree, indexes, 0, mode, total_weight);
        if (indexes.size() != number_of_vertices)
        {
            std::cout << "\nThe graph isn't connected!" << std::endl;
            return;
        }
        std::cout << "\nThe spanning tree is created!" << std::endl;
        spanning_tree.write_graph();
        spanning_tree.clear();
    }
    void create_the_smallest_spanning_tree()
    {
        if (orientation)
        {
            std::cout << "\nSpanning tree for undirected graph only" << std::endl;
            return;
        }
        if (!connected_graph()) return;
        Graph_structure spanning_tree = kruskal();
        std::cout << "\nThe spanning tree is created!" << std::endl;
        spanning_tree.write_graph();
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
            << "3)Find paths between all vertices.\n0)Back.\n"
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
            << "2)Create the smallest spanning tree.\n0)Back.\n"
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
void edit_menu(T1& graph, T2& new_graph)
{
    while (true)
    {
        std::cout << "\n\n------------------------------------------------"
            << "\nEdit menu:\n1)Add vertex.\n2)Add edge.\n3)Create random graph.\n"
            << "4).\n0)Back.\n"
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
            std::cout << "\nThe old graph was cleared!" << std::endl;
            return;
        }
            break;       
        case'0': return;       
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
            << "7)Create spanning tree.\n0)Back.\n"
            << "################################################\n\n";
        switch (_getch())
        {
        case '1': edit_menu(graph, new_graph);
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
    std::size_t number_of_vertex = correct::read_size_t("the initial number of vertices in the graph");
    bool orientation = correct::read_bool("True to graph will be directed or False to it will be undirected");
    Graph_matrix graph(number_of_vertex, orientation);
    Graph_structure new_graph(orientation);
    graph_menu(graph, new_graph);
}
void graph_structure_menu()
{
    std::size_t number_of_vertex = correct::read_size_t("the initial number of vertices in the graph");
    bool orientation = correct::read_bool("True to graph will be directed or False to it will be undirected");
    Graph_structure graph(number_of_vertex, orientation);
    Graph_matrix new_graph(orientation);
    graph_menu(graph, new_graph);
}
void interactive_dialog_mode()
{
    
    while (true)
    {
        std::cout << "\nSelect one:\n1)Graph based on adjacency matrix.\n"
            << "2)Graph based on adjacency structure.\n0)Back.\n";
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
void demo_mode()
{
    std::cout << std::endl;
}
void benchmark_mode()
{
    std::cout << std::endl;
}
int main()
{
    while (true)
    {
        std::cout << "Select the application mode:\n1)Interactive dialog mode.\n"
            << "2)Demo mode.\n3)Automatic benchmark mode.\n0)Exit.\n";
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

    return 0;
}