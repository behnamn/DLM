/*
 *
 *	New.h
 * 	Author: Behnam
 *
 */

#ifndef NEW_H_
#define NEW_H_

#include "Headers.h"
#include "Common.h"
#include "Input.h"

class Domain {
public:
	int id; //use vertices.fitst instead
	pair<int,int> nucs;
	pair<int,int> vertices;
	vector<Domain*> cross_domains; //no need for this
	vector<Crossover*> crossovers;
	vector<Domain*> stack_domains;
	Staple* staple; //the index of the staple.
	Edge_desc edge; //pair<Edge_desc, bool> edgePair = edge(u, v, g);
	
	int length;
	string seq;
	
	bool is_seam;
	bool is_edge;
	bool is_middle;
	int s_index; //the index in the vector of domains of the staple.
	int helix;
};

class Crossover {
public:
	int id;
	pair<int,int> nucs;
	pair<int,int> vertices;
	pair<Domain*,Domain*> domains;
	Staple* staple;
	pair<Edge_desc,bool> edge;
	
	char type;  //i: inside, o: outside, m: seam, l: long
	bool is_53; //On staple (not scaffold)
	pair<int,int> helices;
};

class Strand {
public:
	int id;
	string seq;  // 5'->3'
	string reverse_comp; // 3'->5' C<->G A<->T
	int length;
	int n_domains; //Not set for scaffold yet.
	void set_seq(string);
	void set_length();
	void set_reverse_comp();
	void print_seq();
};

class Scaffold: public Strand {
public:
	Scaffold();
	Scaffold(string, string);
	void read_string(string);
	int first_nuc;
	vector<Domain*> domains;
	void read_domains(string);
};

class Staple: public Strand {
public:
	Staple(string);
	pair<int,int> nucs;
	pair<int,int> helices;
	bool is_seam;
	bool is_edge;
	void read_string(string);
	void print_staple();
	void split_seqs();
	vector<Domain*> domains;
	vector<Crossover*> crossovers;
};

class Design {
public:
	Design();
	Design(Inputs*);
	Inputs* inputs;
	
	Scaffold scaffold;
	vector<Staple*> staples;
	int n_staples;
	int n_domains; //AKA n_vertices
	
	void read_files();
	void print_staples();
	void match(Staple&);
	void fill_staple_domains();
	void fill_domain_indices();
	void fill_seams();
	void fill_crossovers();
	void fill_lengths();
	void fill_edges();
	void fill_helices();
	void REVERESE_LEN_DOMAINS();
	
	int circ_p(size_t,int);
	vector<int> M; //To track already matched bases.
	bool is_not_already_found(pair<int,int>);

	void fill_crossover_ids();
	void print_domains();
	void print_crossovers();

	vector<int> domain_to_crossovers(int);
	vector<int> vertex_to_crossovers(int);
	int vpair_to_crossover( pair<int,int> );
	int dpair_to_crossover( pair<int,int> );
	bool check_single_domain_staple(int);
	bool check_double_domain_staple(int);
	bool check_triple_domain_staple(int);

	void get_n_domains();
	void fill_domains();
	void fill_crossovers();
	void renumber();
	void fill_cross_domains();
	void fill_stack_domains();
	void add_long_crossovers();
	void add_ids_for_crossovers();
};

class Origami {
public:
	Origami();
	Origami(Design*);
	Design* design;
	MyGraph* G; //Make full if design->input says melt. Otherwise empty.

	//Manage both design and graph here. Include this in Simulation
	
};



#endif
