

#include <iostream>
#include <fstream>
#include <vector>
#include <istream>
#include <string>
#include <cstdint>
#include <chrono>
#include <algorithm>
#include <array>
#include <queue>


int GetLowPoint(const std::vector<std::string>& matrix, size_t row, size_t col)
{
	if (row > 0 && row < (matrix.size() - 1) && col > 0 && col < (matrix[row].size() - 1))
	{
		if (matrix[row][col] == '9')
			return 0;
		if (matrix[row][col] > matrix[row + 1][col])
			return 0;
		if (matrix[row][col] > matrix[row - 1][col])
			return 0;
		if (matrix[row][col] > matrix[row][col + 1])
			return 0;
		if (matrix[row][col] > matrix[row][col - 1])
			return 0;
		char ret = matrix[row][col];
		return (atoi(&ret) + 1);
	}
	if (row == 0 && col > 0 && col < (matrix[row].size() - 1))
	{
		if (matrix[row][col] == '9')
			return 0;
		if (matrix[row][col] > matrix[row + 1][col])
			return 0;
		if (matrix[row][col] > matrix[row][col + 1])
			return 0;
		if (matrix[row][col] > matrix[row][col - 1])
			return 0;
		char ret = matrix[row][col];
		return (atoi(&ret) + 1);
	}
	if (row == (matrix.size() - 1) && col > 0 && col < (matrix[row].size() - 1))
	{
		if (matrix[row][col] == '9')
			return 0;
		if (matrix[row][col] > matrix[row - 1][col])
			return 0;
		if (matrix[row][col] > matrix[row][col + 1])
			return 0;
		if (matrix[row][col] > matrix[row][col - 1])
			return 0;
		char ret = matrix[row][col];
		return (atoi(&ret) + 1);
	}
	if (row > 0 && row < (matrix.size() - 1) && col == 0)
	{
		if (matrix[row][col] == '9')
			return 0;
		if (matrix[row][col] > matrix[row + 1][col])
			return 0;
		if (matrix[row][col] > matrix[row - 1][col])
			return 0;
		if (matrix[row][col] > matrix[row][col + 1])
			return 0;
		char ret = matrix[row][col];
		return (atoi(&ret) + 1);
	}
	if (row > 0 && row < (matrix.size() - 1) && col == (matrix[row].size() - 1))
	{
		if (matrix[row][col] == '9')
			return 0;
		if (matrix[row][col] > matrix[row + 1][col])
			return 0;
		if (matrix[row][col] > matrix[row - 1][col])
			return 0;
		if (matrix[row][col] > matrix[row][col - 1])
			return 0;
		char ret = matrix[row][col];
		return (atoi(&ret) + 1);
	}
	if (row == 0 && col == 0)
	{
		if (matrix[row][col] == '9')
			return 0;
		if (matrix[row][col] > matrix[row + 1][col])
			return 0;
		if (matrix[row][col] > matrix[row][col + 1])
			return 0;
		char ret = matrix[row][col];
		return (atoi(&ret) + 1);
	}
	if (row == 0 && col == (matrix[row].size() - 1))
	{
		if (matrix[row][col] == '9')
			return 0;
		if (matrix[row][col] > matrix[row + 1][col])
			return 0;
		if (matrix[row][col] > matrix[row][col - 1])
			return 0;
		char ret = matrix[row][col];
		return (atoi(&ret) + 1);
	}
	if (row == (matrix.size() - 1) && col == (matrix[row].size() - 1))
	{
		if (matrix[row][col] == '9')
			return 0;
		if (matrix[row][col] > matrix[row - 1][col])
			return 0;
		if (matrix[row][col] > matrix[row][col - 1])
			return 0;
		char ret = matrix[row][col];
		return (atoi(&ret) + 1);
	}
	if (row == (matrix.size() - 1) && col == 0)
	{
		if (matrix[row][col] == '9')
			return 0;
		if (matrix[row][col] > matrix[row - 1][col])
			return 0;
		if (matrix[row][col] > matrix[row][col + 1])
			return 0;
		char ret = matrix[row][col];
		return (atoi(&ret) + 1);
	}
	return 0;
}
std::array<int, 3> GetTopBasins(const std::vector<std::string>& origMatrix)
{
	std::vector<std::string> matrix{ origMatrix };
	std::array<int, 3> topBasins{ 0,0,0 };
	int basinCount{ 0 };
	std::queue<std::pair<size_t, size_t>> queue{};
	for (size_t row{ 0 }; row < matrix.size(); ++row)
	{
		for (size_t col{ 0 }; col < matrix[0].size(); ++col)
		{
			if (matrix[row][col] != '9' && matrix[row][col] != 'c')
			{
				basinCount++;
				matrix[row][col] = 'c';
				if ((row + 1) != matrix.size())
					if (matrix[row + 1][col] != '9')
					{
						queue.push(std::pair<size_t, size_t>(row + 1, col));
					}
				if (matrix[row][col + 1] != '9')
				{
					if ((col + 1) != matrix[0].size())
						queue.push(std::pair<size_t, size_t>(row, col + 1));
				}
				std::pair<size_t, size_t> queueFront;
				while (!queue.empty())
				{
					queueFront = queue.front();
					if (matrix[queueFront.first][queueFront.second] == 'c')
					{
						queue.pop();
						continue;
					}
					basinCount++;
					matrix[queueFront.first][queueFront.second] = 'c';
					queue.pop();
					if (queueFront.first != (matrix.size() - 1))
						if (matrix[queueFront.first + 1][queueFront.second] != '9' && matrix[queueFront.first + 1][queueFront.second] != 'c')
							queue.push(std::pair<size_t, size_t>(queueFront.first + 1, queueFront.second));
					if (queueFront.second != (matrix[0].size() - 1))
						if (matrix[queueFront.first][queueFront.second + 1] != '9' && matrix[queueFront.first][queueFront.second + 1] != 'c')
							queue.push(std::pair<size_t, size_t>(queueFront.first, queueFront.second + 1));
					if (queueFront.second != 0)
						if (matrix[queueFront.first][queueFront.second - 1] != '9' && matrix[queueFront.first][queueFront.second - 1] != 'c')
							queue.push(std::pair<size_t, size_t>(queueFront.first, queueFront.second - 1));
					if (queueFront.first != 0)
						if (matrix[queueFront.first - 1][queueFront.second] != '9' && matrix[queueFront.first - 1][queueFront.second] != 'c')
							queue.push(std::pair<size_t, size_t>(queueFront.first - 1, queueFront.second));
				}
				if (topBasins[0] < basinCount)
				{
					topBasins[0] = basinCount;
					std::sort(topBasins.begin(), topBasins.end(), [](int a, int b) {return a < b; });
				}
				basinCount = 0;
			}
		}
	}
	return topBasins;
}
void solveDAY9()
{

	std::string line{};
	std::ifstream myTxt;
	std::vector<std::string> matrix{};
	myTxt.open("D:\\VC_projects\\AdventOfCode\\input.txt");
	auto start = std::chrono::high_resolution_clock::now();
	if (myTxt.is_open())
	{

		myTxt.clear();
		myTxt.seekg(std::ios::beg);
		while (std::getline(myTxt, line))
		{
			matrix.push_back(line);
		}
	}
	int sum{ 0 };
	for (size_t j{ 0 }; j < matrix.size(); ++j)
	{
		for (size_t k{ 0 }; k < matrix[0].size(); ++k)
		{
			sum += GetLowPoint(matrix, j, k);
		}
	}
	//for (size_t j{ 0 }; j < matrix.size(); ++j)
	//{
	//	if(j!= 0)
	//	std::cout << '\n';
	//	for (size_t k{ 0 }; k < matrix[0].size(); ++k)
	//	{
	//		if (matrix[j][k] == '9')
	//			std::cout << ' ';
	//		else
	//			std::cout << 'b';
	//	}
	//}
	std::array<int, 3> basins{ GetTopBasins(matrix) };
	std::cout << "\n\n" << basins[0] << "*" << basins[1] << "*" << basins[2] << "=" << basins[0] * basins[1] * basins[2];

	//std::cout << "result:" << sum << '\n';
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = end - start;
	std::cout << "\n\n elapsed time:" << elapsed.count() << "s.";
	myTxt.close();
}


