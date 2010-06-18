/*
 * headers.h
 *
 *  Created on: 26-May-2010
 *      Author: shirish
 */

#ifndef HEADERS_H_
#define HEADERS_H_

#include <stdlib.h>
#include <iostream>
#include <cv.h>
#include <highgui.h>
#include <math.h>
#include <dirent.h>
#include <string.h>
#include <list>
#include <map>
#include <fstream>

/**
 * Defining a template for easy access of RGB vales in an image
 */
template<class T> class Image
{
  private:
  IplImage* imgp;
  public:
  Image(IplImage* img=0) {imgp=img;}
  ~Image(){imgp=0;}
  void operator=(IplImage* img) {imgp=img;}
  inline T* operator[](const int rowIndx) {
    return ((T *)(imgp->imageData + rowIndx*imgp->widthStep));}
};

typedef struct{
  unsigned char b,g,r;
} RgbPixel;

typedef struct{
  float b,g,r;
} RgbPixelFloat;

typedef Image<RgbPixel>       RgbImage;
typedef Image<RgbPixelFloat>  RgbImageFloat;
typedef Image<unsigned char>  BwImage;
typedef Image<float>          BwImageFloat;


#endif /* HEADERS_H_ */
