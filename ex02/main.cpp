/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 13:18:22 by naankour          #+#    #+#             */
/*   Updated: 2026/04/08 14:08:14 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main(int ac, char **av)
{
	PmergeMe p;
	try
	{
		p.parse(ac, av);
		p.run();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
}