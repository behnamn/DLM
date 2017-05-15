/*
 *
 *	Transition.cpp
 * 	Author: Behnam
 *
 */

#include "Transition.h"

//State Reduction Map
void reduce_state(vector<int> &state){ 
	//eg 123 -> 023 => need (almost) all cases
	int n = state.size();
	switch (n) {
		case 1: 
		break;
		case 2: 
			switch (state[0]){
				case 0:
					switch (state[1]){
						case 0:	
						break;
						case 1:	
						break;
						case 2:	
							state[1] = 1;
						break;
					}
				break;
				case 1:
					switch (state[1]){
						case 0:	
						break;
						case 1:	
						break;
						case 2:	
						break;
					}
				break;
				case 2:
					switch (state[1]){
						case 0:	
							state[0] = 1;
						break;
						case 1:	
							state[0] = 1;
							state[1] = 2;
						break;
						case 2:	
							state[0] = 1;
							state[1] = 1;
						break;
					}
				break;
			}
		break;
		case 3: 
			switch (state[0]){
				case 0:
					switch (state[1]){
						case 0:
							switch (state[2]){
								case 0: 
								break;
								case 1:
								break;
								case 2:
									state[2] = 1;
								break;
								case 3:
									state[2] = 1;
								break;
							}
						break;
						case 1:
							switch (state[2]){
								case 0: 
								break;
								case 1:
								break;
								case 2:
								break;
								case 3:
									state[2] = 2;
								break;
							}
						break;
						case 2:
							switch (state[2]){
								case 0: 
									state[1] = 1;
								break;
								case 1:
									state[1] = 1;
									state[2] = 2;
								break;
								case 2:
									state[1] = 1;
									state[2] = 1;
								break;
								case 3:
									state[1] = 1;
									state[2] = 2;
								break;
							}
						break;
						case 3:
							switch (state[2]){
								case 0: 
									state[1] = 1;
								break;
								case 1:
									state[1] = 1;
									state[2] = 2;
								break;
								case 2:
									state[1] = 1;
									state[2] = 2;
								break;
								case 3:
									state[1] = 1;
									state[2] = 1;
								break;
							}
						break;
					}
				break;
				case 1:
					switch (state[1]){
						case 0:
							switch (state[2]){
								case 0: 
								break;
								case 1:
								break;
								case 2:
								break;
								case 3:
									state[2] = 2;
								break;
							}
						break;
						case 1:
							switch (state[2]){
								case 0: 
								break;
								case 1:
								break;
								case 2:
								break;
								case 3:
									state[2] = 2;
								break;
							}
						break;
						case 2:
							switch (state[2]){
								case 0: 
								break;
								case 1:
								break;
								case 2:
									state[0] = 2;
									state[1] = 1;
									state[2] = 1;
								break;
								case 3:
								break;
							}
						break;
						case 3:
							switch (state[2]){
								case 0: 
									state[1] = 2;
								break;
								case 1:
									state[1] = 2;
								break;
								case 2:
									state[0] = 1;
									state[1] = 2;
									state[2] = 3;
								break;
								case 3:
									state[0] = 2;
									state[1] = 1;
									state[2] = 1;
								break;
							}
						break;
					}
				break;
				case 2:
					switch (state[1]){
						case 0:
							switch (state[2]){
								case 0: 
									state[0] = 1;
								break;
								case 1:
									state[0] = 1;
									state[2] = 2;
								break;
								case 2:
									state[0] = 1;
									state[2] = 1;
								break;
								case 3:
									state[0] = 1;
									state[2] = 2;
								break;
							}
						break;
						case 1:
							switch (state[2]){
								case 0: 
									state[0] = 1;
									state[1] = 2;
								break;
								case 1:
								break;
								case 2:
									state[0] = 1;
									state[1] = 2;
									state[2] = 1;
								break;
								case 3:
									state[0] = 1;
									state[1] = 2;
									state[2] = 3;
								break;
							}
						break;
						case 2:
							switch (state[2]){
								case 0: 
									state[0] = 1;
									state[1] = 1;
								break;
								case 1:
									state[0] = 1;
									state[1] = 1;
									state[2] = 2;
								break;
								case 2:
									state[0] = 1;
									state[1] = 1;
									state[2] = 1;
								break;
								case 3:
									state[0] = 1;
									state[1] = 1;
									state[2] = 2;
								break;
							}
						break;
						case 3:
							switch (state[2]){
								case 0: 
									state[0] = 1;
									state[1] = 2;
								break;
								case 1:
									state[0] = 1;
									state[1] = 2;
									state[2] = 3;
								break;
								case 2:
									state[0] = 1;
									state[1] = 2;
									state[2] = 1;
								break;
								case 3:
									state[0] = 2;
									state[1] = 1;
									state[2] = 1;
								break;
							}
						break;
					}
				break;
				case 3:
					switch (state[1]){
						case 0:
							switch (state[2]){
								case 0: 
									state[0] = 1;
								break;
								case 1:
									state[0] = 1;
									state[2] = 2;
								break;
								case 2:
									state[0] = 1;
									state[2] = 2;
								break;
								case 3:
									state[0] = 1;
									state[2] = 1;
								break;
							}
						break;
						case 1:
							switch (state[2]){
								case 0: 
									state[0] = 1;
									state[1] = 2;
								break;
								case 1:
									state[0] = 2;
								break;
								case 2:
									state[0] = 1;
									state[1] = 2;
									state[2] = 3;
								break;
								case 3:
									state[0] = 1;
									state[1] = 2;
									state[2] = 1;
								break;
							}
						break;
						case 2:
							switch (state[2]){
								case 0: 
									state[0] = 1;
									state[1] = 2;
								break;
								case 1:
									state[0] = 1;
									state[1] = 2;
									state[2] = 3;
								break;
								case 2:
									state[0] = 2;
									state[1] = 1;
									state[2] = 1;
								break;
								case 3:
									state[0] = 1;
									state[1] = 2;
									state[2] = 1;
								break;
							}
						break;
						case 3:
							switch (state[2]){
								case 0: 
									state[0] = 1;
									state[1] = 1;
								break;
								case 1:
									state[0] = 1;
									state[1] = 1;
									state[2] = 2;
								break;
								case 2:
									state[0] = 1;
									state[1] = 1;
									state[2] = 2;
								break;
								case 3:
									state[0] = 1;
									state[1] = 1;
									state[2] = 1;
								break;
							}
						break;
					}
				break;
			}
		break;
	}	
}

