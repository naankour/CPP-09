/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 14:07:41 by naankour          #+#    #+#             */
/*   Updated: 2026/04/08 17:51:09 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}

PmergeMe::~PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe& other) 
{
	this->vector = other.vector;
	this->deque = other.deque;
}

PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
	if (this != &other)
	{
		this->vector = other.vector;
		this->deque = other.deque;
	}
	return (*this);
}

static bool isValidPositiveInt(const std::string &arg)
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
	if (val >= 0 && val <= INT_MAX)
		return (true);
	else 
		return (false);
}

void PmergeMe::parse(int ac, char **av)
{
	if (ac < 2)
		throw std::runtime_error("Error: Not enough arguments");

	for (int i = 1; i < ac; i++)
	{
		std::string arg = av[i];
		if (!isValidPositiveInt(arg))
			throw std::runtime_error("Error: only positive intergers are accepted.");
		this->vector.push_back(static_cast<int>(strtol(arg.c_str(), NULL, 10)));
		this->deque.push_back(static_cast<int>(strtol(arg.c_str(), NULL, 10)));
	}
}

void PmergeMe::run()
{
	std::cout << "Before: ";
	for (size_t i = 0; i < this->vector.size(); i++)
		std::cout << this->vector[i] << " ";
	std::cout << std::endl;
	this->algoVector();
}





 
std::vector<Pair> mergeInsertSort(std::vector<Pair> list)
{
	std::vector<Pair> bigPairs;
	std::vector<Pair> smallPairs;
	
	Pair left;
	bool hasLeft = false;
	
	if (list.size() <= 1)
	return (list);
	
	if ((list.size() % 2) != 0)
	{
		left = list.back();
		hasLeft = true;
	}

	for (size_t i = 0; i + 1 < list.size(); i+=2)
	{
		if (list[i].big > list[i + 1].big)
		{
			bigPairs.push_back(list[i]);
			smallPairs.push_back(list[i+1]);
		}
		else
		{
			bigPairs.push_back(list[i+1]);
			smallPairs.push_back(list[i]);
		}	
	}
	bigPairs = mergeInsertSort(bigPairs);
	
	// if (hasLeft)
	// 	bigPairs.push_back(left);
	
	// std::cout << "BIGS SORTED: ";
	// for (size_t i = 0; i < bigPairs.size(); i++)
	// 	std::cout << " bigg: " << bigPairs[i].big;
	// std::cout << std::endl;
		
	// std::vector<int> final;
		
	// final.push_back(smallPairs[0].small);
	// for (size_t i = 0; i < bigPairs.size(); i++)
	// 	final.push_back(bigPairs[i].big);

	return(list);
}

void PmergeMe::algoVector()
{
	std::vector<Pair> list;

	int left = -1;
	if ((this->vector.size() % 2) != 0)
		left = this->vector.back();

	for (size_t i = 0; i + 1 < this->vector.size(); i+=2)
	{
		Pair pair;
		if (vector[i] >= vector[i + 1])
		{
			pair.big = vector[i];
			pair.small = vector[i + 1];
		}
		else if (vector[i] < vector[i + 1])
		{
			pair.big = vector[i + 1];
			pair.small = vector[i];
		}
		list.push_back(pair);
	}

	for (size_t i = 0; i < list.size(); i++)
	{
		std::cout << "big: " << list[i].big;
		std::cout << " small: " << list[i].small << std::endl;
	}
	std::cout << "Reste: " << left << std::endl;

	std::vector<int> bigs;
	std::vector<int> smalls;
	// std::vector<int> reste;

	for (size_t i = 0; i < list.size(); i++)
		bigs.push_back(list[i].big);
	for (size_t i = 0; i < list.size(); i++)
		smalls.push_back(list[i].small);

	std::cout << "Bigs : ";
	for (size_t i = 0; i < bigs.size(); i++)
		 std::cout << bigs[i] << " ";
	std::cout << std::endl;

	std::cout << "Smalls : ";
	for (size_t i = 0; i < smalls.size(); i++)
		 std::cout << smalls[i] << " ";
	std::cout << std::endl;
	mergeInsertSort(list);
	
	
}

void PmergeMe::algoDeque()
{
	
}