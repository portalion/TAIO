#include <iostream>
#include <iomanip>
#include <limits>
#include "CliHelpers.h"
#include "GraphReader.h"

std::vector<Graph> LoadGraphs(std::string filename)
{
    std::ifstream file(filename);
    return GraphReader(file).readAllGraphs();
}

void printGraphsInfo(const std::string& label, size_t count)
{
    std::cout << std::left << std::setw(30) << label << count << " grafow\n";
}

void printSeparator()
{
    std::cout << std::string(40, '=') << '\n';
}

void printMenu()
{
    printSeparator();
    std::cout << std::left;
    std::cout << std::setw(10) << "Opcja" << "Opis\n";
    printSeparator();
    std::cout << std::setw(10) << " 1." << "Znajdz maksymalne cykle w grafie\n";
    std::cout << std::setw(10) << " 2." << "Znajdz minimalne rozszerzenie grafu do zawierajacego CH\n";
    std::cout << std::setw(10) << " 3." << "Policz odleglosc miedzy dwoma grafami\n";
    std::cout << std::setw(10) << " 0." << "Wyjdz\n";
    printSeparator();
}

int getValidInput(const std::string& prompt)
{
    int choice;
    while (true)
    {
        std::cout << prompt;
        std::cin >> choice;

        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Niepoprawny wybor. Podaj liczbe calkowita.\n";
        }
        else
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return choice;
        }
    }
}

Graph chooseGraph(const std::vector<Graph>& firstFileGraphs, const std::vector<Graph>& secondFileGraphs)
{
    int choice;
    int graphIndex;
    bool validChoice = false;  

    while (!validChoice)
    {
        printSeparator();  
        std::cout << std::left;  

        if (secondFileGraphs.size() == 0)
        {
            graphIndex = getValidInput("Wybierz numer grafu z pierwszego pliku (0 aby anulowac): ");
            if (graphIndex >= 1 && graphIndex <= firstFileGraphs.size())
            {
                validChoice = true;
                return firstFileGraphs[graphIndex - 1];
            }
            else
            {
                std::cout << "Anulowanie wyboru grafu.\n";
                return Graph(0);
            }
            continue;
        }

        std::cout << std::setw(30) << "Wybierz kolekcje grafow:" << std::endl;
        std::cout << std::setw(30) << "1. Pierwszy plik (zawiera " << firstFileGraphs.size() << " grafow)" << std::endl;
        std::cout << std::setw(30) << "2. Drugi plik (zawiera " << secondFileGraphs.size() << " grafow)" << std::endl;
        std::cout << std::setw(30) << "0. Anuluj" << std::endl;

        choice = getValidInput("Wybierz opcje: ");

        if (choice == 0)
        {
            std::cout << "Anulowanie wyboru grafu.\n";
            return Graph(0); 
        }

        if (choice == 1)
        {
            graphIndex = getValidInput("Wybierz numer grafu z pierwszego pliku: ");
            if (graphIndex >= 1 && graphIndex <= firstFileGraphs.size())
            {
                validChoice = true;
                return firstFileGraphs[graphIndex - 1];
            }
            else
            {
                std::cout << "Niepoprawny numer grafu. Sprobuj ponownie.\n";
            }
        }
        else if (choice == 2)
        {
            graphIndex = getValidInput("Wybierz numer grafu z drugiego pliku: ");
            if (graphIndex >= 1 && graphIndex <= secondFileGraphs.size())
            {
                validChoice = true;
                return secondFileGraphs[graphIndex - 1];
            }
            else
            {
                std::cout << "Niepoprawny numer grafu. Sprobuj ponownie.\n";
            }
        }
        else
        {
            std::cout << "Niepoprawny wybor. Sprobuj ponownie.\n";
        }
    }
}