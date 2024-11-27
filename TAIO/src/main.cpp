#include <iostream>
#include "GraphReader.h"


int main()
{
	std::ifstream input("data\\test1.txt");
	auto reader = GraphReader(input);
	while (!reader.isEmpty())
	{
		auto graph = reader.readNextGraph();
		graph.printGraph(std::cout);
		auto longestCycle = graph.getMaximumCycle();
		if (!longestCycle.size())
			continue;

		for (auto v : longestCycle)
		{
			std::cout << v << "->";
			if (v == longestCycle.back())
				std::cout << longestCycle[0];
		}

		std::cout << "\n\n";
	}
}