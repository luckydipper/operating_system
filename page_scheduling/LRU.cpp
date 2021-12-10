#include <deque>
#include <algorithm>
#include "LRU.h"

using namespace std;


int LruNumPagefault(const deque<int>& reference_string, const int& num_frame)
{
	deque<int> ram_frames(num_frame, -1);
	int num_page_fault = 0;
	for (int index = 0; index < reference_string.size(); index++)
	{
		int demend_page_id = reference_string[index];
		bool caching_complete = PageCaching(ram_frames, demend_page_id);

		if (caching_complete)
			continue;
		else
		{
			num_page_fault++;
			int extract_index =  ChooseExtractIndex(reference_string, ram_frames, index);
			ram_frames[extract_index] = demend_page_id;
		}
	}
	return num_page_fault;
}


bool PageCaching(deque<int>& frame, int demend_page_index)
{
	deque<int>::iterator finding_iter = find(frame.begin(), frame.end(), demend_page_index);
	if (finding_iter == frame.end())
		return false;
	else
		return true;
}

int ChooseExtractIndex(const deque<int>& reference_string, const deque<int>& frame, int loaded_index)
{
	int index = 0;
	deque<int> offset_container(frame.size());
	
	for (int i=0; i< frame.size(); i++)
	{
		if (frame[i] == -1)
			return i;
	}

	for (const int& page_id : frame)
	{
		int offset = FindBeforeOffset(reference_string, loaded_index, page_id);
		if (offset == -1)
			return index;
		offset_container[index] = offset;
		index++;
	}
	int least_recently_use_index = max_element(offset_container.begin(), offset_container.end()) - offset_container.begin();
	return least_recently_use_index;
}

int FindBeforeOffset(const deque<int>& feild, int end_index, const int finding_elem)
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
