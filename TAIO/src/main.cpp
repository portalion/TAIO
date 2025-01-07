#include <iostream>
#include <iomanip>
#include <chrono>
#include <string>
#include <vector>
#include "GraphReader.h"
#include "Algorithms.h"
#include "CliHelpers.h"

void getMaxCyclesOperation(Graph g, bool useApprox);
void graphComplementToHamiltonOperation(Graph g, bool useApprox);
void graphDistanceOperation(Graph g1, Graph g2, bool useApprox);

void printUsage()
{
    std::cout << "Usage:\n"
        << "  ./Taio.exe [filename] distance [graph_index1] [graph_index2] [approx]\n"
        << "     calculates the distance between graphs with indices [graph_index1] and [graph_index2]\n"
        << "     If you provide 'approx' at the end, an approximate algorithm will be used.\n\n"
        << "  ./Taio.exe [filename] cycles [graph_index] [approx]\n"
        << "     calculates the longest cycles in the graph with index [graph_index].\n"
        << "     If you provide 'approx' at the end, an approximate algorithm will be used.\n\n"
        << "  ./Taio.exe [filename] hamilton [graph_index] [approx]\n"
        << "     calculates the minimal set of edges to add in order to obtain a Hamiltonian cycle in the graph with index [graph_index].\n"
        << "     If you provide 'approx' at the end, an approximate algorithm will be used.\n\n"
        << "Examples:\n"
        << "  ./Taio.exe data.txt cycles 1\n"
        << "  ./Taio.exe data.txt cycles 1 approx\n"
        << "  ./Taio.exe data.txt hamilton 3\n"
        << "  ./Taio.exe data.txt hamilton 3 approx\n"
        << "  ./Taio.exe data.txt distance 5 6\n"
        << "  ./Taio.exe data.txt distance 5 6 approx\n";
}

int main(int argc, char* argv[])
{
    //  tryb normalny - minimum 3 argumenty
    //    [filename], [function], [index lub dwa indeksy], ew. [approx]
    if (argc < 3)
    {
        printUsage();
        return 1;
    }

    // Nazwa pliku i funkcja
    std::string filename = argv[1];
    std::string function = argv[2];

    // Wczytujemy wszystkie grafy z pliku
    auto graphs = LoadGraphs(filename);
    // Sprawdzamy, czy faktycznie sie wczyta³y
    if (graphs.empty())
    {
        std::cerr << "Failed to load any graph from file: " << filename << std::endl;
        return 1;
    }

    // Weryfikujemy, czy ostatni argument to "approx"
    bool useApprox = false;
    if (std::string(argv[argc - 1]) == "approx")
    {
        useApprox = true;
    }

    try
    {
        if (function == "distance")
        {
            // Oczekujemy przynajmniej 5 argumentow: 
            // ./Taio.exe filename distance index1 index2 [approx]
            if (argc < 5)
            {
                printUsage();
                return 1;
            }

            int index1 = std::stoi(argv[3]);
            int index2 = std::stoi(argv[4]);

            if (index1 < 0 || index1 >= (int)graphs.size() ||
                index2 < 0 || index2 >= (int)graphs.size())
            {
                std::cerr << "Wrong graph index!\n";
                return 1;
            }

            // Wykonujemy operacje distance
            graphDistanceOperation(graphs[index1], graphs[index2], useApprox);
        }
        else if (function == "cycles")
        {
            // ./Taio.exe filename cycles index [approx]
            if (argc < 4)
            {
                printUsage();
                return 1;
            }

            int index = std::stoi(argv[3]);
            if (index < 0 || index >= (int)graphs.size())
            {
                std::cerr << "Wrong graph index!\n";
                return 1;
            }

            // Wykonujemy operacje cycles
            getMaxCyclesOperation(graphs[index], useApprox);
        }
        else if (function == "hamilton")
        {
            // ./Taio.exe filename hamilton index [approx]
            if (argc < 4)
            {
                printUsage();
                return 1;
            }

            int index = std::stoi(argv[3]);
            if (index < 0 || index >= (int)graphs.size())
            {
                std::cerr << "Wrong graph index!\n";
                return 1;
            }

            graphComplementToHamiltonOperation(graphs[index], useApprox);
        }
        else
        {
            std::cerr << "Unknown function: " << function << std::endl;
            printUsage();
            return 1;
        }
    }
    catch (const std::exception& ex)
    {
        std::cerr << "An error ocured: " << ex.what() << std::endl;
        return 1;
    }

    return 0;
}
void getMaxCyclesOperation(Graph g, bool useApprox)
{
    std::cout << "Max cycles\n";
    printSeparator();
    std::cout << "Graph\n"
        << "Number of vertices: " << g.getNumberOfVertices() << "\n"
        << "Adjacency matrix: \n";
    g.printGraph(std::cout);

    std::vector<std::vector<int>> foundCycles;

    if (useApprox)
        foundCycles = approxGetMaxCycles(g);
    else
        foundCycles = getMaxCycles(g);

    printSeparator();
    std::cout << "Found " << foundCycles.size() << " cycles\n";

    if (foundCycles.size() > 0)
    {
        std::cout << "Length of longest cycle: " << foundCycles[0].size() << "\n";
        std::cout << "Example cycle: \n";
        for (auto cycleValue : foundCycles[0])
            std::cout << cycleValue << " ";

        // Dla ³adnego zamkniêcia cyklu dodajemy pocz¹tek na koñcu
        std::cout << foundCycles[0][0] << '\n';
    }

    printSeparator();
}

void graphComplementToHamiltonOperation(Graph g, bool useApprox)
{
    std::cout << "Hamiltonian extension\n";
    printSeparator();
    std::cout << "Graph\n"
        << "Number of vertices:" << g.getNumberOfVertices() << "\n"
        << "Adjacency matrix: \n";
     g.printGraph(std::cout);

    std::vector<std::pair<int, int>> result;
    std::vector<std::vector<int>> foundCycles;

    if (useApprox)
    {
        result = ApproximateATSP(g, 0, 3);
    }
    else
    {
        result = graphComplement(g);
    }
    Graph edgesToAddGraph(g.getNumberOfVertices());

    for (auto edge : result)
    {
        edgesToAddGraph.addEdge(edge.first, edge.second);
    }

    printSeparator();
    std::cout << "Number of edges to add: "
        << result.size() << "\n";
    std::cout << "Edges to add: \n";
    std::cout << edgesToAddGraph;

    for (auto edge : result)
    {
        g.addEdge(edge.first, edge.second);
    }

    if (useApprox)
        foundCycles = approxGetMaxCycles(g);
    else
        foundCycles = getMaxCycles(g);

    std::cout << "Number of hamiltonian cycles: " << foundCycles.size() <<"\n";
    if(foundCycles.size() > 0)
    {
        std::cout << "Example cycle: \n";
        for (auto cycleValue : foundCycles[0])
            std::cout << cycleValue << " ";

        // Dla ³adnego zamkniêcia cyklu dodajemy pocz¹tek na koñcu
        std::cout << foundCycles[0][0] << '\n';
    }
    printSeparator();
}

void graphDistanceOperation(Graph g1, Graph g2, bool useApprox)
{
    printSeparator();

    if (useApprox)
    {
        int dist = Graph::GetDistanceBetweenGraphsApprox(g1, g2);
        std::cout << "Approximative distance between graphs is: " << dist << '\n';
    }
    else
    {
        int dist = Graph::GetDistanceBetweenGraphs(g1, g2);
        std::cout << "Distance between graphs is: " << dist << '\n';
    }

    printSeparator();
}
