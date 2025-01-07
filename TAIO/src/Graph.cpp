#include "Graph.h"
#include <ostream>
#include <unordered_map>
#include <stack>
#include <algorithm>

int Graph::GetDistanceBetweenGraphsHelper(Graph& a, Graph& b)
{
    if (a.verticesCount > b.verticesCount)
    {
        return GetDistanceBetweenGraphsHelper(b, a);
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

int Graph::getVertexDegree(int vertexIndex)
{
    int result = 0;
    for (int i = 0; i < verticesCount; i++)
    {
        if (edgeMatrix[vertexIndex][i] > 0) result++;
    }
    return result;
}

Graph::Graph(int verticesNumber)
{
    this->verticesCount = verticesNumber;
    this->edgeMatrix = std::vector<std::vector<int>>
        (this->verticesCount, std::vector<int>(this->verticesCount, 0));
}

Graph::Graph(std::vector<int> verticesPermutation, const Graph& b)
{
    verticesCount = b.verticesCount;
    edgesCount = b.edgesCount;

    this->edgeMatrix = std::vector<std::vector<int>>
        (this->verticesCount, std::vector<int>(this->verticesCount, 0));

    for (int i = 0; i < edgeMatrix.size(); i++)
    {
        for (int j = 0; j < edgeMatrix[i].size(); j++)
        {
            edgeMatrix[i][j] = b.edgeMatrix[verticesPermutation[i]][verticesPermutation[j]];
        }
    }
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
    //stream << this->verticesCount << '\n';

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
    std::vector<int> aPermuted = std::vector<int>(a.getNumberOfVertices());
    for (int i = 0; i < aPermuted.size(); i++)
        aPermuted[i] = i;

    int result = std::numeric_limits<int>::max();

    do {
        auto newA = Graph(aPermuted, a);
        result = std::min(result, GetDistanceBetweenGraphsHelper(b, newA));
    } while (std::next_permutation(aPermuted.begin(), aPermuted.end()));

    return result;
}

int Graph::GetDistanceBetweenGraphsApprox(Graph& a, Graph& b)
{
    std::vector<int> aSorted = std::vector<int>(a.verticesCount);
    std::vector<int> bSorted = std::vector<int>(b.verticesCount);

    for (int i = 0; i < aSorted.size(); i++)
        aSorted[i] = i;

    for (int i = 0; i < bSorted.size(); i++)
        bSorted[i] = i;

    std::sort(aSorted.begin(), aSorted.end(), [&](int f, int s) {
        return a.getVertexDegree(f) < a.getVertexDegree(s);
        });
    std::sort(bSorted.begin(), bSorted.end(), [&](int f, int s) {
        return b.getVertexDegree(f) < b.getVertexDegree(s);
        });

    auto firstGraph = Graph(aSorted, a);
    auto secondGraph = Graph(bSorted, b);

    return GetDistanceBetweenGraphsHelper(firstGraph, secondGraph);
}
