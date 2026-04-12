/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naziha <naziha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 14:07:41 by naankour          #+#    #+#             */
/*   Updated: 2026/04/12 23:40:28 by naziha           ###   ########.fr       */
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

std::vector<size_t> buildJacob(size_t size)
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
	std::cout << "JACOB SEQ: ";
	for (size_t i = 0; i < jacob.size(); i++)
		std::cout << jacob[i] << " ";
	std::cout << std::endl;
	
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
	std::cout << "ORDER INSERTION: ";
	for (size_t i = 0; i < order.size(); i++)
		std::cout << order[i] << " ";
	std::cout << std::endl;
    return (order);
}



// std::vector<int> mergeInsertSort(std::vector<int> arr)
// {
//     std::vector<int> bigPairs;
//     std::vector<int> smallPairs;

//     int straggler = -1;
//     bool hasStraggler = false;

//     if (arr.size() <= 1)
//         return (arr);
    
//     // ✅ Gérer l'impair
//     if ((arr.size() % 2) != 0)
//     {
//         straggler = arr.back();
//         arr.pop_back();
//         hasStraggler = true;
//     }

//     // ✅ ÉTAPE 1 : Former les paires 2 par 2
//     for (size_t i = 0; i + 1 < arr.size(); i += 2)
//     {
//         if (arr[i] > arr[i + 1])
//         {
//             bigPairs.push_back(arr[i]);
//             smallPairs.push_back(arr[i + 1]);
//         }
//         else
//         {
//             bigPairs.push_back(arr[i + 1]);
//             smallPairs.push_back(arr[i]);
//         }	
//     }

//     std::cout << "Paires formées:" << std::endl;
//     for (size_t i = 0; i < bigPairs.size(); i++)
//     {
//         std::cout << "  big: " << bigPairs[i] << " small: " << smallPairs[i] << std::endl;
//     }
//     if (hasStraggler)
//         std::cout << "  Straggler: " << straggler << std::endl;
    
//     // ✅ ÉTAPE 2 : RÉCURSION sur les bigs pour refaire des paires de paires
//     bigPairs = mergeInsertSort(bigPairs);
    
//     // ✅ ÉTAPE 3 : Créer result avec les bigs triés
//     std::vector<int> result = bigPairs;

//     // ✅ ÉTAPE 4 : Insérer les smalls avec Jacobsthal
//     std::vector<size_t> jacob = buildJacob(smallPairs.size());
//     for (size_t i = 0; i < jacob.size(); i++)
//     {
//         size_t index = jacob[i];
//         if (index < smallPairs.size())
//         {
//             std::vector<int>::iterator position = std::lower_bound(result.begin(), result.end(), smallPairs[index]);
//             result.insert(position, smallPairs[index]);
//         }
//     }
    
//     // ✅ ÉTAPE 6 : Insérer le straggler
//     if (hasStraggler)
//     {
//         std::vector<int>::iterator position = std::lower_bound(result.begin(), result.end(), straggler);
//         result.insert(position, straggler);
//     }

//     return (result);
// }


// void PmergeMe::algoVector()
// {
//     std::cout << "Before: ";
//     for (size_t i = 0; i < this->vector.size(); i++)
//         std::cout << this->vector[i] << " ";
//     std::cout << std::endl;

//     // ✅ APPEL UNIQUE avec TOUTE la liste
//     this->vector = mergeInsertSort(this->vector);

//     std::cout << "After: ";
//     for (size_t i = 0; i < this->vector.size(); i++)
//         std::cout << this->vector[i] << " ";
//     std::cout << std::endl;
// }
std::vector<int> mergeInsertSort(std::vector<int> arr )
{
	std::vector<int> bigPairs;
	std::vector<int> smallPairs;

	int left = -1;
	bool hasLeft = false;

	if (arr.size() <= 1)
		return (arr);
	
	if ((arr.size() % 2) != 0)
	{
		left = arr.back();
		arr.pop_back();
		hasLeft = true;
	}

	for (size_t i = 0; i + 1 < arr.size(); i+=2)
	{
		if (arr[i] > arr[i + 1])
		{
			bigPairs.push_back(arr[i]);
			smallPairs.push_back(arr[i+1]);
		}
		else
		{
			bigPairs.push_back(arr[i+1]);
			smallPairs.push_back(arr[i]);
		}	
	}
	
	bigPairs = mergeInsertSort(bigPairs);
	
	std::vector<int> result = bigPairs;

	std::vector<size_t> jacob = buildJacob(smallPairs.size());
	for (size_t i = 0; i < jacob.size(); i++)
    {
        size_t index = jacob[i];
        if (index < smallPairs.size())
        {
            std::vector<int>::iterator position = std::lower_bound(result.begin(), result.end(), smallPairs[index]);
            result.insert(position, smallPairs[index]);
        }
    }

	for (int i = bigPairs.size() - 1; i >= 1; i--)
    {
        std::vector<int>::iterator position = std::lower_bound(result.begin(), result.end(), bigPairs[i]);
        result.insert(position, bigPairs[i]);
    }
	
	if (hasLeft)
	{
		std::vector<int>::iterator position = std::lower_bound(result.begin(), result.end(), left);
		result.insert(position, left);
	}
	
	std::cout << "SORTED: ";
	for (size_t i = 0; i < result.size(); i++)
		std::cout << result[i] << " ";
	std::cout << std::endl;

	return(result);
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

	std::vector<size_t> jacobOrder = buildJacob(smalls.size());
	std::cout << "JACOB: ";
	for (size_t i = 0; i < jacobOrder.size(); i++)
		std::cout << jacobOrder[i] << " ";
	std::cout << std::endl;

	for(size_t i = 0; i < jacobOrder.size(); i++)
	{
		size_t index = jacobOrder[i];
		if (index < smalls.size())
		{
			std::vector<int>::iterator position = std::lower_bound(finalChain.begin(), finalChain.end(), smalls[index]);
			finalChain.insert(position, smalls[index]);
		}
		
	}

	if (left != -1)
	{
		std::vector<int>::iterator position = std::lower_bound(finalChain.begin(), finalChain.end(), left);
		finalChain.insert(position, left);
	}
	
	std::cout << "After: ";
	for (size_t i = 0; i < finalChain.size(); i++)
		std::cout << finalChain[i] << " ";
	std::cout << std::endl;

	// finalChain.push_back(smallPairs[0].big);
	// for (size_t i = 0; i < bigPairs.size(); i++)
	// 	finalChain.push_back(bigPairs[i].big);

}

void PmergeMe::algoDeque()
{
	
}