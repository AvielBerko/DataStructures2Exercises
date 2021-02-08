#pragma once

#include "graph_components.h"

#include <iostream>
#include <vector>
#include <map>

class DirectedGraph {
public:
    DirectedGraph();
    ~DirectedGraph();

    // Adds a new vertex to the graph with no edges.
    // Returns true if no vertex with the given key is in the graph, else returns false.
    bool add_vertex(const std::string& key);
    // Deletes a vertex from the graph with a given key.
    // Returns true if the vertex exists, else returns false.
    bool delete_vertex(const std::string& key);
    // Adds a new edge between two given vertecies' keys to the graph.
    // Returns true if the vertecies exist, else returns false.
    bool add_edge(const std::string& source_key, const std::string& dest_key);
    // Deletes an edge from the graph with a given keys.
    // Returns true if the vertecies exist, else returns false.
    bool delete_edge(const std::string& source_key, const std::string& dest_key);

    // Prints all the adjacent vertecies directed from the given vertex to them.
    // Returns true if the vertex exists, else returns false
    bool print_adjacents_from(const std::string& key, std::ostream& os = std::cout) const;
    // Prints all the adjacent vertecies directed from them to the given vertex.
    // Returns true if the vertex exists, else returns false
    bool print_adjacents_to(const std::string& key, std::ostream& os = std::cout) const;
    // Prints all the vertecies that are connected to the given vertex with a full path.
    // Returns true if the vertex exists, else returns false
    bool print_connected(const std::string& key, std::ostream& os = std::cout) const;
    // Prints all the vertecies and their edges.
    void print(std::ostream& os = std::cout) const;

private:
    // These functions finds a vertex by its key.
    std::map<std::string, Vertex*>::iterator m_find_vertex(const std::string& key);
    std::map<std::string, Vertex*>::const_iterator m_find_vertex(const std::string& key) const;

    // These functions returns all the adjacent vertecies directed from the vertex to them.
    std::vector<AdjacentVertex> m_find_adjacents_from(Vertex& vertex);
    std::vector<AdjacentVertexConst> m_find_adjacents_from(const Vertex& vertex) const;
    // These functions returns all the adjacent vertecies directed from them to the vertex.
    std::vector<AdjacentVertex> m_find_adjacents_to(Vertex& vertex);
    std::vector<AdjacentVertexConst> m_find_adjacents_to(const Vertex& vertex) const;
    // These functions returns all the connected vertecies to a given vertex with a full path.
    std::vector<Vertex*> m_find_connected_from(Vertex& vertex);
    std::vector<const Vertex*> m_find_connected_from(const Vertex& vertex) const;

private:
    std::map<std::string, Vertex*> m_vertecies;
};

std::ostream& operator<<(std::ostream& os, const DirectedGraph& graph);
