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
	Staple* staple; 
	bool is_middle;
	int s_index; 
	bool is_seam;
	int helix;
	bool is_edge;
	//int* state;
	
	int length;
	string seq;
	double dH;
	double dS;
	
	Edge_desc edge; //pair<Edge_desc, bool> edgePair = edge(u, v, g);
};

#endif
