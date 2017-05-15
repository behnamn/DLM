/*
 *
 *	TempRamp.h
 * 	Author: Behnam
 *
 */

#ifndef TEMPRAMP_H_
#define TEMPRAMP_H_

#include "Common.h"
#include "Input.h"

class TempRamp{
public:
    TempRamp();
    virtual ~TempRamp(){}
    //TempRamp(double T_start_, double T_end_, double cool_rate_, int n_cycles_);
    
    Inputs * inputs;

    int _current_t;
    vector<double> _ramp;
    
    double T_high;
    double T_low;
    bool anneal;
    bool melt;
    double cool_rate; // seconds/K   ***should be 60.
    int n_cycles;
    
    double t_max; // seconds
    double t_max_in_each;

    double current_t;
    double current_T;

    double previous_T;
    bool T_was_changed;
    
    void _fill_anneal();
    void _fill_melt();
    
    void print_ramp();
    void set_temp(double);

    void set_time(double);
    void move_time(double);
    double get_T();
};

class AnnealMelt: public TempRamp{
public:
    AnnealMelt(Inputs*);
    virtual ~AnnealMelt(){}
    void _fill_ramp();
};

class Anneal: public TempRamp{
public:
    Anneal(Inputs*);
    virtual ~Anneal(){}
    void _fill_ramp();
};

class Melt: public TempRamp{
public:
    Melt(Inputs*);
    virtual ~Melt(){}
    void _fill_ramp();
};


#endif
