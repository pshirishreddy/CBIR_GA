/*
 * QuickSort.cpp
 *
 *  Created on: 02-Jun-2010
 *      Author: shirish
 */

#include "QuickSort.h"
#include <algorithm>

void QuickSort :: swap(int &a, int &b) {
	int t = a;
	a = b;
	b = t;
}
int QuickSort :: partition(int arr[], int p, int r) {
	int i;
	int x = arr[r];
	i = p-1;
	for (int j=p; j<=r-1; j++) {
		if(arr[j]<=x) {
			i++;
			swap(arr[i], arr[j]);
		}
	}
	swap(arr[i+1], arr[r]);
	return i+1;

}

void QuickSort :: quick_sort(int arr[], int p, int r) {
	int q;
	if(p<r) {
		q = partition(arr, p, r);
		quick_sort(arr, p, q-1);
		quick_sort(arr, q+1, r);
	}
}

