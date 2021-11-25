#include "bankers.hpp"
#include <vector>
#include <iostream>
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

// 모든 원소에서 오른쪽 벡터가 크냐
bool operator<=(const vector<int>& left, const vector<int>& right)
{
	for (unsigned int i = 0; i < left.size(); i++)
	{
		if (left[i] > right[i])
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
			if (elem != value)
				return false;
		}
	}
	return true;
}

void VectorSetInt(vector<int>& left, const int value)
{
	for (int& elem : left)
		elem = value;
}


bool BankerAlgorithm::Request(const int& process_index, const vector<int>& require)
{
	if (available - require < 0)
		return false;
	
	available = available - require;
	needs[process_index] = needs[process_index] - require;
	allocation[process_index] = allocation[process_index] + require;
	return FindSequence();
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
	vector<vector<int>> need_processes = needs;
	vector<int> available_process = available;

	for (int i = 0; i < need_processes.size(); i++)
	{ 
		if (need_processes == 0) // all value should be 0
		{
			cout << "SAFE! There is safe sequence." << endl;
			for (int& elem : safe_sequence)
				cout << elem << " -> ";
			cout << "\n" << endl;
			return true;
		}
		else if (need_processes[i] == 0)
			continue;
		else if ( need_processes[i] <= available_process )
		{
			available_process = available_process + max[i];

			// set vector's all value 0으로 만듬
			VectorSetInt(need_processes[i], 0);
			safe_sequence.push_back(i);

			// search by one 
			i = -1;
		}
	}
	cout << "There is no safe sequence." << endl;
	safe_sequence.empty();
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

void BankerAlgorithm::EmptySafeSequence()
{
	safe_sequence.clear();
}