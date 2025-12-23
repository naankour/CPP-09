/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazihaaankour <nazihaaankour@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 11:46:02 by naankour          #+#    #+#             */
/*   Updated: 2025/12/23 00:58:18 by nazihaaanko      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinDB::BitcoinDB() {}

BitcoinDB::~BitcoinDB() {}

BitcoinDB::BitcoinDB(const BitcoinDB& other) 
{
	*this = other;
}

BitcoinDB& BitcoinDB::operator=(const BitcoinDB& other) 
{
	if (this != &other)
		map = other.map;
	return (*this);
}

bool BitcoinDB::isValidDate(const std::string& date)
{
	if (date.size() != 10 || date[4] != '-' || date[7] != '-')
		return false;
	
	int year = std::atoi(date.substr(0, 4).c_str());
	int month = std::atoi(date.substr(5, 2).c_str());
	int day = std::atoi(date.substr(8, 2).c_str());

	if (year <= 0)
		return false;
	if (month < 1 || month > 12)
		return false;
	int daysInMonth[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
	if (day < 1 || day > daysInMonth[month - 1])
		return false;
	return true;
}

bool BitcoinDB::parseLine(const std::string& line, std::string& date, double& value)
{
	std::size_t pipePos = line.find('|');
	if (pipePos == std::string::npos)
	{
		date = line;
		std::cerr << "Error: bad input => " << date << std::endl;
		return false;
	}

	date = line.substr(0, pipePos);
	std::string valueStr = line.substr(pipePos + 1);

	date.erase(0, date.find_first_not_of(" \t"));
	date.erase(date.find_last_not_of(" \t") + 1);
	valueStr.erase(0, valueStr.find_first_not_of(" \t"));
	valueStr.erase(valueStr.find_last_not_of(" \t") + 1);

	if (!isValidDate(date))
	{
		std::cerr << "Error: bad input => " << date << std::endl;
		return false;
	}

	value = std::strtod(valueStr.c_str(), NULL);
	if (value < 0)
	{
		std::cerr << "Error: not a positive number." << std::endl;
		return false;
	}
	if (value > 1000)
	{
		std::cerr << "Error: too large a number." << std::endl;
		return false;
	}
	return true;
}

bool BitcoinDB::loadFile(const std::string& filename)
{
	std::ifstream file(filename.c_str());
	if (!file)
	{
		std::cerr << "Error: could not open input file. " << filename << std::endl;
		return false;
	}

	std::string line;
	if (!std::getline(file, line))
	{
		std::cerr << "Error: empty file." << std::endl;
		file.close();
		return false;
	}

	line.erase(0, line.find_first_not_of(" \t"));
	line.erase(line.find_last_not_of(" \t") + 1);
	
	if (line != "date | value")
	{
		std::cerr << "Error: first line must be 'date | value'" << std::endl;
		file.close();
		return false;
	}

	while (std::getline(file, line))
	{
		if (line.empty())
			continue;

		std::string date;
		double value;

		if (!parseLine(line, date, value))
			continue;

		std::map<std::string, float>::iterator it = map.lower_bound(date);
		if (it == map.end() || it->first != date)
		{
			if (it == map.begin())
			{
				std::cerr << "Error: no exchange rate available for date " << date << std::endl;
				continue;
			}
			--it;
		}

		float rate = it->second;
		double result = value * rate;

		std::cout << date << " => " << value << " = " << result << std::endl;
	}

	file.close();
	return true;
}

bool BitcoinDB::loadDatabase(const std::string& filename)
{
	std::ifstream file(filename.c_str());
	if (!file)
	{
		std::cerr << "Error: could not open database file: " << filename << std::endl;
		return false;
	}

	std::string line;
 	if (!std::getline(file, line))
	{
		std::cerr << "Error: empty database file." << std::endl;
		return false;
	}

	line.erase(0, line.find_first_not_of(" \t"));
	line.erase(line.find_last_not_of(" \t") + 1);

	if (line != "date,exchange_rate")
	{
		std::cerr << "Error: first line must be 'date,exchange_rate'" << std::endl;
		return false;
	}

	while (std::getline(file, line))
	{
		if (line.empty())
			continue;

		std::size_t commaPos = line.find(',');
		if (commaPos == std::string::npos)
		{
			std::cerr << "Error: bad database line => " << line << std::endl;
			continue;
		}

		std::string date = line.substr(0, commaPos);
		std::string rateStr = line.substr(commaPos + 1);

		date.erase(0, date.find_first_not_of(" \t"));
		date.erase(date.find_last_not_of(" \t") + 1);
		rateStr.erase(0, rateStr.find_first_not_of(" \t"));
		rateStr.erase(rateStr.find_last_not_of(" \t") + 1);

		if (!isValidDate(date))
		{
			std::cerr << "Error: bad date in database => " << date << std::endl;
			continue;
		}

		float rate = std::strtod(rateStr.c_str(), NULL);
		map[date] = rate;
	}

	file.close();
	return true;
}