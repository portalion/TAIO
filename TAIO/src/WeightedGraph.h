#pragma once
#include <vector>
#include <iostream>
#include <limits>

class WeightedGraph
{
private:
    int verticesCount;
    int edgesCount;
    // U¿ywamy typu int dla wag; wartoœæ std::numeric_limits<int>::max() oznacza brak krawêdzi
    std::vector<std::vector<int>> edgeMatrix;

public:
    WeightedGraph(int verticesNumber);

    void addEdge(int vertexA, int vertexB, int weight);
    void setEdgeWeight(int vertexA, int vertexB, int weight);
    int getEdgeWeight(int vertexA, int vertexB) const;
    bool hasEdge(int vertexA, int vertexB) const;

    int getVerticesCount() const;
    int getEdgesCount() const;

    void printGraph(std::ostream& stream) const;

    // Funkcja przekszta³caj¹ca graf nieskierowany bez wag na pe³ny graf skierowany z wagami
    static WeightedGraph FromUnweightedGraph(class Graph unweightedGraph);
};
