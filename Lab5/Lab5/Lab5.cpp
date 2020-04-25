//
#include <iostream>
#include <vector>

struct Graph_node
{
    bool contiguity;
    int weight_coefficient;
    bool was_verified;
    Graph_node()
    {
        contiguity = false;
        weight_coefficient = 0;
        was_verified = false;
    }
    Graph_node(bool contiguity, int weight_coefficient)
    {
        this->contiguity = contiguity;
        this->weight_coefficient = weight_coefficient;
        was_verified = false;
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
    void checking_the_connectivity_of_graph_current(std::vector<std::size_t>& indexes, std::size_t index)
    {
        for (std::size_t j = 0; j < number_of_vertex; j++)
        {
            if (array[index][j].contiguity)
            {
                add_index(indexes, index);
                if (index == j) continue;
                if (!array[index][j].was_verified)
                {
                    array[index][j].was_verified = true;
                    checking_the_connectivity_of_graph_current(indexes, j);
                }
            }
        }
    }
    void verified_false()
    {
        for (std::size_t i = 0; i < number_of_vertex; i++)
        {
            for (std::size_t j = 0; i < number_of_vertex; i++)
            {
                array[i][j].was_verified = false;
            }
        }
    }
    bool is_connected(std::vector<std::size_t>& indexes)
    {
        array[0][0].was_verified = true;
        checking_the_connectivity_of_graph_current(indexes, 0);
        verified_false();
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
    }    
    void checking_the_connectivity_of_graph()
    {
        std::vector<std::size_t> indexes;
        if (is_connected(indexes))
        {
            std::cout << "\nThe graph is connected!" << std::endl;
        }
        else
        {
            std::cout << "\nThe graph isn't connected!" << std::endl;
        }
    }
    void depth_first_search()
    {
        std::vector<std::size_t> indexes;
        if (is_connected(indexes))
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
    graph.add_edge(0, 1, 10);
    graph.add_edge(0, 5, 10);
    graph.add_edge(3, 4, 10);
    graph.add_edge(3, 2, 10);
    graph.add_edge(5, 3, 10);
    graph.write_graph();
    graph.depth_first_search();

    return 0;
}