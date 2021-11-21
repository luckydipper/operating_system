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
	safe_sequence.resize(num_process);
}



bool operator<(const vector<int>& arrays, const int min_val)
{
	for (const int& elem : arrays)
	{
		if (elem >= min_val)
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

// 모든 원소에서 왼족 친구가 크냐
bool operator>=(const vector<int>& left, const vector<int>& right)
{
	vector<int> r_copy = left;
	for (unsigned int i = 0; i < r_copy.size(); i++)
	{
		if (left[i] < right[i])
			return false;
	}
	return true;
}

//모든 값이 value와 같냐
bool operator==(const vector<vector<int>>& left, const int value)
{
	for (const auto& row : left)
	{
		for (const int& elem : row)
		{
			if (elem == value)
				return false;
		}
	}
	return true;
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

bool operator==(const vector<int>& left, int val)
{
	for (int elem : left)
	{
		if (elem != val)
			return false;
	}
	return true;
}

bool BankerAlgorithm::FindSequence()
{
	vector<vector<int>> copy_need = needs;
	vector<int> copy_available = available;

	for (int i = 0; i < max.size(); i++)
	{
		//needs matrix의 모든 값이 0이면 return 
		if (copy_need == 0)
			return true;

		if (copy_available >= copy_need[i])
		{
			if (copy_need == 0)
			{
				safe_sequence.empty();
				return true;
			}
			// 모든 값을 0으로 만듬
			copy_available = copy_available - copy_need[i];
			for(auto& elem :copy_need[i])
				elem = 0; 
			copy_available = copy_available + max[i];
			safe_sequence.push_back(i); 
		}
	}
	return false;
	
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