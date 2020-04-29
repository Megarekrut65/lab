// №1, №2, №5, №11, №14, №17, №19, №21
#include <iostream>
#include <vector>

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
private:
    std::vector<std::vector<Edge>> matrix;
    std::size_t number_of_vertex;
    std::size_t number_of_edge;
    bool orientation;
    int total_weight;

    bool is_index(std::size_t index)
    {
        if (index >= number_of_vertex)
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
        for (std::size_t i = 0; i < number_of_vertex; i++) numbers.push_back(i);
        if(!mode) return numbers;
        for (std::size_t i = 0; i < number_of_vertex; i++)
        {
            for (std::size_t j = 0; j < (number_of_vertex - 1 - i); j++)
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
        for (std::size_t j = 0; j < number_of_vertex; j++)
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
        for (std::size_t i = 0; i < number_of_vertex; i++)
        {
            is_connected_current(indexes, i, mode);
            if (indexes.size() == number_of_vertex)
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
        for (std::size_t i = 0; i < number_of_vertex; i++)
        {
            if (!is_set[i] && distance[i] <= min)
            {
                min = distance[i];
                index = i;
            }
        }

        return index;
    }
    int* dijkstra(std::size_t vertex)
    {
        int* distance = new int[number_of_vertex];
        bool* is_set = new bool[number_of_vertex];
        for (std::size_t i = 0; i < number_of_vertex; i++)
        {
            distance[i] = INT_MAX;
            is_set[i] = false;
        }
        distance[vertex] = 0;
        for (std::size_t i = 0; i < number_of_vertex; i++)
        {
            std::size_t index = min_distance(distance, is_set);
            is_set[index] = true;
            for (std::size_t j = 0; j < number_of_vertex; j++)
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
        std::vector<std::vector<std::size_t>> set(number_of_vertex);
        for (std::size_t i = 0; i < number_of_vertex; i++)
        {
            for (std::size_t j = 0; j < number_of_vertex; j++)
            {
                if (matrix[i][j].contiguity) set[j].push_back(i);
            }
        }
        return set;
    }
    void edit_set(std::vector<std::vector<std::size_t>>& set, std::size_t index)
    {
        for (std::size_t i = 0; i < number_of_vertex; i++)
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
    bool is_in_vertices(std::vector<std::size_t> vertices, std::size_t index)
    {
        for (std::size_t i = 0; i < vertices.size(); i++)
        {
            if (vertices[i] == index) return true;
        }
        return false;
    }
    void create_spanning_tree_current(Graph_matrix& spanning_tree, std::vector<std::size_t>& indexes, std::size_t index, bool mode, int& total_weight)
    {
        std::vector<std::size_t> numbers = create_numbers(index, mode);
        for (std::size_t j = 0; j < number_of_vertex; j++)
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
        Graph_matrix spanning_tree(number_of_vertex, false);
        std::vector<std::size_t> belongs(number_of_vertex);
        for (std::size_t i = 0; i < number_of_vertex; i++)
        {
            belongs[i] = i;
        }
        std::size_t first_index;
        std::size_t second_index;
        for (std::size_t vertices = 1; vertices < number_of_vertex; vertices++)
        {
            int min = INT_MAX;
            for (std::size_t i = 0; i < number_of_vertex; i++)
            {
                for (std::size_t j = 0; j < number_of_vertex; j++)
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
                for (std::size_t i = 0; i < number_of_vertex; i++)
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
    void create_graph(std::size_t number_of_vertex, bool orientation)
    {
        this->number_of_vertex = number_of_vertex;
        number_of_edge = 0;
        this->orientation = orientation;
        std::vector<Edge> new_line(number_of_vertex, Edge());
        for (std::size_t i = 0; i < number_of_vertex; i++)
        {
            matrix.push_back(new_line);
        }
        total_weight = 0;
    }
    bool create_random(std::size_t number_of_vertex, std::size_t number_of_edge, bool orientation, int max_weight)
    {
        clear();
        create_graph(number_of_vertex, orientation);
        for (std::size_t i = 0; i < number_of_vertex; i++)
        {
            for (std::size_t j = 0; j < number_of_vertex; j++)
            {
                if (this->number_of_edge >= number_of_edge) return true;
                if ((i != j) && !matrix[i][j].contiguity)
                {
                    add_edge(i, j, rand() % max_weight, false);
                }
            }
        }
        if (this->number_of_edge < number_of_edge)
        {
            for (std::size_t i = 0; i < number_of_vertex; i++)
            {
                if (this->number_of_edge >= number_of_edge) return true;
                if (!matrix[i][i].contiguity)
                {
                    add_edge(i, i, rand() % max_weight, false);
                }
            }
        }
        if (this->number_of_edge < number_of_edge)
        {
            std::cout << "\nThere are too many edges!" << std::endl;
            clear();
            return false;
        }
    }
public:
    Graph_matrix(bool orientation)
    {
        number_of_vertex = 0;
        number_of_edge = 0;
        this->orientation = orientation;
        total_weight = 0;
    }
    Graph_matrix(std::size_t number_of_vertex, bool orientation)
    {
        create_graph(number_of_vertex, orientation);
    }       
    void add_vertex()
    {
        for (std::size_t i = 0; i < number_of_vertex; i++)
        {
            matrix[i].push_back(Edge());
        }
        number_of_vertex++;
        std::vector<Edge> new_line(number_of_vertex, Edge());
        matrix.push_back(new_line);
    }
    void add_edge(std::size_t i_vertex, std::size_t j_vertex, int weight_coefficient, bool show = true)
    {
        if (!is_index(i_vertex) || !is_index(j_vertex)) return;
        if (matrix[i_vertex][j_vertex].contiguity)
        {
            if (show) std::cout << "\nThe edge already exists between the vertices!" << std::endl;
            return;
        }
        Edge node = Edge(true, weight_coefficient);
        matrix[i_vertex][j_vertex] = node;
        if(!orientation) matrix[j_vertex][i_vertex] = node;
        number_of_edge++;
        total_weight += weight_coefficient;
        if(show) std::cout <<"\nThe edge added!" << std::endl;
    }
    void write_graph()
    {
        std::cout << "\nGraph:\n" << std::endl;
        for (std::size_t i = 0; i < number_of_vertex; i++)
        {
            std::cout << "| ";
            for (std::size_t j = 0; j < number_of_vertex; j++)
            {
                if (matrix[i][j].contiguity) std::cout << "1 ";
                else std::cout << "0 ";
            }
            std::cout << "|" << std::endl;
        }
        std::cout << "\nVertices: " << number_of_vertex << std::endl;
        std::cout << "Edges: " << number_of_edge << std::endl;
        std::cout << "Total weight: " << total_weight << std::endl;
    }    
    void create_random_graph(std::size_t number_of_vertex, std::size_t number_of_edge, bool orientation, int max_weight)
    {
        if (create_random(number_of_vertex, number_of_edge, orientation, max_weight))
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
            for (std::size_t i = 0; i < number_of_vertex; i++)
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
    void find_paths_between_two_vertices(std::size_t first_vertex, std::size_t second_vertex)
    {
        if (!connected_graph()) return;
        int* distance = dijkstra(first_vertex);       
        if (distance[second_vertex] == INT_MAX)
        {
            std::cout << "\nThe graph is poorly oriented so it cannot be reached from " << first_vertex
                << " to " << second_vertex << "." << std::endl;
        }
        else
        {
            std::cout << "\nThe smallest distance from " << first_vertex
                << " to " << second_vertex << " = " << distance[second_vertex] << "." << std::endl;
        }
        delete[]distance;
    }   
    void find_path_from_the_vertex_to_everyone_else(std::size_t vertex)
    {
        if (!connected_graph()) return;
        int* distance = dijkstra(vertex);
        for (std::size_t i = 0; i < number_of_vertex; i++)
        {
            if (distance[i] == INT_MAX)
            {
                std::cout << "\nThe graph is poorly oriented so it cannot be reached from " << vertex
                    << " to " << i << "." << std::endl;
            }
            else
            {
                std::cout << "\nThe smallest distance from " << vertex
                    << " to " << i << " = " << distance[i] << "." << std::endl;
            }
        }       
        delete[]distance;
    }
    void find_paths_between_all_vertices()
    {
        if (!connected_graph()) return;
        for (std::size_t i = 0; i < number_of_vertex; i++)
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
        std::vector<std::size_t> vertices;
        std::vector<std::vector<std::size_t>> set = create_set(); 
        for (std::size_t i = 0; i < number_of_vertex; i++)
        {           
            if ((set[i].size() == 0 ) && (!is_in_vertices(vertices, i)))
            {
                vertices.push_back(i);
                edit_set(set, i);
                i = -1;
            }
        }
        if (vertices.size() != number_of_vertex)
        {
            std::cout << "\nThe graph has a cycle!" << std::endl;
            return;
        }
        std::cout << "\nResult: ";
        for (std::size_t i = 0; i < number_of_vertex; i++)
        {
            std::cout << vertices[i] << " ";
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
        Graph_matrix spanning_tree(number_of_vertex, false);
        std::vector<std::size_t> indexes;        
        int total_weight = 0;
        create_spanning_tree_current(spanning_tree, indexes, 0, mode, total_weight);
        if (indexes.size() != number_of_vertex)
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
        for (std::size_t i = 0; i < number_of_vertex; i++)
        {
            matrix[i].clear();
        }
        matrix.clear();
        number_of_vertex = 0;
        number_of_edge = 0;
        orientation = false;
        total_weight = 0;
    }
};
struct Graph_node
{
    std::size_t vertex;
    Graph_node* next;
    int weight_coefficient;

    Graph_node()
    {
        vertex = 0;
        next = nullptr;
        weight_coefficient = 0;
    }
    Graph_node(std::size_t vertex, Graph_node* next)
    {
        this->vertex = vertex;
        this->next = next;
        weight_coefficient = 0;
    }
    Graph_node(std::size_t vertex, Graph_node* next, int weight_coefficient)
    {
        this->vertex = vertex;
        this->next = next;
        this->weight_coefficient = weight_coefficient;
    }
};
struct Graph_list
{
private:
    std::vector<Graph_node*> list;
    std::size_t number_of_vertex;
    std::size_t number_of_edge;
    bool orientation;
    int total_weight;

    bool is_index(std::size_t index)
    {
        if (index >= number_of_vertex)
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
    bool add_node(std::size_t first_vertex, std::size_t second_vertex, int weight_coefficient)
    {
        if (is_edge(first_vertex, second_vertex)) return false;
        Graph_node* current = list[first_vertex]->next;
        if (!current)
        {
            list[first_vertex]->next = new Graph_node(second_vertex, nullptr, weight_coefficient);
            return true;
        }
        Graph_node* temp_node = list[first_vertex];
        for (; current; current = current->next)
        {
            if (current->vertex > second_vertex)
            {
                temp_node->next = new Graph_node(second_vertex, current, weight_coefficient);
                return true;
            }
            temp_node = current;
        }
        temp_node->next = new Graph_node(second_vertex, nullptr, weight_coefficient);
        
        return true;
    }
    bool is_edge(std::size_t first_vertex, std::size_t second_vertex)
    {
        for (Graph_node* current = list[first_vertex]; current; current = current->next)
        {
            if (current->vertex == second_vertex) return true;
        }
        return false;
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
        for (Graph_node* current = list[index]->next; current; current = current->next)
        {
            line.push_back(current->weight_coefficient);
            numbers.push_back(current->vertex);
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
        for (std::size_t i = 0; i < number_of_vertex; i++)
        {
            is_connected_current(indexes, i, mode);
            if (indexes.size() == number_of_vertex)
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
public:
    Graph_list(bool orientation)
    {
        number_of_vertex = 0;
        number_of_edge = 0;
        this->orientation = orientation;
        total_weight = 0;
    }
    Graph_list(std::size_t number_of_vertex, bool orientation)
    {        
        number_of_edge = 0;
        this->number_of_vertex = 0;
        this->orientation = orientation;
        total_weight = 0;
        for (std::size_t i = 0; i < number_of_vertex; i++)
        {
            add_vertex();
        }
    }
    void add_vertex()
    {
        list.push_back(new Graph_node(number_of_vertex, nullptr));
        number_of_vertex++;
    }   
    void add_edge(std::size_t i_vertex, std::size_t j_vertex, int weight_coefficient, bool show = true)
    {
        if (!is_index(i_vertex) || !is_index(j_vertex)) return;
        if (!add_node(i_vertex, j_vertex, weight_coefficient))
        {
            if (show) std::cout << "\nThe edge already exists between the vertices!" << std::endl;
            return;
        }
        if (!orientation && (i_vertex != j_vertex))
        {
            if (!add_node(j_vertex, i_vertex, weight_coefficient))
            {
                if (show) std::cout << "\nThe edge already exists between the vertices!" << std::endl;
                return;
            }
        }
        total_weight += weight_coefficient;
        if (show) std::cout << "\nThe edge added!" << std::endl;
        number_of_edge++;
    }
    void write_graph()
    {
        std::cout << "\nGraph:" << std::endl;
        for (std::size_t i = 0; i < number_of_vertex; i++)
        {            
            std::cout << "Vertex: [" << list[i]->vertex << "]-> { ";
            for (Graph_node* current = list[i]->next; current; current = current->next)
            {
                std::cout << current->vertex << "-> ";
            }
            std::cout << "# }" << std::endl;
        }
        std::cout << "\nVertices: " << number_of_vertex << std::endl;
        std::cout << "Edges: " << number_of_edge << std::endl;
        std::cout << "Total weight: " << total_weight << std::endl;
    }
    void checking_the_connectivity_of_graph()
    {
        if (connected_graph())
        {
            std::cout << "\nThe graph is connected!" << std::endl;
        }
    }

};
int main()
{
    Graph_list graph(5, true);
    graph.add_edge(0, 1, 2);
    graph.add_edge(0, 2, 2);
    graph.add_edge(2, 4, 3);
    graph.add_edge(4, 3, 3);
    graph.add_edge(0, 3, 1);
    graph.write_graph();
    graph.checking_the_connectivity_of_graph();
    return 0;
}