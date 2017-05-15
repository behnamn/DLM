/*
 *
 *	Domain.h
 * 	Author: Behnam
 *
 */

#ifndef DOMAIN_H_
#define DOMAIN_H_

#include "../Headers/Graph.h"

class Crossover;
class Staple;

class Domain {
public:
	Domain();
	virtual ~Domain(){}
		
	int id; //use vertices.first instead
	pair<int,int> nucs;
	pair<int,int> vertices;
	vector<
			vector<Domain>::iterator
			> cross_domains; 
	vector<
			vector<Crossover>::iterator
			> crossovers;
	vector<
			vector<Domain>::iterator
			> stack_domains;
	vector<Staple>::iterator staple; 
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

typedef vector<Domain>::iterator DOM;

#endif
