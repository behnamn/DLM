/*
 *
 *	Transition.h
 * 	Author: Behnam
 *
 */

#ifndef TRANSITION_H_
#define TRANSITION_H_

#include "Headers.h"
#include "Common.h"
#include "Staple.h"
#include "MyGraph.h"

void reduce_state(vector<int>&);
vector< pair<int,int> > get_changes(vector<int>, int );

class MyMaps {
public:
	MyMaps();

	std::map< 	vector<int>,
				vector<int> >
				state_map;
				/*
		 		* maps to reduced states.
		 		*/
	std::map<	pair< vector<int>,int >,
				vector <pair<int,int> > >
				transition_map;
				/*
				 * Maps from:
				 * - a reduced state (vector<int>).
				 * - position of the domain (int).
				 * To:
				 * - possible final states:
				 *   - first: changed to (int).
				 *   - position of cross_domain (-1 = none).
				 */

	void fill_state_map();
	void fill_transition_map();
};


class Transition {
public:
	Transition();
	Transition(ST , DOM, int, int, MyMaps*);
	void initialise(int, int);

	MyMaps* maps;
	ST staple;
	DOM domain;
	
	vector<int> final_state;
	pair<CR, bool> crossover;
	bool bind; 		//1: bind, 0: unbind

	double rate;
	
	void apply(MyGraph*);
};


#endif 
