//
//  main.cpp
//
//  Created by Yuyang on 2017-11-21.
//  Copyright © 2017 Yuyang. All rights reserved.
//

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include "DBentry.h"
#include "TreeDB.h"
#include "TreeNode.h"

using namespace std;

void printErrorDNE () {
    cout<<"Error: entry does not exist"<<endl;
}

int main(int argc, const char * argv[]) {
    string line;
    string command;
    string name;
    string active;
    unsigned int IPaddress;
    bool status;
    TreeDB * DB = new TreeDB();
    cout<<"> ";
    getline(cin, line);

    
    while (!cin.eof()){
        stringstream linestream (line);
    while(true){
        string command;
        linestream >> command;
        if (command=="insert"){
            linestream >> name;
            linestream >> IPaddress;
            linestream >> active;
            
            if (active == "active") status = true;
            else status = false;
            
            DBentry * toInsert = new DBentry(name,IPaddress,status);
            
            if(!(DB->insert(toInsert))){
                cout<<"Error: entry already exists"<<endl;
                delete toInsert;
                break;
            };
            
            cout<<"Success"<<endl;
        }
        
        else if (command=="find"){
            linestream >> name;
            
            DBentry * found = DB->find(name);
            
            if (found == NULL){
                printErrorDNE();
                break;
            }
            
            if (found->getActive()== true) active = "active";
            else active = "inactive";
            
            cout << found->getName() << " : " << found->getIPaddress() << " : " << active <<endl;
            
        }

        else if (command=="remove"){
            linestream >> name;
            
            if (!DB->remove(name)){
                printErrorDNE();
                break;
            }
            
            cout << "Success" <<endl;

        }

        else if (command=="printall"){
            cout<<*DB;
        }

        else if (command=="printprobes"){
            linestream >> name;
            if(DB->find(name)==NULL){
                printErrorDNE();
                break;
            }
            DB->printProbes();
        }

        else if (command=="removeall"){
            DB->clear();
            cout << "Success" <<endl;
        }

        else if (command=="countactive"){
            DB->countActive();
        }

        else if (command=="updatestatus"){
            linestream >> name;
            linestream >> active;
            
            if (active == "active") status = true;
            else status = false;
            
            DBentry * temp = DB->find(name);
            
            if (temp==NULL){
                printErrorDNE();
                break;
            }
            
            temp->setActive(status);
            cout << "Success" << endl;
            
        }

        else {
            cout<<"invalid command"<<endl;
            break;
        }
        
        break;
        
    }
        cout<<"> ";
        getline(cin, line);
    }
    
    DB->clear();
    delete DB;
    return 0;
}


