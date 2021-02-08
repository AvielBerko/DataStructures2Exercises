#include "directed_graph.h"

#include <queue>

DirectedGraph::DirectedGraph() { }

DirectedGraph::~DirectedGraph() {
    // Frees all the vertecies.
    for (std::map<std::string, Vertex*>::iterator it = m_vertecies.begin();
        it != m_vertecies.end(); ++it)
    {
        delete it->second;
    }
}

bool DirectedGraph::add_vertex(const std::string& key) {
    std::map <std::string, Vertex*>::iterator it = m_find_vertex(key);
    if (it == m_vertecies.end()) {
        m_vertecies[key] = new Vertex{ key };
        return true;
    }
    return false;
}

bool DirectedGraph::delete_vertex(const std::string& key) {
    std::map<std::string, Vertex*>::iterator it = m_find_vertex(key);
    if (it == m_vertecies.end()) return false;

    // Deletes all the edges directed to the deleted vertex.
    std::vector<AdjacentVertex> adjacents_to = m_find_adjacents_to(*(it->second));
    for (std::vector<AdjacentVertex>::iterator adj_it = adjacents_to.begin();
        adj_it != adjacents_to.end(); ++adj_it)
    {
        adj_it->vertex->edges.remove(*adj_it->edge);
    }

    delete it->second;
    m_vertecies.erase(it);

    return true;
}

bool DirectedGraph::add_edge(const std::string& source_key, const std::string& dest_key) {
    std::map<std::string, Vertex*>::iterator src_it = m_find_vertex(source_key);
    if (src_it == m_vertecies.end()) return false;

    std::map<std::string, Vertex*>::iterator dest_it = m_find_vertex(dest_key);
    if (dest_it == m_vertecies.end()) return false;

    // Checks whether the edge exists.
    Edge edge = { src_it->second, dest_it->second };
    for (std::list<Edge>::iterator it = src_it->second->edges.begin();
        it != src_it->second->edges.end(); ++it)
    {
        if (*it == edge) return false;
    }

    src_it->second->edges.push_back(edge);
    return true;
}

bool DirectedGraph::delete_edge(const std::string& source_key, const std::string& dest_key) {
    std::map<std::string, Vertex*>::iterator src_it = m_find_vertex(source_key);
    if (src_it == m_vertecies.end()) return false;

    std::map<std::string, Vertex*>::iterator dest_it = m_find_vertex(dest_key);
    if (dest_it == m_vertecies.end()) return false;

    // Finds the edge to delete.
    Edge edge = { src_it->second, dest_it->second };
    for (std::list<Edge>::iterator it = src_it->second->edges.begin();
        it != src_it->second->edges.end(); ++it)
    {
        if (*it == edge) {
            src_it->second->edges.erase(it);
            return true;
        }
    }

    return false;
}

bool DirectedGraph::print_adjacents_from(const std::string& key, std::ostream& os) const {
    std::map<std::string, Vertex*>::const_iterator it = m_find_vertex(key);
    if (it == m_vertecies.end()) return false;

    std::vector<AdjacentVertexConst> adjacents_from = m_find_adjacents_from(*(it->second));
    for (std::vector<AdjacentVertexConst>::iterator adj_it = adjacents_from.begin();
        adj_it != adjacents_from.end(); ++adj_it)
    {
        os << adj_it->vertex->key << ' ';
    }

    return true;
}

bool DirectedGraph::print_adjacents_to(const std::string& key, std::ostream& os) const {
    std::map<std::string, Vertex*>::const_iterator it = m_find_vertex(key);
    if (it == m_vertecies.end()) return false;

    std::vector<AdjacentVertexConst> adjacents_to = m_find_adjacents_to(*(it->second));
    for (std::vector<AdjacentVertexConst>::iterator adj_it = adjacents_to.begin();
        adj_it != adjacents_to.end(); ++adj_it)
    {
        os << adj_it->vertex->key << ' ';
    }

    return true;
}

bool DirectedGraph::print_connected(const std::string& key, std::ostream& os) const {
    std::map<std::string, Vertex*>::const_iterator it = m_find_vertex(key);
    if (it == m_vertecies.end()) return false;

    std::vector<const Vertex*> connected_from = m_find_connected_from(*(it->second));
    for (std::vector<const Vertex*>::iterator conn_it = connected_from.begin();
        conn_it != connected_from.end(); ++conn_it)
    {
        os << (*conn_it)->key << ' ';
    }

    return true;
}

void DirectedGraph::print(std::ostream& os) const {
    for (std::map<std::string, Vertex*>::const_iterator it = m_vertecies.begin();
        it != m_vertecies.end(); ++it)
    {
        os << it->second->key << ':';

        // Prints the edges of the vertex.
        for (std::list<Edge>::const_iterator edge_it = it->second->edges.begin();
            edge_it != it->second->edges.end(); ++edge_it)
        {
            os << ' ' << edge_it->destination->key;
        }

        os << std::endl;
    }
}

