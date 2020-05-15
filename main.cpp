#include <iostream>
#include "graph.h"
#include "dijkstra.h"


int main() {
    Graph graph;

    bool run = true;
    while (run) {
        std::cout << "\n\n\nGraph:";
        graph.print();
        std::cout << "\n\ncommands: \n1 - find path\n2 - open file\nother - exit\n\ninput command: ";

        int cmd;
        std::cin >> cmd;
        switch (cmd) {
            case 1: {
                std::string city;
                std::cout << "input city #1: ";
                std::cin >> city;
                Graph::Vertex *vertex1 = graph.get_vertex(city);
                if (vertex1 == nullptr) {
                    std::cout << "no such city!";
                    break;
                }
                std::cout << "input city #2: ";
                std::cin >> city;
                Graph::Vertex *vertex2 = graph.get_vertex(city);
                if (vertex2 == nullptr) {
                    std::cout << "no such city!";
                    break;
                }
                auto path = DijkstraAlgorithm::find_path(graph, *vertex1, *vertex2);
                if (path.length() > 0) {
                    double path_weight = vertex2->dijkstra_weight;
                    std::cout << "path cost: " << path_weight << "\n";
                    std::cout << "path: ";
                    for (int i = 0; i < path.length(); i++) {
                        std::cout << " " << path[i]->city;
                    }
                    std::cout << "\n";
                } else {
                    std::cout << "no path exists.\n";
                }
                std::cout << "press enter to continue...";
                std::cin >> city;
                break;
            }
            case 2: {
                std::string filename;
                std::cout << "input file name: ";
                std::cin >> filename;
                if (graph.fromFile(filename)) {
                    std::cout << "success\n";
                } else {
                    std::cout << "failed to read\n";
                }
                break;
            }
            default:
                run = false;
                break;
        }
        std::cout << "\n";
    }

    graph.fromFile("../input.txt");
    graph.print();
//
//    std::cout << "\n\n";
//    auto path = DijkstraAlgorithm::find_path(g, *g.get_vertex("Moscow"), *g.get_vertex("Vladivostok"));
//    std::cout << "path length: " << path.length() << "\n";
//    for (int i = 0; i < path.length(); i++) {
//        std::cout << " " << path[i]->city;
//    }
    return 0;
}