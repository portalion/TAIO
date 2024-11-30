#include <iostream>
#include <chrono>
#include "GraphReader.h"
#include "Algorithms.h"

int main()
{
    std::cout << "Hello from main!\n";

    std::ifstream input("data\\test5.txt");
    auto reader = GraphReader(input);

    while (!reader.isEmpty())
    {   
        std::cout << "====================================\n";
        Graph graph = reader.readNextGraph();
        //graph.printGraph(std::cout);
        
        /*  std::cout << "Smallest complement:\n";
        std::vector<std::pair<int, int>> complement = graphComplement(graph);
        for (auto edge : complement)
        {
            std::cout << edge.first << ',' << edge.second << ' ';
        }
        std::cout << '\n';*/

        int startVertex = 0;
        int depth = 1;
        std::cout << counter << ". Smalest complement approximation: " << std::endl;
        
        auto start = std::chrono::high_resolution_clock::now();
        
        std::vector<std::pair<int, int>> complementApprox = ApproximateATSP(graph, startVertex, depth);
        
        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> elapsed = end - start;
        for (auto edge : complementApprox)
        {
            std::cout << edge.first << ',' << edge.second << ' ';
        }
        std::cout << '\n';
        std::cout << elapsed.count() << "s \n";
        std::cout << "====================================\n";

    }

    std::cout << "Goodbye from main\n";
    return 0;
}
