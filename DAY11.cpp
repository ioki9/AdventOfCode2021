#include "DAY11.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <istream>
#include <string>
#include <cstdint>
#include <chrono>
#include <algorithm>
#include <array>
#include <deque>


void solveDAY11()
{
	std::string line{};
	std::ifstream myTxt;
	std::array<std::array<int, 10>, 10> octoMatrix{};
	std::deque <std::pair<size_t, size_t>> bombDeque{};
	long long flashes{ 0 };
	myTxt.open("input.txt");
	if (myTxt.is_open())
	{
		myTxt.clear();
		myTxt.seekg(std::ios::beg);
		size_t row{ 0 };
		while (std::getline(myTxt, line))
		{
			for (size_t col{ 0 }; col < line.size(); col++)
			{
				char ch = line[col];
				octoMatrix[row][col] = atoi(&ch);
			}
			row++;
		}
	}
	int step{ 0 };
	bool allFlash{ false };
	//for part 2, change to steps for part 1
	while(!allFlash)
	{
		//adding +1 to every element of matrix
		step++;
		for (size_t row{ 0 }; row < 10; row++)
		{
			for (size_t col{ 0 }; col < 10; col++)
			{
				if(octoMatrix[row][col] == -1)
					octoMatrix[row][col] += 2;
				else
					octoMatrix[row][col] += 1;
			}
		}
		//calculating explosions
		for (size_t row{ 0 }; row < 10; row++)
		{
			for (size_t col{ 0 }; col < 10; col++)
			{
				if (octoMatrix[row][col] > 9)
				{
					octoMatrix[row][col] = -1;
					flashes++;
					if ((row + 1) != 10)
						if (octoMatrix[row + 1][col] != -1)
							bombDeque.push_back({ row + 1,col });
					if ((col + 1) != 10)
						if (octoMatrix[row][col + 1] != -1)
							bombDeque.push_back({ row,col + 1 });
					if ((col + 1) != 10 && (row + 1) != 10)
						if (octoMatrix[row + 1][col + 1] != -1)
							bombDeque.push_back({ row + 1,col + 1 });
					if ((col - 1) != -1 && (row - 1) != -1)
						if (octoMatrix[row - 1][col - 1] != -1)
							bombDeque.push_back({ row - 1,col - 1 });
					if ((col - 1) != -1)
						if (octoMatrix[row][col - 1] != -1)
							bombDeque.push_back({ row,col - 1 });
					if ((row - 1) != -1)
						if (octoMatrix[row - 1][col] != -1)
							bombDeque.push_back({ row - 1,col });
					if ((row - 1) != -1 && (col + 1) != 10)
						if (octoMatrix[row - 1][col + 1] != -1)
							bombDeque.push_back({ row - 1,col + 1 });
					if ((row + 1) != 10 && (col - 1) != -1)
						if (octoMatrix[row + 1][col - 1] != -1)
							bombDeque.push_back({ row + 1,col - 1 });

					std::pair<size_t, size_t> processed{};
					while (!bombDeque.empty())
					{
						processed = bombDeque.back();
						bombDeque.pop_back();
						if (octoMatrix[processed.first][processed.second] == -1)
							continue;

						octoMatrix[processed.first][processed.second] += 1;
						if (octoMatrix[processed.first][processed.second] > 9)
						{
							flashes++;
							octoMatrix[processed.first][processed.second] = -1;
							if ((processed.first + 1) != 10)
								if (octoMatrix[processed.first + 1][processed.second] != -1)
									bombDeque.push_back({ processed.first + 1,processed.second });
							if ((processed.second + 1) != 10)
								if (octoMatrix[processed.first][processed.second + 1] != -1)
									bombDeque.push_back({ processed.first,processed.second + 1 });
							if ((processed.second + 1) != 10 && (processed.first + 1) != 10)
								if (octoMatrix[processed.first + 1][processed.second + 1] != -1)
									bombDeque.push_back({ processed.first + 1,processed.second + 1 });
							if ((processed.second - 1) != -1 && (processed.first - 1) != -1)
								if (octoMatrix[processed.first - 1][processed.second - 1] != -1)
									bombDeque.push_back({ processed.first - 1,processed.second - 1 });
							if ((processed.second - 1) != -1)
								if (octoMatrix[processed.first][processed.second - 1] != -1)
									bombDeque.push_back({ processed.first,processed.second - 1 });
							if ((processed.first - 1) != -1)
								if (octoMatrix[processed.first - 1][processed.second] != -1)
									bombDeque.push_back({ processed.first - 1,processed.second });
							if ((processed.first - 1) != -1 && (processed.second + 1) != 10)
								if (octoMatrix[processed.first - 1][processed.second + 1] != -1)
									bombDeque.push_back({ processed.first - 1,processed.second + 1 });
							if ((processed.first + 1) != 10 && (processed.second - 1) != -1)
								if (octoMatrix[processed.first + 1][processed.second - 1] != -1)
									bombDeque.push_back({ processed.first + 1,processed.second - 1 });
						}
					}
				}
			}
		}
		//checking for all flash
		int count{ 0 };
		for (size_t row{ 0 }; row < 10; row++)
		{
			for (size_t col{ 0 }; col < 10; col++)
			{
				if (octoMatrix[row][col] != 0 && octoMatrix[row][col] != -1)
					goto next;
			}
		}
		allFlash = true;
	next:
		continue;
	}
	std::cout << step;

	myTxt.close();
}
