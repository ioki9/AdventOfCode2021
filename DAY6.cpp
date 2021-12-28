
#include <iostream>
#include <fstream>
#include <vector>
#include <istream>
#include <string>
#include <cstdint>
#include <chrono>
void solveDAY6()
{

	std::string line{};
	std::ifstream myTxt;
	std::vector<long long> fishVec(9, 0);
	myTxt.open("input.txt");
	if (myTxt.is_open())
	{
		//getting fishes
		myTxt.clear();
		myTxt.seekg(std::ios::beg);
		while (std::getline(myTxt, line))
		{
			for (size_t j{ 0 }; j < line.size(); ++j)
			{
				if (line[j] != ',')
				{
					fishVec[atoi(&line[j])] += 1;
				}

			}
		}
	}
	auto start = std::chrono::high_resolution_clock::now();
	for (size_t l{ 0 }; l < 519; l++)
	{
		long long temp1{ 0 }, temp2{ 0 };
		temp1 = fishVec[8];
		temp2 = fishVec[7];
		fishVec[7] = temp1;
		temp1 = fishVec[6];
		fishVec[6] = temp2;
		temp2 = fishVec[5];
		fishVec[5] = temp1;
		temp1 = fishVec[4];
		fishVec[4] = temp2;
		temp2 = fishVec[3];
		fishVec[3] = temp1;
		temp1 = fishVec[2];
		fishVec[2] = temp2;
		temp2 = fishVec[1];
		fishVec[1] = temp1;
		temp1 = fishVec[0];
		fishVec[6] += fishVec[0];
		fishVec[8] = fishVec[0];
		fishVec[0] = temp2;

	}
	long long sum{ 0 };
	for (const auto& it : fishVec)
	{
		sum += it;
	}
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	std::cout << "time: " << elapsed_seconds.count() << '\n';
	std::cout << sum;
	myTxt.close();
}

