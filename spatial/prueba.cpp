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
    qt.compress("sample2.qt");
    qt.decompress("sample2.qt");
    qt.convertToPGM("sample2.ppm");
    std::cout<< comparator.equals("sample2.ppm", "sample.ppm")<<std::endl;
    return 0;
}