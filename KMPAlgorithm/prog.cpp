/*KMP Algorithm Practice
Randomly generates a string and pattern from an array of chars
Finds all occurences of the pattern within the string and prints them out and shows where they occur
*/

#include <iostream>
#include <time.h>

int* lpsArray(std::string pattern);
void patternMatch(std::string pattern, std::string string);

int main()
{
	std::cout << std::endl;
	std::string s;
	std::string pattern;

	//hardcode
	/*
	s = "onionionsplonionionspl";
	pattern = "onions";*/

	//Random string and pattern
	std::string alphabet = "eetaaiioonshrdw";
	srand(time(0));
	//str length 10-50
	int strLength = (rand() % 40) + 10;
	//pattern length 1-5
	int patternLength = (rand() % 5) + 1;
	for (int i = 0; i < strLength; i++)
	{
		//random alphabet char
		int randIndex = (rand() % alphabet.length());
		s += alphabet[randIndex];
	}
	for (int i = 0; i < patternLength; i++)
	{
		int randIndex = (rand() % alphabet.length());
		pattern += alphabet[randIndex];
	}

	std::cout << "==============================Result==============================";
	std::cout << "\nString: " << s << " \n";
	std::cout << "Pattern: " << pattern << " \n";
	patternMatch(pattern, s);
	std::cout << "==================================================================\n\n";
}

//return an array denoting the longest partial suffix at each index i of a given string input
int* lpsArray(std::string pattern)
{
	int length = pattern.length();
	int* lpsArray = new int[length];

	//longest partial suffix at the 0 index is always 0
	lpsArray[0] = 0;
	//index of the start of the last char in the current longest pattern that has been found
	//also the length of the current longest pattern
	int currentPatternLength = 0;
	//start looking for patterns at 1st index
	int i = 1;

	while (i < length)
	{
		//if we find a matching character
		if (pattern[i] == pattern[currentPatternLength])
		{
			//increment the length of the longest matching string at the current position
			lpsArray[i] = currentPatternLength + 1;
			//increment both of our indexes
			currentPatternLength++;
			i++;
		}
		else
		{
			//we had a pattern before and found a mismatch
			if (currentPatternLength != 0)
			{
				//reset currentPatternLength to where it was at the previous iteration to preserve the previously matched chars
				//length will be reset to the previous position and enter the first if statement in the while loop
				currentPatternLength = lpsArray[currentPatternLength - 1];
			}
			//we did not have a pattern yet so keep looking
			else
			{
				lpsArray[i] = 0;
				i++;
			}
		}
	}
	return lpsArray;
}

void patternMatch(std::string pattern, std::string string)
{
	int numMatches = 0;
	int strLength = string.length();
	int patternLength = pattern.length();
	//curent place in string
	int i = 0;
	//current place in pattern
	int j = 0;
	//longest partial suffix array of pattern
	int* lpsArr = lpsArray(pattern);
	//iterate over passed string
	while (i < strLength)
	{
		//matching chars found
		if (string[i] == pattern[j])
		{
			i++;
			j++;
		}
		else
		{
			//revert j to the index of the longest matched partial suffix
			if (j != 0)
			{
				j = lpsArr[j - 1];
			}
			//j was 0 so we keep looking for the first char match in t he pattern
			else
			{
				i++;
			}
		}
		//j reaching the length of the pattern means that the pattern was found
		if (j == patternLength)
		{
			numMatches++;
			int patternStart = i - j;
			std::cout << "\n\nMatch " << numMatches << " found for \"" << pattern << "\" at: \n\n";
			std::cout << "string: ";
			for (int h = 0; h < patternStart; h++)
			{
				std::cout << string[h] << " ";
			}
			for (int h = patternStart; h < i; h++)
			{
				std::cout << "[" << string[h] << "]";
			}
			std::cout << " ";
			for (int h = i; h < strLength; h++)
			{
				std::cout << string[h] << " ";
			}
			std::cout << "\npattern: ";
			for (int h = 0; h < patternStart; h++)
			{
				std::cout << "  ";
			}
			for (int h = 0; h < patternLength; h++)
			{
				std::cout << pattern[h] << "  ";
			}
			//revert j to the index of the longest matched partial suffix to find more matches
			j = lpsArr[j - 1];
		}
	}
	std::cout << "\n\nTotal matches found: " << numMatches << "\n\n";
}

//{o n i o n i o n s p l}
//{o n i o n s}