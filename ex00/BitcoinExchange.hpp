/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazihaaankour <nazihaaankour@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 11:46:05 by naankour          #+#    #+#             */
/*   Updated: 2025/12/23 00:36:29 by nazihaaanko      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <map>
#include <string>
#include <cstdlib>
#include <fstream>

class BitcoinDB
{
	private:
		std::map<std::string, float> map;
	public:
		BitcoinDB();
		~BitcoinDB();
		BitcoinDB(const BitcoinDB& other);
		BitcoinDB& operator=(const BitcoinDB& other);

		bool isValidDate(const std::string& date);
		bool parseLine(const std::string& line, std::string& date, double& value);
		bool loadFile(const std::string& filename);

		bool loadDatabase(const std::string& filename);
};