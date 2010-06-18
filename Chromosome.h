/*
 * Chromosome.h
 *
 *  Created on: 26-May-2010
 *      Author: shirish
 */

#ifndef CHROMOSOME_H_
#define CHROMOSOME_H_

/**
 * Declares basic operations of Chromosome construction and crossover
 */
class Chromosome {
public:
    Chromosome();
    virtual ~Chromosome();
    int **const_chromo(char *);
    int **const_chromo_db(char *);
    int **horizontalCrossover(char *);
    int **verticalCrossover(char*);
private:
    int **chromosome_1;
    int **chromosome_2;
    int **crossedChromosome_1;
    int **crossedChromosome_2;

};

#endif /* CHROMOSOME_H_ */
