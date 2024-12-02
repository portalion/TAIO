#include <iostream>
#include "GraphReader.h"
#include "Algorithms.h"


int main()
{
	std::cout << "Hello from main!\n";

	std::ifstream input("data\\test2.txt");
	auto reader = GraphReader(input);
	while (!reader.isEmpty())
	{
		std::cout << "====================================\n";
		Graph graph = reader.readNextGraph();
		graph.printGraph(std::cout);
		std::cout << "Smallest complement:\n";
		std::vector<std::pair<int, int>> complement = graphComplement(graph);
		for (auto edge : complement)
		{
			std::cout << edge.first << ',' << edge.second << ' ';
		}
		std::cout << '\n';
		std::cout << "====================================\n";
	}

	//std::ifstream input("data\\test1.txt");
	//auto reader = GraphReader(input);
	//while (!reader.isEmpty())
	//{
	//	std::cout << "====================================\n";
	//	Graph graph = reader.readNextGraph();
	//	graph.printGraph(std::cout);
	//	std::cout << '\n';

	//	auto maxCycles = approxGetMaxCycles(graph);

	//	for (auto cycle : maxCycles)
	//	{
	//		for (auto v : cycle)
	//		{
	//			std::cout << v << ' ';
	//		}
	//		std::cout << '\n';
	//	}

	//	std::cout << '\n';
	//	std::cout << "====================================\n";
	//}

	std::cout << "Goodbye from main\n";
}