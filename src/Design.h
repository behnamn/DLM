/*
 *
 *	Design.h
 * 	Author: Behnam
 *
 */

#ifndef DESIGN_H_
#define DESIGN_H_

#include "Input.h"
#include "Staple.h"
#include "Scaffold.h"


class Design {
public:
	Design();
	Design(Inputs*);
	Inputs* inputs;
	
	Scaffold scaffold;
	vector<Staple> staples;
	vector<Domain> domains;
	vector<Crossover> crossovers;
	vector<vector<int> > helices;
	//StaplePool S; //Containing staples (which contain domians) and (temporary) domains
	//StaplePool U;
	//StaplePool H;
	
	int n_staples;
	int n_domains; //AKA n_vertices
	
	void add_scaffold();
	void add_helices();
	void add_staples();
	void add_domains();
	void add_domains_to_staples();
	void add_crossovers();
	void fill_stack_domains();
	//void add_domains_to_scaffold(); //StaplePool has domains
	
	void print_staples();
	void print_domains();
	void print_crossovers();
	
	vector<int> M; //To track already matched bases.
	/*

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
	*/
};




#endif
