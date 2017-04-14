/*
 *
 *	Staple.h
 * 	Author: Behnam
 *
 */

#ifndef STAPLE_H_
#define STAPLE_H_

#include "Strand.h"

class Staple: public Strand {
public:
	Staple();
	Staple(string&);
	void read_string(string&);
	int id;
	pair<int,int> nucs; //Should be coloumns (not nucs)
	pair<int,int> helices;
	vector<Domain> temp_domains; //for sizes and seqs
	bool is_seam;
	vector<Domain*> domains;
	vector<Crossover*> crossovers;
	
	void print();
	
	bool is_edge;
};

/*
class StaplePool {
public:
	StaplePool();
	Staple(string&);

};
*/

#endif