//Transition
Transition::Transition(){}
Transition::Transition(ST staple_, const DOM domain_, const int target_, bool cross_) :
staple(staple_), domain(domain_), target(target_), cross(cross_) {
    
    decide_possible();
    
    recalculate = true;
    
    if (target > 0) bind = true;
    else bind = false;
    
    rate = 0;
}

void Transition::decide_possible(){
    const vector<int> &state = staple->state;
    const int &p1 = domain->s_index;
    this->possible = false;
    this->crossover.second = false;
    int p2,p3;
    switch (state.size()) {
        case 1:
            switch (state[p1]){
                case 0:
                    switch (target){
                        case 0:
                            break;
                        case 1:
                            possible = true;
                            break;
                    }
                    break;
                case 1:
                    switch (target){
                        case 0:
                            possible = true;
                            break;
                        case 1:
                            break;
                    }
                    break;
            }
            break;
        case 2:
            if (p1 == 0){p2 = 1;} else {p2 = 0;}
            switch (state[p1]){
                case 0:
                    switch (state[p2]){
                        case 0:
                            switch (target){
                                case 0:
                                    break;
                                case 1:
                                    if (!cross){
                                        possible = true;
                                    }
                                    break;
                                case 2:
                                    break;
                            }
                            break;
                        case 1:
                            switch (target){
                                case 0:
                                    break;
                                case 1:
                                    if (cross){
                                        possible = true;
                                        crossover = staple->dp2cross(domain, staple->domains[p2]);
                                    }
                                    break;
                                case 2:
                                    if (!cross){
                                        possible = true;
                                    }
                                    break;
                            }
                            break;
                    }
                    break;
                case 1:
                    switch (state[p2]){
                        case 0:
                            switch (target){
                                case 0:
                                    if (!cross){
                                        possible = true;
                                    }
                                    break;
                            }
                            break;
                        case 1:
                            switch (target){
                                case 0:
                                    if (cross){
                                        possible = true;
                                        crossover = staple->dp2cross(domain, staple->domains[p2]);
                                    }
                                    break;
                            }
                            break;
                        case 2:
                            switch (target){
                                case 0:
                                    if (!cross){
                                        possible = true;
                                    }
                                    break;
                            }
                            break;
                    }
                    break;
                case 2:
                    switch (target){
                        case 0:
                            if (!cross){
                                possible = true;
                            }
                            break;
                    }
                    break;
            }
            break;
        case 3:
            if (p1 == 0){p2 = 1; p3 = 2;}
            else if (p1 == 1) {p2 = 0; p3 = 2;}
            else if (p1 == 2) {p2 = 0; p3 = 1;}
            switch (state[p1]){
                case 0:
                    switch (state[p2]){
                        case 0:
                            switch (state[p3]){
                                case 0:
                                    switch (target){
                                        case 0:
                                            break;
                                        case 1:
                                            if (!cross){
                                                possible = true;
                                            }
                                            break;
                                        case 2:
                                            break;
                                    }
                                    break;
                                case 1:
                                    switch (target){
                                        case 0:
                                            break;
                                        case 1:
                                            if (cross){
                                                possible = true;
                                                crossover = staple->dp2cross(domain, staple->domains[p3]);
                                            }
                                            break;
                                        case 2:
                                            if (!cross){
                                                possible = true;
                                            }
                                            break;
                                    }
                                    break;
                            }
                            break;
                        case 1:
                            switch (state[p3]){
                                case 0:
                                    switch (target){
                                        case 0:
                                            break;
                                        case 1:
                                            if (cross){
                                                possible = true;
                                                crossover = staple->dp2cross(domain, staple->domains[p2]);
                                            }
                                            break;
                                        case 2:
                                            if (!cross){
                                                possible = true;
                                            }
                                            break;
                                    }
                                    break;
                                case 1:
                                    if (p1 != 1) {//forbid 101->111 but allow 011->111 & 110->111
                                        switch (target){
                                            case 0:
                                                break;
                                            case 1:
                                                if (cross){
                                                    possible = true;
                                                    crossover = staple->dp2cross(domain, staple->domains[1]);
                                                }
                                                break;
                                            case 2:
                                                break;
                                        }
                                    }
                                    switch (target){
                                        case 0:
                                            break;
                                        case 1:
                                            break;
                                        case 2:
                                            if (!cross){
                                                possible = true;
                                            }
                                            break;
                                    }
                                    break;
                                case 2:
                                    switch (target){
                                        case 0:
                                            break;
                                        case 1:
                                            if (cross){
                                                possible = true;
                                                crossover = staple->dp2cross(domain, staple->domains[p2]);
                                            }
                                            break;
                                        case 2:
                                            if (cross){
                                                possible = true;
                                                crossover = staple->dp2cross(domain, staple->domains[p3]);
                                            }
                                            break;
                                        case 3:
                                            if (!cross){
                                                possible = true;
                                            }
                                            break;
                                    }
                                    break;
                            }
                            break;
                        case 2:
                            switch (state[p3]){
                                case 1:
                                    switch (target){
                                        case 0:
                                            break;
                                        case 1:
                                            if (cross){
                                                possible = true;
                                                crossover = staple->dp2cross(domain, staple->domains[p3]);
                                            }
                                            break;
                                        case 2:
                                            if (cross){
                                                possible = true;
                                                crossover = staple->dp2cross(domain, staple->domains[p2]);
                                            }
                                            break;
                                        case 3:
                                            if (!cross){
                                                possible = true;
                                            }
                                            break;
                                    }
                                    break;
                            }
                            break;
                    }
                    break;
                case 1:
                    switch (state[p2]){
                        case 0:
                            switch (state[p3]){
                                case 0:
                                    switch (target){
                                        case 0:
                                            if (!cross){
                                                possible = true;
                                            }
                                            break;
                                    }
                                    break;
                                case 1:
                                    switch (target){
                                        case 0:
                                            if (cross){
                                                possible = true;
                                                crossover = staple->dp2cross(domain, staple->domains[p3]);
                                            }
                                            break;
                                    }
                                    break;
                                case 2:
                                    switch (target){
                                        case 0:
                                            if (!cross){
                                                possible = true;
                                            }
                                            break;
                                    }
                                    break;
                            }
                            break;
                        case 1:
                            switch (state[p3]){
                                case 0:
                                    switch (target){
                                        case 0:
                                            if (cross){
                                                possible = true;
                                                crossover = staple->dp2cross(domain, staple->domains[p2]);
                                            }
                                            break;
                                    }
                                    break;
                                case 1:
                                    if (p1 != 1){//forbid 111->101 but allow 111->011 & 111->110
                                        switch (target){
                                            case 0:
                                                if (cross){
                                                    possible = true;
                                                    crossover = staple->dp2cross(domain, staple->domains[1]);
                                                }
                                                break;
                                        }
                                    }
                                    break;
                                case 2:
                                    switch (target){
                                        case 0:
                                            if (cross){
                                                possible = true;
                                                crossover = staple->dp2cross(domain, staple->domains[p2]);
                                            }
                                            break;
                                    }
                                    break;
                            }
                            break;
                        case 2:
                            switch (state[p3]){
                                case 0:
                                    switch (target){
                                        case 0:
                                            if (!cross){
                                                possible = true;
                                            }
                                            break;
                                    }
                                    break;
                                case 1:
                                    switch (target){
                                        case 0:
                                            if (cross){
                                                possible = true;
                                                crossover = staple->dp2cross(domain, staple->domains[p3]);
                                            }
                                            break;
                                    }
                                    break;
                                case 3:
                                    switch (target){
                                        case 0:
                                            if (!cross){
                                                possible = true;
                                            }
                                            break;
                                    }
                                    break;
                            }
                            break;
                    }
                    break;
                case 2:
                    switch (target){
                        case 0:
                            if (!cross){
                                possible = true;
                            }
                            break;
                    }
                    break;
                case 3:
                    switch (target){
                        case 0:
                            if (!cross){
                                possible = true;
                            }
                            break;
                    }
                    break;
            }
            break;
    }
}

