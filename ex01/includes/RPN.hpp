#pragma once

#include <string>
#include <stack>


class RPN
{
    private:
        std::stack<double> rpnStack;
        void reset();
        void doOperation(char op);
        bool isOperator(char ch);

    public:
        RPN() = default;
        RPN(const RPN& other) = default;
        RPN& operator=(const RPN& other) = default;
        ~RPN() = default;

        double calcucate(const std::string& expressionStr);

};
