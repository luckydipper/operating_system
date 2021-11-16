#ifndef bankers_algorithm_21_11_16
#define bankers_algorithm_21_11_16

#include <vector>
using namespace std;

class BankerAlgorithm
{
private:
	static const int NUM_OF_PROCESS;
	static const int NUM_OF_RESOURCE;
	vector<vector<int>> matrix;

public:
	BankerAlgorithm(int num_process, int num_resource);
};


#endif // !bankers_algorithm_21_11_16
