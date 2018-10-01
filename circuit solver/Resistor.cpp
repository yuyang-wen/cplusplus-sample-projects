//
//  Resistor.cpp
//
//  Created by Yuyang on 2017-10-15.
//  Copyright © 2017 Yuyang. All rights reserved.
//

#include "Resistor.h"
Resistor::Resistor(){
}
Resistor::Resistor(string name_,double resistance_,int endpoints_[2]){
    name = name_;
    resistance = resistance_;
    endpointNodeIDs[0] = endpoints_ [0];
    endpointNodeIDs[1] = endpoints_ [1];
    next=NULL;
}

Resistor::~Resistor(){
}

string Resistor::getName() const{
    return name;
}// returns the name

double Resistor::getResistance() const{
    return resistance;
}// returns the resistance

void Resistor::setResistance (double resistance_){
    resistance = resistance_;
}

void Resistor::setNext(Resistor * _toSet){
    next = _toSet;
}

int Resistor::getNodeID(int index){
    return endpointNodeIDs[index];
}

void Resistor::changeResistance(double _resistance){
    resistance = _resistance;
}

Resistor * Resistor::getNext() const{
    return next;
}

int Resistor::getOther(int _ID) const{
    if (endpointNodeIDs[0]==_ID) return endpointNodeIDs[1];
    else return endpointNodeIDs[0];
}
