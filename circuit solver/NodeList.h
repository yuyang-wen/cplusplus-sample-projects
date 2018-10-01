//
//  NodeList.h
//
//  Created by Yuyang on 2017-11-06.
//  Copyright © 2017 Yuyang. All rights reserved.
//

#ifndef NodeList_h
#define NodeList_h

#include <stdio.h>

#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>
#include "Rparser.h"
#include "Node.h"
#include "Resistor.h"

#define MIN_ITERATION_CHANGE 0.0001

using namespace std;

class NodeList
{
    
private:
    Node* head;
    
public:
    NodeList();
    ~NodeList();

    //void insertval, bool value exists, bool deleteval
    
    //find node return pointer or null
    Node *  findNode(int _nodeID);
    
    //find/insesrt node return pointer to node or create new
    Node * insertNode(int _nodeID);
    
    //determine if a resistor exists
    bool resistorExist(string _name);
    
    void printResistor(string _name);
    
    void printNode(int _ID);
    
    void printNodeAll();
    
    //change the resistance of resistor / return fail
    double changeResistance(string _name, double _resistance);
    
    //delete resistor by name
    bool deleteResistor(string _name);
    
    //delete all resistors
    void deleteAll();
    
    void solve();
    
    Node* NodeExists(int ID);
};


#endif /* NodeList_hpp */
