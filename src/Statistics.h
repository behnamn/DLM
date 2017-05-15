//
//  Statistics.h
//  DLM_XC
//
//  Created by Behnam Najafi on 09/05/2017.
//  Copyright © 2017 Behnam Najafi. All rights reserved.
//

#ifndef Statistics_h
#define Statistics_h

#include "Common.h"
#include "Input.h"
#include "Transition.h"
#include "Design.h"

enum param_t {N_nucs, N_cross, N_H_dom, N_U_dom, N_S_dom, N_H_st, N_U_st, N_S_st, param_t_MAX};
class Param{
public:
    param_t pt;
    int n;
    int val;
    double average;
    void update(){
        n++;
        average = average + ( ((val) - average) / (n*1.) );
    }
};

/*
enum stparam_t {s0, s1, s00, s10, s01, s11, s12, s000, s001, s010, s100, s011, s110, s101, s012, s120, s102, s112, s211, s121, s123, s111, stparam_t_MAX};
class stParam{
public:
    stparam_t pt;
    //stParam(const Staple& staple_) : staple(staple_) {}
    stParam(){}
    virtual ~stParam(){}
    //const Staple& staple;
    int n;
    int val;
    double average;
    void update(){
        n++;
        average = average + ( ((val) - average) / (n*1.) );
    }
};
*/

class Stat{
public:
    double T;
    const Design* design;
    int n_transitions;
    vector<Param> params;
    //vector<vector<stParam> > stparams;
    //vector<domParam> domParam;
    
    Stat(double, const Design*);
    virtual ~Stat(){}
    void update(const TR);
    void write(ofstream&);
};

class Statistics{
public:
    Statistics(const Inputs*, const Design*, const bool full = false);
    int n_transitions;
    vector<Stat> vec;
    int stat;
    virtual ~Statistics(){}
    void update(const TR);
    void select_stat(double);
    void write(const string&);
};

#endif /* Statistics_h */
