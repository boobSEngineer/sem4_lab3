#include "gtest/gtest.h"
#include "../array.h"
#include "../dijkstra.h"


TEST(Graph, Pathfinding) {
    Graph graph;
    Graph::Vertex* vertex1 = graph.get_or_add_vertex("city1");
    Graph::Vertex* vertex2 = graph.get_or_add_vertex("city2");
    Graph::Vertex* vertex3 = graph.get_or_add_vertex("city3");
    Graph::Vertex* vertex4 = graph.get_or_add_vertex("city4");
    vertex1->connect(*vertex2, 10);
    vertex1->connect(*vertex3, 1);
    vertex3->connect(*vertex2, 2);
    vertex2->connect(*vertex4, 20);

    Array<Graph::Vertex*> path = DijkstraAlgorithm::find_path(graph, *vertex1, *vertex4);
    std::cout << "test path: ";
    for (int i = 0; i < path.length(); i++) {
        std::cout << " " << path[i]->city;
    }
    std::cout << "\n";
    ASSERT_EQ(path.length(), 4);
    ASSERT_EQ(path[0], vertex1);
    ASSERT_EQ(path[1], vertex3);
    ASSERT_EQ(path[2], vertex2);
    ASSERT_EQ(path[3], vertex4);

    path = DijkstraAlgorithm::find_path(graph, *vertex4, *vertex1);
    ASSERT_EQ(path.length(), 0);
}

TEST(Graph, BuildSimpleGraph) {
    Graph graph;
    Graph::Vertex* vertex1 = graph.get_or_add_vertex("city1");
    Graph::Vertex* vertex2 = graph.get_or_add_vertex("city2");
    Graph::Vertex* vertex3 = graph.get_or_add_vertex("city3");

    ASSERT_EQ(vertex2, graph.get_or_add_vertex("city2")); // duplicate
    ASSERT_EQ(graph.vertices.get_length(), 3);
}

// array tests
TEST(Array, MassiveAddAndClearTest) {
    Array<std::string> array;
    const int size = 10000;
    for (int i = 0; i < size; i++) {
        array.add("test_string");
    }
    ASSERT_EQ(array.length(), size);
    for (int i = 0; i < size; i++) {
        ASSERT_EQ(array[i], "test_string");
    }
    array.clear();
    ASSERT_EQ(array.length(), 0);
}
