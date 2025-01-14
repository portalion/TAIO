#pragma once
#include <stack>
#include <map>
#include <set>
#include <queue>
#include <vector>
#include <algorithm>
#include "Graph.h"
#include "WeightedGraph.h"

// ===== Max cycles =====

std::vector<std::vector<int>> getMaxCycles(Graph& graph);
int getMaxCyclesCount(Graph& graph);

std::vector<std::vector<int>> approxGetMaxCycles(Graph& graph);
int approxGetMaxCyclesCount(Graph& graph);

// ===== Max cycles =====

// ===== Complement finding =====

std::vector<std::pair<int, int>> graphComplement(Graph graph);

std::vector<std::pair<int, int>> ApproximateATSP( Graph& graph, int startVertex, int maxDepth);


// ===== Complement finding =====