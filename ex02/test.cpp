
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


// Génère la séquence de Jacobsthal pour l'ordre d'insertion optimal
static std::vector<int> jacobsthalSequence(int n)
{
	std::vector<int> seq;
	if (n <= 0) return seq;
	
	int j0 = 0, j1 = 1;
	seq.push_back(1);
	
	while (j1 < n)
	{
		int j2 = j1 + 2 * j0;
		if (j2 < n)
			seq.push_back(j2);
		j0 = j1;
		j1 = j2;
	}
	return seq;
}

// Merge-Insert Sort récursif sur toute la liste
std::vector<int> mergeInsertSort(std::vector<int> data)
{
	// Cas de base
	if (data.size() <= 1)
		return data;
	
	int leftover = -1;
	bool hasLeftover = false;
	
	// Gérer le cas impair
	if (data.size() % 2 != 0)
	{
		leftover = data.back();
		data.pop_back();
		hasLeftover = true;
	}
	
	// Étape 1: Créer les paires et séparer en grands et petits
	std::vector<int> bigs;
	std::vector<int> smalls;
	
	for (size_t i = 0; i + 1 < data.size(); i += 2)
	{
		if (data[i] > data[i + 1])
		{
			bigs.push_back(data[i]);
			smalls.push_back(data[i + 1]);
		}
		else
		{
			bigs.push_back(data[i + 1]);
			smalls.push_back(data[i]);
		}
	}
	
	// Étape 2: Tri récursif des GRANDS
	bigs = mergeInsertSort(bigs);
	
	// Étape 3: Insertion des PETITS avec optimisation Jacobsthal
	std::vector<int> result;
	result.push_back(smalls[0]);
	for (size_t i = 0; i < bigs.size(); i++)
		result.push_back(bigs[i]);
	
	// Insérer les petits restants en utilisant la séquence de Jacobsthal
	std::vector<int> jacobSeq = jacobsthalSequence(smalls.size());
	
	for (int idx : jacobSeq)
	{
		if (idx < (int)smalls.size())
		{
			std::vector<int>::iterator pos = 
				std::lower_bound(result.begin(), result.end(), smalls[idx]);
			result.insert(pos, smalls[idx]);
		}
	}
	
	// Insérer les petits non traités (ceux entre les indices Jacobsthal)
	for (size_t i = 1; i < smalls.size(); i++)
	{
		bool found = false;
		for (int idx : jacobSeq)
		{
			if (idx == (int)i)
			{
				found = true;
				break;
			}
		}
		if (!found)
		{
			std::vector<int>::iterator pos = 
				std::lower_bound(result.begin(), result.end(), smalls[i]);
			result.insert(pos, smalls[i]);
		}
	}
	
	// Insérer le nombre restant si la liste était impaire
	if (hasLeftover)
	{
		std::vector<int>::iterator pos = 
			std::lower_bound(result.begin(), result.end(), leftover);
		result.insert(pos, leftover);
	}
	
	return result;
}

void PmergeMe::algoVector()
{
	std::vector<int> sorted = mergeInsertSort(this->vector);
	
	std::cout << "After: ";
	for (size_t i = 0; i < sorted.size(); i++)
		std::cout << sorted[i] << " ";
	std::cout << std::endl;
}

void PmergeMe::algoDeque()
{
	
}