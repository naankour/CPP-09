/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 11:46:05 by naankour          #+#    #+#             */
/*   Updated: 2025/12/17 15:39:27 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <map>
#include <string>

class BitcoinDB
{
	private:
		std::map<std::string, float> map;
	public:
		BitcoinDB();
		~BitcoinDB();
		BitcoinDB(const BitcoinDB& other);
		BitcoinDB& operator=(const BitcoinDB& other);

};