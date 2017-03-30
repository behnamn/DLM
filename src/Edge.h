/*
 *
 *	Edge.h
 * 	Author: Behnam
 *
 */

#ifndef EDGE_H_
#define EDGE_H_

#include "Headers.h"
#include "Domain.h"
#include "Crossover.h"

struct EdgeProperty{
	int id;
	pair<Domain*,bool> domain;
	pair<Crossover*,bool> crossover;
	int length;
	double weight;
	char type; 	
		/*
		 * s: single-stranded
		 * d: double-stranded
		 * i: inside-crossover
		 * o: outside-crossover 
		 * m: seam-crossover
		 * l: long-crossover
		 */
	vector<int> state; //current state.
		/*
		 * 0 1
		 * 00 10 01 11 12
		 * 000 100 110 111 120 112 123
		 * 101 121 ?
		 */
	int pos; //position on the staple.
		//char staple_type;
		/*
		 * H
		 * U
		 * S
		 */
	vector<int> changes; //state[pos] can change to.
	vector<int> pos_cross; 
		/* -1 means no crossover change in 
		 * the transion. Otherwise pos of 
		 * relevent domain in state is given.
		 */
	vector<double> rates; //rate of changes.
	string colour; //for drawing.
	string thickness; //for drawing.
	bool is_53;
	pair<int,bool> is_crossover; //first gives id of crossover in design.crossovers.
};

#endif
