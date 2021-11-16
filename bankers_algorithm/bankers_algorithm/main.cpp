#include <iostream>
#include <vector>
#include "bankers.hpp"
using namespace std;

int main()
{
	BankerAlgorithm bankers_algorithm(5, 4);

	vector<vector<int>> max = { {6,0,1,2},
								{1,7,5,0},
								{2,3,5,6},
								{1,6,5,3},
								{1,6,5,6} };

	vector<vector<int>> alloc = { {4,0,0,1},
								  {1,1,0,0},
								  {1,2,5,4},
								  {0,6,3,3},
								  {0,2,1,2} };

	vector<int> available = {3,2,1,1};



	bankers_algorithm.SetMax(max);
	bankers_algorithm.SetAlloc(alloc);
	bankers_algorithm.SetNeed();
	bankers_algorithm.SetAvaiable(available);
	

	return 0;
}