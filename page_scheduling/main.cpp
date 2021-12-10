#include <deque>
#include <iostream>
#include "LRU.h"
#include "optimal.h"
using namespace std;



//int has_elem(const )

#include <iostream>
using namespace std;
int main()
{
	deque<int> reference_string = { 1, 2, 1, 4, 5, 6, 3, 4, 6, 3, 7, 3, 1, 5, 3, 7, 3, 4, 2, 4, 1, 4, 5, 1 };
	int page_frame_size = 4;

	int num_page_fault = LruNumPagefault(reference_string, page_frame_size);
	cout << "LRU page Fault number : " << num_page_fault << endl;


	int optimal_num_page_fault = OptimalNumPagefault(reference_string, page_frame_size);
	cout << "optimal page fault number : " << optimal_num_page_fault << endl;

	return 0;
}