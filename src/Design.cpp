/*
 *
 *	Design.cpp
 * 	Author: Behnam
 *
 */

#include "Design.h"

//Constructors
Design::Design(){}
Design::Design(Inputs* inputs_){
	this->inputs = inputs_;
	add_scaffold();
	add_helices();
	add_staples();
	add_domains();
	add_domains_to_staples();
	add_crossovers();
	fill_stack_domains();
	initialise_states();
}

//Initialisers
void Design::add_scaffold(){
	//Just for folding.
	this->scaffold = Scaffold(inputs->scaffold_file_name); 
}
void Design::add_helices(){
	vector<int> helix;
	//add 109 or 110 (not all are equal length)
	int nuc = 101;
	for (int row = 0; row<12; row++){ //from centre top going left.
		helix.clear();
		if (row == 2 || row == 6 || row == 10) {
			for (int i=0; i<111; i++){
				helix.push_back(nuc);
				nuc++;
			}
		}
		else{
			for (int i=0; i<110; i++){
				helix.push_back(nuc);
				nuc++;
			}
		}
		helices.push_back(helix);
	}
	for (int row = 11; row>0; row--){ //from centre bottom up to 2nd helix.
		if (row == 1 || row == 5 || row == 9) {
			for (int i=0; i<111; i++){
				helices[row].push_back(nuc);
				nuc++;
			}
		}
		else{
			for (int i=0; i<110; i++){
				helices[row].push_back(nuc);
				nuc++;
			}
		}
	}
	int row = 0;
	while (nuc < scaffold.length){
		helices[row].push_back(nuc);
		nuc++;
	}
	for (int i=0; i<101; i++){
		helices[row].push_back(i);
	}
}
void Design::add_staples(){
	/*
	 * Adds n_staples to Design
	 * Adds staples with:
	 * 	helices, nucs, id, is_seam, is_edge, temp_domains(sizes & seqs))
	 */
	Staple staple;
	string line;
	ifstream myfile (inputs->staple_file_name);
	if (myfile.is_open()) {
		while(getline(myfile, line)) {
			staple = Staple(line);
			this->staples.push_back(staple);
		}
		myfile.close();
	}
	else {printf ("Error:\t Could not read Staples file\n"); exit (EXIT_FAILURE);}
	
	this->n_staples = staples.size();
	
	for (vector<Staple>::iterator st = staples.begin(); st!=staples.end(); ++st){
		st->id = st - staples.begin();
		st->is_seam = false;
		if (st->helices.first < 12 && st->helices.first > 1){
			if (st->nucs.first < 128 && st->nucs.first >= 95){
				st->is_seam = true;
			}
		}		
		if (st->helices.second < 12 && st->helices.second > 1){
			if (st->nucs.second < 128 && st->nucs.second > 95){
				st->is_seam = true;
			}
		}
		st->is_edge = false;
		if (st->nucs.first < 15 && st->nucs.second < 15){
			st->is_edge = true;
		}
		if (st->nucs.first > 210 && st->nucs.second > 210){
			st->is_edge = true;
		}
	}
}
void Design::add_domains(){ 
	/*
	 * Adds to Design:
	 * 	n_domains, domains
	 * Adds to each domain:
	 * 	domain sizes, ids, nucs, seqs, vertices, helix, dH, dS.
	 */
	string line;
	int i = 0;
	Domain domain;
	ifstream myfile (inputs->domain_file_name);
	if (myfile.is_open()) {
		while(getline(myfile, line)) {
			if (i==0){
				this->scaffold.first_nuc = -1 * stoi(line);
			}
			else{
				domain = Domain();
				domain.id = i-1;
				domain.length = stoi(line);
				this->domains.push_back(domain);
			}
			i++;
		}
		myfile.close();
	}
	else {printf ("Error:\t Could not read Domains file\n"); exit (EXIT_FAILURE);}
	
	this->n_domains = this->domains.size();
	
	int current_nuc = scaffold.first_nuc;
	for (int d=0; d < this->n_domains - 1; d++){
		domains[d].seq = (this->scaffold).seq.substr(current_nuc,domains[d].length);
		domains[d].nucs = make_pair(current_nuc, current_nuc + domains[d].length - 1);
		domains[d].vertices = make_pair(domains[d].id, domains[d].id+1);
		current_nuc += domains[d].length;
	}
	string end_str;
	int remaining = (this->scaffold).length - current_nuc;
	end_str = (this->scaffold).seq.substr(current_nuc,remaining);
	end_str += (this->scaffold).seq.substr(0,scaffold.first_nuc);
	domains[n_domains-1].seq = end_str;
	domains[n_domains-1].nucs = make_pair(current_nuc, (this->scaffold).first_nuc-1);
	domains[n_domains-1].vertices = make_pair(domains[n_domains-1].id, 0);

	int h_first, h_second;
	for (vector<Domain>::iterator dom = domains.begin(); dom!=domains.end(); ++dom){
		for (vector<vector<int> >::iterator helix = helices.begin(); helix!=helices.end(); ++helix){
			if(find(helix->begin(), helix->end(), dom->nucs.first) != helix->end()) { 
				h_first = helix-helices.begin()+1;
			}
			if(find(helix->begin(), helix->end(), dom->nucs.second) != helix->end()) { 
				h_second = helix-helices.begin()+1;
			}
		}
		if (h_first == h_second){dom->helix = h_first;}
		else {cout << "WARNING: domain's vertices are on different helices!\n";}
	}
	double dH, dS;
	for (vector<Domain>::iterator dom = domains.begin(); dom!=domains.end(); ++dom){
		dH = 0.;
		dS = 0.;
		string sub;
		for (int i=0; i<dom->length-1; i++){
			sub.clear();
			sub += dom->seq[i];
			sub += dom->seq[i+1];
			if (sub == "AA" || sub == "TT") { dH+=dH_AA; dS+=dS_AA; }
			else if (sub == "CA" || sub == "TG") { dH+=dH_CA; dS+=dS_CA; }
			else if (sub == "GT" || sub == "AC") { dH+=dH_GT; dS+=dS_GT; }
			else if (sub == "CT" || sub == "AG") { dH+=dH_CT; dS+=dS_CT; }
			else if (sub == "GA" || sub == "TC") { dH+=dH_GA; dS+=dS_GA; }
			else if (sub == "GG" || sub == "CC") { dH+=dH_GG; dS+=dS_GG; }
			else if (sub == "AT") { dH+=dH_AT; dS+=dS_AT; }
			else if (sub == "TA") { dH+=dH_TA; dS+=dS_TA; }
			else if (sub == "CG") { dH+=dH_CG; dS+=dS_CG; }
			else if (sub == "GC") { dH+=dH_GC; dS+=dS_GC; }
			else {
				printf ("Error! dom->seq not in nn database. \n"); 
				exit (EXIT_FAILURE);
			}
		}
		dom->dH = dH;
		dom->dS = dS;
	}

}	
void Design::add_domains_to_staples(){ //Adds pointers. Fills s_index, is_middle, is_seam, is_edge.
	string rev_comp;
	for (vector<Staple>::iterator st=staples.begin(); st!=staples.end(); ++st){
		for (vector<Domain>::reverse_iterator td=st->temp_domains.rbegin(); td!=st->temp_domains.rend(); ++td){
			rev_comp = reverse_comp(td->seq);
			for (vector<Domain>::iterator d=domains.begin(); d!=domains.end(); ++d){
				if(d->seq == rev_comp){
					st->domains.push_back(d);
					if (d->nucs.first < d->nucs.second){
						for (int i = d->nucs.first; i < d->nucs.second+1; i++){M.push_back(i);}
					}
					else {
						for (int i = d->nucs.first; i < scaffold.length; i++){M.push_back(i);}
						for (int i = 0; i < d->nucs.second+1; i++){M.push_back(i);}
					}
				}
			}
		}
		st->temp_domains.clear();
	}
	for (vector<Staple>::iterator st=staples.begin(); st!=staples.end(); ++st){
		for (vector<DOM>::iterator dom=st->domains.begin(); dom!=st->domains.end(); ++dom){
			(*dom)->staple = st;
			(*dom)->s_index = dom - st->domains.begin();
			(*dom)->is_middle = false;
			if (st->domains.size() == 3 && (*dom)->s_index == 1) {(*dom)->is_middle = true;}
			(*dom)->is_seam = false;
			if (st->is_seam){
				if (st->domains.size()==3 && (*dom)->s_index > 0) {(*dom)->is_seam = true;} 
				if (st->domains.size()==2) {(*dom)->is_seam = true;} 
			}
			(*dom)->is_edge = false;
			if (st->is_edge){
				if (st->n_domains > 1){
					if (inputs->staple_file_name == "U_Staples.txt"){(*dom)->is_edge = true;}
					if (inputs->staple_file_name == "S_Staples.txt"){
						if ((*dom)->helix == 1 || (*dom)->helix == 12){(*dom)->is_edge = true;}
						else{
							if ((*dom)->s_index != st->n_domains -1){(*dom)->is_edge = true;} 
						}
					}
				}
			}
		}
	}
}
void Design::add_crossovers(){
	for (vector<Staple>::iterator s = staples.begin(); s != staples.end(); ++s){
		for (int d = 0; d<s->domains.size()-1; d++){
			if ( 	(s->is_seam && s->domains.size() == 2 && d == 0) 
				|| 	(s->is_seam && s->domains.size() == 3 && d == 1) ){
				Crossover crossover;
				crossover.nucs.first = (s->domains[d])->nucs.first;
				crossover.nucs.second = (s->domains[d+1])->nucs.second;
				crossover.vertices.first = (s->domains[d])->vertices.first;
				crossover.vertices.second = (s->domains[d+1])->vertices.second;
				crossover.domains = make_pair(s->domains[d],s->domains[d+1]);
				crossover.staple = s;
				crossover.is_long = false;
				crossover.is_seam = true;
				this->crossovers.push_back(crossover);
			}
			else{
				Crossover crossover;
				crossover.nucs.first = (s->domains[d])->nucs.second;
				crossover.nucs.second = (s->domains[d+1])->nucs.first;
				crossover.vertices.first = (s->domains[d])->vertices.second;
				crossover.vertices.second = (s->domains[d+1])->vertices.first;
				crossover.domains = make_pair(s->domains[d],s->domains[d+1]);
				crossover.staple = s;
				crossover.is_long = false;
				crossover.is_seam = false;
				this->crossovers.push_back(crossover);
			}
		}
	}
	//Adding long crossovers
	DOM dom3;
   	DOM	dom5;
	Crossover crossover;
	for (vector<Staple>::iterator st=staples.begin(); st!=staples.end(); ++st){
		if (st->n_domains == 3){
			dom3 = st->domains[0];
			dom5 = st->domains[2];
			crossover.nucs.first = dom3->nucs.second;
			crossover.nucs.second = dom5->nucs.first;
			crossover.vertices.first = dom3->vertices.second;
			crossover.vertices.second = dom5->vertices.first;
			crossover.domains = make_pair(dom3,dom5);
			crossover.staple = st;
			crossover.is_long = true;
			if (st->is_seam){crossover.is_seam = true;}
			else{crossover.is_seam = false;}
			this->crossovers.push_back(crossover);
		}
	}
	//Adding ids and helices
	for (vector<Crossover>::iterator cross = crossovers.begin(); cross!=crossovers.end(); ++cross){
		cross->id = cross - crossovers.begin();
		for (vector<vector<int> >::iterator helix = helices.begin(); helix!=helices.end(); ++helix){
			if(find(helix->begin(), helix->end(), cross->nucs.first) != helix->end()) { 
				cross->helices.first = helix-helices.begin()+1;
			}
			if(find(helix->begin(), helix->end(), cross->nucs.second) != helix->end()) { 
				cross->helices.second = helix-helices.begin()+1;
			}
		}
	}
	//Deciding whether crossover goes in 5->3 direction of scaffold (Top right is unconventional!)
	for (vector<Crossover>::iterator cross = crossovers.begin(); cross!=crossovers.end(); ++cross){
		if (cross->nucs.first > 80 && cross->nucs.second > 80){
			if (cross->nucs.first > cross->nucs.second){cross->is_53 = false;}
			else{cross->is_53 = true;}
		}
		else{
			if (cross->nucs.first > cross->nucs.second){cross->is_53 = true;}
			else{cross->is_53 = false;}
		}
	}	
	//Adding crossover types
	int h2;
	for (vector<Crossover>::iterator cross = crossovers.begin(); cross!=crossovers.end(); ++cross){
		for (int h1=1; h1<13; h1++){
			h2 = h1+1;
			if 		(cross->helices.first == h1 && cross->helices.second == h2 && h1 % 2 != 0) {cross->type = 'i';}
			else if (cross->helices.second == h1 && cross->helices.first == h2 && h1 % 2 != 0) {cross->type = 'i';}
			else if (cross->helices.first == h1 && cross->helices.second == h2 && h1 % 2 == 0) {cross->type = 'o';}
			else if (cross->helices.second == h1 && cross->helices.first == h2 && h1 % 2 == 0) {cross->type = 'o';}
			else if (cross->is_seam) {} //Leaving seams with no type.
			else if (cross->is_long && !cross->is_seam) {} //Leaving long non-seam crossovers with no type.
			else {}
		}	
	}
	//Adding pointers to domains and staples
	for (vector<Crossover>::iterator cross = crossovers.begin(); cross!=crossovers.end(); ++cross){
		for (vector<Staple>::iterator s = staples.begin(); s != staples.end(); ++s){
			if (cross->staple->id == s->id){
				s->crossovers.push_back(cross);
			}
		}
		for (vector<Domain>::iterator dom = domains.begin(); dom != domains.end(); ++dom){
			if (cross->domains.first->id == dom->id){
				dom->crossovers.push_back(cross);
				dom->cross_domains.push_back(cross->domains.second);
			}
			if (cross->domains.second->id == dom->id){
				dom->crossovers.push_back(cross);
				dom->cross_domains.push_back(cross->domains.first);
			}
		}
	}
}
void Design::fill_stack_domains(){
	for (vector<Domain>::iterator dom = domains.begin(); dom != domains.end(); ++dom) {
		if (dom->is_seam){
			for (vector<CR>::iterator cross = dom->crossovers.begin(); cross != dom->crossovers.end(); ++cross){
				if ((*cross)->is_seam && !(*cross)->is_long){
					if ((*cross)->domains.first->id == dom-domains.begin()){
						dom->stack_domains.push_back((dom-1));
						dom->stack_domains.push_back((*cross)->domains.second);
					}
					else if ((*cross)->domains.second->id == dom-domains.begin()){
						dom->stack_domains.push_back((dom+1));
						dom->stack_domains.push_back((*cross)->domains.first);
					}
					else {
						cout << "Problems with filling stack domains in seam domains! \n" << endl;
					}
				}
			}
		}
		else if (dom->is_edge){
			if (dom-domains.begin() < n_domains/2) {
				if (dom->helix % 2 != 0){ //1,3,5,7,9,11 Left
					if (dom!=domains.begin()) {dom->stack_domains.push_back((dom-1));}
					else {dom->stack_domains.push_back(domains.end());} 
				}
				else{ //2,4,6,8,10,12 Left
					if (dom!=domains.end()) {dom->stack_domains.push_back((dom+1));}
					else {dom->stack_domains.push_back(domains.begin());} 
				}
			}
			else if (dom-domains.begin() > n_domains/2){
				if (dom->helix % 2 != 0){ //1,3,5,7,9,11 Right
					if (dom!=domains.end()) {dom->stack_domains.push_back((dom+1));}
					else {dom->stack_domains.push_back(domains.begin());} 
				}
				else{ //2,4,6,8,10,12 Right
					if (dom!=domains.begin()) {dom->stack_domains.push_back((dom-1));}
					else {dom->stack_domains.push_back(domains.end());} 
				}
			}
			else {
				cout << "Problems with filling stack domains in edge domains! \n" << endl;
			}
		}
		else{
			if (dom!=domains.end()) {dom->stack_domains.push_back((dom+1));}
			else {dom->stack_domains.push_back(domains.begin());} 
			if (dom!=domains.begin()) {dom->stack_domains.push_back((dom-1));}
			else {dom->stack_domains.push_back(domains.end());} 
		}
	}
}
void Design::initialise_states(){
	for (auto it = staples.begin(); it!= staples.end(); ++it){
		for (auto dom = it->domains.begin(); dom != it->domains.end(); ++dom){
			it->state.push_back(0);
		}
	}
	/*
	for (auto it = staples.begin(); it!= staples.end(); ++it){
		for (int i = 0; i < it->domains.size(); i++){
			it->domains[i]->state = &(it->state[i]);
		}
	}
	*/
}


