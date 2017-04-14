/*
 *
 *	Graph.h
 * 	Author: Behnam
 *
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#include "Headers.h"
#include "Common.h"
#include "VertexProperty.h"
#include "EdgeProperty.h"

typedef adjacency_list<vecS, vecS, undirectedS, VertexProperty, EdgeProperty > Graph;
typedef graph_traits<Graph>::vertex_iterator Vertex_iter;
typedef graph_traits<Graph>::edge_iterator Edge_iter;
typedef graph_traits<Graph>::vertex_descriptor Vertex_desc;
typedef graph_traits<Graph>::edge_descriptor Edge_desc;
typedef vector<Edge_desc> Path;
typedef vector< Path > Embedding; //for embeddings 

#endif
