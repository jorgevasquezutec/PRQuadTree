#pragma once

#include "../utils/pnm.hpp"

namespace utec {
namespace spatial {

/**
 * PNMImage implementation
 */
class PNMImage {
 private:
 public:
  static bool equals(const std::string& left, const std::string& right) {
       auto ppmleft = pnm::read(left);
       auto ppmright = pnm::read(right);

        if(ppmleft.x_size()!=ppmright.x_size() && ppmleft.y_size()!=ppmright.y_size()){
          return false;
        }

        for(std::size_t y=0; y<ppmleft.y_size(); ++y)
        {
            for(std::size_t x=0; x<ppmleft.x_size(); ++x)
            {
                if(ppmleft[y][x] != ppmleft[y][x]){
                    return false;
                }
            }
        }
        return true;
  };

};

}  // namespace spatial
}  // namespace utec
