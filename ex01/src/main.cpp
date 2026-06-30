/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 22:46:07 by ybutkov           #+#    #+#             */
/*   Updated: 2026/06/30 02:17:10 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "RPN.hpp"
#include <iostream>
#include <map>
#include <string>


int main(int argc, char** argv)
{
	if (argc != 2) {
        std::cerr << "Error: Need expression." << std::endl;
        return 1;
    }

	RPN rpn;
	double res;
	try {
		res = rpn.calcucate(argv[1]);
	} catch (const std::exception& ex) {
		std::cerr << "Error" << std::endl;
		return 1;
	}
    std::cout << res << std::endl;
	return 0;
}
