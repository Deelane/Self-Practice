#include <iostream>
#include <unordered_map>
#include <math.h>
#include <limits.h>
#include <vector>
#include <time.h>

int main()
{
    int numReqs;
    int numBlocks;

    //Requirements
    std::cout << "Enter number of requirements: ";
    std::cin >> numReqs;
    while (numReqs < 0)
    {
        std::cout << "Number of requirements must be positive.\n";
        std::cout << "Enter number of requirements: ";
        std::cin >> numReqs;
    }
    //Blocks
    std::cout << "Enter number of blocks: ";
    std::cin >> numBlocks;
    while (numBlocks < 0)
    {
        std::cout << "Number of blocks must be positive.\n";
        std::cout << "Enter number of blocks: ";
        std::cin >> numBlocks;
    }

    std::string* reqs = new std::string[numReqs];
    std::cout << "Enter requirements\n";
    for (int i = 0; i < numReqs; i++)
    {
        std::cout << "Requirement " << i+1 << ": ";
        std::string req = "";
        std::cin >> req;
        reqs[i] = req;
        std::cout << std::endl;
    }

    //Map our numBlocks
    //Array of maps
    std::unordered_map<std::string, bool>* blocks = new std::unordered_map<std::string, bool>[numBlocks];
    
    /*
    //User input values
    for (int i = 0; i < numBlocks; i++)
    {
        std::unordered_map<std::string, bool> block;
        for (int j = 0; j < numReqs; j++)
        {
            std::cout << "Enter 1 for true or 0 for false\n";
            bool input;
            std::cin >> input;
            block.insert({ reqs[j], input });
        }
        blocks[i] = block;
    }*/

    
    //Randomly generated values
    //seed the random generator
    srand(time(0));
    for (int i = 0; i < numBlocks; i++)
    {
        std::unordered_map<std::string, bool> block;
        for (int j = 0; j < numReqs; j++)
        {
            //random 1-10
            int random = (rand() % 10) + 1;
            //if random is 5 or 10 (20% chance)
            //set requirement to true
            if (random % 5 == 0)
            {
                block.insert({ reqs[j], true });
            }
            else
            {
                block.insert({ reqs[j], false });
            }
        }
        blocks[i] = block;
    }

    //Print blocks
    std::cout << std::endl;
    for (int i = 0; i < numBlocks; i++)
    {
        std::cout << "Block: " << i << ":\n";
        for (int j = 0; j < numReqs; j++)
        {
            std::string status = "true";
            if (!blocks[i].at(reqs[j]))
            {
                status = "false";
            }
            std::cout << "\t" << reqs[j] << ": " << status << std::endl;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    //Hold the current min distance and best value index
    int minDistance = INT_MAX;
    int bestValueIndex = -1;

    //Check every block in blocks and every adjacent block
    //Do this until the sum distance from all requirements is calculated
    for (int i = 0; i < numBlocks; i++)
    {
        //to track how many blocks we have checked
        int count = 0;

        std::unordered_map<std::string, bool> block = blocks[i];

        //Hold indexes of missing requirements
        std::vector<std::string> missingReqs;
        for (int j = 0; j < numReqs; j++)
        {
            if (!block.at(reqs[j]))
            {
                missingReqs.push_back(reqs[j]);
            }
        }
        //size of missingrequirements
        int size = missingReqs.size();
        //indexes left and right of current position
        int l = i - 1;
        int r = i + 1;

        //While we still have missing requirements and one side of the array is still in bounds
        while (size > 0 && (l >= 0 || r < numBlocks))
        {
            //left is still in bounds
            if (l >= 0)
            {
                std::unordered_map<std::string, bool> leftBlock = blocks[l];
                for (int j = 0; j < size; j++)
                {
                    //check if the block has one of our missingrequirements
                    if (leftBlock.at(missingReqs[j]))
                    {
                        missingReqs.erase(missingReqs.begin() + j);
                        size--;
                    }
                }
                count++;
                //we have met all of the requirements
                if (size == 0)
                {
                    break;
                }
                //else we continue going left
                l--;
            }
            //right is still in bounds
            if (r < numBlocks)
            {
                std::unordered_map<std::string, bool> rightBlock = blocks[r];
                for (int j = 0; j < size; j++)
                {
                    //check if the block has one of our missingrequirements
                    if (rightBlock.at(missingReqs[j]))
                    {
                        missingReqs.erase(missingReqs.begin() + j);
                        size--;
                    }
                }
                count++;
                //we have met all of the requirements
                if (size == 0)
                {
                    break;
                }
                //else we continue going right
                r++;
            }
        }
        //we found a valid solution
        if (size == 0)
        {
            if (count < minDistance)
            {
                minDistance = count;
                bestValueIndex = i;
            }
        }
    }
    std::cout << "Best value index: " << bestValueIndex << std::endl << "Sum distance from requirements: " << minDistance << std::endl;
}
