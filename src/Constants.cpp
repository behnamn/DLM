/*
 *
 *	Constants.cpp
 * 	Author: Behnam
 *
 */

#include "Constants.h"


void Constants::change_gamma(double gamma_){
	if (abs(gamma_-1.5) < 0.000000000000001){
		gamma_parameter = 1.5;
		C_parameter = 6.7 * pow(10,-19);
	}
	else if (abs(gamma_-2.5) < 0.000000000000001){
		gamma_parameter = 2.5;
		C_parameter = 2.8 * pow(10,-18);
	}
	else if (abs(gamma_-3.5) < 0.00000000000001){
		gamma_parameter = 3.5;
		C_parameter = 5.2 * pow(10,-18);
	}
	else {printf ("Error! Value of gamma not supported.\n"); exit (EXIT_FAILURE);}
}

void Constants::write_params(ofstream &file_) {
	file_ << "y= " << gamma_parameter << "\nn= " << n_parameter << "\nconc= " << conc_staple << endl;
}

Constants::Constants () { //conc_ in nM
	change_gamma(2.5);
	conc_staple = 20. * pow(10,-6); // mol m-3
	n_parameter = 2.;
}

Constants::Constants (double y_, double n_, double conc_) { //conc_ in nM
	change_gamma(y_);
	conc_staple = conc_ * pow(10,-6);; // mol m-3
	n_parameter = n_;
}



