#pragma once
#include <vector>
#include <iostream>
class Graph
{
private:
	int verticesNumber;
	std::vector<std::vector<int>> edgeMatrix;
public:
	Graph(int verticesNumber);

	bool addEdge(int vertexA, int vertexB);
	bool removeEdge(int vertexA, int vertexB);
	void setEdge(int vertexA, int vertexB, int value);
	inline bool hasEdge(int vertexA, int vertexB) const { return edgeMatrix[vertexA][vertexB]; }
	inline int getNumberOfVertices() { return verticesNumber; }

	void printGraph(std::ostream& stream) const;
};

