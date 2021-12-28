
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <bitset>
#include <string_view>
#include <algorithm>
#include <cmath>
struct points
{
	int x1{ 0 }, y1{ 0 };
	int x2{ 0 }, y2{ 0 };
};
void solveDAY5()
{
	std::string line{};
	std::ifstream myTxt;

	std::vector<points> pointsVec{};
	int max_x{ 0 };
	int max_y{ 0 };
	myTxt.open("input.txt");
	if (myTxt.is_open())
	{
		//getting the points
		myTxt.clear();
		myTxt.seekg(std::ios::beg);
		while (std::getline(myTxt, line))
		{
			points pointsTemp{};
			std::string temp{};
			for (size_t j{ 0 }; j < line.size(); ++j)
			{
				if (line[j] <= '9' && line[j] >= '0')
				{
					temp += line[j];
				}
				if (line[j] == ',' && !pointsTemp.x1)
				{
					pointsTemp.x1 = atoi(temp.c_str());
					temp = "";
					continue;
				}
				else if (line[j] == ',' && pointsTemp.x1)
				{
					pointsTemp.x2 = atoi(temp.c_str());
					temp = "";
					continue;
				}
				else if (line[j] == ' ' && !pointsTemp.y1)
				{
					pointsTemp.y1 = atoi(temp.c_str());
					temp = "";
					continue;
				}
				if (j + 1 == line.size())
				{
					pointsTemp.y2 = atoi(temp.c_str());
					temp = "";
				}
			}
			pointsVec.push_back(pointsTemp);
			//std::cout << pointsTemp.x1 << ',' << pointsTemp.y1 << " -> " << pointsTemp.x2 << ',' << pointsTemp.y2<<'\n';
		}
		for (const auto& it : pointsVec)
		{
			if (it.x2 > max_x)
				max_x = it.x2;
			else if (it.x1 > max_x)
				max_x = it.x1;
			if (it.y2 > max_y)
				max_y = it.y2;
			if (it.y1 > max_y)
				max_y = it.y1;
		}
		std::vector<std::vector<int>> map(max_x + 1, std::vector<int>(max_y + 1));
		for (const auto& it : pointsVec)
		{
			if (it.x1 == it.x2)
			{
				int temp_x{ it.x2 }, temp_y{ it.y2 };
				if (temp_x < it.x1)
					temp_x = it.x1;
				if (temp_y < it.y1)
					temp_y = it.y1;
				int interval = std::abs(it.y2 - it.y1);
				for (int k{ 0 }; k < interval + 1; ++k)
				{
					map[temp_x][temp_y - k] += 1;
				}
			}
			else if (it.y1 == it.y2)
			{
				int interval = std::abs(it.x2 - it.x1);
				int temp_x{ it.x2 }, temp_y{ it.y2 };
				if (temp_x < it.x1)
					temp_x = it.x1;
				if (temp_y < it.y1)
					temp_y = it.y1;
				for (int k{ 0 }; k < interval + 1; ++k)
				{
					map[temp_x - k][temp_y] += 1;
				}
			}
			else if ((std::abs(it.y2 - it.y1) / std::abs(it.x2 - it.x1)) == 1)
			{
				int interval = std::abs(it.x2 - it.x1);

				for (int k{ 0 }; k < interval + 1; ++k)
				{
					map[it.x1 - ((it.x1 > it.x2) ? k : (-k))][it.y1 - ((it.y1 > it.y2) ? k : (-k))] += 1;
				}
			}
		}
		int count{ 0 };
		for (size_t l{ 0 }; l < max_x + 1; ++l)
		{
			for (size_t n{ 0 }; n < max_y + 1; ++n)
			{
				if (map[l][n] > 1)
					count++;
			}
		}
		std::cout << count;
	}
	myTxt.close();
}

