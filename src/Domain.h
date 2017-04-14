/*
 *
 *	Domain.h
 * 	Author: Behnam
 *
 */

#ifndef DOMAIN_H_
#define DOMAIN_H_

#include "Graph.h"

class Crossover;
class Staple;

class Domain {
public:
	Domain(){}
	int id; //use vertices.first instead
	pair<int,int> nucs;
	pair<int,int> vertices;
	vector<Domain*> cross_domains; //no need for this
	vector<Crossover*> crossovers;
	vector<Domain*> stack_domains;
	Staple* staple; //the index of the staple.
	bool is_middle;
	int s_index; //the index in the vector of domains of the staple.
	bool is_seam;
	int helix;
	bool is_edge;
	
	int length;
	string seq;
	
	Edge_desc edge; //pair<Edge_desc, bool> edgePair = edge(u, v, g);
};

#endif
