/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 14:10:41 by naankour          #+#    #+#             */
/*   Updated: 2026/03/04 15:17:45 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

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
				throw std::runtime_error("Error: division by zero.");
			else
				return num1 / num2;
		}
		default:
			throw std::runtime_error("Error: invalid operator");
	}
}

std::vector<std::string> splitExpression(const std::string& expr)
{
	std::vector<std::string> tokens;
	for (size_t i = 0; i < expr.size(); i++)
	{
		if (expr[i] == ' ')
			continue;
		else
		{
			std::string temp;
			temp += expr[i];
			tokens.push_back(temp);
		}
	}
	return (tokens);
}

int RPN::RPNalgo(std::string& token)
{
	if (checkFormat(token) == false)
		throw std::runtime_error("Invalid format, only digits and + - * / operators are acepted.");
	
	std::vector<std::string> tokens = splitExpression(token);
	
	for (size_t i = 0; i < tokens.size(); i++)
	{
		std::string currentToken = tokens[i];

		if (isOperand(currentToken) == true)
		{
			s1.push((currentToken[0] - '0'));
		}
		else if (isOperator(currentToken) == true)
		{
			if (s1.size() < 2)
				throw std::runtime_error("Invalid RPN expression.");
			int num2 = s1.top();
			s1.pop();
			int num1 = s1.top();
			s1.pop();
			int result = evaluateExpression(num1, num2, currentToken[0]);
			s1.push(result);
		}
		else
		{
			throw std::runtime_error("Error: Token not expected.");
		}
	}
	
	if (s1.size() != 1)
	{
		throw std::runtime_error("Invalid RPN expression.");
	}
	return(s1.top());
}