//Converters
/*
pair<bool,Crossover*> Design::dp2cross(Domain* d1, Domain* d2){
	pair<bool,Crossover*> result;
	result.first = false;
	for (auto c1 = d1->crossovers.begin(); c1!= d1->crossovers.end(); ++c1){
		for (auto c2 = d2->crossovers.begin(); c2!= d2->crossovers.end(); ++c2){
			//if((*c1)->id == (*c2)->id){
			if(c1 == c2){
				result.first = true;
				result.second = *(c1);
				break;
			}
		}
	}
	return result;
}
*/

//Printers
void Design::print_staples(){
	cout << "\n------- Printing Staples -------\n\n"; 
	for (vector<Staple>::iterator s = staples.begin(); s != staples.end(); ++s){
		cout << s - staples.begin() << "\t";
		s->print();
	}
}
void Design::print_domains(){
	cout << "\n------- Printing Domains -------\n\n"; 
	for (vector<Domain>::iterator dom = domains.begin(); dom != domains.end(); ++dom){
		cout << dom->id << " ";
		cout << "(" << dom->vertices.first << "->" << dom->vertices.second << ")\t";
		cout << dom->length << "\t";
		//cout << "(" << dom->nucs.first << "->" << dom->nucs.second << ")\t";
		//cout << "seam? " << dom->is_seam << "\t";
		//cout << "edge? " << dom->is_edge << "\t";
		cout << dom->staple->id << "\t";
		cout << dom->seq << "\t";

		//cout << "s_index " << dom->s_index << "\t";
		//cout << "helix " << dom->helix << "\t";
		cout << "Crossover_ids: ";
		for (vector<CR>::iterator cross=dom->crossovers.begin(); cross!=dom->crossovers.end(); ++cross){
			cout << (*cross)->id << "\t"; 
			//cout << (*cross)->id << ": " << "(" << (*cross)->domains.first->id << "->" << (*cross)->domains.second->id << ")\t";
		}
		cout << "Cross_domains: ";
		for (vector<DOM>::iterator cross_dom=dom->cross_domains.begin(); cross_dom!=dom->cross_domains.end(); ++cross_dom){
			cout << (*cross_dom)->id << " (" << (*cross_dom)->vertices.first << "->" << (*cross_dom)->vertices.second << ")\t"; 
		}
		cout << "Stack_domains: ";
		for (vector<DOM>::iterator stack_dom=dom->stack_domains.begin(); stack_dom!=dom->stack_domains.end(); ++stack_dom){
			cout << (*stack_dom)->id << " (" << (*stack_dom)->vertices.first << "->" << (*stack_dom)->vertices.second << ")\t"; 
		}
		cout << endl;
	}
}
void Design::print_crossovers(){
	cout << "\n------- Printing Crossovers -------\n\n"; 
	for (vector<Crossover>::iterator cross = crossovers.begin(); cross != crossovers.end(); ++cross){
		cout << cross->id << " ";
		cout << "(" << cross->vertices.first << "->" << cross->vertices.second << ")\t";
		//cout << "(" << cross->nucs.first << "->" << cross->nucs.second << ")\t";
		cout << "seam? " << cross->is_seam << "\t";
		cout << "long? " << cross->is_long << "\t";
		cout << "5->3? " << cross->is_53 << "\t";
		cout << "Type: " << cross->type << "\t";
		cout << "staple " << cross->staple->id << "\t";
		cout << endl;
	}
}
















