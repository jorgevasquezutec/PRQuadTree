#pragma once
#include "SpatialImageBase.hpp"
#include "../utils/pnm.hpp"
#include <iostream>
#include <cmath>
#include <queue>
#include <unordered_map>
namespace utec {
namespace spatial {


int ratio;

template<typename T>
struct NodeQuadTree{

    long address{-1};
    long q1address{-1};
    long q2address{-1};
    long q3address{-1};
    long q4address{-1};
    NodeQuadTree<T> *q1;
    NodeQuadTree<T> *q2;
    NodeQuadTree<T> *q3;
    NodeQuadTree<T> *q4;
    bool isleaf;
    T pixel;
    int startx;
    int endx;
    int starty;
    int endy;
    NodeQuadTree(){
      this->q1=nullptr;
      this->q2=nullptr;
      this->q3=nullptr;
      this->q4=nullptr;
      this->isleaf=false;
    }
};

/**
 * PRQuadTreeImage implementation
 */
class PRQuadTreeImage : public SpatialImageBase {
 private:
  NodeQuadTree<pnm::rgb_pixel> *root;
  NodeQuadTree<pnm::rgb_pixel> *nroot;
  int width;
  int height;
  std::string name;
  std::string magicNumber;
  std::string value;
  long nextPostInsert{-1};
  long rootDirection{-1};

  bool diffPix(int startx,int starty,int endx,int endy,pnm::image<pnm::rgb_pixel> &ppm){
    
    auto first=ppm[starty][startx];
    for(int y=starty; y<=endy; ++y)
    {
        for(int x=startx; x<=endx; ++x)
        { 
            if(first!=ppm[y][x]){
              return true;
            }
        }
    }
    return false;
  }
  void builQuadTree(int startx,int endx,int starty,int endy, NodeQuadTree<pnm::rgb_pixel>* &parent, pnm::image<pnm::rgb_pixel> &ppm){

      if(!diffPix(startx,starty,endx,endy,ppm)){
          parent->isleaf=true;
          parent->pixel=ppm[starty][startx];
          parent->startx=startx;
          parent->starty=starty;
          parent->endx=endx;
          parent->endy=endy;
      }else{
        parent->q1=new NodeQuadTree<pnm::rgb_pixel>();
        parent->q2=new NodeQuadTree<pnm::rgb_pixel>();
        parent->q3=new NodeQuadTree<pnm::rgb_pixel>();
        parent->q4=new NodeQuadTree<pnm::rgb_pixel>();
        builQuadTree(startx,floor((endx+startx)/2),starty,floor((endy+starty)/2),parent->q1,ppm);
        builQuadTree(floor((endx+startx)/2)+1,endx,starty,floor((endy+starty)/2),parent->q2,ppm);
        builQuadTree(startx,floor((endx+startx)/2),floor((endy+starty)/2)+1,endy,parent->q3,ppm);
        builQuadTree(floor((endx+startx)/2)+1,endx,floor((endy+starty)/2)+1,endy,parent->q4,ppm);
      }
  }

  void fillImage(std::unordered_map<int,std::unordered_map<int,pnm::rgb_pixel>> &image,NodeQuadTree<pnm::rgb_pixel>* &current){
        if(current==nullptr){
          return;
        }
        if(current->isleaf){
          for(int y=current->starty; y<=current->endy; ++y)
            {
                for(int x=current->startx; x<=current->endx; ++x)
                { 
                  image[y][x] = current->pixel;
                }
            }
          return;
        }else{
          fillImage(image,current->q1);
          fillImage(image,current->q2);
          fillImage(image,current->q3);
          fillImage(image,current->q4);
        }
  }

  void reserveMemory(){
    auto address=this->nextPostInsert+sizeof(NodeQuadTree<pnm::rgb_pixel>);
    this->nextPostInsert=address;
  }

  void insertPostOrden(NodeQuadTree<pnm::rgb_pixel>* &current,const std::string& filename){
      if(current==nullptr){
        return;
      }else{
        insertPostOrden(current->q1,filename);
        insertPostOrden(current->q2,filename);
        insertPostOrden(current->q3,filename);
        insertPostOrden(current->q4,filename);
        //WriteNode(*current,this->nextPostInsert,filename);
        // std::cout<<this->nextPostInsert<<std::endl;
        if(current->q1!=nullptr){
          current->q1address=current->q1->address;
        }
        if(current->q2!=nullptr){
          current->q2address=current->q2->address;
        }
        if(current->q3!=nullptr){
          current->q3address=current->q3->address;
        }
        if(current->q4!=nullptr){
          current->q4address=current->q4->address;
        }
        current->address=this->nextPostInsert;
        WriteNode(*current,current->address,filename);
        reserveMemory();

      }
  }

