#include <iostream>
#include "GraphReader.h"


int main()
{
	std::ifstream input("data\\test1.txt");
	auto reader = GraphReader(input);
	while (!reader.isEmpty())
	{
		reader.readNextGraph().printGraph(std::cout);
	}
}