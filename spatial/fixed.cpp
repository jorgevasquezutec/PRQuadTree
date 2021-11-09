#include <iostream>
#include<fstream>
#include<cstdio>
using namespace std;

struct test{
    long address{-1};
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    bool isleaf;
    long q1address{-1};
    long q2address{-1};
    long q3address{-1};
    long q4address{-1};
    int startx;
    int starty;
    int endx;
    int endy;
    long write(std::fstream &stream) {
        stream.seekg(0,std::ios::end);
        long pos_begin = stream.tellp();
        if(isleaf){
            stream.write((char *) &isleaf, sizeof(isleaf));
            stream.write((char *) &red, sizeof(red));
            stream.write((char *) &green, sizeof(red));
            stream.write((char *) &blue, sizeof(blue));
            stream.write((char *) &startx, sizeof(startx));
            stream.write((char *) &starty, sizeof(starty));
            stream.write((char *) &endx, sizeof(endx));
            stream.write((char *) &endy, sizeof(endy));
        }else{
            stream.write((char *) &isleaf, sizeof(isleaf));
            stream.write((char *) &q1address, sizeof(q1address));
            stream.write((char *) &q2address, sizeof(q2address));
            stream.write((char *) &q3address, sizeof(q3address));
            stream.write((char *) &q3address, sizeof(q4address));
        }
        return pos_begin;
    }


    bool read(std::fstream &stream) {
        stream.read((char *) &isleaf, sizeof(isleaf));
        if(isleaf){
            stream.read((char *) &red, sizeof(red));
            stream.read((char *) &green, sizeof(red));
            stream.read((char *) &blue, sizeof(red));
            stream.read((char *) &startx, sizeof(startx));
            stream.read((char *) &starty, sizeof(starty));
            stream.read((char *) &endx, sizeof(endx));
            stream.read((char *) &endy, sizeof(endy));
        }
        else{
            stream.read((char *) &q1address, sizeof(q1address));
            stream.read((char *) &q2address, sizeof(q2address));
            stream.read((char *) &q3address, sizeof(q3address));
            stream.read((char *) &q3address, sizeof(q4address));
        }
         if (stream.fail()) return false;
        return true;
    }
};


long  WriteNode(test _reg,const std::string& filename){
        std::fstream outFile;
        outFile.open(filename,std::ios::in| std::ios::out| std::ios::binary | std::ios::app);
        long _pos;
        if(outFile.is_open()){
            _pos = _reg.write(outFile);
            outFile.close();
        }
        return _pos;
};
  

test readNode(long pos,const std::string& filename){
    fstream outFile;
    test obj;
    outFile.open(filename,ios::in | ios::binary);
    if (outFile.is_open()) {
        outFile.seekg(pos, ios::beg);
        obj.read(outFile);
        outFile.close();
    }
    return obj;
};

int main(){

    struct test nodo1 = {0, 128,   0,   0, 0,100,200,300,400,-1,-1,-1,-1};
    struct test hijo1 = {1, 128,   0, 128, 1, -1, -1, -1, -1, 1, 2, 3, 4};
    struct test hijo2 = {1, 128,   0, 128, 1, -1, -1, -1, -1, 1, 2, 3, 7};
    struct test nodo3 = {4,   0,   0,   0, 0, 80, 40, 10, 20,-1,-1,-1,-1};
    long t1pos= WriteNode(nodo1,"prueba.txt");
    long t2pos= WriteNode(hijo1,"prueba.txt");
    long t3pos= WriteNode(hijo2,"prueba.txt");
    long t4pos= WriteNode(nodo3,"prueba.txt");
  
    auto tmp= readNode(t3pos,"prueba.txt");
    return 0;
}