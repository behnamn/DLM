/*
 *
 *	Simulation.cpp
 * 	Author: Behnam
 *
 */

#include "Simulation.h"

//General Simulation Methods
double Simulation::dG_duplex(Domain &domain) {
	double result;
	double dH = 0.;
	double dS = 0.;
	double terminal = 0;
	double T = ramp->get_T();
	string sequence = domain.seq;

	if (sequence[0] == 'A' || sequence[0] == 'T'){terminal += dH_termAT - T*dS_termAT;}
	if (sequence[sequence.size()-1] == 'A' || sequence[sequence.size()-1] == 'T'){terminal += dH_termAT - T*dS_termAT;}

	string sub;
	for (int i=0; i<sequence.size()-1; i++){
		sub.clear();
		sub += sequence[i];
		sub += sequence[i+1];
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
		else {printf ("Error! sequence not in nn database. \n"); exit (EXIT_FAILURE);}
	}
	
	double dS_salt = ((domain.length - 1) * 0.368 * salt_per_phosphate) / 1000.; // using 0.001 * 12.5 and 0.001 * 40.  (Frits)
	result = dH_init - T*dS_init + dH - T*dS + terminal - T * dS_salt;
	return result;
}
double Simulation::dG_duplex_average(Domain &domain) {
	double result;
	double T = ramp->get_T();
	double terminal = ( ( dH_termAT - T*dS_termAT ) + ( dH_termCG - T*dS_termCG ) ); // 2 * 1/2
	double dH = (domain.length - 1) * dH_average;
	double dS = (domain.length - 1) * dS_average;
	//double dS_salt = (domain.length-1) * 0.368 * log( 0.5*constants->conc_Tris + 3.3*sqrt(constants->conc_Mg) );
	//double dS_salt = (domain.length-1) * 0.368 * 3.45528339927;  //using 12.5 and 40.
	//double dS_salt = (domain.length - 1) * 0.368 * -0.944; // using 0.001 * 12.5 and 0.001 * 40.  (Frits)
	double dS_salt = ((domain.length - 1) * 0.368 * salt_per_phosphate) / 1000.; // using 0.001 * 12.5 and 0.001 * 40.  (Frits)
	//double dS_salt = 0.;
	result = dH_init - T*dS_init + dH - T*dS + terminal - T * dS_salt;
	return result;
}
double Simulation::dG_stack() {
	double result;
	double dG_average = dH_average - ramp->get_T()*dS_average; //Not sure if this is what he means in paper.
	result = constants->n_parameter * dG_average;
	//cout << result << endl;
	return result;
}	
void Simulation::print_rates(){
	//folding purpose.
	print_matrix(rates);
}
double Simulation::calc_tot_rate(){
	double result = 0;
	Edge_desc e1;
	for (int d=0; d<G->design.n_domains; d++){
		e1 = G->id_to_edge(d);
		for(vector<double>::iterator j = G->g[e1].rates.begin(); j != G->g[e1].rates.end(); ++j){
			result += *j;
		}
	}
	return result;
}


