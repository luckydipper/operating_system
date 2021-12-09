#include <deque>
#include <algorithm>// find
#include <iostream>
using namespace std;

int before_find(const deque<int>& feild, int end_index, const int finding_elem)
{
	int finding_offset = 0;

	for (end_index; 0 < end_index; end_index--)
	{
		if (feild[end_index] == finding_elem)
			return finding_offset;
		finding_offset++;
	}

	// there is no finding element 
	return -1;
}

//int has_elem(const )

int main()
{
	deque<int> reference_string = { 1, 2, 1, 4, 5, 6, 3, 4, 6, 3, 7, 3, 1, 5, 3, 7, 3, 4, 2, 4, 1, 4, 5, 1 };
	deque<int> page_frame(4, NULL);

	deque<int> reference_string_2 = { 7,0, 1,2,0,3,0,4,2,3,0,3,2,1,2,0,1,7,0,1 };
	deque<int> page_frame_2(3,NULL);

	int num_page_fault = 0;
	cout << before_find(reference_string_2, 5, 1);
	for (int processing_index = 0; processing_index < reference_string_2.size(); processing_index++)
	{

	}
	return 0;
}