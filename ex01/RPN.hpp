/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 10:25:42 by naankour          #+#    #+#             */
/*   Updated: 2026/04/20 16:58:17 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once 
#include "stack"
#include <iostream>
#include <vector>

class RPN
{
	private:
		std::stack<int> s1;
	
	public:
		bool checkFormat(std:: string& token);
		bool isOperator(char token);
		bool isOperand(char token);
		int evaluateExpression(int num1, int num2, char op);
		int RPNalgo(std::string& token);
};