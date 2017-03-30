/*
 *
 *	Strand.cpp
 * 	Author: Behnam
 *
 */

#include "Strand.h"

//Strand Methods
void Strand::set_seq(string& seq_){
	seq = seq_;
}
void Strand::set_length(){
	length = seq.length();
}
void Strand::set_reverse_comp(){
	string result;
	for (string::reverse_iterator rit=seq.rbegin(); rit!=seq.rend(); ++rit){
		if ((*rit) == 'G') {result += 'C';}
		else if ((*rit) == 'C') {result += 'G';}
		else if ((*rit) == 'T') {result += 'A';}
		else if ((*rit) == 'A') {result += 'T';}
		else {printf ("Error:\t nucleotide type not recognised (ATCG).\n"); exit (EXIT_FAILURE);}
	}
	reverse_comp = result;
}
void Strand::print_seq(){
	cout << this->seq << endl;
}

