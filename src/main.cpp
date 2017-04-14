/*
 *
 *	main.cpp
 * 	Author: Behnam
 *
 */

#include "Constants.h"
#include "Design.h"

int main(int argc, char * argv[]) {
	Inputs *inputs = new Inputs(argc,argv);
	Constants *constants = new Constants(inputs->gamma,inputs->n_param,inputs->concentration);
	Design design(inputs);

	design.print_staples();
	design.print_domains();
	design.print_crossovers();
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

