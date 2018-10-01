//
//  ResistorList.hpp
//
//  Created by Yuyang on 2017-11-06.
//  Copyright © 2017 Yuyang. All rights reserved.
//

#ifndef ResistorList_hpp
#define ResistorList_hpp

#include <stdio.h>
#include "Resistor.h"

using namespace std;

class ResistorList
{
private:
    Resistor * head;
    
public:
    ResistorList();
    ~ResistorList();
    void insertResistor(Resistor * _toInsert);
    Resistor * findResistor(string _name);
    bool deleteResistor(string _name);
    Resistor * getHead() const;
};

#endif /* ResistorList_hpp */
