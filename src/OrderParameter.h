//
//  OrderParameter.h
//  DLM_XC
//
//  Created by Behnam Najafi on 03/05/2017.
//  Copyright © 2017 Behnam Najafi. All rights reserved.
//

#ifndef OrderParameter_h
#define OrderParameter_h

#include "Common.h"

class OrderParameter{
public:
    OrderParameter(){}
    ~OrderParameter(){}
    
    OrderParameter(string);
    
    string name;
    int value;
    
    OrderParameter operator ++ ();
    
};

vector<OrderParameter>::iterator OP;

#endif
