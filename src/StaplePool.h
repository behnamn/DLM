/*
 *
 *	StaplePool.h
 * 	Author: Behnam
 *
 */

#ifndef STAPLE_H_
#define STAPLE_H_

#include "Staple.h"
#include "Crossover.h"

class Staple: public Strand {
public:
	Staple();
	Staple(string&);
	void read_string(string&);
	pair<int,int> nucs;
	pair<int,int> helices;
	vector<Domain> temp_domains; //for sizes and seqs
	
	bool is_seam;
	bool is_edge;
	void print_staple();
	void split_seqs();
	vector<Domain*> domains;
	vector<Crossover*> crossovers;
};


#endif
