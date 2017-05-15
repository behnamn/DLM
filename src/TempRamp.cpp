/*
 *
 *	TempRamp.cpp
 * 	Author: Behnam
 *
 */

#include "TempRamp.h"


//General TempRamp Methods
TempRamp::TempRamp(){}
void TempRamp::_fill_anneal(){
	double Temp;
	double const_T;
	for (Temp = T_high; Temp > T_low; Temp -=1){
		for (int i=0; i< cool_rate; i++){
			if (i % inputs->const_T_interval == 0){
				const_T = Temp - (i/cool_rate);
			}
			_ramp.push_back(const_T);
		}
	}
}
void TempRamp::_fill_melt(){
	double Temp;
	double const_T;
	for (Temp = T_low; Temp < T_high; Temp +=1){
		for (int i=0; i< cool_rate; i++){
			if (i % inputs->const_T_interval == 0){
				const_T = Temp + (i/cool_rate);
			}
			_ramp.push_back(const_T);
		}
	}
}
void TempRamp::set_time(double current_t_){
	current_t = current_t_;
	if (current_t < t_max){ 
		_current_t = current_t;
		current_T = _ramp[_current_t];
        if (abs(previous_T-current_T) > 0.0000000000000000000001){
            T_was_changed = true;
        }
        else{
            T_was_changed  = false;
        }
        previous_T = current_T;
	}
	else {
		cout << "Simulation time exceeded so cannot update the temperature in TempRamp.\n";
	} 
}
void TempRamp::move_time(double delta_t){
	current_t = current_t + delta_t;
	if (current_t < t_max){ 
		_current_t = current_t;
		current_T = _ramp[_current_t];
        if (abs(previous_T-current_T) > 0.000000000000000000001){
            T_was_changed = true;
        }
        else{
            T_was_changed  = false;
        }
        previous_T = current_T;
	}
	else {
		cout << "Simulation time exceeded so cannot update the temperature in TempRamp.\n";
	} 
}
void TempRamp::print_ramp(){
	//print_vec(_ramp);
	for (vector<double>::iterator it = _ramp.begin(); it!=_ramp.end(); ++it){
		cout << it - _ramp.begin() << "\t" << centigrade(*it) << endl;
	}
}
double TempRamp::get_T(){
	return current_T;
}
void TempRamp::set_temp(double current_T_){
	current_T = kelvin(current_T_);
}


//AnnealMelt Methods
AnnealMelt::AnnealMelt(Inputs * inputs_){
    this->inputs = inputs_;
    n_cycles = inputs->n_cycles;
    if (inputs->anneal == true) {anneal = true;}
    else {anneal = false;}
    if (inputs->melt == true) {melt = true;}
    else {melt = false;}
    T_high = kelvin(inputs->max_temp);
    T_low = kelvin(inputs->min_temp);
    cool_rate = Cpm2spC(inputs->cool_rate);
    t_max_in_each = abs(T_high-T_low) * cool_rate;
    if (anneal && melt) {t_max = 2. * n_cycles * t_max_in_each;}
    else if(anneal && !melt) {t_max = n_cycles * t_max_in_each;}
    else if(!anneal && melt) {t_max = n_cycles * t_max_in_each;}
    else{
        printf ("Please select anneal, melt or both to fill ramp. \n");
        exit (EXIT_FAILURE);
    }
    _fill_ramp();
    previous_T = -1.;
    set_time(0.);
}
void AnnealMelt::_fill_ramp(){
    for (int i=0; i<n_cycles; i++){
        if (anneal) _fill_anneal();
        if (melt) _fill_melt();
    }
}


//Anneal Methods
Anneal::Anneal(Inputs * inputs_) {
	this->inputs = inputs_;
    n_cycles = inputs->n_cycles;
    if (inputs->anneal == true) {anneal = true;}
    else {anneal = false;}
    if (inputs->melt == true) {melt = true;}
    else {melt = false;}
    if(anneal && !melt && n_cycles==1){}
    else{
        printf ("This ramp is only suitable for single anneal. \n");
        exit (EXIT_FAILURE);
    }
	T_high = kelvin(inputs->max_temp);
	T_low = kelvin(inputs->min_temp);
	cool_rate = Cpm2spC(inputs->cool_rate);
	t_max_in_each = abs(T_high-T_low) * cool_rate;
	t_max = n_cycles * t_max_in_each;
	_fill_ramp();
    previous_T = -1.;
    set_time(0.);
}
void Anneal::_fill_ramp(){
	if (anneal){
		_fill_anneal();
	}
	else {
		cout << "Anneal ramp selected with wrong temperature gradient!" << endl;
	}	
}


//Melt Methods
Melt::Melt(Inputs * inputs_){
	this->inputs = inputs_;
    n_cycles = inputs->n_cycles;
    if (inputs->anneal == true) {anneal = true;}
    else {anneal = false;}
    if (inputs->melt == true) {melt = true;}
    else {melt = false;}
    if(!anneal && melt && n_cycles==1){}
    else{
        printf ("This ramp is only suitable for single melt. \n");
        exit (EXIT_FAILURE);
    }
	T_high = kelvin(inputs->max_temp);
	T_low = kelvin(inputs->min_temp);
	cool_rate = Cpm2spC(inputs->cool_rate);
	t_max_in_each = abs(T_high-T_low) * cool_rate;
	t_max = n_cycles * t_max_in_each;
	_fill_ramp();
    previous_T = -1.;
    set_time(0.);
}
void Melt::_fill_ramp(){
	if (melt){
        _fill_melt();
	}
	else {
		cout << "Melt ramp selected with wrong temperature gradient!" << endl;
    }
}


