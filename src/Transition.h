/*
 *
 *	Transition.h
 * 	Author: Behnam
 *
 */

#ifndef TRANSITION_H_
#define TRANSITION_H_

#include "Common.h"
#include "Staple.h"
#include "MyGraph.h"

void reduce_state(vector<int>&);

class Transition {
public:
    Transition();
    Transition(ST , const DOM, const int, bool);
    virtual ~Transition(){}
    
    ST staple;
    DOM domain;
    
    int target;
    bool cross;
    bool possible;
    bool bind; 		//1: bind, 0: unbind
    pair<CR, bool> crossover;
    
    double rate;
    
    void decide(const vector<int> &, const int);
    void apply(MyGraph*);
};

/*
class Transition {
public:
	Transition();
	Transition(const ST , const DOM, int, int, MyMaps*);
	virtual ~Transition(){}

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
*/


#endif 
