/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 14:10:41 by naankour          #+#    #+#             */
/*   Updated: 2026/03/03 15:38:28 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

//caracteres valides
bool RPN::checkFormat(std:: string& token)
{
	for (size_t i = 0; i < token.size(); i++)
	{
		if (token[i] == ' ' || token[i] == '\t')
			continue ;
		if (!isdigit(token[i]) && token[i] != '+' && token[i] != '-' && token[i] != '*' && token[i] != '/')
			return false;
	}
	return true;
}

bool RPN::isOperator(std::string& token)
{
	if (token.size() != 1)
		return false;
	if (token == "+" || token == "-" || token == "*" || token == "/")
		return true;
	else
		return false;
}

bool RPN::isOperand(std::string& token)
{
	if (token.size() != 1)
		return false;
	if (token >= "0" && token <= "9")
		return true;
	else
		return false;
}

int RPN::evaluateExpression(int num1, int num2, char op)
{
	switch(op)
	{
		case '+':
			return num1 + num2;
		case '-':
			return num1 - num2;
		case '*':
			return num1 * num2;
		case '/':
		{
			if(num2 == 0)
				throw 
			else
				return num1 / num2;
		}
		default:
	}
}