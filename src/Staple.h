/*
 *
 *	Staple.h
 * 	Author: Behnam
 *
 */

#ifndef STAPLE_H_
#define STAPLE_H_

#include "Headers.h"
#include "Common.h"
#include "Domain.h"
#include "Crossover.h"
#include "Strand.h"

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


#endif