//Local Model Methods
Local::Local(Constants *constants_, MyGraph *G_, TempRamp *ramp_, Inputs *inputs_){
	ramp = ramp_;
	constants = constants_;
	G = G_;
	inputs = inputs_;
	//rates.resize(G->design.domains.size());
	/*
	affected.resize(rates.size());
	for (int i = 0; i < rates.size(); i++){
		affected[i] = i;
	}
	*/
}
double Local::dG_shape(Crossover &crossover) {
	double result;
	double E;
	E = lambda_ss * lambda_ss + G->total_weight(crossover.v_a, crossover.v_b);
	result = -(gas_constant * ramp->get_T()) * constants->gamma_parameter * log(constants->C_parameter / E);
	//cout << crossover.v_a << "\t" << crossover.v_b << "\t" << G->total_weight(crossover.v_a, crossover.v_b) << "\t" << ramp->get_T() << "\t" << E << "\t" << result << endl;
	return result;
}
void Local::fill_rate(int d){
	Domain domain = G->design.domains[d];
	Edge_desc e1 = G->id_to_edge(d);
	Edge_desc stack_edge;
	//Should I put: 
	//g[e1].set_state[d];
	//g[e1].set_changes[d]; 
	//here?
	G->g[e1].rates.clear();
	(G->g[e1].rates).resize(G->g[e1].changes.size());

	vector<int> state = G->g[e1].state;
	vector<int> changes = G->g[e1].changes;
	vector<int> pos_cross = G->g[e1].pos_cross;
	int p1 = G->g[e1].pos;
	double dG;
	double RT = gas_constant * ramp->get_T();
	Crossover crossover;
	int cross_dom;

	for (int i=0; i<changes.size(); i++){
		dG = 0;
		if ( changes[i] > 0 ){//Binding
			if(pos_cross[i] > -1) { // same staple.
				cross_dom = G->find_interacting_domain(d,pos_cross[i]);
				crossover = G->design.crossovers[G->design.dpair_to_crossover(make_pair(d,cross_dom))];
				dG += dG_shape(crossover);
				G->g[e1].rates[i] = pow(10,3) * k_plus * exp( -dG / RT ); 
			}
			else{
				G->g[e1].rates[i] = k_plus * constants->conc_staple; 
			}
		}
		if ( changes[i] == 0 ){//Unbinding (rates are the same in local model). Can do pos_cross[i] > -1 to differentiate.
			if (inputs->seq_dependence){
				dG += dG_duplex(domain);
			}
			else{
				dG += dG_duplex_average(domain);
			}
			for (vector<int>::iterator it = domain.stack_domains.begin(); it != domain.stack_domains.end(); ++it){
				stack_edge = G->id_to_edge(*it);
				if (G->g[stack_edge].type == 'd'){
					dG += dG_stack();
				}
			}
			G->g[e1].rates[i] = pow(10,3) * k_plus * exp( dG / RT );
		}
	}

	//this->rates.push_back(G->g[e1].rates);
}
void Local::fill_rates() {
	//rates.clear();
	for (int i=0; i<G->design.n_domains; i++){
		fill_rate(i);
	}
}
void Local::run() {
	ofstream occupancy_file;
	string T_string;
	int T_int;
	int dummy = 0;
	occupancy_file.open(inputs->occupancy_file_name);
	typedef boost::minstd_rand base_generator_type;
	base_generator_type generator(inputs->seed);
	uniform_real<> uni_dist(0,1);
	variate_generator<base_generator_type&, uniform_real<> > uni(generator, uni_dist);
    double r1, r2, tau, min, max, total_rate, T_now, T_past;
	int next_edge, reaction_type;
	Edge_desc e1;
	ramp->set_time(0.);
	vector<int> bound_counts;
	bound_counts.resize(inputs->staple_species.size());
	while (ramp->current_t < ramp->t_max){
		T_now = ramp->get_T();
		/*
		if ( abs(T_now-T_past) > 0.00000000001){ 
			T_int = (int)centigrade(T_now);
			T_string = to_string(T_int);
			G->write_gv(HUS+"_T_"+T_string);
			G->write_gv_circle(HUS+"_T_"+T_string);
		}
		if ( abs( centigrade(T_now) - 65. ) < 0.2){ 
			dummy += 1;
			if (dummy%100 == 0){
				dummy_string = to_string(dummy);
				T_int = (int)centigrade(T_now);
				T_string = to_string(T_int);
				G->write_gv(HUS+"_T_"+T_string+"_"+dummy_string);
				G->write_gv_circle(HUS+"_T_"+T_string+"_"+dummy_string);
			}
		}
		*/
		fill_rates();
		r1 = uni(); r2 = uni();
		total_rate = calc_tot_rate(); 
		min = 0.; //check whether this can be outside this loop.
		max = 0.;
		for (int i=0; i<G->design.n_domains; i++){ 
			e1 = G->id_to_edge(i);
			for (int j=0; j<G->g[e1].rates.size(); j++){ 
				max = max + G->g[e1].rates[j]/total_rate; 
				if (r2 >= min && r2 < max){
					next_edge = i;
					reaction_type = j;
					break; //need to break twice
				}
				min = max;
			}
			if (r2 >= min && r2 < max){
				break;
			}
		}
		tau = (1./total_rate)*log(1./r1); //Total rate is very small when mostly bound at low T (upto 60C)! This is causing problems by giving large tau.		
		if (tau > ramp->cool_rate){continue;}
		occupancy_file << ramp->current_t << "\t";
	   	occupancy_file << centigrade(ramp->get_T()) << "\t";
		occupancy_file << next_edge << "\t";
	   	//occupancy_file << G->get_bound_dom_count() << "\t";
	   	occupancy_file << G->get_bound_nuc_count() << "\t";
		G->get_bound_dom_counts(bound_counts);
		for (vector<int>::iterator it = bound_counts.begin(); it != bound_counts.end(); ++it){
			occupancy_file << *it << "\t";
		}
		/*
		e1 = G->id_to_edge(next_edge);
		occupancy_file << "E1:\t";
		for (int i=0; i < G->g[e1].state.size(); i++){
			occupancy_file << G->g[e1].state[i];
		}	occupancy_file << "\t";
	   	occupancy_file	<< G->g[e1].pos << "\t";
	   	occupancy_file	<< G->g[e1].length << "\t";
	   	occupancy_file	<< G->g[e1].rates[reaction_type] << "\t";
	    occupancy_file	<< total_rate << "\t";
		*/
	    occupancy_file << "\n";
		G->make_transition(next_edge,reaction_type);
		ramp->move_time(tau); //this causes segmentation fault if the current time after this is longer that total time. But fixes it in the function itself.
		T_past = T_now;
	}
	occupancy_file.close();
}
/*
vector<double> Local::calc_rate(int d){
	vector<double> result;
	double dG = 0;
	Domain domain = G->design.domains[d];
	Edge_desc edge = G->id_to_edge(d);
	Edge_desc cross_edge;
	Edge_desc stack_edge;
	// Binding
	if (G->g[edge].type == 's') {
		if(domain.cross_domains.empty()){ // 0 --> 1
			result.push_back(k_plus * constants->conc_staple);
		}
		else{
			for (vector<int>::iterator it = domain.cross_domains.begin(); it != domain.cross_domains.end(); ++it) {
				cross_edge = G->id_to_edge(*it);
				if (G->g[cross_edge].type == 's') { // 00 --> 01
					result.push_back(k_plus * constants->conc_staple);
				}
				else if (G->g[cross_edge].type == 'd') { // 01 --> 11 or 12   
					//Can check s22 case by checking whether the crossover exists.
					int c = domain.crossover_ids[0]; //needs updating for multiple crossovers
					Crossover crossover = G->design.crossovers[c];
					dG += dG_shape(crossover);
					result.push_back( pow(10,3)* k_plus * exp( -dG / (gas_constant * ramp->get_T()) ) );
					result.push_back(k_plus * constants->conc_staple); //12 case (different staples)
					//result = k_plus * exp( -dG / (gas_constant * ramp->get_T()) );
				}
				else{printf ("Error!\n"); exit (EXIT_FAILURE);}
			}
		}
	}
	// Unbinding
	else if (G->g[edge].type == 'd') {
		if(domain.cross_domains.empty()){ // 1 --> 0
			dG += dG_duplex(domain); 
		}
		else{
			for (vector<int>::iterator it = domain.cross_domains.begin(); it != domain.cross_domains.end(); ++it) {
				cross_edge = G->id_to_edge(*it);
				if (G->g[cross_edge].type == 's') { // 01 --> 00
					dG += dG_duplex(domain);
				}
				else if (G->g[cross_edge].type == 'd') { // 11 --> 01
					//Two different rates here as well. 
					//DANGER! DANGER! DANGER! DANGER! DANGER! 
					//Actually, the rates are the same in local model.
					dG += dG_duplex(domain);
				}
				else{printf ("Error!\n"); exit (EXIT_FAILURE);}
			}
		}
		for (vector<int>::iterator it = domain.stack_domains.begin(); it != domain.stack_domains.end(); ++it){
			stack_edge = G->id_to_edge(*it);
			if (G->g[stack_edge].type == 'd'){
				dG += dG_stack();
			}
		}
		result.push_back( pow(10,3) * k_plus * exp( dG / (gas_constant * ramp->get_T() ) ) );
		//result = constants->k_plus * exp( dG / (constants->gas_constant * ramp->get_T() ) );
	}
	else{printf ("Error!\n"); exit (EXIT_FAILURE);}
	
	return result;
}
void Local::fill_rates() {
	//rates.clear();
	//for (int d=0; d<G->design.domains.size(); d++){
		//cout << calc_rate(d).size() << endl;
	//	rates.push_back(calc_rate(d));
	//}
	//for (int d=0; d<rates.size(); d++){
		//cout << calc_rate(d).size() << endl;
		//cout << d << endl;
	//	rates[d] = calc_rate(d);
	//}
	int d;
	for (int i=0; i<affected.size(); i++){
		//cout << calc_rate(d).size() << endl;
		//cout << d << endl;
		d = affected[i];
		rates[d] = calc_rate(d);
	}
}
void Local::run(string filename_, int seed) {
	ofstream change_file;
	string filename = filename_+".txt";
	change_file.open(filename);
	change_file << "seed= " << seed << endl;
	change_file << "cool_rate[s/K]= " << ramp->cool_rate << endl;
	constants->write_params(change_file);
	typedef boost::minstd_rand base_generator_type;
	base_generator_type generator(seed);
	uniform_real<> uni_dist(0,1);
	variate_generator<base_generator_type&, uniform_real<> > uni(generator, uni_dist);
    double r1, r2, tau, min, max, total_rate, T_now, T_past;
	int next_edge, reaction_type;
	ramp->set_time(0.);
	while (ramp->current_t < ramp->t_max){
		T_now = ramp->get_T();
		bool add = true;
		if ( abs(T_now-T_past) > 0.00000000001){ 
			affected.clear();
			affected.resize(rates.size());
			for (int i = 0; i < rates.size(); i++){
				affected[i] = i;
			}
		}
		sort( affected.begin(), affected.end() );
		affected.erase( unique( affected.begin(), affected.end() ), affected.end() );
		//for (int i=0; i<affected.size(); i++){
			//cout << affected[i] << " ";
		//}
		//cout << "\n\n";
		//print_rates();
		fill_rates();
		affected.clear();
		r1 = uni(); r2 = uni();
		total_rate = calc_tot_rate(); 
		min = 0.; //check whether this can be outside this loop.
		max = 0.;
		for (int i=0; i<rates.size(); i++){ 
			for (int j=0; j<rates[i].size(); j++){ 
				max = max + rates[i][j]/total_rate; 
				if (r2 >= min && r2 < max){
					next_edge = i;
					reaction_type = j;
					break; //need to break twice
				}
				min = max;
			}
			if (r2 >= min && r2 < max){
				break;
			}
		}
		if (reaction_type == 1) {add = false;}
		//G->set_edge_weights(); 
		tau = (1./total_rate)*log(1./r1); //Total rate is very small when mostly bound at low T (upto 60C)! This is causing problems by giving large tau.		
		if (tau > ramp->cool_rate){continue;}
		change_file << ramp->current_t << "\t" << centigrade(ramp->get_T()) << "\t" << next_edge << "\t" << G->get_bound_count() << "\n";
		G->make_transition(next_edge,add,affected);
		ramp->move_time(tau); //this causes segmentation fault if the current time after this is longer that total time. But fixes it in the function itself.
		T_past = T_now;
	}
	change_file.close();
}
*/
