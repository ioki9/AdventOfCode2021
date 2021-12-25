#include "DAY12.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <istream>
#include <string>
#include <cstdint>
#include <cctype>
#include <algorithm>
#include <queue>
#include <chrono>
#include <map>

struct Route
{
	std::string location;
	std::vector<std::string> visited;
	bool smallUsed{ false };
	bool willHave{ false };
};

void solveDAY12()
{
	std::string line{};
	std::ifstream myTxt;
	int path_count{ 0 };
	std::map < std::string, std::vector<std::string>> map{};
	std::queue<Route> route_queue{};
	myTxt.open("D:\\VC_projects\\AdventOfCode\\input.txt");
	if (myTxt.is_open())
	{
		myTxt.clear();
		myTxt.seekg(std::ios::beg);
		while (std::getline(myTxt, line))
		{
			std::string temp{};
			for (size_t j{ 0 }; j < line.size(); j++)
			{
				if (line[j] == '-')
				{
					map[temp].push_back(line.substr(j + 1));
					map[line.substr(j + 1)].push_back(temp);
					break;
				}
				temp += line[j];
			}
		}
		
	}
	
	for (const auto& rt : map["start"])
		route_queue.push(Route{ rt,{},{} });
	
	
	Route route{};
	
	while (!route_queue.empty())
	{
		
		route = route_queue.front();
		route_queue.pop();
	
		if (route.location == "end")
		{
			path_count += 1;
			continue;
		}
		
		if (route.willHave)
			route.smallUsed = true;
		if (!std::isupper(route.location[0]))
			route.visited.push_back(route.location);
		

		
		for (const auto& rt : map[route.location])
		{

			if (std::find(route.visited.begin(), route.visited.end(), rt) != route.visited.end())
			{
				if (route.smallUsed == true)
					continue;
				route.willHave = true;
			}
			if (rt != "start")
			{
				route_queue.push(Route{ rt, route.visited, route.smallUsed,route.willHave });
			}
			route.willHave = false;
		}
	}

	std::cout <<"\n\npath count:"<< path_count<<"\n";
	myTxt.close();
}
