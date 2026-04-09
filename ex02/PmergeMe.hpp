/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 13:21:45 by naankour          #+#    #+#             */
/*   Updated: 2026/04/09 15:59:16 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <limits.h>
#include <deque>
#include <algorithm>

struct Pair
{
	int big;
	int small;
};

//si jai un vector de Pair
// on aura vector[0] = PAIR = big, small ?
// si ensuite je veux separer les grands et les petits 
//je dois faire un autre vector big et un autre vector small?

class PmergeMe
{
	private:
		std::vector<int> vector;
		std::deque<int> deque;

		void algoVector();
		void algoDeque();
	
	public:
		PmergeMe();
		~PmergeMe();
		PmergeMe(const PmergeMe& other);
		PmergeMe& operator=(const PmergeMe& other);

		void parse(int ac, char **av);
		void run();
};