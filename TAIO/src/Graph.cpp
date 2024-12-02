#include "Graph.h"
#include <ostream>
#include <unordered_map>
#include <stack>

Graph::Graph(int verticesNumber)
{
    this->verticesCount = verticesNumber;
    this->edgeMatrix = std::vector<std::vector<int>>
        (this->verticesCount, std::vector<int>(this->verticesCount, 0));
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