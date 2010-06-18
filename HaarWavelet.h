/*
 * HaarWavelet.h
 *
 *  Created on: 26-May-2010
 *      Author: shirish
 */

#ifndef HAARWAVELET_H_
#define HAARWAVELET_H_

#include "headers.h"
/**
 * Declares Decomposition methods along different channels of an image
 */
class HaarWavelet {
public:
    HaarWavelet();
    virtual ~HaarWavelet();
    IplImage* decompose_Image(IplImage *dec_img);
    IplImage* decompose_Image_b(IplImage *dec_img);
    IplImage* decompose_Image_g(IplImage *dec_img);
    IplImage* decompose_Image_r(IplImage *dec_img);

private:
    IplImage* test_img;

};

#endif /* HAARWAVELET_H_ */
