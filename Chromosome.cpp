/*
 * Chromosome.cpp
 *
 *  Created on: 26-May-2010
 *      Author: shirish
 */

#include "Chromosome.h"
#include <fstream>
#include <string.h>
#include <iostream>
#include <stdlib.h>

using namespace std;
/**
 * Initiate memory for construction of chromosomes from the text files
 * chromosome_1, chromosome_2 for performing crossover
 * crossedChromosomes for storing the new wavelet coefficients
 */
Chromosome::Chromosome() {
	chromosome_1 = new int*[1024];
	for(int i=0; i<1024; i++) {
		chromosome_1[i] = new int[3];
	}
	chromosome_2 = new int*[1024];
	for(int i=0; i<1024; i++) {
		chromosome_2[i] = new int[3];
	}
	crossedChromosome_1 = new int*[1024];
	for(int i=0; i<1024; i++) {
		crossedChromosome_1[i] = new int[3];
	}
	crossedChromosome_2 = new int*[1024];
	for(int i=0; i<1024; i++) {
		crossedChromosome_2[i] = new int[3];
	}

}

/**
 * Free up memory allocated dynamically while construction of chromosome
 */
Chromosome::~Chromosome() {
	for(int i=0; i<1024; i++) {
		delete [] chromosome_1[i];
	}
	delete [] chromosome_1;

	for(int i=0; i<1024; i++)
		delete [] chromosome_2[i];
	delete [] chromosome_2;

	for(int i=0; i<1024; i++)
		delete [] crossedChromosome_1[i];
	delete [] crossedChromosome_1;

	for(int i=0; i<1024; i++)
		delete [] crossedChromosome_2[i];
	delete [] crossedChromosome_2;

}

/**
 * Construction of Chromosome_1 of Query Image using the text files
 */
int** Chromosome :: const_chromo(char *file_name_rgb) {
	string str;
	ifstream rgb_file(file_name_rgb, ios::in);
	ofstream rgb_dup("rgb_dup.txt", ios::out);
	for(int i=0; i<1024; i++) {
		for(int j=0; j<3; j++) {
			rgb_file>>str;
			chromosome_1[i][j]=atoi(str.c_str());
			rgb_dup<<str;
			rgb_dup<<"\t";
		}
		rgb_dup<<"\n";
	}
	rgb_dup.close();
	rgb_file.close();
	return chromosome_1;
}

/**
 * Construction of Chromosome_2 for each individual Database image
 */
int **Chromosome :: const_chromo_db(char *file_name_rgb) {
	string str;
	ifstream rgb_file(file_name_rgb, ios::in);
	for(int i=0; i<1024; i++) {
		for(int j=0; j<3; j++) {
			rgb_file>>str;
			chromosome_2[i][j] = atoi(str.c_str());
		}
	}
	rgb_file.close();
	return chromosome_2;
}

/**
 * Performing Genetic Operations of Crossover
 * 1. Horizontal Cross over
 */
int **Chromosome :: horizontalCrossover(char *file) {
	string str;
	chromosome_1 = const_chromo("rgb_pos.txt");
	ifstream high_fit(file, ios::in);
	for(int i=0; i<1024; i++) {
		for(int j=0; j<3; j++) {
			high_fit>>str;
			crossedChromosome_1[i][j] = atoi(str.c_str());
		}
	}
	high_fit.close();
	for(int i=0; i<1024; i++) {
		swap(chromosome_1[i][1], crossedChromosome_1[i][1]);
	}

	ofstream hybrid1("hybrid1.txt", ios::out);
	ofstream hybrid2("hybrid2.txt", ios::out);
	for(int i=0; i<1024; i++) {
		for(int j=0; j<3; j++) {
			hybrid1<<chromosome_1[i][j]<<"\t";
			hybrid2<<crossedChromosome_1[i][j]<<"\t";
		}
		hybrid1<<"\n";
		hybrid2<<"\n";
	}
	hybrid2.close();
	hybrid1.close();
}

/**
 * 2.Vertical Cross over
 */
int **Chromosome :: verticalCrossover(char *file) {
	string str;
	chromosome_1 = const_chromo("hybrid1.txt");
	ifstream high_fit(file, ios::in);
	for(int i=0; i<1024; i++) {
		for(int j=0; j<3; j++) {
			high_fit>>str;
			crossedChromosome_1[i][j] = atoi(str.c_str());
		}
	}
	high_fit.close();
	for(int i=0; i<512; i++) {
		for(int j=0; j<3; j++){
			swap(chromosome_1[i][j], crossedChromosome_1[i][j]);
		}
	}

	ofstream hybrid1("hybrid1.txt", ios::out);
	ofstream hybrid2("hybrid2.txt", ios::out);
	for(int i=0; i<1024; i++) {
		for(int j=0; j<3; j++) {
			hybrid1<<chromosome_1[i][j]<<"\t";
			hybrid2<<crossedChromosome_1[i][j]<<"\t";
		}
		hybrid1<<"\n";
		hybrid2<<"\n";
	}
	hybrid2.close();
	hybrid1.close();
}
