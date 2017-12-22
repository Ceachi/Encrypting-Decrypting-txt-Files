#pragma once
#include "stdafx.h"
#include <vector>
#include "mergeSort.h"
using namespace std;
void merge(vector<int> &left, int nLeft, vector<int> &right, int nRight, vector<int> &A, int n) {
	int i = 0, j = 0, k = 0; // i->left[i], j->right[j], k->A[k]
	while (i < nLeft && j < nRight) {
		if (left[i] <= right[j]) {
			A[k] = left[i];
			i++;
		}
		else {
			A[k] = right[j];
			j++;
		}
		k++;
	}
	// put the remaining elements in A
	while (i < nLeft) {
		A[k] = left[i];
		i++;
		k++;
	}
	while (j < nRight) {
		A[k] = right[j];
		j++;
		k++;
	}
}

void mergeSort(vector<int> &A, int n) {
	if (n < 2) return;
	int mid = (n / 2);
	std::vector<int> left(mid);
	std::vector<int> right(n - mid);
	for (int i = 0; i < mid; i++) {
		left[i] = A[i];
	}
	for (int i = mid; i < n; i++) {
		right[i - mid] = A[i];
	}

	mergeSort(left, mid);
	mergeSort(right, n - mid);
	merge(left, mid, right, n - mid, A, n);

}

void printArray(vector<int> &A, int size) {
	int i;
	for (i = 0; i < size; i++)
		printf("%d ", A[i]);
	printf("\n");
}