/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 23:12:55 by ybutkov           #+#    #+#             */
/*   Updated: 2026/05/16 23:23:03 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "BitcoinExchange.hpp"
#include "CSVReader.hpp"
#include <iostream>
#include <map>
#include <string>
#include <fstream>



int main()
{
	std::map<std::string, double> priceMap = CSVReader::loadPricesCSV("data.csv");
	std::cout << priceMap.size() << std::endl;
	return 0;
}
