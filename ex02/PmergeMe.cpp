/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 14:07:41 by naankour          #+#    #+#             */
/*   Updated: 2026/04/18 16:27:36 by naankour         ###   ########.fr       */
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


size_t PmergeMe::getVectorSize() const
{
	return (this->vector.size());
}

size_t PmergeMe::getDequeSize() const
{
	return (this->deque.size());
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
	this->vector.clear();
	this->deque.clear();

	if (ac < 2)
		throw std::runtime_error("Error: Not enough arguments");

	for (int i = 1; i < ac; i++)
	{
		std::string arg = av[i];
		if (!isValidPositiveInt(arg))
			throw std::runtime_error("Error: only positive integers are accepted.");
		this->vector.push_back(static_cast<int>(strtol(arg.c_str(), NULL, 10)));
		this->deque.push_back(static_cast<int>(strtol(arg.c_str(), NULL, 10)));
	}
}

std::vector<size_t> buildJacobVector(size_t size)
{
	std::vector<size_t> order;
	
	if (size == 0)
		return (order);
	
	if (size == 1)
	{
		order.push_back(0);
		return (order);
	}
	
	std::vector<size_t> jacob;
	jacob.push_back(0);
	jacob.push_back(1);

	while (jacob.back() < size)
	{
		size_t next = jacob[jacob.size() - 1] + 2 * jacob[jacob.size() - 2];
		jacob.push_back(next);
	}

	std::vector<bool> used(size, false);
	for (size_t i = 1; i < jacob.size(); i++)
	{
		size_t start = jacob[i - 1] + 1;
		size_t end;

		if (jacob[i] < size)
			end = jacob[i];
		else
			end = size - 1;
	
		for (size_t j = end; j >= start && j < size; j--)
		{
			if (used[j] == false)
			{
				order.push_back(j);
				used[j] = true;
			}
		}
	}

	for (size_t i = 0; i < size; i++)
	{
		if (used[i] == false)
			order.push_back(i);
	}
	return (order);
}

std::vector<int> mergeInsertSortVector(std::vector<int> arr)
{
	if (arr.size() <= 1)
		return arr;

	int odd = -1;
	bool hasOdd = false;

	if (arr.size() % 2 != 0)
	{
		odd = arr.back();
		arr.pop_back();
		hasOdd = true;
	}

	std::vector<Pair> pairs;
	for (size_t i = 0; i + 1 < arr.size(); i += 2)
	{
		Pair p;
		if (arr[i] > arr[i + 1])
		{
			p.big = arr[i];
			p.small = arr[i + 1];
		}
		else
		{
			p.big = arr[i + 1];
			p.small = arr[i];
		}
		pairs.push_back(p);
	}
	
	std::vector<int> bigs;
	for (size_t i = 0; i < pairs.size(); i++)
		bigs.push_back(pairs[i].big);

	bigs = mergeInsertSortVector(bigs);

	//réordonner pairs selon bigs triés
	std::vector<Pair> sortedPairs;
	std::vector<bool> used(pairs.size(), false);
	for (size_t i = 0; i < bigs.size(); i++)
	{
		for (size_t j = 0; j < pairs.size(); j++)
		{
			if (!used[j] && pairs[j].big == bigs[i])
			{
				sortedPairs.push_back(pairs[j]);
				used[j] = true;
				break;
			}
		}
	}

	std::vector<int> result = bigs;

	//smalls dans l'ordre associé aux bigs triés
	std::vector<int> smalls;
	for (size_t i = 0; i < sortedPairs.size(); i++)
		smalls.push_back(sortedPairs[i].small);

	//smalls[0 <= bigs[0]
	result.insert(result.begin(), smalls[0]);

	//inserer smalls avec jacob et borne du big associe
	std::vector<size_t> jacob = buildJacobVector(smalls.size());
	for (size_t i = 0; i < jacob.size(); i++)
	{
		size_t index = jacob[i];
		if (index == 0 || index >= smalls.size())
			continue;

		int value = smalls[index];
		int big = sortedPairs[index].big;

		std::vector<int>::iterator bigPos = std::find(result.begin(), result.end(), big);
		std::vector<int>::iterator pos = std::lower_bound(result.begin(), bigPos, value);
		result.insert(pos, value);
	}

	if (hasOdd)
	{
		std::vector<int>::iterator pos = std::lower_bound(result.begin(), result.end(), odd);
		result.insert(pos, odd);
	}
	return (result);
}

