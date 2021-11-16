#include "bankers.hpp"
#include <vector>
using namespace std;


BankerAlgorithm::BankerAlgorithm(const int &num_process, const int &num_resource)
{
	//change size
	max.resize(num_process);
	for (auto &row : max)
		row.resize(num_resource);
	allocation = max;
	needs = max;
	available.resize(num_resource);
}

bool operator<(const vector<int>& arrays, const int element)
{
	for (const int& elem : arrays)
	{
		if (elem > element)
			return false;
	}
	return true;
}

vector<vector<int>> operator-(const vector<vector<int>>& right, const vector<vector<int>>& left)
{
	vector<vector<int>> r_copy = right;
	for (int row = 0; row < right.size(); row++)
	{
		for (int col = 0; col < right[0].size(); col++)
			r_copy[row][col] -= left[row][col];
	}
	return r_copy;
}

vector<int> operator-(const vector<int>& right, const vector<int>& left)
{
	vector<int> r_copy = right;
	for (int i = 0; i < r_copy.size(); i++)
		r_copy[i] = r_copy[i] - left[i];
	return r_copy;
}

vector<int> operator+(const vector<int>& right, const vector<int>& left)
{
	vector<int> r_copy = right;
	for (int i = 0; i < r_copy.size(); i++)
		r_copy[i] = r_copy[i] + left[i];
	return r_copy;
}

bool BankerAlgorithm::Request(const int& process_index, const vector<int>& require)
{
	if (available - require < 0)
		return false;
	
	available = available - require;
	needs[process_index] = needs[process_index] - require;
	allocation[process_index] = allocation[process_index] + require;
	return true;
}

void BankerAlgorithm::SetMax(const vector<vector<int>>& set)
{
	max = set;
}

void BankerAlgorithm::SetAlloc(const vector<vector<int>>& alloc)
{
	allocation = alloc;
}



void BankerAlgorithm::SetNeed()
{
	needs = max - allocation;
}

void BankerAlgorithm::SetAvaiable(const vector<int>& avail)
{
	available = avail;
}