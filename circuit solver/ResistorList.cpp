//
//  ResistorList.cpp
//
//  Created by Yuyang on 2017-11-06.
//  Copyright © 2017 Yuyang. All rights reserved.
//

#include "ResistorList.h"
#include "Resistor.h"

ResistorList::ResistorList(){
    head = NULL;
}
ResistorList::~ResistorList(){
    
   Resistor *p;
    while (head != NULL){
        p = head;
        head = p -> getNext();
        delete p;
    }
}
Resistor * ResistorList::getHead() const{
    return head;
}

void ResistorList::insertResistor(Resistor * _toInsert ){
    if (head == NULL)
        head=_toInsert;
    else{
        for (Resistor *temp = head; temp != NULL; temp = temp -> getNext()){
            if (temp->getNext()==NULL){
                temp->setNext(_toInsert);
                return;
            }
        }
    }
}

Resistor * ResistorList::findResistor(string _name){
    if (head == NULL)
        return NULL;
    else{
        for (Resistor *temp = head; temp != NULL; temp = temp -> getNext()){
            if (temp->getName()==_name)
                return temp;
        }
    }
    return NULL;
}

bool ResistorList::deleteResistor(string _name){
    if (head == NULL)
        return false;
    else{
        if (head->getName()==_name){
            Resistor * toDelete = head;
            head = head->getNext();
            delete toDelete;
            return true;
        }
        else{
        for (Resistor *temp = head; temp -> getNext() != NULL; temp = temp -> getNext()){
            if (temp->getNext()->getName()==_name){
                Resistor * toDelete = temp->getNext();
                temp->setNext(toDelete->getNext());
                delete toDelete;
                return true;
            }
        }
        }
    }
    return false;
}

