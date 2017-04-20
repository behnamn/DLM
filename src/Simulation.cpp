/*
 *
 *	Simulation.cpp
 * 	Author: Behnam
 *
 */

#include "Simulation.h"

//General Simulation Methods
double Simulation::dG_duplex(Domain* domain) {
	double terminal = 0;
	double T = ramp->get_T();
	if (domain->seq[0] == 'A' || domain->seq[0] == 'T'){
		terminal += dH_termAT - T*dS_termAT;
	}
	if (domain->seq[domain->length-1] == 'A' || domain->seq[domain->length-1] == 'T'){
		terminal += dH_termAT - T*dS_termAT;
	}
	double dS_salt = (domain->length - 1) * salt_per_phosphate_hack; // using 0.001 * 12.5 and 0.001 * 40.  (Frits)
	return dH_init - T*dS_init + domain->dH - T*domain->dS + terminal - T*dS_salt;
}
double Simulation::dG_duplex_average(Domain* domain) {
	double result;
	double T = ramp->get_T();
	double terminal = ( ( dH_termAT - T*dS_termAT ) + ( dH_termCG - T*dS_termCG ) ); // 2 * 1/2
	double dH = (domain->length - 1) * dH_average;
	double dS = (domain->length - 1) * dS_average;
	//double dS_salt = (domain.length-1) * 0.368 * log( 0.5*constants->conc_Tris + 3.3*sqrt(constants->conc_Mg) );
	//double dS_salt = (domain.length-1) * 0.368 * 3.45528339927;  //using 12.5 and 40.
	//double dS_salt = (domain.length - 1) * 0.368 * -0.944; // using 0.001 * 12.5 and 0.001 * 40.  (Frits)
	double dS_salt = (domain->length - 1) * salt_per_phosphate_hack; // using 0.001 * 12.5 and 0.001 * 40.  (Frits)
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

//Local Model Methods
double Local::dG_shape(Crossover* crossover) {
	double result;
	double E;
	E = lambda_ss * lambda_ss + G->total_weight(crossover->vertices.first, crossover->vertices.second);
	result = -(gas_constant * ramp->get_T()) * constants->gamma_parameter * log(constants->C_parameter / E);
	return result;
}
Local::Local(Constants *constants_, Design* design_, MyGraph *G_, TempRamp *ramp_, Inputs *inputs_){
	ramp = ramp_;
	design = design_;
	constants = constants_;
	G = G_;
	inputs = inputs_;
	maps = MyMaps();
}
void Local::fill_transitions(){
	transitions.clear();
	total_rate = 0.;
	vector<pair<int,int> > dummy;
	for (vector<Staple>::iterator st = design->staples.begin(); st!=design->staples.end(); ++st){
		for (vector<Domain*>::iterator dom = st->domains.begin(); dom!=st->domains.end(); ++dom){
			dummy = maps.transition_map[ make_pair( st->state, (*dom)->s_index ) ];
			for (auto pa = dummy.begin(); pa!=dummy.end(); ++pa){
				transitions.push_back(Transition(&(*st), *dom, pa->first, pa->second, &maps));
			}
		}
	}
	double dG;
	double RT = gas_constant * ramp->get_T();
	for (auto tr = transitions.begin(); tr!=transitions.end(); ++tr){
		dG=0;
		if (tr->bind){
			if(tr->crossover.second == true){
				dG += dG_shape(tr->crossover.first);
				tr->rate = pow(10,3) * k_plus * exp( -dG / RT ); 
			}
			else{
				tr->rate = k_plus * constants->conc_staple; 
			}
		}
		else{
			if(tr->crossover.second == true){
				if (inputs->seq_dependence){
					dG += dG_duplex(tr->domain);
				}
				else{
					dG += dG_duplex_average(tr->domain);
				}
				for (auto stack = tr->domain->stack_domains.begin(); stack != tr->domain->stack_domains.end(); ++stack){
					//if (*((*stack)->state) > 0){
					if ( tr->staple->state[((*stack)->s_index)] > 0){
						dG += dG_stack();
					}
				}
				tr->rate = pow(10,3) * k_plus * exp( dG / RT );
			}
			else{ //same in local model.
				if (inputs->seq_dependence){
					dG += dG_duplex(tr->domain);
				}
				else{
					dG += dG_duplex_average(tr->domain);
				}
				for (auto stack = tr->domain->stack_domains.begin(); stack != tr->domain->stack_domains.end(); ++stack){
					//if (*((*stack)->state) > 0){
					if ( tr->staple->state[((*stack)->s_index)] > 0){
						dG += dG_stack();
					}
				}
				tr->rate = pow(10,3) * k_plus * exp( dG / RT );
			}
		}
		total_rate += tr->rate;
	}
}
void Local::run() {
	//clock_t t0;
   	//double total_time;
	//t0 = clock();
	clock_t t1, t2;
	double time_per_step;
	ofstream occupancy_file;
	occupancy_file.open(inputs->occupancy_file_name);
	Transition* next;
    double r1, r2, tau, min, max, T_now, T_past;
	typedef boost::minstd_rand base_generator_type;
	base_generator_type generator(inputs->seed);
	uniform_real<> uni_dist(0,1);
	variate_generator<base_generator_type&, uniform_real<> > uni(generator, uni_dist);
	ramp->set_time(0.);
	while (ramp->current_t < ramp->t_max){
		t1 = clock();
		T_now = ramp->get_T();
		fill_transitions();
		r1 = uni(); r2 = uni();
		min = 0.; 
		max = 0.;
		for (auto tr = transitions.begin(); tr!=transitions.end(); ++tr){
			max += tr->rate/total_rate; 
			if (r2 >= min && r2 < max){
				next = &*(tr);
				break; 
			}
			min = max;
		}
		tau = (1./total_rate)*log(1./r1);		
		if (tau > ramp->cool_rate){continue;}

		occupancy_file << ramp->current_t << "\t";
	   	occupancy_file << centigrade(ramp->get_T()) << "\t";
		occupancy_file << "[ ";
		for (auto it = next->staple->state.begin(); it!=next->staple->state.end(); ++it){
			if ( it - next->staple->state.begin() == next->domain->s_index)
				occupancy_file << "(";
			occupancy_file << (*it);
			if ( it - next->staple->state.begin() == next->domain->s_index)
				occupancy_file << ")";
		}	
		occupancy_file << "->";
		for (auto it = next->final_state.begin(); it!=next->final_state.end(); ++it){
			if ( it - next->final_state.begin() == next->domain->s_index)
				occupancy_file << "(";
			occupancy_file << (*it);
			if ( it - next->final_state.begin() == next->domain->s_index)
				occupancy_file << ")";
		}	
		occupancy_file << " ]\t";
		occupancy_file << next->domain->id << "\t";
		occupancy_file << next->crossover.second << "\t";
		occupancy_file << G->num_bound_H << "\t";
		occupancy_file << G->num_bound_U << "\t";
		occupancy_file << G->num_bound_S << "\t";
		occupancy_file << G->num_bound_domains << "\t";
		occupancy_file << G->num_bound_nucs << "\t";

		next->apply(G);
		ramp->move_time(tau); 
		T_past = T_now;
		t2 = clock();
		time_per_step = (t2-t1) / (double) CLOCKS_PER_SEC;
		//total_time = (t2-t0) / (double) CLOCKS_PER_SEC;
		occupancy_file << time_per_step << "\t";
	    occupancy_file << "\n";
	}
	occupancy_file.close();
}
