#pragma once
#include <vector>
#include <iostream>

class Graph
{
private:
	int edgesCount;
	int verticesCount;
	std::vector<std::vector<int>> edgeMatrix;

	static int GetDistanceBetweenGraphsHelper(Graph& a, Graph& b);
public:
	Graph(int verticesNumber);
	Graph(std::vector<int> verticesPermutation, const Graph& b);

	bool addEdge(int vertexA, int vertexB);
	bool removeEdge(int vertexA, int vertexB);
	void setEdge(int vertexA, int vertexB, int value);
	inline bool isEmpty() { return verticesCount == 0; }
	inline bool hasEdge(int vertexA, int vertexB) const { return edgeMatrix[vertexA][vertexB]; }
	inline int getNumberOfVertices() { return verticesCount; }
	inline int getNumberOfEdges() { return edgesCount; }

	void printGraph(std::ostream& stream) const;

	int getVertexDegree(int vertexIndex);
	static int GetDistanceBetweenGraphs(Graph& a, Graph& b);
	static int GetDistanceBetweenGraphsApprox(Graph& a, Graph& b);
	friend std::ostream& operator<<(std::ostream& os, const Graph& g);
};