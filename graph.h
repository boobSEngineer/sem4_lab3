#include <string.h>
#include <fstream>
#include "array.h"
#include "list.h"

#ifndef SEM4LAB3_GRAPH_H
#define SEM4LAB3_GRAPH_H

class Graph {
public:
    class Vertex;

    struct Edge {
    public:
        Vertex* vertex = nullptr;
        double weight = 0;

        Edge();
        Edge(Vertex& vertex, double weight);
    };

    class Vertex {
    public:
        Graph* graph = nullptr;
        std::string city = "";
        List<Edge> adjacent;

        double dijkstra_weight;
        Array<Vertex*> dijkstra_path;

        Vertex();;
        Vertex(Graph* graph, std::string const& city);;
        List<Edge>::Iterator find_edge(Vertex& vertex);
        Edge* get_edge(Vertex& vertex);
        void connect(Vertex& vertex, double weight);
        void disconnect(Vertex& vertex);
    };


    List<Vertex> vertices;

    Graph();
    void clear();

    List<Vertex>::Iterator find_vertex(std::string const& city);
    Vertex* get_vertex(std::string const& city);
    Vertex* get_or_add_vertex(std::string const& city);
    bool fromFile(std::string filename);
    void print();
};


#endif //SEM4LAB3_GRAPH_H
