//
//  symbolTabl.hpp
//  twoPassAssembler
//
//  Created by admin on 12/11/2018.
//  Copyright © 2018 wndzlf. All rights reserved.
//

#ifndef symbolTabl_hpp
#define symbolTabl_hpp

#include <string>
#include <fstream>

#endif /* symbolTabl_hpp */

using namespace std;

class symtab{
private:
    fstream symboltab;
    string label;
    string path = "/Users/admin/Desktop/twoPassAssembler/twoPassAssembler/symtab.txt";
public:
    //파일 open, close
    symtab();
    ~symtab();
    
    //label 찾기,추가,주소 리턴
    int search(string label);
    void insert(string label, int locc);
    string findAddr(string label);
};
