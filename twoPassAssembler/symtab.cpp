//
//  symtab.cpp
//  twoPassAssembler
//
//  Created by admin on 12/11/2018.
//  Copyright © 2018 wndzlf. All rights reserved.
//

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

class symtab{
private:
    fstream symboltab;
    
    string label;
    string path;
    
    int num;
public:
    symtab();
    ~symtab();

    int search(string label);
    void insert(string label, int locc);
    
};

symtab::symtab(){
    symboltab.open("/Users/admin/Desktop/twoPassAssembler/twoPassAssembler/symtab.txt",ios::out);
    this->num = 0;
};
symtab::~symtab() {
    symboltab.close();
}



int symtab::search(string label){
    string line;
    while(!symboltab.eof()){
        getline(symboltab, line);
        string sym, val;
        istringstream stream(line);
        stream >> sym >> val;
        //duplicate
        if (label == sym) {
            return -1;
        }
    }
    return 1;
}

void symtab::insert(string label, int locc){
    symboltab <<label<<" " << locc <<endl;
}
