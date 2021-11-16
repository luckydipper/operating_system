#include "bankers.hpp"
#include <vector>
using namespace std;

BankerAlgorithm::BankerAlgorithm(int num_process, int num_resource)
{
	matrix.resize(num_process);
	for (auto &row : matrix)
	{
		row.resize(num_resource);
	}

}