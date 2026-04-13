/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 14:07:41 by naankour          #+#    #+#             */
/*   Updated: 2026/04/13 17:18:29 by naankour         ###   ########.fr       */
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


//methode avec les paires 
// std::vector<int> mergeInsertSort(std::vector<int> arr)
// {
//     if (arr.size() <= 1)
//         return arr;

//     int odd = -1;
//     bool hasOdd = false;

//     if (arr.size() % 2 != 0)
//     {
//         odd = arr.back();
//         arr.pop_back();
//         hasOdd = true;
//     }

//     // 1. création des paires
//     std::vector<Pair> pairs;
//     for (size_t i = 0; i + 1 < arr.size(); i += 2)
//     {
//         Pair p;
//         if (arr[i] > arr[i + 1])
//         {
//             p.big = arr[i];
//             p.small = arr[i + 1];
//         }
//         else
//         {
//             p.big = arr[i + 1];
//             p.small = arr[i];
//         }
//         pairs.push_back(p);
//     }

//     // 2. extraire bigs
//     std::vector<int> bigs;
//     for (size_t i = 0; i < pairs.size(); i++)
//         bigs.push_back(pairs[i].big);

//     // 3. tri récursif des bigs
//     bigs = mergeInsertSort(bigs);

//     // 4. réordonner les pairs selon bigs triés
//     std::vector<Pair> sortedPairs;
//     std::vector<bool> used(pairs.size(), false);
//     for (size_t i = 0; i < bigs.size(); i++)
//     {
//         for (size_t j = 0; j < pairs.size(); j++)
//         {
//             if (!used[j] && pairs[j].big == bigs[i])
//             {
//                 sortedPairs.push_back(pairs[j]);
//                 used[j] = true;
//                 break;
//             }
//         }
//     }

//     // 5. résultat initial = bigs triés
//     std::vector<int> result = bigs;

//     // 6. smalls dans l'ordre associé aux bigs triés
//     std::vector<int> smalls;
//     for (size_t i = 0; i < sortedPairs.size(); i++)
//         smalls.push_back(sortedPairs[i].small);

//     // 7. smalls[0] est forcément <= bigs[0], insertion gratuite en tête
//     result.insert(result.begin(), smalls[0]);

//     // 8. insertion des smalls restants avec Jacobsthal + borne optimisée
//     std::vector<size_t> jacob = buildJacob(smalls.size());
//     for (size_t i = 0; i < jacob.size(); i++)
//     {
//         size_t index = jacob[i];
//         if (index == 0 || index >= smalls.size())
//             continue;

//         int value = smalls[index];
//         int big = sortedPairs[index].big;

//         std::vector<int>::iterator bigPos = std::find(result.begin(), result.end(), big);
//         std::vector<int>::iterator pos = std::lower_bound(result.begin(), bigPos, value);
//         result.insert(pos, value);
//     }

//     // 9. élément impair
//     if (hasOdd)
//     {
//         std::vector<int>::iterator pos = std::lower_bound(result.begin(), result.end(), odd);
//         result.insert(pos, odd);
//     }
// 	std::cout << "SORTED: ";
// 	for (size_t i = 0; i < result.size(); i++)
// 		std::cout << result[i] << " ";
// 	std::cout << std::endl;
//     return result;
// }


//en prenantn en compte l ordre des bigs lie au small
// std::vector<int> mergeInsertSort(std::vector<int> arr)
// {
//     if (arr.size() <= 1)
//         return (arr);

//     int odd = -1;
//     bool hasOdd = false;

//     if ((arr.size() % 2) != 0)
//     {
//         odd = arr.back();
//         arr.pop_back();
//         hasOdd = true;
//     }

//     std::vector<int> bigs, smalls;
//     for (size_t i = 0; i + 1 < arr.size(); i += 2)
//     {
//         if (arr[i] > arr[i + 1])
//         { bigs.push_back(arr[i]); smalls.push_back(arr[i + 1]); }
//         else
//         { bigs.push_back(arr[i + 1]); smalls.push_back(arr[i]); }
//     }

