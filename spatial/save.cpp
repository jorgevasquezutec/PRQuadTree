#include <iostream>
#include "../utils/pnm.hpp"
#include <iostream>
#include "PNMImage.hpp"



int main()
{
    // using namespace utec::spatial;
    // PNMImage comparator;

    // pnm::image<pnm::rgb_pixel> ppm = pnm::read("sample.ppm");
    // pnm::image<pnm::rgb_pixel> copy(ppm.width(),ppm.height());

    //   for(std::size_t y=0; y<ppm.y_size(); ++y)
    // {
    //     for(std::size_t x=0; x<ppm.x_size(); ++x)
    //     {
    //         copy[y][x] = ppm[y][x];
    //     }
    // }
    // pnm::write("out.ppm", ppm, pnm::format::ascii);
    // std::cout<< comparator.equals("sample.ppm", "out.ppm")<<std::endl;

    // using namespace pnm::literals;
    //     pnm::image<pnm::rgb_pixel> ppm = pnm::read("sample.ppm");

    //     std::cout << "width  = " << ppm.width()  << std::endl;
    //     std::cout << "height = " << ppm.height() << std::endl;

    //     for(std::size_t y=0; y<ppm.y_size(); ++y)
    //     {
    //         for(std::size_t x=0; x<ppm.x_size(); ++x)
    //         {
    //             ppm[y][x] = 0xFF00FF_rgb;
    //         }
    //     }
    //     pnm::write("out.ppm", ppm, pnm::format::binary);

    //     return 0;

    // void print(RTreeNode* root, std::ostream& os)
    // {
    //     if (root == nullptr)
    //         return;

    //     std::queue<RTreeNode*> q;
    //     q.push(root);

    //     while (!q.empty()) 
    //     {
    //         int cont = q.size();
    //         while (cont > 0)
    //         {
    //             RTreeNode* node = q.front();
    //             std::cout << node << std::endl;
    //             q.pop();
    //             if (node->NW != nullptr)
    //                 q.push(node->NW);
    //             if (node->NE != nullptr)    
    //                 q.push(node->NE);
    //             if (node->SW != nullptr)
    //                 q.push(node->SW);
    //             if (node->SE != nullptr)
    //                 q.push(node->SE);
    //             cont--;
    //         }
    //         os << std::endl;
    //     }
    // }

    //      if(root==nullptr)
    //     return;
    //   std::queue<NodeQuadTree<pnm::rgb_pixel>*> q;
    //   q.push(root);

    //   while(!q.empty()){
    //         int cont=q.size();
    //         while (cont>0)
    //         {
    //            auto *node = q.front();
    //            node->address=nextPostInsert;
    //            this->nextPostInsert=WriteAndReturnNextPosInsert(*node,this->nextPostInsert,filename);
    //            q.pop();
    //            if(node->q1 !=nullptr){
    //              q.push(node->q1);
    //            }
    //            if(node->q2 !=nullptr){
    //              q.push(node->q2);
    //            }
    //            if(node->q3 !=nullptr){
    //              q.push(node->q3);
    //            }
    //            if(node->q4!=nullptr){
    //              q.push(node->q4);
    //            }
    //            cont--;
    //         }
    //   }


    //    if(current==nullptr){
    //     return;
    //   }else{
    //     if (current->q1!=nullptr)
    //     {
    //         reserveMemory(this->nextPostInsert,current->q1);
    //         current->q1address=this->nextPostInsert;
    //     }
    //     if(current->q2!=nullptr){
    //         reserveMemory(this->nextPostInsert,current->q2);
    //         current->q2address=this->nextPostInsert;
    //     }
    //     if(current->q3!=nullptr){
    //         reserveMemory(this->nextPostInsert,current->q3);
    //         current->q3address=this->nextPostInsert;
    //     }
    //     if(current->q4!=nullptr){
    //         reserveMemory(this->nextPostInsert,current->q4);
    //         current->q4address=this->nextPostInsert;
    //     }
    //     WriteNode(*current,current->address,filename);
       
    //     insertBFS(current->q1,filename);
    //     insertBFS(current->q2,filename);
    //     insertBFS(current->q3,filename);
    //     insertBFS(current->q4,filename);
    //   }
  
  
}