#include "bankers.hpp"
#include <vector>
using namespace std;


//template<typename int>
//bool vector<int>::operator+(const int & a)
//{
//
//}

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

void BankerAlgorithm::SetMax(const vector<vector<int>>& set)
{
	max = set;
}

void BankerAlgorithm::SetAlloc(const vector<vector<int>>& alloc)
{
	allocation = alloc;
}


vector<vector<int>> operator-(const vector<vector<int>> &right, const vector<vector<int>> &left)
{
	vector<vector<int>> r_copy = right;
	for (int row = 0; row < right.size(); row++)
	{
		for (int col = 0; col < right[0].size(); col++)
			r_copy[row][col] -= left[row][col];
	}
	return r_copy;
}

void BankerAlgorithm::SetNeed()
{
	needs = max - allocation;
}

void BankerAlgorithm::SetAvaiable(const vector<int>& avail)
{
	available = avail;
}