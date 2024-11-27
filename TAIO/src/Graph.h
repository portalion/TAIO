#pragma once
#include <vector>
#include <iostream>
class Graph
{
private:
	int verticesCount;
	int edgesCount;
	std::vector<std::vector<int>> edgeMatrix;
public:
	Graph(int verticesNumber);

	bool addEdge(int vertexA, int vertexB);
	bool removeEdge(int vertexA, int vertexB);
	void setEdge(int vertexA, int vertexB, int value);
	inline bool hasEdge(int vertexA, int vertexB) const { return edgeMatrix[vertexA][vertexB]; }
	inline int getNumberOfVertices() { return verticesCount; }
	inline int getNumberOfEdges() { return edgesCount; }

	void printGraph(std::ostream& stream) const;

	static int GetDistanceBetweenGraphs(Graph& a, Graph& b);
};

