/*
 *
 *	TransitionManager.h
 * 	Author: Behnam
 *
 */

#ifndef TRANSITIONMANAGER_H_
#define TRANSITIONMANAGER_H_

#include "Design.h"
#include "MyGraph.h"
#include "TempRamp.h"
#include "Transition.h"

typedef boost::minstd_rand base_generator_type;
typedef variate_generator<base_generator_type&, uniform_real<> > Uni;

class TransitionManager {
public:
    TransitionManager();
    TransitionManager(Constants*, Design*, MyGraph*, TempRamp*, Inputs*);
    virtual ~TransitionManager(){}
    
    Constants* constants;
    Design* design;
    MyGraph* G;
    TempRamp* ramp;
    Inputs* inputs;
    
    vector<Transition> transitions;
    void initialise_transitions();
        
    void reset_possibles(TR);
    void reset_recalculates(TR);
    
    void set_dG_duplex(TR);
    void set_dG_duplex_average(TR);
    void set_dG_stack(TR);
    
    void set_dG_shape(TR);
    
    double r1, r2, min, max;
    double total_rate, tau;
        
    TR next;
    
    void fill_transitions();
    void select_transition(Uni&);
    
};

#endif
