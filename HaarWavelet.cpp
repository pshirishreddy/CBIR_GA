/*
 * HaarWavelet.cpp
 *
 *  Created on: 26-May-2010
 *      Author: shirish
 */

#include "HaarWavelet.h"
#include "headers.h"

using namespace std;

HaarWavelet::HaarWavelet() {
}


HaarWavelet::~HaarWavelet() {
}
/**
 * Decomposing Image along the single channel
 * Uses Haar Wavelet Decomposition and Pyramid Algorithm
 * @params : grey scale converted image
 * @return : returns decomposed image along grey channel
 * Generally Not used in the Code. Used previously while computing
 * location based similarity
 */
IplImage* HaarWavelet :: decompose_Image(IplImage *dec_img) {
    cvNamedWindow("Decomposed_image",1);
    cvShowImage("Decomposed_image",dec_img);
    //cvWaitKey(0);
    BwImage imgA(dec_img);
    //row
    IplImage *imgA_1 = cvCreateImage(cvSize(dec_img->height,dec_img->width), dec_img->depth, dec_img->nChannels);
    for(int row = 0; row<dec_img->height; row++) {
	for(int col = 0; col<dec_img->width; col++) {
            imgA[row][col] = ((float)imgA[row][col]) /sqrt(dec_img->width);
        }
        cvCopyImage(dec_img, imgA_1);
	BwImage imgA1(imgA_1);
	int h = dec_img->height;
	while(h>1) {
            h/=2;
            for(int i=0; i<h; i++) {
                imgA1[row][i] = ((float)imgA[row][2*i] + (float)imgA[row][2*i+1])/sqrt(2);
                imgA1[row][h+i] = ((float)imgA[row][2*i] - (float)imgA[row][2*i+1])/sqrt(2);
            }
            cvCopyImage(imgA_1,dec_img);
	}
    }
    //col
    IplImage *imgA_2 = cvCreateImage(cvSize(dec_img->height,dec_img->width), dec_img->depth, dec_img->nChannels);
    for(int col = 0; col<dec_img->width; col++) {
        for(int row = 0; row<dec_img->height; row++) {
            imgA[row][col] = ((float)imgA[row][col])/sqrt(dec_img->width);
	}
	cvCopyImage(dec_img, imgA_2);
	BwImage imgA2(imgA_2);
	int h = dec_img->width;
	while(h>1) {
            h/=2;
            for(int i=0; i<h; i++) {
                imgA2[i][col] = ((float)imgA[2*i][col] + (float)imgA[2*i+1][col])/sqrt(2);
		imgA2[h+i][col] = ((float)imgA[2*i][col] - (float)imgA[2*i+1][col])/sqrt(2);
            }
            cvCopyImage(imgA_2,dec_img);
	}
    }
    cvReleaseImage(&imgA_2);
    cvReleaseImage(&imgA_1);
    return dec_img;

}

/**
  * Decomposition along Blue channel
  * @Desc: Haar Wavelet Decomposition along blue channel
  */

IplImage* HaarWavelet::decompose_Image_b(IplImage *dec_img)
{
	//cvNamedWindow("a",1);
	//cvShowImage("a",dec_img);
	//cvWaitKey(0);
	RgbImage imgA(dec_img);
	IplImage *imgA_1 = cvCreateImage(cvSize(dec_img->height,dec_img->width), dec_img->depth, dec_img->nChannels);

	//row

	for(int row = 0; row<dec_img->height; row++) {



		for(int col = 0; col<dec_img->width; col++) {
			imgA[row][col].b = ((float)imgA[row][col].b)/sqrt(dec_img->width);
		}
		cvCopyImage(dec_img, imgA_1);
		RgbImage imgA1(imgA_1);
		int h = dec_img->height;
		while(h>1) {
			h/=2;
			for(int i=0; i<h; i++) {
				imgA1[row][i].b = ((float)imgA[row][2*i].b + (float)imgA[row][2*i+1].b)/sqrt(2);
				imgA1[row][h+i].b =((float)imgA[row][2*i].b - (float)imgA[row][2*i+1].b)/sqrt(2);
			}
			cvCopyImage(imgA_1,dec_img);
		}
		//cvReleaseImage(&imgA_1);
	}

	//col
	IplImage *imgA_2 = cvCreateImage(cvSize(dec_img->height,dec_img->width), dec_img->depth, dec_img->nChannels);
 	for(int col = 0; col<dec_img->width; col++) {

		for(int row = 0; row<dec_img->height; row++) {
			imgA[row][col].b = ((float)imgA[row][col].b) / sqrt(dec_img->width);
		}
		cvCopyImage(dec_img, imgA_2);
		RgbImage imgA2(imgA_2);

		int h = dec_img->width;
		while(h>1) {
			h/=2;
			for(int i=0; i<h; i++) {
				imgA2[i][col].b = ((float)imgA[2*i][col].b + (float)imgA[2*i+1][col].b)/sqrt(2);
				imgA2[h+i][col].b = ((float)imgA[2*i][col].b - (float)imgA[2*i+1][col].b)/sqrt(2);
			}
			cvCopyImage(imgA_2,dec_img);
		}
	}
	return dec_img;

}
// end of decomposition along blue channel

