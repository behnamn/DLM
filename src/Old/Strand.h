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
#include "Input.h"
		
//bool is_not_already_found(pair<int,int>, vector<int>);

int circ_dist(int, int, int);

class Strand {
	public:
		string seq;  // 5'->3'
		string reverse_comp; // 3'->5' C<->G A<->T
		int length;
		int n_domains; //Not set for scaffold yet.
		void set_seq(string);
		void set_length();
		void set_reverse_comp();
		void print_seq();
};

class Scaffold: public Strand {
	public:
		Scaffold();
		Scaffold(string, string);
		void read_string(string);
		vector<int> len_domains;
		vector<string> seq_domains;
		vector< pair<int,int> > domains;
		int first_nuc;
		void read_domains(string);
};

class Staple: public Strand {
	public:
		Staple(string);
		int start_helix;
		int end_helix;
		int start_nuc;
		int end_nuc;
		void read_string(string);
		void print_staple();
		void split_seqs();
		vector<string> seq_domains; //Ordered 5'->3' in vec. CHANGED in REVERESE_LEN_DOMAINS().
		vector<string> rev_seq_domains; //Ordered 3'->5' in vec.
		vector< pair<int,int> > domains; //nuc numbers on scaffold 
		vector<int> domain_indices;	//id of domains
		vector< pair<int,int> > vertices; //id of vertices of domains.
		vector<int> len_domains; //length of domains. Changed to 3'->5' in REVERESE_LEN_DOMAINS().
		bool is_seam;
		bool is_edge;
		//char type;
		//vector<string> domain_seq;
		vector< pair<int,int> > crossovers; //nuc numbers of scaffold
		vector<int> len_crossovers; 
		vector< pair<int,int> > cross_indices; //id (vertex->vertex)
		//vector<bool> is_53;
};

class Origami {
	public:
		Origami();
		Origami(Inputs *);
		Scaffold scaffold;
		vector<Staple> staples;
		Inputs * inputs;
		void read_files();
		void print_staples();
		int end_staple;
		void match(Staple&);
		void fill_staple_domains();
		void fill_scaffold_domains();
		void find_end_staple();
		void fix_end();
		void fill_crossovers();
		void fill_lengths();
		void fill_domain_indices();
		int circ_p(size_t,int);
		void fill_seams();
		void fill_edges();
		vector<int> M; //To track already matched bases.
		bool is_not_already_found(pair<int,int>);
		vector<vector<int> > helices;
		void fill_helices();
		void REVERESE_LEN_DOMAINS();
};
		

#endif
