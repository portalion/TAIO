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
    std::cout << "Uzycie:\n"
        << "  ./Taio.exe [filename] distance [graph_index1] [graph_index2] [approx]\n"
        << "     oblicza odleglosc miedzy grafami o indeksach [graph_index1] i [graph_index2]\n"
        << "     Jesli podasz 'approx' na koncu, uzyty zostanie algorytm przyblizony.\n\n"
        << "  ./Taio.exe [filename] cycles [graph_index] [approx]\n"
        << "     oblicza najdluzsze cykle w grafie o indeksie [graph_index].\n"
        << "     Jesli podasz 'approx' na koncu, uzyty zostanie algorytm przyblizony.\n\n"
        << "  ./Taio.exe [filename] hamilton [graph_index] [approx]\n"
        << "     oblicza minimalny zbior krawedzi do dodania, by uzyskac cykl Hamiltona w grafie o indeksie [graph_index].\n"
        << "     Jesli podasz 'approx' na koncu, uzyty zostanie algorytm przyblizony.\n\n"
        << "Przyklady:\n"
        << "  ./Taio.exe dane.txt cycles 1\n"
        << "  ./Taio.exe dane.txt cycles 1 approx\n"
        << "  ./Taio.exe dane.txt hamilton 3\n"
        << "  ./Taio.exe dane.txt hamilton 3 approx\n"
        << "  ./Taio.exe dane.txt distance 5 6\n"
        << "  ./Taio.exe dane.txt distance 5 6 approx\n";
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
    // Sprawdzamy, czy faktycznie sie wczyta�y
    if (graphs.empty())
    {
        std::cerr << "Nie udalo sie wczytac zadnych grafow z pliku: " << filename << std::endl;
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
                std::cerr << "Niepoprawne indeksy grafow!\n";
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
                std::cerr << "Niepoprawny indeks grafu!\n";
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
                std::cerr << "Niepoprawny indeks grafu!\n";
                return 1;
            }

            graphComplementToHamiltonOperation(graphs[index], useApprox);
        }
        else
        {
            std::cerr << "Nieznana funkcja: " << function << std::endl;
            printUsage();
            return 1;
        }
    }
    catch (const std::exception& ex)
    {
        std::cerr << "Wystapil blad: " << ex.what() << std::endl;
        return 1;
    }

    return 0;
}
void getMaxCyclesOperation(Graph g, bool useApprox)
{
    std::vector<std::vector<int>> foundCycles;

    if (useApprox)
        foundCycles = approxGetMaxCycles(g);
    else
        foundCycles = getMaxCycles(g);

    printSeparator();
    std::cout << "Znaleziono " << foundCycles.size() << " cykli\n";
    for (int i = 0; i < (int)foundCycles.size(); i++)
    {
        std::cout << "Cykl " << i + 1 << ": ";
        for (auto cycleValue : foundCycles[i])
            std::cout << cycleValue << " ";

        // Dla �adnego zamkni�cia cyklu dodajemy pocz�tek na ko�cu
        std::cout << foundCycles[i][0] << '\n';
    }
    printSeparator();
}

void graphComplementToHamiltonOperation(Graph g, bool useApprox)
{
    std::vector<std::pair<int, int>> result;
    if (useApprox)
    {
        result = ApproximateATSP(g, 0, 1);
    }
    else
    {
        result = graphComplement(g);
    }

    for (auto edge : result)
    {
        g.addEdge(edge.first, edge.second);
    }

    printSeparator();
    std::cout << "Znaleziono nastepujace krawedzie do dodania (dopelnienie): \n";
    std::cout << g;
    printSeparator();
}

void graphDistanceOperation(Graph g1, Graph g2, bool useApprox)
{
    printSeparator();

    if (useApprox)
    {
        int dist = 0; //approximateDistance(g1, g2);
        std::cout << "Odleglosc aproksymowana pomiedzy grafami: " << dist << '\n';
    }
    else
    {
        int dist = Graph::GetDistanceBetweenGraphs(g1, g2);
        std::cout << "Odleglosc pomiedzy grafami: " << dist << '\n';
    }

    printSeparator();
}
