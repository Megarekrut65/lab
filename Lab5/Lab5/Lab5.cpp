//
#include <iostream>
#include <vector>

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
        std::vector<std::size_t> indexes;
        if (is_connected(indexes, false))
        {
            std::cout << "\nThe graph is connected!" << std::endl;
        }
        else
        {
            std::cout << "\nThe graph isn't connected!" << std::endl;
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
};
int main()
{
    Graph_matrix graph(6, false);
    graph.add_edge(0, 1, 0);
    graph.add_edge(0, 2, 7);
    graph.add_edge(0, 3, 6);
    graph.add_edge(2, 5, 40);
    graph.add_edge(3, 4, -7);
    graph.add_edge(3, 5, 14);
    graph.write_graph();
    graph.depth_first_search(false);
    graph.add_vertex();
    graph.depth_first_search(true);

    return 0;
}