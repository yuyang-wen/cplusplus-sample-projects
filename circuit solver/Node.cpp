//
//  Node.cpp
//  lab3
//
//  Created by Yuyang on 2017-10-15.
//  Copyright © 2017 Yuyang. All rights reserved.
//

#include "Node.h"

Node::Node(){
}

Node::Node(int _NodeID, Node * _next){
    nodeID = _NodeID;
    next = _next;
    connected = new ResistorList;
    setV = false;
    Voltage = 0;
}

Node::~Node(){
    if (connected!=NULL) delete connected;
}

int Node::getID() const{
    return nodeID;
}

Node * Node::getNext() const{
    return next;
}

void Node::setNext(Node *_next){
    next = _next;
    return;
}

ResistorList * Node::getResistorList() const{
    return connected;
}

int Node::countResistor() {
    int count = -1;
    for (Resistor* temp = connected->getHead();;){
        count=count+1;
        if(temp==NULL||connect==false) return count;
        else temp=temp->getNext();
    }
}

bool Node::getsetV()const{
    return setV;
}
double Node::getV()const{
    return Voltage;
}
void Node::set(bool _set){
    setV = _set;
}
void Node::setVol(double _vol){
    Voltage = _vol;
}

void Node::setC(bool _c){
    connect = _c;
}

void Node::setResistorList(){
    connected = new ResistorList;
}
