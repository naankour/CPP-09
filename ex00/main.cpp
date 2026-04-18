/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 11:46:08 by naankour          #+#    #+#             */
/*   Updated: 2026/04/18 15:16:54 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Error: wrong number of arguments. Usage: ./btc <input_file>" << std::endl;
		return (1);
	}

	BitcoinDB db;

	if (!db.loadDatabase("data.csv"))
		return 1;

	if (!db.loadFile(argv[1]))
		return 1;
	return (0);
}