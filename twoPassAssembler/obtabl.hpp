//
//  obtab.hpp
//  twoPassAssembler
//
//  Created by admin on 12/11/2018.
//  Copyright © 2018 wndzlf. All rights reserved.
//

#ifndef obtab_hpp
#define obtab_hpp

#include <fstream>
#include <string>

#endif /* obtab_hpp */

using namespace std;

class optab {
private:
    fstream optabl;
    string path = "/Users/admin/Desktop/twoPassAssembler/twoPassAssembler/opcode.txt";
    
public:
    optab();
    ~optab();
    
    //opcode의 value값 리턴 , opcode 존재 유무
    string findOpcode(string opcode);
    int search(string opcode);
};
