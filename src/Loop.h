//
//  Loop.h
//  DLM_XC
//
//  Created by Behnam Najafi on 03/05/2017.
//  Copyright © 2017 Behnam Najafi. All rights reserved.
//

#ifndef LOOP_h
#define LOOP_h

#include "../Headers/Graph.h"
#include "Design.h"

class Loop {
public:
    Path vec;
    double weight;
    void calculate_weight();
    void recalculate_weight(DOM);
};

class FaceManager : public planar_face_traversal_visitor {
public:
    vector<Loop> faces;
    int i;
    void begin_traversal(){
        i = 0;
        faces.clear();
    }
    void begin_face() {
        Loop L;
        faces.push_back(L);
    }
    void end_face() {
        i++;
    }
    template <typename Edge>
    void next_edge(Edge e)
    {
        (faces[i].vec).push_back(e);
    }
    void end_traversal(){//removing the big overall loop
        faces.erase(faces.begin());
    }
    void test(int j){
        faces.erase(faces.end()-j);
    }
};

#endif /* Loop_h */
