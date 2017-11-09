//2_1. Даны два массива целых чисел одинаковой длины A[0..n-1] и B[0..n-1]. 
//Необходимо найти первую пару индексов i0 и j0, i0 ≤ j0, такую что A[i0] + B[j0] = max {A[i] + B[j], 
//где 0 <= i < n, 0 <= j < n, i <= j}. Время работы - O(n).

#include <iostream>
#include "assert.h"

void first(const int n, const int* A, const int* B, int *i0, int *j0) {

	int indexA = 0;

	for(int i = 0; i < n; i++) {
		
		if(A[indexA] < A[i]) {
			indexA = i;
		}

		if((A[*i0] + B[*j0] < A[indexA] + B[i]) && i >= indexA) {
			*j0 = i;
			*i0 = indexA;
		}
	}
}

int main() {
	int n = 0, i0 = 0, j0 = 0;
	std::cin >> n;
	
	if(n < 0 || n > 100000) {
		return 0;
	}

	int* A = new int[n];
	int* B = new int[n];

	for(int i = 0; i < n; i++) {
		std::cin >> A[i];
	}
	for(int j = 0; j < n; j++) {
		std::cin >> B[j];
	}

	first(n, A, B, &i0, &j0);

	std::cout << i0 << ' ' << j0;

	delete[] A;
	delete[] B;

	return 0;
}