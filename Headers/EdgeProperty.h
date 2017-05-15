/*
 *
 *	EdgeProperty.h
 * 	Author: Behnam
 *
 */

#ifndef EDGEPROPERTY_H_
#define EDGEPROPERTY_H_

class Crossover;
class Domain;

struct EdgeProperty{
	int id;
	pair<vector<Domain>::iterator,
		bool> domain;
	pair<
		vector<Crossover>::iterator, 
		bool> crossover;
	double weight;

	//For drawing
	char type; 	
		/*
		 * s: single-stranded
		 * d: double-stranded
		 * i: inside-crossover
		 * o: outside-crossover 
		 * m: seam-crossover
		 * l: long-crossover
		 */
	string colour; //for drawing.
	string thickness; //for drawing.
	int length; //for drawing.
};

#endif
