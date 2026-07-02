#pragma once

#include <string>
#include <vector>


class PmergeMe
{
    private:
        

    public:
        PmergeMe() = default;
        PmergeMe(const PmergeMe& other) = default;
        PmergeMe& operator=(const PmergeMe& other) = default;
        ~PmergeMe() = default;

        static std::vector<int> sort(std::vector<int>);
        

};
