/*
 *
 *	MyGraph.h
 * 	Author: Behnam
 *
 */

#ifndef MYGRAPH_H_
#define MYGRAPH_H_

#include "Loop.h"

class MyGraph{
public:
	//MyGraph (Design*);
    MyGraph (Design*, bool full = false);
	virtual ~MyGraph(){}
    
	Design* design;
	Graph g;
	void add_vertices();
	void add_domains();
	void reset_vertex_index(); 
	void reset_edge_index(); 
	double total_weight(const CR); 
    
	void bind_domain(const DOM);
	void unbind_domain(const DOM);
	
	void add_crossover(CR);
	void remove_crossover(CR);
    
    /*
	int num_bound_nucs;
	int num_bound_H;
	int num_bound_U;
	int num_bound_S;
    int num_bound_FH;
    int num_bound_FU;
    int num_bound_FS;
    */
    void complete();
    
	void print_edges();
	void write_gv(const string&);
	void write_gv_circle(const string&);
    void write_gv_rectangleU(const string&);
    void write_gv_rectangleS(const string&);
	//Edge_desc id_to_edge(int);
    
    vector<Weight> distances; // To store distances for djkastra

    Embedding emb; //Saves the edges for each vertex in order.
    FaceManager Faces;
    void update_embedding();
    void update_faces();
    Path select_face(Edge_desc);
    vector<Path> select_all_faces(Edge_desc);
    void print_embedding();
 
    //void get_affected(int, vector<int> &);
};

#endif


