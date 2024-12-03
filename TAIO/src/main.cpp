#include <iostream>
#include <iomanip>
#include <chrono>
#include "GraphReader.h"
#include "Algorithms.h"
#include "CliHelpers.h"

bool askAboutApproximationAlgorithm();
void getMaxCyclesOperation(Graph g);
void graphComplementOperation(Graph g);
void graphDistanceOperation(Graph g1, Graph g2);


int main(int argc, char* argv[])
{
    if (argc < 2 || argc > 3)
    {
        std::cout << "Nie mozna zaladowac plikow. Podaj je jako argumenty (maksymalnie 2, minimalnie 1).\n";
        return 1;
    }

    auto firstFileGraphs = LoadGraphs(argv[1]);
    std::vector<Graph> secondFileGraphs;

    std::cout << std::left;
    printSeparator();
    if (argc == 3)
    {
        secondFileGraphs = LoadGraphs(argv[2]);
        std::cout << "Zaladowano 2 pliki\n";
        printGraphsInfo("Pierwszy plik zawiera:", firstFileGraphs.size());
        printGraphsInfo("Drugi plik zawiera:", secondFileGraphs.size());
    }
    else
    {
        std::cout << "Zaladowano 1 plik\n";
        printGraphsInfo("Plik zawiera:", firstFileGraphs.size());
    }
    printSeparator();
    
    int choice = 0;

    do
    {
        printMenu();
        choice = getValidInput("Wybierz opcje: ");

        switch (choice)
        {
        case 1:
        {
            auto g1 = chooseGraph(firstFileGraphs, secondFileGraphs);
            if (g1.isEmpty())
                break;

            getMaxCyclesOperation(g1);

            break;
        }
        case 2:
        {
            auto g1 = chooseGraph(firstFileGraphs, secondFileGraphs);
            if (g1.isEmpty())
                break;

            graphComplementOperation(g1);
            break;
        }
        case 3:
        {
            auto g1 = chooseGraph(firstFileGraphs, secondFileGraphs);
            if (g1.isEmpty())
                break;
            auto g2 = chooseGraph(firstFileGraphs, secondFileGraphs);
            if (g1.isEmpty())
                break;
            
            graphDistanceOperation(g1, g2);
            break;
        }
        case 0:
            std::cout << "Konczenie programu...\n";
            break;
        default:
            std::cout << "Niepoprawny wybor.\n";
            break;
        }
    } while (choice != 0);
    return 0;
}

bool askAboutApproximationAlgorithm()
{
    std::cout << "Czy chcesz uzyc algorytmu aproksymujacego? (1 - tak, 0 - nie): ";
    int choice = getValidInput("Wybierz 1 lub 0: ");

    return choice == 1;
}

void getMaxCyclesOperation(Graph g)
{
    std::vector<std::vector<int>> foundCycles;
    if (askAboutApproximationAlgorithm())
        foundCycles = approxGetMaxCycles(g);
    else
        foundCycles = getMaxCycles(g);

    printSeparator();
    std::cout << "Znaleziono " << foundCycles.size() << " cykli\n";
    for (int i = 0; i < foundCycles.size(); i++)
    {
        std::cout << "Cykl " << i + 1 << ": ";
        for (auto cycleValue : foundCycles[i])
            std::cout << cycleValue << " ";
        std::cout << foundCycles[i][0] << '\n';
    }
    printSeparator();
}

void graphComplementOperation(Graph g)
{
    std::vector<std::pair<int, int>> result;
    if (askAboutApproximationAlgorithm())
        result = ApproximateATSP(g, 0 , 1);
    else
        result = graphComplement(g);

    for (auto edge : result)
    {
        g.addEdge(edge.first, edge.second);
    }
    printSeparator();
    std::cout << "Znaleziono nastepujace dopelnienie: \n";
    std::cout << g;
    printSeparator();

}

void graphDistanceOperation(Graph g1, Graph g2)
{
    printSeparator();
    std::cout << "Odleglosc pomiedzy grafami wynosi: " << Graph::GetDistanceBetweenGraphs(g1, g2) << '\n';
    printSeparator();
}