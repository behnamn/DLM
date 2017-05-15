/*
 *
 *	Simulation.h
 * 	Author: Behnam
 *
 */

#ifndef SIMULATION_H_
#define SIMULATION_H_

#include "TransitionManager.h"
#include "Statistics.h"


class Simulation{
public:
    Simulation(Constants*, Design*, MyGraph*, TempRamp*, Inputs*, TransitionManager*, Statistics*);
    ~Simulation(){}

    Constants* constants;
    Design* design;
    MyGraph* G;
    TempRamp* ramp;
    Inputs* inputs;
    TransitionManager* trManager;
    Statistics* statistics;

    void run();
};

#endif