  void readDFS(long pos,NodeQuadTree<pnm::rgb_pixel>* &current,const std::string& filename){
      if(pos==-1){
        return;
      }
      NodeQuadTree<pnm::rgb_pixel> obj=readNode(pos,filename);
      current->address=obj.address;
      current->isleaf=obj.isleaf;
      current->pixel=obj.pixel;
      current->startx=obj.startx;
      current->starty=obj.starty;
      current->endx=obj.endx;
      current->endy=obj.endy;
      current->q1address=obj.q1address;
      current->q2address=obj.q2address;
      current->q3address=obj.q3address;
      current->q4address=obj.q4address;
      current->q1= new NodeQuadTree<pnm::rgb_pixel>();
      current->q2= new NodeQuadTree<pnm::rgb_pixel>();
      current->q3= new NodeQuadTree<pnm::rgb_pixel>();
      current->q4= new NodeQuadTree<pnm::rgb_pixel>();
      readDFS(current->q1address,current->q1,filename);
      readDFS(current->q2address,current->q2,filename);
      readDFS(current->q3address,current->q3,filename);
      readDFS(current->q4address,current->q4,filename);
      
  }


  void  WriteNode(NodeQuadTree<pnm::rgb_pixel> _reg,long pos,const std::string& filename){
        std::fstream outFile;
        outFile.open(filename,std::ios::in| std::ios::out| std::ios::binary | std::ofstream::app);
        long _pos;
        if(outFile.is_open()){
            outFile.seekg(pos, std::ios::beg);
            outFile.write((char* )&_reg, sizeof(NodeQuadTree<pnm::rgb_pixel>));
            _pos=outFile.tellg();
            outFile.close();
        }
    }
  

  NodeQuadTree<pnm::rgb_pixel> readNode(long pos,const std::string& filename){
        std::ifstream outFile;
        NodeQuadTree<pnm::rgb_pixel> obj;
        outFile.open(filename,std::ios::in| std::ios::out| std::ios::binary);
        if (outFile.is_open()) {
            outFile.seekg(pos, std::ios::beg);
            outFile.read((char *) &obj, sizeof(NodeQuadTree<pnm::rgb_pixel>));
            outFile.close();
        }
        return obj;
    }


 public:
  PRQuadTreeImage(){
    root= new NodeQuadTree<pnm::rgb_pixel>();
    nroot= new NodeQuadTree<pnm::rgb_pixel>();
  }
  void load(const std::string& filename) override {
      pnm::image<pnm::rgb_pixel> ppm = pnm::read(filename);
      this->width=ppm.width();
      this->height=ppm.height();
      std::ifstream file(filename);
      std::string line;
      std::getline(file,magicNumber);
      std::getline(file,name);
      std::getline(file,line);
      std::getline(file,value);
      file.close();
      ratio= 256 / (stoi(value) + 1);

      builQuadTree(0,ppm.x_size()-1,0,ppm.y_size()-1,this->root,ppm);
  }
  void compress(const std::string& filename) override {
      this->nextPostInsert=0;
      this->root->address=0;
      insertPostOrden(root,filename);
      this->rootDirection=root->address;
  }
  void decompress(const std::string& filename) override {
      readDFS(this->rootDirection,nroot,filename);
  }
  void convertToPGM(const std::string& filename) override {
    std::unordered_map<int,std::unordered_map<int,pnm::rgb_pixel>> newFile; 
    fillImage(newFile,nroot);
    std::ofstream tmpfile(filename);
    tmpfile<<magicNumber<<std::endl;
    tmpfile<<name<<std::endl;
    tmpfile<<this->width<< " "<<this->height<<std::endl;
    tmpfile<<this->value<<std::endl;

    for(int i = 0;i<this->height;i++){
        for(int y=0;y<this->width;y++){
            tmpfile<<(uint16_t)newFile[i][y].red/ratio<<" "<<(uint16_t)newFile[i][y].green/ratio<<" "<<(uint16_t)newFile[i][y].blue/ratio<<"   ";
        }
        tmpfile<<std::endl;
    }
    tmpfile.close();
  }
};

}  // namespace spatial
}  // namespace utec
