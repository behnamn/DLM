/*
 *
 *	Design.h
 * 	Author: Behnam
 *
 */

#ifndef DESIGN_H_
#define DESIGN_H_

#include "Headers.h"
#include "Common.h"
#include "Staple.h"
#include "Scaffold.h"
#include "Input.h"







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




#endif
