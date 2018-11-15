

//
//  symbolTabl.cpp
//  twoPassAssembler
//
//  Created by admin on 12/11/2018.
//  Copyright © 2018 wndzlf. All rights reserved.
//

#include "symtabl.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>

symtab::symtab(){
    symboltab.open(path,ios::out);
};
symtab::~symtab() {
    symboltab.close();
}

//똑같은 파일을 쓰고 읽을때 --> 읽을때 새로운 stream을 만들어주자(안그러면 써지지가 않음)
int symtab::search(string label){
    string line;
    ifstream inputFile(path);
    while(!inputFile.eof()){
        getline(inputFile, line);
        string sym, val;
        istringstream stream(line);
        stream >> sym >> val;
        
        inputFile.close();
        if (label == sym) {
            cout<<"중복됨"<<endl;
            return -1;
        }
    }
    return 1;
}
string symtab::findAddr(string label){
    string line;
    ifstream inputFile(path);
    while(!inputFile.eof()){
        getline(inputFile, line);
        string sym, val;
        istringstream stream(line);
        stream >> sym >> val;
        
        if (label == sym){
            return val;
        }
    }
    return "nothing";
}

void symtab::insert(string label, int locc){
    symboltab <<setw(10)<<label<<setw(10)<<hex<<locc <<endl;
}
