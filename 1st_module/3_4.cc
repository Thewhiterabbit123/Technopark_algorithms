//Vasilieva Nadezda APO-12

// 3_4. Дан отсортированный массив различных целых чисел A[0..n-1] и массив целых чисел B[0..m-1]. 
// Для каждого элемента массива B[i] найдите минимальный индекс элемента массива A[k], ближайшего по значению к B[i]. 
// Время работы поиска для каждого элемента B[i]: O(log(k)). n ≤ 110000, m ≤ 1000.
#include <iostream>
#include <cmath>

int BinarySearch(const int *mass, int n, int value) {
	int left   = 0;
	int right  = n - 1;
	int middle = 0;

	//a[3] = {1 ,7 ,20}
	//b[3] = {3, 16, 8}

	while (*(mass + middle) < value) {
		left = middle;
		if (middle == 0) {
			middle = 1;
		}
		if ((middle *= 2) > n-1) {
			break;
		}
	}

	if ((middle * 2) < n-1) {
			right = middle;
	}

	while(true) {
		if(left > right) {
			return middle;
		}

		middle = (right + left)/2;

		if(*(mass + middle) == value){
			return middle;
		}
		if(*(mass + middle) < value) {
			left = middle + 1;
		}
		if(*(mass + middle) > value) {
			right = middle - 1; 
		}
		if((*(mass + middle + 1) > value) && (*(mass + middle) < value)) {		
			if (std::abs(*(mass+middle) - value) <= std::abs(*(mass + middle + 1) - value)) {		
				return middle;
			} else {
				return middle + 1;
			}
		}
	}
}


int main() {
	int n = -1, m = -1;
	
	std::cin >> n;
	//assert(n > 0 && n < 110000);
	int* A = new int[n];
	for(int i = 0; i < n; i++) {
		std::cin >> A[i];
	}

	std::cin >> m;
	int* B = new int[m];
	for(int i = 0; i < m; i++) {
		std::cin >> B[i];
	}

	for(int i = 0; i < m; i++) {
		std::cout << BinarySearch(A, n, *(B+i)) << " ";
	}


	delete[] A;
	delete[] B;

}