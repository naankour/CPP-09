/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 10:28:42 by naankour          #+#    #+#             */
/*   Updated: 2026/02/27 11:42:14 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

//caracteres valides
bool checkFormat(std:: string& token)
{
	for (size_t i = 0; i < token.size(); i++)
	{
		if (token[i] == ' ' || token[i] == '\t')
			continue ;
		if (!isdigit(token[i]) && token[i] != '+' && token[i] != '-' && token[i] != '*' && token[i] != '/')
			return false;
	}
	return true;
}

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Error: Wrong number of arguments." << std::endl;
		return (1);
	}
	std::string token = argv[1];
	
	std::cout << token << std::endl;

	if (checkFormat(token) == false)
	{
		std::cout << "Error: Incorrect format only digits and + - * / are allowed" << std::endl;
		return (1);
	}
	//regles logiques
	// 5 1 2 +?
	//
	//a la fin il foit y avoir n valeurs et n - 1 operateurs
	// on parcourt token, on check si cest un digit, si cest le cas, on convertit avec atoi et on ajoute a la stack
	
}