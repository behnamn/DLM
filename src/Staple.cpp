/*
 *
 *	Staple.cpp
 * 	Author: Behnam
 *
 */

#include "Staple.h"

//Staple Methods
Staple::Staple () {}
Staple::Staple (string &string_) {
	read_string(string_);
	set_length();
	set_reverse_comp();
}
void Staple::read_string(string& line_){
	vector<std::string> line; //To split the line into position, seq and domains.
	boost::split(line, line_, boost::is_any_of("\t"));	
	if (line.size()>5) {printf ("Error:\t tab separation of staple line failed... Or more than 3 domains found on staple.\n"); exit (EXIT_FAILURE);}

	//cout << line.size() << endl;

	string str_start_helix;
	string str_end_helix;
	string str_start_nuc;
	string str_end_nuc;

	vector<std::string> position; //To split position into beginning and end.
	boost::split(position, line[0], boost::is_any_of("-"));	
	if (position.size()>2) {printf ("Error:\t - separation of position failed.\n"); exit (EXIT_FAILURE);}
	position[0].pop_back(); position[1].pop_back(); //Removing the ] at the ends.

	vector<std::string> beginning; //To split beginning into helix and nucleotide.
	boost::split(beginning, position[0], boost::is_any_of("["));	
	if (beginning.size()>2) {printf ("Error:\t [ separation of begininning failed.\n"); exit (EXIT_FAILURE);}
	str_start_helix = beginning[0]; str_start_nuc = beginning[1];

	vector<std::string> end; //To split beginning into helix and nucleotide.
	boost::split(end, position[1], boost::is_any_of("["));	
	if (end.size()>2) {printf ("Error:\t [ separation of begininning failed.\n"); exit (EXIT_FAILURE);}
	str_end_helix = end[0]; str_end_nuc = end[1];

	this->helices.first = stoi(str_start_helix);
	this->helices.second = stoi(str_end_helix);
	this->nucs.first = stoi(str_start_nuc);
	this->nucs.second = stoi(str_end_nuc);

	string seq_to_add; //To hold the seq
	for (string::iterator it=line[1].begin(); it!=line[1].end(); ++it){
		if ((*it)!=' ') {seq_to_add += (*it);}
	}
	//Taking out blunt TTTT ends.
	int len = seq_to_add.length();
	if (seq_to_add[0] == 'T' && seq_to_add[len-1] == 'T'){
		if (seq_to_add[1] == 'T' && seq_to_add[len-2] == 'T'){
			if (seq_to_add[2] == 'T' && seq_to_add[len-3] == 'T'){
				if (seq_to_add[3] == 'T' && seq_to_add[len-4] == 'T'){
					seq_to_add.erase(len-4,4);
					seq_to_add.erase(0,4);
				}
			}
		}
	}
	this->set_seq(seq_to_add);
	
	Domain domain;
	//Adding temporary domains sizes.
	vector<string> str_doms;
	for (int i=2; i<line.size(); i++){
		str_doms.push_back(line[i]);
	}	
	this->n_domains = str_doms.size();
	int current_nuc = 0;
	for (vector<string>::iterator st = str_doms.begin(); st != str_doms.end(); ++st){
		domain.length = stoi(*st);
		domain.seq = this->seq.substr(current_nuc,domain.length);
		//Took rev_comp out from original version!
		temp_domains.push_back(domain);
		current_nuc += domain.length;
	}
}
void Staple::print(){
	cout << n_domains << " ";
	cout << this->length << "\t";
   	cout << helices.first << " " << nucs.first << "\t";
   	cout << helices.second << " " << nucs.second << "\t"; 
	cout << this->is_seam << "\t";
	//cout << reverse_comp << "\t";
	cout << "Domains:\t";
	for (vector<Domain*>::iterator dom = domains.begin(); dom != domains.end(); ++dom){
		//cout << "(" << (**dom).id << ") ";
		cout << "(" << (**dom).vertices.first << "->" << (**dom).vertices.second << ") ";
		cout << "(" << (**dom).nucs.first << "->" << (**dom).nucs.second << ") ";
		cout << "(" << (**dom).seq.length() << ")\t";
		//cout << "(" << seq_domains[d] << ")\t";
	}
	cout << "Crossovers:\t";
	for (vector<Crossover*>::iterator cross = crossovers.begin(); cross != crossovers.end(); ++cross){
		//cout << "(" << (**cross).id << ") ";
		cout << "(" << (**cross).vertices.first << "->" << (**cross).vertices.second << ") ";
		cout << "(" << (**cross).nucs.first << "->" << (**cross).nucs.second << ") ";
	}
	cout << endl;
}
pair<Crossover*,bool> Staple::dp2cross(Domain* d1, Domain* d2){
	pair<Crossover*,bool> result;
	result.second = false;
	for (auto c1 = d1->crossovers.begin(); c1!= d1->crossovers.end(); ++c1){
		for (auto c2 = d2->crossovers.begin(); c2!= d2->crossovers.end(); ++c2){
			if((*c1)->id == (*c2)->id){
			//if(c1 == c2){
				result.second = true;
				result.first = *(c1);
				break;
			}
		}
	}
	return result;
}
		

