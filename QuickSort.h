/*
 * QuickSort.h
 *
 *  Created on: 02-Jun-2010
 *      Author: shirish
 */

#ifndef QUICKSORT_H_
#define QUICKSORT_H_

class QuickSort {
public:
	void swap(int &a, int &b);
	void quick_sort(int arr[], int p, int r);
	int partition(int arr[], int p, int r);
};

#endif /* QUICKSORT_H_ */
