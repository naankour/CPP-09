/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazihaaankour <nazihaaankour@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 11:46:08 by naankour          #+#    #+#             */
/*   Updated: 2025/12/23 00:47:00 by nazihaaanko      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cout << "Error could not open file." << std::endl;
		return (1);
	}

	BitcoinDB db;

	if (!db.loadDatabase("data.csv"))
		return 1;

	if (!db.loadFile(argv[1]))
		return 1;
}