//     std::vector<int> bigsBeforeSort = bigs;

//     bigs = mergeInsertSort(bigs);

//     std::vector<int> sortedSmalls;
//     std::vector<bool> used(bigsBeforeSort.size(), false);
//     for (size_t i = 0; i < bigs.size(); i++)
//     {
//         for (size_t j = 0; j < bigsBeforeSort.size(); j++)
//         {
//             if (!used[j] && bigsBeforeSort[j] == bigs[i])
//             {
//                 sortedSmalls.push_back(smalls[j]);
//                 used[j] = true;
//                 break;
//             }
//         }
//     }

//     std::vector<int> result = bigs;
//     result.insert(result.begin(), sortedSmalls[0]);

//     std::vector<size_t> jacob = buildJacob(sortedSmalls.size());
//     for (size_t i = 0; i < jacob.size(); i++)
//     {
//         size_t index = jacob[i];
//         if (index == 0 || index >= sortedSmalls.size())
//             continue;

//         std::vector<int>::iterator bound = std::upper_bound(result.begin(), result.end(), bigs[index]);
//         std::vector<int>::iterator pos = std::lower_bound(result.begin(), bound, sortedSmalls[index]);
//         result.insert(pos, sortedSmalls[index]);
//     }

//     if (hasOdd)
//     {
//         std::vector<int>::iterator pos = std::lower_bound(result.begin(), result.end(), odd);
//         result.insert(pos, odd);
//     }
// 	std::cout << "SORTED: ";
// 	for (size_t i = 0; i < result.size(); i++)
// 		std::cout << result[i] << " ";
// 	std::cout << std::endl;
//     return result;
// }
// std::vector<int> mergeInsertSort(std::vector<int> arr )
// {
// 	if (arr.size() <= 1)
// 		return (arr);

// 	int odd = -1;
// 	bool hasOdd = false;

// 	if ((arr.size() % 2) != 0)
// 	{
// 		odd = arr.back();
// 		arr.pop_back();
// 		hasOdd = true;
// 	}

// 	std::vector<int> bigs;
// 	std::vector<int> smalls;

// 	for (size_t i = 0; i + 1 < arr.size(); i += 2)
// 	{
// 		if (arr[i] > arr[i + 1])
// 		{
// 			bigs.push_back(arr[i]);
// 			smalls.push_back(arr[i + 1]);
// 		}
// 		else
// 		{
// 			bigs.push_back(arr[i + 1]);
// 			smalls.push_back(arr[i]);
// 		}	
// 	}

// 	std::vector<int> bigsOrderBeforeSort = bigs;
// 	// std::vector<int> smallsReorder(bigs.size());
// // small ≤ big associé
// 	bigs = mergeInsertSort(bigs);
	
// 	std::vector<int> result = bigs;

// 	std::vector<size_t> jacob = buildJacob(smalls.size());
// 	for (size_t i = 0; i < jacob.size(); i++)
//     {
//         size_t index = jacob[i];
//         if (index < smalls.size())
//         {
//             std::vector<int>::iterator position = std::lower_bound(result.begin(), result.end(), smalls[index]);
//             result.insert(position, smalls[index]);
//         }
// 	}

// 	if (hasOdd)
// 	{
// 		std::vector<int>::iterator position = std::lower_bound(result.begin(), result.end(), odd);
// 		result.insert(position, odd);
// 	}
	
// 	std::cout << "SORTED: ";
// 	for (size_t i = 0; i < result.size(); i++)
// 		std::cout << result[i] << " ";
// 	std::cout << std::endl;

// 	return(result);
// }


void PmergeMe::algoVector()
{
	this->vector = mergeInsertSort(this->vector);

}

void PmergeMe::algoDeque()
{
	
}