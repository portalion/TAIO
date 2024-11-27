#include "Graph.h"
#include <ostream>

Graph::Graph(int verticesNumber)
{
	this->verticesCount = verticesNumber;
	this->edgeMatrix = std::vector<std::vector<int>>
		(this->verticesCount, std::vector<int>(this->verticesCount, 0));
}

void Graph::searchCycleDFS(int current, int start, std::vector<bool>& visited, std::vector<int>& path, int& maxLength, std::vector<int>& longestCycle)
{
	path.push_back(current);
	visited[current] = true;

	for (int neighbor = 0; neighbor < verticesCount; ++neighbor)
	{
		if (edgeMatrix[current][neighbor])
		{
			if (neighbor == start)
			{
				if (path.size() > maxLength)
				{
					maxLength = path.size();
					longestCycle = path;
				}
			}
			else if (!visited[neighbor])
			{
				searchCycleDFS(neighbor, start, visited, path, maxLength, longestCycle);
			}
		}
	}

	visited[current] = false;
	path.pop_back();
}

bool Graph::addEdge(int vertexA, int vertexB)
{
	bool hadEdge = hasEdge(vertexA, vertexB);
	edgeMatrix[vertexA][vertexB] = 1;

	edgesCount++;
	if (hadEdge)
		edgesCount--;

	return !hadEdge;
}

bool Graph::removeEdge(int vertexA, int vertexB)
{
	bool hadEdge = hasEdge(vertexA, vertexB);
	edgeMatrix[vertexA][vertexB] = 0;

	edgesCount--;
	if (hadEdge)
		edgesCount++;

	return hadEdge;
}

void Graph::setEdge(int vertexA, int vertexB, int value)
{
	if (value == 0)
		removeEdge(vertexA, vertexB);
	else
		addEdge(vertexA, vertexB);
}

void Graph::printGraph(std::ostream& stream) const
{
	stream << this->verticesCount << '\n';

	for (std::vector<int> row : this->edgeMatrix)
	{
		for (int edgeValue : row)
			stream << edgeValue << ' ';
		stream << '\n';
	}
}

int Graph::GetDistanceBetweenGraphs(Graph& a, Graph& b)
{
	if (a.verticesCount > b.verticesCount)
	{
		return GetDistanceBetweenGraphs(b, a);
	}
	
	int result = 0;
	result += std::abs(a.verticesCount - b.verticesCount);

	for (int i = 0; i < a.verticesCount; i++)
	{
		for (int j = 0; j < a.verticesCount; j++)
		{
			if (a.edgeMatrix[i][j] != b.edgeMatrix[i][j])
				result++;
		}
	}

	for (int i = a.verticesCount; i < b.verticesCount; i++)
	{
		for (int j = 0; j < b.verticesCount; j++)
		{
			if (b.edgeMatrix[i][j] == 1)
				result++;
			if (b.edgeMatrix[j][i] == 1)
				result++;
		}
	}

	for (int i = a.verticesCount; i < b.verticesCount; i++)
	{
		for (int j = a.verticesCount; j < b.verticesCount; j++)
		{
			if (b.edgeMatrix[i][j] == 1)
				result--;
		}
	}

	return result;
}

std::vector<int> Graph::getMaximumCycle()
{
	int maxLength = 0;
	std::vector<int> longestCycle;
	std::vector<bool> visited(verticesCount, false);
	std::vector<int> path;

	for (int start = 0; start < verticesCount; ++start)
	{
		searchCycleDFS(start, start, visited, path, maxLength, longestCycle);
	}

	return longestCycle;
}