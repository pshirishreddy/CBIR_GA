/*
 * Similarity.cpp
 *
 *  Created on: 26-May-2010
 *      Author: shirish
 */

#include "Similarity.h"
#include <iostream>
#include <fstream>
#include <string>
#include "Chromosome.h"

using namespace std;

/**
 * Functions for calculating similarity of the query image with the database images
 * 1. Gray scale wavelet decomposed similarity calculation
 * 2. Location aware Wavelet decomposed similarity calculator
 */
Similarity::Similarity() {
}


Similarity::~Similarity() {
}
/**
 * @Desc: Grey scale images similarity calculation using jacobs equation
 * @vars: Grey Scale images, Query and DB images
 */
long Similarity::wave_coeff_stg(IplImage *wave_coeff, IplImage *db_img) {
    int count = 0;
    BwImage ImgW(wave_coeff);
    int arr[256][256];
    for(int i=0;i<256;i++) {
        for(int j=0; j<256; j++) {
            arr[i][j] = (int)ImgW[i][j];
            count++;
	}
    }
    count = 0;
    BwImage db_ImgW(db_img);
    int db_arr[256][256];
    for(int i=0;i<256;i++) {
	for(int j=0; j<256; j++) {
            db_arr[i][j] = (int)db_ImgW[i][j];
	}
    }
    cout<<"\n\n ********* SIMILARITY USING JACOBS EQUATION *********\n\n";
    int q_sum =0, d_sum = 0;
    for(int i=0;i<256;i++) {
    	for(int j=0; j<256; j++) {
            q_sum += arr[i][j];
            d_sum += db_arr[i][j];
        }
    }
    int jacob_dist = 0;
    for(int i=0;i<256;i++) {
    	for(int j=0; j<256; j++) {
            jacob_dist += abs(arr[i][j] - db_arr[i][j]);
        }
    }
    cout<<abs(q_sum - d_sum) + jacob_dist<<endl;
    return (jacob_dist);
}

/**
 * @Desc: Location aware wavelet decomposition and similarity calculation using Jacobs equation
 * Calls Chromosme construction methods of both Query and Database images
 */
long Similarity :: wave_coeff_loc_aware(char* query_txt, char* db_txt) {
    Chromosome C;
    int **val1 = C.const_chromo(query_txt);
    int **val2;
    int SIM;
    val2 = C.const_chromo_db(db_txt);
	for(int i=0; i<1024; i++) {
       	for(int j=0; j<3; j++) {
       		SIM += abs(val1[i][j] - val2[i][j]);
       	}
    }

    return SIM;
}
