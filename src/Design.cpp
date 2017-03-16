/*
 *
 *	Design.cpp
 * 	Author: Behnam
 *
 */


#include "Design.h"

//General Design Methods
Design::Design () {
}
void Design::fill_crossover_ids(){
	for (vector<Domain>::iterator d = domains.begin(); d != domains.end(); ++d) {
		for (vector<Crossover>::iterator c = crossovers.begin(); c != crossovers.end(); ++c) {
			if ((*c).d_a == distance(domains.begin(),d) || (*c).d_b == distance(domains.begin(),d)){
				(*d).crossover_ids.push_back(distance(crossovers.begin(), c));
			}
		}
	}
}
void Design::print_domains () {
	cout << "\n------- Design:: Printing Domains -------\n\n";
	for (vector<Domain>::iterator d = domains.begin(); d != domains.end(); ++d) {
		cout << distance(domains.begin(), d) << " (" << (*d).source << "," << (*d).target << ")\t" << (*d).length << "\t";
		cout << "\tcross_domains: ";
		for (vector<int>::iterator bp = (*d).cross_domains.begin(); bp != (*d).cross_domains.end(); ++bp) {	
			cout << (*bp) << " (" << domains[*bp].source << "," << domains[*bp].target << ")\t";
		}
		cout << "\tstack_domains: ";
		for (vector<int>::iterator sp = (*d).stack_domains.begin(); sp != (*d).stack_domains.end(); ++sp) {	
			cout << (*sp) << " (" << domains[*sp].source << "," << domains[*sp].target << ")\t";
		}
		cout << "\tcrossover_ids: ";
		for (vector<int>::iterator sp = (*d).crossover_ids.begin(); sp != (*d).crossover_ids.end(); ++sp) {	
			cout << (*sp) << "\t";
		}
		cout << "\thelix: " << d->helix;
		cout << "\tis_seam: : " << d->is_seam;
		cout << "\tis_edge: : " << d->is_edge;
		//cout << "\tStaple_ids:\t";
		//cout << d->staple;
		cout << "\n";
	}
	cout << endl;
}
void Design::print_crossovers () {
	cout << "\n------- Design:: Printing Crossovers -------\n\n";
	for (vector<Crossover>::iterator c = crossovers.begin(); c != crossovers.end(); ++c) {
		cout << distance(crossovers.begin(), c) << "\t";
		cout << "Vertices: " << (*c).v_a << "->" << (*c).v_b << "\t";
	   	cout << "Domains: " << (*c).d_a << "->" << (*c).d_b << "\t";
	   	cout << "Full: (" << (*c).d_a1 << "," << (*c).d_a2 << ")->(" << (*c).d_b1 << "," << (*c).d_b2 << ")" << "\t";
		cout << "Type: " << (*c).type << "\t";
		cout << "is_53: " << c->is_53 << "\t";
		cout << "\n";
	}
	cout << endl;
}
vector<int> Design::domain_to_crossovers(int d){
	vector<int> result;
	for (vector<Crossover>::iterator c = crossovers.begin(); c != crossovers.end(); ++c) {
		if ((*c).d_a == d || (*c).d_b == d){
			result.push_back(distance(crossovers.begin(), c));
			break;
		}
	}
	return result;
}
vector<int> Design::vertex_to_crossovers(int v){
	vector<int> result;
	for (vector<Crossover>::iterator c = crossovers.begin(); c != crossovers.end(); ++c) {
		if ((*c).v_a == v || (*c).v_b == v){
			result.push_back(distance(crossovers.begin(), c));
		}
	}
	return result;
}
int Design::vpair_to_crossover(pair<int,int> vpair){//DANGER: Could have multiple crossovers!
	int result;
	for (vector<Crossover>::iterator c = crossovers.begin(); c != crossovers.end(); ++c) {
		if ( ((*c).v_a == vpair.first && (*c).v_b == vpair.second) || ((*c).v_b == vpair.first && (*c).v_a == vpair.second) ){
			result = distance(crossovers.begin(), c);
			break;
		}
	}
	return result;
}
int Design::dpair_to_crossover(pair<int,int> dpair){
	int result;
	for (vector<Crossover>::iterator c = crossovers.begin(); c != crossovers.end(); ++c) {
		if ( ((*c).d_a == dpair.first && (*c).d_b == dpair.second) || ((*c).d_b == dpair.first && (*c).d_a == dpair.second) ){
			result = distance(crossovers.begin(), c);
			break;
		}
	}
	return result;
}
bool Design::check_single_domain_staple(int e){
	bool result;
	if (domains[e].crossover_ids.empty()){
		result = true;
	}
	else{
		result = false;
	}
	return result;
}
bool Design::check_double_domain_staple(int e){
	bool result;
	if (domains[e].crossover_ids.size()==1){
		result = true;
	}
	else{
		result = false;
	}
	return result;
}
bool Design::check_triple_domain_staple(int e){//DANGER: could be 3 with long crossovers!
	bool result;
	if (domains[e].crossover_ids.size()>1){
		result = true;
	}
	else{
		result = false;
	}
	return result;
}

