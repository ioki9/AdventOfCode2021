

#include <iostream>
#include <fstream>
#include <vector>
#include <istream>
#include <string>
#include <cstdint>
#include <chrono>
#include <algorithm>

std::string RemoveSubstr(const std::string& string, const std::string& string_to_remove, bool sort = false)
{
	std::string tempString{ string };
	std::string tempRemove{ string_to_remove };
	size_t strSize{ tempString.size() };
	size_t strRemSize{ tempRemove.size() };
	for (int j{ 0 }; j < strSize; ++j)
	{
		if (tempRemove.empty())
			break;
		for (int l{ 0 }; l < strRemSize; ++l)
		{
			if (tempString[j] == tempRemove[l])
			{
				--strRemSize;
				--strSize;
				tempString.erase(j, size_t(1));
				tempRemove.erase(l, size_t(1));
				--j;
				break;
			}
		}
	}
	if (sort)
		std::sort(tempString.begin(), tempString.end());
	return tempString;
}


void solveDAY8()
{
	auto start = std::chrono::high_resolution_clock::now();
	std::string line{};
	std::ifstream myTxt;
	std::vector<std::string> outputPatterns{};
	std::vector < std::string > patterns{};
	std::vector<std::string> solvedPatterns(10, "");
	long long sum{ 0 };
	myTxt.open("input.txt");
	if (myTxt.is_open())
	{

		myTxt.clear();
		myTxt.seekg(std::ios::beg);
		while (std::getline(myTxt, line))
		{
			std::string temp{};
			patterns.clear();
			outputPatterns.clear();
			//get patterns;
			for (size_t j{ 0 }; j < line.size(); ++j)
			{
				if (line[j] == '|')
				{
					++j;
					++j;
					temp = "";
					for (size_t k{ j }; k < line.size(); ++k)
					{
						if (line[k] == ' ')
						{
							std::sort(temp.begin(), temp.end());
							outputPatterns.push_back(temp);
							temp = "";
							continue;
						}
						temp += line[k];
					}
					std::sort(temp.begin(), temp.end());
					outputPatterns.push_back(temp);
					break;
				}

				if (line[j] == ' ')
				{
					std::sort(temp.begin(), temp.end());
					patterns.push_back(temp);
					temp = "";
					continue;
				}
				temp += line[j];
			}

			std::sort(patterns.begin(), patterns.end(), [](std::string& a, std::string& b) { return a.size() < b.size(); });
			solvedPatterns[1] = patterns[0];
			solvedPatterns[4] = patterns[2];
			solvedPatterns[7] = patterns[1];
			solvedPatterns[8] = patterns.back();
			//solvedPatterns[3]
			for (auto pat = patterns.begin(); pat != patterns.end(); ++pat)
			{
				if (pat->size() == 5)
				{
					std::string check{ RemoveSubstr(*pat, solvedPatterns[1]) };
					if (check.size() == 3)
					{
						solvedPatterns[3] = *pat;
						break;
					}
				}
			}
			//solvedPatterns[9]
			for (auto pat = patterns.begin(); pat != patterns.end(); ++pat)
			{
				if (pat->size() == 6)
				{
					std::string check{ RemoveSubstr(*pat, solvedPatterns[3]) };
					if (check.size() == 1)
					{
						solvedPatterns[9] = *pat;
						break;
					}
				}
			}
			//solvedPatterns[2]
			for (auto pat = patterns.begin(); pat != patterns.end(); ++pat)
			{
				if (pat->size() == 5 && *pat != solvedPatterns[3])
				{
					std::string check{ RemoveSubstr(*pat, solvedPatterns[9]) };
					if (check.size() == 1)
					{
						solvedPatterns[2] = *pat;
						break;
					}
				}
			}
			//solvedPatterns[5]
			for (auto pat = patterns.begin(); pat != patterns.end(); ++pat)
			{
				if (pat->size() == 5 && *pat != solvedPatterns[3] && *pat != solvedPatterns[2])
				{
					solvedPatterns[5] = *pat;
				}
			}
			// solvedPatterns[0]	
			for (auto pat = patterns.begin(); pat != patterns.end(); ++pat)
			{
				if (pat->size() == 6 && *pat != solvedPatterns[9])
				{
					std::string str = RemoveSubstr(*pat, solvedPatterns[7]);
					if (str.size() == 3)
					{
						solvedPatterns[0] = *pat;
						break;
					}
				}
			}
			// solvedPatterns[6]
			for (auto pat = patterns.begin(); pat != patterns.end(); ++pat)
			{
				if (pat->size() == 6 && *pat != solvedPatterns[9] && *pat != solvedPatterns[0])
				{
					solvedPatterns[6] = *pat;
					break;
				}
			}
			std::string numString{ "" };
			for (const auto& it : outputPatterns)
			{
				auto found = std::find(solvedPatterns.begin(), solvedPatterns.end(), it);
				if (found != solvedPatterns.end())
				{
					numString += std::to_string(std::distance(solvedPatterns.begin(), found));
				}
			}
			sum += atoi(numString.c_str());
		}
		std::cout << "\n\nsum:" << sum;
	}
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = end - start;
	std::cout << "\n elapsed time:" << elapsed.count();
	myTxt.close();
}


