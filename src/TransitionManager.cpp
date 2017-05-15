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

TransitionManager::TransitionManager(Constants *constants_, Design* design_, MyGraph *G_, TempRamp *ramp_, Inputs *inputs_) :
constants(constants_), design(design_), G(G_), ramp(ramp_), inputs(inputs_){
    initialise_transitions();
}

void TransitionManager::initialise_transitions(){
    for (auto st = design->staples.begin(); st!=design->staples.end(); ++st){
        for (auto dom = st->domains.begin(); dom!=st->domains.end(); ++dom){
            for (int i=0; i<st->n_domains+1; i++){
                if (st->n_domains == 1){
                    transitions.push_back(Transition(st, *(dom), i, false));
                }
                else{
                    transitions.push_back(Transition(st, *(dom), i, true));
                    transitions.push_back(Transition(st, *(dom), i, false));
                }
            }
        }
    }
}

void TransitionManager::reset_possibles(TR tr){
    for (auto it = transitions.begin(); it != transitions.end(); ++it){
        if (it->staple->id == tr->staple->id){
            it->decide_possible();
        }
    }
}

void TransitionManager::reset_recalculates(TR tr){
    for (auto it = transitions.begin(); it != transitions.end(); ++it){
        it->recalculate = false;
        if (ramp->T_was_changed){
            it->recalculate = true;
        }
        else{
            tr->recalculate = true; //itself
            for (auto stack = tr->domain->stack_domains.begin(); stack != tr->domain->stack_domains.end(); ++stack){ //DANGER!
                if (it->domain->id == (*stack)->id ){// Stacking
                    it->recalculate = true;
                }
            }
            if (it->staple->id == tr->staple->id){ //Same staple
                it->recalculate = true;
            }
            if (it->bind && it->cross){ //Looping
                it->recalculate = true;
            }
        }
    }
}

//General Simulation Methods
void TransitionManager::set_dG_duplex(TR tr) {
    double terminal = 0;
    double T = ramp->get_T();
    if (tr->domain->seq[0] == 'A' || tr->domain->seq[0] == 'T'){
        terminal += dH_termAT - T*dS_termAT;
    }
    if (tr->domain->seq[tr->domain->length-1] == 'A' || tr->domain->seq[tr->domain->length-1] == 'T'){
        terminal += dH_termAT - T*dS_termAT;
    }
    double dS_salt = (tr->domain->length - 1) * salt_per_phosphate_hack; // using 0.001 * 12.5 and 0.001 * 40.  (Frits)
    tr->dG_duplex = dH_init - T*dS_init + tr->domain->dH - T*tr->domain->dS + terminal - T*dS_salt;
}
void TransitionManager::set_dG_duplex_average(TR tr) {
    double result;
    double T = ramp->get_T();
    double terminal = ( ( dH_termAT - T*dS_termAT ) + ( dH_termCG - T*dS_termCG ) ); // 2 * 1/2
    double dH = (tr->domain->length - 1) * dH_average;
    double dS = (tr->domain->length - 1) * dS_average;
    //double dS_salt = (tr->domain.length-1) * 0.368 * log( 0.5*constants->conc_Tris + 3.3*sqrt(constants->conc_Mg) );
    //double dS_salt = (tr->domain.length-1) * 0.368 * 3.45528339927;  //using 12.5 and 40.
    //double dS_salt = (tr->domain.length - 1) * 0.368 * -0.944; // using 0.001 * 12.5 and 0.001 * 40.  (Frits)
    double dS_salt = (tr->domain->length - 1) * salt_per_phosphate_hack; // using 0.001 * 12.5 and 0.001 * 40.  (Frits)
    //double dS_salt = 0.;
    result = dH_init - T*dS_init + dH - T*dS + terminal - T * dS_salt;
    tr->dG_duplex = result;
}
void TransitionManager::set_dG_stack(TR tr) {
    double dG_average = dH_average - ramp->get_T()*dS_average; //Not sure if this is what he means in paper.
    tr->dG_stack = constants->n_parameter * dG_average;
}

//Local Model Methods
void TransitionManager::set_dG_shape(TR tr) {
    double E;
    E = cs_hack + G->total_weight(tr->crossover.first);
    tr->dG_shape = -(gas_constant * ramp->get_T()) * constants->gamma_parameter * log(constants->C_parameter / E);
}

void TransitionManager::fill_transitions(){
    total_rate = 0;
    double dG;
    double RT = gas_constant * ramp->get_T();
    for (auto tr = transitions.begin(); tr!=transitions.end(); ++tr){
        if(tr->possible){
            if (tr->recalculate){
                tr->rate = 0.;
                dG=0.;
                if (tr->bind){
                    if(tr->crossover.second == true){
                        set_dG_shape(tr);
                        dG += tr->dG_shape;
                        tr->rate = 1000. * k_plus * exp( -dG / RT );
                    }
                    else{
                        tr->rate = k_plus * constants->conc_staple;
                    }
                }
                else{
                    if (inputs->seq_dependence){
                        set_dG_duplex(tr);
                        dG += tr->dG_duplex;
                    }
                    else{
                        set_dG_duplex_average(tr);
                        dG += tr->dG_duplex;
                    }
                    for (auto stack = tr->domain->stack_domains.begin(); stack != tr->domain->stack_domains.end(); ++stack){
                        if( (design->domains[(*stack)->id]).staple->state[(*stack)->s_index] > 0){
                            set_dG_stack(tr);
                            dG += tr->dG_stack;
                        }
                    }
                    tr->rate = 1000. * k_plus * exp( dG / RT );
                }
            }
            total_rate += tr->rate;
        }
    }
}

void TransitionManager::select_transition(Uni& uni){
    r1 = uni(); r2 = uni();
    min = 0.;
    max = 0.;
    for (auto tr = transitions.begin(); tr!=transitions.end(); ++tr){
        if (tr->possible){
            max += tr->rate/total_rate;
            if (r2 >= min && r2 < max){
                next = tr;
                break;
            }
            min = max;
        }
    }
    tau = (1./total_rate)*log(1./r1);
}


