/*
 *
 *	Common.h
 * 	Author: Behnam
 *
 */

#ifndef COMMON_H_
#define COMMON_H_

#include "Headers.h"

/*
const string Scaffold_file_name = "Scaffold.txt";

const string Staple_file_name = "S_Staples.txt";
const string Domain_file_name = "S_Lengths.txt";

const string Anneal_Melt = "Melt";

const string Short_Long = "Short";

const string HUS(1,Staple_file_name[0]);
*/

void print_matrix(vector< vector<double> >&);
void write_matrix(vector< vector<double> >&);

template <class T> void print_vec(vector<T> &vec){
	for (int i=0; i<vec.size(); i++){
		cout << i << "\t" << vec[i] << "\n";
	}
}
//template <class T> void print_vec(vector<T> &);
void copy_vec(int*, const int*, int);
double sum_elements(vector<double>&);
int sum_elements(vector<int>&);

double kelvin(double);
double centigrade(double);

double seconds(double);
double minutes(double);

double Cpm2spC(double);

int circ_dist(int, int, int);

string reverse_comp(string);

#endif




/*
template <class T> void print_vec(vector<T> &vec);
void print_matrix(vector< vector<double> >& matrix);
void write_matrix(vector< vector<double> >& matrix);
void copy_vec(int *a, const int *b, int b_size);

double sum_elements(vector<double>& v);

double kelvin(double C);
double centigrade(double K);

double seconds(double minutes);
double minutes(double seconds);
double Cpm2spC (double Cpm);
*/






/*
struct face_counter : public planar_face_traversal_visitor {
	face_counter() : count(0) {}
	void begin_face() { ++count; }
	int count;
};
struct output_visitor : public planar_face_traversal_visitor {
	void begin_face() { cout << "New face: "; }
	void end_face() { cout << endl; }
};
struct vertex_output_visitor : public output_visitor {
	template <typename Vertex> 
	void next_vertex(Vertex v) 
	{ 
		cout << v << " "; 
	}
};
struct edge_output_visitor : public output_visitor {
	template <typename Edge> 
	void next_edge(Edge e) 
	{ 
		cout << e << " "; 
	}
};
*/
