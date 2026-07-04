#include "PmergeMe.hpp"


PmergeMe::Node::Node(int v, int pr, int pa) : value(v), prev(pr), partner(pa) {}

std::size_t PmergeMe::getJacobsthalNumber(std::size_t idx)
{
    for(std::size_t i = jacobsthal.size(); i <= idx; ++i)
    {
        if (i < 2)
            jacobsthal.push_back(static_cast<int>(i));
        else
            jacobsthal.push_back(jacobsthal[i - 1] + 2 * jacobsthal[i - 2]);
    }
    return jacobsthal[idx];
}

std::size_t PmergeMe::getCountComparing()
{
    return count_cmp;
}
