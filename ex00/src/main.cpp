/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 23:12:55 by ybutkov           #+#    #+#             */
/*   Updated: 2026/06/29 22:47:54 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "BitcoinExchange.hpp"
#include "CSVReader.hpp"
#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <iomanip>



int main(int argc, char** argv)
{
	if (argc != 2) {
        std::cerr << "Error: could not open file." << std::endl;
        return 1;
    }

	try {
    	CSVReader dbReader("data.csv", ",", true, {"date","exchange_rate"});
    	if (!dbReader.isOpen()) {
    	    std::cerr << "Error: missing data.csv" << std::endl;
    	    return 1;
    	}

    	BitcoinExchange bybit;
		bybit.loadPricesFromCSV(dbReader);

		std::string balanceFileName = argv[1];
    
		CSVReader balanceReader(balanceFileName, " | ", true, {"date","value"});
    	if (!balanceReader.isOpen()) {
    	    std::cerr << "Error: could not open file." << std::endl;
    	    return 1;
    	}
		bybit.processBalanceFromCSV(balanceReader);

	} catch (const std::exception& ex) {
		std::cerr << "Error: " << ex.what() << std::endl;
		return 1;
	}
    
	return 0;
}
