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
		auto longestCycles = graph.getLongestCycles();
		if (!longestCycles.size())
			continue;

		for (auto cycle : longestCycles)
		{
			for (auto v : cycle)
			{
				std::cout << v << "->";
				if (v == cycle.back())
					std::cout << cycle[0] << '\n';
			}
		}

		std::cout << "Longest cycle count: " << graph.countLongestCycles() << "\n\n";
	}
}