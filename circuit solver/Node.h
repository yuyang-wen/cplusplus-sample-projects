#ifndef NODE_H
#define NODE_H

#include "Rparser.h"
#include "ResistorList.h"

class Node
{
    
private:
    
    int nodeID;
    Node *next;
    ResistorList *connected;
    bool setV=false;
    double Voltage = 0;
    bool connect=true;

public:
    
    Node();
    Node (int _ID, Node *_next);
    ~Node();
    int getID() const;
    Node * getNext() const;
    ResistorList * getResistorList() const;
    void setNext(Node *_next);
    int countResistor();
    bool getsetV()const;
    double getV()const;
    void set(bool _set);
    void setVol(double _vol);
    void setC(bool _c);
    void setResistorList();

};

#endif	/* NODE_H */

