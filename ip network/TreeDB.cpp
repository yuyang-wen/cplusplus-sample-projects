//
//  TreeDB.cpp
//
//  Created by Yuyang on 2017-11-21.
//  Copyright © 2017 Yuyang. All rights reserved.
//

#include "TreeDB.h"


// the default constructor, creates an empty database.
TreeDB::TreeDB(){
    root = NULL;
    total = 0;
    probesCount = 0;
}

// the destructor, deletes all the entries in the database.
TreeDB::~TreeDB(){
}

int TreeDB::count(TreeNode * cur, int num) const {
    
    if(cur!=NULL){
        num = num + count(cur->getLeft(),num) + count(cur->getRight(),num);
        if (cur->getEntry()->getActive()){
            num=num+1;
            return num;
        }
    }
    return num;
}

void TreeDB::deleteAll (TreeNode* cur) {

    if (cur == NULL) return;
    deleteAll(cur->getLeft());
    deleteAll(cur->getRight());
    delete cur;
    root = NULL;
}

void TreeDB::insertNode(TreeNode * cur, DBentry * newEntry){
    
    
    if ((cur->getEntry()->getName()) > (newEntry->getName())){
        if (cur->getLeft() == NULL){
            //left = new
            cur->setLeft(new TreeNode(newEntry));
        }
        else{
            //left = insert recursion
            insertNode(cur->getLeft(), newEntry);
        }
        
    }
    
    else {
        if (cur->getRight() == NULL){
            //right = new
            cur->setRight(new TreeNode(newEntry));
        }
        else{
            //right= insert recursion
            insertNode(cur->getRight(), newEntry);
        }
    }
}

TreeNode* TreeDB::findNode(TreeNode * cur, string _name){
    probesCount++;
   if (cur==NULL){
        return NULL;
   }
    
   if (cur->getEntry()->getName()==_name){
        return cur;
   }
   if (cur->getEntry()->getName() > _name){
        if (cur->getLeft() == NULL){
            //left = new
            return NULL;
        }
        else{
            //left = insert recursion
            return findNode(cur->getLeft(), _name);
        }
    }
    
    else {
        if (cur->getRight() == NULL){
            //right = new
            return NULL;
        }
        else{
            //right = insert recursion
            return findNode(cur->getRight(), _name);
        }
    }
    
}



TreeNode* TreeDB::findParent(TreeNode * cur, TreeNode * child) const{
    
    if (cur == child)
        return NULL;
    
    if (cur->getRight()!=NULL)
    return (findParent(cur->getRight(), child));
    
    if (cur->getLeft()!=NULL)
    return (findParent(cur->getLeft(), child));

    if (cur->getRight()==child || cur->getRight()==child){
        return cur;
    }
    
    return cur;
}


TreeNode* TreeDB::locateMax(TreeNode * cur){

    if (cur->getRight()==NULL){
        return cur;
    }
    
    else {
        return locateMax(cur->getRight());
    }
}

TreeNode* TreeDB::locateMin(TreeNode * cur){
    
    if (cur->getLeft()==NULL){
        return cur;
    }
    
    else {
        return locateMin(cur->getLeft());
    }
}


// inserts the entry pointed to by newEntry into the database.
// If an entry with the same key as newEntry's exists
// in the database, it returns false. Otherwise, it returns true.
bool TreeDB::insert(DBentry* newEntry){
    if (total==0){
        root = new TreeNode(newEntry);
        total++;
        return true;
    }
    if (find(newEntry->getName())!=NULL){
        return false;
    }

    insertNode(root, newEntry);
    total++;
    return true;
}

// searches the database for an entry with a key equal to name.
// If the entry is found, a pointer to it is returned.
// If the entry is not found, the NULL pointer is returned.
// Also sets probesCount
DBentry* TreeDB::find(string name){
    probesCount=0;
    if (total==0){
        return NULL;
    }
    TreeNode* temp = findNode(root, name);
    if (temp==NULL){
        return NULL;
    }
    else {
    DBentry* returnVal = (temp->getEntry());
    return returnVal;
    }
}

void TreeDB::removeNode(string name, TreeNode * cur){//v
    if (name < cur->getEntry()->getName()){
        if (cur->getLeft()!=NULL)

            removeNode(name,(cur->getLeft()));
        
        return;
    }
    if (name > cur->getEntry()->getName()){
        if (cur->getRight() != NULL)
            removeNode(name,cur->getRight());
        return;
    }
    if ((cur->getLeft()==NULL)&&(cur->getRight()==NULL)){
        TreeNode * parent = findParent(root, cur);
        if (parent!=NULL){
        parent->setLeft(NULL);
        parent->setRight(NULL);
        delete cur;
        }
        else {
            delete cur;

        }
    }
    else if ((cur->getLeft()==NULL)&&(cur->getRight()!=NULL)){
        TreeNode * temp = cur;
        TreeNode * parent = findParent(root, cur);
        if (parent!=NULL){
            if (parent->getRight()==cur)
                parent->setRight(cur->getRight());
            if (parent->getLeft()==cur)
                parent->setLeft(cur->getRight());}
        else (root=cur->getRight());
        delete temp;
    }
    else if ((cur->getLeft()!=NULL)&&(cur->getRight()==NULL)){
        TreeNode * temp = cur;
        TreeNode * parent = findParent(root, cur);
        if (parent!=NULL){
            if (parent->getRight()==cur)
                parent->setRight(cur->getLeft());
            if (parent->getLeft()==cur)
                parent->setLeft(cur->getLeft());}
        else (root=cur->getLeft());
        delete temp;
    }
    else {
        TreeNode * m = locateMax(cur->getLeft());
        string tname = m->getEntry()->getName();
        unsigned int tIP = m->getEntry()->getIPaddress();
        bool tActive = m->getEntry()->getActive();


        removeNode(m->getEntry()->getName(), cur->getLeft());
        
        cur->getEntry()->setIPaddress(tIP);
        cur->getEntry()->setName(tname);
        cur->getEntry()->setActive(tActive);
        }
    return;
}



// deletes the entry with the specified name (key)  from the database.
// If the entry was indeed in the database, it returns true.
// Returns false otherwise.
bool TreeDB::remove(string name){
    if (total==1) {
	deleteAll(root);
	total = 0;
	return true;
	}
    if(findNode(root,name)==NULL)
        return false;
    removeNode(name,root);
    total--;
    return true;
}

// deletes all the entries in the database.
void TreeDB::clear(){
    if (total==0) return;
    deleteAll(root);
    total = 0;
}

// prints the number of probes stored in probesCount
void TreeDB::printProbes() const{
    cout << probesCount <<endl;
}

// computes and prints out the total number of active entries
// in the database (i.e. entries with active==true).
void TreeDB::countActive () const{
    cout<<count(root,0)<<endl;
}

void TreeDB::print(TreeNode * cur) const{

    if(cur==NULL) return;
    
    print(cur->getLeft());
    
    string status;
    if (cur->getEntry()->getActive()){
        status = "active";
    }
    else status = "inactive";
    cout<<cur->getEntry()->getName() << " : " << cur->getEntry()->getIPaddress() << " : " << status <<endl;
    
    print(cur->getRight());
    
}

ostream& operator<< (ostream& out, const TreeDB& rhs){
    rhs.print(rhs.root);
    return out;
}



