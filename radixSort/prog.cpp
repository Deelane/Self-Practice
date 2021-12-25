#include <iostream>
#include <vector>
#include <time.h>

int main()
{
    int length;

    //Length
    std::cout << "Enter length of array: ";
    std::cin >> length;
    while (length < 0)
    {
        std::cout << "Length must be positive.\n";
        std::cout << "Enter length of array: ";
        std::cin >> length;
    }

    int* arr = new int[length];

    /*
    //User input
    std::cout << "Enter array values:\n";
    for (int i = 0; i < length; i++)
    {
        std::cin >> arr[i];
    }*/

    //Random Input
    srand(time(0));
    for (int i = 0; i < length; i++)
    {
        //random 1-10000
        int randomNum = rand() % 10000 + 1;
        arr[i] = randomNum;
    }

    std::cout << std::endl;

    //find max
    int max = arr[0];
    for (int i = 1; i < length; i++)
    {
        if (max < arr[i])
        {
            max = arr[i];
        }
    }

    int maxDigits = 0;
    while (max > 0)
    {
        max /= 10;
        maxDigits++;
    }

    //Intermediate sorting array of vectors
    std::vector<int> buckets[10];

    //Radix sort
    //Iterate over array once for each number of digits in the largest number
    for (int i = 0; i < maxDigits; i++)
    {
        //iterate over array
        for (int j = 0; j < length; j++)
        {

            //A copy of the current value
            //Math will be performed to find the current digit we are working on
            int current = arr[j];
            //divide current by 10 i number of times to get the digit we want
            //e.g. if i = 0, 23 / 10 0 times gives us 23, i = 1 gives us 2, etc.
            for (int x = 0; x < i; x++)
            {
                current /= 10;
            }
            //mod the current value with 10 to get the index that the number goes to
            //e.g. if i = 1 and arr[j] is 23, current will be 23/10 = 2, 2 % 10 will give us 2 for the index
            buckets[current % 10].push_back(arr[j]);
            std::cout << "buckets[" << current % 10 << "]: ";
            for (int h = 0, size = buckets[current % 10].size(); h < size; h++)
            {
                std::cout << buckets[current % 10][h] << " ";
            }
            std::cout << std::endl;
        }
        //Rearrange values in original array according to bucket values
        int index = 0;
        for (int x = 0; x < 10; x++)
        {
            //drain bucket of values 
            while (!buckets[x].empty())
            {
                //grab and erase front value
                arr[index] = buckets[x].front();
                buckets[x].erase(buckets[x].begin());
                index++;
            }
        }
        std::cout << std::endl;
        //print the array in its current state
        for (int n = 0; n < length; n++)
        {
            std::cout << arr[n] << " ";
        }
        std::cout << std::endl;
        std::cout << std::endl;
    }
}
