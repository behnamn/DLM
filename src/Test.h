//
//  Test.h
//  DLM_XC
//
//  Created by Behnam Najafi on 10/05/2017.
//  Copyright © 2017 Behnam Najafi. All rights reserved.
//

#ifndef Test_h
#define Test_h

#include "Common.h"

class TransitionProperty {
public:
    TransitionProperty(){
        allowed = false;
        domain = -1;
        bind = false;
        cross = false;
        cross_dom = -1;
    }
    TransitionProperty(bool bind_, short domain_) : bind(bind_) , domain(domain_) {
        allowed = true;
        cross = false;
        cross_dom = -1;
    }
    TransitionProperty(bool bind_, short domain_, short cross_dom_) : bind(bind_) , domain(domain_) , cross_dom(cross_dom_){
        allowed = true;
        cross = true;
    }
    virtual ~TransitionProperty(){}
    bool allowed;
    short domain;
    bool bind;
    bool cross;
    short cross_dom;
};

typedef TransitionProperty TP;



/*
class TransitionListU {
public:
    std::array<string,5> states;
    map<string, std::array<TransitionProperty,5> > transitions;
    
    TransitionListU(){
        states = {"00","10","01","11","12"};
        transitions["00"] = {TP(0),TP("0b"),TP("1b"),TP(0),TP(0)};
        transitions["10"] = {TP("0u"),TP(0),TP(0),TP("1b0"),TP("1b")};
        transitions["01"] = {TP("1u"),TP(0),TP(0),TP("0b1"),TP("0b")};
        transitions["11"] = {TP(0),TP("1u0"),TP("0u1"),TP(0),TP(0)};
        transitions["12"] = {TP(0),TP("1u"),TP("0u"),TP(0),TP(0)};
    }
    virtual ~TransitionListU(){}
};



class TransitionListS {
public:
    std::array<string,15> states;
    map<string, std::array<TransitionProperty,15> > transitions;
    TransitionListS(){
        states = {            "000","001","010","100","011","110","101","012","120","102","112","211","121","123","111"};
        transitions["000"] = {TP(0),TP("2b"),TP("1b"),TP("0b"),TP(0),TP(0),TP(0),TP(0),TP(0),TP(0),TP(0),TP(0),TP(0),TP(0),TP(0)};
        transitions["001"] = {TP("2u"),TP(0),TP(0),TP(0),TP("1b2"),TP(0),TP("0b2"),TP("1b"),TP(0),TP("0b"),TP(0),TP(0),TP(0),TP(0),TP(0)};
        transitions["010"] = {TP("1u"),TP(0),TP(0),TP(0),TP("2b1"),TP("0b1"),TP(0),TP("2b"),TP("0b"),TP(0),TP(0),TP(0),TP(0),TP(0),TP(0)};
        transitions["100"] = {TP("0u"),TP(0),TP(0),TP(0),TP(0),TP("1b0"),TP("2b0"),TP(0),TP("1b"),TP("2b"),TP(0),TP(0),TP(0),TP(0),TP(0)};
        transitions["011"] = {TP(0),TP("1u2"),TP("2u1"),TP(0),TP(0),TP(0),TP(0),TP(0),TP(0),TP(0),TP(0),TP("0b"),TP(0),TP(0),TP("0b1")};
        transitions["110"] = {TP(0),TP(0),TP("0u1"),TP("1u0"),TP(0),TP(0),TP(0),TP(0),TP(0),TP(0),TP("2b"),TP(0),TP(0),TP(0),TP("2b1")};
        transitions["101"] = {TP(0),TP("0u2"),TP(0),TP("2u0"),TP(0),TP(0),TP(0),TP(0),TP(0),TP(0),TP(0),TP(0),TP("1b"),TP(0),TP(0)};
        transitions["012"] = {TP(0),TP("1u"),TP("2u"),TP(0),TP(0),TP(0),TP(0),TP(0),TP(0),TP(0),TP("0b1"),TP(0),TP("0b2"),TP("0b"),TP(0)};
        transitions["120"] = {TP(0),TP(0),TP("0u"),TP("1u"),TP(0),TP(0),TP(0),TP(0),TP(0),TP(0),TP(0),TP("2b1"),TP("2b0"),TP("2b"),TP(0)};
        transitions["102"] = {TP(0),TP("0u"),TP(0),TP("2u"),TP(0),TP(0),TP(0),TP(0),TP(0),TP(0),TP("1b0"),TP("1b2"),TP(0),TP("1b"),TP(0)};
        transitions["112"] = {TP(0),TP(0),TP(0),TP(0),TP(0),TP("2u"),TP(0),TP("0u1"),TP(0),TP("1u0"),TP(0),TP(0),TP(0),TP(0),TP(0)};
        transitions["211"] = {TP(0),TP(0),TP(0),TP(0),TP("0u"),TP(0),TP(0),TP(0),TP("2u1"),TP("1u2"),TP(0),TP(0),TP(0),TP(0),TP(0)};
        transitions["121"] = {TP(0),TP(0),TP(0),TP(0),TP(0),TP(0),TP("1u"),TP("0u2"),TP("2u0"),TP(0),TP(0),TP(0),TP(0),TP(0),TP(0)};
        transitions["123"] = {TP(0),TP(0),TP(0),TP(0),TP(0),TP(0),TP(0),TP("0u"),TP("2u"),TP("1u"),TP(0),TP(0),TP(0),TP(0),TP(0)};
        transitions["111"] = {TP(0),TP(0),TP(0),TP(0),TP("0u1"),TP("2u1"),TP(0),TP(0),TP(0),TP(0),TP(0),TP(0),TP(0),TP(0),TP(0)};
    }
    virtual ~TransitionListS(){}
};

*/


#endif /* Test_h */
