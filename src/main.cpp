/*
 *
 *	main.cpp
 * 	Author: Behnam
 *
 */

#include "Constants.h"
#include "Design.h"
#include "MyGraph.h"
#include "TempRamp.h"
#include "Transition.h"
#include "Simulation.h"

int main(int argc, char * argv[]) {
	Inputs *inputs = new Inputs(argc,argv);
	Constants *constants = new Constants(inputs->gamma,inputs->n_param,inputs->concentration);
	Design *design = new Design(inputs);
	//design->print_staples();
	//design->print_domains();
	//design->print_crossovers();
	
	MyGraph *G = new MyGraph(design);
	//G->print_edges();

	if (inputs->anneal){
		Anneal *anneal = new Anneal(inputs);
		Local local_a = Local(constants, design, G, anneal, inputs);
		local_a.run();
	}
	else if (inputs->melt){
		//local_m.run();
	}


	/*
	for (vector<Domain>::iterator dom = design.domains.begin(); dom!=design.domains.end(); ++dom){
		cout << dom->nucs.first << endl;
	}
	for (vector<Staple>::iterator st = design.staples.begin(); st!=design.staples.end(); ++st){
		for (vector<Domain*>::iterator dom = st->domains.begin(); dom!=st->domains.end(); ++dom){
			cout << (**dom).nucs.first << endl;
		}
	}
	*/

	delete inputs;
	delete constants;

	return 0;
}

