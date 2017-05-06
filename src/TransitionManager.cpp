//
//  TransitionManager.cpp
//  DLM_XC
//
//  Created by Behnam Najafi on 25/04/2017.
//  Copyright © 2017 Behnam Najafi. All rights reserved.
//


#include "TransitionManager.h"

TransitionManager::TransitionManager(){
}

TransitionManager::TransitionManager(Design * design_) : design(design_) {
    initialise_transitions();
}

void TransitionManager::initialise_transitions(){
    for (auto st = design->staples.begin(); st!=design->staples.end(); ++st){
        for (auto dom = st->domains.begin(); dom!=st->domains.end(); ++dom){
            for (int i=0; i<st->n_domains+1; i++){
                transitions.push_back(Transition(st, *(dom), i, true));
                transitions.push_back(Transition(st, *(dom), i, false));
            }
        }
    }
}

