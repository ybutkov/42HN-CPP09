/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:11:34 by ybutkov           #+#    #+#             */
/*   Updated: 2026/07/03 01:07:58 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "PmergeMe.hpp"
#include <iostream>
#include <sstream>
#include <map>
#include <string>
#include <vector>
#include <climits>


namespace {

bool parseToken(std::string& token, int& out)
{
	std::stringstream ss(token);
	long val;
	if (!(ss >> val) && !ss.eof())
		return false;
	if (val < 0 || val > INT_MAX)
		return false;
	
	out = static_cast<int>(val);
	return true;
}
}

// $(shuf -i 1-100000 -n 3000 | tr '\n' ' ')
int main(int argc, char** argv)
{
	(void)argc;
	(void)argv;
	
	if (argc < 2) {
        std::cerr << "Error" << std::endl;
        return 1;
    }

	// "17 3 22 8 14 87 25 1 19 36  6 11 23 9 16 4 20 12 7  28 35 24 2 15 10 21 5 18 13"
	// std::string f = "17 3 22 8 14 25 1 19 6 11 23 9 16 4 20 12 7 24 2 15 10 21 5 18 13";
	// std::string f = argv[1];
	// std::string f;
	std::stringstream ss;
	std::vector<int> values;
	
	for (int i = 1; i < argc; ++i)
	{
    	std::stringstream ss(argv[i]);
    	std::string token;
    	while (ss >> token)
    	{
        	int n;
        	if (!parseToken(token, n) || n < 0 || n > INT_MAX)
			{
				std::cerr << "Error2" << std::endl;
				return 1;
			}
        	values.push_back(n);
    	}
	}

	// for (int i = 1; i < argc; ++i)
	// {
	// 	ss.str(argv[i]);
	// 	long n;
	// 	char remaining;

	// 	while (ss >> n)
	// 	{
	// 		if (n >= 0 && n <= INT_MAX)
	// 			values.push_back(static_cast<int>(n));
	// 		else {
	// 			std::cout << n +1<< std::endl;
	// 			std::cerr << "Error2" << std::endl;
	// 			return 1;
	// 		}
	// 	}
	// 	std::cout << n << std::endl;
	// 	if (ss >> remaining) {
    //         std::cerr << "Error3" << std::endl;
	// 		return 1;
    //     }
	// 	std::cout << ">" << remaining << "<" << std::endl;
    		
	// 	ss.clear();
		
	// }
		
	std::vector<int> res = PmergeMe::sort(values);

	// for (std::size_t idx = 0; idx < 15; ++idx)
	// {
	// 	int n = PmergeMe::getJacobsthalNumber(idx);
	// 	std::cout << n << ",";
	// }
	// int n = PmergeMe::getNextJacobsthalNumber(0);
	// std::cout << n << "\n";
	// n = PmergeMe::getNextJacobsthalNumber(1);
	// std::cout << n << "\n";
	// n = PmergeMe::getNextJacobsthalNumber(4);
	// std::cout << n << "\n";
	// n = PmergeMe::getNextJacobsthalNumber(5);
	// std::cout << n << "\n";
	// n = PmergeMe::getNextJacobsthalNumber(12);
	// std::cout << n << "\n";

	// std::cout << std::endl;

	
	
	
	
	return 0;
}
