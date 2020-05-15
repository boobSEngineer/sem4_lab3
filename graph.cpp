#include "graph.h"

Graph::Edge::Edge() {}

Graph::Edge::Edge(Graph::Vertex &vertex, double weight) {
    this->vertex = &vertex;
    this->weight = weight;
}

Graph::Vertex::Vertex() {}

Graph::Vertex::Vertex(Graph *graph, std::string const &city) : graph(graph), city(city) {}

List<Graph::Edge>::Iterator Graph::Vertex::find_edge(Graph::Vertex &vertex) {
    for (auto it = adjacent.begin(); it != adjacent.end(); it++) {
        if ((*it).vertex == &vertex) {
            return it;
        }
    }
    return adjacent.end();
}

Graph::Edge *Graph::Vertex::get_edge(Graph::Vertex &vertex) {
    auto it = find_edge(vertex);
    return it != adjacent.end() ? &(*it) : nullptr;
}

void Graph::Vertex::connect(Graph::Vertex &vertex, double weight) {
    Edge* edge = get_edge(vertex);
    if (edge != nullptr) {
        edge->weight = weight;
    } else {
        adjacent.add(Edge(vertex, weight));
    }
}

void Graph::Vertex::disconnect(Graph::Vertex &vertex) {
    auto edge_it = find_edge(vertex);
    if (edge_it != adjacent.end()) {
        adjacent.erase(edge_it);
    }
}


Graph::Graph() {}

void Graph::clear() {
    vertices.clear();
}

List<Graph::Vertex>::Iterator Graph::find_vertex(std::string const &city) {
    for (auto it = vertices.begin(); it != vertices.end(); it++) {
        if ((*it).city == city) {
            return it;
        }
    }
    return vertices.end();
}

Graph::Vertex *Graph::get_vertex(std::string const &city) {
    auto it = find_vertex(city);
    return it != vertices.end() ? &(*it) : nullptr;
}

Graph::Vertex *Graph::get_or_add_vertex(std::string const &city) {
    Vertex* vertex = get_vertex(city);
    if (vertex != nullptr) {
        return vertex;
    } else {
        auto it = vertices.add(Vertex(this, city));
        return &(*it);
    }
}

bool Graph::fromFile(std::string filename) {
    std::ifstream stream(filename);
    if (stream) {
        clear();

        std::string line;
        while (std::getline(stream, line)) {
            Array<std::string> tokens;

            char* token = strtok(line.data(), ";");
            while (token != nullptr) {
                tokens.add(std::string(token));
                token = strtok(nullptr, ";");
            }

            if (tokens.length() == 4) {
                Vertex* vertex1 = get_or_add_vertex(tokens[0]);
                Vertex* vertex2 = get_or_add_vertex(tokens[1]);
                if (tokens[2] != "N/A") {
                    vertex1->connect(*vertex2, std::strtod(tokens[2].data(), nullptr));
                }
                if (tokens[3] != "N/A") {
                    vertex2->connect(*vertex1, std::strtod(tokens[3].data(), nullptr));
                }
            } else if (!line.empty()) {
                std::cout << "error in reading file, line skipped: " << line << "\n";
            }
        }
        return true;
    } else {
        return false;
    }
}

void Graph::print() {
    for (auto i = vertices.begin(); i != vertices.end(); i++) {
        Vertex& vertex = *i;
        std::cout << "flights from " << vertex.city << ": ";
        for (auto j = vertex.adjacent.begin(); j != vertex.adjacent.end(); j++) {
            std::cout << (*j).vertex->city << " = " << (*j).weight << ", ";
        }
        std::cout << "\n";
    }
}
