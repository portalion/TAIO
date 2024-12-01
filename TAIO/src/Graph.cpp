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

std::vector<int> Graph::approximationDFS(int start) {
    std::vector<bool> visited(verticesCount, false);
    std::vector<int> parent(verticesCount, -1);
    std::stack<int> stack;
    std::vector<int> path;
    std::vector<int> longestPath;

    stack.push(start);
    visited[start] = true;

    while (!stack.empty()) 
    {
        int current = stack.top();
        stack.pop();
        path.push_back(current);

        for (int neighbor = 0; neighbor < verticesCount; ++neighbor) 
        {
            if (edgeMatrix[current][neighbor]) 
            {
                if (visited[neighbor] && neighbor != parent[current]) 
                {
                    longestPath = longestPath.size() < path.size() ? path : longestPath;
                }
                else if (!visited[neighbor]) {
                    stack.push(neighbor);
                    visited[neighbor] = true;
                    parent[neighbor] = current;
                }
            }
        }
    }

    return longestPath;
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