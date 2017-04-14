/*
 *
 *	Strand.h
 * 	Author: Behnam
 *
 */

#ifndef STRAND_H_
#define STRAND_H_

#include "Crossover.h"

class Strand {
public:
	int length;
	int n_domains; 
	
	string seq;  
	string reverse_comp; 
	
	void set_seq(string&);
	void set_length();
	void set_reverse_comp();
	void print_seq();
};


#endif