void Transition::check_fully(){
    for (auto s = staple->state.begin(); s!=staple->state.end(); ++s){
        if ((*s) == 1) {
            if (s==staple->state.end()-1){
                fully = true;
                break;
            }
            else{
                continue;
            }
        }
        else {
            break;
        }
    }
}

void Transition::apply(MyGraph* G){
    fully = false;
    check_fully();
	staple->state[domain->s_index] = target;
	reduce_state(staple->state);
    check_fully();
	if (bind){
		G->bind_domain(domain);
		if(crossover.second == true){
			G->add_crossover(crossover.first);
            //G->update_embedding();
		}
		else{
		}
	}
	else{
		G->unbind_domain(domain);
		if(crossover.second == true){
			G->remove_crossover(crossover.first);
            //G->update_embedding();
		}
		else{ 
		}
	}
}

void Transition::write(ofstream& transition_file){
    transition_file << "[ ";
    for (auto it = staple->state.begin(); it!=staple->state.end(); ++it){
        if ( it - staple->state.begin() == domain->s_index)
            transition_file << "(";
        transition_file << (*it);
        if ( it - staple->state.begin() == domain->s_index)
            transition_file << ")";
    }
    transition_file << "->" << target;
    transition_file << " ]\t";
    transition_file << staple->id << "\t";
    transition_file << domain->id << "\t";
}


