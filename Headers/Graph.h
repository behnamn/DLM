/*
 *
 *	Graph.h
 * 	Author: Behnam
 *
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#include "../Headers/Headers.h"
#include "../Headers/VertexProperty.h"
#include "../Headers/EdgeProperty.h"

typedef adjacency_list<vecS, vecS, undirectedS, VertexProperty, EdgeProperty > Graph;
typedef graph_traits<Graph>::vertex_iterator Vertex_iter;
typedef graph_traits<Graph>::edge_iterator Edge_iter;
typedef graph_traits<Graph>::vertex_descriptor Vertex_desc;
typedef graph_traits<Graph>::edge_descriptor Edge_desc;
typedef vector<Edge_desc> Path;
typedef vector<Path> Embedding; //for embeddings

typedef double Weight;
typedef property_map <Graph,vertex_index_t>::type IndexMap;
typedef iterator_property_map <Weight*,IndexMap,Weight,Weight&> DistanceMap;

struct face_counter : public planar_face_traversal_visitor {
    face_counter() : count(0) {}
    void begin_face() { ++count; }
    int count;
};
struct output_visitor : public planar_face_traversal_visitor {
    void begin_face() { cout << "New face: "; }
    void end_face() { cout << endl; }
};
struct vertex_output_visitor : public output_visitor {
    template <typename Vertex>
    void next_vertex(Vertex v)
    {
        cout << v << " ";
    }
};
struct edge_output_visitor : public output_visitor {
    template <typename Edge>
    void next_edge(Edge e)
    {
        cout << e << " ";
    }
};



#endif
