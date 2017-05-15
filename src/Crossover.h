/*
 *
 *	Crossover.h
 * 	Author: Behnam
 *
 */

#ifndef CROSSOVER_H_
#define CROSSOVER_H_

#include "Domain.h"

class Crossover {
public:
	Crossover();
	virtual ~Crossover(){}

	int id;

	pair<DOM,DOM> domains;
	vector<Staple>::iterator staple;
	
	pair<int,int> nucs;
	pair<int,int> vertices;
	bool is_seam;
	bool is_long;
	bool is_53; 
	/*
	 * On staple (not scaffold)
	 * Actually on scaffold (not staple) 
	 * Always 3->5 on staple
	 */
	pair<int,int> helices;
	char type;
	/*
	 * i: inside 
	 * o: outside
	 */
	
	pair<Edge_desc,bool> edge;
};

typedef vector<Crossover>::iterator CR;

#endif
