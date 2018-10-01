#ifndef RESISTOR_H
#define RESISTOR_H

#include <string>
#include <iostream>
#include <iomanip>
#include "Rparser.h"
using namespace std;

class Resistor
{
    
private:
    
    double resistance = 0.0; // resistance (in Ohms)
    string name; // C++ string holding the label
    int endpointNodeIDs[2]; // IDs of nodes it attaches to
    Resistor * next;

public:
    
    Resistor();
    Resistor(string name_,double resistance_,int endpoints_[2]);
    ~Resistor();
    string getName () const;
    Resistor * getNext () const;
    void changeResistance(double _resistance);
    double getResistance() const;
    void setResistance(double _resistance);
    void setNext(Resistor * _toSet);
    int getNodeID(int index);
    int getOther(int _ID) const;
};


#endif	/* RESISTOR_H */

