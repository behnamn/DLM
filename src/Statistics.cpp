//
//  Statistics.cpp
//  DLM_XC
//
//  Created by Behnam Najafi on 09/05/2017.
//  Copyright © 2017 Behnam Najafi. All rights reserved.
//

#include "Statistics.h"

Stat::Stat(double T_, const Design* design_): T(T_), design(design_){
    n_transitions = 0;
    for (int i = 0; i < param_t_MAX; i++){
        Param param;
        param.pt = param_t(i);
        param.val = 0;
        param.n = 0;
        param.average = 0.;
        params.push_back(param);
    }
    /*
    for (auto st = design->staples.begin(); st!= design->staples.end(); ++st){
        vector<stParam> dummy;
        if (st->n_domains==1){
            for (int i = s0; i < s00; i++){
                //stParam stparam(*st);
                stParam stparam;
                stparam.val = 0;
                stparam.n = 0;
                stparam.average = 0.;
                stparam.pt = stparam_t(i);
                dummy.push_back(stparam);
            }
        }
        if (st->n_domains==2){
            for (int i = s00; i < s000; i++){
                //stParam stparam(*st);
                stParam stparam;
                stparam.val = 0;
                stparam.n = 0;
                stparam.average = 0.;
                stparam.pt = stparam_t(i);
                dummy.push_back(stparam);
            }
        }
        if (st->n_domains==3){
            for (int i = s000; i < stparam_t_MAX; i++){
                //stParam stparam(*st);
                stParam stparam;
                stparam.val = 0;
                stparam.n = 0;
                stparam.average = 0.;
                stparam.pt = stparam_t(i);
                dummy.push_back(stparam);
            }
        }
        stparams.push_back(dummy);
    }
    */
}

void Stat::write(ofstream& statistics_file){
    statistics_file << this->T << "\t";
    statistics_file << this->n_transitions << "\t";
    for (auto par = params.begin(); par != params.end(); ++par){
        statistics_file << par->average << "\t";
    }
    statistics_file << "\n";
    /*
    for (auto st = stparams.begin(); st!=stparams.end(); ++st){
        statistics_file << this->T << "\t";
        for (auto par = st->begin(); par!=st->end(); ++par){
            statistics_file << par->average << "\t";
        }
        statistics_file << "\n";
    }
    statistics_file << "\n";
    */
}

void Stat::update(const TR tr){
    if (tr->bind){
        if(tr->staple->n_domains == 1){
            params[N_H_dom].val++; params[N_H_dom].update();
            params[N_H_st].val++; params[N_H_st].update();
        }
        if(tr->staple->n_domains == 2){
            params[N_U_dom].val++; params[N_U_dom].update();
            if (tr->fully){
                params[N_U_st].val++; params[N_U_st].update();
            }
        }
        if(tr->staple->n_domains == 3){
            params[N_S_dom].val++; params[N_S_dom].update();
            if (tr->fully){
                params[N_S_st].val++; params[N_S_st].update();
            }
        }
        params[N_nucs].val += tr->domain->length;   params[N_nucs].update();
        if(tr->cross){
            params[N_cross].val++; params[N_cross].update();
        }
    }
    else{
        if(tr->staple->n_domains == 1){
            params[N_H_dom].val--; params[N_H_dom].update();
            params[N_H_st].val--; params[N_H_st].update();
        }
        if(tr->staple->n_domains == 2){
            params[N_U_dom].val--; params[N_U_dom].update();
            if (tr->fully){
                params[N_U_st].val--; params[N_U_st].update();
            }
        }
        if(tr->staple->n_domains == 3){
            params[N_S_dom].val--; params[N_S_dom].update();
            if (tr->fully){
                params[N_S_st].val--; params[N_S_st].update();
            }
        }
        params[N_nucs].val -= tr->domain->length;   params[N_nucs].update();
        if(tr->cross){
            params[N_cross].val--; params[N_cross].update();
        }
    }
    this->n_transitions++;
    /*
    if(tr->staple->n_domains == 1){
        if (tr->staple->state[0] == 0){
            stparams[tr->staple->id][s0].val++; stparams[tr->staple->id][s0].update();
        }
        if (tr->staple->state[0] == 1){
            stparams[tr->staple->id][s1].val++; stparams[tr->staple->id][s1].update();
        }
    }
    if(tr->staple->n_domains == 2){
        if (tr->staple->state[0] == 0 && tr->staple->state[1] == 0){
            stparams[tr->staple->id][s00].val++; stparams[tr->staple->id][s00].update();
        }
        if (tr->staple->state[0] == 1 && tr->staple->state[1] == 0){
            stparams[tr->staple->id][s10].val++; stparams[tr->staple->id][s10].update();
        }
        if (tr->staple->state[0] == 0 && tr->staple->state[1] == 1){
            stparams[tr->staple->id][s01].val++; stparams[tr->staple->id][s01].update();
        }
        if (tr->staple->state[0] == 1 && tr->staple->state[1] == 1){
            stparams[tr->staple->id][s11].val++; stparams[tr->staple->id][s11].update();
        }
        if (tr->staple->state[0] == 1 && tr->staple->state[1] == 2){
            stparams[tr->staple->id][s12].val++; stparams[tr->staple->id][s12].update();
        }
    }
    if(tr->staple->n_domains == 3){
        if (tr->staple->state[0] == 0 && tr->staple->state[1] == 0 && tr->staple->state[2] == 0){
            stparams[tr->staple->id][s000].val++; stparams[tr->staple->id][s000].update();
        }
        if (tr->staple->state[0] == 0 && tr->staple->state[1] == 0 && tr->staple->state[2] == 1){
            stparams[tr->staple->id][s001].val++; stparams[tr->staple->id][s001].update();
        }
        if (tr->staple->state[0] == 0 && tr->staple->state[1] == 1 && tr->staple->state[2] == 0){
            stparams[tr->staple->id][s010].val++; stparams[tr->staple->id][s010].update();
        }
        if (tr->staple->state[0] == 1 && tr->staple->state[1] == 0 && tr->staple->state[2] == 0){
            stparams[tr->staple->id][s100].val++; stparams[tr->staple->id][s100].update();
        }
        if (tr->staple->state[0] == 0 && tr->staple->state[1] == 1 && tr->staple->state[2] == 1){
            stparams[tr->staple->id][s011].val++; stparams[tr->staple->id][s011].update();
        }
        if (tr->staple->state[0] == 1 && tr->staple->state[1] == 1 && tr->staple->state[2] == 0){
            stparams[tr->staple->id][s110].val++; stparams[tr->staple->id][s110].update();
        }
        if (tr->staple->state[0] == 1 && tr->staple->state[1] == 0 && tr->staple->state[2] == 1){
            stparams[tr->staple->id][s101].val++; stparams[tr->staple->id][s101].update();
        }
        if (tr->staple->state[0] == 0 && tr->staple->state[1] == 1 && tr->staple->state[2] == 2){
            stparams[tr->staple->id][s012].val++; stparams[tr->staple->id][s012].update();
        }
        if (tr->staple->state[0] == 1 && tr->staple->state[1] == 2 && tr->staple->state[2] == 0){
            stparams[tr->staple->id][s120].val++; stparams[tr->staple->id][s120].update();
        }
        if (tr->staple->state[0] == 1 && tr->staple->state[1] == 0 && tr->staple->state[2] == 2){
            stparams[tr->staple->id][s102].val++; stparams[tr->staple->id][s102].update();
        }
        if (tr->staple->state[0] == 1 && tr->staple->state[1] == 1 && tr->staple->state[2] == 2){
            stparams[tr->staple->id][s112].val++; stparams[tr->staple->id][s112].update();
        }
        if (tr->staple->state[0] == 2 && tr->staple->state[1] == 1 && tr->staple->state[2] == 1){
            stparams[tr->staple->id][s211].val++; stparams[tr->staple->id][s211].update();
        }
        if (tr->staple->state[0] == 1 && tr->staple->state[1] == 2 && tr->staple->state[2] == 1){
            stparams[tr->staple->id][s121].val++; stparams[tr->staple->id][s121].update();
        }
        if (tr->staple->state[0] == 1 && tr->staple->state[1] == 2 && tr->staple->state[2] == 3){
            stparams[tr->staple->id][s123].val++; stparams[tr->staple->id][s123].update();
        }
        if (tr->staple->state[0] == 1 && tr->staple->state[1] == 1 && tr->staple->state[2] == 1){
            stparams[tr->staple->id][s111].val++; stparams[tr->staple->id][s111].update();
        }
    }
    */
}

