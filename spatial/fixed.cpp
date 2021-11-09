#include <iostream>
#include<fstream>
#include<cstdio>
using namespace std;

struct test{
    long pos{-1};
    uint8_t red;
    uint8_t geeen;
    uint8_t blue;
    long write(std::fstream &stream) {
        long pos_begin = stream.tellp();
        stream.write((char *) &pos, sizeof(pos));
        stream.write((char *) &red, sizeof(red));
        stream.write((char *) &blue, sizeof(blue));
        return pos_begin;
    }

      bool read(std::fstream &stream) {
        stream.read((char *) &pos, sizeof(pos));
        stream.read((char *) &geeen, sizeof(geeen));
        stream.read((char *) &blue, sizeof(blue));
        if (stream.fail()) return false;
        return true;
    }
};


long  WriteNode(test _reg,const std::string& filename){
        std::fstream outFile;
        outFile.open(filename,std::ios::in| ios::out| ios::binary | std::ofstream::app);
        long _pos;
        if(outFile.is_open()){
            outFile.seekg(0,ios::end);
            outFile.write((char* )&_reg, sizeof(test));
            _pos=outFile.tellg()- sizeof(test);
            outFile.close();
        }
        return _pos;
};
  

test readNode(long pos,const std::string& filename){
    ifstream outFile;
    test obj;
    outFile.open(filename,ios::in| ios::out| ios::binary);
    if (outFile.is_open()) {
        outFile.seekg(pos, ios::beg);
        outFile.read((char *) &obj, sizeof(test));
        outFile.close();
    }
    return obj;
};

int main(){

    struct test t1 = {0, 128, 0,0};
    struct test t2 = {1, 128, 0,128};
    struct test t3 = {3, 128, 128,128};
    struct test t4 = {4, 0, 0, 0};
    long t1pos= WriteNode(t1,"prueba.txt");
    long t2pos= WriteNode(t2,"prueba.txt");
    long t3pos= WriteNode(t3,"prueba.txt");
    long t4pos= WriteNode(t4,"prueba.txt");
  
    auto tmp= readNode(t3pos,"prueba.txt");
    return 0;
}