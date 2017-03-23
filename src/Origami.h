/*
 *
 *	Origami.h
 * 	Author: Behnam
 *
 */

#ifndef ORIGAMI_H_
#define ORIGAMI_H_

#include "Headers.h"
#include "Common.h"
#include "Design.h"
#include "MyGraph.h"

class Origami {
public:
	Origami();
	Origami(Design*);
	Design* design;
	MyGraph* G; //Make full if design->input says melt. Otherwise empty.

	//Manage both design and graph here. Include this in Simulation
	
};


#endif