Statistics::Statistics(const Inputs* inputs, const Design* design, const bool full){
    n_transitions = 0;
    double increment = inputs->const_T_interval/Cpm2spC(inputs->cool_rate);
    for (double Temp = inputs->min_temp; Temp <= inputs->max_temp; Temp += increment){
        vec.push_back(Stat(Temp, design));
    }
    if (full){
        for (auto st = design->staples.begin(); st != design->staples.end(); ++st){
            if (st->n_domains == 1){
                vec[0].params[N_H_dom].val++;   vec[0].params[N_H_dom].average++;
                vec[0].params[N_H_st].val++;    vec[0].params[N_H_st].average++;
            }
            if (st->n_domains == 2){
                vec[0].params[N_U_dom].val+=2;  vec[0].params[N_U_dom].average+=2;
                vec[0].params[N_U_st].val++;    vec[0].params[N_U_st].average++;
                vec[0].params[N_cross].val++;   vec[0].params[N_cross].average++;
            }
            if (st->n_domains == 3){
                vec[0].params[N_S_dom].val+=3;   vec[0].params[N_S_dom].average+=3;
                vec[0].params[N_S_st].val++;   vec[0].params[N_S_st].average++;
                vec[0].params[N_cross].val+=2;   vec[0].params[N_cross].average+=2;
            }
        }
        for (auto dom = design->domains.begin(); dom != design->domains.end(); ++dom){
            vec[0].params[N_nucs].val+=dom->length;   vec[0].params[N_nucs].average+=dom->length;
        }
        //cout << vec[vec.size()-1].params[N_nucs].val << endl;
    }
    stat = -1;
}
void Statistics::select_stat(double T){
    int last_stat = stat;
    for (int i = 0; i<vec.size(); i++){
        if (abs(T- (vec[i]).T ) < 0.001){
            stat = i;
            continue;
        }
    }
    if (last_stat!=-1){
        for (int i = 0; i < vec[stat].params.size(); i++){
            vec[stat].params[i].val = vec[last_stat].params[i].val;
            vec[stat].params[i].average = vec[last_stat].params[i].average;
        }
    }
}
void Statistics::update(const TR tr){
    vec[stat].update(tr);
    this->n_transitions++;
}

void Statistics::write(const string& statistics_file_name){
    ofstream statistics_file;
    statistics_file.open(statistics_file_name);
    statistics_file << n_transitions << "\n";
    for (auto stat = vec.begin(); stat != vec.end(); ++stat){
        stat->write(statistics_file);
    }
    statistics_file.close();
}


