#include "Graph.h"
#include "WeightedGraph.h"

WeightedGraph::WeightedGraph(int verticesNumber)
{
    this->verticesCount = verticesNumber;
    this->edgesCount = 0;
    this->edgeMatrix = std::vector<std::vector<int>>(
        this->verticesCount, std::vector<int>(this->verticesCount, std::numeric_limits<int>::max()));
}

void WeightedGraph::addEdge(int vertexA, int vertexB, int weight)
{
    if (!hasEdge(vertexA, vertexB))
    {
        edgesCount++;
    }
    edgeMatrix[vertexA][vertexB] = weight;
}

void WeightedGraph::setEdgeWeight(int vertexA, int vertexB, int weight)
{
    if (!hasEdge(vertexA, vertexB))
    {
        edgesCount++;
    }
    edgeMatrix[vertexA][vertexB] = weight;
}

int WeightedGraph::getEdgeWeight(int vertexA, int vertexB) const
{
    return edgeMatrix[vertexA][vertexB];
}

bool WeightedGraph::hasEdge(int vertexA, int vertexB) const
{
    return edgeMatrix[vertexA][vertexB] != std::numeric_limits<int>::max();
}

int WeightedGraph::getVerticesCount() const
{
    return verticesCount;
}

int WeightedGraph::getEdgesCount() const
{
    return edgesCount;
}

void WeightedGraph::printGraph(std::ostream& stream) const
{
    stream << this->verticesCount << '\n';

    for (const std::vector<int>& row : this->edgeMatrix)
    {
        for (int edgeValue : row)
        {
            if (edgeValue == std::numeric_limits<int>::max())
                stream << "INF ";
            else
                stream << edgeValue << ' ';
        }
        stream << '\n';
    }
    stream << '\n';
}

WeightedGraph WeightedGraph::FromUnweightedGraph(Graph unweightedGraph)
{
    int n = unweightedGraph.getNumberOfVertices();
    WeightedGraph weightedGraph(n);

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (i == j)
            {
                // Brak pêtli w³asnych; ustawiamy wagê na INF
                weightedGraph.setEdgeWeight(i, j, std::numeric_limits<int>::max());
            }
            else if (unweightedGraph.hasEdge(i, j))
            {
                // KrawêdŸ istnia³a w oryginalnym grafie; ustawiamy wagê na 0
                weightedGraph.setEdgeWeight(i, j, 0);
            }
            else
            {
                // KrawêdŸ nie istnia³a; dodajemy j¹ z wag¹ 1
                weightedGraph.setEdgeWeight(i, j, 1);
            }
        }
    }

    return weightedGraph;
}
