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
Scaffold::Scaffold (string& string_) {
	read_string(&string_);
	set_length();
	set_reverse_comp();
}
void Scaffold::read_string(string& line){
	set_seq(line);
}

