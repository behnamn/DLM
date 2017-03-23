/*
 *
 *	Design.cpp
 * 	Author: Behnam
 *
 */

#include "Design.h"

//Design Methods
Design::Design(){}
Design::Design(Inputs* inputs_){
	this->inputs = inputs;
	add_scaffold();
	add_staples();
}


Design::add_scaffold(){
	string line;
	ifstream myfile (inputs->scaffold_file_name);
	if (myfile.is_open()) {
		getline (myfile,line);
		myfile.close();
	}
	else {printf ("Error:\t Could not read Scaffold file\n"); exit (EXIT_FAILURE);}
	this->scaffold = new Scaffold(line, inputs->domain_file_name); 
}
Design::add_staples(){
	string line;
	ifstream myfile (inputs->staple_file_name);
	if (myfile.is_open()) {
		while(getline(myfile, line)) {
			staple = new Staple(line);
			this->staples.push_back(staple);
		}
		myfile.close();
	}
	else {printf ("Error:\t Could not read Staples file\n"); exit (EXIT_FAILURE);}
}













