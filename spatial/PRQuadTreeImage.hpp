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

    void print(int &nodeCount, std::ostream& os = std::cout)
    {
        if (isleaf)
        {
            os << startx << "," << endx << "," << starty << "," << endy << ",";
            printRGBPixel(pixel,",", os);
        }
        else
        {
            os << nodeCount++ << ",*";
        }
    }

};

/**
 * PRQuadTreeImage implementation
 */
class PRQuadTreeImage : public SpatialImageBase {
 private:
  NodeQuadTree<pnm::rgb_pixel> *root;
  int width;
  int height;
  std::string name;
  std::string magicNumber;
  std::string value;

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
 public:
  PRQuadTreeImage(){
    root= new NodeQuadTree<pnm::rgb_pixel>();
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
     //print(root);
  }
  void decompress(const std::string& filename) override {
    
  }
  void convertToPGM(const std::string& filename) override {
    std::unordered_map<int,std::unordered_map<int,pnm::rgb_pixel>> newFile; 
    fillImage(newFile,root);
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
