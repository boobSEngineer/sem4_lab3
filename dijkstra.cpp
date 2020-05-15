#include "dijkstra.h"
#include "graph.h"

namespace DijkstraAlgorithm {
    Array<Graph::Vertex*> find_path(Graph& graph, Graph::Vertex& start, Graph::Vertex& end) {
        // prepare algorithm
        for (auto it = graph.vertices.begin(); it != graph.vertices.end(); it++) {
            (*it).dijkstra_weight = -1;
            (*it).dijkstra_path.clear();
        }

        start.dijkstra_path.add(&start);
        start.dijkstra_weight = 0;

        List<Graph::Vertex*> non_infinite_vertices;
        non_infinite_vertices.add(&start);

        while (non_infinite_vertices.get_length() > 0) {
            auto min_vertex_it = non_infinite_vertices.end();
            for (auto it = non_infinite_vertices.begin(); it != non_infinite_vertices.end(); it++) {
                if (min_vertex_it == non_infinite_vertices.end() || (*it)->dijkstra_weight < (*min_vertex_it)->dijkstra_weight) {
                    min_vertex_it = it;
                }
            }

            if (min_vertex_it != non_infinite_vertices.end()) {
                Graph::Vertex* min_vertex = *min_vertex_it;
                for (auto it = min_vertex->adjacent.begin(); it != min_vertex->adjacent.end(); it++) {
                    Graph::Edge& edge = *it;
                    if (edge.vertex->dijkstra_weight < 0 || edge.vertex->dijkstra_weight > min_vertex->dijkstra_weight + edge.weight) {
                        edge.vertex->dijkstra_weight = min_vertex->dijkstra_weight + edge.weight;
                        edge.vertex->dijkstra_path = min_vertex->dijkstra_path;
                        edge.vertex->dijkstra_path.add(edge.vertex);
                        non_infinite_vertices.add(edge.vertex);
                    }
                }
                non_infinite_vertices.erase(min_vertex_it);
            }

        }

        return end.dijkstra_path;
    }
};
