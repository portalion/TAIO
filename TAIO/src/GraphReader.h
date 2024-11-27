#pragma once
#include <fstream>
#include "Graph.h"

class GraphReader
{
	std::istream& streamToReadFrom;
	int numberOfGraphs;
public:
	inline bool isEmpty() { return numberOfGraphs <= 0; }
	GraphReader(std::istream& input);
	Graph readNextGraph();
};

