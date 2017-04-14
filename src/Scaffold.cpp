/*
 *
 *	Scaffold.cpp
 * 	Author: Behnam
 *
 */

#include "Scaffold.h"

//Scaffold Methods
Scaffold::Scaffold () {
}
Scaffold::Scaffold (string& scaffold_file_name) {
	read_sequence_file(scaffold_file_name);
	set_length();
	set_reverse_comp();
}
void Scaffold::read_sequence_file(string& scaffold_file_name){
	string line;
	ifstream myfile (scaffold_file_name);
	if (myfile.is_open()) {
		getline (myfile,line);
		myfile.close();
	}
	else {printf ("Error:\t Could not read Scaffold file\n"); exit (EXIT_FAILURE);}
	set_seq(line);
}

