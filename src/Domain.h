/*
 *
 *	Domain.h
 * 	Author: Behnam
 *
 */

#ifndef DOMAIN_H_
#define DOMAIN_H_

#include "Headers.h"
#include "Common.h"

class Domain {
public:
	int id; //use vertices.first instead
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

#endif
