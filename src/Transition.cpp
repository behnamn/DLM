/*
 *
 *	Transition.cpp
 * 	Author: Behnam
 *
 */

#include "Transition.h"

//MyMaps
MyMaps::MyMaps(){
	fill_state_map();
	fill_transition_map();
}

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
void MyMaps::fill_state_map(){
	vector<int> initial;
	vector<int> reduced;
	//Single domain
	for (int i=0; i<2; i++){
		initial.push_back(i);
		reduced = initial;
		reduce_state(reduced);
		state_map.insert(make_pair(initial,reduced));
		initial.clear();
	}
	//Double domain
	for (int i=0; i<3; i++){
		for (int j=0; j<3; j++){
			initial.push_back(i);
			initial.push_back(j);
			reduced = initial;
			reduce_state(reduced);
			state_map.insert(make_pair(initial,reduced));
			initial.clear();
		}
	}
	//Triple domain
	for (int i=0; i<4; i++){
		for (int j=0; j<4; j++){
			for (int k=0; k<4; k++){
				initial.push_back(i);
				initial.push_back(j);
				initial.push_back(k);
				reduced = initial;
				reduce_state(reduced);
				state_map.insert(make_pair(initial,reduced));
				initial.clear();
			}
		}
	}
	//Print
	for (auto it = state_map.begin(); it!=state_map.end(); ++it){
		for (auto fit = it->first.begin(); fit!=it->first.end(); ++fit){
			cout << *(fit);
		}
		cout << "\t-->\t";
		for (auto sit = it->second.begin(); sit!=it->second.end(); ++sit){
			cout << *(sit);
		}
		cout << "\n";
	}
	vector<int> a {3,1,2}; 
	for (auto sit = state_map[a].begin(); sit!=state_map[a].end(); ++sit){
		cout << *(sit);
	}
	cout << "\n";
	/*
	*/
}