/**
  * decomposition along green channel
  * @Desc: Haar Wavelet Decomposition along Green Channel
  */
IplImage* HaarWavelet::decompose_Image_g(IplImage *dec_img)
{
//	cvNamedWindow("a",1);
//	cvShowImage("a",dec_img);
//	cvWaitKey(0);
	RgbImage imgA(dec_img);

	//row
	IplImage *imgA_1 = cvCreateImage(cvSize(dec_img->height,dec_img->width), dec_img->depth, dec_img->nChannels);
	for(int row = 0; row<dec_img->height; row++) {

		for(int col = 0; col<dec_img->width; col++) {
			imgA[row][col].g = ((float)imgA[row][col].g)/sqrt(dec_img->width);
		}
		cvCopyImage(dec_img, imgA_1);
		RgbImage imgA1(imgA_1);
		int h = dec_img->height;
		while(h>1) {
			h/=2;
			for(int i=0; i<h; i++) {
				imgA1[row][i].g = ((float)imgA[row][2*i].g + (float)imgA[row][2*i+1].g)/sqrt(2);
				imgA1[row][h+i].g = ((float)imgA[row][2*i].g - (float)imgA[row][2*i+1].g)/sqrt(2);
			}
			cvCopyImage(imgA_1,dec_img);
		}

	}

	//col
	IplImage *imgA_2 = cvCreateImage(cvSize(dec_img->height,dec_img->width), dec_img->depth, dec_img->nChannels);
 	for(int col = 0; col<dec_img->width; col++) {

		for(int row = 0; row<dec_img->height; row++) {
			imgA[row][col].g = ((float)imgA[row][col].g)/sqrt(dec_img->width);
		}
		cvCopyImage(dec_img, imgA_2);
		RgbImage imgA2(imgA_2);

		IplImage* decompose_Image_b(IplImage *dec_img);int h = dec_img->width;
		while(h>1) {
			h/=2;
			for(int i=0; i<h; i++) {
				imgA2[i][col].g = ((float)imgA[2*i][col].g + (float)imgA[2*i+1][col].g)/sqrt(2);
				imgA2[h+i][col].g = ((float)imgA[2*i][col].g - (float)imgA[2*i+1][col].g)/sqrt(2);
			}
			cvCopyImage(imgA_2,dec_img);
		}

	}
	return dec_img;

}

// end of decomposition along green channel

/**
  * start decomposing along red channel
  * @Desc: Decomposition along red channel
  */
IplImage* HaarWavelet::decompose_Image_r(IplImage *dec_img)
{
//	cvNamedWindow("a",1);
//	cvShowImage("a",dec_img);
//	cvWaitKey(0);
	RgbImage imgA(dec_img);

	//row
	IplImage *imgA_1 = cvCreateImage(cvSize(dec_img->height,dec_img->width), dec_img->depth, dec_img->nChannels);
	for(int row = 0; row<dec_img->height; row++) {

		for(int col = 0; col<dec_img->width; col++) {
			imgA[row][col].r = ((float)imgA[row][col].r)/sqrt(dec_img->width);
		}
		cvCopyImage(dec_img, imgA_1);
		RgbImage imgA1(imgA_1);
		int h = dec_img->height;
		while(h>1) {
			h/=2;
			for(int i=0; i<h; i++) {
				imgA1[row][i].r = ((float)imgA[row][2*i].r + (float)imgA[row][2*i+1].r)/sqrt(2);
				imgA1[row][h+i].r = ((float)imgA[row][2*i].r - (float)imgA[row][2*i+1].r)/sqrt(2);
			}
			cvCopyImage(imgA_1,dec_img);
		}

	}

	//col
	IplImage *imgA_2 = cvCreateImage(cvSize(dec_img->height,dec_img->width), dec_img->depth, dec_img->nChannels);
 	for(int col = 0; col<dec_img->width; col++) {

		for(int row = 0; row<dec_img->height; row++) {
			imgA[row][col].r = ((float)imgA[row][col].r)/sqrt(dec_img->width);
		}
		cvCopyImage(dec_img, imgA_2);
		RgbImage imgA2(imgA_2);

		int h = dec_img->width;
		while(h>1) {
			h/=2;
			for(int i=0; i<h; i++) {
				imgA2[i][col].r = ((float)imgA[2*i][col].r + (float)imgA[2*i+1][col].r)/sqrt(2);
				imgA2[h+i][col].r = ((float)imgA[2*i][col].r - (float)imgA[2*i+1][col].r)/sqrt(2);
			}
			cvCopyImage(imgA_2,dec_img);
		}

	}
//	cvShowImage("a",dec_img);
	return dec_img;

}
// end decomposng

