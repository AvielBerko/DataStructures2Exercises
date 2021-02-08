#pragma once

#include <string>
#include <list>
#include <iostream>

class Vertex;

struct Edge {
    Vertex* source;
    Vertex* destination;

    bool operator==(const Edge& other) const {
        return source == other.source &&
            destination == other.destination;
    }
    bool operator!=(const Edge& other) const {
        return operator==(other);
    }
};

struct Vertex {
    std::string key;
    std::list<Edge> edges;
};

struct AdjacentVertex {
    Vertex* vertex;
    Edge* edge;
};

struct AdjacentVertexConst {
    const Vertex* vertex;
    const Edge* edge;
};

enum VertexState { WHITE, GRAY, BLACK };

