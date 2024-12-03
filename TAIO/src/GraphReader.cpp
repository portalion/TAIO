#include "GraphReader.h"
#include "Graph.h"
#include <string>
#include <algorithm>
#include <sstream>

bool isSingleInteger(const std::string& line) {
    std::istringstream iss(line);
    int num;
    return (iss >> num) && (iss.eof());
}

GraphReader::GraphReader(std::istream& input)
    : streamToReadFrom{ input }, numberOfGraphs{ 0 }
{
    std::stringstream tempStream; // Temporary stream to store read lines
    std::string line;
    int singleIntegerLines = 0;
    for (int i = 0; i < 2; i++)
    {
        std::getline(input, line);
        tempStream << line << '\n';
        singleIntegerLines += isSingleInteger(line);
    }
    for(int i = tempStream.str().size() - 1; i >= 0; i--)
        input.putback(tempStream.str()[i]);

    if (singleIntegerLines == 1)
        this->numberOfGraphs = 1;
    else
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
        std::string line;
        std::getline(streamToReadFrom, line); 
        std::istringstream lineStream(line); 

        for (int j = 0; j < vertices; j++) 
        {
            int edgeValue;
            lineStream >> edgeValue; 
            result.setEdge(i, j, !!edgeValue);
        }
    }

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