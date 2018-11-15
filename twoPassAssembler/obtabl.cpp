//
//  obtab.cpp
//  twoPassAssembler
//
//  Created by admin on 12/11/2018.
//  Copyright © 2018 wndzlf. All rights reserved.
//

#include "obtabl.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

optab::optab() {
    //optabl.open(path,ios::in);
}
optab::~optab(){
    //optabl.close();
}
int optab::search(string opcode) {
    
    fstream optable;
    optable.open(path , ios::in);
    
    string line;
    string op, val;
    
    while(getline(optable,line)) {
        istringstream stream(line);
        stream >> op >> val;
        
        if (op == opcode){
            optable.close();
            return 1;
        }
        
        op = " ";
        val = " ";
    }
    optable.close();
    return -1;
};
string optab::findOpcode(string opcode ){
    fstream optable;
    optable.open(path , ios::in);
    
    string line;
    string op, val;
    
    while(getline(optable,line)) {
        istringstream stream(line);
        stream >> op >> val;
        
        if (op == opcode){
            optable.close();
            return val;
        }
        
        op = " ";
        val = " ";
    }
    optable.close();
    return "not exist opcode";
}
