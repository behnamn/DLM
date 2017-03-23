/*
 *
 *	Scaffold.h
 * 	Author: Behnam
 *
 */

#ifndef SCAFFOLD_H_
#define SCAFFOLD_H_

#include "Headers.h"
#include "Common.h"
#include "Domain.h"
#include "Crossover.h"
#include "Strand.h"

class Scaffold: public Strand {
public:
	Scaffold();
	Scaffold(string, string);
	void read_string(string);
	int first_nuc;
	vector<Domain*> domains;
	void read_domains(string);
};


#endif
