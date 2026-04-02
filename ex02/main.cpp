/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 13:18:22 by naankour          #+#    #+#             */
/*   Updated: 2026/04/02 16:27:09 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

bool isValidPositiveInt(const std::string &arg)
{
	if (arg.empty())
		return false;

	size_t start = 0;
	if (arg[0] == '+')
		start = 1;
	
	if (start == arg.length())
		return (false);
	for (size_t i = start; i < arg.length(); i++)
	{
		if (!isdigit(arg[i]))
			return false;
	}

	if (arg.length() > 10)
		return false;

	long val = strtol(arg.c_str(), NULL, 10);
	if (val > 0 && val <= INT_MAX)
		return (true);
	else 
		return (false);
}

int main(int ac, char **av)
{
	if (ac < 2)
	{
		std::cerr << "Not enough arguments" << std::endl;
		return (1);
	}
	
	std::vector<int> nums;
	for (int i = 1; i < ac; i++)
	{
		std::string arg = av[i];
		if (!isValidPositiveInt(arg))
		{
			std::cerr << "Error: only positive intergers are accepted." << std::endl;
			return (1);
		}
		nums.push_back(static_cast<int>(strtol(arg.c_str(), NULL, 10)));
	}

	std::cout << "Before: ";
	for (size_t i = 0; i < nums.size(); i++)
		std::cout << nums[i] << " ";
	std::cout << std::endl;
	
}