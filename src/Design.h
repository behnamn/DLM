/*
 *
 *	Design.h
 * 	Author: Behnam
 *
 */

#ifndef DESIGN_H_
#define DESIGN_H_

#include "Headers.h"
#include "Common.h"
#include "Input.h"
#include "Strand.h"

			

class Domain {
	public:
		int source; int target; //Source can be used as id.
		vector<int> cross_domains; //no need for this
		vector<int> crossover_ids;
		vector<int> stack_domains;
		int staple; //the index of the staple.
		int length;
		string seq;
		bool is_seam;
		bool is_edge;
		bool is_middle;
		int s_index; //the index in the vector of domains of the staple.
		int helix;

};
bool Domain_sort(const Domain&, const Domain&);
class Crossover {
	public:
		int id;
		int v_a; int v_b;
		int d_a; int d_b;
		int d_a1; int d_a2; int d_b1; int d_b2; //no need for this
		char type;  //i: inside, o: outside, m: seam, l: long
		int staple;
		bool is_53; //On staple (not scaffold)
		int h_a; int h_b; //helices
};
class Design {
	public:
		int n_vertices;
		int n_domains;
		vector<Domain> domains;
		vector<Crossover> crossovers;
		
		void fill_crossover_ids();
		Design();
		void print_domains();
		void print_crossovers();

		vector<int> domain_to_crossovers(int);
		vector<int> vertex_to_crossovers(int);
		int vpair_to_crossover( pair<int,int> );
		int dpair_to_crossover( pair<int,int> );
		bool check_single_domain_staple(int);
		bool check_double_domain_staple(int);
		bool check_triple_domain_staple(int);

		string scaffold_sequence;
};

class Tile: public Design{
	public:
		//Tile();
		Tile(Origami);
		Origami origami;
		void get_n_domains();
		void fill_domains();
		void fill_crossovers();
		void renumber();
		void fill_cross_domains();
		void fill_stack_domains();
		void add_long_crossovers();
		void add_ids_for_crossovers();
};

class Frits: public Design{
	public:
		Frits();
		void fill_domains();
		void fill_crossovers();
};

class Simple: public Design{
	public:
		Simple();
		void fill_domains();
		void fill_crossovers();
};



#endif

