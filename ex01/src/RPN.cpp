#include "RPN.hpp"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <list>
#include <cctype>


void RPN::reset() {
    this->rpnStack = std::stack<double>(); 
}

bool RPN::isOperator(char ch) {
        return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

void RPN::doOperation(char op)
{
    if (this->rpnStack.size() < 2)
        throw std::runtime_error("Not enough operands for operator");
    double number2 = this->rpnStack.top();
    this->rpnStack.pop();
    double number1 = this->rpnStack.top();
    this->rpnStack.pop();

    double result;
    switch (op) {
        case '+': 
            result = number1 + number2;
            break;
        case '-': 
            result = number1 - number2;
            break;
        case '*': 
            result = number1 * number2;
            break;
        case '/':
            if (number2 == 0)
                throw std::runtime_error("Division by zero");
            result = number1 / number2;
            break;
        default :
            throw std::runtime_error("Incorrect operation");
    }
    this->rpnStack.push(result);
}


double RPN::calcucate(const std::string& expressionStr)
{
    this->reset();

    for (char ch : expressionStr) {
        if (std::isspace(ch))
            continue;
        if (std::isdigit(ch))
            this->rpnStack.push(ch - '0');
        else if (this->isOperator(ch))
            this->doOperation(ch);
        else
            throw std::runtime_error("Unkwoun character");
    }
    double res = this->rpnStack.top();
    this->rpnStack.pop();
    if (!this->rpnStack.empty())
        throw std::runtime_error("Too many operands left in the stack");
    return res;
}
