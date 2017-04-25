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
	Staple(const string&);
	virtual ~Staple(){}

	void read_string(const string&);
	int id;
	pair<int,int> nucs; //Should be coloumns (not nucs)
	pair<int,int> helices;
	vector<Domain> temp_domains; //for sizes and seqs
	bool is_seam;
	bool is_edge;
	vector<DOM> domains;
	vector<CR> crossovers;
	
	void print();
	vector<int> state;
	pair<CR,bool> dp2cross(const DOM, const DOM);
};

typedef vector<Staple>::iterator ST;

#endif
