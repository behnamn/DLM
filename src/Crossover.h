/*
 *
 *	Crossover.h
 * 	Author: Behnam
 *
 */

#ifndef CROSSOVER_H_
#define CROSSOVER_H_

#include "Headers.h"
#include "Common.h"

class Crossover {
public:
	int id;
	pair<int,int> nucs;
	pair<int,int> vertices;
	pair<Domain*,Domain*> domains;
	Staple* staple;
	pair<Edge_desc,bool> edge;
	
	char type;  //i: inside, o: outside, m: seam, l: long
	bool is_53; //On staple (not scaffold)
	pair<int,int> helices;
};



#endif
