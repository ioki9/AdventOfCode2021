
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <bitset>
#include <string_view>
#include <algorithm>
#include <array>
#define MAX_LINES_TXT 999;
typedef std::array<std::array<std::string, 5>, 5>::iterator matrix_iter;

enum class identif
{
	row,
	column
};
int count{};
std::tuple<size_t, identif, size_t> getMinSum(std::array<std::array<std::string, 5>, 5>& matrix, std::vector<std::string>& checkNumbers)
{

	size_t maxValC{ 20000 };
	size_t temp{ 0 };
	size_t tempR{ 0 };
	size_t maxValR{ 20000 };
	size_t minCol{};
	size_t minRow{};
	size_t minRowColNum{};
	std::vector<std::pair<int, int>> rowsMax{};
	std::vector<std::pair<int, int>> columnsMax{};
	for (size_t row{ 0 }; row < 5; ++row)
	{
		tempR = 0;
		temp = 0;
		for (size_t column{ 0 }; column < 5; ++column)
		{
			auto foundR = std::find(checkNumbers.begin(), checkNumbers.end(), matrix[row][column]);
			if (foundR != checkNumbers.cend())
			{
				if (tempR < std::distance(checkNumbers.begin(), foundR))
					tempR = std::distance(checkNumbers.begin(), foundR);
			}
			else
			{
				tempR += 200000;
			}

			auto foundC = std::find(checkNumbers.begin(), checkNumbers.end(), matrix[column][row]);
			if (foundC != checkNumbers.cend())
			{
				if (temp < std::distance(checkNumbers.begin(), foundC))
					temp = std::distance(checkNumbers.begin(), foundC);
			}
			else
			{
				temp += 200000;
			}
		}

		rowsMax.push_back(std::pair<int, int>(tempR, row));
		columnsMax.push_back(std::pair<int, int>(temp, row));
	}
	identif id;
	size_t result{ 20000 };
	for (size_t k{ 0 }; k < 5; ++k)
	{
		if (rowsMax[k].first < result)
		{
			result = rowsMax[k].first;
			minRowColNum = rowsMax[k].second;
			id = identif::row;
		}

		if (columnsMax[k].first < result)
		{
			result = columnsMax[k].first;
			minRowColNum = columnsMax[k].second;
			id = identif::column;
		}

	}

	return std::tuple(result, id, minRowColNum);
}

void solveDAY4()
{
	std::string line{};
	std::ifstream myTxt;
	myTxt.open("D:\\VC_projects\\AdventOfCode\\input.txt");
	std::vector < std::string> numbersToCheck{};
	size_t maxValId{ 0 };
	size_t minSumPos{ 0 };
	if (myTxt.is_open())
	{
		//getting numbers to check
		std::getline(myTxt, line);
		std::string tempNum{};
		for (size_t ch{ 0 }; ch < line.size(); ++ch)
		{
			if (line[ch] != ',')
			{
				tempNum += line[ch];
			}
			else
			{
				numbersToCheck.push_back(tempNum);
				tempNum = "";
			}
		}
		numbersToCheck.push_back(tempNum);
		size_t lCount{ 0 };
		myTxt.clear();
		myTxt.seekg(std::ios::beg);
		std::getline(myTxt, line);
		std::getline(myTxt, line);
		lCount += 2;
		std::string temp{};
		size_t arrIndexR{ 0 };
		size_t arrIndexC{ 0 };
		std::array<std::array<std::string, 5>, 5> tempMatrix{};
		std::array<std::array<std::string, 5>, 5> minMatrix{};
		identif minRow_Col{};
		size_t minRow_ColNum{};
		while (std::getline(myTxt, line))
		{
			lCount++;

			if (line.empty())
			{

				if (std::tuple<size_t, identif, size_t> newSum{ (getMinSum(tempMatrix,numbersToCheck)) }; maxValId < std::get<0>(newSum))
				{

					minMatrix = tempMatrix;
					minRow_Col = std::get<1>(newSum);
					maxValId = std::get<0>(newSum);
					minRow_ColNum = std::get<2>(newSum);
					minSumPos = lCount;
				}
				arrIndexR = 0;
				continue;
			}

			//fill matrix
			arrIndexC = 0;
			for (size_t k{ 0 }; k < line.size(); ++k)
			{
				if ((k + 1) % 3 == 0)
				{
					tempMatrix[arrIndexR][arrIndexC] = temp;
					temp = "";
					//std::cout << minMatrix[arrIndexR][arrIndexC]<<" ";
					arrIndexC++;
					continue;
				}
				if (line[k] != ' ')
					temp += line[k];
			}
			tempMatrix[arrIndexR][arrIndexC] = temp;
			//std::cout << minMatrix[arrIndexR][arrIndexC] << "   row/col: " << static_cast<int>(minRow_Col) << "  " << "number:" << minRow_ColNum << "  sum:" << minSumHoriz<< "\n";
			temp = "";
			++arrIndexR;

		}

		if (std::tuple<size_t, identif, size_t> newSum{ (getMinSum(tempMatrix,numbersToCheck)) }; maxValId < std::get<0>(newSum))
		{

			minMatrix = tempMatrix;
			minRow_Col = std::get<1>(newSum);
			maxValId = std::get<0>(newSum);
			minRow_ColNum = std::get<2>(newSum);
			minSumPos = lCount;
		}
		int sum{};

		for (size_t row{ 0 }; row < 5; row++)
		{
			std::cout << '\n';
			for (size_t col{ 0 }; col < 5; col++)
			{
				std::cout << minMatrix[row][col] << " ";
				auto found = std::find(numbersToCheck.begin(), numbersToCheck.end(), minMatrix[row][col]);
				if (found < (numbersToCheck.begin() + maxValId + 1))
					continue;
				sum += atoi(minMatrix[row][col].c_str());
			}
		}

		std::cout << '\n' << '\n';
		std::cout << "row/col: " << static_cast<int>(minRow_Col) << "  " << "number:" << minRow_ColNum << "  max:" << maxValId << '\n';
		std::wcout << sum << "*" << atoi(numbersToCheck[maxValId].c_str()) << "=" << sum * atoi(numbersToCheck[maxValId].c_str());
	}

	//std::cout << "\n\nposition:" << commonBits <<"\n\n";
	myTxt.close();
}