//Tile Design Methods
//Tile::Tile () {}
Tile::Tile (Origami origami_) {
	origami = origami_;
	get_n_domains();
	fill_domains();
	fill_crossovers();
	renumber();
	fill_crossover_ids();
	fill_stack_domains();
	add_long_crossovers();
	fill_cross_domains();
	add_ids_for_crossovers();
}
/*
void Tile::fill_stack_domains(){
	for (vector<Domain>::iterator d = domains.begin(); d != domains.end(); ++d) {
		d->stack_domains.push_back((d->source+1)%n_domains);
		d->stack_domains.push_back((n_domains+(d->source-1))%n_domains);
	}
}
*/
void Tile::fill_cross_domains(){
	for (int d=0; d < domains.size(); d++) {
		for (vector<Crossover>::iterator c = crossovers.begin(); c != crossovers.end(); ++c) {
			if (c->d_b == d) {domains[d].cross_domains.push_back(c->d_a);}
			if (c->d_a == d) {domains[d].cross_domains.push_back(c->d_b);}
		}
	}
}
void Tile::get_n_domains(){
	this->n_domains = 0;
	for (vector<Staple>::iterator s = origami.staples.begin(); s!=origami.staples.end(); ++s)
	{
		for (vector<pair<int, int> >::iterator d = (*s).domains.begin(); d!=(*s).domains.end(); ++d){
			this->n_domains += 1;
		}
	}
	this->n_vertices = this->n_domains;
}
void Tile::fill_domains(){
	Domain dom; 
	int h_a, h_b;
	for (vector<Staple>::iterator s = origami.staples.begin(); s!=origami.staples.end(); ++s)
	{
		for (int d=0; d < s->domains.size(); d++){
			dom.s_index = d;
			dom.length = s->len_domains[d]; 
			dom.staple = s - origami.staples.begin();
			dom.source = s->vertices[d].first;
			dom.target = s->vertices[d].second;
			if (d==0){
				dom.seq = s->seq.substr(0,dom.length);
			}
			else {
				dom.seq = s->seq.substr(s->len_domains[d-1],dom.length);
			}
			for (int h=0; h<origami.helices.size(); h++){
				if(find(origami.helices[h].begin(), origami.helices[h].end(), s->domains[d].first) != origami.helices[h].end()) { 
					h_a = h+1;
				}
				if(find(origami.helices[h].begin(), origami.helices[h].end(), s->domains[d].second) != origami.helices[h].end()) { 
					h_b = h+1;
				}
			}
			if (h_a==h_b){dom.helix = h_a;}
			else {
				cout << "WARNING: domain's vertices are on different helices!";
			   	cout << "\t" << h_a << " " << s->domains[d].first;
				cout << "\t" << h_b << " " << s->domains[d].second;  
				cout << endl;}
			if ((s->is_seam && s->domains.size() == 3 && d == 1) ||
				(s->is_seam && s->domains.size() == 3 && d == 2) ||	
				(s->is_seam && origami.inputs->staple_file_name == "U_Staples.txt"))
			{
				dom.is_seam = true;
			}
			else{ dom.is_seam = false;} 
			
			if ((s->is_edge && s->domains.size() > 1 && origami.inputs->staple_file_name == "S_Staples.txt" && dom.helix==1) ||
				(s->is_edge && s->domains.size() > 1 && origami.inputs->staple_file_name == "S_Staples.txt" && dom.helix==12) || 
				(s->is_edge && s->domains.size() > 1 && origami.inputs->staple_file_name == "S_Staples.txt" && dom.helix>1 && dom.helix<12 && d != s->domains.size()-1) ||	
				(s->is_edge && s->domains.size() == 2 && origami.inputs->staple_file_name == "U_Staples.txt"))
			{
				dom.is_edge = true;
			}
			else{ dom.is_edge = false;} 
				
			dom.is_middle = false;
			if (s->domains.size()==3 && dom.s_index == 1) {dom.is_middle = true;}	
			this->domains.push_back(dom);
		}
	}
}
void Tile::fill_crossovers(){ 
	Crossover cross;
	for (vector<Staple>::iterator s = origami.staples.begin(); s!=origami.staples.end(); ++s){
		for (int c=0; c < s->crossovers.size(); c++){
			cross.v_a = s->cross_indices[c].first;
			cross.v_b = s->cross_indices[c].second;
			cross.staple = s - origami.staples.begin();
			for (int h=0; h<origami.helices.size(); h++){
				if(find(origami.helices[h].begin(), origami.helices[h].end(), s->crossovers[c].first) != origami.helices[h].end()) { 
					cross.h_a = h+1;
				}
				if(find(origami.helices[h].begin(), origami.helices[h].end(), s->crossovers[c].second) != origami.helices[h].end()) { 
					cross.h_b = h+1;
				}
			}
			if ((s->is_seam && s->domains.size() == 3 && c == 1) || (s->is_seam && s->domains.size() == 2)){
				cross.d_a1 = cross.v_a;
				cross.d_a2 = (cross.v_a + 1) % n_vertices;
				cross.d_b1 = (n_vertices + cross.v_b - 1) % n_vertices;
				cross.d_b2 = cross.v_b;
				if (s->crossovers[c].first > s->crossovers[c].second){
					cross.is_53 = false;
				}
				else {
					cross.is_53 = true;
				}
				if ( (cross.h_a == 1 && cross.h_b == 2) || (cross.h_b == 1 && cross.h_a == 2) ) {cout << "WARNING: No seam here!" << endl;}
				else if ( (cross.h_a == 2 && cross.h_b == 3) || (cross.h_b == 2 && cross.h_a == 3) ) {cross.type = 'o';}
				else if ( (cross.h_a == 3 && cross.h_b == 4) || (cross.h_b == 3 && cross.h_a == 4) ) {cout << "WARNING: No seam here!" << endl;}
				else if ( (cross.h_a == 4 && cross.h_b == 5) || (cross.h_b == 4 && cross.h_a == 5) ) {cross.type = 'o';}
				else if ( (cross.h_a == 5 && cross.h_b == 6) || (cross.h_b == 5 && cross.h_a == 6) ) {cout << "WARNING: No seam here!" << endl;}
				else if ( (cross.h_a == 6 && cross.h_b == 7) || (cross.h_b == 6 && cross.h_a == 7) ) {cross.type = 'o';}
				else if ( (cross.h_a == 7 && cross.h_b == 8) || (cross.h_b == 7 && cross.h_a == 8) ) {cout << "WARNING: No seam here!" << endl;}
				else if ( (cross.h_a == 8 && cross.h_b == 9) || (cross.h_b == 8 && cross.h_a == 9) ) {cross.type = 'o';}
				else if ( (cross.h_a == 9 && cross.h_b == 10) || (cross.h_b == 9 && cross.h_a == 10) ) {cout << "WARNING: No seam here!" << endl;}
				else if ( (cross.h_a == 10 && cross.h_b == 11) || (cross.h_b == 10 && cross.h_a == 11) ) {cross.type = 'o';}
				else if ( (cross.h_a == 11 && cross.h_b == 12) || (cross.h_b == 11 && cross.h_a == 12) ) {cout << "WARNING: No seam here!" << endl;}
				else if ( cross.h_a == cross.h_b ) {cross.type = 'm';}
				else {cout << "HAHAHA???" << endl;}
			}
			else {
				cross.d_a1 = (n_vertices + s->cross_indices[c].first - 1) % n_vertices;
				cross.d_a2 = s->cross_indices[c].first;
				cross.d_b1 = s->cross_indices[c].second;
				cross.d_b2 = (s->cross_indices[c].second + 1) % n_vertices;
				if (s->crossovers[c].first > 80 && s->crossovers[c].second > 80){ //To make sure that the crossover going
				   	//from 3' to 5' end of staple is not in the top right section.
					if (s->crossovers[c].first > s->crossovers[c].second){
						cross.is_53 = false;
					}
					else {
						cross.is_53 = true;
					}
				}
				else{
					if (s->crossovers[c].first > s->crossovers[c].second){
						cross.is_53 = true;
					}
					else {
						cross.is_53 = false;
					}
				}
				if ( (cross.h_a == 1 && cross.h_b == 2) || (cross.h_b == 1 && cross.h_a == 2) ) {cross.type = 'i';}
				else if ( (cross.h_a == 2 && cross.h_b == 3) || (cross.h_b == 2 && cross.h_a == 3) ) {cross.type = 'o';}
				else if ( (cross.h_a == 3 && cross.h_b == 4) || (cross.h_b == 3 && cross.h_a == 4) ) {cross.type = 'i';}
				else if ( (cross.h_a == 4 && cross.h_b == 5) || (cross.h_b == 4 && cross.h_a == 5) ) {cross.type = 'o';}
				else if ( (cross.h_a == 5 && cross.h_b == 6) || (cross.h_b == 5 && cross.h_a == 6) ) {cross.type = 'i';}
				else if ( (cross.h_a == 6 && cross.h_b == 7) || (cross.h_b == 6 && cross.h_a == 7) ) {cross.type = 'o';}
				else if ( (cross.h_a == 7 && cross.h_b == 8) || (cross.h_b == 7 && cross.h_a == 8) ) {cross.type = 'i';}
				else if ( (cross.h_a == 8 && cross.h_b == 9) || (cross.h_b == 8 && cross.h_a == 9) ) {cross.type = 'o';}
				else if ( (cross.h_a == 9 && cross.h_b == 10) || (cross.h_b == 9 && cross.h_a == 10) ) {cross.type = 'i';}
				else if ( (cross.h_a == 10 && cross.h_b == 11) || (cross.h_b == 10 && cross.h_a == 11) ) {cross.type = 'o';}
				else if ( (cross.h_a == 11 && cross.h_b == 12) || (cross.h_b == 11 && cross.h_a == 12) ) {cross.type = 'i';}
				else {cout << "HAHAHA???" << endl;}
			}
			cross.d_a = cross.d_a1;
			cross.d_b = cross.d_b1;
			this->crossovers.push_back(cross);
		}
	}
}
void Tile::fill_stack_domains(){//FIX THIS
	for (vector<Domain>::iterator d = domains.begin(); d != domains.end(); ++d) {
		if (d->is_seam){
			for (vector<int>::iterator c = d->crossover_ids.begin(); c != d->crossover_ids.end(); ++c){
				if (crossovers[*c].type == 'm'){	
					if (crossovers[*c].is_53 == false && crossovers[*c].d_a == d-domains.begin()){
						d->stack_domains.push_back(d-domains.begin()-1);
						d->stack_domains.push_back(crossovers[*c].d_b);
					}
					else if (crossovers[*c].is_53 == false && crossovers[*c].d_b == d-domains.begin()){
						d->stack_domains.push_back(d-domains.begin()+1);
						d->stack_domains.push_back(crossovers[*c].d_a);
					}
					else if (crossovers[*c].is_53 == true && crossovers[*c].d_a == d-domains.begin()){
						d->stack_domains.push_back(d-domains.begin()-1);
						d->stack_domains.push_back(crossovers[*c].d_b);
					}
					else if (crossovers[*c].is_53 == true && crossovers[*c].d_b == d-domains.begin()){
						d->stack_domains.push_back(d-domains.begin()+1);
						d->stack_domains.push_back(crossovers[*c].d_a);
					}
					else {
						cout << "Problems with filling stack domains in seam domains! \n" << endl;
					}
				}
			}
		}
		else if (d->is_edge){
			if (d-domains.begin() < n_domains/2) {
				if (d->helix % 2 != 0){ //1,3,5,7,9,11 Left
					d->stack_domains.push_back((n_domains+(d-domains.begin()-1))%n_domains);
				}
				else{ //2,4,6,8,10,12 Left
					d->stack_domains.push_back((d-domains.begin()+1)%n_domains);
				} 
			}
			else if (d-domains.begin() > n_domains/2){
				if (d->helix % 2 != 0){ //1,3,5,7,9,11 Right
					d->stack_domains.push_back((d-domains.begin()+1)%n_domains);
				}
				else{ //2,4,6,8,10,12 Right
					d->stack_domains.push_back((n_domains+(d-domains.begin()-1))%n_domains);
				} 
			}
			else {
				cout << "Problems with filling stack domains in edge domains! \n" << endl;
			}
		}
		else{
			d->stack_domains.push_back((d-domains.begin()+1)%n_domains);
			d->stack_domains.push_back((n_domains+(d-domains.begin()-1))%n_domains);
		}
	}
}
bool Domain_sort(const Domain &a, const Domain &b) {
	    return a.source < b.source;
}
void Tile::renumber(){
	std::sort(domains.begin(),domains.end(),Domain_sort);
}
void Tile::add_long_crossovers(){
	Crossover cross, c1, c2;
	int index = crossovers.size();
	for (vector<Domain>::iterator d = domains.begin(); d!=domains.end(); ++d){
		if (d->is_middle){
			c1 = crossovers[d->crossover_ids[0]]; c2 = crossovers[d->crossover_ids[1]];
			cross.v_a = c1.v_a;	cross.v_b = c2.v_b;
			cross.d_a = c1.d_a;	cross.d_b = c2.d_b;
			cross.d_a1 = domains[cross.d_a].source; cross.d_a2 = domains[cross.d_a].target;
			cross.d_b1 = domains[cross.d_b].source; cross.d_b2 = domains[cross.d_b].target;
			cross.staple = c1.staple;
			cross.type = 'l';
			crossovers.push_back(cross);
			domains[cross.d_a].crossover_ids.push_back(index);
			domains[cross.d_b].crossover_ids.push_back(index);
			index += 1;
		}
	}
}
void Tile::add_ids_for_crossovers(){
	for (int i=0; i<crossovers.size(); i++){
		crossovers[i].id = i;
	}
}



