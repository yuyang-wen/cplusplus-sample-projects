#ifndef _TREEDB_H
#define _TREEDB_H

#include "TreeNode.h"
#include "DBentry.h"
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

class TreeDB {

private:
   TreeNode* root;
   int probesCount;
   void insertNode(TreeNode * cur, DBentry * newEntry);
   TreeNode * findNode(TreeNode * cur, string name);
   TreeNode * findParent(TreeNode * cur, TreeNode * child)const;
   TreeNode* locateMax(TreeNode * cur);
   TreeNode* locateMin(TreeNode * cur);
   void print(TreeNode * cur) const;
   void deleteAll (TreeNode * cur);
   int count(TreeNode * cur, int num) const;
   void removeNode(string name, TreeNode * cur);
   int total;

public:
   // the default constructor, creates an empty database.
   TreeDB();

   // the destructor, deletes all the entries in the database.
   ~TreeDB();

   // inserts the entry pointed to by newEntry into the database. 
   // If an entry with the same key as newEntry's exists 
   // in the database, it returns false. Otherwise, it returns true.
   bool insert(DBentry* newEntry); 

   // searches the database for an entry with a key equal to name.
   // If the entry is found, a pointer to it is returned.
   // If the entry is not found, the NULL pointer is returned.
   // Also sets probesCount
   DBentry* find(string name);

   // deletes the entry with the specified name (key)  from the database.
   // If the entry was indeed in the database, it returns true.
   // Returns false otherwise.
   bool remove(string name);
	
   // deletes all the entries in the database.
   void clear();
    
   // prints the number of probes stored in probesCount
   void printProbes() const;
   
   // computes and prints out the total number of active entries
   // in the database (i.e. entries with active==true).
   void countActive () const;

   // Prints the entire tree, in ascending order of key/name
   friend ostream& operator<< (ostream& out, const TreeDB& rhs);
}; 

ostream& operator<< (ostream& out, TreeNode* rhs);   
   
#endif 

