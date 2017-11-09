//Реализуйте дек с динамическим зацикленным буфером.
//Для тестирования дека на вход подаются команды.
//В первой строке количество команд. Затем в каждой строке записана одна команда.
//Каждая команда задаётся как 2 целых числа: a b.
//a = 1 - push front
//a = 2 - pop front,
//a = 3 - push back,
//a = 4 - pop back.
#include <cstring>
#include <iostream>

template <typename T> 
class Deque {
	public:
		Deque();
		~Deque();

		const bool is_empty() const;

        T pop_back();
        T pop_front();

        void push_front(const T& elem);
        void push_back (const T& elem);

    private:
    	T*     _buffer;
    	int    _capacity;
        int    _head;
        int    _end;
        size_t _size;

        void array_realloc();
};
template <typename  T>
Deque<T>::Deque(): _buffer(nullptr), _size(0), _capacity(0), _head(0), _end(0) {
	_capacity = 4;
    _buffer = new int[_capacity];
}

template <typename  T>
Deque<T>::~Deque() {
        delete[] _buffer;
} 

template <typename  T>
const bool Deque<T>::is_empty() const {
    return (_size == 0);
}  

template <typename  T>
T Deque<T>::pop_back() {
    if (is_empty()) {
        return -1;
    }
    _end = ((_end - 1) + _capacity) % _capacity;
    T temp = _buffer[_end];
    --_size;
   	return temp;
} 

template <typename  T>
T Deque<T>::pop_front() {
    if (is_empty()) {
        return -1;
    }
    T temp = _buffer[_head];
    _head = (_head + 1) % _capacity;
    --_size;   
    return temp;
}

template <typename  T>
void Deque<T>::array_realloc() {
    T *newBuffer = new int[_capacity * 2];
    memcpy(newBuffer, _buffer + _head, (_capacity - _head) * sizeof(T));

    if (_head != 0) {
        memcpy(newBuffer + (_capacity - _head), _buffer, _end * sizeof(T));
    }

    delete[] _buffer;

    _buffer = newBuffer;
    _head = 0;
    _end = _capacity;
    _capacity *= 2;
} 

template <typename  T>
void Deque<T>::push_back(const T& elem) {
    if (_size == _capacity) {
        array_realloc();
    }
    _size++;
    _buffer[_end] = elem;
    _end = (_end + 1) % _capacity;
} 

template <typename  T>
void Deque<T>::push_front(const T& elem) {
    if (_size == _capacity) {
        array_realloc();
    }
  	_size++;
    _head = ((_head - 1) + _capacity) % _capacity;
    _buffer[_head] = elem;
} 
int main() {
	Deque <int> _deque;
	int n = 0, comand = 0, number = 0;
	bool correct = true;

	std::cin >> n;
	for (int i = 0; i < n; ++i) {
		std::cin >> comand >> number;

		switch(comand) {
			case 1: 
				_deque.push_front(number);
				break;
			case 2:
				if (number != _deque.pop_front()) {
                	correct = false;
            	}
				break;
			case 3:
				_deque.push_back(number);
				break;
			case 4: 
				if (number != _deque.pop_back()) {
                	correct = false;
            	}
		}
	}
	if (!correct) {
		std::cout << "NO";
	} else {
		std::cout << "YES";
	}
	return 0;
}