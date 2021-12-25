#include "DAY10.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <istream>
#include <string>
#include <cstdint>
#include <chrono>
#include <algorithm>
#include <stack>


void solveDAY10()
{
	std::string line{};
	std::ifstream myTxt;

	myTxt.open("D:\\VC_projects\\AdventOfCode\\input.txt");
	long sum{ 0 };
	short curly_count{ 0 };
	short square_count{ 0 };
	short round_count{ 0 };
	short angle_count{ 0 };
	std::vector<size_t> p2_scores{};
	std::string	bracketsOpen{};
	auto getReverseBracket = [](const char bracket) 
	{ 
		switch (bracket)
	{
	case '[':
		return ']';
	case '{':
		return '}';
	case '(':
		return ')';
	case '<':
		return '>';
	case '>':
		return '<';
	case ')':
		return '(';
	case '}':
		return '{';
	case ']':
		return '[';
	}

	};
	if (myTxt.is_open())
	{
		myTxt.clear();
		myTxt.seekg(std::ios::beg);
		while (std::getline(myTxt, line))
		{
			for (size_t j{ 0 }; j < line.size(); ++j)
			{
				if (line[j] == '[' || line[j] == '{' || line[j] == '(' || line[j] == '<')
					bracketsOpen += line[j];
				else
				{
					if (bracketsOpen.back() == getReverseBracket(line[j]))
						bracketsOpen.erase(bracketsOpen.end() - 1);
					else
					{
						switch (line[j])
						{
						case ']':
							square_count++;
							break;
						case '}':
							curly_count++;
							break;
						case ')':
							round_count++;
							break;
						case '>':
							angle_count++;
							break;
						default:
							break;
						}
						bracketsOpen = "";
						break;
					}
				}
			}
			if (!bracketsOpen.empty())
			{
				size_t sum{ 0 };
				for (auto iter = bracketsOpen.rbegin(); iter != bracketsOpen.rend(); ++iter)
				{
					sum *= 5;
					switch (*iter)
					{
					case '(':
						sum += 1;
						break;
					case '[':
						sum += 2;
						break;
					case '{':
						sum += 3;
						break;
					case '<':
						sum += 4;
						break;
					}
				}
				p2_scores.push_back(sum);
				bracketsOpen = "";
			}
		}
		std::sort(p2_scores.begin(), p2_scores.end());

		std::cout <<"______________PART 1______________\n\n"<< round_count << "*3+" << square_count << "*57+" << curly_count << "*1197+" << angle_count << "*25137="
			<< round_count * 3 + square_count * 57 + curly_count * 1197 + angle_count * 25137<<'\n';
		std::cout << "______________PART 2______________\n\n" << p2_scores[(p2_scores.size() - 1) / 2];

	}
	myTxt.close();
}