void PmergeMe::algoVector()
{
	std::cout << "Before:   ";
	for (size_t i = 0; i < this->vector.size(); i++)
		std::cout << this->vector[i] << " ";
	std::cout << std::endl;

	this->vector = mergeInsertSortVector(this->vector);
	
	std::cout << "After:    ";
	for (size_t i = 0; i < this->vector.size(); i++)
		std::cout << this->vector[i] << " ";
	std::cout << std::endl;

}

std::deque<size_t> buildJacobDeque(size_t size)
{
	std::deque<size_t> order;
	
    if (size == 0)
		return (order);
	
	if (size == 1)
	{
		order.push_back(0);
		return (order);
	}
	
	std::deque<size_t> jacob;
	jacob.push_back(0);
	jacob.push_back(1);

	while (jacob.back() < size)
	{
		size_t next = jacob[jacob.size() - 1] + 2 * jacob[jacob.size() - 2];
		jacob.push_back(next);
	}
	std::deque<bool> used(size, false);

	for (size_t i = 1; i < jacob.size(); i++)
	{
		size_t start = jacob[i - 1] + 1;
		size_t end;

		if (jacob[i] < size)
			end = jacob[i];
		else
			end = size - 1;
	
		for (size_t j = end; j >= start && j < size; j--)
		{
			if (used[j] == false)
			{
				order.push_back(j);
				used[j] = true;
			}
		}
	}

	for (size_t i = 0; i < size; i++)
	{
		if (used[i] == false)
			order.push_back(i);
	}
	return (order);
}


std::deque<int> mergeInsertSortDeque(std::deque<int> arr)
{
	if (arr.size() <= 1)
		return (arr);

	int odd = -1;
	bool hasOdd = false;

	if (arr.size() % 2 != 0)
	{
		odd = arr.back();
		arr.pop_back();
		hasOdd = true;
	}

	std::deque<Pair> pairs;
	for (size_t i = 0; i + 1 < arr.size(); i += 2)
	{
		Pair p;
		if (arr[i] > arr[i + 1])
		{
			p.small = arr[i + 1];
			p.big = arr[i];
		}
		else
		{
			p.small = arr[i];
			p.big = arr[i + 1];
		}
		pairs.push_back(p);
	}
	
	std::deque<int> bigs;
	for (size_t i = 0; i < pairs.size(); i++)
		bigs.push_back(pairs[i].big);
	
	bigs = mergeInsertSortDeque(bigs);

	std::deque<Pair> sortedPairs;
	std::deque<bool> used(pairs.size(), false);

	for (size_t i = 0; i < bigs.size(); i++)
	{
		for (size_t j = 0; j < pairs.size(); j++)
		{
			if (used[j] == false && pairs[j].big == bigs[i])
			{
				sortedPairs.push_back(pairs[j]);
				used[j] = true;
				break;
			}
		}
	}

	std::deque<int> result = bigs;

	std::deque<int> smalls;
	for (size_t i = 0; i < sortedPairs.size(); i++)
		smalls.push_back(sortedPairs[i].small);

	result.insert(result.begin(), smalls[0]);
	std::deque<size_t> jacob = buildJacobDeque(smalls.size());
	for (size_t i = 0; i < jacob.size(); i++)
	{
		size_t index = jacob[i];
		if (index == 0 || index >= smalls.size())
			continue;
		
		int value = smalls[index];
		int big = sortedPairs[index].big;

		std::deque<int>::iterator bigPos = std::find(result.begin(), result.end(), big);
		std::deque<int>::iterator pos = std::lower_bound(result.begin(), bigPos, value);
		result.insert(pos, value);
	}

	if (hasOdd)
	{
		std::deque<int>::iterator pos = std::lower_bound(result.begin(), result.end(), odd);
		result.insert(pos, odd);
	}
	return (result);
}

void PmergeMe::algoDeque()
{
	this->deque = mergeInsertSortDeque(this->deque);	
}