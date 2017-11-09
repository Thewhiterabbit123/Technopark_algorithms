// P(n,k) = P(n, k-1) + P(n - k, k)
//Дано N кубиков. Требуется определить каким количеством способов можно выстроить из этих кубиков пирамиду. 

#include <iostream>

long long int tiny_cube(long long int total_cube) {

 	int **matrix;
 	matrix = new int*[400];

 	for(int i = 0; i < 400; ++i) {
		matrix[i] = new int[400];
	}

	matrix[0][0] = 1;

	for (int i = 1; i < total_cube + 1; ++i) {
		matrix[i][0] = 0;
	}

	for (int n = 0; n < total_cube + 1; ++n) {
		for (int k = 1; k < total_cube + 1; ++k) {
			if (k < n) {
				matrix[n][k] = matrix[n][n];
			} else {
				matrix[n][k] = matrix[n][k - 1] + matrix[n - k][k];
			}
		}
	}

	int answer = matrix[total_cube][total_cube];
	
	// for(int i = 0; i < 400; ++i) {
	// 	delete [] matrix[i];
	// }
	// delete [] matrix;

	return answer;
}

int main() {
	long long int n = 0;
	std::cin >> n;
	std::cout << tiny_cube(n);
}