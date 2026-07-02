/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:11:34 by ybutkov           #+#    #+#             */
/*   Updated: 2026/07/01 21:33:10 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "PmergeMe.hpp"
#include <iostream>
#include <sstream>
#include <map>
#include <string>
#include <vector>


int main(int argc, char** argv)
{
	(void)argc;
	(void)argv;
	
	// if (argc < 2) {
    //     std::cerr << "Error" << std::endl;
    //     return 1;
    // }

	std::string f = "17 3 22 8 14 25 1 19 6 11 23 9 16 4 20 12 7 24 2 15 10 21 5 18 13";
	std::stringstream ss;

	ss.str(f);
	std::vector<int> values;
	int n;
	while (ss >> n)
    	values.push_back(n);
		
	std::vector<int> res = PmergeMe::sort(values);
	
	
	return 0;
}
