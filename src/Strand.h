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
	string seq;  // 5'->3'
	string reverse_comp; // 3'->5' C<->G A<->T
	int length;
	int n_domains; //Not set for scaffold yet.
	void set_seq(string);
	void set_length();
	void set_reverse_comp();
	void print_seq();
};


#endif
