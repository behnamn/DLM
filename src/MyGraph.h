/*
 *
 *	MyGraph.h
 * 	Author: Behnam
 *
 */

#ifndef MYGRAPH_H_
#define MYGRAPH_H_

#include "Constants.h"
#include "Graph.h"
#include "Graph.h"
#include "Design.h"

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

class Faces_visitor : public planar_face_traversal_visitor {
public:
	Embedding faces;
	int i = 0;
	void begin_face() { 
		Path f;
		faces.push_back(f);
	}
	void end_face() { 
		i++;
	}
	template <typename Edge> 
	void next_edge(Edge e) 
	{ 
		faces[i].push_back(e);
	}
};

class MyGraph{
public:
	MyGraph (Design*);
	Design* design;
	Graph g;
	Embedding emb;
	Embedding faces;
	void add_vertices();
	void add_domains();
	void reset_vertex_index(); 
	void reset_edge_index(); 
	double total_weight(int, int); 
	void update_embedding(); 

	void bind_domain(Domain*);
	void unbind_domain(Domain*);
	
	void add_crossover(Crossover*);
	void remove_crossover(Crossover*);

	int num_bound_domains;
	int num_bound_nucs;

	void print_edges();
	void write_gv(string);
	void write_gv_circle(string);
	void print_embedding(); 
	//Edge_desc id_to_edge(int);
};


#endif

/*
void MyGraph::update_embedding() {
	emb.resize(num_vertices(g));
	cout << "Testing for planarity: ";
	if (boyer_myrvold_planarity_test(boyer_myrvold_params::graph = g,boyer_myrvold_params::embedding = &emb[0]))
		cout << "input graph is planar." << endl;
	else
		cout << "input graph is not planar." << endl;
}
void MyGraph::print_embedding() {
	face_counter count_visitor;
	planar_face_traversal(g, &emb[0], count_visitor, get(&EdgeProperty::id, g));
	cout << "Traversing faces of planar embedding... the planar embedding of the graph has " << count_visitor.count << " faces." << endl;
	cout << endl << "Vertices on the faces: " << endl;
	vertex_output_visitor v_vis;
	planar_face_traversal(g, &emb[0], v_vis, get(&EdgeProperty::id, g));
	cout << endl << "Edges on the faces: " << endl;
	edge_output_visitor e_vis;
	planar_face_traversal(g, &emb[0], e_vis, get(&EdgeProperty::id, g));
}
void MyGraph::add_affected(int a, int b, vector<int> & affected) {
	typedef double Weight;
	typedef property_map <Graph,vertex_index_t>::type IndexMap;
	typedef iterator_property_map <Vertex_desc*,IndexMap,Vertex_desc,Vertex_desc&> PredecessorMap;
	typedef iterator_property_map <Weight*,IndexMap,Weight,Weight&> DistanceMap;
	vector<Vertex_desc> predecessors(num_vertices(g)); // To store parents
	vector<Weight> distances(num_vertices(g)); // To store distances
	IndexMap indexMap = get(vertex_index, g);
	PredecessorMap predecessorMap(&predecessors[0], indexMap);
	DistanceMap distanceMap(&distances[0], indexMap);
	dijkstra_shortest_paths(g, a, weight_map(get(&EdgeProperty::weight, g)).distance_map(distanceMap).predecessor_map(predecessorMap));
	//typedef vector<Edge_desc> Path;
	Path path;
	Vertex_desc v=b; // We want to start at the destination and work our way back to the source
	for(Vertex_desc u=predecessorMap[v]; u!=v; v=u, u=predecessorMap[v]) {
		pair<Edge_desc, bool> edgePair = edge(u, v, g);
		Edge_desc edge = edgePair.first;
		path.push_back(edge);
	}
	int i;
	for (Path::iterator it = path.begin(); it != path.end(); ++it) {
		i = g[*it].id;
		//cout << (*it) << "\t";
		if (i<design.n_domains){
			affected.push_back(i);
		}
	}
	//cout << endl;
}
void MyGraph::test_transition(int e, bool add) {
	Domain domain = design.domains[e];
	vector<int> possible_crossovers = domain.crossover_ids;
	Edge_desc myedge = id_to_edge(e);
	int e2, v1, v2;
	Edge_desc cross_edge;
	Crossover c;
	for (vector<int>::iterator it = possible_crossovers.begin(); it != possible_crossovers.end(); ++it) {
		c = design.crossovers[*it];
		if ( c.d_a == e ) { e2 = c.d_b; } else { e2 = c.d_a; } 
		cross_edge = id_to_edge(e2);
		if (g[cross_edge].type == 'd') {
			if (g[myedge].type == 'd') {
				if (edge(c.v_a, c.v_b, g).second == true || edge(c.v_b, c.v_a, g).second == true){
					//remove_crossover(*it);
				}
			}
			else if (g[myedge].type == 's') {
				if (add == true){ 
					//add_crossover(*it);
				}
			}
			else {printf ("Error!\n"); exit (EXIT_FAILURE);}
		}
	}
	if (g[myedge].type == 'd') {
		g[myedge].type = 's';
	}
	else if (g[myedge].type == 's') {
		g[myedge].type = 'd';
	}
	else {printf ("Error!\n"); exit (EXIT_FAILURE);}
	set_edge_weights();
}
Path MyGraph::select_face(int d) {
	//selects the shortest loop that the domain is a part of. 
	Edge_desc es = id_to_edge(d);
	Path loop;
	for (Embedding::iterator f = faces.begin(); f != faces.end(); ++f) {
		for (Path::iterator e = (*f).begin(); e != (*f).end(); ++e) {		
			if ( (*e) == es) {
				loop = (*f);
				if ( (*f).size() < loop.size() ) {
					loop = (*f);
				}
			}
		}
	}
	return loop;
}
void MyGraph::get_affected(int d, vector<int> &affected){
	//affected.clear();
	update_embedding();
	update_faces();
	Path new_face = select_face(d);
	int i;
	for (Path::iterator it = new_face.begin(); it != new_face.end(); ++it) {
		i = g[*it].id;
		if (i<design.n_domains){
			affected.push_back(i);
		}
	}
}
*/
