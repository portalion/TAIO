#include "Graph.h"
#include <ostream>

Graph::Graph(int verticesNumber)
{
	this->verticesNumber = verticesNumber;
	this->edgeMatrix = std::vector<std::vector<int>>
		(this->verticesNumber, std::vector<int>(this->verticesNumber, 0));
}

bool Graph::addEdge(int vertexA, int vertexB)
{
	edgeMatrix[vertexA][vertexB] = 1;

	return !hasEdge(vertexA, vertexB);
}

bool Graph::removeEdge(int vertexA, int vertexB)
{
	edgeMatrix[vertexA][vertexB] = 0;

	return hasEdge(vertexA, vertexB);
}

void Graph::setEdge(int vertexA, int vertexB, int value)
{
	edgeMatrix[vertexA][vertexB] = value;
}

void Graph::printGraph(std::ostream& stream) const
{
	stream << this->verticesNumber << '\n';

	for (std::vector<int> row : this->edgeMatrix)
	{
		for (int edgeValue : row)
			stream << edgeValue << ' ';
		stream << '\n';
	}
	stream << '\n';
}

