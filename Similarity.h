/*
 * Similarity.h
 *
 *  Created on: 26-May-2010
 *      Author: shirish
 */

#ifndef SIMILARITY_H_
#define SIMILARITY_H_

#include "headers.h"
/**
 * Declares functions used in calculation of similarity between images
 */
class Similarity {
public:
    Similarity();
    virtual ~Similarity();
    long wave_coeff_stg(IplImage *wave_coeff, IplImage *db_img);
    long wave_coeff_loc_aware(char *, char* );
private:

};

#endif /* SIMILARITY_H_ */
