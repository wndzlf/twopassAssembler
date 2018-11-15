//
//  main.cpp
//  twoPassAssembler
//
//  Created by admin on 08/11/2018.
//  Copyright © 2018 wndzlf. All rights reserved.
//

#include "symtabl.hpp"
#include "obtabl.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>

using namespace std;

int stringToHex(string s);
int stringToDec(string s);

int main(int argc, const char * argv[]) {
    
    fstream input , intermediate, listing;
    
    input.open("/Users/admin/Desktop/twoPassAssembler/twoPassAssembler/input.txt");
    intermediate.open("/Users/admin/Desktop/twoPassAssembler/twoPassAssembler/intermediate.txt",ios::out);
    
    symtab symtab;
    optab optab;
    
    int startAddress = 0 ;
    int locctr = 0 ;
    int length = 0 ;
    
    string label, opcode, operand , addr;
    string line;
    
    /* pass1 */
    if(input.good()){
        
        getline(input,line);
        istringstream stream(line);
        //해당 행을 labe, opcode, operand로 파싱
        stream >> label >> opcode >> operand;
        
        //inputxt에서 label이 공백이면 operand가 공백이 된다.
        if (operand == " "){
            operand = opcode;
            opcode = label;
            label = " ";
        }
        
        if (opcode == "start"){
            startAddress = stringToHex(operand);
            locctr = startAddress;
            
            intermediate << hex << setw(10) << locctr << " "
                            << setw(10)<< label << " "
                            << setw(10)<< opcode << " "
                            << setw(10)<< operand << " "
                            << endl;
            
            getline(input,line);
            istringstream stream(line);
            stream >> label >> opcode >>operand;
            
            if (operand == " "){
                operand = opcode;
                opcode = label;
                label = " ";
            }
        }
        
        while(opcode != "end"){
            if (label != " "){//label have symbol
                if (symtab.search(label) == -1) {
                    cout<<"duplicated symbol\n";
                }else {
                    symtab.insert(label,locctr);
                }
            }
            
            intermediate << hex << setw(10) << locctr << " "
            << setw(10)<< label << " "
            << setw(10)<< opcode << " "
            << setw(10)<< operand << " "
            << endl;
            
            if (optab.search(opcode) == 1){ //otable have opcode
                locctr += 3;
            }
            else if (opcode == "word"){
                locctr += 3;
            }
            else if (opcode == "resw"){
                locctr += 3*stringToDec(operand);
            }
            else if (opcode == "resb"){
                locctr += stringToDec(operand);
            }
            else if (opcode == "byte"){
                if(operand[0] == 'x')
                    locctr += (operand.length()-3) / 2;
                else if (operand[0] == 'c')
                    locctr += operand.length()-3;
            }
            else {
                cout<<"not exist Opcode"<<endl;
            }
            
            label = " ";
            opcode = " ";
            operand = " ";
            
            getline(input,line);
            istringstream stream(line);
            stream >> label >> opcode >> operand;
            
            if (operand == " "){
                operand = opcode;
                opcode = label;
                label = " ";
            }
        }
        
        intermediate << hex << setw(10) << locctr << " "
        << setw(10)<< label << " "
        << setw(10)<< opcode << " "
        << setw(10)<< operand << " "
        << endl;
        
        length = locctr - startAddress;
        intermediate << "length:" << length;
        
        input.close();
        intermediate.close();
    }
    
    /* pass2 */
    intermediate.open("/Users/admin/Desktop/twoPassAssembler/twoPassAssembler/intermediate.txt",ios::in);
    listing.open("/Users/admin/Desktop/twoPassAssembler/twoPassAssembler/listing.txt",ios::out);
    
    
    getline(intermediate,line);
    stringstream str(line);
    str >> addr >> label >> opcode >>operand;
    
    if (operand == " "){
        operand = opcode;
        opcode = label;
        label = " ";
    }
    
    //헤더 작성
    if (opcode == "start"){
        listing << "H" <<setw(6)<<left<<label<<setw(6)<<hex<<setfill('0')<<right
        <<startAddress<<setw(6)<<hex<<right<<setfill('0')<<length<<endl;
    }
    
    //텍스트 작성
    int countRecordLength = 0 ;
    int count = 0;
    string operandAddress;
    
    while(opcode != "end"){
        
        addr = " ";
        label = " ";
        opcode = " ";
        operand = " ";
        
        getline(intermediate, line);
        stringstream str2(line);
        
        str2 >> addr >> label >> opcode >> operand;
        
        if (operand == " "){
            operand = opcode;
            opcode = label;
            label = " ";
        }
        
        if (countRecordLength++ == 0){
            listing<<"T"<<setw(6)<<right<<setfill('0')<<addr<<"";
        }
        
        if (optab.search(opcode) == 1){ //optable have opcode
            operandAddress += optab.findOpcode(opcode);
            if (symtab.search(operand) == 1){ //symtab have operand
                operandAddress += symtab.findAddr(operand);
            }else {
                operandAddress = "0";
                cout<<"undefined symbol";
            }
            count +=6;
        }
        
        if(opcode == "word"){
            int opAd = stringToHex(operand);
            ostringstream ss;
            ss << setfill('0')<<setw(6)<<hex<<opAd;
            operandAddress += ss.str();
            count +=6;
        }
        else if (opcode == "byte"){
            if (operand[0] == 'x'){
                ostringstream ss;
                ss <<setfill('0')<<setw(6)<<right<<operand.substr(2,operand.length()-3);
                operandAddress += ss.str();
                cout<<operandAddress;
            }//else if (operand[0] == 'c')
            count +=6;
        }
        
        if (countRecordLength == 5) {
            listing<<hex<<setfill('0')<<setw(2)<< (count / 2) << operandAddress<<endl;
            
            count = 0 ;
            countRecordLength = 0 ;
            operandAddress = "";
        }
    }
    
    listing<<"E"<<setw(6)<<setfill('0')<<right<<startAddress<<endl;

    intermediate.close();
    listing.close();
    
    return 0;
}

int stringToHex(string s)
{
    stringstream str;
    int value;
    str << s;
    str >> hex >> value;
    return value;
}

int stringToDec(string s)
{
    stringstream str;
    int value;
    str << s;
    str >> value;
    return value;
}

