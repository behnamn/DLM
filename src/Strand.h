/*
 *
 *	Strand.h
 * 	Author: Behnam
 *
 */

#ifndef STRAND_H_
#define STRAND_H_

#include "Headers.h"
#include "Common.h"

class Strand {
public:
	int id;
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
