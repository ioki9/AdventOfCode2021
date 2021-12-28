
#include <iostream>
#include <fstream>
#include <vector>
#include <istream>
#include <string>
#include <cstdint>
#include <chrono>

int getAbsSum(int refPoint, std::vector<int>& values)
{
	int sum{ 0 };
	int n{ 0 };
	for (const auto& it : values)
	{
		n = std::abs(refPoint - it);
		sum += ((n * (n + 1)) / 2);
	}
	return sum;
}

void solveDAY7()
{
	std::string line{};
	std::ifstream myTxt;
	std::vector<int> values;
	int max_val{};
	int min_val{};
	myTxt.open("input.txt");
	if (myTxt.is_open())
	{
		//getting fishes
		myTxt.clear();
		myTxt.seekg(std::ios::beg);
		while (std::getline(myTxt, line))
		{
			std::string temp{};
			for (size_t j{ 0 }; j < line.size(); ++j)
			{

				if (line[j] == ',')
				{
					values.push_back(atoi(temp.c_str()));
					temp = "";
					continue;
				}
				temp += line[j];
			}
			values.push_back(atoi(temp.c_str()));
			for (const auto& it : values)
			{
				if (max_val < it)
					max_val = it;
				if (min_val > it)
					min_val = it;
			}
		}
		int sum1{};
		int minSum{ INT_MAX };
		for (int j{ 0 }; j < max_val; ++j)
		{
			sum1 = getAbsSum(j, values);
			if (sum1 < minSum)
				minSum = sum1;
		}
		std::cout << minSum << '\n';

	}
}


