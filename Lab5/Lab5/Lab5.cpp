// №1, №2, №5, №11, №14, №17, №19, 
#include <iostream>
#include <vector>

struct Path
{
    int weight_coefficient;
    bool is_end;
    std::size_t begin_vertex;
    std::size_t end_vertex;
    Path()
    {
        weight_coefficient = 0;
        is_end = false;
        begin_vertex = 0;
        end_vertex = 0;
    }
    Path(std::size_t begin_vertex, std::size_t end_vertex)
    {
        weight_coefficient = 0;
        is_end = false;
        this->begin_vertex = begin_vertex;
        this->end_vertex = end_vertex;
    }
    void add_weight(std::size_t next_vertex, int weight_coefficient)
    {
        if (is_end) return;
        this->weight_coefficient += weight_coefficient;
        if (next_vertex == end_vertex)
        {
            is_end = true;
        }
    }
    void select_min(Path path)
    {
        if (!path.is_end) return;
        if(!is_end) weight_coefficient = path.weight_coefficient;
        if (weight_coefficient > path.weight_coefficient)
        {
            weight_coefficient = path.weight_coefficient;
        }
    }
};
struct Graph_node
{
    bool contiguity;
    int weight_coefficient;

    Graph_node()
    {
        contiguity = false;
        weight_coefficient = 0;
    }
    Graph_node(bool contiguity, int weight_coefficient)
    {
        this->contiguity = contiguity;
        this->weight_coefficient = weight_coefficient;
    }
};
struct Graph_matrix
{
private:
    std::vector<std::vector<Graph_node>> array;
    std::size_t number_of_vertex;
    std::size_t number_of_edge;
    bool orientation;
    bool is_index(std::size_t index)
    {
        if (index >= number_of_vertex)
        {
            std::cout << "\nVertex with index: " << index << " isn't in Graph!" << std::endl;
            return false;
        }
        return true;
    }
    void add_index(std::vector<std::size_t>& indexes, std::size_t index)
    {
        for (std::size_t i = 0; i < indexes.size(); i++)
        {
            if (indexes[i] == index) return;
        }
        indexes.push_back(index);
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
        std::vector<Graph_node> line = array[index];
        for (std::size_t i = 0; i < number_of_vertex; i++) numbers.push_back(i);
        if(!mode) return numbers;
        for (std::size_t i = 0; i < number_of_vertex - 1; i++)
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
    bool add_vertex(std::vector<std::size_t> indexes, std::size_t index_i, std::size_t index_j)
    {
        for (std::size_t i = 0; i < indexes.size(); i++)
        {
            if (indexes[i] == index_j)
            {
                return false;
            }
        }       
        return true;
    }
    void is_connected_current(std::vector<std::size_t>& indexes, std::size_t index, bool mode)
    {
        std::vector<std::size_t> numbers = create_numbers(index, mode);
        for (std::size_t j = 0; j < number_of_vertex; j++)
        {            
            if (array[index][numbers[j]].contiguity)
            {
                add_index(indexes, index);              
                if (index == numbers[j]) continue;
                if (add_vertex(indexes, index, numbers[j]))
                {
                    add_index(indexes, numbers[j]);
                    is_connected_current(indexes, numbers[j], mode);
                }
            }
        }
    }
    bool is_connected(std::vector<std::size_t>& indexes, bool mode)
    {
        is_connected_current(indexes, 0, mode);
        if (indexes.size() == number_of_vertex)
        {
            return true;
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
                if (!is_set[j] && array[index][j].contiguity
                    && distance[index] != INT_MAX
                    && distance[index] + array[index][j].weight_coefficient < distance[j])
                    distance[j] = distance[index] + array[index][j].weight_coefficient;
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
                if (array[i][j].contiguity) set[j].push_back(i);
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
public:
    Graph_matrix(bool orientation)
    {
        number_of_vertex = 0;
        number_of_edge = 0;
        this->orientation = orientation;
    }
    Graph_matrix(std::size_t number_of_vertex, bool orientation)
    {
        this->number_of_vertex = number_of_vertex;
        number_of_edge = 0;
        this->orientation = orientation;
        std::vector<Graph_node> new_line(number_of_vertex, Graph_node());
        for (std::size_t i = 0; i < number_of_vertex; i++)
        {
            array.push_back(new_line);
        }
    }    
    void add_vertex()
    {
        for (std::size_t i = 0; i < number_of_vertex; i++)
        {
            array[i].push_back(Graph_node());
        }
        number_of_vertex++;
        if (array.size() == 0)
        {
            std::vector<Graph_node> new_line(1, Graph_node());
            array.push_back(new_line);
            return;
        }
        std::vector<Graph_node> new_line(number_of_vertex, Graph_node());
        array.push_back(new_line);
    }
    void add_edge(std::size_t i_vertex, std::size_t j_vertex, int weight_coefficient)
    {
        if (!is_index(i_vertex) || !is_index(j_vertex)) return;
        if (array[i_vertex][j_vertex].contiguity)
        {
            std::cout << "\nThe edge already exists between the vertices!" << std::endl;
            return;
        }
        Graph_node node = Graph_node(true, weight_coefficient);
        array[i_vertex][j_vertex] = node;
        if(!orientation) array[j_vertex][i_vertex] = node;
        number_of_edge++;
        std::cout <<"\nThe edge added!" << std::endl;
    }
    void write_graph()
    {
        std::cout << "\nGraph:\n" << std::endl;
        for (std::size_t i = 0; i < number_of_vertex; i++)
        {
            std::cout << "| ";
            for (std::size_t j = 0; j < number_of_vertex; j++)
            {
                if (array[i][j].contiguity) std::cout << "1 ";
                else std::cout << "0 ";
            }
            std::cout << "|" << std::endl;
        }
        std::cout << "\nVertex: " << number_of_vertex << std::endl;
        std::cout << "Edge: " << number_of_edge << std::endl;
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
                i = 0;
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
};
int main()
{
    Graph_matrix graph(5, false);
    graph.add_edge(0, 0, 10);
    graph.add_edge(0, 1, 1);
    graph.add_edge(1, 1, 12);
    graph.add_edge(1, 2, 1);
    graph.add_edge(2, 2, 13);
    graph.add_edge(2, 3, 1);
    graph.add_edge(3, 3, 11);
    graph.add_edge(3, 4, 1);
    graph.add_edge(4, 4, 17);
    graph.write_graph();
    graph.find_paths_between_all_vertices();

    return 0;
}