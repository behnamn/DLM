/*
 *
 *	main.cpp
 * 	Author: Behnam
 *
 */

#include "Constants.h"
#include "Design.h"
#include "MyGraph.h"
#include "TempRamp.h"
#include "Simulation.h"
#include "Test.h"

int main(int argc, char * argv[]) {
	//Inputs *inputs = new Inputs(argc,argv);
    //Inputs *inputs = new Inputs();
	Inputs *inputs = new Inputs(argc,argv);

	Constants *constants = new Constants(inputs->gamma,inputs->n_param,inputs->concentration);

    /*
    enum S_State { s000, s001, s010, s100, s011, s110, s101, s012, s120, s102, s112, s211, s121, s123, s111, S_State_MAX };
    enum U_State { s00, s10, s01, s11, s12, U_State_MAX };
    enum H_State { s0, s1, H_State_MAX };
    */
    /*
    enum State { s0, s1, s00, s10, s01, s11, s12, s000, s001, s010, s100, s011, s110, s101, s012, s120, s102, s112, s211, s121, s123, s111, State_MAX };
    std::array<string,State_MAX> State_names = { "s0", "s1", "s00", "s10", "s01", "s11", "s12", "s000", "s001", "s010", "s100", "s011", "s110", "s101", "s012", "s120", "s102", "s112", "s211", "s121", "s123", "s111"};
    
    std::map< pair<State,State>, TP > FullTransitionMap;
    for (int i=0; i<State_MAX; i++){
        for (int j=0; j<State_MAX; j++){
            FullTransitionMap[make_pair(State(i),State(j))] = TP();
        }
    }
    FullTransitionMap[make_pair(s0,s1)] = TP(true,0);
    
    FullTransitionMap[make_pair(s00,s10)] = TP(true,0);     FullTransitionMap[make_pair(s00,s01)] = TP(true,1);
    FullTransitionMap[make_pair(s10,s11)] = TP(true,1,0);   FullTransitionMap[make_pair(s10,s12)] = TP(true,1);
    FullTransitionMap[make_pair(s01,s11)] = TP(true,0,1);   FullTransitionMap[make_pair(s01,s12)] = TP(true,0);
    
    FullTransitionMap[make_pair(s000,s001)] = TP(true,2);   FullTransitionMap[make_pair(s000,s010)] = TP(true,1);   FullTransitionMap[make_pair(s000,s100)] = TP(true,0);
    FullTransitionMap[make_pair(s001,s011)] = TP(true,1,2); FullTransitionMap[make_pair(s001,s101)] = TP(true,0,2); FullTransitionMap[make_pair(s001,s012)] = TP(true,1);   FullTransitionMap[make_pair(s001,s102)] = TP(true,0);
    FullTransitionMap[make_pair(s010,s011)] = TP(true,2,1); FullTransitionMap[make_pair(s010,s110)] = TP(true,0,1); FullTransitionMap[make_pair(s010,s012)] = TP(true,2);   FullTransitionMap[make_pair(s010,s120)] = TP(true,0);
    FullTransitionMap[make_pair(s100,s110)] = TP(true,1,0); FullTransitionMap[make_pair(s100,s101)] = TP(true,2,0); FullTransitionMap[make_pair(s100,s120)] = TP(true,1);   FullTransitionMap[make_pair(s100,s102)] = TP(true,2);
    
    FullTransitionMap[make_pair(s011,s211)] = TP(true,0); FullTransitionMap[make_pair(s011,s111)] = TP(true,0,1);
    FullTransitionMap[make_pair(s110,s112)] = TP(true,2); FullTransitionMap[make_pair(s110,s111)] = TP(true,2,1);
    FullTransitionMap[make_pair(s101,s121)] = TP(true,1); //FullTransitionMap[make_pair(s101,s111)] = TP(true,0,1);
    
    FullTransitionMap[make_pair(s012,s112)] = TP(true,0,1); FullTransitionMap[make_pair(s012,s121)] = TP(true,0,2); FullTransitionMap[make_pair(s012,s123)] = TP(true,0);
    FullTransitionMap[make_pair(s120,s211)] = TP(true,2,1); FullTransitionMap[make_pair(s120,s121)] = TP(true,2,0); FullTransitionMap[make_pair(s120,s123)] = TP(true,2);
    FullTransitionMap[make_pair(s102,s112)] = TP(true,1,0); FullTransitionMap[make_pair(s102,s211)] = TP(true,1,2); FullTransitionMap[make_pair(s102,s123)] = TP(true,1);
    
    for (int i = 0; i<State_MAX; i++){
        for (int j = 0; j<State_MAX; j++){
            if (j>i){
                FullTransitionMap[make_pair(State(j),State(i))] = FullTransitionMap[make_pair(State(i),State(j))];
                FullTransitionMap[make_pair(State(j),State(i))].bind = false;
            }
        }
    }
    
    for (int i = 0; i<State_MAX; i++){
        cout << State_names[i] << "\t";
        for (int j = s0; j<State_MAX; j++){
            if (FullTransitionMap[make_pair(State(i),State(j))].allowed)
                cout << State_names[j] << "\t";
                //cout << FullTransitionMap[make_pair(State(i),State(j))].cross_dom << " ";
        }
        cout << endl;
    }
    */
    
    
    
    //Design *design = new Design(inputs);
	//design->print_staples();
	//design->print_domains();
	//design->print_crossovers();
    //delete design;
	
	//MyGraph *G = new MyGraph(design);
    //G->update_embedding();
    //G->update_faces();
    //G->print_embedding();
    //G->complete();
    //G->update_embedding();
    //G->update_faces();

    /*
    for (auto a = G->Faces.faces.begin(); a!= G->Faces.faces.end(); ++a){
        for (auto b = a->vec.begin(); b!=a->vec.end(); ++b){
            cout << *b << "\t";
        }
        cout << "\n";
    }
    cout << G->Faces.i << endl;
    G->Faces.test(2);
    for (auto a = G->Faces.faces.begin(); a!= G->Faces.faces.end(); ++a){
        for (auto b = a->vec.begin(); b!=a->vec.end(); ++b){
            cout << *b << "\t";
        }
        cout << "\n";
    }
    G->write_gv("Graph");
	*/
    
	if (inputs->anneal && !inputs->melt){
        Design *design = new Design(inputs);
		AnnealMelt *anneal = new AnnealMelt(inputs);
        MyGraph *G = new MyGraph(design);
        TransitionManager *localManager = new TransitionManager(constants, design, G, anneal, inputs);
        Statistics* statistics = new Statistics(inputs, design);
        Simulation *local_a = new Simulation(constants, design, G, anneal, inputs, localManager, statistics);
		local_a->run();
        delete design;
		delete anneal;
        delete G;
        delete localManager;
        delete local_a;
        delete statistics;
	}
	else if (!inputs->anneal && inputs->melt){
        Design *design = new Design(inputs, true);
        AnnealMelt *melt = new AnnealMelt(inputs);
        MyGraph *G = new MyGraph(design, true);
        //cout << design->crossovers.size() + design->domains.size() << "\t" << num_edges(G->g) << endl;
        G->write_gv("Graph");
        G->write_gv_circle("Circle");
        G->write_gv_rectangleS("Rectangle");
        TransitionManager *localManager = new TransitionManager(constants, design, G, melt, inputs);
        Statistics* statistics = new Statistics(inputs, design, true);
        Simulation *local_m = new Simulation(constants, design, G, melt, inputs, localManager, statistics);
        local_m->run();
        delete design;
        delete melt;
        delete G;
        delete localManager;
        delete local_m;
        delete statistics;
	}
    
	delete inputs;
	delete constants;

	return 0;
}


/*
 //TransitionListS test;
 //cout << test.transitions["001"].at(1).cross_dom << endl;
 
 
 string str = "1b2";
 TP tp = TP(str);
 
 for (auto it=test.transitions.begin(); it!=test.transitions.end(); ++it){
 cout << (*it).first << "\t";
 for (auto it2=it->second.begin(); it2!=it->second.end(); ++it2){
 cout << it2->cross_dom << "\t";
 }
 cout << "\n";
 }
 
 enum S_State { s000, s001, s010, s100, s011, s110, s101, s012, s120, s102, s112, s211, s121, s123, s111};
 std::map<std::pair<S_State,S_State>, TransitionProperty> myMap;
 for (int i = s000; i != s111; i++){
 
 }
 */
