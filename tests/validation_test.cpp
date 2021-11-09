#include <gtest/gtest.h>

#include <iostream>

#include "PNMImage.hpp"
#include "PRQuadTreeImage.hpp"

using namespace utec::spatial;
//./tests/validation_test


long GetFileSize(std::string filename)
{
    struct stat stat_buf;
    int rc = stat(filename.c_str(), &stat_buf);
    return rc == 0 ? stat_buf.st_size : -1;
}


TEST(QuadTest, BasicTest) {
  PNMImage comparator;
  
  PRQuadTreeImage qt;
  qt.load("../tests/images/img16Out.ppm");
  qt.compress("../tests/images/img16Out.qt");
  qt.decompress("../tests/images/img16Out.qt");
  qt.convertToPGM("../tests/images/img16Out2.ppm");
  EXPECT_TRUE(comparator.equals("../tests/images/img16Out.ppm", "../tests/images/img16Out2.ppm"));
  float ratio = (float)GetFileSize("../tests/images/img16Out.qt")/ (float)GetFileSize("../tests/images/img16Out.ppm");
  std::cout<<"Relacion de compresion img16 :"<<ratio <<std::endl;

  PRQuadTreeImage qt1;
  qt1.load("../tests/images/img32Out.ppm");
  qt1.compress("../tests/images/img32Out.qt");
  qt1.decompress("../tests/images/img32Out.qt");
  qt1.convertToPGM("../tests/images/img32Out2.ppm");
  EXPECT_TRUE(comparator.equals("../tests/images/img32Out.ppm", "../tests/images/img32Out2.ppm"));
  float ratio1 = (float)GetFileSize("../tests/images/img32Out.qt")/ (float)GetFileSize("../tests/images/img32Out.ppm");
  std::cout<<"Relacion de compresion img32 :"<<ratio1 <<std::endl;

  PRQuadTreeImage qt2;
  qt2.load("../tests/images/img64Out.ppm");
  qt2.compress("../tests/images/img64Out.qt");
  qt2.decompress("../tests/images/img64Out.qt");
  qt2.convertToPGM("../tests/images/img64Out2.ppm");
  EXPECT_TRUE(comparator.equals("../tests/images/img64Out.ppm", "../tests/images/img64Out2.ppm"));
  float ratio2 = (float)GetFileSize("../tests/images/img64Out.qt")/ (float)GetFileSize("../tests/images/img64Out.ppm");
  std::cout<<"Relacion de compresion img64 :"<<ratio2 <<std::endl;

  PRQuadTreeImage qt3;
  qt3.load("../tests/images/img128Out.ppm");
  qt3.compress("../tests/images/img128Out.qt");
  qt3.decompress("../tests/images/img128Out.qt");
  qt3.convertToPGM("../tests/images/img128Out2.ppm");

  EXPECT_TRUE(comparator.equals("../tests/images/img128Out.ppm", "../tests/images/img128Out2.ppm"));
  float ratio3 = (float)GetFileSize("../tests/images/img128Out.qt")/ (float)GetFileSize("../tests/images/img128Out.ppm");
  std::cout<<"Relacion de compresion img128 :"<<ratio3 <<std::endl;

}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
