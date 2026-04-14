/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 13:18:22 by naankour          #+#    #+#             */
/*   Updated: 2026/04/14 15:45:46 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main(int ac, char **av)
{

	struct timeval start;
	struct timeval end;

	PmergeMe p;
	try
	{
		gettimeofday(&start, NULL);
		p.parse(ac, av);
		p.algoVector();
		gettimeofday(&end, NULL);
		
		double time = (end.tv_sec - start.tv_sec) * 1000000.0 + (end.tv_usec - start.tv_usec);
		std::cout << "Time to process a range of " << p.getVectorSize() << " elements with std::vector : " << time << "us" << std::endl;

	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

	try
	{
		gettimeofday(&start, NULL);
		p.parse(ac, av);
		p.algoDeque();
		gettimeofday(&end, NULL);

		double time = (end.tv_sec - start.tv_sec) * 1000000.0 + (end.tv_usec - start.tv_usec);
		std::cout << "Time to process a range of " << p.getDequeSize() << " elements with std::deque : " << time << "us" << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
}