//1_4. ​Дано натуральное число N. Представить N в виде A + B, так, что НОД(A, B) максимален, A ≤ B. Вывести
//A и B. Если возможно несколько ответов - вывести ответ с минимальным A.

#include <iostream>

int simple_number(int n) {
	int j = 2, max = 1;

    while (n > 1) {
        if (n % j == 0) {
        	max = j;
            n /= j;
        } else {
            ++j;
        }
    }
    return max;
}


int main() {
	int n;
	std::cin >> n;
	int A = simple_number(n);
	int B = n - A;
	std::cout << A << ' ' << B << std::endl;

}