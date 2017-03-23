/*
 *
 *	Strand.cpp
 * 	Author: Behnam
 *
 */

#include "Strand.h"


int circ_dist(int p1, int p2, int scaffold_length){
	int a1, a2, result;
	a1 = ((scaffold_length + p1 - p2) % scaffold_length) +1 ;
	a2 = ((scaffold_length + p2 - p1) % scaffold_length) +1 ;
	if (a1<a2){
		result = a1;
	}
	else if (a1>a2){
		result = a2;
	}
	else {
		cout << "Warning: a1=a2." << endl;
		result = a2;
	}
	return result;
}

//Strand Methods
void Strand::set_seq(string seq_){
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

//Scaffold Methods
Scaffold::Scaffold () {
}
Scaffold::Scaffold (string string_, string Domain_file_name) {
	read_string(string_);
	set_length();
	set_reverse_comp();
	read_domains(Domain_file_name);
}
void Scaffold::read_string(string line){
	set_seq(line);
}
void Scaffold::read_domains(string Domain_file_name){
	string line;
	int kk = 0;
	ifstream myfile2 (Domain_file_name);
	if (myfile2.is_open()) {
		while(getline(myfile2, line)) {
			//cout << line << endl;
			if (kk==0){this->first_nuc = -1 * stoi(line);}
			else{
				this->len_domains.push_back(stoi(line));
			}
			kk++;
		}
		myfile2.close();
	}
	else {printf ("Error:\t Could not read Domains file\n"); exit (EXIT_FAILURE);}
	if (sum_elements(this->len_domains) != this->length){
		cout << "WARNING: total domain lengths does not match this->length..." << endl;
		cout << "\tDomain lengths: " << sum_elements(this->len_domains) << "\tScaff: " << this->length << endl;
	}
	this->n_domains = this->len_domains.size();
	
	string dom_str;
	int current_nuc = this->first_nuc;
	pair <int,int> domain;
	for (int d=0; d < this->n_domains - 1; d++){
		dom_str = this->seq.substr(current_nuc,len_domains[d]);
		this->seq_domains.push_back(dom_str);
		this->domains.push_back(make_pair(current_nuc, current_nuc+this->len_domains[d]-1));
		current_nuc += this->len_domains[d];
	}
	string end_str;
	int remaining = this->length - current_nuc;
	end_str = this->seq.substr(current_nuc,remaining);
	end_str += this->seq.substr(0,first_nuc);
	this->seq_domains.push_back(end_str);
	this->domains.push_back(make_pair(current_nuc, this->first_nuc-1));
	if (end_str.length() != this->len_domains[this->n_domains-1]){
		cout << "WARNING: End staple messed up in scaffold!" << endl;
	}
}

//Staple Methods
Staple::Staple (string string_) {
	read_string(string_);
	set_length();
	set_reverse_comp();
	if (this->length != sum_elements(this->len_domains) ) {cout << "Warning: staple length weird!\n";}
	split_seqs();
	//if (this->length>16){ n_domains = 2;}
	//else {n_domains = 1;}
	/*
	n_domains = abs(end_helix-start_helix)+1;
	if (start_helix < 12 && start_helix > 1){
		if (start_nuc < 128 && start_nuc >= 95){
			n_domains = SEAM_DOMAINS;
		}
	}		
	if (end_helix < 12 && end_helix > 1){
		if (end_nuc < 128 && end_nuc > 95){
			n_domains = SEAM_DOMAINS;
		}
	}
	*/
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

	this->start_helix = stoi(str_start_helix);
	this->end_helix = stoi(str_end_helix);
	this->start_nuc = stoi(str_start_nuc);
	this->end_nuc = stoi(str_end_nuc);

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

//Origami Methods
Origami::Origami () {
}
Origami::Origami (Inputs * inputs_) {
	inputs = inputs_;
	read_files();
	fill_staple_domains();
	//fill_scaffold_domains();
	//find_end_staple();
	//fix_end();
	fill_domain_indices();
	fill_seams();
	fill_crossovers();
	fill_lengths();
	fill_edges();
	fill_helices();
	REVERESE_LEN_DOMAINS();
}
void Origami::read_files(){
	string sc_line;
	ifstream myfile (inputs->scaffold_file_name);
	if (myfile.is_open()) {
		getline (myfile,sc_line);
		myfile.close();
	}
	else {printf ("Error:\t Could not read Scaffold file\n"); exit (EXIT_FAILURE);}
	scaffold = Scaffold(sc_line, inputs->domain_file_name); 
	string line;
	ifstream myfile1 (inputs->staple_file_name);
	//int i=0;
	if (myfile1.is_open()) {
		while(getline(myfile1, line)) {
			//cout << "Staple " << i << endl;
			//i++;
			staples.push_back(Staple(line));
		}
		myfile1.close();
	}
	else {printf ("Error:\t Could not read Staples file\n"); exit (EXIT_FAILURE);}
	
}
void Origami::print_staples(){
	cout << "\n------- Origami:: Printing Staples -------\n\n"; 
	for (int s=0; s<staples.size(); s++){
		cout << s << "\t";
		staples[s].print_staple();
	}
	if (M.size() == scaffold.length) {/*cout << "All matched!" << endl;*/}
	else {cout << "Total bases matched: " << M.size() << "\tScaffold length: " << scaffold.length << endl;}
}
int Origami::circ_p(size_t pos, int dom_len){
	int result;
	if (pos!=std::string::npos){
		result = pos;
		if (result > scaffold.length - dom_len ){
			result = -1;
		}
		if (result == 0){
			result = -1;
		}
	}
	else {
		result = -1;
	}
	return result;
}
bool Origami::is_not_already_found(pair<int,int> domain){
	bool result = true;
	for (vector<int>::iterator it = M.begin(); it!=M.end(); ++it){
		if (domain.first == (*it) || domain.second == (*it)){
			result = false;
		}
	}
	return result;
}
/*
void Origami::match(Staple &s){
	int found;
	int start=0;
	int d, len;
	pair<int,int> domain;
	for (int d2=0; d2 < s.len_domains.size(); d2++){
		d = s.len_domains.size()-d2-1; //High to low because of reverse_comp.
		len = s.len_domains[d];
		found = circ_p(scaffold.seq.find(s.reverse_comp.substr(start,len)),len);
		if (found!=-1){
			domain.first = found; domain.second = found + len - 1;
			if (is_not_already_found(domain)){ 
				s.domains.push_back(domain);
				for (int i = domain.first; i < domain.second+1; i++){M.push_back(i);}
			}
		}
		start += len;
	}
}
*/
void Origami::match(Staple &s){
	string rev_comp;
	string sc_seq;
	pair<int,int> domain;
	for (int d=0; d<s.rev_seq_domains.size(); d++){
		rev_comp = s.rev_seq_domains[d];
		for (int scd = 0; scd < scaffold.seq_domains.size(); scd++){
			sc_seq = scaffold.seq_domains[scd];
			if(sc_seq == rev_comp){
				domain = scaffold.domains[scd];
				s.domains.push_back(domain);
				if (domain.first < domain.second){
					for (int i = domain.first; i < domain.second+1; i++){M.push_back(i);}
				}
				else {
					for (int i = domain.first; i < scaffold.length; i++){M.push_back(i);}
					for (int i = 0; i < domain.second+1; i++){M.push_back(i);}
				}
			}
		}
	}
}
void Origami::fill_staple_domains(){
	for (int s = 0; s < staples.size(); s++){
		match(staples[s]);
	}
}	
/*
void Origami::fill_scaffold_domains(){
	int current_nuc = scaffold.first_nuc;
	for (int scd = 0; scd < scaffold.n_domains; scd++){
		
		current_nuc += scaffold.len_domains[scd];
	}
	for (int s = 0; s < staples.size(); s++){
		match(staples[s]);
	}
}	
*/
void Origami::find_end_staple(){
	for (int s=0; s < staples.size(); s++){
		if (staples[s].domains.size() < staples[s].n_domains){
			end_staple = s;
			break;
		}
	}
}
void Origami::fix_end(){
	pair<int,int> domain;
	int max=0;
	int min=100;
	for (vector<Staple>::iterator s = staples.begin(); s != staples.end(); ++s){
		for (vector<pair<int,int> >::iterator d = s->domains.begin(); d != s->domains.end(); ++d){
			if (d->first < min)
				min = d->first;
			if (d->second > max)
				max = d->second;;
		}
	}
	domain.first=max+1;
	domain.second=min-1;
	vector<pair<int,int> >::iterator it = staples[end_staple].domains.begin();
	staples[end_staple].domains.insert(it,domain);
	
	for (int i = domain.first; i < scaffold.length; i++){M.push_back(i);}
	for (int i = 0; i < domain.second+1; i++){M.push_back(i);}
}
void Origami::fill_domain_indices(){
	vector<int> sorted;
	for (vector<Staple>::iterator s = staples.begin(); s != staples.end(); ++s){
		for (vector<pair<int,int> >::iterator d = s->domains.begin(); d != s->domains.end(); ++d){
			sorted.push_back(d->first);
		}
	}
	std::sort(sorted.begin(),sorted.end());
	for (vector<Staple>::iterator s = staples.begin(); s != staples.end(); ++s){
		for (vector<pair<int,int> >::iterator d = s->domains.begin(); d != s->domains.end(); ++d){
			for (int i = 0; i < sorted.size(); i++){
				if (d->first == sorted[i]){
					s->domain_indices.push_back(i);
					s->vertices.push_back(make_pair(i, (i+1)%sorted.size()));
				}
			}
		}
	}
}
void Origami::fill_seams(){
	for (vector<Staple>::iterator s = staples.begin(); s != staples.end(); ++s){
		s->is_seam = false;
		if (s->start_helix < 12 && s->start_helix > 1){
			if (s->start_nuc < 128 && s->start_nuc >= 95){
				s->is_seam = true;
			}
		}		
		if (s->end_helix < 12 && s->end_helix > 1){
			if (s->end_nuc < 128 && s->end_nuc > 95){
				s->is_seam = true;
			}
		}
	}
}
/*
void Origami::fill_domain_indices(){
	//Orders the domains like Frits.
	//int start_staple = 84;
	int start_domain = 89;
	//int start_nuc = staples[84].domains[0].first;
	vector<int> sorted;
	for (vector<Staple>::iterator s = staples.begin(); s != staples.end(); ++s){
		for (vector<pair<int,int> >::iterator d = s->domains.begin(); d != s->domains.end(); ++d){
			sorted.push_back(d->first);
		}
	}
	std::sort(sorted.begin(),sorted.end());
	vector<int> sorted2;
	for (int i=start_domain; i<sorted.size(); i++){
		sorted2.push_back(sorted[i]);
	}
	for (int i=0; i<start_domain; i++){
		sorted2.push_back(sorted[i]);
	}
	for (vector<Staple>::iterator s = staples.begin(); s != staples.end(); ++s){
		for (vector<pair<int,int> >::iterator d = s->domains.begin(); d != s->domains.end(); ++d){
			for (int i = 0; i < sorted2.size(); i++){
				if (d->first == sorted2[i]){
					s->domain_indices.push_back(i);
					s->vertices.push_back(make_pair(i, (i+1)%sorted2.size()));
				}
			}
		}
	}
}
*/
void Origami::fill_crossovers(){
	for (vector<Staple>::iterator s = staples.begin(); s != staples.end(); ++s){
		for (int d = 0; d<s->domains.size()-1; d++){
			if (s->is_seam && s->domains.size() == 2 /*&& d == 0*/){
				s->crossovers.push_back(make_pair(s->domains[d].first, s->domains[d+1].second));
				s->cross_indices.push_back(make_pair(s->vertices[d].first, s->vertices[d+1].second));
			}
			else if (s->is_seam && s->domains.size() == 3 && d == 1){
				s->crossovers.push_back(make_pair(s->domains[d].first, s->domains[d+1].second));
				s->cross_indices.push_back(make_pair(s->vertices[d].first, s->vertices[d+1].second));
			}
			else{
				s->crossovers.push_back(make_pair(s->domains[d].second, s->domains[d+1].first));
				s->cross_indices.push_back(make_pair(s->vertices[d].second, s->vertices[d+1].first));
			}
		}
	}
}
void Origami::fill_lengths(){
	for (vector<Staple>::iterator s = staples.begin(); s != staples.end(); ++s){
		for (vector<pair<int,int> >::iterator c = s->crossovers.begin(); c != s->crossovers.end(); ++c){
			s->len_crossovers.push_back(circ_dist(c->second,c->first,scaffold.length));
		}
	}
}
void Origami::fill_edges(){
	for (vector<Staple>::iterator s = staples.begin(); s != staples.end(); ++s){
		s->is_edge = false;
		if (s->start_nuc < 15 && s->end_nuc < 15){
			s->is_edge = true;
		}
		if (s->start_nuc > 210 && s->end_nuc > 210){
			s->is_edge = true;
		}
	}
}
void Origami::fill_helices(){
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
	/*
	for (vector<vector<int> >::iterator helix = helices.begin(); helix != helices.end(); ++helix){
		for (vector<int>::iterator x = helix->begin(); x!=helix->end(); ++x){
			cout << *x << " ";
		}
		cout << endl;
	}
	*/
}
void Origami::REVERESE_LEN_DOMAINS(){
	for (vector<Staple>::iterator s = staples.begin(); s!=staples.end(); ++s){
		std::reverse(s->len_domains.begin(),s->len_domains.end());
		std::reverse(s->seq_domains.begin(),s->seq_domains.end());
	}
}	

