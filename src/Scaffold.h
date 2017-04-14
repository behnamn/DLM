/*
 *
 *	Scaffold.h
 * 	Author: Behnam
 *
 */

#ifndef SCAFFOLD_H_
#define SCAFFOLD_H_

#include "Strand.h"

class Scaffold: public Strand {
public:
	Scaffold();
	Scaffold(string&);
	void read_sequence_file(string&);
	int first_nuc;
	//vector<Domain*> domains;
};

#endif
