#include "Graph.h"
#include <stack>
#include <map>
#include <set>
#include <queue>
#include <vector>
#include <algorithm>
#include "Algorithms.h"

bool compareBySize(const std::set<int>& a, const std::set<int>& b) {
    return a.size() < b.size();
}

std::vector<std::set<int>> getAllSubsets(int n)
{
    std::queue<std::set<int>> vertexSubsets;
    std::set<int> emptySet;
    vertexSubsets.push(emptySet);
    for (int i = 1; i < n; ++i)
    {
        int queueSize = vertexSubsets.size();
        for (int j = 0; j < queueSize; ++j)
        {
            std::set<int> vec = vertexSubsets.front();
            vertexSubsets.pop();
            std::set<int> vecCopy = vec;
            vecCopy.insert(i);
            vertexSubsets.push(vec);
            vertexSubsets.push(vecCopy);
        }
    }

    std::vector<std::set<int>> vec;
    while (!vertexSubsets.empty()) {
        vec.push_back(vertexSubsets.front());
        vertexSubsets.pop();
    }

    std::sort(vec.begin(), vec.end(), compareBySize);
    return vec;
}

void maxCyclesDFS(Graph& graph, int current, int start, std::vector<bool>& visited, std::vector<int>& path, int& maxLength, std::vector<std::vector<int>>& maxCycles)
{
    path.push_back(current);
    visited[current] = true;

    for (int neighbor = 0; neighbor < graph.getNumberOfVertices(); ++neighbor)
    {
        if (graph.hasEdge(current, neighbor))
        {
            if (neighbor == start) 
            {
                if (path.size() > maxLength)
                {
                    maxLength = path.size();
                    maxCycles.clear();
                    maxCycles.push_back(path);
                }
                else if (path.size() == maxLength)
                {
                    maxCycles.push_back(path);
                }
            }
            else if (!visited[neighbor])
            {
                maxCyclesDFS(graph, neighbor, start, visited, path, maxLength, maxCycles);
            }
        }
    }

    visited[current] = false;
    path.pop_back();
}

std::vector<std::vector<int>> getMaxCycles(Graph& graph)
{
    int verticesCount = graph.getNumberOfVertices();
    std::vector<std::vector<int>> allLongestCycles;
    int maxLength = 0;
    std::vector<bool> visited(verticesCount, false);
    std::vector<int> path;

    for (int start = 0; start < verticesCount; ++start)
    {
        maxCyclesDFS(graph, start, start, visited, path, maxLength, allLongestCycles);
    }

    return allLongestCycles;
}

int getMaxCyclesCount(Graph& graph)
{
    return getMaxCycles(graph).size();
}

std::vector<std::pair<int, int>> graphComplement(Graph graph)
{
    std::vector<std::pair<int, int>> complement;
    int n = graph.getNumberOfVertices();

    std::vector<std::set<int>> subsets = getAllSubsets(n);

    std::map<std::pair<std::set<int>, int>, std::pair<std::vector<int>, int>> g;
    for (int k = 1; k < n; ++k)
    {
        std::set<int> subset;
        subset.insert(k);
        std::vector<int> path;
        path.push_back(k);
        int cost = graph.hasEdge(0, k) ? 0 : 1;

        std::pair<std::set<int>, int> keyPair;
        keyPair.first = subset;
        keyPair.second = k;

        std::pair<std::vector<int>, int> valuePair;
        valuePair.first = path;
        valuePair.second = cost;

        g[keyPair] = valuePair;
    }

    for (const auto& subset : subsets)
    {
        int s = subset.size();
        if (s < 2)
            continue;

        for (int k : subset)
        {
            int minCost = n + 10;
            int minM = -1;
            std::set<int> keySet = subset;
            keySet.erase(k);
            for (int m : subset)
            {
                if (k == m)
                    continue;

                int dmk = graph.hasEdge(m, k) ? 0 : 1;
                std::pair<std::set<int>, int> keyPair;
                keyPair.first = keySet;
                keyPair.second = m;
                int cost = g[keyPair].second + dmk;

                if (cost < minCost)
                {
                    minCost = cost;
                    minM = m;
                }
            }
            std::pair<std::set<int>, int> keyPair;
            keyPair.first = subset;
            keyPair.second = k;

            std::pair<std::set<int>, int> tempPair;
            tempPair.first = keySet;
            tempPair.second = minM;
            std::vector<int> path = g[tempPair].first;
            path.push_back(k);

            std::pair<std::vector<int>, int> valuePair;
            valuePair.first = path;
            valuePair.second = minCost;

            g[keyPair] = valuePair;
        }
    }

    std::set<int> fullSubset = subsets[subsets.size() - 1];
    int bestCost = n + 10;
    int bestK = -1;
    std::pair<std::set<int>, int> keyPair;
    keyPair.first = fullSubset;
    for (int k = 1; k < n; ++k)
    {
        keyPair.second = k;
        int cost = g[keyPair].second + graph.hasEdge(0, k) ? 0 : 1;
        if (cost < bestCost)
        {
            bestCost = cost;
            bestK = k;
        }
    }

    keyPair.second = bestK;
    std::vector<int> finalPath = g[keyPair].first;
    finalPath.push_back(0);
    finalPath.push_back(finalPath[0]);
    for (int i = 0; i < n; ++i)
    {
        if (!graph.hasEdge(finalPath[i], finalPath[i + 1]))
        {
            std::pair<int, int> edge;
            edge.first = finalPath[i];
            edge.second = finalPath[i + 1];
            complement.push_back(edge);
        }
    }

    return complement;
}
