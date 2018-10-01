//
//  Rparser.cpp
//
//  Created by Yuyang on 2017-10-15.
//  Copyright © 2017 Yuyang. All rights reserved.
//

#include "Rparser.h"
#include "Node.h"
#include "Resistor.h"
#include "NodeList.h"
#include "ResistorList.h"

int Rparser(void) {
    
    //variable declaration
    string line, name, teststring, endcheck;
    int nodeid[2];
    double resistance;
    NodeList* nodeNetWork = new NodeList();
    int voltageCount = 0;

    //initial input prompt
    cout<<"> ";
    getline (cin, line);
    
    //while loop for new commands
    while (!cin.eof()){
        string command;
        
        //lineStream for arguments
        stringstream lineStream (line);
        
        //testStream will be advanced with lineStream for length check
        stringstream testStream (line);
        
        //while loop to set up break
        while (true){
            lineStream >> command;
            testStream >> teststring;
            
            //insert command
            if (command=="insertR"){
                
                lineStream >> name;
                testStream >> teststring;
                
                //check if empty
                if(emptyCheck(testStream))break;
                
                //check if not all
                if(name=="all"){
                    cout << "Error: resistor name cannot be the keyword \"all\"" << endl;
                    break;
                };
                
                
                lineStream >> resistance;
                testStream >> teststring;
                
                //check if empty
                if(emptyCheck(testStream)) break;
                
                //check if type is valid
                if (!validCheck(lineStream)) break;
                
                //check if input is a positive number with no trailing letters
                if (!resistanceCheck(resistance, lineStream)) break;
                
                
                lineStream >> nodeid[0];
                testStream >> teststring;
                
                //check if empty
                if(emptyCheck(testStream)) break;
                
                //check if type is valid
                if (!validCheck(lineStream)) break;
                
                //check if 0 < int < max
                if (!nodeCheck(lineStream, nodeid[0])) break;
                
                
                lineStream >> nodeid[1];
                testStream >> teststring;
                
                //check if empty
                if(emptyCheck(testStream)) break;
                
                //check if type is valid
                if (!validCheck(lineStream)) break;
                
                //check if 0 < int < max
                if (!nodeCheck(lineStream, nodeid[1])) break;
                
                
                //check if the argument line has ended
                testStream >> teststring;
                if(!testStream.fail()){
                    cout << "Error: too many arguments" << endl;
                    break;
                }
                
                
                //check if name is taken
                if (nodeNetWork->resistorExist(name)){
                    cout << "Error: resistor "<< name <<" already exists"<<endl;
                    break;
                }
                
                
                //check if the nodes are equal
                if (nodeid[0] == nodeid[1]){
                    cout << "Error: both terminals of resistor connect to node " << nodeid[0] << endl;
                    break;
                }

                
                //success
                //update resistor list
                
                Node*temp0 = nodeNetWork->NodeExists(nodeid[0]);
                Node*temp1 = nodeNetWork->NodeExists(nodeid[1]);
                if (temp0==NULL)
                temp0 = nodeNetWork->insertNode(nodeid[0]);
                if (temp1==NULL)
                temp1 = nodeNetWork->insertNode(nodeid[1]);
                
                Resistor* in1 = new Resistor (name, resistance, nodeid);
                Resistor* in2 = new Resistor (name, resistance, nodeid);
                
                temp0->getResistorList()->insertResistor(in1);
                temp1->getResistorList()->insertResistor(in2);
                temp0->setC(true);
                temp1->setC(true);
                
                //success statement
                cout<<"Inserted: resistor " << name << " " << setprecision(2) << fixed << resistance << " Ohms " << nodeid[0] << " -> " << nodeid[1] << endl;
            }
            



            
            else if (command == "modifyR"){
                
                lineStream >> name;
                testStream >> teststring;
                
                //check if empty
                if(emptyCheck(testStream))break;
                
                //check if not all
                if(name=="all"){
                    cout << "Error: resistor name cannot be the keyword \"all\"" << endl;
                    break;
                };
                
                lineStream >> resistance;
                testStream >> teststring;
                
                //check if empty
                if(emptyCheck(testStream))break;
                
                //check if type is valid
                if (!validCheck(lineStream)) break;
                
                //check if positive number with no trailing letters
                if (!resistanceCheck(resistance, lineStream)) break;
                
                //check if the argument line has ended
                testStream >> teststring;
                if(!testStream.fail()){
                    cout << "Error: too many arguments" << endl;
                    break;
                }
                
                //check if name exists
                if(!nodeNetWork->resistorExist(name)){
                    cout<<"Error: resistor "<<name<<" not found"<<endl;
                    break;
                }
                
                
                
                //change resistance
                double resistanceOG = nodeNetWork -> changeResistance(name, resistance);
                
                
                //success statemnet
                cout << "Modified: resistor " << name << " from " <<setprecision(2) << fixed << resistanceOG << " Ohms to " << setprecision(2) << fixed << resistance << " Ohms" << endl;
            }
            
            else if (command == "printR"){
                
                //check if empty
                lineStream >> name;
                testStream >> teststring;
                if (emptyCheck(testStream))break;
                
                //check for print all
                if(name == "all"){
                    
                    //check if too many arguments
                    cout << "Error: cannot print all resistors"<<endl;
                    break;
                    
                }
                
                //check if argument line has ended
                testStream >> teststring;
                if(!testStream.fail()){
                    cout << "Error: too many arguments" << endl;
                    break;
                }
                
                //success
                //check if name exists
                if (!nodeNetWork -> resistorExist(name)){
                    cout << "Error: resistor "<<name<<" not found"<<endl;
                    break;
                }

                
                else{
                    cout << "Print:" <<endl;
                    nodeNetWork -> printResistor(name);
                }
            }
            
            else if (command == "printNode"){
                
                //check if empty
                testStream >> teststring;
                if(emptyCheck(testStream)) break;
                
                //check if input is all
                if (teststring == "all"){
                    //check if too many arguments
                    testStream >> endcheck;
                    if(!testStream.fail()){
                        cout << "Error: too many arguments" << endl;
                        break;
                    }
                    //success
                    cout << "Print:" << endl;
                    nodeNetWork -> printNodeAll();
                    
                }
                
                //processing input other than all
                else {
                    
                    lineStream >> nodeid[0];
                    
                    //check if type is valid
                    if (!validCheck(lineStream)) break;
                    
                    //check if 0 < int < max
                    if (!nodeCheck(lineStream, nodeid[0])) break;
                    
                    //check if argument line has ended
                    lineStream >> endcheck;
                    if(!lineStream.fail()){
                        cout << "Error: too many arguments" << endl;
                        break;
                    }
                    
                    //success
                    else {
                        cout << "Print: " << endl;
                        nodeNetWork->printNode(nodeid[0]);
                        
                    }
                    
                }
            }
            
            else if (command == "deleteR"){
                
                //check if empty
                lineStream >> name;
                testStream >> teststring;
                if(emptyCheck(testStream))break;
                
                //check if all
                if(name == "all"){
                    
                    //check if argument line has ended
                    lineStream >> endcheck;
                    if(!lineStream.fail()){
                        cout << "Error: too many arguments" << endl;
                        break;
                    }
                    
                    //success
                    nodeNetWork -> deleteAll();
                    voltageCount=0;
                    //success statemnet
                    cout << "Deleted: all resistors" << endl;
                    break;
                }
                
                //check if ended
                testStream >> teststring;
                if(!testStream.fail()){
                    cout << "Error: too many arguments" << endl;
                    break;
                }
                
                if(!nodeNetWork->resistorExist(name)){
                    cout<< "Error: resistor "<<name<<" not found"<<endl;
                    break;
                }
                
                //success
                else {
                    nodeNetWork -> deleteResistor(name);
                    cout << "Deleted: resistor " << name << endl;
                }

            }
            else if (command == "setV"){
                int nodeID;
                double vol;
                
                lineStream >> nodeID;
                testStream >> teststring;
                
                //check if empty
                if(emptyCheck(testStream))break;
                
                //check if type is valid
                if (!validCheck(lineStream)) break;
                
                //check if positive number with no trailing letters
                if (!nodeCheck(lineStream, nodeID)) break;
                
                lineStream >> vol;
                testStream >> teststring;
                
                //check if empty
                if(emptyCheck(testStream))break;
                
                //check if type is valid
                if (!validCheck(lineStream)) break;
                
                //check if the argument line has ended
                testStream >> teststring;
                if(!testStream.fail()){
                    cout << "Error: too many arguments" << endl;
                    break;
                }
                
                //check if node exists
                if(nodeNetWork->NodeExists(nodeID)==NULL){
                    cout << "Error: node "<<nodeID<<" not found"<<endl;
                }
                
                nodeNetWork -> NodeExists(nodeID) -> setVol(vol);
                nodeNetWork -> NodeExists(nodeID) -> set(true);
                
                
                //success statemnet
                cout << "Set: node " << nodeID << " to " <<setprecision(2) << fixed << vol << " Volts" << endl;
                voltageCount++;
            }

            else if (command == "unsetV"){
                int nodeID;
                
                lineStream >> nodeID;
                testStream >> teststring;
                
                //check if empty
                if(emptyCheck(testStream))break;
                
                //check if type is valid
                if (!validCheck(lineStream)) break;
                
                //check if positive number with no trailing letters
                if (!nodeCheck(lineStream, nodeID)) break;
                
                //check if the argument line has ended
                testStream >> teststring;
                if(!testStream.fail()){
                    cout << "Error: too many arguments" << endl;
                    break;
                }
                
                //check if node exists
                if(nodeNetWork->NodeExists(nodeID)==NULL){
                    cout<<"Error: node "<<nodeID<<" not found"<<endl;
                    break;
                }
                
                nodeNetWork -> NodeExists(nodeID) -> setVol(0);
                nodeNetWork -> NodeExists(nodeID) -> set(false);
                
                
                //success statemnet
                cout << "Unset: the solver will determine the voltage of node " << nodeID << endl;
                voltageCount--;
            }
            
            else if (command=="solve"){
                if (voltageCount==0) {
                    cout <<"Error: no nodes have their voltage set"<<endl;
                    break;
                }
                cout <<"Solve: "<<endl;
                nodeNetWork->solve();
            }
            
            else{
                    //invalid command
                    cout << "Error: invalid command" << endl;
                
            }
            
            //breaking out of inner while loop
            break;
        }
        
        //clearing lineStream
        lineStream.ignore(1000, '\n');
        lineStream.clear();
        
        //prompt for new input
        cout<<"> ";
        getline (cin, line);
    }
    
    //clearing memory before exiting
    
    return 0;
}





