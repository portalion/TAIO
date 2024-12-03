#pragma once
#include <vector>
#include <string>
#include "Graph.h"

std::vector<Graph> LoadGraphs(std::string filename);
void printGraphsInfo(const std::string& label, size_t count);
void printSeparator();
void printMenu();
int getValidInput(const std::string& prompt);
void displayMenuAndWaitForOperation();
Graph chooseGraph(const std::vector<Graph>& firstFileGraphs, const std::vector<Graph>& secondFileGraphs);