/*
 *
 *	Simulation.cpp
 * 	Author: Behnam
 *
 */

#include "Simulation.h"

Simulation::Simulation(Constants *constants_, Design* design_, MyGraph *G_, TempRamp *ramp_, Inputs *inputs_, TransitionManager* trManager_, Statistics* statistics_){
    ramp = ramp_;
    design = design_;
    constants = constants_;
    G = G_;
    inputs = inputs_;
    trManager = trManager_;
    statistics = statistics_;
}

void Simulation::run() {
    ofstream transition_file;
    transition_file.open(inputs->transition_file_name);
    base_generator_type generator(inputs->seed);
    uniform_real<> uni_dist(0,1);
    Uni uni(generator, uni_dist);
    string movie_file_name;
    string to_pdf_cmd;
    if (inputs->make_movie){
        system("mkdir Movie");
    }
    while (ramp->current_t < ramp->t_max){
        trManager->fill_transitions();
        trManager->select_transition(uni);
        if (trManager->tau > inputs->const_T_interval){continue;}
        trManager->next->apply(G);
        if (statistics->n_transitions % inputs->write_transition_every == 0){
            transition_file << ramp->current_t << "\t";
            transition_file << centigrade(ramp->get_T()) << "\t";
            trManager->next->write(transition_file);
            transition_file << "\n";
        }
        if (ramp->T_was_changed){
            statistics->select_stat(centigrade(ramp->get_T()));
            cout << centigrade(ramp->get_T()) << " ";
        }
        if (statistics->n_transitions % inputs->write_state_every == 0){
            design->write_state();
        }
        if (inputs->make_movie && statistics->n_transitions % 100 == 0){
            movie_file_name = "Movie/";
            movie_file_name += to_string(statistics->n_transitions);
            movie_file_name += "_";
            movie_file_name += to_string_with_precision(centigrade(ramp->get_T()));
            if (inputs->domain_file_name == "S_Lengths.txt"){
                G->write_gv_rectangleS(movie_file_name);
            }
            else{
                G->write_gv_rectangleU(movie_file_name);
            }
        }
        
        statistics->update(trManager->next);
        trManager->reset_possibles(trManager->next);
        trManager->reset_recalculates(trManager->next);
        ramp->move_time(trManager->tau);
    }
    statistics->write(inputs->statistics_file_name);
    transition_file.close();
}
