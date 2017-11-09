//Дано выражение в инфиксной записи. 
//Вычислить его, используя перевод выражения в постфиксную запись. 
//Выражение не содержит отрицительных чисел. 
//Количество операций ≤ 100. 

#include <iostream>
#include <string.h>
#include <cstdlib>


class Stack {
    private:
        int _size;
        int _capacity;
        int *value;
        
    public:
        Stack():_size(0), value(nullptr), _capacity(0) {};
        ~Stack();
        void array_realloc();
        void push(const int& c);
        int  pop();
        bool is_empty();
};

Stack::~Stack() {
    delete[] value;
}

void Stack::array_realloc() {
    if (_capacity == 0) {
        _capacity =  1;
    }
    _capacity *= 2;
    int* temp = value;
    value = new int[_capacity];
    memcpy(value, temp, sizeof(int)*_size);
    delete[] temp;
} 

void Stack::push(const int& c) {
    if (_size == _capacity) {
        array_realloc();
    }
    value[_size++] = c;
}

int Stack::pop() {
    if(is_empty()) {
        return 0;
    }
    return value[--_size];
}

bool Stack::is_empty() {
    return (_size == 0);
}

class RPN {        
    public:
        RPN(const char* input);
        ~RPN();
        int   calculate();
        
    private:
        char* parse_to_rpn();
        int   one_operation(int lhs, int rhs, char _operator);
        bool  is_operator(const char c);
        char  priority(const char);
        char* input;
        char* polish;
        int   answer;
    
};
RPN::RPN(const char* input) {
    int len = strlen(input) + 1;
    this->input = new char[len];
    strcpy(this->input, input);
    polish = new char[1024];
}
RPN::~RPN() {
    delete[] input;
    delete[] polish;
}
bool RPN::is_operator(const char c) {
    return(c == '-' || c == '+' || c == '*' || c == '/');
}
char RPN::priority(const char _operator) {
    switch (_operator) {
        case '(':
            return 0;
        case ')':
            return 1;
        case '+':
            return 2;
        case '-':
            return 2;
        case '*':
            return 3;
        case '/' :
            return 3;
    }
}
char* RPN::parse_to_rpn() {
    Stack* st = new Stack();
    int i = 0, j = 0;
    char last_ch = '\0';
    
    while (input[i] != '\0') {
        
        if (isdigit(input[i])) {
            polish[j++] = input[i++];
            continue;
        } else {
            polish[j++] = ' ';
        }
        
        if (is_operator(input[i]) || input[i] == '(' || input[i] == ')') {
            if (st->is_empty()) {
                st->push(input[i++]);
                continue;
            } else {
                while (!st->is_empty()) {
                    last_ch = st->pop();
                    
                    if ((priority(input[i]) <= priority(last_ch)) && is_operator(last_ch) && is_operator(this->input[i])) {
                        polish[j++] = last_ch;
                    } else {
                        st->push(last_ch);
                        break;
                    }
                }
                if (input[i] != ')') {
                    st->push(input[i++]);
                    continue;
                }
            }
            
            if (input[i] == ')') {
                while (true) {
                    last_ch = st->pop();
                    
                    if (last_ch == '(') {
                        break;
                    }
                    polish[j++] = last_ch;
                }
            }
        }
        i++;
    }
    
    while (!st->is_empty()) {
        polish[j++] = st->pop();    
    }
    polish[j] = '\0';

    delete st;
    return polish;   
}
int RPN::one_operation(int lhs, int rhs, char _operator) {
    switch (_operator) {
        case '+':
            return lhs + rhs;
        case '-':
            return lhs - rhs;
        case '/' :
            return lhs / rhs;
        case '*':
            return lhs * rhs;
    }
    
}

int RPN::calculate() {
    const char* rpn = parse_to_rpn();
    char* buf = new char[1024];
    
    Stack *st = new Stack();
    
    char _operator = 0;
    int i = 0, j = 0;
    int result_num = 0;
    int buf_res = 0;
    int lhs = 0;
    int rhs = 0;
    
    while (rpn[i] != '\0') {
        if (strlen(buf) != 0 && (rpn[i] == ' ' || is_operator(rpn[i]))) {
            buf[j] = '\0';
            st->push(atoi(buf));
            j = 0;
            buf[0] = '\0';
        }
        
        if (isdigit(rpn[i])) {
            buf[j++] = rpn[i];
        }
        
        if (is_operator(rpn[i])) {
            rhs = st->pop();
            lhs = st->pop();
            _operator = rpn[i++];
            buf_res = one_operation(lhs, rhs, _operator);
            st->push(buf_res);
            continue;
        }
        
        i++;
    }
    result_num = buf_res;
    
    delete st;
    delete buf;
    
    return result_num;
    
}

int main() {
    
    char* str = new char[1024];    
    std::cin >> str;

    RPN* rpn = new RPN(str);
    std::cout << rpn->calculate();

    delete str;
    delete rpn;
    
    return 0;
}

