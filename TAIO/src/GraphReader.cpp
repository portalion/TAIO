#include "GraphReader.h"
#include "Graph.h"
#include <string>
#include <algorithm>

GraphReader::GraphReader(std::istream& input)
: streamToReadFrom{input}
{
    streamToReadFrom >> this->numberOfGraphs;
}

Graph GraphReader::readNextGraph()
{
    if (!this->numberOfGraphs--)
    {
        throw "cannot load more graphs";
    }
    int vertices;
    streamToReadFrom >> vertices;
    Graph result = Graph(vertices);
    for (int i = 0; i < vertices; i++)
    {
        for (int j = 0; j < vertices; j++)
        {
            int edgeValue;
            streamToReadFrom >> edgeValue;
            result.setEdge(i, j, !!edgeValue);
        }
    }

    streamToReadFrom.ignore(1);
    //skip to next graph
    std::string nextLine;
    while (std::getline(streamToReadFrom, nextLine)) 
    {
        if (nextLine.empty() || std::all_of(nextLine.begin(), nextLine.end(), ::isspace))
        {
            break;
        }
    }
    
    return result;
}

std::vector<Graph> GraphReader::readAllGraphs()
{
    std::vector<Graph> result;
    while (!isEmpty())
    {
        result.push_back(readNextGraph());
    }
    return result;
}