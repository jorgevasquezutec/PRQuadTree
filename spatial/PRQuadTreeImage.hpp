#pragma once
#include "SpatialImageBase.hpp"
#include "../utils/pnm.hpp"
#include <iostream>
#include <fstream>
#include <cmath>
#include <queue>
#include <unordered_map>
namespace utec {
namespace spatial {


int ratio;

struct NodeQuadTree{
    long address{-1};
    long q1address{-1};
    long q2address{-1};
    long q3address{-1};
    long q4address{-1};
    NodeQuadTree *q1;
    NodeQuadTree *q2;
    NodeQuadTree *q3;
    NodeQuadTree *q4;
    bool isleaf;
    uint16_t red;
    uint16_t green;
    uint16_t blue;
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
  NodeQuadTree *root;
  NodeQuadTree *nroot;
  int width;
  int height;
  std::string name;
  std::string magicNumber;
  std::string value;
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

  bool comparePixel(pnm::rgb_pixel &pix,NodeQuadTree* node){
    if(pix.blue==node->blue && pix.red ==node->red && pix.green==node->green){
      return true;
    }
    return false;
  }

  void builQuadTree(int startx,int endx,int starty,int endy, NodeQuadTree* &parent, pnm::image<pnm::rgb_pixel> &ppm){

      if(!diffPix(startx,starty,endx,endy,ppm)){
          parent->isleaf=true;
          parent->blue=(uint16_t)ppm[starty][startx].blue;
          parent->red=(uint16_t)ppm[starty][startx].red;
          parent->green=(uint16_t)ppm[starty][startx].green;
          parent->startx=startx;
          parent->starty=starty;
          parent->endx=endx;
          parent->endy=endy;
      }else{
        parent->q1=new NodeQuadTree();
        parent->q2=new NodeQuadTree();
        parent->q3=new NodeQuadTree();
        parent->q4=new NodeQuadTree();
        builQuadTree(startx,floor((endx+startx)/2),starty,floor((endy+starty)/2),parent->q1,ppm);
        builQuadTree(floor((endx+startx)/2)+1,endx,starty,floor((endy+starty)/2),parent->q2,ppm);
        builQuadTree(startx,floor((endx+startx)/2),floor((endy+starty)/2)+1,endy,parent->q3,ppm);
        builQuadTree(floor((endx+startx)/2)+1,endx,floor((endy+starty)/2)+1,endy,parent->q4,ppm);
      }
  }

   void fillImagePostOrden(pnm::image<pnm::rgb_pixel> &image,NodeQuadTree* &current){
        if(current==nullptr){
          return;
        }
        else{
           fillImagePostOrden(image,current->q1);
           fillImagePostOrden(image,current->q2);
           fillImagePostOrden(image,current->q3);
           fillImagePostOrden(image,current->q4);
           if(current->isleaf){
              for(int y=current->starty; y<=current->endy; ++y)
              {
                  for(int x=current->startx; x<=current->endx; ++x)
                  { 
                      image[y][x]=pnm::rgb_pixel((uint8_t)current->red,(uint8_t)current->green,(uint8_t)current->blue);                     
                  }
              }
           }
        }
  }


  void insertPostOrden(NodeQuadTree* &current,const std::string& filename){
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
        current->address=WriteNode(*current,filename);

      }
  }

  void readDFS(long pos,NodeQuadTree* &current,const std::string& filename){
      if(pos==-1){
        return;
      }
      NodeQuadTree obj=readNode(pos,filename);
      current->address=obj.address;
      current->isleaf=obj.isleaf;
      current->red=obj.red;
      current->blue=obj.blue;
      current->green=obj.green;
      current->startx=obj.startx;
      current->starty=obj.starty;
      current->endx=obj.endx;
      current->endy=obj.endy;
      current->q1address=obj.q1address;
      current->q2address=obj.q2address;
      current->q3address=obj.q3address;
      current->q4address=obj.q4address;
      current->q1= new NodeQuadTree();
      current->q2= new NodeQuadTree();
      current->q3= new NodeQuadTree();
      current->q4= new NodeQuadTree();
      readDFS(current->q1address,current->q1,filename);
      readDFS(current->q2address,current->q2,filename);
      readDFS(current->q3address,current->q3,filename);
      readDFS(current->q4address,current->q4,filename);
      
  }


  long  WriteNode(NodeQuadTree _reg,const std::string& filename){
        std::fstream outFile;
        outFile.open(filename,std::ios::in| std::ios::out| std::ios::binary | std::ofstream::app);
        long _pos;
        if(outFile.is_open()){
            outFile.seekg(0,std::ios::end);
            outFile.write((char* )&_reg, sizeof(NodeQuadTree));
            _pos=(long)outFile.tellg()- (long)sizeof(NodeQuadTree);
            outFile.close();
        }
        return _pos;
    }
  

  NodeQuadTree readNode(long pos,const std::string& filename){
        std::ifstream outFile;
        NodeQuadTree obj;
        outFile.open(filename,std::ios::in| std::ios::out| std::ios::binary);
        if (outFile.is_open()) {
            outFile.seekg(pos, std::ios::beg);
            outFile.read((char *) &obj, sizeof(NodeQuadTree));
            outFile.close();
        }
        return obj;
    }


 public:
  PRQuadTreeImage(){
    root= new NodeQuadTree();
    nroot= new NodeQuadTree();
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
      insertPostOrden(root,filename);
      this->rootDirection=root->address;
  }
  void decompress(const std::string& filename) override {
      readDFS(this->rootDirection,nroot,filename);
  }
  void convertToPGM(const std::string& filename) override {
       pnm::image<pnm::rgb_pixel> newFile (this->width,this->height);
       fillImagePostOrden(newFile,nroot);
       pnm::write(filename, newFile, pnm::format::ascii);
   }
};

}  // namespace spatial
}  // namespace utec
