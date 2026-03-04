/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 10:28:42 by naankour          #+#    #+#             */
/*   Updated: 2026/03/04 15:11:54 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Error: Wrong number of arguments." << std::endl;
		return (1);
	}
	
	std::string token = argv[1];
	RPN	expression;

	// std::cout << token << std::endl;
	try
	{
		{
			int result = expression.RPNalgo(token);
			std::cout << result << std::endl;
		}
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
}