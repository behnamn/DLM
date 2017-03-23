/*
 *
 *	Staple.cpp
 * 	Author: Behnam
 *
 */

#include "Staple.h"

//Staple Methods
Staple::Staple (string string_) {
	read_string(string_);
	set_length();
	set_reverse_comp();
}
void Staple::read_string(string line_){
	vector<std::string> line; //To split the line into position and seq.
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
	//Adding domain sizes.
	vector<string> str_doms;
	for (int i=2; i<line.size(); i++){
		str_doms.push_back(line[i]);
		//str_doms.insert(str_doms.begin(),line[i]);
		//cout << line[i] << "\t";
	}	
	//std::reverse(str_doms.begin(),str_doms.end());
	//cout << endl;
	this->n_domains = str_doms.size();
	for (vector<string>::iterator st = str_doms.begin(); st != str_doms.end(); ++st){
		this->len_domains.push_back(stoi(*st));
	}
}
void Staple::split_seqs(){
	string dom_str;
	int current_nuc = 0;
	for (int d=0; d < this->n_domains; d++){
		dom_str = this->seq.substr(current_nuc,len_domains[d]);
		this->seq_domains.push_back(dom_str);
		current_nuc += this->len_domains[d];
	}
	current_nuc = 0;
	int d;
	for (int d2=0; d2 < this->n_domains; d2++){
		d = this->n_domains - d2 - 1;
		dom_str = this->reverse_comp.substr(current_nuc,len_domains[d]);
		this->rev_seq_domains.push_back(dom_str);
		current_nuc += this->len_domains[d];
	}
}
void Staple::print_staple(){
	cout << n_domains << " ";
	cout << this->length << "\t";
   	cout << start_helix << " " << start_nuc << "\t";
   	cout << end_helix << " " << end_nuc << "\t"; 
	cout << this->seq << "\t";
	cout << reverse_comp << "\t";
	cout << "Domains:\t";
	for (int d = 0; d < this->domains.size(); d++){
		//cout << "(" << domain_indices[d] << ") ";
		//cout << "(" << vertices[d].first << "->" << vertices[d].second << ") ";
		cout << "(" << domains[d].first << "-" <<  domains[d].second << ") ";
		cout << "(" << len_domains[d] << ")\t";
		//cout << "(" << seq_domains[d] << ")\t";
	}
	cout << "Crossovers:\t";
	for (int c = 0; c < this->crossovers.size(); c++){
		cout << crossovers[c].first << "->" <<  crossovers[c].second << " ";
		//cout << cross_indices[c].first << "->" <<  cross_indices[c].second << " ";
		//cout << "(" << len_crossovers[c] << ")\t";
	}
	cout << endl;
}

