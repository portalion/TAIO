#include "Graph.h"
#include <ostream>
#include <unordered_map>

Graph::Graph(int verticesNumber)
{
    this->verticesCount = verticesNumber;
    this->edgeMatrix = std::vector<std::vector<int>>
        (this->verticesCount, std::vector<int>(this->verticesCount, 0));
}

void Graph::searchCycleDFS(int current, int start, std::vector<bool>& visited, std::vector<int>& path, int& maxLength, std::vector<std::vector<int>>& allLongestCycles)
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
                    allLongestCycles.clear();
                    allLongestCycles.push_back(path);
                }
                else if (path.size() == maxLength)
                {
                    allLongestCycles.push_back(path);
                }
            }
            // could we add that condition path.size() + (verticesCount - path.size()) > maxLength
            else if (!visited[neighbor])
            {
                searchCycleDFS(neighbor, start, visited, path, maxLength, allLongestCycles);
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

std::vector<std::vector<int>> Graph::getLongestCycles()
{
    int maxLength = 0;
    std::vector<std::vector<int>> allLongestCycles;
    std::vector<bool> visited(verticesCount, false);
    std::vector<int> path;

    for (int start = 0; start < verticesCount; ++start)
    {
        searchCycleDFS(start, start, visited, path, maxLength, allLongestCycles);
    }

    return allLongestCycles;
}

int Graph::countLongestCycles()
{
    int maxLength = 0;
    std::vector<std::vector<int>> allLongestCycles;
    std::vector<bool> visited(verticesCount, false);
    std::vector<int> path;

    for (int start = 0; start < verticesCount; ++start)
    {
        searchCycleDFS(start, start, visited, path, maxLength, allLongestCycles);
    }

    return allLongestCycles.size();
}