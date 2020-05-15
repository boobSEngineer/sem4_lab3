#include "graph.h"

#ifndef SEM4LAB3_DIJKSTRA_H
#define SEM4LAB3_DIJKSTRA_H

namespace DijkstraAlgorithm {
    Array<Graph::Vertex*> find_path(Graph& graph, Graph::Vertex& start, Graph::Vertex& end);
};

#endif //SEM4LAB3_DIJKSTRA_H