std::map<std::string, Vertex*>::iterator DirectedGraph::m_find_vertex(const std::string& key) {
    for (std::map<std::string, Vertex*>::iterator it = m_vertecies.begin();
        it != m_vertecies.end(); ++it)
    {
        if (it->second->key == key) return it;
    }

    return m_vertecies.end();
}

std::map<std::string, Vertex*>::const_iterator DirectedGraph::m_find_vertex(const std::string& key) const {
    for (std::map<std::string, Vertex*>::const_iterator it = m_vertecies.begin();
        it != m_vertecies.end(); ++it)
    {
        if (it->second->key == key) return it;
    }

    return m_vertecies.end();
}

std::vector<AdjacentVertex> DirectedGraph::m_find_adjacents_from(Vertex& vertex) {
    std::vector<AdjacentVertex> result;
    for (std::list<Edge>::iterator it = vertex.edges.begin();
        it != vertex.edges.end(); ++it)
    {
        result.push_back({ it->destination, &*it });
    }

    return result;
}

std::vector<AdjacentVertexConst> DirectedGraph::m_find_adjacents_from(const Vertex& vertex) const {
    std::vector<AdjacentVertexConst> result;
    for (std::list<Edge>::const_iterator it = vertex.edges.begin();
        it != vertex.edges.end(); ++it)
    {
        result.push_back({ it->destination, &*it });
    }

    return result;
}

std::vector<AdjacentVertex> DirectedGraph::m_find_adjacents_to(Vertex& vertex) {
    std::vector<AdjacentVertex> result;

    // For each vertex, searches if has an edge connected to the given vertex.
    for (std::map<std::string, Vertex*>::iterator it = m_vertecies.begin();
        it != m_vertecies.end(); ++it)
    {
        for (std::list<Edge>::iterator edge_it = it->second->edges.begin();
            edge_it != it->second->edges.end(); ++edge_it)
        {
            if (edge_it->destination == &vertex) {
                result.push_back({ it->second, &*edge_it });
            }
        }
    }

    return result;
}

std::vector<AdjacentVertexConst> DirectedGraph::m_find_adjacents_to(const Vertex& vertex) const {
    std::vector<AdjacentVertexConst> result;

    // For each vertex, searches if has an edge connected to the given vertex.
    for (std::map<std::string, Vertex*>::const_iterator it = m_vertecies.begin();
        it != m_vertecies.end(); ++it)
    {
        for (std::list<Edge>::const_iterator edge_it = it->second->edges.begin();
            edge_it != it->second->edges.end(); ++edge_it)
        {
            if (edge_it->destination == &vertex) {
                result.push_back({ it->second, &*edge_it });
            }
        }
    }

    return result;
}

std::vector<Vertex*> DirectedGraph::m_find_connected_from(Vertex& vertex) {
    // This function using a BFS like algorithm.

    std::map<Vertex*, VertexState> states;
    std::queue<Vertex*> queue;
    std::vector<Vertex*> result;

    queue.push(&vertex);
    while (!queue.empty()) {
        Vertex* current = queue.front();
        queue.pop();

        std::vector<AdjacentVertex> adjacents_from = m_find_adjacents_from(*current);
        for (std::vector<AdjacentVertex>::iterator adj_it = adjacents_from.begin();
            adj_it != adjacents_from.end(); ++adj_it)
        {
            if (states[adj_it->vertex] == WHITE) {
                states.insert({ adj_it->vertex, GRAY });
                queue.push(adj_it->vertex);
                result.push_back(adj_it->vertex);
            }
        }

        states[current] = BLACK;
    }

    return result;
}

std::vector<const Vertex*> DirectedGraph::m_find_connected_from(const Vertex& vertex) const {
    // This function using a BFS like algorithm.

    std::map<const Vertex*, VertexState> states;
    std::queue<const Vertex*> queue;
    std::vector<const Vertex*> result(1, &vertex);

    queue.push(&vertex);
    while (!queue.empty()) {
        const Vertex* current = queue.front();
        queue.pop();

        std::vector<AdjacentVertexConst> adjacents_from = m_find_adjacents_from(*current);
        for (std::vector<AdjacentVertexConst>::iterator adj_it = adjacents_from.begin();
            adj_it != adjacents_from.end(); ++adj_it)
        {
            if (states[adj_it->vertex] == WHITE) {
                states[adj_it->vertex] = GRAY;
                queue.push(adj_it->vertex);
                result.push_back(adj_it->vertex);
            }
        }

        states[current] = BLACK;
    }

    return result;
}

std::ostream& operator<<(std::ostream& os, const DirectedGraph& graph) {
    graph.print(os);
    return os;
}
