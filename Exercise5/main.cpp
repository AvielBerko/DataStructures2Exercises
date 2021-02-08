// Names: Aviel Berkovich (211981105), Meir Klemfner(211954185)
// Data Structures 2
// Exercise 4
// The main program has no comments beacuse it was copied from the moodle

#include <iostream>
#include <string>

#include "directed_graph.h"

int main() {
    try {
        std::string v1, v2, name;
        DirectedGraph graph;
        int choice;
        std::cout << "choose one of the following:\n";
        std::cout << "1 - add a writer\n";
        std::cout << "2 - delete a writer\n";
        std::cout << "3 - add a follow up (edge)\n";
        std::cout << "4 - delete a follow up (edge)\n";
        std::cout << "5 - print all neighbors (followed)\n";
        std::cout << "6 - print all followers\n";
        std::cout << "7 - print all vertices that can be reached from V\n";
        std::cout << "8 - print all the graph\n";
        std::cout << "10 - exit\n";

        do
        {
            std::cin >> choice;
            switch (choice)
            {
            case 1:
                std::cout << "enter the writer name\n";
                std::cin >> v1;
                graph.add_vertex(v1);
                break;
            case 2:
                std::cout << "enter the writer name\n";
                std::cin >> v1;
                if (graph.delete_vertex(v1))
                    std::cout << "success";
                else
                    std::cout << "ERROR";
                break;
            case 3:
                std::cout << "enter the follower and the writer\n";
                std::cin >> v1 >> v2;
                if (graph.add_edge(v1, v2))
                    std::cout << "success";
                else
                    std::cout << "ERROR";
                break;
            case 4:
                std::cout << "enter the follower and the writer\n";
                std::cin >> v1 >> v2;
                if (graph.delete_edge(v1, v2))
                    std::cout << "success";
                else
                    std::cout << "ERROR";
                break;
            case 5:
                std::cout << "enter the v you want to print its neighbours\n";
                std::cin >> v1;
                if (!graph.print_adjacents_from(v1)) {}
                    //std::cout << "ERROR";
                break;
            case 6:
                std::cout << "enter the v you want to its followers\n";
                std::cin >> v1;
                if (!graph.print_adjacents_to(v1))
                    std::cout << "ERROR";
                break;
            case 7:
                std::cout << "enter writer\n";
                std::cin >> v1;
                if (!graph.print_connected(v1))
                    std::cout << "ERROR";
                break;
            case 8:
                std::cout << "The graph:\n" << graph;
                break;
            case 10: std::cout << "byebye"; break;
            default: std::cout << "ERROR"; break;
            }
            std::cout << std::endl;
        } while (choice != 10);
    }
    catch (const std::string& err)
    {
        std::cout << err << std::endl;
    }
    return 0;
}
