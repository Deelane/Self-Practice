/*
Attempt at medium google coding interview with ben awad youtube
Removes islands from a matrix using DFS
*/

#include <iostream>
#include <vector>

int count = 0;
void DFS(int i, int j, std::vector<std::vector<int>> &matrix, std::vector<std::vector<int>> &markMatrix);

int main()
{
    int rows;
    int cols;
    std::cin >> rows;
    while (rows < 0)
    {
        std::cout << "Rows must be non-negative\n";
        std::cin >> rows;
    }
    std::cin >> cols;
    while (cols < 0)
    {
        std::cout << "Columns must be non-negative\n";
        std::cin >> cols;
    }
    
    //Matrix of values
    std::vector<std::vector<int>> matrix;
    
    //this will track the points we have already visited
    std::vector<std::vector<int>> markMatrix;

    /*
    //Create matrix and initialize mark matrix values to false
    for (int i = 0; i < rows; i++)
    {
        std::vector<int> row;
        std::vector<int> markRow;
        
        for (int j = 0; j < cols; j++)
        {
            int input;
            std::cin >> input;
            while (input < 0 || input > 1)
            {
                std::cout << "Input must be 0 or 1\n";
                std::cin >> input;
            }
            row.push_back(input);
            markRow.push_back(false);
        }
        matrix.push_back(row);
        markMatrix.push_back(markRow);
    }*/
    
    
    //Random matrix
    
    //pass system time as unsigned int for random seed
    unsigned seed = time(0);
    srand(seed);
    //Create matrix and initialize mark matrix values to false
    for (int i = 0; i < rows; i++)
    {
        std::vector<int> row;
        std::vector<int> markRow;
        
        for (int j = 0; j < cols; j++)
        {
            //random number 1-10
            int random = (std::rand() % 10) + 1;
            //row vector
            //30% chance of being set to 1
            if (random % 3 == 0)
            {
                row.push_back(1);
            }
            else
            {
                row.push_back(0);
            }
            markRow.push_back(false);
        }
        matrix.push_back(row);
        markMatrix.push_back(markRow);
    }
    
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    
    /*for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            std::cout << markMatrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;*/
    
    //DFS
    //Run DFS on each border node, check left right up and down (if in bounds)
    //Result will be a matrix with the islands removed
    
    //Run 4 DFS on the borders
    //Left and right borders
    for (int i = 0; i < rows; i++)
    {
        DFS(i, 0, matrix, markMatrix);
        DFS(i, cols-1, matrix, markMatrix);
    }
    //Top and bottom borders
    for (int i = 0; i < cols; i++)
    {
        DFS(0, i, matrix, markMatrix);
        DFS(rows-1, i, matrix, markMatrix);
    }
    
    //compare mark array and original matrix, if a point was marked then it keeps its value
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            //if the point was not visited then it was an island
            if (markMatrix[i][j] != 1)
            {
                //values that were originally 0 remain 0 even if they were marked "unvisited"
                matrix[i][j] = 0;
            }
        }
    }
    
    //Output
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    std::cout << "DFS ran " << count << " times.\n";
}

//If a node is 0, mark it and do not continue DFS
//If a node is 1, mark it and continue DFS
void DFS(int i, int j, std::vector<std::vector<int>> &matrix, std::vector<std::vector<int>> &markMatrix)
{
    //point has already been visited
    if (markMatrix[i][j] == 1)
    {
        return;
    }
    
    //we have reached a 1 
    if (matrix[i][j] == 1)
    {
        //mark the array
        markMatrix[i][j] = 1;
    }
    //if we reach a 0 then get outta there
    //we don't even need to mark border nodes in the array since all 0s will retain their values in the end no matter what
    else
    {
        return;
    }
    
    //continue DFS
    //ensure i and j stay in matrix bounds
    //go right
    if (j + 1 < matrix[0].size())
    {
        DFS(i, j+1, matrix, markMatrix);
    }
    //go left
    if (j - 1 >= 0)
    {
        DFS(i, j-1, matrix, markMatrix);
    }
    //go up
    if (i - 1 >= 0)
    {
        DFS(i-1, j, matrix, markMatrix);
    }
    //go down
    if (i + 1 < matrix.size())
    {
        DFS(i+1, j, matrix, markMatrix);
    }
    count++;

}
