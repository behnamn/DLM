#include "Input.h"
#include "Common.h"
#include "Constants.h"
#include "Strand.h"
#include "Design.h"
#include "MyGraph.h"
#include "TempRamp.h"
#include "Simulation.h"

int main(int argc, char * argv[]) {
	Inputs *inputs = new Inputs(argc,argv);
	Origami origami = Origami(inputs);
	//origami.print_staples();
	//cout << "End Staple: " << origami.end_staple << endl;
	//cout << "Scaffold Length: " << origami.scaffold.length << endl;
	
	Tile tile(origami);
	//cout << "tile.n_domains: " << tile.n_domains << endl;
	//tile.print_domains();
	//tile.print_crossovers();

	//Frits frits;
	//cout << "frits.n_domains: " << frits.n_domains << endl;
	//frits.print_domains();
	//frits.print_crossovers();

	Constants *constants = new Constants(inputs->gamma,inputs->n_param,inputs->concentration);
	
	//anneal->print_ramp();
	//melt->print_ramp();
	
	MyGraph *G = new MyGraph(tile);	
	MyGraph *G_full = new MyGraph(tile);
	for (int i=0; i<tile.n_domains; i++){G_full->make_transition(i,true);}
	G_full->reset_all_states();
	
	if (inputs->anneal){
		Anneal *anneal = new Anneal(inputs);
		Local local_a = Local(constants, G, anneal, inputs);
		//local_a.run();
	}
	else if (inputs->melt){
		Melt *melt = new Melt(inputs);
		Local local_m = Local(constants, G_full, melt, inputs);
		//local_m.run();
	}
	else{
		printf ("Error! Anneal_Melt not specified!\n"); exit (EXIT_FAILURE);
	}

	delete inputs;
	delete constants;
	delete G;
	//delete anneal;
	//delete melt;

	return 0;
}

