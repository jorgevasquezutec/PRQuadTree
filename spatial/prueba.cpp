#include <iostream>
#include "PRQuadTreeImage.hpp"
#include "PNMImage.hpp"

using namespace utec::spatial;
using namespace pnm::literals;
int main()
{
    PRQuadTreeImage qt;
    PNMImage comparator;
    qt.load("sample.ppm");
    qt.convertToPGM("sample2.ppm");
    std::cout<< comparator.equals("sample.ppm", "sample2.ppm")<<std::endl;
    return 0;
}