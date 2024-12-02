#pragma once
#include <stack>
#include <map>
#include <set>
#include <queue>
#include <vector>
#include <algorithm>
#include "Graph.h"
#include "WeightedGraph.h"
// ===== Complement finding =====

std::vector<std::pair<int, int>> graphComplement(Graph graph);

std::vector<std::pair<int, int>> ApproximateATSP(const Graph& graph, int startVertex, int maxDepth);


// ===== Complement finding =====