//Frits Design Methods
Frits::Frits () {
	n_vertices = 166;
	n_domains = n_vertices;
	fill_domains();
	fill_crossovers();
	fill_crossover_ids();
}
void Frits::fill_domains(){
	Domain d; d.length = 16; 
	for(int i=0; i<n_vertices-1; i++){
		d.source = i; d.target = i+1;
		domains.push_back(d);
	}
	d.source = n_vertices-1; d.target = 0;
	domains.push_back(d);
	domains[82].length *= 2; 
	domains[165].length *= 2; 
	int d1, d2;
	d1 = 1;
	d2 = 10;
	domains[d1].cross_domains.push_back(d2); domains[d2].cross_domains.push_back(d1);
	domains[d1].stack_domains.push_back(d1-1); domains[d1].stack_domains.push_back(d1+1);
	domains[d2].stack_domains.push_back(d2-1); domains[d2].stack_domains.push_back(d2+1);
	for (int L = 0; L < 11; L++){
		for (int l = 0; l < 3; l++){	
			if (L==0 && l==0){continue;}
			d1 += 2;
			d2 -= 2;
			domains[d1].cross_domains.push_back(d2); domains[d2].cross_domains.push_back(d1);
			domains[d1].stack_domains.push_back(d1-1); domains[d1].stack_domains.push_back(d1+1);
			domains[d2].stack_domains.push_back(d2-1); domains[d2].stack_domains.push_back(d2+1);
		}
		if (L%2 != 0) {d1 += 2; d2 += 12;}
		else {d2 += 14;}	
	}
	d1 = 84;
	d2 = 93; 
	domains[d1].cross_domains.push_back(d2); domains[d2].cross_domains.push_back(d1);
	domains[d1].stack_domains.push_back(d1-1); domains[d1].stack_domains.push_back(d1+1);
	domains[d2].stack_domains.push_back(d2-1); domains[d2].stack_domains.push_back(d2+1);
	for (int L = 0; L < 11; L++){
		for (int l = 0; l < 3; l++){	
			if (L==0 && l==0){continue;}
			d1 += 2;
			d2 -= 2;
			domains[d1].cross_domains.push_back(d2); domains[d2].cross_domains.push_back(d1);
			domains[d1].stack_domains.push_back(d1-1); domains[d1].stack_domains.push_back(d1+1);
			domains[d2].stack_domains.push_back(d2-1); domains[d2].stack_domains.push_back(d2+1);
		}
		if (L%2 != 0) {d1 += 2; d2 += 12;}
		else {d2 += 14;}	
	}
	d1=12; d2=152;
	for (int i=0; i<5; i++){
		domains[d1].cross_domains.push_back(d2); domains[d2].cross_domains.push_back(d1);
		domains[d1].stack_domains.push_back(d1-1); domains[d1].stack_domains.push_back(d2);
		domains[d2].stack_domains.push_back(d2+1); domains[d2].stack_domains.push_back(d1);
		d1+=1; d2-=1;
		domains[d1].cross_domains.push_back(d2); domains[d2].cross_domains.push_back(d1);
		domains[d1].stack_domains.push_back(d1+1); domains[d1].stack_domains.push_back(d2);
		domains[d2].stack_domains.push_back(d2-1); domains[d2].stack_domains.push_back(d1);
		d1+=13; d2-=13;
	}
	domains[0].stack_domains.push_back(165); domains[0].stack_domains.push_back(1);
	domains[165].stack_domains.push_back(164); domains[165].stack_domains.push_back(0);
	int myarray[] = {2,4,77,79,81,82,83,85,87,160,162,164};
	int i;
	for (int j=0; j<sizeof(myarray)/sizeof(*myarray); j++){	
		i=myarray[j];
		domains[i].stack_domains.push_back(i-1); domains[i].stack_domains.push_back(i+1);
	}

	scaffold_sequence = "CTTCAAGAACTCTGTAGCACCGCCTACATACCTCGCTCTGCTAATCCTGTTACCAGTGGCTGCTGCCAGTGGCGATAAGTCGTGTCTTACCGGGTTGGACTCAAGACGATAGTTACCGGATAAGGCGCAGCGGTCGGGCTGAACGGGGGGTTCGTGCACACAGCCCAGCTTGGAGCGAACGACCTACACCGAACTGAGATACCTACAGCGTGAGCTATGAGAAAGCGCCACGCTTCCCGAAGGGAGAAAGGCGGACAGGTATCCGGTAAGCGGCAGGGTCGGAACAGGAGAGCGCACGAGGGAGCTTCCAGGGGGAAACGCCTGGTATCTTTATAGTCCTGTCGGGTTTCGCCACCTCTGACTTGAGCGTCGATTTTTGTGATGCTCGTCAGGGGGGCGGAGCCTATGGAAAAACGCCAGCAACGCGGCCTTTTTACGGTTCCTGGCCTTTTGCTGGCCTTTTGCTCACATGTTCTTTCCTGCGTTATCCCCTGATTCTGTGGATAACCGTATTACCGCCTTTGAGTGAGCTGATACCGCTCGCCGCAGCCGAACGACCGAGCGCAGCGAGTCAGTGAGCGAGGAAGCGGAAGAGCGCCCAATACGCAAACCGCCTCTCCCCGCGCGTTGGCCGATTCATTAATGCAGCTGGCACGACAGGTTTCCCGACTGGAAAGCGGGCAGTGAGCGCAACGCAATTAATGTGAGTTAGCTCACTCATTAGGCACCCCAGGCTTTACACTTTATGCTTCCGGCTCGTATGTTGTGTGGAATTGTGAGCGGATAACAATTTCACACAGGAAACAGCTATGACCATGATTACGCCAAGCTCCTCAGCAATTCACTGGCCGTCGTTTTACAACGTCGTGACTGGGAAAACCCTGGCGTTACCCAACTTAATCGCCTTGCAGCACATCCCCCTTTCGCCAGCTGGCGTAATAGCGAAGAGGCCCGCACCGATCGCCCTTCCCAACAGTTGCGCAGCCTGAATGGCGAATGGCGCCTGATGCGGTATTTTCTCCTTACGCATCTGTGCGGTATTTCACACCGCATATGGTGCACTCTCAGTACAATCTGCTCTGATGCCGCATAGTTAAGCCAGCCCCGACACCCGCCAACACCCGCTGACGCGCCCTGACGGGCTTGTCTGCTCCCGGCATCCGCTTACAGACAAGCTGTGACCGTCTCCGGGAGCTGCATGTGTCAGAGGTTTTCACCGTCATCACCGAAACGCGCGAGACGAAAGGGCCTCGTGATACGCCTATTTTTATAGGTTAATGTCATGATAATAATGGTTTCTTAGACGTCAGGTGGCACTTTTCGGGGAAATGTGCGCGGAACCCCTATTTGTTTATTTTTCTAAATACATTCAAATATGTATCCGCTCATGAGACAATAACCCTGATAAATGCTTCAATAATATTGAAAAAGGAAGAGTATGAGTATTCAACATTTCCGTGTCGCCCTTATTCCCTTTTTTGCGGCATTTTGCCTTCCTGTTTTTGCTCACCCAGAAACGCTGGTGAAAGTAAAAGATGCTGAAGATCAGTTGGGTGCACGAGTGGGTTACATCGAACTGGATCTCAACAGCGGTAAGATCCTTGAGAGTTTTCGCCCCGAAGAACGTTTTCCAATGATGAGCACTTTTAAAGTTCTGCTATGTGGCGCGGTATTATCCCGTATTGACGCCGGGCAAGAGCAACTCGGTCGCCGCATACACTATTCTCAGAATGACTTGGTTGAGTACTCACCAGTCACAGAAAAGCATCTTACGGATGGCATGACAGTAAGAGAATTATGCAGTGCTGCCATAACCATGAGTGATAACACTGCGGCCAACTTACTTCTGACAACGATCGGAGGACCGAAGGAGCTAACCGCTTTTTTGCACAACATGGGGGATCATGTAACTCGCCTTGATCGTTGGGAACCGGAGCTGAATGAAGCCATACCAAACGACGAGCGTGACACCACGATGCCTGTAGCAATGGCAACAACGTTGCGCAAACTATTAACTGGCGAACTACTTACTCTAGCTTCCCGGCAACAATTAATAGACTGGATGGAGGCGGATAAAGTTGCAGGACCACTTCTGCGCTCGGCCCTTCCGGCTGGCTGGTTTATTGCTGATAAATCTGGAGCCGGTGAGCGTGGGTCTCGCGGTATCATTGCAGCACTGGGGCCAGATGGTAAGCCCTCCCGTATCGTAGTTATCTACACGACGGGGAGTCAGGCAACTATGGATGAACGAAATAGACAGATCGCTGAGATAGGTGCCTCACTGATTAAGCATTGGTAACTGTCAGACCAAGTTTACTCATATATACTTTAGATTGATTTAAAACTTCATTTTTAATTTAAAAGGATCTAGGTGAAGATCCTTTTTGATAATCTCATGACCAAAATCCCTTAACGTGAGTTTTCGTTCCACTGAGCGTCAGACCCCGTAGAAAAGATCAAAGGATCTTCTTGAGATCCTTTTTTTCTGCGCGTAATCTGCTGCTTGCAAACAAAAAAACCACCGCTACCAGCGGTGGTTTGTTTGCCGGATCAAGAGCTACCAACTCTTTTTCCGAAGGTAACTGGCTTCAGCAGAGCGCAGATACCAAATACTGTTCTTCTAGTGTAGCCGTAGTTAGGCCACCA"; //5'-3'; start at domain 165, end at domain 0. 

	for (int i=1; i<82; i+=4){
		domains[i].length = 15;
	}
	for (int i=84; i<165; i+=4){
		domains[i].length = 15;
	}

	//string domain_sequence;
	int s = 0;
	for (unsigned i = domains.size(); i-- > 0; ) {
		//domain_sequence.clear();
		for (int j=0; j<domains[i].length; j++) {
			domains[i].seq += scaffold_sequence[s];
			//domain_sequence += scaffold_sequence[s];
			//(domains[i].seq).append(scaffold_sequence[s]);
			//cout << i << "\t" << j << "\t" << s << "\t" << scaffold_sequence[s] << endl;
	  		s++;
		}
		//domains[i].seq = domain_sequence;	
	}
}
void Frits::fill_crossovers(){
	int v1, v2, d1, d2;
   	Crossover c;
	v1=1; v2=11; d1=1; d2=10;
	c.v_a = v1; c.v_b = v2; c.d_a = d1; c.d_b = d2;	
	c.d_a1 = domains[d1].source; c.d_a2 = domains[d1].target; c.d_b1 = domains[d2].source; c.d_b2 = domains[d2].target; c.type = 'i';
	crossovers.push_back(c);
	for (int L = 0; L < 11; L++){
		for (int l = 0; l < 3; l++){	
			if(L==0 && l==0){continue;}
			v1 = v1 + 2; v2 = v2 - 2; d1 = d1 + 2; d2 = d2 - 2;
			c.v_a = v1; c.v_b = v2;	c.d_a = d1; c.d_b = d2; 
			c.d_a1 = domains[d1].source; c.d_a2 = domains[d1].target; c.d_b1 = domains[d2].source; c.d_b2 = domains[d2].target; 
			if (L%2 == 0) {c.type = 'i';}
			else {c.type = 'o';}
			crossovers.push_back(c);
		}
		v1 = v1 + 1; v2 = v2 + 13;	
		if (L%2 != 0) {d1 = d1 + 2; d2 = d2 + 12;}
		else {d2 = d2 + 14;}	
	}
	v1 = 84; v2 = 94; d1 = 84; d2 = 93; 
	c.v_a = v1; c.v_b = v2;	c.d_a = d1; c.d_b = d2; 
	c.d_a1 = domains[d1].source; c.d_a2 = domains[d1].target; c.d_b1 = domains[d2].source; c.d_b2 = domains[d2].target; c.type = 'i';
	crossovers.push_back(c);
	for (int L = 0; L < 11; L++){
		for (int l = 0; l < 3; l++){	
			if(L==0 && l==0){continue;}
			v1 = v1 + 2; v2 = v2 - 2; d1 = d1 + 2; d2 = d2 - 2;
			c.v_a = v1; c.v_b = v2;	c.d_a = d1; c.d_b = d2; 
			c.d_a1 = domains[d1].source; c.d_a2 = domains[d1].target; c.d_b1 = domains[d2].source; c.d_b2 = domains[d2].target; 
			if (L%2 == 0) {c.type = 'i';}
			else {c.type = 'o';}
			crossovers.push_back(c);
		}
		v1 = v1 + 1; v2 = v2 + 13;	
		if (L%2 != 0) {d1 = d1 + 2; d2 = d2 + 12;}
		else {d2 = d2 + 14;}	
	}
	c.v_a = 12; c.v_b = 153; 	c.d_a = 12; c.d_b = 152;
	c.d_a1 = domains[12].source; c.d_a2 = domains[12].target; c.d_b1 = domains[152].source; c.d_b2 = domains[152].target; c.type = 'm';
	crossovers.push_back(c);
	c.v_a = 14; c.v_b = 151; 	c.d_a = 13; c.d_b = 151;
	c.d_a1 = domains[13].source; c.d_a2 = domains[13].target; c.d_b1 = domains[151].source; c.d_b2 = domains[151].target; c.type = 'm';
	crossovers.push_back(c);
	c.v_a = 26; c.v_b = 139; 	c.d_a = 26; c.d_b = 138;
	c.d_a1 = domains[26].source; c.d_a2 = domains[26].target; c.d_b1 = domains[138].source; c.d_b2 = domains[138].target; c.type = 'm';
	crossovers.push_back(c);
	c.v_a = 28; c.v_b = 137; 	c.d_a = 27; c.d_b = 137;
	c.d_a1 = domains[27].source; c.d_a2 = domains[27].target; c.d_b1 = domains[137].source; c.d_b2 = domains[137].target; c.type = 'm';
	crossovers.push_back(c);
	c.v_a = 40; c.v_b = 125; 	c.d_a = 40; c.d_b = 124;
	c.d_a1 = domains[40].source; c.d_a2 = domains[40].target; c.d_b1 = domains[124].source; c.d_b2 = domains[124].target; c.type = 'm';
	crossovers.push_back(c);
	c.v_a = 42; c.v_b = 123; 	c.d_a = 41; c.d_b = 123;
	c.d_a1 = domains[41].source; c.d_a2 = domains[41].target; c.d_b1 = domains[123].source; c.d_b2 = domains[123].target; c.type = 'm';
	crossovers.push_back(c);
	c.v_a = 54; c.v_b = 111; 	c.d_a = 54; c.d_b = 110;
	c.d_a1 = domains[54].source; c.d_a2 = domains[54].target; c.d_b1 = domains[110].source; c.d_b2 = domains[110].target; c.type = 'm';
	crossovers.push_back(c);
	c.v_a = 56; c.v_b = 109; 	c.d_a = 55; c.d_b = 109;
	c.d_a1 = domains[55].source; c.d_a2 = domains[55].target; c.d_b1 = domains[109].source; c.d_b2 = domains[109].target; c.type = 'm';
	crossovers.push_back(c);
	c.v_a = 68; c.v_b = 97; 	c.d_a = 68; c.d_b = 96;
	c.d_a1 = domains[68].source; c.d_a2 = domains[68].target; c.d_b1 = domains[96].source; c.d_b2 = domains[96].target; c.type = 'm';
	crossovers.push_back(c);
	c.v_a = 70; c.v_b = 95; 	c.d_a = 69; c.d_b = 95;
	c.d_a1 = domains[69].source; c.d_a2 = domains[69].target; c.d_b1 = domains[95].source; c.d_b2 = domains[95].target; c.type = 'm';
	crossovers.push_back(c);
}


