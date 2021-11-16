#ifndef bankers_algorithm_21_11_16
#define bankers_algorithm_21_11_16

#include <vector>
using namespace std;

class BankerAlgorithm
{
private:
	static const int NUM_OF_PROCESS;
	static const int NUM_OF_RESOURCE;
	vector<vector<int>> max;
	vector<vector<int>> allocation;
	vector<vector<int>> needs;
	vector<int> available;

public:
	BankerAlgorithm(const int &num_process, const int &num_resource);
	bool Request(const int &process_index, const vector<int> &require);
	bool FindSequence() const;

	void SetMax(const vector<vector<int>>& set);
	void SetAlloc(const vector<vector<int>>& alloc);
	void SetNeed();
	void SetAvaiable(const vector<int>& avail);
};


#endif // !bankers_algorithm_21_11_16
