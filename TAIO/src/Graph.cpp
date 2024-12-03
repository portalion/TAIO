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

std::ostream& operator<<(std::ostream& os, const Graph& g)
{
    for (int i = 0; i < g.verticesCount; ++i)
    {
        for (int j = 0; j < g.verticesCount; ++j)
        {
            os << g.edgeMatrix[i][j] << " ";
        }
        os << "\n";
    }
    return os;
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