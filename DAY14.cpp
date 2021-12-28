#include "DAY14.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <istream>
#include <string>
#include <cstdint>
#include <utility>
#include <algorithm>
#include <chrono>
#include <map>

void solveDAY14()
{
	std::string polymer{ "" };
	std::map<std::string, char>  map_val{};
	std::map<std::string, size_t> map_insert{};
	std::map<char, size_t> char_count{};
	std::string line{};
	std::ifstream myTxt;
	myTxt.open("input.txt");
	if (myTxt.is_open())
	{
		std::getline(myTxt, polymer);
		std::getline(myTxt, line);
		while (std::getline(myTxt, line))
		{
			map_val[line.substr(0, 2)] = line[6];
		}
	}
	//get initial values to calculate
	for (size_t ch{ 1 }; ch < polymer.size(); ch++)
	{
		char_count[polymer[ch-1]] += 1;
		if (map_val.find(polymer.substr(ch - 1, 2)) != map_val.end())
		{
			map_insert[polymer.substr(ch - 1, 2)] += 1;
		}
	}
	char_count[polymer.back()] += 1;

	//calc values
	for (size_t step{ 0 }; step < 40; ++step)
	{
		std::map temp(map_insert);
		for (const auto& val : map_val)
		{
			if (map_insert.find(val.first) != map_insert.end())
			{
				temp[std::string() + val.first[0] + val.second] += map_insert[val.first];
				temp[std::string() + val.second + val.first[1]] += map_insert[val.first];
				char_count[val.second] += map_insert[val.first];
				temp[val.first] -= map_insert[val.first];
			}
		}
		map_insert = temp;
	}


	size_t max{ 0 };
	size_t min{ SIZE_MAX };
	for (const auto& it : char_count)
	{
		if (it.second > max)
			max = it.second;
		else if (it.second < min)
			min = it.second;
	}

	std::cout << max - min;
	myTxt.close();
}

