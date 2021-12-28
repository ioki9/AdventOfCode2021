#include "DAY13.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <istream>
#include <string>
#include <cstdint>
#include <cctype>
#include <utility>
#include <algorithm>
#include <windows.h>
#include <chrono>
#include <unordered_set>
#include <set>


struct coord
{
	int x;
	int y;
};

void sortAndUniqueVector(std::vector<coord>& vec, bool sortX)
{
	auto hash = [](const coord& p) { return p.x + 10 * p.y; };
	auto equal = [](const coord& p1, const coord& p2) { return p1.x == p2.x && p1.y == p2.y; };
	std::unordered_set<coord, decltype(hash), decltype(equal)> s;
	for (auto& i : vec)
		s.insert(i);
	vec.assign(s.begin(), s.end());
	if (sortX)
		std::sort(vec.begin(), vec.end(), [](const coord& a, const coord& b) { return a.x < b.x  ; });
	else
		std::sort(vec.begin(), vec.end(), [](const coord& a, const coord& b) { return a.y < b.y; });
}
void foldPaper(std::vector<coord>& vec, const coord& fold)
{
	if (fold.x != 0)
	{
		int max_val{ 0 };
		for (auto iter = vec.rbegin(); iter != vec.rend(); iter++)
		{
			if (iter->x <= fold.x)
				break;
			if (iter != vec.rbegin())
			{
				iter->x = (max_val - iter->x);
			}
			else
			{
				max_val = fold.x*2;
				iter->x = vec[0].x;
			}
		}
	}
	else
	{
		int max_val{ 0 };
		for (auto iter = vec.rbegin(); iter != vec.rend(); iter++)
		{
			if (iter->y <= fold.y)
				break;
			if (iter != vec.rbegin())
			{
				iter->y = (max_val - iter->y);
			}
			else
			{
				max_val = fold.y*2;
				iter->y = vec[0].y;
			}
		}
	}
}

void solveDAY13()
{
	std::string line{};
	std::ifstream myTxt;
	std::vector<coord> dots{};
	std::vector<coord> folds{};
	myTxt.open("input.txt");	
	if (myTxt.is_open())
	{
		myTxt.clear();
		myTxt.seekg(std::ios::beg);
		while (std::getline(myTxt, line))
		{
			std::string x{};
			for (size_t j{ 0 }; j < line.size(); j++)
			{
				if (line[j] == ',')
				{

					dots.push_back({ atoi(x.c_str()),atoi(line.substr(j + 1).c_str()) });
					x = "";
					break;
				}
				x += line[j];

				if (line[j] == 'f')
				{
					if (line[j + 11] == 'x')
						folds.push_back({ atoi(line.substr(j + 13).c_str()),0 });
					else
						folds.push_back({ 0, atoi(line.substr(j + 13).c_str()) });
					break;
				}
			}
		}
	}
	if (folds.front().x != 0)
		std::sort(dots.begin(), dots.end(), [](const coord& a, const coord& b) {return a.x < b.x; });
	else
		std::sort(dots.begin(), dots.end(), [](const coord& a, const coord& b) {return a.y < b.y; });
	bool sortX{};
	for (auto iter = folds.begin(); iter != folds.end(); iter++)
	{
		if (iter->x != 0)
			sortX = true;
		else
			sortX = false;
		sortAndUniqueVector(dots, sortX);
		foldPaper(dots, *iter);
	}
	sortAndUniqueVector(dots, false);

	HANDLE console_out = GetStdHandle(STD_OUTPUT_HANDLE);
	for (const auto& it : dots)
	{
		SetConsoleCursorPosition(console_out, COORD(it.x, it.y));
		std::cout << '#';
	}
		
	myTxt.close();

}