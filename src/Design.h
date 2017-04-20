/*
 *
 *	Design.h
 * 	Author: Behnam
 *
 */

#ifndef DESIGN_H_
#define DESIGN_H_

#include "Constants.h" //For dH,dS
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
	vector<vector<int> > helices; //nucs on each helix.
	
	int n_staples;
	int n_domains; //AKA n_vertices
	
	void add_scaffold();
	void add_helices();
	void add_staples();
	void add_domains();
	void add_domains_to_staples();
	void add_crossovers();
	void fill_stack_domains();
	void initialise_states(); //Can go to staple file.
	
	void print_staples();
	void print_domains();
	void print_crossovers();
	
	vector<int> M; //To track already matched bases.
	
	pair<bool,Crossover*> dp2cross(Domain*, Domain*);
};




#endif