//Simple Design Methods
Simple::Simple () {
	n_vertices = 10;
	n_domains = n_vertices;
	fill_domains();
	fill_crossovers();
}
void Simple::fill_domains(){
	Domain d; d.length = 16; 
	for(int i=0; i<n_vertices-1; i++){
		d.source = i; d.target = i+1;
		domains.push_back(d);
	}
	d.source = n_vertices-1; d.target = 0;
	domains.push_back(d);
	domains[0].stack_domains.push_back(9); domains[0].stack_domains.push_back(1);
	for (int i=1; i<n_vertices-1; i++){
		domains[i].stack_domains.push_back(i-1); domains[i].stack_domains.push_back(i+1);
	}
	domains[9].stack_domains.push_back(8); domains[9].stack_domains.push_back(0);
	
	domains[1].cross_domains.push_back(8);
	domains[8].cross_domains.push_back(1);
	
	domains[3].cross_domains.push_back(6);
	domains[6].cross_domains.push_back(3);
}
void Simple::fill_crossovers(){
	int v1, v2, d1, d2;
   	Crossover c;
	v1=2; v2=8; d1=1; d2=8;
	c.v_a = v1; c.v_b = v2; c.d_a = d1; c.d_b = d2;	
	c.d_a1 = domains[d1].source; c.d_a2 = domains[d1].target; c.d_b1 = domains[d2].source; c.d_b2 = domains[d2].target; c.type = 'i';
	crossovers.push_back(c);
	v1=4; v2=6; d1=3; d2=6;
	c.v_a = v1; c.v_b = v2; c.d_a = d1; c.d_b = d2;	
	c.d_a1 = domains[d1].source; c.d_a2 = domains[d1].target; c.d_b1 = domains[d2].source; c.d_b2 = domains[d2].target; c.type = 'i';
	crossovers.push_back(c);
}
