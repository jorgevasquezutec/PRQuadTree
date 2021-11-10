#include <iostream>
#include "PRQuadTreeImage.hpp"
#include "PNMImage.hpp"
#include <sys/stat.h>

using namespace utec::spatial;

long GetFileSize(std::string filename)
{
    struct stat stat_buf;
    int rc = stat(filename.c_str(), &stat_buf);
    return rc == 0 ? stat_buf.st_size : -1;
}

int main()
{
    PRQuadTreeImage qt;
    PNMImage comparator;
    qt.load("sample.ppm");
    qt.compress("sample.qt");
    qt.decompress("sample.qt");
    qt.convertToPGM("sample2.ppm");
    std::cout<< comparator.equals("sample2.ppm", "sample.ppm")<<std::endl;
    float ratio = (float)GetFileSize("sample.qt")/ (float)GetFileSize("sample.ppm");
    std::cout<<"Relacion de compresion:"<<ratio <<std::endl;
    return 0;
}