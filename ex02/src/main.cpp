/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:11:34 by ybutkov           #+#    #+#             */
/*   Updated: 2026/07/03 21:16:45 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "PmergeMe.hpp"
#include "TimeProfiler.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <climits>
#include <iomanip>


namespace {

bool parseToken(std::string& token, int& out)
{
	std::stringstream ss(token);
	long val;
	if (!(ss >> val) || !ss.eof())
		return false;
	if (val < 0 || val > INT_MAX)
		return false;
	
	out = static_cast<int>(val);
	return true;
}

template <typename T>
void printValues(const T& container, const std::string& name)
{
	if (container.empty())
		return ;
    std::cout << std::right; 

    std::cout << std::setw(10) << name << ": ";
	auto currIt = container.begin();
    std::cout << *currIt;
	++currIt;
	std::size_t i = 1;
	while (currIt != container.end())
	{
		if (i < 10)
			std::cout << " " << *currIt;
		else {
			std::cout << " [...] ";
			break;
		}
		++i;
		++currIt;
    }
    std::cout << std::endl;
}

template <typename Iterator>
bool isSorted(Iterator first, Iterator last)
{
    if (first == last)
        return true;
    Iterator next = first;
    ++next;
    for (; next != last; ++first, ++next)
        if (*next < *first)
            return false;
    return true;
}

}

int main(int argc, char** argv)
{
	if (argc < 2) {
        std::cerr << "Error" << std::endl;
        return 1;
    }

	std::vector<int> values;
	TimeProfiler timeProfiler("pmerge");
	
	for (int i = 1; i < argc; ++i)
	{
    	std::stringstream ss(argv[i]);
    	std::string token;
    	while (ss >> token)
    	{
        	int n;
        	if (!parseToken(token, n))
			{
				std::cerr << "Error" << std::endl;
				return 1;
			}
        	values.push_back(n);
    	}
	}

	if (values.empty()) {
        std::cerr << "Error" << std::endl;
        return 1;
    }

	printValues(values, "Before");
	
	timeProfiler.start();
	std::vector<int> res = PmergeMe::sort(values);
	timeProfiler.stop();

	printValues(res, "After");
	std::cout << "Time to process a range of " << values.size()
          << " elements with std::vector : "
          << timeProfiler.getDurationInMicroseconds() << " us" << std::endl;

		  std::cout << "Result is " << (isSorted(res.begin(), res.end()) ? "sorted" : "not sorted") << std::endl;
	std::cout << "Comparisons count = " << PmergeMe::getCountComparing() << std::endl;
	
	return 0;
}
