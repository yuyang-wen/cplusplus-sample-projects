//
//  NodeList.cpp
//
//  Created by Yuyang on 2017-11-06.
//  Copyright © 2017 Yuyang. All rights reserved.
//

#include "NodeList.h"
NodeList::NodeList(){
    head = NULL;
}

NodeList::~NodeList(){
    Node *p;
    while (head != NULL){
        p = head;
        head = p -> getNext();
        delete p;
    }
    
}

//find node return pointer or null
Node * NodeList :: findNode(int _nodeID){
    if (head == NULL)
        return NULL;
    for (Node *temp = head; temp != NULL; temp = temp -> getNext()){
        if (temp->getID() == _nodeID)
            return temp;
        else if (temp->getID() > _nodeID ||temp->getNext() == NULL)
            return NULL;
    }
    return NULL;
}

//find/insesrt node return pointer to node or create new
Node * NodeList::insertNode(int _nodeID){
    if (NodeExists(_nodeID)!=NULL)
        return NodeExists(_nodeID);
    else if(head==NULL){
        head = new Node(_nodeID,NULL);
        return head;
    }
    else if(head->getID()>_nodeID){
        Node *toSet = new Node(_nodeID,head);
        head = toSet;
        return head;

    }
    else
        for (Node *temp = head; temp != NULL; temp = temp -> getNext()){
            if (temp->getNext()==NULL){
                Node *toSet = new Node(_nodeID,temp->getNext());
                temp->setNext(toSet);
                return toSet;
            }
            if (temp->getNext()->getID() > _nodeID){
                Node *toSet = new Node(_nodeID,temp->getNext());
                temp->setNext(toSet);
                return toSet;
            }
        }
    return NULL;
}

//determine if a resistor exists
bool NodeList::resistorExist(string _name){
    if (head==NULL)
        return false;
    for (Node * temp = head; temp !=NULL; temp = temp -> getNext()){
        if ( temp->getResistorList()->findResistor(_name) != NULL)
            return true;
    }
    return false;
}

void NodeList::printResistor(string _name){
    for (Node * temp = head; temp !=NULL; temp = temp -> getNext()){
        if ( temp->getResistorList()->findResistor(_name) != NULL){
            Resistor * cur = temp->getResistorList()->findResistor(_name);
            cout << setw(20) << left << cur->getName() << " " << setprecision(2) << fixed << cur->getResistance() << " Ohms " << cur->getNodeID(0) << " -> " << cur->getNodeID(1) << endl;
            return;
        }
    }
}

void NodeList::printNode(int _ID){
    Node * temp = NodeExists(_ID);
    if (temp->countResistor()==0) return;
    cout << "Connection at node "<< _ID << ": "<< temp->countResistor() << " resistors(s)"<<endl;
    for (Resistor * cur = temp->getResistorList()->getHead();cur != NULL; cur = cur->getNext()){
        cout <<"  "<< setw(20) << left << cur->getName() << " " << setprecision(2) << fixed << cur->getResistance() << " Ohms " << cur->getNodeID(0) << " -> " << cur->getNodeID(1) << endl;
    }
}

void NodeList::printNodeAll(){
    if (head==NULL) return;
    for (Node * temp = head; temp != NULL; temp = temp -> getNext()){
        printNode(temp->getID());
    }
}

//change the resistance of resistor / return fail
double NodeList::changeResistance(string _name, double _resistance){
    if (head==NULL)return -1;
    for (Node * temp = head; temp !=NULL; temp = temp -> getNext()){
        for (Resistor * cur = temp -> getResistorList()->getHead(); cur != NULL; cur = cur -> getNext()){
            if (cur->getName() == _name){
                double old = cur->getResistance();
                cur->changeResistance(_resistance);
                return old;
            }
        }
    }
    return -1;

}

//delete resistor by name
bool NodeList::deleteResistor(string _name){
    bool x = false;
    
    if(head==NULL) return false;
    
    for (Node * temp = head; temp !=NULL; temp = temp -> getNext()){
        x = temp->getResistorList()->deleteResistor(_name);
    }
    
    return x;
}

//delete all resistors
void NodeList::deleteAll(){
    for (Node * temp = head; temp !=NULL; temp = temp -> getNext()){
        delete temp->getResistorList();
        temp->setResistorList();
        temp->setC(false);
    }
}

void NodeList::solve(){
    double change=0, A=0, B=0;
    do {
        change=0;
        for (Node* temp = head; temp != NULL; temp = temp -> getNext()) {
            if (!temp->getsetV()){
                A=0;
                B=0;
                for (Resistor * cur = temp->getResistorList()->getHead(); cur != NULL; cur = cur ->getNext()){
                    A=A+(1/(cur->getResistance()));
                    int otherEnd = cur->getOther(temp->getID());
                    B=B+((NodeExists(otherEnd)->getV())/(cur->getResistance()));
                }
                double temp_change = abs((temp->getV())-((1/A)*B));
                if(temp_change>change)change=temp_change;
                temp->setVol(((1/A)*B));
            }
        }
    } while (change > MIN_ITERATION_CHANGE);
    
    for(Node* print=head; print!=NULL; print = print->getNext()){
        cout << "Node: "<<print->getID()<<": "<<setprecision(2) << fixed <<print->getV()<<" V"<<endl;

    }
}

Node * NodeList::NodeExists(int ID){
    if (head==NULL) return NULL;
    for (Node * temp = head; temp != NULL; temp = temp -> getNext()){
        if(temp->getID()==ID) return temp;
    }
    return NULL;
}
