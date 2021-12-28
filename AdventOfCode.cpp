#include "DAY14.h"
#include <chrono>
#include <iostream>

int main()
{
	auto start = std::chrono::high_resolution_clock::now();
	solveDAY14();
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = end - start;
	std::cout << "\n\n elapsed time:" << elapsed.count() << "s.";
	return 1;
}