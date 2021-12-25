#include <iostream>
#include <vector>
#include <time.h>
#include <limits.h>

int main()
{
    int vertices;
    int edges;
    int startingVertex;

    //Vertices
    std::cout << "Enter number of vertices: ";
    std::cin >> vertices;
    while (vertices < 0)
    {
        std::cout << "Number of vertices must be positive.\n";
        std::cout << "Enter number of vertices: ";
        std::cin >> vertices;
    }
    std::cout << std::endl;

    //Edges
    std::cout << "Enter number of edges: ";
    std::cin >> edges;
    while (edges < 0)
    {
        std::cout << "Number of edges must be positive.\n";
        std::cout << "Enter number of edges: ";
        std::cin >> edges;
    }
    std::cout << std::endl;

    //Adjacency Matrix
    int** matrix = new int*[vertices];
    for (int i = 0; i < vertices; i++)
    {
        matrix[i] = new int[vertices];
    }
    //Initialize values
    for (int i = 0; i < vertices; i++)
    {
        for (int j = 0; j < vertices; j++)
        {
            if (i == j)
            {
                matrix[i][j] = 0;
            }
            else
            {
                matrix[i][j] = -1;
            }
        }
    }

    for (int i = 0; i < edges; i++)
    {
        //Vertex A
        int vertexA;
        std::cin >> vertexA;
        while (vertexA < 0 || vertexA > vertices)
        {
            std::cout << "Vertex must be non-negative and exist within V\n";
            std::cin >> vertexA;
        }

        //Vertex B
        int vertexB;
        std::cin >> vertexB;
        while (vertexB < 0 || vertexB > vertices)
        {
            std::cout << "Vertex must be non-negative and exist within V\n";
            std::cin >> vertexB;
        }

        //Edge
        int edge;
        std::cin >> edge;
        while (edge < 0)
        {
            std::cout << "Edge cost cannot be negative\n";
            std::cin >> edge;
        }

        //Add edge between vertices (undirected)
        matrix[vertexA-1][vertexB-1] = matrix[vertexB - 1][vertexA - 1] = edge;

    }

    //Starting vertex
    std::cout << "Enter starting vertex: ";
    std::cin >> startingVertex;
    while (startingVertex < 0 || startingVertex > vertices)
    {
        std::cout << "Vertex must be non-negative and exist within V\n";
        std::cout << "Enter starting vertex: ";
        std::cin >> startingVertex;
    }
    std::cout << std::endl;
    //adjust for 0 index start
    startingVertex -= 1;
    
    std::cout << std::endl;
    //Print matrix
    std::cout << "   ";
    for (int i = 0; i < vertices; i++)
    {
        std::cout << "[" << i+1 << "]";
    }
    std::cout << std::endl;
    for (int i = 0; i < vertices; i++)
    {
        std::cout << "[" << i+1 << "] ";
        for (int j = 0; j < vertices; j++)
        {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }

    //Prim's algorithm
    //Start at starting vertex
    //Mark the current vertex in the mark array
    //Iterate over all nodes connected to starting vertex and pick the lowest edge cost
    //Add current vertex to output graph
    //Add the current vertex, connected vertex, and edge cost to output
    //Repeat prim's from the start with the current vertex 
    //Output is the minimum spanning tree of the graph
    
    //track unvisited vertices
    bool* markArray = new bool[vertices];
    for (int i = 0; i < vertices; i++)
    {
        markArray[i] = false;
    }
    markArray[startingVertex] = true;

    //Graph of our current added vertices
    std::vector<int> currentGraph = { startingVertex };

    //output string
    std::string output = "";

    while (currentGraph.size() != vertices)
    {
        //smallest edge cost
        int min = INT_MAX;
        //index of starting edge
        int vertexA = -1;
        //index of smallest edge cost
        int vertexB = -1;

        //iterate over the vertices in our current graph
        for (int i = 0, size = currentGraph.size(); i < size; i++)
        {
            //store current vertex we are working on for code simplicity's sake
            int currentVertex = currentGraph[i];

            //iterate over all 4 vertices and check for the smallest connection
            for (int j = 0; j < vertices; j++)
            {
                //there is a connection and it is smaller than the current smallest connection
                //the connected vertex has also not been visited
                if (!markArray[j] && matrix[currentVertex][j] > 0 && matrix[currentVertex][j] < min)
                {
                    //update smallest edge cost
                    min = matrix[currentVertex][j];
                    //update index of starting edge
                    vertexA = currentVertex;
                    //update index of smallest edge cost
                    vertexB = j;

                }

                std::cout << "Current vertex: " << currentVertex << std::endl;
                std::cout << "Current j: " << j << std::endl;
                std::cout << "Current min: " << min << std::endl;
                std::cout << "Current vertexA: " << vertexA << std::endl;
                std::cout << "Current vertexB: " << vertexB << std::endl;
                std::cout << "Current graph: ";
                for (int x = 0, size = currentGraph.size(); x < size; x++)
                {
                    std::cout << currentGraph[x] << " ";
                }
                std::cout << std::endl;
                std::cout << std::endl;
            }
        }

        //Update mark array
        markArray[vertexB] = true;
        //update currentGraph
        currentGraph.push_back(vertexB);
        //update output
        output += std::to_string(vertexA+1) + " " + std::to_string(vertexB+1) + " " + std::to_string(min) + "\n";
    }
    std::cout << output << std::endl;
    std::cout << "Min Spanning Tree: ";
    for (int i = 0; i < vertices; i++)
    {
        if (i != vertices - 1)
        {
            std::cout << currentGraph[i]+1 << "-> ";
        }
        else
        {
            std::cout << currentGraph[i]+1 << std::endl;
        }
    }
    std::cout << std::endl;
}
