/*
 *
 *	Simulation.h
 * 	Author: Behnam
 *
 */

#ifndef SIMULATION_H_
#define SIMULATION_H_

#include "TempRamp.h"
#include "TransitionManager.h"

class Simulation{
	public:
		//Simulation(Constants *constants_, MyGraph *G_, TempRamp *ramp_);
		Simulation(){}
		~Simulation(){}

		Constants* constants;
		Design* design;
		MyGraph* G;
		TempRamp* ramp;
		Inputs* inputs;
    
        TransitionManager trManager;

		double dG_duplex(DOM);
		double dG_duplex_average(DOM);
		double dG_stack();
    
        double total_rate;

};

class Local: public Simulation{
	public:
		Local(Constants*, Design*, MyGraph*, TempRamp*, Inputs*);
		~Local(){}

		double dG_shape(CR);

		void fill_transitions();
		void run();
};


#endif

