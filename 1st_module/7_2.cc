/* 7_2. Заявки на переговоры.
В большой IT-фирме есть только одна переговорная комната. Желающие посовещаться заполняют заявки с желаемым временем начала и конца. Ваша задача определить максимальное количество заявок, которое может быть удовлетворено.
Число заявок  ≤ 100000.
Формат входных данных:
Вход содержит только пары целых чисел  —  начала и концы заявок.
Формат выходных данных:
Выход должен содержать натуральное число  — максимальное число заявок.
 */

#include <cstring>
#include <iostream>


class Meeting {
	private:
		unsigned int _start;
		unsigned int _end;

	public:
		Meeting(): _start(0), _end(0) { }
		Meeting(unsigned int start, unsigned int end): _start(start), _end(end) { }

		const unsigned int start() const;
		const unsigned int end()   const;

		Meeting& operator=  (const Meeting& rhs);
		friend std::istream& operator >> (std::istream&, Meeting&);
		friend bool operator < (const Meeting &rhs, const Meeting &lhs);
		friend bool operator > (const Meeting &rhs, const Meeting &lhs);
};

Meeting& Meeting::operator=(const Meeting& rhs) {
    this->_start = rhs._start;
    this->_end = rhs._end;
    return *this;
}

const unsigned int Meeting::start() const {
    return this->_start;
} 
const unsigned int Meeting::end() const {
    return this->_end;
} 

bool operator  < (const Meeting& lhs, const Meeting& rhs) {
    if (lhs._end < rhs._end) {
        return 1;
    } 
    return 0;
}

bool operator  > (const Meeting& lhs, const Meeting& rhs) {
    if (lhs._end > rhs._end) {
        return 1;
    } 
    return 0;
}

std::istream& operator >> (std::istream& is, Meeting& obj) {
    
    unsigned int begin = 0, end = 0;

	is >> obj._start;
	is >> obj._end;
 
    return is;
}

class Meetings {
    private:
        Meeting* value;
        size_t _capacity;
        size_t _size;
        void array_realloc();

    public:
        Meetings(): _size(0), _capacity(0), value(nullptr) {};
        ~Meetings();
        void push_back(const Meeting elem);
        void quickSort(int a, int b);
        const size_t size() const;
        Meeting operator[](size_t n);
};

Meetings::~Meetings() {
    if (_capacity != 0 ) {
        delete[] value;
    }
} 
void Meetings::array_realloc() {
    if (_capacity == 0) {
        _capacity =  1;
    }
    _capacity *= 2;
    Meeting* temp = value;
    value = new Meeting[_capacity];
    memcpy(value, temp, sizeof(Meeting)*_size);
    delete[] temp;
} 

void Meetings::push_back(const Meeting elem) {
    if(_size ==_capacity) {
        array_realloc();
    }
    value[_size++] = elem;
} 

const size_t Meetings::size() const {
    return this->_size;
} 

Meeting Meetings::operator[](size_t i) {
    return value[i];
}

void Meetings::quickSort(int left, int right) {
  	Meeting pivot  = value[(left + right) / 2]; 
	int i = left;
    int j = right;
    while (i <= j) {
        while (i < _size && value[i] < pivot) {
            i++;
        }
        while (j < _size && value[j] > pivot) {
            j--;
        }
        if (i >= _size || j >= _size) {
            break;
        }
        if (i <= j) {
            Meeting temp = value[i];
            value[i] = value[j];
            value[j] = temp;
            i++;
            j--;
        }
    }
    if (j > _size) {
        j = 0;
    }
    if (left < j) {
        quickSort(left, j);
    }
    if (i < right) {
        quickSort(i, right);
    }
}

int count_meetings(Meetings &meetings) {
	meetings.quickSort(0, meetings.size() - 2);

	int count = 1;
	int j = 0;

	for (int i = 1; i < meetings.size(); ++i) {
		if (meetings[i].start() >= meetings[j].end()) {
			count++;
			j = i;
		}
	}

	return count;
}

int main() {
	Meetings meetings;

	while (!std::cin.eof()) {
		Meeting temp;
		std::cin >> temp;

		meetings.push_back(temp);
	}
	
	std::cout << count_meetings(meetings);

	return 0;
}