//this function checks if the input type is valid
bool validCheck(stringstream& varStream){
    if (varStream.fail()){
        cout << "Error: invalid argument" << endl;
        return false;
    }
    else return true;
}

//this function checks if the input is empty by checking if stream >> string is successful (only to be called after stream >> string)
bool emptyCheck(stringstream& varStream){
    if (varStream.fail()){
        cout << "Error: too few arguments" << endl;
        return true;
    }
    else return false;
}

//this function varifies if the resistance value is valid
bool resistanceCheck(double resistance, stringstream& varStream){
    if (varStream.peek() != ' ' && !varStream.eof()){
        cout << "Error: invalid argument" << endl;
        return false;
    }
    else {
        if (resistance < 0){
            cout << "Error: negative resistance" << endl;
            return false;
        }
        else if (resistance >= 0){
            return true;
        }
    }
    return false;
}

//this function varifies if the node value is valid
bool nodeCheck(stringstream& varStream, int nodevar){
    if (varStream.fail()){
        cout << "Error: invalid argument" << endl;
        return false;
    }
    else if (varStream.peek() != ' ' && !varStream.eof()){
        cout << "Error: invalid argument" << endl;
        return false;
    }
    
    else return true;
}

bool maxValCheck(stringstream& varStream, int maxVal){
    if (varStream.fail()){
        cout << "Error: invalid argument" << endl;
        return false;
    }
    else if (varStream.peek() != ' ' && !varStream.eof()){
        cout << "Error: invalid argument" << endl;
        return false;
    }
    else if (maxVal <= 0){
        cout << "Error: maxVal arguments must be greater than 0" << endl;
        return false;
    }
    else return true;
}
