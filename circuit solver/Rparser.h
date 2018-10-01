//
//  Parser.hpp
//
//  Created by Yuyang on 2017-10-15.
//  Copyright © 2017 Yuyang. All rights reserved.
//

#ifndef Parser_hpp
#define Parser_hpp

#include <stdio.h>
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>

using namespace std;

// function declaration
bool validCheck(stringstream& varStream);
bool allCheck(string varName);
bool emptyCheck(stringstream& varStream);
bool resistanceCheck(double resistance, stringstream& varStream);
bool nodeCheck(stringstream& varStream, int nodevar);
bool maxValCheck(stringstream& varStream, int maxVal);
int Rparser(void);

#endif /* Parser_hpp */

