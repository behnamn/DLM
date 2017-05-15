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
    bool bind; 	//1: bind, 0: unbind
    
    bool fully; /*
                 Whether the staple fully binds
                 or unbinds from fully_bound.
                 To keep track of fullys.
                 */
    void check_fully();
    pair<CR, bool> crossover;
    
    bool recalculate;
    double dG_duplex;
    double dG_stack;
    double dG_shape;
    double rate;
    
    void decide_possible();
    void apply(MyGraph*);
    
    void write(ofstream&);
};

typedef vector<Transition>::iterator TR;



#endif
