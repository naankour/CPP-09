/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 10:25:42 by naankour          #+#    #+#             */
/*   Updated: 2026/03/03 15:24:56 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once 
#include "stack"
#include <iostream>

class RPN
{
	private:
		std::stack<int> s1;
	
	public:
		bool checkFormat(std:: string& token);
		bool isOperator(std::string& token);
		bool isOperand(std::string& token);
		int evaluateExpression(int num1, int num2, char op);
};