//Transition Map
vector<pair<int,int> > get_changes(vector<int> state, int p1){ 
	int n = state.size();
	int p2, p3; //positions
 	pair<int,int> result;
	vector<pair<int,int> > Results;
	switch (n) {
		case 1: 
			switch (state[p1]){
				case 0: 
					result.first=1; result.second=-1;
					Results.push_back(result);
				break;
				case 1:
					result.first=0; result.second=-1;
					Results.push_back(result);
				break;
			}
		break;
		case 2: 
			if (p1 == 0){p2 = 1;} else {p2 = 0;}
			switch (state[p1]){
				case 0:
					switch (state[p2]){
						case 0:	
							result.first=1; result.second=-1;
							Results.push_back(result);
						break;
						case 1:	
							result.first=1; result.second=p2;
							Results.push_back(result);
							result.first=2; result.second=-1;
							Results.push_back(result);
						break;
					}
				break;
				case 1:
					switch (state[p2]){
						case 0:	
							result.first=0; result.second=-1;
							Results.push_back(result);
						break;
						case 1:	
							result.first=0; result.second=p2;
							Results.push_back(result);
						break;
						case 2:	
							result.first=0; result.second=-1;
							Results.push_back(result);
						break;
					}
				break;
				case 2:
					result.first=0; result.second=-1;
					Results.push_back(result);
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
									result.first=1;	result.second=-1;
									Results.push_back(result);
								break;
								case 1:
									result.first=1;	result.second=p3;
									Results.push_back(result);
									result.first=2;	result.second=-1;
									Results.push_back(result);
								break;
							}
						break;
						case 1:
							switch (state[p3]){
								case 0: 
									result.first=1; result.second=p2;
									Results.push_back(result);
									result.first=2;	result.second=-1;
									Results.push_back(result);
								break;
								case 1:
									if (p1 != 1) {//forbid 101->111 but allow 011->111 & 110->111 
										result.first=1; result.second=1;
										Results.push_back(result);
									}
									result.first=2; result.second=-1; 
									Results.push_back(result);
								break;
								case 2:
									result.first=1; result.second=p2;
									Results.push_back(result);
									result.first=2; result.second=p3;
									Results.push_back(result);
									result.first=3; result.second=-1;
									Results.push_back(result);
								break;
							}
						break;
						case 2:
							switch (state[p3]){
								case 1: 
									result.first=1; result.second=p3;
									Results.push_back(result);
									result.first=2; result.second=p2;
									Results.push_back(result);
									result.first=3; result.second=-1;
									Results.push_back(result);
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
									result.first=0;	result.second=-1;
									Results.push_back(result);
								break;
								case 1:
									result.first=0;	result.second=p3;
									Results.push_back(result);
								break;
								case 2:
									result.first=0;	result.second=-1;
									Results.push_back(result);
								break;
							}
						break;
						case 1:
							switch (state[p3]){
								case 0: 
									result.first=0; result.second=p2;
									Results.push_back(result);
								break;
								case 1:
									if (p1 != 1){//forbid 111->101 but allow 111->011 & 111->110 
										result.first=0; result.second=1;
										Results.push_back(result);
									}
								break;
								case 2:
									result.first=0; result.second=p2;
									Results.push_back(result);
								break;
							}
						break;
						case 2:
							switch (state[p3]){
								case 0: 
									result.first=0; result.second=-1;
									Results.push_back(result);
								break;
								case 1: 
									result.first=0; result.second=p3;
									Results.push_back(result);
								break;
								case 3: 
									result.first=0; result.second=-1;
									Results.push_back(result);
								break;
							}
						break;
					}
				break;
				case 2:
					result.first=0; result.second=-1;
					Results.push_back(result);
				break;
				case 3:
					result.first=0; result.second=-1;
					Results.push_back(result);
				break;
			}
		break;
	}	
	return Results;
}
void MyMaps::fill_transition_map(){
	vector<vector<int> > unique;
	for (auto it = state_map.begin(); it!=state_map.end(); ++it){
		unique.push_back(it->second);
	}
	std::set<vector<int> > s(unique.begin(), unique.end());
	for (auto it = s.begin(); it!=s.end(); ++it){
		for (int p = 0; p<it->size(); p++){
			transition_map.insert(make_pair(make_pair(*(it),p), get_changes(*(it),p) ));
		}
	}
	//Print
	for (auto it = transition_map.begin(); it!=transition_map.end(); ++it){
		cout << "{";
		for(auto s = it->first.first.begin(); s!=it->first.first.end(); ++s){
			if (s - it->first.first.begin() == it->first.second) cout <<"(";
			cout << *s;
			if (s - it->first.first.begin() == it->first.second) cout <<")";
		}
		cout << "}\t";
		//cout << it->first.second << ":\t";
		for(auto s = it->second.begin(); s!=it->second.end(); ++s){
			cout << "[" << s->first << ", " << s->second << "]\t";
		}
		cout << "\n";
	}
	/*
	*/
}


//Transition
Transition::Transition(){}
Transition::Transition(const ST staple_, const DOM domain_, int target, int pos_cross, MyMaps* mymaps_) : staple(staple_), domain(domain_), maps(mymaps_) {
	initialise(target, pos_cross);
}
void Transition::initialise(int target, int pos_cross){
	final_state = staple->state;
	final_state[domain->s_index] = target;
	if (target > 0) bind = true;
	else bind = false;
	if(pos_cross>-1){
		crossover = staple->dp2cross(domain, staple->domains[pos_cross]);
	}
	else{crossover.second = false;}
}
void Transition::apply(MyGraph* G){
	staple->state[domain->s_index] = final_state[domain->s_index];
	staple->state = maps->state_map[final_state];
	//reduce_state(staple->state);
	if (bind){
		G->bind_domain(domain);
		if(crossover.second == true){
			G->add_crossover(crossover.first);
		}
		else{
		}
	}
	else{
		G->unbind_domain(domain);
		if(crossover.second == true){
			G->remove_crossover(crossover.first);
		}
		else{ 
		}
	}
}





