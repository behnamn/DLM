/*
 *
 *	MyGraph.cpp
 * 	Author: Behnam
 *
 */

#include "MyGraph.h"


MyGraph::MyGraph (Design design_){
	design = design_;
	add_vertices();
	add_domains();
	reset_all_states();
	for (int d=0; d<design.n_domains; d++){
		set_changes(d);
	}
}

void MyGraph::reduce_state(vector<int> &state){ //Can put in beginning of set_changes. eg. 122 -> 211
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
void MyGraph::reduce_state2(vector<int> &state){ //Can put in beginning of set_changes. eg. 122 -> 211
	int n = state.size();
	int a, b, c;
	switch (n) {
		case 1: 
		break;
		case 2: 
			a=state[0]; b=state[1];
			if (a>0){
				if (b>0){
					if(a==b){
						state[0]=1; state[1]=1;	
					}
				}
			}
		break;
		case 3: 
			a=state[0]; b=state[1]; c=state[3];
			if (a>0){
				if (b>0){
					if (c>0){
					}
				}
			}
		break;
	}	
}
void MyGraph::set_changes(int d){
	if (d>design.domains.size()-1){ 
		printf ("Error! crossover cannot have rate.\n"); exit (EXIT_FAILURE); 
	}
	Domain domain = design.domains[d];
	Edge_desc e1 = id_to_edge(d);
	reduce_state(g[e1].state);
	vector<int> state = g[e1].state;
	int n = state.size();
	int p1 = g[e1].pos;	int p2, p3; //positions
	int d1, d2, d3; //domain ids
	
	g[e1].changes.clear();
	g[e1].pos_cross.clear();

	switch (n) {
		case 1: 
			switch (state[p1]){
				case 0: 
					g[e1].changes.push_back(1); g[e1].pos_cross.push_back(-1);
				break;
				case 1:
					g[e1].changes.push_back(0); g[e1].pos_cross.push_back(-1);
				break;
			}
		break;
		case 2: 
			if (p1 == 0){p2 = 1;} else {p2 = 0;}
			switch (state[p1]){
				case 0:
					switch (state[p2]){
						case 0:	
							g[e1].changes.push_back(1); g[e1].pos_cross.push_back(-1);
						break;
						case 1:	
							g[e1].changes.push_back(1); g[e1].pos_cross.push_back(p2);
							g[e1].changes.push_back(2); g[e1].pos_cross.push_back(-1);
						break;
					}
				break;
				case 1:
					switch (state[p2]){
						case 0:	
							g[e1].changes.push_back(0); g[e1].pos_cross.push_back(-1);
						break;
						case 1:	
							g[e1].changes.push_back(0); g[e1].pos_cross.push_back(p2);
						break;
						case 2:	
							g[e1].changes.push_back(0); g[e1].pos_cross.push_back(-1);
						break;
					}
				break;
				case 2:
					g[e1].changes.push_back(0);
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
									g[e1].changes.push_back(1);	g[e1].pos_cross.push_back(-1);
								break;
								case 1:
									g[e1].changes.push_back(1);	g[e1].pos_cross.push_back(p3);
									g[e1].changes.push_back(2);	g[e1].pos_cross.push_back(-1);
								break;
							}
						break;
						case 1:
							switch (state[p3]){
								case 0: 
									g[e1].changes.push_back(1); g[e1].pos_cross.push_back(p2);
									g[e1].changes.push_back(2);	g[e1].pos_cross.push_back(-1);
								break;
								case 1:
									if (p1 != 1){//forbid 101->111 but allow 011->111 & 110->111 
										g[e1].changes.push_back(1); g[e1].pos_cross.push_back(1);
									}
									g[e1].changes.push_back(2); g[e1].pos_cross.push_back(-1); 
								break;
								case 2:
									g[e1].changes.push_back(1); g[e1].pos_cross.push_back(p2);
									g[e1].changes.push_back(2); g[e1].pos_cross.push_back(p3);
									g[e1].changes.push_back(3); g[e1].pos_cross.push_back(-1);
								break;
							}
						break;
						case 2:
							switch (state[p3]){
								case 1: 
									g[e1].changes.push_back(1); g[e1].pos_cross.push_back(p3);
									g[e1].changes.push_back(2); g[e1].pos_cross.push_back(p2);
									g[e1].changes.push_back(3); g[e1].pos_cross.push_back(-1);
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
									g[e1].changes.push_back(0);	g[e1].pos_cross.push_back(-1);
								break;
								case 1:
									g[e1].changes.push_back(0);	g[e1].pos_cross.push_back(p3);
								break;
								case 2:
									g[e1].changes.push_back(0);	g[e1].pos_cross.push_back(-1);
								break;
							}
						break;
						case 1:
							switch (state[p3]){
								case 0: 
									g[e1].changes.push_back(0); g[e1].pos_cross.push_back(p2);
								break;
								case 1:
									if (p1 != 1){//forbid 111->101 but allow 111->011 & 111->110 
										g[e1].changes.push_back(0); g[e1].pos_cross.push_back(1);
									}
								break;
								case 2:
									g[e1].changes.push_back(0); g[e1].pos_cross.push_back(p2);
								break;
							}
						break;
						case 2:
							switch (state[p3]){
								case 0: 
									g[e1].changes.push_back(0); g[e1].pos_cross.push_back(-1);
								break;
								case 1: 
									g[e1].changes.push_back(0); g[e1].pos_cross.push_back(p3);
								break;
								case 3: 
									g[e1].changes.push_back(0); g[e1].pos_cross.push_back(-1);
								break;
							}
						break;
					}
				break;
				case 2:
					g[e1].changes.push_back(0); g[e1].pos_cross.push_back(-1);
				break;
				case 3:
					g[e1].changes.push_back(0); g[e1].pos_cross.push_back(-1);
				break;
			}
		break;
	}	
}
pair<Edge_desc,bool> MyGraph::check_cross(int d1, int d2){ /* Takes two domains and checks if crossover exists. 
														If it does, then "this.first" is its id.*/
	pair<Edge_desc,bool> result;
	Domain dom1 = design.domains[d1];		Domain dom2 = design.domains[d2];
	Edge_desc edge1 = id_to_edge(d1);		Edge_desc edge2 = id_to_edge(d2);
	int c = design.dpair_to_crossover(make_pair(d1,d2));
	Crossover cross = design.crossovers[c];
	pair<Edge_desc,bool> cross_edge;//, rev_cross_edge;
	//cross_edge = edge(cross.v_a, cross.v_b, g);
	//rev_cross_edge = edge(cross.v_b, cross.v_a, g);
	Edge_iter ei,ef;
	tie(ei,ef) = edges(g);
	for ( ; ei != ef ; ++ei ){
		if(g[*ei].is_crossover.second == true && g[*ei].is_crossover.first == cross.id){
			cross_edge.first = *ei;
			cross_edge.second = true;
		}
	}
	//Extra checks (no need)
	if(find(dom1.cross_domains.begin(), dom1.cross_domains.end(), d2) != dom1.cross_domains.end()) {
	/* dom2 is in dom1.cross_domains */
		if (cross_edge.second == true ){
			if (cross.is_53 == g[cross_edge.first].is_53){
				result = cross_edge;
			}		
		}
		/*
		else if (rev_cross_edge.second == true ){
			if (cross.is_53 == g[rev_cross_edge.first].is_53){
				result = rev_cross_edge;
			}		
		}*/
		else {
			result.second = false;
		}
				
	} 
	else {
		cout << "Warning: The domains should not have crossovers by design!!" << endl;
	}
	return result;
}
void MyGraph::set_state(int d){
	if (d>design.domains.size()-1){
		printf ("Error! crossover cannot have state.\n"); exit (EXIT_FAILURE);
	}
	Domain domain = design.domains[d];
	Edge_desc myedge = id_to_edge(d);
	//g[myedge].pos = domain.s_index;
	Edge_desc crossedge, crossedge2;
	//Edge_desc stackedge;
	int d1,d2,d3;
	bool cross12, cross23, cross13;
	g[myedge].state.clear();
	switch (domain.cross_domains.size()) {
		case 0: 
			g[myedge].state.push_back(0);
			switch (g[myedge].type){
				case 's': //0
				break;
				case 'd':
					g[myedge].state[g[myedge].pos] = 1;	//1
				break;
			}
		break;
		case 1: 
			g[myedge].state.push_back(0);
			g[myedge].state.push_back(0);
			d1 = d;
			d2 = domain.cross_domains[0];
			cross12 = check_cross(d1,d2).second;
			crossedge = id_to_edge(domain.cross_domains[0]);
			switch (g[myedge].type){
				case 's':
					switch (g[crossedge].type){
						case 's':	//00
						break;
						case 'd':	//01 10
							g[myedge].state[g[crossedge].pos] = 1;
						break;
					}
				break;
				case 'd':
					g[myedge].state[g[myedge].pos] = 1;
					switch (g[crossedge].type){
						case 's': //10 01
						break;
						case 'd':
							if (cross12 == true) {g[myedge].state[g[crossedge].pos] = 1;} //11
							else {g[myedge].state[g[crossedge].pos] = 2;} //12
						break;
					}
				break;
			}
		break;
		case 2: 
			g[myedge].state.push_back(0);
			g[myedge].state.push_back(0);
			g[myedge].state.push_back(0);
			crossedge = id_to_edge(domain.cross_domains[0]);
			crossedge2 = id_to_edge(domain.cross_domains[1]);
			d1 = d;
			d2 = domain.cross_domains[0];
			d3 = domain.cross_domains[1];
			cross12 = check_cross(d1,d2).second;
			cross13 = check_cross(d1,d3).second;
			cross23 = check_cross(d2,d3).second;
			switch (g[myedge].type){
				case 's':
					switch (g[crossedge].type){
						case 's':
							switch (g[crossedge2].type){
								case 's': //000
								break;
								case 'd':
									g[myedge].state[g[crossedge2].pos] = 1; //100 010 001
								break;
							}
						break;
						case 'd':
							g[myedge].state[g[crossedge].pos] = 1;
							switch (g[crossedge2].type){
								case 's': //100 010 001
								break;
								case 'd':
									if (cross23 == true) {g[myedge].state[g[crossedge2].pos] = 1;}//DANGER! //011 101 110
									else { g[myedge].state[g[crossedge2].pos] = 2;} //012 102 120
								break;
							}
						break;
					}
				break;
				case 'd':
					g[myedge].state[g[myedge].pos] = 1;
					switch (g[crossedge].type){
						case 's':
							switch (g[crossedge2].type){
								case 's': //100 101 001
								break;
								case 'd':
									if (cross13 == true) {g[myedge].state[g[crossedge2].pos] = 1;} //011 101 110
									else { g[myedge].state[g[crossedge2].pos] = 2;} //012 102 120
								break;
							}
						break;
						case 'd':
							if (cross12 == true) {g[myedge].state[g[crossedge].pos] = 1;}
							else { g[myedge].state[g[crossedge].pos] = 2;} 
							switch (g[crossedge2].type){
								case 's': //011 101 110 012 102 120
								break;
								case 'd': //111 112 121 212 122 123
									if (cross23 == false && cross12 == false && cross13 == false){g[myedge].state[g[crossedge2].pos]=3;} //123

									else if (cross23 == true && cross12 == true && cross13 == false){g[myedge].state[g[crossedge2].pos]=1;}//111
									else if (cross23 == false && cross12 == true && cross13 == true){g[myedge].state[g[crossedge2].pos]=1;}//111

									else if (cross23 == false && cross12 == true && cross13 == false){g[myedge].state[g[crossedge2].pos]=2;}//112
									else if (cross23 == true && cross12 == false && cross13 == false){g[myedge].state[g[crossedge2].pos]=2;}//122 
									else if (cross23 == false && cross12 == false && cross13 == true){g[myedge].state[g[crossedge2].pos]=1;}//121 
									else if (cross23 == true && cross12 == true && cross13 == true){g[myedge].state[g[crossedge2].pos]=5;} //115!
									else{ cout << "NEED MORE IFs!" << endl;}
								break;
							}
						break;
					}
				break;
			}
		break;
	}	
}
void MyGraph::reset_all_states(){
	for (int d=0; d<design.n_domains; d++){
		set_state(d);		
	}
}
void MyGraph::add_vertices(){
	for(int i=0; i<design.n_vertices; i++){
		add_vertex(g);
	}
	reset_vertex_index();
}
void MyGraph::add_domains(){
	EdgeProperty EP; 
	EP.type = 's';
	for (vector<Domain>::iterator d = design.domains.begin(); d != design.domains.end(); ++d) {	
		EP.id = distance(design.domains.begin(), d);
		//EP.length = d->length / 4.;
		EP.length = d->length;
		EP.pos = d->s_index;
		add_edge(d->source, d->target, EP, g);
	}
	reset_edge_index();
	set_edge_weights();
}
Edge_desc MyGraph::id_to_edge(int e){
	Edge_desc result;
	Edge_iter ei,ef;
	tie(ei,ef) = edges(g);
	for ( ; ei != ef ; ++ei ){
		if(g[*ei].id == e){result = *ei;}
	}
	return result;
}
void MyGraph::reset_vertex_index() {
	Vertex_iter vi,vf;
	int i = 0;
	for(tie(vi,vf) = vertices(g); vi != vf; ++vi) {
		g[*vi].id = i;
		i++;
	}
}	
void MyGraph::reset_edge_index() {
	Edge_iter ei,ef;
	tie(ei,ef) = edges(g);
	int i = 0;
	for ( ; ei != ef ; ++ei){
		g[*ei].id = i;
		i++;
	}
}
void MyGraph::add_crossover_v(pair<int,int> vpair){
	int cross_id = design.vpair_to_crossover(vpair);
	EdgeProperty EP; 
	EP.type = design.crossovers[cross_id].type;
	EP.length = default_crossover_size;
	if (EP.type == 'l') {EP.length *= 2;}
	add_edge(design.crossovers[cross_id].v_a, design.crossovers[cross_id].v_b, EP, g);
	reset_edge_index();
	set_edge_weights();
}
void MyGraph::add_crossover_d(pair<int,int> dpair){
	int cross_id = design.dpair_to_crossover(dpair);
	Crossover crossover = design.crossovers[cross_id];
	EdgeProperty EP; 
	EP.type = design.crossovers[cross_id].type;
	EP.length = default_crossover_size;
	EP.is_53 = crossover.is_53;
	EP.is_crossover=(make_pair(crossover.id,true));
	add_edge(design.crossovers[cross_id].v_a, design.crossovers[cross_id].v_b, EP, g);
	reset_edge_index();
	set_edge_weights();
}
void MyGraph::add_crossover(int c){
	Crossover crossover = design.crossovers[c];
	EdgeProperty EP; 
	EP.type = crossover.type;
	EP.length = default_crossover_size;
	EP.is_53 = crossover.is_53;
	EP.is_crossover=(make_pair(crossover.id,true));
	add_edge(crossover.v_a, crossover.v_b, EP, g);
	reset_edge_index();
	set_edge_weights();
}
void MyGraph::remove_crossover(int c){
	Crossover crossover = design.crossovers[c];
	remove_edge(crossover.v_a, crossover.v_b, g);
	reset_edge_index();
	set_edge_weights();
}
void MyGraph::add_all_crossovers(){
	EdgeProperty EP; 
	EP.length = default_crossover_size;
	for (vector<Crossover>::iterator c = design.crossovers.begin(); c != design.crossovers.end(); ++c) {
		EP.type = (*c).type;
		add_edge((*c).v_a, (*c).v_b, EP, g);
	}
	reset_edge_index();
	set_edge_weights();
}
void MyGraph::bind_all_domains() {
	Edge_iter ei,ef;
	tie( ei, ef) = edges(g);
	for ( ; ei != ef ; ++ei ){
		if(g[*ei].type == 's'){g[*ei].type = 'd';}
	}
	set_edge_weights();
}
void MyGraph::set_edge_weights(){	
	Edge_iter ei,ef;
	tie( ei, ef) = edges(g);
	for ( ; ei != ef ; ++ei ){
		if(g[*ei].type == 'd'){g[*ei].weight = g[*ei].length * l_ds * g[*ei].length * l_ds;}
		else if(g[*ei].type == 's'){g[*ei].weight = g[*ei].length * l_ss * lambda_ss;}
		else if(g[*ei].type == 'i' || g[*ei].type == 'o' || g[*ei].type == 'm' || g[*ei].type == 'l'){g[*ei].weight = lambda_ss * lambda_ss;}
		else {cout << "no domain type found for edge" << endl;}
	}
}
void MyGraph::print_edges(){
	cout << "\n\n---------------------- Printing Edges -------------------------\n";
	Edge_iter ei,ef;
	tie( ei, ef) = edges(g);
	for ( ; ei != ef ; ++ei ){
		cout << g[*ei].id << "\t";
		cout << *ei << "\t";
		cout << "Type: " << g[*ei].type << "\t";
		//cout << "Length: " << g[*ei].length << "\t";
		cout << "State: ";
		for (vector<int>::iterator it = g[*ei].state.begin(); it != g[*ei].state.end(); ++it){
			cout << (*it);
		}
		cout << "\t";
		cout << "Changes: ";
		for (int i=0; i< g[*ei].changes.size(); i++){
			cout << g[*ei].changes[i] << " (" << g[*ei].pos_cross[i] << ") ";
		}
		cout << "\t";
		cout << "Pos: " << g[*ei].pos << "\t";
		cout << "is_53: " << g[*ei].is_53 << "\t";
		//cout << "Weight: " << g[*ei].weight; 
		cout << "\n";
	}	
}
void MyGraph::write_gv_circle(string filename) {
	double radius = 25;
	Vertex_iter vi,vf;
	int n_vertices = design.n_vertices;
	double x, y, angle;
	angle = (2 * M_PI) / n_vertices;
	vector<double> X,Y;
	for (int i=0; i<n_vertices; i++){
		x = radius * cos(i*angle);
		y = radius * sin(i*angle);
		X.push_back(x);
		Y.push_back(y);
	}	
	int i=0;
	for(tie(vi,vf) = vertices(g); vi != vf; ++vi) {
		g[*vi].pos = std::to_string(X[i]);
		g[*vi].pos += ",";
		g[*vi].pos += std::to_string(Y[i]);
		g[*vi].pos += "!";
		g[*vi].height = 0.3;
		g[*vi].width = 0.3;
		g[*vi].other = "true";
		i++;
	}
	Edge_iter ei,ef;
	tie( ei, ef) = edges(g);
	for ( ; ei != ef ; ++ei ){
		if(g[*ei].type == 'd'){g[*ei].colour = "black"; g[*ei].thickness = "6.0";}
		else if(g[*ei].type == 's'){g[*ei].colour = "black"; g[*ei].thickness = "2.0";}
		else if(g[*ei].type == 'i'){g[*ei].colour = "green"; g[*ei].thickness = "2.0";}
		else if(g[*ei].type == 'o'){g[*ei].colour = "blue"; g[*ei].thickness = "2.0";}
		else if(g[*ei].type == 'm'){g[*ei].colour = "red"; g[*ei].thickness = "2.0";}
		else if(g[*ei].type == 'l'){g[*ei].colour = "purple"; g[*ei].thickness = "2.0";}
		else {cout << "no domain type found for edge" << endl;}
	}
	boost::dynamic_properties dp;
	dp.property("len", get(&EdgeProperty::length, g));
	//dp.property("weight", get(&EdgeProperty::weight, g));
	//dp.property("label", get(&EdgeProperty::weight, g));
	dp.property("type", get(&EdgeProperty::type, g));
	dp.property("color", get(&EdgeProperty::colour, g));
	dp.property("penwidth", get(&EdgeProperty::thickness, g));
	//dp.property("label", get(&VertexProperty::name, g));
	dp.property("node_id", get(&VertexProperty::id, g)); //must have!
	dp.property("pos", get(&VertexProperty::pos, g)); //must have!
	dp.property("height", get(&VertexProperty::height, g)); //must have!
	dp.property("width", get(&VertexProperty::width, g)); //must have!
	dp.property("fixedsize", get(&VertexProperty::other, g)); //must have!
	ofstream outfile;
	outfile.open(filename+"_C.gv");
	write_graphviz_dp(outfile, g, dp);
	outfile.close();
}
void MyGraph::write_gv(string filename) {
	Edge_iter ei,ef;
	tie( ei, ef) = edges(g);
	for ( ; ei != ef ; ++ei ){
		if(g[*ei].type == 'd'){g[*ei].colour = "black"; g[*ei].thickness = "6.0";}
		else if(g[*ei].type == 's'){g[*ei].colour = "black"; g[*ei].thickness = "2.0";}
		else if(g[*ei].type == 'i'){g[*ei].colour = "green"; g[*ei].thickness = "2.0";}
		else if(g[*ei].type == 'o'){g[*ei].colour = "blue"; g[*ei].thickness = "2.0";}
		else if(g[*ei].type == 'm'){g[*ei].colour = "red"; g[*ei].thickness = "2.0";}
		else if(g[*ei].type == 'l'){g[*ei].colour = "purple"; g[*ei].thickness = "2.0";}
		else {cout << "no domain type found for edge" << endl;}
	}
	boost::dynamic_properties dp;
	dp.property("len", get(&EdgeProperty::length, g));
	//dp.property("weight", get(&EdgeProperty::weight, g));
	//dp.property("label", get(&EdgeProperty::weight, g));
	dp.property("type", get(&EdgeProperty::type, g));
	dp.property("color", get(&EdgeProperty::colour, g));
	dp.property("penwidth", get(&EdgeProperty::thickness, g));
	//dp.property("label", get(&VertexProperty::name, g));
	dp.property("node_id", get(&VertexProperty::id, g)); //must have!
	ofstream outfile;
	outfile.open(filename+".gv");
	write_graphviz_dp(outfile, g, dp);
	outfile.close();
}
int MyGraph::get_bound_dom_count(){
	int result = 0;
	Edge_iter ei,ef;
	tie( ei, ef) = edges(g);
	for ( ; ei != ef ; ++ei ){
		if(g[*ei].type == 'd'){result++;}
	}
	return result;
}
int MyGraph::get_bound_nuc_count(){
    int result = 0;
    Edge_iter ei,ef;
    tie( ei, ef) = edges(g);
    for ( ; ei != ef ; ++ei ){
        if(g[*ei].type == 'd'){
            result += g[*ei].length;
        }
    }
    return result;
}
void MyGraph::get_bound_dom_counts(vector<int> &counts){
    Edge_iter ei,ef;
    tie( ei, ef) = edges(g);
	for (int i=0; i<counts.size(); i++){
		counts[i] = 0;
	}
	for ( ; ei != ef ; ++ei ){
		for (int i=0; i<counts.size(); i++){
			if(g[*ei].type == 'd' && g[*ei].state.size() == (i+1) ){
				counts[i] += 1;
			}
		}
	}
}
double MyGraph::total_weight(int a, int b) {
	typedef double Weight;
	typedef property_map <Graph,vertex_index_t>::type IndexMap;
	typedef iterator_property_map <Vertex_desc*,IndexMap,Vertex_desc,Vertex_desc&> PredecessorMap;
	typedef iterator_property_map <Weight*,IndexMap,Weight,Weight&> DistanceMap;
	vector<Vertex_desc> predecessors(num_vertices(g)); // To store parents
	vector<Weight> distances(num_vertices(g)); // To store distances
	IndexMap indexMap = get(vertex_index, g);
	PredecessorMap predecessorMap(&predecessors[0], indexMap);
	DistanceMap distanceMap(&distances[0], indexMap);
	dijkstra_shortest_paths(g, a, weight_map(get(&EdgeProperty::weight, g)).distance_map(distanceMap).predecessor_map(predecessorMap));
	//typedef vector<Edge_desc> Path;
	Path path;
	Vertex_desc v=b; // We want to start at the destination and work our way back to the source
	for(Vertex_desc u=predecessorMap[v]; u!=v; v=u, u=predecessorMap[v]) {
		pair<Edge_desc, bool> edgePair = edge(u, v, g);
		Edge_desc edge = edgePair.first;
		path.push_back(edge);
	}
	return distanceMap[b];
}
void MyGraph::make_transition(int e, bool add) {
	Domain domain = design.domains[e];
	vector<int> possible_crossovers = domain.crossover_ids;
	Edge_desc myedge = id_to_edge(e);
	int e2, v1, v2;
	Edge_desc cross_edge;
	Crossover c;
	for (vector<int>::iterator it = possible_crossovers.begin(); it != possible_crossovers.end(); ++it) {
		c = design.crossovers[*it];
		if ( c.d_a == e ) { e2 = c.d_b; } else { e2 = c.d_a; } 
		cross_edge = id_to_edge(e2);
		if (g[cross_edge].type == 'd') {
			if (g[myedge].type == 'd') {
				if (edge(c.v_a, c.v_b, g).second == true || edge(c.v_b, c.v_a, g).second == true){
					remove_crossover(*it);
				}
			}
			else if (g[myedge].type == 's') {
				if (add == true && c.type != 'l'){ 
					add_crossover(*it);
				}
			}
			else {printf ("Error! MyGraph::make_tansition: domain is neither s nor d. \n"); exit (EXIT_FAILURE);}
		}
	}
	if (g[myedge].type == 'd') {
		g[myedge].type = 's';
	}
	else if (g[myedge].type == 's') {
		g[myedge].type = 'd';
	}
	else {printf ("Error! MyGraph::make_tansition: domain is neither s nor d. \n"); exit (EXIT_FAILURE);}
	set_edge_weights();
	/*
	set_state(e);
	for (vector<int>::iterator it = possible_crossovers.begin(); it != possible_crossovers.end(); ++it) {
		c = design.crossovers[*it];
		if ( c.d_a == e ) { e2 = c.d_b; } else { e2 = c.d_a; } 
		set_state(e2);
	}
	*/
}
void MyGraph::make_transition(int e, bool add, vector<int> &affected) {
	Domain domain = design.domains[e];
	vector<int> possible_crossovers = domain.crossover_ids;
	Edge_desc myedge = id_to_edge(e);
	int e2, v1, v2;
	Edge_desc cross_edge;
	Crossover c;
	//affected.push_back(e); 
	//stack affected domains.
	for (vector<int>::iterator it = domain.stack_domains.begin(); it != domain.stack_domains.end(); ++it){
		affected.push_back(*it);
	}
	if (possible_crossovers.size() == 0){
		get_affected(e, affected);
	}
	else {
		for (vector<int>::iterator it = possible_crossovers.begin(); it != possible_crossovers.end(); ++it) {
			c = design.crossovers[*it];
			if ( c.d_a == e ) { e2 = c.d_b; } else { e2 = c.d_a; } 
			cross_edge = id_to_edge(e2);
			affected.push_back(e2);
			if (g[cross_edge].type == 'd') {
				if (g[myedge].type == 'd') {
					if (edge(c.v_a, c.v_b, g).second == true || edge(c.v_b, c.v_a, g).second == true){
						remove_crossover(*it);
					}
					get_affected(e, affected);
					//get_affected(e2, affected);
				}
				else if (g[myedge].type == 's') {
					get_affected(e, affected);
					//get_affected(e2, affected);
					if (add == true){ 
						add_crossover(*it);
					}
				}
				else {printf ("Error! MyGraph::make_tansition: domain is neither s nor d. \n"); exit (EXIT_FAILURE);}
			}
			else if (g[cross_edge].type == 's') {
				get_affected(e, affected);
			}
			else {printf ("Error! MyGraph::make_tansition: cross-domain is neither s nor d. \n"); exit (EXIT_FAILURE);}
		}
	}
	if (g[myedge].type == 'd') {
		g[myedge].type = 's';
	}
	else if (g[myedge].type == 's') {
		g[myedge].type = 'd';
	}
	else {printf ("Error! MyGraph::make_tansition: domain is neither s nor d. \n"); exit (EXIT_FAILURE);}
	set_edge_weights();
}
int MyGraph::find_interacting_domain(int d, int interacting_pos){
	Domain domain = design.domains[d];
	Domain cross_dom;
	int result;
	for (vector<int>::iterator it = domain.cross_domains.begin(); it != domain.cross_domains.end(); ++it){
		cross_dom = design.domains[*it];
		if (cross_dom.s_index == interacting_pos){
			result = cross_dom.source;
		}
	}
	return result;
}
void MyGraph::make_transition(int d, int i) { 
	/*
	 * d is the domain number. 
	 * i is the index in edge.changes (identifies the change) NOT POSITION on edge.state
	 */
	if (d>design.domains.size()-1){ 
		printf ("Error! Cannot perform transion on crossover!\n"); exit (EXIT_FAILURE); 
	}
	Domain domain = design.domains[d];
	Edge_desc e1 = id_to_edge(d);
	vector<int> state = g[e1].state;
	int change = g[e1].changes[i];
	int p1 = g[e1].pos; //position of THE domain on edge.state 
	int pc = g[e1].pos_cross[i]; //position of interating domain on edge.state
 	int d2; //interating domain's id.
	int c; //crossover id in design.crossovers that connects d to d2
	Crossover crossover;
	Domain cross_dom;
	Edge_desc e2;
	
	(g[e1].state)[p1] = change;
	if (change > 0){
		g[e1].type = 'd';
	}
	else{
		g[e1].type = 's';
	}

	if (pc > -1){
		d2 = find_interacting_domain(d,pc);
		c = design.dpair_to_crossover(make_pair(d,d2));
		if (change > 0){ //Add crossover d & d2
			add_crossover(c);
		}
		else{ //Remove crossover between d & d2
			remove_crossover(c);
		}
	}
	set_changes(d);	
	for (vector<int>::iterator it = domain.cross_domains.begin(); it != domain.cross_domains.end(); ++it){
		cross_dom = design.domains[*it];
		e2 = id_to_edge(*it);
		(g[e2].state)[p1] = change;
		set_changes(*it);	
	}
	reset_edge_index();
	set_edge_weights();
}
void MyGraph::update_embedding() {
	emb.resize(num_vertices(g));
	if (boyer_myrvold_planarity_test(boyer_myrvold_params::graph = g,boyer_myrvold_params::embedding = &emb[0]))
		return;
	else
		cout << "input graph is not planar." << endl;
}
void MyGraph::print_embedding() {
	face_counter count_visitor;
	planar_face_traversal(g, &emb[0], count_visitor, get(&EdgeProperty::id, g));
	cout << "Traversing faces of planar embedding... the planar embedding of the graph has " << count_visitor.count << " faces." << endl;
	cout << endl << "Vertices on the faces: " << endl;
	vertex_output_visitor v_vis;
	planar_face_traversal(g, &emb[0], v_vis, get(&EdgeProperty::id, g));
	cout << endl << "Edges on the faces: " << endl;
	edge_output_visitor e_vis;
	planar_face_traversal(g, &emb[0], e_vis, get(&EdgeProperty::id, g));
}
void MyGraph::update_faces() {
	//updates faces of the graph.
	Faces_visitor Faces;
	planar_face_traversal(g, &emb[0], Faces, get(&EdgeProperty::id, g));
	faces = Faces.faces;
	//removing the big overall loop
	for (Embedding::iterator f = faces.begin(); f != faces.end(); ++f) {
		if ( (*f).size() == design.n_domains ) {
			faces.erase(f);
		}
	}   
}
Path MyGraph::select_face(int d) {
	//selects the shortest loop that the domain is a part of. 
	Edge_desc es = id_to_edge(d);
	Path loop;
	for (Embedding::iterator f = faces.begin(); f != faces.end(); ++f) {
		for (Path::iterator e = (*f).begin(); e != (*f).end(); ++e) {		
			if ( (*e) == es) {
				loop = (*f);
				if ( (*f).size() < loop.size() ) {
					loop = (*f);
				}
			}
		}
	}
	return loop;
}
vector<Path> MyGraph::select_all_faces(int d) {
	//selects all loops that the domain is a part of. 
	Edge_desc es = id_to_edge(d);
	vector<Path> loops;
	for (Embedding::iterator f = faces.begin(); f != faces.end(); ++f) {
		for (Path::iterator e = (*f).begin(); e != (*f).end(); ++e) {		
			if ( (*e) == es) {
				loops.push_back(*f);
			}
		}
	}
	return loops;
}
void MyGraph::get_affected(int d, vector<int> &affected){
	//affected.clear();
	//update_embedding();
	//update_faces();
	/*
	Path new_face = select_face(d);
	int i;
	for (Path::iterator it = new_face.begin(); it != new_face.end(); ++it) {
		i = g[*it].id;
		if (i<design.n_domains){
			affected.push_back(i);
		}
	}
	*/
	affected.push_back(d);
	/*
	vector<Path> new_faces = select_all_faces(d);
	int i;
	for (vector<Path>::iterator f = new_faces.begin(); f != new_faces.end(); ++f) {
		for (Path::iterator it = (*f).begin(); it != (*f).end(); ++it) {
			i = g[*it].id;
			if (i<design.n_domains){
				if (g[*it].type == 's'){
					for (vector<int>::iterator c = design.domains[i].cross_domains.begin(); c != design.domains[i].cross_domains.end(); ++c) {
						if (g[id_to_edge(*c)].type == 'd'){
							affected.push_back(i);
						}
					}
				}
			}
		}
	}
	*/
	for (int i=0; i<design.n_domains; i++){
		if (g[id_to_edge(i)].type == 's'){
			for (vector<int>::iterator c = design.domains[i].cross_domains.begin(); c != design.domains[i].cross_domains.end(); ++c) {
				if (g[id_to_edge(*c)].type == 'd'){
					affected.push_back(i);
				}
			}
		}
	}
}
