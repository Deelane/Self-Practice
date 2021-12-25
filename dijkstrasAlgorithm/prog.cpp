#include <iostream>
#include <vector>
#include <time.h>
#include <limits.h>
#include <utility>
int main()
{
    int vertices;
    int edges;
    int startingVertex;
    
    /*
    //User input
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
    */

    //Random values
    //1-10 vertices
    srand(time(0));
    vertices = (rand() % 10) + 1;
    //2-20 edges
    edges = (rand() % 19) + 2;

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

    /*
    //User input
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
    */

    //Random values
    //Ensure edges dont get overwritten
    bool** markMatrix = new bool*[vertices];
    for (int i = 0; i < vertices; i++)
    {
        markMatrix[i] = new bool[vertices];
    }
    for (int i = 0; i < vertices; i++)
    {
        for (int j = 0; j < vertices; j++)
        {
            markMatrix[i][j] = false;
        }
    }

    for (int i = 0; i < edges; i++)
    {
        //Vertex A
        //random vertex
        int vertexA = rand() % vertices;

        //Vertex B
        int vertexB = rand() % vertices;
        //Ensure vertexB is not vertexA and there is not already an edge between vertexA and vertexB
        while (vertexB == vertexA || markMatrix[vertexA][vertexB])
        {
            vertexB = rand() % vertices;
        }

        //Edge
        //Random cost 1 - 9
        int edge = (rand() % 9) + 1;

        //Add edge between vertices (undirected)
        matrix[vertexA][vertexB] = matrix[vertexB][vertexA] = edge;
        //mark vertices as having an edge
        markMatrix[vertexA][vertexB] = markMatrix[vertexB][vertexA] = true;

    }
    //done with mark matrix
    delete markMatrix;

    //Starting vertex
    startingVertex = rand() % vertices;

    std::cout << "Vertices: " << vertices << std::endl;
    std::cout << "Edges : " << edges << std::endl;
    std::cout << "Starting vertex: " << startingVertex << std::endl;
    std::cout << std::endl;

    //Print matrix
    std::cout << "   ";
    for (int i = 0; i < vertices; i++)
    {
        std::cout << "[" << i << "]";
    }
    std::cout << std::endl;
    for (int i = 0; i < vertices; i++)
    {
        std::cout << "[" << i << "] ";
        for (int j = 0; j < vertices; j++)
        {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }


    //Dijkstra's algorithm//
    //1. Initialize an array of distances from source vertex to all other vertices to infinity
    //2. Initialize a minimum priority queue to hold all vertices adjacent to current graph
    //3. Priority queue will automatically order elements by weight lowest -> highest
    //4. Pop off the first value (source vertex on first iteration) and label it with u, loop until there are no more values in the pq
    //5. Loop over all adjacent vertices to u (every value in the array at matrix[u])
    //6. Update the distance array if the distance from the source to the current vertex + the weight 
    //to get to the current vertex (dist[u] + weight) is less
    //than the current shortest distance from the source to u dist[u].
    //7. Result will be a distance array with the shortest distance from the source to any node v in the graph

    //Matrix of pairs representing the cost to get to that point and the node it came from
    //Actually an array of pointers to arrays of pairs
    std::vector<std::pair<int, int>*> pairMatrix;

    //distance array
    //holds shortest distance from source vertex to every other vertex
    int* distanceArr = new int[vertices];
    //starting vertex to itself is of cost 0
    distanceArr[startingVertex] = 0;

    //Priority queue (min) to store vertices that
    //are being preprocessed. This is weird syntax in C++.
    //Refer below link for details of this syntax
    //https://www.geeksforgeeks.org/implement-min-heap-using-stl/
    priority_queue< std::pair<int, int>, vector <std::pair<int, int>>, greater<std::pair<int, int>> > pq;
    
    //Push starting vertex onto priority queue
    pq.push(make_pair(0, startingVertex))

    int index = 0;
    int parentVertex;
    for (int i = 0; i < vertices; i++)
    {
        //grab startingVertex value from the matrix and associate it with itself as a pair
        std::pair<int, int> pair(matrix[startingVertex][i], startingVertex);
        pairArr[i] = pair;

        //Vertex is unvisited and has an edge connected to the source vertex
        if (!markArray[i] && pair.first > 0)
        {
            //update the minimum edge cost value and the vertex associated with it
            if (currentPair.first < minEdgeCost)
            {
                //the cost to reach the vertex
                minEdgeCost = pair.first;
                //the source vertex
                parentVertex = startingVertex;
                //the destination vertex
                index = i;
            }
        }
    }
    //There is no path from the starting vertex to any node so the graph is not complete
    if (minEdgeCost == INT_MAX)
    {
        std::cout << "Graph is not complete\n";
        return 0;
    }
    pairMatrix.push_back(pairArr);

    //Find the smallest edge cost of an unvisited node in the current pairmatrix
    int currentVertex = startingVertex;
    int minEdgeCost = INT_MAX;
    int index = -1;
    for (int i = 0; i < vertices; i++)
    {
        std::pair<int, int> currentPair = pairMatrix[currentVertex][i];
        //if the vertex we are looking at is unvisited and we have a 
        if (!markArray[currentPair.second] && currentPair.first > 0)
        {
            //update the minimum edge cost value and the vertex associated with it
            if (currentPair.first < minEdgeCost)
            {
                minEdgeCost = pair.second;
                index = pair.first;
            }
        }
    }

    //Print pair matrix
    //(cost, sourceVertex)
    std::cout << "    ";
    for (int i = 0; i < vertices; i++)
    {
        std::cout << "  [" << i << "]  ";
    }
    std::cout << std::endl;
    for (int i = 0, size = pairMatrix.size(); i < size; i++)
    {
        std::cout << "[" << startingVertex << "] ";
        for (int j = 0; j < vertices; j++)
        {
            std::cout << "(" << pairMatrix[i][j].first << ", " << pairMatrix[i][j].second << ") ";
        }
        std::cout << std::endl;
    }
}
//    [0]   [1]   [2]
//[0] (0, 0)(1, 1)(3, 3)
//[1]
