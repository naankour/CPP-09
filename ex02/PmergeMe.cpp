/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 14:07:41 by naankour          #+#    #+#             */
/*   Updated: 2026/04/09 18:33:07 by naankour         ###   ########.fr       */
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


std::vector<int> mergeInsertSort(std::vector<int> bigs )
{
	std::vector<int> bigPairs;
	std::vector<int> smallPairs;


	int left = -1;
	bool hasLeft = false;

	if (bigs.size() <= 1)
	return (bigs);
	
	if ((bigs.size() % 2) != 0)
	{
		left = bigs.back();
		bigs.pop_back();
		hasLeft = true;
	}

	for (size_t i = 0; i + 1 < bigs.size(); i+=2)
	{
		if (bigs[i] > bigs[i + 1])
		{
			bigPairs.push_back(bigs[i]);
			smallPairs.push_back(bigs[i+1]);
		}
		else
		{
			bigPairs.push_back(bigs[i+1]);
			smallPairs.push_back(bigs[i]);
		}	
	}
	bigPairs = mergeInsertSort(bigPairs);
	
	std::vector<int> sorted;
	sorted.push_back(smallPairs[0]);
	for(size_t i = 0; i < bigPairs.size(); i++)
		sorted.push_back(bigPairs[i]);

	if (hasLeft)
	{
		std::vector<int>::iterator position = std::lower_bound(sorted.begin(), sorted.end(), left);
		sorted.insert(position, left);
	}
	
	std::cout << "SORTED: ";
	for (size_t i = 0; i < sorted.size(); i++)
		std::cout << sorted[i] << " ";
	std::cout << std::endl;

	return(sorted);
}


std::vector<size_t> buildJacob(size_t size)
{
    std::vector<size_t> order;
    std::vector<size_t> jacob;

    if (size == 0)
        return (order);

    jacob.push_back(1);
    jacob.push_back(3);

    while (jacob.back() < size)
    {
        size_t next = jacob[jacob.size() - 1] + 2 * jacob[jacob.size() - 2];
        jacob.push_back(next);
    }

    size_t prev = 1;
    for (size_t i = 1; i < jacob.size(); i++)
    {
        size_t curr = jacob[i];
        for (size_t j = curr; j > prev; j--)
        {
            if (j <= size)
                order.push_back(j);
        }
        prev = curr;
    }
    return (order);
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

	std::vector<int> finalChain;
	finalChain = mergeInsertSort(bigs);
	finalChain.insert(finalChain.begin(), smalls[0]);

	std::cout << "SORTED with smallest: ";
	for (size_t i = 0; i < finalChain.size(); i++)
		std::cout << finalChain[i] << " ";
	std::cout << std::endl;

	std::vector<size_t> jacob = buildJacob(smalls.size());
	std::cout << "JACOB: ";
	for (size_t i = 0; i < jacob.size(); i++)
		std::cout << jacob[i] << " ";
	std::cout << std::endl;
	
	std::vector<bool> inserted(smalls.size(), false);

	for(size_t i = 0; i < jacob.size(); i++)
	{
		size_t index = jacob[i] - 1;
		if (index >= smalls.size())
			continue;
		std::vector<int>::iterator position = std::lower_bound(finalChain.begin(), finalChain.end(), smalls[index]);
		finalChain.insert(position, smalls[index]);
		inserted[index] = true;
	}

	for(size_t i = 0; i < smalls.size(); i++)
	{
		if (inserted[i] == true)
			continue;

		std::vector<int>::iterator position = std::lower_bound(finalChain.begin(), finalChain.end(), smalls[i]);
		finalChain.insert(position, smalls[i]);
	}

	std::cout << "After: ";
	for (size_t i = 0; i < finalChain.size(); i++)
		std::cout << finalChain[i] << " ";
	std::cout << std::endl;

	if (left != -1)
	{
		std::vector<int>::iterator position = std::lower_bound(finalChain.begin(), finalChain.end(), left);
		finalChain.insert(position, left);
	}
	
	// finalChain.push_back(smallPairs[0].big);
	// for (size_t i = 0; i < bigPairs.size(); i++)
	// 	finalChain.push_back(bigPairs[i].big);

}

void PmergeMe::algoDeque()
{
	
}