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

    using namespace pnm::literals;
        pnm::image<pnm::rgb_pixel> ppm = pnm::read("sample.ppm");

        std::cout << "width  = " << ppm.width()  << std::endl;
        std::cout << "height = " << ppm.height() << std::endl;

        for(std::size_t y=0; y<ppm.y_size(); ++y)
        {
            for(std::size_t x=0; x<ppm.x_size(); ++x)
            {
                ppm[y][x] = 0xFF00FF_rgb;
            }
        }
        pnm::write("out.ppm", ppm, pnm::format::binary);

        return 0;
  
}