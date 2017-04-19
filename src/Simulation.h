/*
 *
 *	Simulation.h
 * 	Author: Behnam
 *
 */

#ifndef SIMULATION_H_
#define SIMULATION_H_

#include "Headers.h"
#include "Common.h"
#include "Domain.h"  
#include "Design.h" 
#include "MyGraph.h"
#include "TempRamp.h"
#include "Transition.h"

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

		MyMaps maps;

		double dG_duplex(Domain*);
		double dG_duplex_average(Domain*);
		double dG_stack();

		vector<Transition> transitions;
		double total_rate;
};

class Local: public Simulation{
	public:
		Local(Constants*, Design*, MyGraph*, TempRamp*, Inputs*);
		~Local(){}

		double dG_shape(Crossover*);

		void fill_transitions();
		void run();
};


#endif

