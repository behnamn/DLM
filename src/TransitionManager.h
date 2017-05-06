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
#include "Transition.h"

class TransitionManager {
public:
    TransitionManager();
    TransitionManager(Design *);
    virtual ~TransitionManager(){}
    
    Design * design;
    
    vector<Transition> transitions;
    void initialise_transitions();
    
};

#endif
